/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

PiResiduos is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PiResiduos is distributed in the hope that it will 
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PiResiduos.  
If not, see <https://www.gnu.org/licenses/>.
*/
/**
@file outputForm.cpp
*/
#include "outputForm.h"

/////////////////////
////////////////////
//outputForm

int outputForm::storeDepMov(qtDatabase & localDatabase,qtDatabase & remoteDatabase,int remote_host_connected)
{
  int ret = -1;
  std::string sqliteQuery,mysqlQuery;
  std::string str_log_message;
  
  //getting sql queries
  storeMov(sqliteQuery,mysqlQuery,depOriginStation,localDatabase);

  //trying to remote save
  if(remote_host_connected)
    {
      str_log_message = "(CARGA) remote db -> ";
      str_log_message += mysqlQuery;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(NULL,mysqlQuery.c_str()))
	{
	  log_message("(CARGA) registro en BD remota parece OK", 1);
	  int sync=1;
	  //RECHECK!
	  check_last(mysqlQuery,depDestinationStation);
	  str_log_message = "(CARGA) chequeo redundante en BD remota -> ";
	  str_log_message += mysqlQuery;
	  log_message(str_log_message, 1);
	  if(remoteDatabase.query(NULL,mysqlQuery.c_str())) //NO SYNCRONIZED
	    sync=0;
	  else
	    {
	      if(remoteDatabase.retData2().empty())
		sync=0;
	    }
	  
	  if(sync)
	    {
	      log_message("(CARGA) chequeo redundante en BD remota parece OK", 1);
	      sqliteQuery.replace(sqliteQuery.length()-2,1,"1");
	    }
	  else
	    log_message("(CARGA) chequeo redundante en BD remota parece que FALLÓ", 1);

	  str_log_message = "(CARGA) local db -> ";
	  str_log_message += sqliteQuery;
	  log_message(str_log_message, 1);
	  if(!localDatabase.query(NULL,sqliteQuery.c_str())) //saving in local server
	    {
	      //deleting from transit
	      ret = 0;
	      mysqlQuery.clear();
	      mysqlQuery = "delete from transito_salidas where (FECHA_HORA =\"";
	      mysqlQuery += retDepDateTime();
	      mysqlQuery += "\" and CODIGO_ESTACION=";
	      mysqlQuery += std::to_string(depOriginStation->getCode());
	      mysqlQuery += ")";
	      str_log_message = "(CARGA) db remota -> ";
	      str_log_message += mysqlQuery;
	      log_message(str_log_message, 1);	      
	      if(remoteDatabase.query(NULL,mysqlQuery.c_str()))
		log_message("(CARGA) registro en BD remota parece ERROR", 2);
	      else
		log_message("(CARGA) registro en BD remota parece OK", 2);		

	      sqliteQuery.clear();
	      sqliteQuery = "delete from TRANSITO_SALIDAS where (FECHA_HORA =\"";
	      sqliteQuery += retDepDateTime();
	      sqliteQuery += "\")";
	      str_log_message = "(CARGA) db local -> ";
	      str_log_message += sqliteQuery;
	      log_message(str_log_message, 1);
	      if(localDatabase.query(NULL,sqliteQuery.c_str()))
		log_message("(CARGA) registro en BD local parece ERROR", 2);
	      else
		log_message("(CARGA) registro en BD local parece OK", 2);		

	      //if order, clean
	      if(!ret && retDepMovType() == DEF_MOV_SALIDA)
		{
		  char * sqlite;
		  char * mysql;
		  delOrder(sqlite,mysql,depOriginStation->getCode(),retDepCosCode(),retDepProdCode());
		  str_log_message = "(CARGA) db local -> ";
		  str_log_message += sqlite;
		  log_message(str_log_message, 1);
		  if(localDatabase.query(NULL,sqlite))
		    {
		      ret=-10;
		      log_message("(CARGA) registro en BD local parece ERROR", 2);
		    }
		  else
		    {
		      log_message("(CARGA) registro en BD local parece OK", 2);		
		    }
		  str_log_message = "(CARGA) db remota -> ";
		  str_log_message += mysql;
		  log_message(str_log_message, 1); 
		  if(remoteDatabase.query(NULL,mysql))
		    {
		      ret = -100;
		      log_message("(CARGA) registro en BD remota parece ERROR", 2);
		    }
		  else
		    {
		      log_message("(CARGA) registro en BD remota parece OK", 2);	
		    }
		  delete sqlite;
		  delete mysql;
		}   
	    }
	  else //local fail, is cathastrophic!
	    {
	      log_message("(CARGA) registro en BD local parece ERROR, es catastrófico!", 2);
	      ret = -2;
	    }
	}
      else //Remote fail, is bad
	{
	  log_message("(CARGA)(guardando movimiento) BD remota ERROR(query)", 2);
	  ret = -1;
	}
    }
  else
    {
      log_message("(CARGA)(guardando movimiento)  BD remota ERROR(connection)", 2);
      ret = -1;
    }
  
  if(ret < 0) //no remote saving
    {
      str_log_message = "(CARGA) db local -> ";
      str_log_message += sqliteQuery;
      log_message(str_log_message, 1); 
      if(!localDatabase.query(NULL,sqliteQuery.c_str())) //REMOVED FROM LOCAL SERVER
	{
	  //DELETING TRANSIT
	  sqliteQuery.clear();
	  sqliteQuery = "delete from TRANSITO_SALIDAS where (FECHA_HORA =\"";
	  sqliteQuery += retDepDateTime();
	  sqliteQuery += "\")";
	  str_log_message = "(CARGA) db local -> ";
	  str_log_message += sqliteQuery;
	  log_message(str_log_message, 1); 	  
	  localDatabase.query(NULL,sqliteQuery.c_str());
	      
	}
      else
	{
	  log_message("(CARGA) registro en BD local parece ERROR, es catastrófico!", 2);
	  ret = -2;
	}
    }

  
  return ret;
}
int outputForm::storeDepTransfer(qtDatabase & my_local_database, qtDatabase & my_remote_database, int remote_host_connected)
{
  int ret = -1;
  std::string str_log_message;
  //only save transfer if connection
  ///

  std::string mysql_query = "insert into transferencias (DI,FECHA_HORA,CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO,CODIGO_TRANSPORTISTA,MATRICULA, REMOLQUE,INCIDENCIAS,COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO) values (\"";
   std::string sqlite_query = "insert into transferencias (DI,FECHA_HORA,CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO,CODIGO_TRANSPORTISTA,MATRICULA, REMOLQUE,INCIDENCIAS,COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO,SINCRONIZADO) values (\""; 
  
  std::string values =  retDepDi();
  values += "\",\"";  
  values += getCurrentDate();
  values += "\",";
  values += std::to_string(depOriginStation->getCode());
  values += ",";
  values += std::to_string(depDestinationStation->getCode());
  values += ",";
  values += std::to_string(retDepProdCode());
  values += ",";
  values += std::to_string(retDepDriCode());
  values += ",\"";
  values += retDepPlate();
  values += "\",\"";
  values += retDepPlateAtt();
  values += "\",\"";
  values += vectorToString(getOutputIncidents(),"; ");
  values += "\",\"";
  values += getOutputComment();
  values += "\",\"";
  values += retDepTreat();
  values += "\"";
 

  mysql_query += values;
  mysql_query +=")";

  sqlite_query +=values;

  //remote saving
  if(remote_host_connected)
    {
      str_log_message = "(CARGA) db remota -> ";
      str_log_message += mysql_query;
      log_message(str_log_message, 1); 
      if(!my_remote_database.query(NULL,mysql_query.c_str()))
	{
	  log_message("(CARGA) registro en BD remota parece OK", 1);
	  ret=0;
	  sqlite_query +=",1)";
	}
      else
	{
	  log_message("(CARGA) registro en BD remota parece ERROR", 2);
	  sqlite_query +=",0)";
	}
    }
  else
    {
      log_message("(CARGA) registro en BD remota parece ERROR", 2);
      sqlite_query +=",0)";
    }

  //local saving
  str_log_message = "(CARGA) db local -> ";
  str_log_message += sqlite_query;
  log_message(str_log_message, 1); 
  if(!my_local_database.query(NULL,sqlite_query.c_str()))
    {
      log_message("(CARGA) registro en BD local parece OK", 1);
      //we have no move code, create one with DI for saving files to server
      std::string moveCode = retDepDi();
      if(!retDepDateTime().empty())
	{
	  moveCode += " ";
	  moveCode += retDepDateTime();
	}
      setDepMovCode(moveCode);
    }
  else
    {
      log_message("(CARGA) registro en BD local parece ERROR, catastrófico", 2);
      ret = -2;
    }
  return ret;
}
void outputForm::setOrders(qtDatabase & myDatabase, long station_code)
{
  char * sql;
  int numCol=0;
  struMovement myOrder;

  allOrders.clear();
  selectAllFromOrders(sql,station_code);
  myDatabase.query(NULL,sql);

  std::vector<std::vector<std::string>> ourData = myDatabase.retData2();
  std::vector <std::vector<std::string>>::iterator row;
  std::vector<std::string>::iterator col;
  for(row=ourData.begin();  row != ourData.end(); ++row)
    {
      myOrder = struMovement {};
      numCol = 0;
      for(col=row->begin(); col != row->end(); ++col)
	{
	  if(numCol == 0) // CODIGO_ORDEN
	    {
	      try
		{
		  myOrder.CODIGO_ORDEN = std::stoi(*col);
		}
	      catch(...)
		{
		  myOrder.CODIGO_ORDEN = -1;
		}
	    }
	  else if(numCol == 2) // CODIGO_CLIENTE
	    {
	      try
		{
		  myOrder.CODIGO_CLIENTE = std::stoul(*col);
		}
	      catch(...)
		{
		  myOrder.CODIGO_CLIENTE = 0;
		}
	    }
	  else if(numCol == 3) // CODIGO_PRODUCTO
	    {
	      try
		{
		  myOrder.CODIGO_PRODUCTO = std::stoul(*col);
		}
	      catch(...)
		{
		  myOrder.CODIGO_PRODUCTO = 0;
		}
	    }
	  else if(numCol == 4) // FECHA_FIRMA
	    myOrder.FECHA_FIRMA = *col;
	  else if(numCol == 5) // FECHA_PROGRAMADA
	    myOrder.FECHA_PROGRAMADA = *col;
	  else if(numCol == 7) // PESO_A_RETIRAR
	    {
	      try
		{
		  myOrder.PESO_A_RETIRAR = std::stoul(*col);
		}
	      catch(...)
		{
		  myOrder.PESO_A_RETIRAR = 0;
		}
	    }
	  else if(numCol == 8) // CODIGO_DESTINO ORIGIN FROM MOVEMENT
	    {
	      try
		{
		  myOrder.CODIGO_ORIGEN = std::stoul(*col);
		}
	      catch(...)
		{
		  myOrder.CODIGO_ORIGEN = 0;
		}
	    }
	  else if(numCol == 10) // REPETIR
	    {
	      try
		{
		  myOrder.REPETIR = std::stoi(*col);
		}
	      catch(...)
		{
		  myOrder.REPETIR = 0;
		}
	    }
	  else if(numCol == 38) // CLIENTE NOMBRE
	    myOrder.CLIENTE_NOMBRE = *col;
	  else if(numCol == 39) // CODIGO LER
	    {
	      try
		{
		  myOrder.PRODUCTO_LER = std::stoul(*col);
		}
	      catch(...)
		{
		  myOrder.PRODUCTO_LER = 0;
		}
	    }

	  numCol++;	    	  
	}
      allOrders.push_back(myOrder);
    }	    

  return;
}
std::vector<std::string> outputForm::retOrdersTable()
{

  std::vector <struMovement>::iterator orden;
  std::vector <std::string> tableText;
  std::string item;
  std::vector<struMovement> myOrders = retOrders();
 
  //DATE,CLIENT NAME, PRODUCT LER
  std::string date;
  std::string clientName;
  std::string productLer;
  for(orden = myOrders.begin(); orden != myOrders.end(); ++orden)
    {

      date = orden->FECHA_PROGRAMADA;
      clientName = orden->CLIENTE_NOMBRE;
      productLer = std::to_string(orden->PRODUCTO_LER);
     
      item = date;
      item += ", LER:";
      item += productLer;    
      item += "\n";
      item += clientName;
      tableText.push_back(item);
    }
  return tableText;
}

struMovement outputForm::selOrder(unsigned int index)
{
  struMovement myOrder;
  
  if(index < allOrders.size())
    myOrder = allOrders.at(index);

  return myOrder;
}

//!creating a transfer movement
void outputForm::setTransferMov(long myCode, station *& myStation)
{
  //MOV TYPE
  setDepMovType(DEF_MOV_TRANSFER);
  
  setDepCosCode(myCode);
  setDepProdCode(0);

  setDepOrigStation(myStation);
  setDepDateTime(getCurrentDate());
}

/*! void outputForm::isArrMov()
return true if we have a movement
by criteria: we have both product and costumer codes
*/
int outputForm::isArrMov()
{
  int ret = 0;
  if(retArrCosCode() >=0 && retArrProdCode() >=0)
    ret = 1;
  
  return ret;
}

//SCALING
int outputForm::isArrPesoOk()
{
  int ret = 0;
  if(retArrScaleIn() > 2)
    {
      ret = 1;
    }
  return ret;
}

int outputForm::isDepPesoOk()
{
  //std::cout << "debug: inside outputForm::isDepPesoOk:" << std::endl;
  int ret = 0;

  long maxExpected = (retDepScaleIn() + retDepWeightToTakeAway()) * ((100.0+retErrorScale())/100.0);
  long minExpected = (retDepScaleIn() + retDepWeightToTakeAway()) * ((100.0-retErrorScale())/100.0);
  
  if(retDepScaleOut() <= maxExpected && retDepScaleOut() >= minExpected)    
    ret = 1;
  else if(retDepScaleOut() < minExpected)
    ret = -1;

  return ret;
}
int outputForm::retDepScaleExpected()
{
  int weight = retDepWeightToTakeAway() + retDepScaleIn();
    return weight;
}
/*! function to save and calculate total scale*/
void outputForm::setAndCalcScaleOut(unsigned int scale)
{
  unsigned int scaleIn;
  
  setDepScaleOut(scale);
  scaleIn = retDepScaleIn();
  setDepTotalWeight(scale-scaleIn);    
}
/*! function to save scale out in database*/
int outputForm::saveScaleOut(qtDatabase & myDatabase, qtDatabase &myRemoteDatabase, const char * remoteHost, int remotePort )
{
  char *sql = NULL;
  std::string another_sql;
  //rodri: int port;
  int ret = 1;

  setAndCalcScaleOut(retDepScaleOut());
  
  updtScaleOutTransSal(sql, retDepDateTime().c_str(), retDepCosCode(), retDepProdCode(), retDepTotalWeight(),getOutputComment().c_str(),vectorToString(getOutputIncidents(),";").c_str());
  
  if(!myDatabase.query(NULL,sql))
    {
      ret = 0;     
      if(isConnected(remoteHost, remotePort))
	{
	  remote_updatePesoSalidaTransitoSalida(another_sql, retDepCosCode(), retDepDateTime().c_str(),ourStation->getCode(),retDepTotalWeight(),getOutputComment().c_str(),vectorToString(getOutputIncidents(),";").c_str());
	  myRemoteDatabase.query(NULL,another_sql.c_str());
	}

    }
  delete sql;

  return ret;
}
//
int outputForm::setMovCode(std::string sLastCode, int stationCode, int movementTypeCode)
{
  long lastCode = std::stol(sLastCode);
  std::string newCode;
  std::string str_station_code;
  //costumer need, bad idea:
  //station codes of fixed size 2.
  // TODO REVCODES
  //if(stationCode <10)
  //  str_station_code = "0";
  str_station_code += std::to_string(stationCode);
  
  if (lastCode > 0 && sLastCode.size() > 11)
    {
      std::string prefix = sLastCode.substr(0,sLastCode.size()-7);
      std::string sIndex = sLastCode.substr(sLastCode.size()-7,6);

      std::string prefix_year = prefix.substr(0,4); 
      long index = std::stol(sIndex);
      index++;
      if(index > 999999)
	index = 999999;
      std::string newIndex = zeroPadNumber(index,6);
      
      newCode = prefix_year + str_station_code + newIndex + std::to_string(movementTypeCode);
    }
  else
    {
      time_t myTime = time(NULL);
      struct tm *aTime = localtime(&myTime);
      int year = aTime->tm_year + 1900;
      
      newCode = std::to_string(year) + str_station_code + "000001" + std::to_string(movementTypeCode);

    }
  myDepMovement.CODIGO_MOVIMIENTO = newCode;
  return 0;
}

//transit movements managment
/*! FUNCTION IS WRONG! FIX IT*/
int outputForm::storeTransit(qtDatabase & myDatabase,qtDatabase & remoteDatabase, station * myStation, int remote_host_connected)
{
  int ret = 0;
  std::string str_log_message;
  
  std::string mysql_sql = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR) values (\"";

  std::string sqlite_sql = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR, SINCRONIZADO) values (\"";
  
  std::string common_sql = retArrDi();
  common_sql += "\",\"";	    
  common_sql += retArrDateTime();
  common_sql += "\",";
  common_sql += std::to_string(retArrCosCode());
  common_sql += ",";
  common_sql += std::to_string(retArrProdCode());
  common_sql += ",";
  common_sql += std::to_string(retArrScaleIn());
  common_sql += ",\"";
  common_sql += retArrPlate();
  common_sql += "\",\"";
  common_sql += retArrPlateAtt();
  common_sql += "\",";
  common_sql += std::to_string(retArrWeightToTakeAway());
  common_sql += ",";
  common_sql += "0"; //PESO_RETIRADO
  common_sql += ",";
  if(arrDestinationStation != NULL)
    common_sql += std::to_string(arrDestinationStation->getCode());
  else
    common_sql += "0";
  common_sql += ",";
  common_sql += std::to_string(myArrMovement.CODIGO_ORDEN);// order code
  common_sql += ",\"";	
  common_sql += vectorToString(getInputIncidents(),"; ");
  common_sql += "\",\"";
  common_sql += getInputComment();
  common_sql += "\"";

  mysql_sql += common_sql;
  mysql_sql += ")";

  sqlite_sql += common_sql;

  //trying remote database first!
  if(remote_host_connected)
    {
      str_log_message = "(LOADING)(to transit) remote db -> ";
      str_log_message += mysql_sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(NULL,mysql_sql.c_str()))
	{
	  log_message("(LOADING)(to transit) remote BD query seems to be OK", 2);
	  sqlite_sql += ",1)";
	}
      else
	{
	  log_message("(LOADING)(to transit) remote BD query seems to be ERROR", 2);
	  ret = -1;//database error
	  sqlite_sql += ",0)";
	}
      str_log_message = "(LOADING)(to transit) local db -> ";
      str_log_message += sqlite_sql;
      log_message(str_log_message, 1);
      myDatabase.query(NULL,sqlite_sql.c_str());

    }
  else
    {
      log_message("(LOADING)(to transit) remote BD query seems to be ERROR", 2);
      ret = -1;
      sqlite_sql += ",0)";
      str_log_message = "(LOADING)(to transit) local db -> ";
      str_log_message += sqlite_sql;
      log_message(str_log_message, 1);
      if(!myDatabase.query(NULL,sqlite_sql.c_str()))
	log_message("(LOADING)(to transit) local BD query seems to be OK", 1);
      else
	log_message("(LOADING)(to transit) local BD query seems to be ERROR (DONE NOTHING!)", 2);
    }
 
  return ret;
}

int outputForm::isPlateInTransit(std::string plate)
{
  int ret = 0;
  std::vector<std::vector<std::string>>::iterator row;
  int index = 0;
  row = vctAllTransit.begin();
  if(!plate.empty() && plate.compare(""))
    {
      while(row != vctAllTransit.end())
	{
	  if(row->size() > 5) //DATABASE DEPENDANT
	    {
	      if(!plate.compare(row->at(5))) //DATABASE DEPENDANT
		{
		  ret = index +1;
		  break;
		}
	    }
	  index++;
	  ++row;
	}
    }

  return ret;
}

int outputForm::delTransit(int index,std::string plate, qtDatabase & myDatabase, qtDatabase & myRemoteDatabase, std::string host, int port, long station_code)
{
  int ret = 1;
  std::string fecha_hora,di,str_log_message;

  if(index >= 0)
    {
      if(vctAllTransit.size() > index)
	    {
	      if(vctAllTransit.at(index).size() >= 6) //transit salidas database dependant
	      {
	        di = vctAllTransit.at(index).at(0); //DI
	        plate = vctAllTransit.at(index).at(5); //PLATE
	        fecha_hora = vctAllTransit.at(index).at(1); //DATE
	      }
	    }
    }

  std::string sql = "delete from transito_salidas where matricula = \"";
  sql += plate;
  sql += "\" and FECHA_HORA=\"";
  sql += fecha_hora;
  sql += "\"";
  std::string mysql = sql + " and codigo_estacion=";
  mysql += std::to_string(station_code);
  
  str_log_message = "(CARGA)(borrando tránsito) db local -> ";
  str_log_message += sql;
  log_message(str_log_message, 1);
  
  if(!myDatabase.query(NULL,sql.c_str()))
    {
      log_message("(CARGA)(borrando tránsito) db local OK", 1);
      ret = 0;
    }
  else
    {
      log_message("(CARGA)(borrando tránsito) db local ERROR", 2);
      ret = 1;
    }
  
  str_log_message = "(CARGA)(borrando tránsito) db remota -> ";
  str_log_message += mysql;
  log_message(str_log_message, 1);
  
  if(isConnected(host.c_str(), port))
    {
      if(!myRemoteDatabase.query(NULL,mysql.c_str()))
	log_message("(CARGA)(borrando tránsito) db remota OK", 1);
      else
	log_message("(CARGA)(borrando tránsito) db remota ERROR (query error)", 2);
    }
  else
    log_message("(CARGA)(borrando tránsito) db remota ERROR (connection error)", 2);
  
  if(!ret) //remove folder
    {
      std::string command  = "rm -r \"saves/";
      command += di;
      command += " ";
      command += fecha_hora;
      command += "\"";
      system(command.c_str());
    }
  return ret;
}
int outputForm::setTransitMov(int index, std::string byPlate, qtDatabase & myDatabase)
{
  int ret = -1, num_of_row = 0;
  std::vector<std::vector<std::string>>::iterator row;
  row = vctAllTransit.begin();
  int type = 0;

  while(row != vctAllTransit.end())
  {
    if(row->size() >= 13) //DATABASE DEPENDANT
	  {
	    if(!byPlate.compare(row->at(5)) && (num_of_row >= index || index == -1)) //DATABASE DEPENDANT
	    {
	      type = retDepMovType();
	      clearDepMov();
	      setDepDi(row->at(0)); //DI
	      setDepDateTime(row->at(1)); //FECHA_HORA
	      try
		    {
		      setDepCosCode(std::stol(row->at(2))); //CODIGO_CLIENTE
		    }
	      catch(...)
		    {
		      setDepCosCode(0);
		    }
	      try
		    {
		      setDepProdCode(std::stol(row->at(3))); //CODIGO PRODUCTO
		    }
	      catch(...)
		    {
		      setDepProdCode(0);
		    }
	      try
		    {
		      setDepScaleIn(std::stoul(row->at(4))); //PESO_ENTRADA
		    }
	      catch(...)
		    {
		      setDepScaleIn(0); //PESO_ENTRADA
		    }
	      setDepPlate(row->at(5)); //MATRICULA
	      setDepPlateAtt(row->at(6)); //REMOLQUE
	      try
		    {
		      setDepWeightToTakeAway(std::stoul(row->at(7))); //PESO_PARA_LLEVAR
		    }
	      catch(...)
		    {
		      setDepWeightToTakeAway(0);
		    }
	      try
		    {
		      setDepTotalWeight(std::stoul(row->at(8))); //PESO_CARGA
		    }
	      catch(...)
		    {
		      setDepTotalWeight(0); //PESO_CARGA
		    }
        /* this is not destination, this is our station
	      try//destination
		    {
		      if(depDestinationStation)
		        delete depDestinationStation;
		      depDestinationStation = new station(std::stol(row->at(9)),myDatabase);
		    }
	      catch(...)
		    {
		      if(depDestinationStation)
		        delete depDestinationStation;
		      depDestinationStation = new station();
		    }*/
	      try
		    {
		      myDepMovement.CODIGO_ORDEN = std::stol(row->at(10)); //ORDER CODE
		    }
	      catch(...)
		    {
		      myDepMovement.CODIGO_ORDEN = 0;
		    }
	      //incidents
	      std::vector<std::string> newIncidents = getOutputIncidents();
	      setOutputIncidents( stringToVector(row->at(11),";"));
	      outputConcatenate(newIncidents);	     
	      //
	      setOutputComment(row->at(12));  //COMENTARIO OPERADOR
	      setDepMovType(type);
	      /*TODO best with it's scaling own class
		    peso salida:*/
	      setDepScaleOut(retDepScaleIn()+retDepTotalWeight());
	      /**/
	      ret = 0;
	      break;
	    }
	  }
    ++row;
    num_of_row++;
  }
  return ret;
}
void outputForm::forceCurrentProduct()
{
  std::vector<std::string>::iterator iter;
  int alreadyDone = 0;

  for(iter=iIncidents.begin();iter!=iIncidents.end() && !alreadyDone;++iter)
    {
      std::string code = iter->substr(0,5);
      if(!code.compare("00133"))
	alreadyDone=1;       
    }
  if(!alreadyDone)
    iIncidents.push_back("00133: Se ha forzado el permiso de SALIDA del producto, ya que el cliente no lo tenía permitido");
      
  return;
}
void outputForm::unforceCurrentProduct()
{
  std::vector<std::string>::iterator iter;
  
  for(iter=iIncidents.begin();iter!=iIncidents.end();)
    {
      std::string code = iter->substr(0,5);
      if(!code.compare("00133"))
	iter= iIncidents.erase(iter);
      else
	++iter;
    }
  return;
}
int outputForm::getFzCurrentProduct()
{
  std::vector<std::string>::iterator iter;
  int isForced = 0;
  
  for(iter=iIncidents.begin();(iter!=iIncidents.end() && !isForced);)
    {
      std::string code = iter->substr(0,5);
      if(!code.compare("00133"))
	isForced=1;
      else
	++iter;
    }
  
  return isForced;
}
// TODO: error handling not implemented
void outputForm::setAllDiData(qtDatabase & localDatabase, station *myStation, long ourCode, long defDriverCode)
{
  //common data
  //product information
  if(retDepProdCode()>0)
  {
    if(setAllProductData(localDatabase)) // TODO: error handling
	    std::cout << "*ERROR*" << std::endl;
  }
  //costumer information
  if(retDepCosCode()>0)
  {
    if(setAllDepCostumerData(localDatabase))
	    std::cout << "*ERROR*" << std::endl;
  }
  //costumer-product information
  if(retDepProdCode()>0 && retDepCosCode()>0)
  {
    if(setAllDepCosProdData(localDatabase,myStation))
	    std::cout << "*ERROR*" << std::endl;
  }
  //billing method and price
  if(set_all_billing_info(localDatabase))
    std::cout << "*ERROR*" << std::endl; 
  // output movement
  if(retDepMovType() == DEF_MOV_SALIDA)
  {
    // origin station, us!
    if(myStation)
      setDepOrigStation(myStation);
    if(ourId)
    {
      depOriginStation->setName(ourId->getName());
      depOriginStation->setNif(ourId->getNif());
      depOriginStation->setAddress(ourId->getAddress());
      depOriginStation->setProvence(ourId->getProvence());
      depOriginStation->setCity(ourId->getCity());
      depOriginStation->setRegion(ourId->getRegion());
      depOriginStation->setZip(ourId->getCp());
      depOriginStation->setNima(ourId->getNima());
      depOriginStation->setNumIns(ourId->getNumIns());
      depOriginStation->setPhone(ourId->getPhone());
      depOriginStation->setMail(ourId->getMail());
    }
    getAllOrderInfo(localDatabase, myDepMovement.CODIGO_ORDEN);
  }
  else
  {
    // origin station, us!
    if(myStation)
      setDepOrigStation(myStation);
    // destination station
    if (depDestinationStation)
    {
      int value;
      depDestinationStation->getType(value);
      if(value == DEF_STATION_DEPOSIT) //movement to deposit
	    {
	      setDepMovType(DEF_MOV_INTERNOD5);
	      setDepCosCode(defDriverCode);
	      setAllDepCostumerData(localDatabase);
	      setDepCosType(3);
	    }
      if(value == DEF_STATION_TRANSFER || value == DEF_STATION_MASTER) //movement of transference
	    {
	      setDepMovType(DEF_MOV_TRANSFER);
	      setDepCosCode(ourCode);
	      setAllDepCostumerData(localDatabase);
	      setDepCosType(2);
	    }
    }
    // default driver loaded
    if (defDriverCode > 0) // if default driver configured
	  {
	    if (retDepDriCode() <= 0)
	    {
	      setDriverByCode(defDriverCode, localDatabase);
	    }
	  }
  }
}
/*! function for managing all new information preset by the order*/
int outputForm::getAllOrderInfo(qtDatabase & localDatabase, long order_code)
{
  char * sql;
  int numCol=0;
  long costumer_code = 0;
  long station_code = 0;

  selOrderById(sql,order_code);
  localDatabase.query(NULL,sql);

  std::vector<std::vector<std::string>> ourData = localDatabase.retData2();
  std::vector<std::string>::iterator col;
  // CODIGO_ORDEN, ECOEMBES, CODIGO_CLIENTE, CODIGO_PRODUCTO, FECHA_FIRMA, FECHA_PROGRAMADA, PRECIO_TN, PESO_RETIRAR , CODIGO_DESTINO , OPERACION_TRATAMIENTO , REPETIR, TIPO_OPERADOR, CODIGO_INFO_ORIGEN_CENTRO, CODIGO_INFO_ORIGEN_AUTORIZADO, CODIGO_INFO_DESTINO_CENTRO, CODIGO_INFO_DESTINO_AUTORIZADO, INFO_DESTINO_CENTRO_NOMBRE, INFO_DESTINO_CENTRO_NIF, INFO_DESTINO_CENTRO_DIRECCION, INFO_DESTINO_CENTRO_CP, INFO_DESTINO_CENTRO_MUNICIPIO, INFO_DESTINO_CENTRO_PROVINCIA, INFO_DESTINO_CENTRO_COMUNIDAD_AUTONOMA, INFO_DESTINO_CENTRO_NIMA, INFO_DESTINO_CENTRO_N_INSC_REGISTRO, INFO_DESTINO_CENTRO_TELEFONO, INFO_DESTINO_CENTRO_EMAIL, INFO_DESTINO_AUTORIZADO_NOMBRE, INFO_DESTINO_AUTORIZADO_NIF, INFO_DESTINO_AUTORIZADO_DIRECCION, INFO_DESTINO_AUTORIZADO_CP, INFO_DESTINO_AUTORIZADO_MUNICIPIO, INFO_DESTINO_AUTORIZADO_PROVINCIA, INFO_DESTINO_AUTORIZADO_COMUNIDAD_AUTONOMA, INFO_DESTINO_AUTORIZADO_NIMA, INFO_DESTINO_AUTORIZADO_N_INSC_REGISTRO, INFO_DESTINO_AUTORIZADO_TELEFONO, INFO_DESTINO_AUTORIZADO_EMAIL
  for(col=ourData.at(0).begin(); col != ourData.at(0).end(); ++col)
	{
    // info_Destino_centro
    // info_destino_autorizado
	  if(numCol == 6) // PRICE
	  {
	    try
		  {
		    setDepPrice(std::stof(*col));
		  }
	    catch(...)
		  {
		    // do nothing
		  }
	  }
	  else if(numCol == 11) // OPERATOR TYPE
	  {
	    try
      {
        setDepCosType(std::stoi(*col));
		  }
	    catch(...)
		  {
		    setDepCosType(1);
		  }
	  }
    else if(numCol == 12)  //CODIGO_INFO_ORIGEN_CENTRO
    {}
    else if(numCol == 13)  //CODIGO_INFO_ORIGEN_AUTORIZADO
    {}
    else if(numCol == 14)  //CODIGO_INFO_DESTINO_CENTRO
    {
      try
		  {
        station_code = std::stoul(*col);
        if(station_code > 0)
        {
          if (depDestinationStation)
            delete depDestinationStation;
          depDestinationStation = new station(station_code, localDatabase);
        }
		  }
	    catch(...)
		  {
		    // do nothing
        station_code = 0;
		  }
    }
    else if(numCol == 15) // CODIGO_INFO_DESTINO_AUTORIZADO
	  {
      try
		  {
        costumer_code = std::stoul(*col);
        if(costumer_code > 0)
        {
          if(depAuthCostumer)
            delete depAuthCostumer;
          depAuthCostumer = new costumer(costumer_code, localDatabase);
        }
		  }
	    catch(...)
		  {
		    // do nothing
        costumer_code = 0;
		  }
	  }
    else if(numCol == 16) // INFO_DESTINO_CENTRO_NOMBRE
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      depDestinationStation->setName(*col);
	  }
    else if(numCol == 17) // INFO_DESTINO_CENTRO_NIF
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      depDestinationStation->setNif(*col);
	  }
    else if(numCol == 18) // INFO_DESTINO_CENTRO_DIRECCION
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      depDestinationStation->setAddress(*col);
	  }
    else if(numCol == 19) // INFO_DESTINO_CENTRO_CP
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      try
		  {
        depDestinationStation->setZip(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 20) // INFO_DESTINO_CENTRO_MUNICIPIO
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      depDestinationStation->setCity(*col);
	  }
    else if(numCol == 21) // INFO_DESTINO_CENTRO_PROVINCIA
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      depDestinationStation->setProvence(*col);
	  }
    else if(numCol == 22) // INFO_DESTINO_CENTRO_COMUNIDAD_AUTONOMA
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      depDestinationStation->setRegion(*col);
	  }
    else if(numCol == 23) // INFO_DESTINO_CENTRO_NIMA
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      try
		  {
        depDestinationStation->setNima(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 24) // INFO_DESTINO_CENTRO_N_INSC_REGISTRO
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      try
		  {
        depDestinationStation->setNumIns(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 25) // INFO_DESTINO_CENTRO_TELEFONO
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      try
		  {
        depDestinationStation->setPhone(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 26) // INFO_DESTINO_CENTRO_EMAIL
	  {
      if(!depDestinationStation)
        depDestinationStation = new station();
      depDestinationStation->setMail(*col);
	  }
    else if(numCol == 27) // INFO_DESTINO_AUTORIZADO_NOMBRE
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      depAuthCostumer->setName(*col);
	  }
    else if(numCol == 28) // INFO_DESTINO_AUTORIZADO_NIF
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      depAuthCostumer->setNif(*col);
	  }
    else if(numCol == 29) // INFO_DESTINO_AUTORIZADO_DIRECCION
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      depAuthCostumer->setAddress(*col);
	  }
    else if(numCol == 30) // INFO_DESTINO_AUTORIZADO_CP
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      try
		  {
        depAuthCostumer->setCp(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 31) // INFO_DESTINO_AUTORIZADO_MUNICIPIO
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      depAuthCostumer->setCity(*col);
	  }
    else if(numCol == 32) // INFO_DESTINO_AUTORIZADO_PROVINCIA
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      depAuthCostumer->setProvence(*col);
	  }
    else if(numCol == 33) // INFO_DESTINO_AUTORIZADO_COMUNIDAD_AUTONOMA
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      depAuthCostumer->setRegion(*col);
	  }
    else if(numCol == 34) // INFO_DESTINO_AUTORIZADO_NIMA
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      try
		  {
        depAuthCostumer->setNima(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 35) // INFO_DESTINO_AUTORIZADO_N_INSC_REGISTRO
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      try
		  {
        depAuthCostumer->setNumIns(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 36) // INFO_DESTINO_AUTORIZADO_TELEFONO
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      try
		  {
        depAuthCostumer->setPhone(std::stoul(*col));
      }
      catch(...)
      {
        // do nothing
      }
	  }
    else if(numCol == 37) // INFO_DESTINO_AUTORIZADO_EMAIL
	  {
      if(!depAuthCostumer)
        depAuthCostumer = new costumer();
      depAuthCostumer->setMail(*col);
	  }
	  numCol++;
	}

  return 0;
}


/*TODO
is DI complete?
*/
int outputForm::isDiComplete()
{
  int ret = 1;
  //COMMON ANALYSIS
  //CODIGO_PRODUCTO
  if(retDepProdCode() <= 0)
    ret = 0;
  //CODIGO_TRANSPORTISTA
  if(retDepDriCode() <= 0)
    ret = 0;
  //CODIGO_CLIENTE
  if(retDepCosCode() <= 0)
     ret = 0;
  //DESTINATION
  if(depDestinationStation->getCode() <= 0 && !depDestinationStation->isManuallyEdited())
    ret = 0;

  return ret;
}


//////////////////////////////////////////////////////////////////
//PDF generation
//////////////////////////////////////////////////////////////////
/*! function for creating our document with all the stored info 
  about our movement*/



void outputForm::createPdf(std::string printerId)
{
  std::cout << "entrando en el método novedosísimo y patentadísimo de CREATE PDF!! es brooma ;-)" << std::endl;
  
  std::string titulo = "Ticket cliente: ";
  //rodri: const char *page_title = titulo.c_str();

  HPDF_Doc  pdf;
  HPDF_Font font;
  HPDF_Page page1,page2;
  HPDF_Image templatePage1,templatePage2;
  char fname[512];
  char signature[512];

  //rodri: float tw;
  float fsize = 14;
  //rodri: int i;
  //rodri: int len;


  std::string myText = retDepDiFolder();
  strcpy (fname, myText.c_str());
  strcat (fname, "/ticket.pdf");
  myText.clear();

  pdf = HPDF_New (error_handler, NULL);
  if (!pdf) {
    printf ("error: cannot create PdfDoc object\n");
    return;
  }

  if (setjmp(env)) {
    HPDF_Free (pdf);
    return;
  }

  //set compression mode 
  HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);
  HPDF_UseUTFEncodings(pdf); 
  // create default-font 
  font = HPDF_GetFont (pdf, HPDF_LoadTTFontFromFile (pdf, "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf", HPDF_TRUE),"UTF-8");

  // add pages objects 
  page1 = HPDF_AddPage (pdf);
  HPDF_Page_SetWidth (page1, 827);
  HPDF_Page_SetHeight (page1, 1169);
  page2 = HPDF_AddPage (pdf);
  HPDF_Page_SetWidth (page2, 827);
  HPDF_Page_SetHeight (page2, 1169);

  templatePage1 = HPDF_LoadPngImageFromFile (pdf, "image/hoja1.png");
  templatePage2 = HPDF_LoadPngImageFromFile (pdf, "image/hoja2.png");  
  
  HPDF_Page_DrawImage (page1, templatePage1,0,0,827,1169);
  HPDF_Page_DrawImage (page2, templatePage2,0,0,827,1169);

  HPDF_Page_SetFontAndSize (page1, font, fsize);  
  HPDF_Page_SetFontAndSize (page2, font, fsize); 

  //LER
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 480, 1034);
  myText = std::to_string(retDepProdLER());
  HPDF_Page_ShowText (page1, myText.c_str());
  HPDF_Page_EndText (page1);
  
  //PELIGRO
  HPDF_Page_BeginText (page1);
  myText = retDepProdPeligro();

  if(myText.empty() || !myText.compare(""))   
    HPDF_Page_MoveTextPos (page1, 672, 1034);    
  else
    HPDF_Page_MoveTextPos (page1, 562, 1034);
  HPDF_Page_ShowText (page1, "X");
  HPDF_Page_EndText (page1);

  //DI
  HPDF_Page_BeginText (page1);
  myText = retDepDi();
  HPDF_Page_MoveTextPos (page1, 558, 1015);
  HPDF_Page_ShowText (page1, myText.c_str());
  HPDF_Page_EndText (page1);

  //NPT
  HPDF_Page_BeginText (page1);
  myText = std::to_string(retDepPermitNPT());
  HPDF_Page_MoveTextPos (page1, 558, 995);
  HPDF_Page_ShowText (page1, myText.c_str());
  HPDF_Page_EndText (page1);

  //DATE TIME
  HPDF_Page_BeginText (page1);
  myText = retDepDateTime();
  HPDF_Page_MoveTextPos (page1, 558, 975);
  HPDF_Page_ShowText (page1, removeTime(myText).c_str());
  HPDF_Page_EndText (page1);

  		//4. COSTUMER DATA

 //Posiciones de la X
 HPDF_Page_BeginText (page1);
 myText = "X";

	if(retDepCosType()==1)
	    {
		  HPDF_Page_MoveTextPos (page1, 183, 925);
	    }
	else if(retDepCosType()==2)
	    {
		  HPDF_Page_MoveTextPos (page1, 290, 913);
	    }
	else if(retDepCosType()==3)
	    {
		  HPDF_Page_MoveTextPos (page1, 509, 925);
	    }	  
	else if(retDepCosType()==4)
	    {
		  HPDF_Page_MoveTextPos (page1, 183, 880);	
	    }	  
	else if(retDepCosType()==5)
	    {
		  HPDF_Page_MoveTextPos (page1, 290, 880);
	    }
	else if(retDepCosType()==6)
	    {
		  HPDF_Page_MoveTextPos (page1, 509, 880);
	    }
		 
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);


if(retDepCosName().compare("OTROS"))
  {
    //NAME
    myText = retDepCosName();
    set_di_text(page1,fsize,47,font,myText,188,841);

    //NIF
    HPDF_Page_BeginText (page1);
    myText = retDepCosNif();
    HPDF_Page_MoveTextPos (page1, 648, 841);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //CP
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepCosZip());
    HPDF_Page_MoveTextPos (page1, 648, 816);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //COMUNIDAD AUTONOMA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    myText = retDepCosReg();
    HPDF_Page_MoveTextPos (page1, 648, 792);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //DIRECCION
    myText = retDepCosAddr();
    set_di_text(page1,fsize,47,font,myText,188,816);

    //MUNICIPIO
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    myText = retDepCosCity();
    HPDF_Page_MoveTextPos (page1, 188, 792);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //NIMA
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepCosNima());
    HPDF_Page_MoveTextPos (page1, 188, 764);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //TELEFONO
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepCosPhone());
    HPDF_Page_MoveTextPos (page1, 188, 737);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //PROVINCIA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    myText = retDepCosProv();
    HPDF_Page_MoveTextPos (page1, 465, 792);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //Nº INSC REGISTRO
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepCosNumIns());
    HPDF_Page_MoveTextPos (page1, 465, 764);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //EMAIL
    HPDF_Page_BeginText (page1);
    myText = retDepCosMail();
    HPDF_Page_MoveTextPos (page1, 465, 737);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);
  }
 else //PARTICULAR COSTUMER
  {
    //NAME
    myText = retDepPCosName();
    set_di_text(page1,fsize,47,font,myText,188,841);

    //NIF
    HPDF_Page_BeginText (page1);
    myText = retDepPCosNif();
    HPDF_Page_MoveTextPos (page1, 648, 841);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //CP
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepPCosZip());
    HPDF_Page_MoveTextPos (page1, 648, 816);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //COMUNIDAD AUTONOMA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    myText = retDepPCosReg();
    HPDF_Page_MoveTextPos (page1, 648, 792);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);
    
    //DIRECCION
    myText = retDepPCosAddr();
    set_di_text(page1,fsize,47,font,myText,188,816);

    //MUNICIPIO
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    myText = retDepPCosCity();
    HPDF_Page_MoveTextPos (page1, 188, 792);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //NIMA
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepPCosNima());
    HPDF_Page_MoveTextPos (page1, 188, 764);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //TELEFONO
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepPCosPhone());
    HPDF_Page_MoveTextPos (page1, 188, 737);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //PROVINCIA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    myText = retDepPCosProv();
    HPDF_Page_MoveTextPos (page1, 465, 792);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //Nº INSC REGISTRO
    HPDF_Page_BeginText (page1);
    myText = std::to_string(retDepPCosNumIns());
    HPDF_Page_MoveTextPos (page1, 465, 764);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //EMAIL
    HPDF_Page_BeginText (page1);
    myText = retDepPCosMail();
    HPDF_Page_MoveTextPos (page1, 465, 737);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);
  }
 
// 5.ORIGIN DATA
 if(retDepMovType() == DEF_MOV_TRANSFER || retDepMovType() == DEF_MOV_SALIDA)
   {
     // A) PRODUCT CENTER (CENTRO ACTUAL)
     station * localOrigin;
     retDepOriginStation(localOrigin);
     //NAME
     myText = localOrigin->getName();
     set_di_text(page1,fsize,47,font,myText,188,638);
     
     //DIRECCION
     myText = localOrigin->getAddress();
     set_di_text(page1,fsize,47,font,myText,188,614);
     
     //MUNICIPIO
     //TODO: to adjust with new set_di_text function
     HPDF_Page_BeginText (page1);
     myText = localOrigin->getCity();
     HPDF_Page_MoveTextPos (page1, 188, 589);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //NIMA
     HPDF_Page_BeginText (page1);
     myText = std::to_string(localOrigin->getNima());
     HPDF_Page_MoveTextPos (page1, 188, 562);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //PROVINCIA
     //TODO: to adjust with new set_di_text function
     HPDF_Page_BeginText (page1);
     myText = localOrigin->getProvence();
     HPDF_Page_MoveTextPos (page1, 465, 589);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //Nº INSC REGISTRO
     HPDF_Page_BeginText (page1);
     myText = std::to_string(localOrigin->getNumIns());
     HPDF_Page_MoveTextPos (page1, 465, 562);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //NIF
     HPDF_Page_BeginText (page1);
     myText = localOrigin->getNif();
     HPDF_Page_MoveTextPos (page1, 648, 638);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);
		  
     //CP
     HPDF_Page_BeginText (page1);
     myText = std::to_string(localOrigin->getZip());
     HPDF_Page_MoveTextPos (page1, 648, 614);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //COMUNIDAD AUTONOMA
     //TODO: to adjust with new set_di_text function
     HPDF_Page_BeginText (page1);
     myText = localOrigin->getRegion();
     HPDF_Page_MoveTextPos (page1, 648, 589);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //CNAE
     HPDF_Page_BeginText (page1);
     myText = "";
     HPDF_Page_MoveTextPos (page1, 648, 562);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);
		 
     delete localOrigin;

     // B) COMPANY, in transfer and output movements is ours

     costumer * our_company;
     retOurId(our_company);

     //NAME
     myText = our_company->getName();
     set_di_text(page1,fsize,47,font,myText,188,512);

     //DIRECCION
     myText = our_company->getAddress();
     set_di_text(page1,fsize,47,font,myText,188,487);
     
     //MUNICIPIO
     //TODO: to adjust with new set_di_text function
     HPDF_Page_BeginText (page1);
     myText = our_company->getCity();
     HPDF_Page_MoveTextPos (page1, 188, 462);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //NIMA
     HPDF_Page_BeginText (page1);
     myText = std::to_string(our_company->getNima());
     HPDF_Page_MoveTextPos (page1, 188, 437);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);
		 
     //TELEFON0
     HPDF_Page_BeginText (page1);
     myText = std::to_string(our_company->getPhone());
     HPDF_Page_MoveTextPos (page1, 188, 411);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);
		 
     //PROVINCIA
     //TODO: to adjust with new set_di_text function
     HPDF_Page_BeginText (page1);
     myText = our_company->getProvence();
     HPDF_Page_MoveTextPos (page1, 465, 462);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //Nº INSC REGISTRO
     HPDF_Page_BeginText (page1);
     myText = std::to_string(our_company->getNumIns());
     HPDF_Page_MoveTextPos (page1, 465, 437);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //EMAIL
     HPDF_Page_BeginText (page1);
     myText = our_company->getMail();
     HPDF_Page_MoveTextPos (page1, 465, 411);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //NIF
     HPDF_Page_BeginText (page1);
     myText = our_company->getNif();
     HPDF_Page_MoveTextPos (page1, 648, 512);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);
		  
     //CP
     HPDF_Page_BeginText (page1);
     myText = std::to_string(our_company->getCp());
     HPDF_Page_MoveTextPos (page1, 648, 487);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     //COMUNIDAD AUTONOMA
     //TODO: to adjust with new set_di_text function
     HPDF_Page_BeginText (page1);
     myText = our_company->getRegion();
     HPDF_Page_MoveTextPos (page1, 648, 462);
     HPDF_Page_ShowText (page1, myText.c_str());
     HPDF_Page_EndText (page1);

     delete our_company;
    }
  else  
    {
      // A) EMPTY

     if(retDepCosName().compare("OTROS")) //REGISTERED COSTUMER
       {	
	 // B) COSTUMER

	 //NAME
	 myText = retDepCosName();
	 set_di_text(page1,fsize,47,font,myText,188,512);
	 
	 //DIRECCION
	 myText = retDepCosAddr();
	 set_di_text(page1,fsize,47,font,myText,188,487);
	 
	 //MUNICIPIO
	 //TODO: to adjust with new set_di_text function
	 HPDF_Page_BeginText (page1);
	 myText = retDepCosCity();
	 HPDF_Page_MoveTextPos (page1, 188, 462);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //NIMA
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepCosNima());
	 HPDF_Page_MoveTextPos (page1, 188, 437);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);
		 
	 //TELEFON0
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepCosPhone());
	 HPDF_Page_MoveTextPos (page1, 188, 411);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);
		 
	 //PROVINCIA
	 //TODO: to adjust with new set_di_text function 
	 HPDF_Page_BeginText (page1);
	 myText = retDepCosProv();
	 HPDF_Page_MoveTextPos (page1, 465, 462);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //Nº INSC REGISTRO
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepCosNumIns());
	 HPDF_Page_MoveTextPos (page1, 465, 437);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //EMAIL
	 HPDF_Page_BeginText (page1);
	 myText = retDepCosMail();
	 HPDF_Page_MoveTextPos (page1, 465, 411);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //NIF
	 HPDF_Page_BeginText (page1);
	 myText = retDepCosNif();
	 HPDF_Page_MoveTextPos (page1, 648, 512);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);
		  
	 //CP
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepCosZip());
	 HPDF_Page_MoveTextPos (page1, 648, 487);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //COMUNIDAD AUTONOMA
	 //TODO: to adjust with new set_di_text function 
	 HPDF_Page_BeginText (page1);
	 myText = retDepCosReg();
	 HPDF_Page_MoveTextPos (page1, 648, 462);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

       }
     else //PARTICULAR COSTUMER
       {

	 //NAME
	 myText = retDepPCosName();
	 set_di_text(page1,fsize,47,font,myText,188,512);
	 
	 //DIRECCION
	 myText = retDepPCosAddr();
	 set_di_text(page1,fsize,47,font,myText,188,487);
	 
	 //MUNICIPIO
	 //TODO: to adjust with new set_di_text function 
	 HPDF_Page_BeginText (page1);
	 myText = retDepPCosCity();
	 HPDF_Page_MoveTextPos (page1, 188, 462);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //NIMA
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepPCosNima());
	 HPDF_Page_MoveTextPos (page1, 188, 437);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);
		 
	 //TELEFON0
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepPCosPhone());
	 HPDF_Page_MoveTextPos (page1, 188, 411);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //PROVINCIA
	 //TODO: to adjust with new set_di_text function 
	 HPDF_Page_BeginText (page1);
	 myText = retDepPCosProv();
	 HPDF_Page_MoveTextPos (page1, 465, 462);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //Nº INSC REGISTRO
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepPCosNumIns());
	 HPDF_Page_MoveTextPos (page1, 465, 437);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //EMAIL
	 HPDF_Page_BeginText (page1);
	 myText = retDepPCosMail();
	 HPDF_Page_MoveTextPos (page1, 465, 411);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //NIF
	 HPDF_Page_BeginText (page1);
	 myText = retDepPCosNif();
	 HPDF_Page_MoveTextPos (page1, 648, 512);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);
		  
	 //CP
	 HPDF_Page_BeginText (page1);
	 myText = std::to_string(retDepPCosZip());
	 HPDF_Page_MoveTextPos (page1, 648, 487);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);

	 //COMUNIDAD AUTONOMA
	 //TODO: to adjust with new set_di_text function 
	 HPDF_Page_BeginText (page1);
	 myText = retDepPCosReg();
	 HPDF_Page_MoveTextPos (page1, 648, 462);
	 HPDF_Page_ShowText (page1, myText.c_str());
	 HPDF_Page_EndText (page1);
       }
    }
		
 //6. DESTINATION INFO
 // A) Insta. Info

 station * localDestination;
 retDepDestinationStation(localDestination);

 //NAME
 myText = localDestination->getName();
 set_di_text(page1,fsize,47,font,myText,188,315);

 //DIRECCION
 myText = localDestination->getAddress();
 set_di_text(page1,fsize,47,font,myText,188,290);
 
 //MUNICIPIO
 //TODO: to adjust with new set_di_text function 
 HPDF_Page_BeginText (page1);
 myText = localDestination->getCity();
 HPDF_Page_MoveTextPos (page1, 188, 265);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //NIMA
 HPDF_Page_BeginText (page1);
 myText = std::to_string(localDestination->getNima());
 HPDF_Page_MoveTextPos (page1, 188, 240);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);
 
 //PROVINCIA
 //TODO: to adjust with new set_di_text function 
 HPDF_Page_BeginText (page1);
 myText = localDestination->getProvence();
 HPDF_Page_MoveTextPos (page1, 465, 265);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //Nº INSC REGISTRO
 HPDF_Page_BeginText (page1);
 myText = std::to_string(localDestination->getNumIns());
 HPDF_Page_MoveTextPos (page1, 465, 240);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //NIF
 HPDF_Page_BeginText (page1);
 myText = localDestination->getNif();
 HPDF_Page_MoveTextPos (page1, 648, 315);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);
  
 //CP
 HPDF_Page_BeginText (page1);
 myText = std::to_string(localDestination->getZip());
 HPDF_Page_MoveTextPos (page1, 648, 290);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //COMUNIDAD AUTONOMA
 //TODO: to adjust with new set_di_text function 
 HPDF_Page_BeginText (page1);
 myText = localDestination->getRegion();
 HPDF_Page_MoveTextPos (page1, 648, 265);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 // DR
 HPDF_Page_BeginText (page1);
 myText = retDepDestStationDR();
 HPDF_Page_MoveTextPos (page1, 686, 240);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

delete localDestination;

  // B) Costumer
  //  -> tags
  std::string s6b_name;
  std::string s6b_address;
  std::string s6b_city;
  std::string s6b_nima;
  std::string s6b_phone;
  std::string s6b_province;
  std::string s6b_num_ins;
  std::string s6b_email;
  std::string s6b_nif;
  std::string s6b_zip;
  std::string s6b_region;
  //  -> logic
  if(retDepMovType() == DEF_MOV_SALIDA && (retDepCosType() == 4 || retDepCosType() == 1)) // special cases
  {
    // NAME
    s6b_name = depAuthCostumer->getName();
    // ADDRESS
    s6b_address = depAuthCostumer->getAddress();
    // CITY
    s6b_city = depAuthCostumer->getCity();
    // NIMA
    s6b_nima = std::to_string(depAuthCostumer->getNima());
    // PHONE
    s6b_phone = std::to_string(depAuthCostumer->getPhone());
    // PROVINCE
    s6b_province = depAuthCostumer->getProvence();
    // REGISTRATION NUMBER
    s6b_num_ins = std::to_string(depAuthCostumer->getNumIns());
    // EMAIL
    s6b_email = depAuthCostumer->getMail();
    // NIF
    s6b_nif = depAuthCostumer->getNif();
    // ZIP
    s6b_zip = std::to_string(depAuthCostumer->getCp());
    // region
    s6b_region = depAuthCostumer->getRegion();
  }
  else
  {
    if(retDepCosName().compare("OTROS")) //Cliente registrado
    {
      // NAME
      s6b_name = retDepCosName();
      // ADDRESS
      s6b_address = retDepCosAddr();
      // CITY
      s6b_city = retDepCosCity();
      // NIMA
      s6b_nima = std::to_string(retDepCosNima());
      // PHONE
      s6b_phone = std::to_string(retDepCosPhone());
      // PROVINCE
      s6b_province = retDepCosProv();
      // REGISTRATION NUMBER
      s6b_num_ins = std::to_string(retDepCosNumIns());
      // EMAIL
      s6b_email = retDepCosMail();
      // NIF
      s6b_nif = retDepCosNif();
      // ZIP
      s6b_zip = std::to_string(retDepCosZip());
      // REGION
      s6b_region = retDepCosReg();
    }
    else //PARTICULAR COSTUMER
    {
      // NAME
      s6b_name = retDepPCosName();
      // ADDRESS
      s6b_address = retDepPCosAddr();
      // CITY
      s6b_city = retDepPCosCity();
      // NIMA
      s6b_nima = std::to_string(retDepPCosNima());
      // PHONE
      s6b_phone = std::to_string(retDepPCosPhone());
      // PROVINCE
      s6b_province = retDepPCosProv();
      // REGISTRATION NUMBER
      s6b_num_ins = std::to_string(retDepPCosNumIns());
      // EMAIL
      s6b_email = retDepPCosMail();
      // NIF
      s6b_nif = retDepPCosNif();
      // ZIP
      s6b_zip = std::to_string(retDepPCosZip());
      // REGION
      s6b_region = retDepPCosReg();
    }
  }
  //  -> printing
  // NAME
  set_di_text(page1,fsize,47,font,s6b_name,188,187);
  // ADDRESS
  set_di_text(page1,fsize,47,font,s6b_address,188,162);
  // CITY
  // TODO: to adjust with new set_di_text function
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 188, 137);
  HPDF_Page_ShowText (page1, s6b_city.c_str());
  HPDF_Page_EndText (page1);
  // NIMA
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 188, 112);
  HPDF_Page_ShowText (page1, s6b_nima.c_str());
  HPDF_Page_EndText (page1);
  // PHONE
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 188, 86);
  HPDF_Page_ShowText (page1, s6b_phone.c_str());
  HPDF_Page_EndText (page1);
  // PROVINCE
  // TODO: to adjust with new set_di_text function
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 465, 137);
  HPDF_Page_ShowText (page1, s6b_province.c_str());
  HPDF_Page_EndText (page1);
  // INSCRIPTION NUMBER
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 465, 112);
  HPDF_Page_ShowText (page1, s6b_num_ins.c_str());
  HPDF_Page_EndText (page1);
  // EMAIL
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 465, 86);
  HPDF_Page_ShowText (page1, s6b_email.c_str());
  HPDF_Page_EndText (page1);
  // NIF
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 648, 187);
  HPDF_Page_ShowText (page1, s6b_nif.c_str());
  HPDF_Page_EndText (page1);
  // ZIP
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 648, 162);
  HPDF_Page_ShowText (page1, s6b_zip.c_str());
  HPDF_Page_EndText (page1);
  // REGION
  // TODO: to adjust with new set_di_text function
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 648, 137);
  HPDF_Page_ShowText (page1, s6b_region.c_str());
  HPDF_Page_EndText (page1);

 // 7.Caracteristicas del residuo
 //LER

 HPDF_Page_BeginText (page2);
 myText = std::to_string(retDepProdLER());
 HPDF_Page_MoveTextPos (page2, 140, 1075);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //DESC
 //TODO: to adjust with new set_di_text function
 HPDF_Page_BeginText (page2);
 myText = retDepProdName1() + " " + retDepProdName2() + " " + retDepProdName3();
 HPDF_Page_MoveTextPos (page2, 303, 1075);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //KG
 HPDF_Page_BeginText (page2);
 myText = std::to_string(retDepTotalWeight());
 HPDF_Page_MoveTextPos (page2, 659, 1075);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //PELIGROS
 //TODO: to adjust with new set_di_text function
 HPDF_Page_BeginText (page2);
 myText = retDepProdPeligro();
 HPDF_Page_MoveTextPos (page2, 260, 1050);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 // 8.Transportistas

 //NAME
 myText = retDepDriName();
 set_di_text(page2,fsize,47,font,myText,188,980);
 
 //DIRECCION
 myText = retDepDriAddr();
 set_di_text(page2,fsize,47,font,myText,188,955);
 
 //MUNICIPIO
 //TODO: to adjust with new set_di_text function
 HPDF_Page_BeginText (page2);
 myText = retDepDriCity();
 HPDF_Page_MoveTextPos (page2, 188, 930);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //NIMA
 HPDF_Page_BeginText (page2);
 myText = std::to_string(retDepDriNima());
 HPDF_Page_MoveTextPos (page2, 188, 904);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //TELEFONO
 HPDF_Page_BeginText (page2);
 myText = std::to_string(retDepDriPhone());
 HPDF_Page_MoveTextPos (page2, 188, 877);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //PROVINCIA
 //TODO: to adjust with new set_di_text function
 HPDF_Page_BeginText (page2);
 myText = retDepDriProv();
 HPDF_Page_MoveTextPos (page2, 465, 930);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //Nº INSC REGISTRO
 HPDF_Page_BeginText (page2);
 myText = std::to_string(retDepDriNumIns());
 HPDF_Page_MoveTextPos (page2, 465, 904);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //EMAIL
 HPDF_Page_BeginText (page2);
 myText = retDepDriMail();
 HPDF_Page_MoveTextPos (page2, 465, 877);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

  //NIF
  HPDF_Page_BeginText (page2);
  myText = retDepDriNif();
  HPDF_Page_MoveTextPos (page2, 648, 980);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);
  
  //CP
  HPDF_Page_BeginText (page2);
  myText = std::to_string(retDepDriZip());
  HPDF_Page_MoveTextPos (page2, 648, 955);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //COMUNIDAD AUTONOMA
  //TODO: to adjust with new set_di_text function
  HPDF_Page_BeginText (page2);
  myText = retDepDriReg();
  HPDF_Page_MoveTextPos (page2, 648, 930);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  // 9. Vehiculos y remolques

  //MATRICULA1
  HPDF_Page_BeginText (page2);
  myText = retDepPlate();
  HPDF_Page_MoveTextPos (page2, 190, 804);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);


  //MATRICULA2
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 190, 763);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //REMOLQUE1
  HPDF_Page_BeginText (page2);
  myText = retDepPlateAtt();
  HPDF_Page_MoveTextPos (page2, 468, 804);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //REMOLQUE2
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 468, 763);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  // 10.Otras informaciones

  //POSICION DE LA X EN SI O NO

  //SI X
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 220, 664);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //NO X
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 220, 640);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //FECHAENTREGA
  HPDF_Page_BeginText (page2);
  myText = retDepFinalDateTime();
  HPDF_Page_MoveTextPos (page2, 395, 690);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //FECHAACEPTACION
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 395, 665);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //CANTIDADACEPTADA
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 650, 665);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //FECHARECHAZO
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 395, 640);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //CANTIDADRECHAZADA
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 650, 640);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //FECHANEWTR
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 650, 614);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  //SRAP
  HPDF_Page_BeginText (page2);
  myText = " ";
  HPDF_Page_MoveTextPos (page2, 650, 583);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  // final and extra info

  //FIRMA
  strcpy (signature,  retDepDiFolder().c_str());
  strcat (signature, "/firma.png");
  draw_image (pdf, signature, 100, HPDF_Page_GetHeight (page2) - 900,"Firma transportista",0);
   /****************************************/
 //nuevas inserciones, Noviembre 2018
 //peso neto //  retDepTotalWeight(
 //peso tara //  retDepScaleOut()
 //peso bruto //  retDepScaleIn()
 //comentario operador // getOutputComment()
 //basculista //ret_staff_code();
 //identificación de bioreciclaje para firma // ?¿
 //precio // no lo tenemos
 //forma de pago //  está en la tabla de entidades de facturación
  //OPERATOR COMMENT BLOCK
 HPDF_Page_SetRGBFill(page2, 0.85, 0.85, 0.85);
 HPDF_Page_Rectangle(page2, 350, 475, 404,20);
 HPDF_Page_FillStroke(page2);
 HPDF_Page_SetRGBFill(page2, 1, 1, 1);
 HPDF_Page_Rectangle(page2, 350, 395, 404,80);
 HPDF_Page_FillStroke(page2);
 HPDF_Page_SetRGBFill(page2, 0, 0, 0);
 HPDF_Page_BeginText (page2);
 HPDF_Page_MoveTextPos (page2, 355, 480);
 HPDF_Page_ShowText (page2, "COMENTARIO OPERADOR:");
 std::vector< std::string> formatted_comment = ret_paragraph_with_lines_return(getOutputComment(),47);
 if(formatted_comment.size())
   {
     HPDF_Page_MoveTextPos(page2, 5, -25);
     HPDF_Page_ShowText(page2, formatted_comment[0].c_str());
     if(formatted_comment.size()>1)
       {
	 HPDF_Page_MoveTextPos(page2, 0, -15);
	 HPDF_Page_ShowText(page2, formatted_comment.at(1).c_str());
	 if(formatted_comment.size()>2)
	   {
	     HPDF_Page_MoveTextPos(page2, 0, -15);	     
	     HPDF_Page_ShowText (page2, formatted_comment.at(2).c_str());
	     if(formatted_comment.size()>3)
	       {
		 HPDF_Page_MoveTextPos(page2, 0, -15);	     
		 HPDF_Page_ShowText (page2, formatted_comment.at(3).c_str());
	       }
	   }
       }
   }
 HPDF_Page_EndText (page2);
 //END OPERATOR COMMENT BLOCK
 
 //WEIGHTS BLOCKS
 HPDF_Page_SetRGBFill(page2, 0.85, 0.85, 0.85);
 HPDF_Page_Rectangle(page2, 348, 345, 60, 40);
 HPDF_Page_Rectangle(page2, 488, 345, 60, 40);
 HPDF_Page_Rectangle(page2, 628, 345, 60, 40);
 HPDF_Page_FillStroke(page2);
 
 HPDF_Page_SetRGBFill(page2, 0, 0, 0);
 HPDF_Page_BeginText (page2);
 HPDF_Page_MoveTextPos (page2, 360, 360);
 HPDF_Page_ShowText (page2, "TARA");
 HPDF_Page_MoveTextPos (page2, 136, 0);
 HPDF_Page_ShowText (page2, "BRUTO");
 HPDF_Page_MoveTextPos (page2, 140, 0);
 HPDF_Page_ShowText (page2, "NETO"); 
 HPDF_Page_EndText (page2);

 HPDF_Page_SetRGBFill(page2, 1, 1, 1);
 HPDF_Page_Rectangle(page2, 408, 345, 70, 40);
 HPDF_Page_Rectangle(page2, 548, 345, 70, 40);
 HPDF_Page_Rectangle(page2, 688, 345, 70, 40);
 HPDF_Page_FillStroke(page2);

 HPDF_Page_SetRGBFill(page2, 0, 0, 0);
 HPDF_Page_BeginText (page2);
 ///tara
 myText = std::to_string(retDepScaleIn());
 myText += " Kg";
 HPDF_Page_MoveTextPos (page2, 412, 360);
 HPDF_Page_ShowText (page2, myText.c_str());
 ///bruto
 myText = std::to_string(retDepScaleOut());
 myText += " Kg";
 HPDF_Page_MoveTextPos (page2, 139, 0); 
 HPDF_Page_ShowText (page2, myText.c_str());
 ///neto
 myText = std::to_string(retDepTotalWeight());
 myText += " Kg"; 
 HPDF_Page_MoveTextPos (page2, 141, 0);
 HPDF_Page_ShowText (page2, myText.c_str()); 
 HPDF_Page_EndText (page2);
 //END WEIGHTS BLOCKS

 //STAFF BLOCK
 HPDF_Page_SetRGBFill(page2, 0.85, 0.85, 0.85);
 HPDF_Page_Rectangle(page2, 350, 315, 235,20);
 HPDF_Page_FillStroke(page2);
 HPDF_Page_SetRGBFill(page2, 1, 1, 1);
 HPDF_Page_Rectangle(page2, 350, 235, 235,80);
 HPDF_Page_FillStroke(page2);
 HPDF_Page_SetRGBFill(page2, 0, 0, 0);
 HPDF_Page_BeginText (page2);
 HPDF_Page_MoveTextPos (page2, 355, 320);
 HPDF_Page_ShowText (page2, "BASCULISTA:");
 
 HPDF_Page_MoveTextPos(page2, 10, -45);
 myText = "CÓDIGO: ";
 myText += std::to_string(ret_staff_code());
 HPDF_Page_ShowText(page2, myText.c_str());   
 HPDF_Page_EndText (page2);
 draw_image (pdf, "image/sellotrans.png", 420, 205,"",0);
 //END STAFF BLOCK
 //PRICE BLOCK
 if(retDepPayProcedure()==1)
   {
     HPDF_Page_SetRGBFill(page2, 0.85, 0.85, 0.85);
     HPDF_Page_Rectangle(page2, 595, 315, 160,20);
     HPDF_Page_FillStroke(page2);
     HPDF_Page_SetRGBFill(page2, 1, 1, 1);
     HPDF_Page_Rectangle(page2, 595, 235, 160,80);
     HPDF_Page_FillStroke(page2);
     HPDF_Page_SetRGBFill(page2, 0, 0, 0);
     HPDF_Page_BeginText (page2);
     HPDF_Page_MoveTextPos (page2, 600, 320);
     HPDF_Page_ShowText (page2, "PRECIO:");

     double total_price = retDepTotalWeight()*retDepPrice() / 1000.0;
     std::stringstream stream;
     stream << std::fixed << std::setprecision(2) << total_price;
     std::string precio_final = stream.str();

     precio_final += " Euros";
     
     HPDF_Page_MoveTextPos(page2, 20, -45);
     HPDF_Page_ShowText(page2, precio_final.c_str());   
     HPDF_Page_EndText (page2);
   }
 //END PRICE BLOCK
 
  try
    {
      std::cout << "INFO: saving to... " << fname << std::endl;
      HPDF_SaveToFile (pdf, fname);
      HPDF_SaveToFile (pdf, "ultima_DI_salidas.pdf");
    }
  catch(...)
    {
      std::cout << "falló la creación del PDF:"<< fname << " !" << std::endl; 
    }
  int iterations,max_iterations;
  max_iterations = 10000;
  iterations = 0;
  struct stat buffer;   
  while(stat (fname, &buffer) && iterations<max_iterations)
    {
      iterations++;
    }

  /* clean up */
  HPDF_Free (pdf);
  std::cout << "FIN CREATE PDF!!" << std::endl;
  // printing

  if (!printerId.empty())
    {
      int num_options = 0;
      cups_option_t *options = NULL;
      num_options = cupsAddOption("fit-to-page", "true", num_options, &options);
      cupsPrintFile(printerId.c_str(), fname, "TICKET", 1, options);
      //cupsPrintFile("Brother-MFC-j625DW",fname, "TICKET", 1, options);
    }
  return;

}

//////////////////////////////////////////////////////////////////
//TICKET generation
//////////////////////////////////////////////////////////////////
/*! function for creating our ticket document with all the stored info 
  about our movement*/
int outputForm::createTicket(std::string printerId, std::string ticketCode)
{
  printable *myTicket;
  std::string fileName = "ticket.pdf";

  myTicket = new printableTicket(fileName, printerId);

  myTicket->setTicketType("REGISTRO DE SALIDA");
  myTicket->setTicketCode(ticketCode);
  costumer * our_costumer;
  retOurId(our_costumer);
  myTicket->setOurCIF(our_costumer->getNif());
  delete our_costumer;
  station * localDestination;
  retDepOriginStation(localDestination);
  myTicket->setStationName(localDestination->getName());
  myTicket->setStationNIMA(std::to_string(localDestination->getNima()));
  delete localDestination;
  myTicket->setMovCode(retDepMovCode());
  myTicket->setMovDate(retDepFinalDateTime().substr(0, retDepFinalDateTime().find(' ')));
  myTicket->setMovTime(retDepFinalDateTime().substr(retDepFinalDateTime().find(' '), retDepFinalDateTime().length()));
  station * destination;
  retDepDestinationStation(destination);
  myTicket->setCostumerName(destination->getName());
  delete destination;
  myTicket->setTransportName(retDepDriName());
  myTicket->setTransportPlate(retDepPlate());
  myTicket->setProductName(retDepProdFullName());
  myTicket->setProductLER(std::to_string(retDepProdLER()));
  myTicket->setGrossWeight(std::to_string(retDepScaleOut()));
  myTicket->setNetWeight(std::to_string(retDepScaleIn()));
  myTicket->setTotalWeight(std::to_string(retDepTotalWeight()));
  myTicket->setPayProcedure(retDepPayProcedure());
  double total_price = retDepTotalWeight()*retDepPrice() / 1000.0;
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << total_price;
  myTicket->setFinalPrice(stream.str());
  myTicket->setComment(getOutputComment());
  myTicket->setStaffCode(std::to_string(ret_staff_code()));
  std::string signaturePath = retDepDiFolder() + "/firma.png";
  myTicket->setSignaturePath(signaturePath);
  myTicket->composeFile();
  myTicket->saveFile();
  myTicket->printFile();
  delete myTicket;

  return 0;
}