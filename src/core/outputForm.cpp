/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023, 2024 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

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
    std::string sqliteQuery, mysqlQuery;
    std::string str_log_message;
  
    setTareWeight(retDepScaleIn());
    setGrossWeight(retDepScaleOut());
    setNetWeight((long)(retDepScaleOut() - retDepScaleIn()));
    // upgrading definetively the DI number
    setDepDi(createDINumber(localDatabase, 0));
    //getting sql queries
    std::string myMoveCode = storeMov(sqliteQuery, mysqlQuery, depOriginStation, localDatabase);

    //trying to remote save
    if(remote_host_connected)
    {
        str_log_message = "(CARGA) remote db -> ";
        str_log_message += mysqlQuery;
        log_message(str_log_message, 1);
        if(!remoteDatabase.query(NULL,mysqlQuery.c_str()))
	    {
	        log_message("(CARGA) registro en BD remota parece OK", 1);
	        int sync = 0;
	        selLastMovCode(mysqlQuery, std::to_string(depOriginStation->getCode()));
	        str_log_message = "(CARGA) chequeo redundante en BD remota -> ";
	        str_log_message += mysqlQuery;
	        log_message(str_log_message, 1);
            if(!remoteDatabase.query(NULL,mysqlQuery.c_str())) //NO SYNCRONIZED
	        {
                if(remoteDatabase.retData2().size())
                {
	                if(remoteDatabase.retData2().at(0).at(0) == myMoveCode)
		                sync = 1;
                }
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
	            // deleting from transit
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
	            if(!ret && retDepMovType() == DEF_MOV_LOADING)
		        {
                    sqliteQuery.clear();
                    mysqlQuery.clear();
		            delOrder(sqliteQuery, mysqlQuery, depOriginStation->getCode(), depCostumer->getCode(), retDepProdCode());
		            str_log_message = "(CARGA) db local -> ";
		            str_log_message += sqliteQuery;
		            log_message(str_log_message, 1);
		            if(localDatabase.query(NULL, sqliteQuery.c_str()))
		            {
		                ret=-10;
		                log_message("(CARGA) registro en BD local parece ERROR", 2);
		            }
		            else
		            {
		                log_message("(CARGA) registro en BD local parece OK", 2);		
		            }
		            str_log_message = "(CARGA) db remota -> ";
		            str_log_message += mysqlQuery;
		            log_message(str_log_message, 1); 
		            if(remoteDatabase.query(NULL, mysqlQuery.c_str()))
		            {
		                ret = -100;
		                log_message("(CARGA) registro en BD remota parece ERROR", 2);
		            }
		            else
		            {
		                log_message("(CARGA) registro en BD remota parece OK", 2);	
		            }
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
    std::cout << "ACTUALIZAMOS INDEX? ret = " << ret << std::endl;
    if (ret != -2)
    {
        // upgrading local incremental number (if we have) 
        upgradeLocalIncremental(localDatabase);
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
    values += std::to_string(depDriver->getCode());
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
    }
    else
    {
        log_message("(CARGA) registro en BD local parece ERROR, catastrófico", 2);
        ret = -2;
    }
    std::cout << "ACTUALIZAMOS INDEX? ret = " << ret << std::endl;
    if (ret != -2)
    {
        // upgrading local incremental number (if we have)
        upgradeLocalIncremental(my_local_database);
    }
    return ret;
}
void outputForm::setOrders(qtDatabase & myDatabase, long station_code)
{
    std::string sql;
    int numCol=0;
    struMovement myOrder;

    allOrders.clear();
    selAllFromOrders(sql, station_code);
    myDatabase.query(NULL, sql.c_str());

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
	        else if(numCol == 40) // NUMERODI
	        {
		        myOrder.DI = *col;
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
void outputForm::setTransferMov(costumer *& myCostumer, station *& myStation)
{
    //MOV TYPE
    setDepMovType(DEF_MOV_TRANSFER);
    setDepCostumer(myCostumer);
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

void outputForm::setDepScaleOut(unsigned int scale)
{
    myDepMovement.PESO_SALIDA = scale;
    long newNet = retDepScaleOut() - retDepScaleIn();
    if(newNet < 0)
        newNet = 0;
    setNetWeight((unsigned int) newNet);
    return;
}

/*! function to save scale out in database*/
int outputForm::saveScaleOut(qtDatabase & myDatabase, qtDatabase &myRemoteDatabase, const char * remoteHost, int remotePort)
{
    std::string sql;
    int ret = 1;

    // this function must be fixed, using grossWeight not netWeight, for saving simply scaling as in Arriving Transit.
    updtScaleOutTransSal(sql, retDepDateTime(), depCostumer->getCode(), retDepProdCode(), retNetWeight(), getOutputComment().c_str(), vectorToString(getOutputIncidents(), ";").c_str());
  
    if(!myDatabase.query(NULL, sql.c_str()))
    {
        ret = 0;
        if(isConnected(remoteHost, remotePort))
	    {
	        remote_updatePesoSalidaTransitoSalida(sql, depCostumer->getCode(), retDepDateTime().c_str(),ourStation->getCode(),retNetWeight(),getOutputComment().c_str(),vectorToString(getOutputIncidents(),";").c_str());
	        myRemoteDatabase.query(NULL, sql.c_str());
	    }
    }
    return ret;
}

//transit movements managment
/*! FUNCTION IS WRONG! FIX IT*/
int outputForm::storeTransit(qtDatabase & myDatabase,qtDatabase & remoteDatabase, station * myStation, int remote_host_connected)
{
    int ret = 0;
    std::string str_log_message;
  
    std::string mysql_sql = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR) values (\"";
    std::string sqlite_sql = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR, SINCRONIZADO, FOLDER) values (\"";
  
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
	        sqlite_sql += ",1 ,\'";
            sqlite_sql += retArrDiFolder() + "\')";
	    }
        else
	    {
	        log_message("(LOADING)(to transit) remote BD query seems to be ERROR", 2);
	        ret = -1;//database error
	        sqlite_sql += ",0 ,\'";
            sqlite_sql += retArrDiFolder() + "\')";
	    }
        str_log_message = "(LOADING)(to transit) local db -> ";
        str_log_message += sqlite_sql;
        log_message(str_log_message, 1);
        if(myDatabase.query(NULL, sqlite_sql.c_str()))
        {
            log_message("(LOADING)(to transit) local BD query seems to be ERROR (DONE NOTHING!)", 2);
            ret = -1;
        }
    }
    else
    {
        log_message("(LOADING)(to transit) remote BD query seems to be ERROR", 2);
        ret = -1;
        sqlite_sql += ",0 ,\'";
        sqlite_sql += retArrDiFolder() + "\')";
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
        if(row->size() >= 14) //DATABASE DEPENDANT
	    {
	        if(!byPlate.compare(row->at(5)) && (num_of_row >= index || index == -1)) //DATABASE DEPENDANT
	        {
	            type = retDepMovType();
	            clearDepMov();
	            setDepDi(row->at(0)); //DI
	            setDepDateTime(row->at(1)); //FECHA_HORA
	            try
		        {
		            depCostumer->setCostumer(std::stol(row->at(2)), myDatabase); // Costumer
		        }
	            catch(...)
		        {
		            depCostumer->reset();
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
		            setDepScaleOut(std::stoul(row->at(8)) + retDepScaleIn());
		        }
	            catch(...)
		        {
		            setDepScaleOut(retDepScaleIn());
		        }
                std::cout << "PESO BÁSCULA SALIDA = " << retDepScaleOut() << std::endl;
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
                // tare and net weight:
                setTareWeight(retDepScaleIn());
                setGrossWeight(retDepScaleOut());
                setNetWeight(retDepScaleOut() - retDepScaleIn());
                //
                std::string toRemove = "saves/";
                std::string folder = row->at(13);
                setDepDiFolder(folder.substr(toRemove.size(), folder.size() - toRemove.size()));
                //  NPT
                setDepNPTData(myDatabase, "SAL");
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
int outputForm::setDepNPTData(qtDatabase & localDatabase, const char * type)
{
    int ret = -1;
    std::string sql;

    if(depCostumer != NULL && retDepProdCode() > 0)
    {
        selProdPermits(sql, type, retDepProdCode());
        if(!localDatabase.query(NULL, sql.c_str()))
        {
            ret = 0;
            std::vector <std::vector <std::string>> dataReturn = localDatabase.retData2();
            if(dataReturn.size())
            {
                try
                {
                    myDepMovement.PERMISOS_PRODUCTO.FLAG_NPT = std::stol(dataReturn[0].at(2));
                }
                catch(...)
                {
                    myDepMovement.PERMISOS_PRODUCTO.FLAG_NPT = 0;
                    ret = -2;
                }
            }
        }
        selProdCosPermits(sql, type, retDepProdCode(), depCostumer->getCode());
        if(!localDatabase.query(NULL, sql.c_str()))
        {
            std::vector <std::vector <std::string>> dataReturn = localDatabase.retData2();
            if(dataReturn.size())
            {
                myDepMovement.PERMISOS_PRODUCTO.NPT = dataReturn[0].at(1);
            }
        }
        std::cout << "NPT data, FLAG = " <<  myDepMovement.PERMISOS_PRODUCTO.FLAG_NPT << ", NPT = " << myDepMovement.PERMISOS_PRODUCTO.NPT << std::endl;
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

std::string outputForm::createDINumber(qtDatabase & localDatabase, int arrive)
{
    station *myStation = NULL;
    costumer *me = NULL;
    costumer *operCostumer = NULL;

    retOurStation(myStation);
    retOurId(me);

    int movType = DEF_MOV_LOADING;
    if(arrive)
    {
        retArrCostumer(operCostumer);
        movType = retArrMovType();
    }
    else
    {
        retDepCostumer(operCostumer);
        movType = retDepMovType();
    }
    if(movType <= 0)
        movType = DEF_MOV_LOADING;

    // TODO: TO IMPROVE, inside the class?
    std::string DI = "";

    // std::cout << "(DI GENERATION): COMPARING OPERATOR WITH US" << std::endl;
    // std::cout << "Operator name = " <<  operCostumer->getName() << " and code = " << std::to_string(operCostumer->getCode()) << std::endl;
    // std::cout << "Us name = " <<  me->getName() << " and code = " << std::to_string(me->getCode()) << std::endl;
    // we are NOT the operators
    if (me->getCode() != operCostumer->getCode() && movType != DEF_MOV_TRANSFER)
    {
        DI = getMovCode(localDatabase, myStation, movType);
        if (!arrive)
            myDepMovement.DI = DI;
        std::cout << "(DI GENERATION): OPERATOR IS NOT US, CASE: 1, DI GENERATED = " << DI << std::endl;
    }
    // we ARE the operators
    else
    {
        // NP present?
        int NP;
        if(arrive)
            NP = myArrMovement.PERMISOS_PRODUCTO.FLAG_NPT;
        else
            NP = myDepMovement.PERMISOS_PRODUCTO.FLAG_NPT;
        if(!NP)
        {
            std::time_t t = std::time(nullptr);
            std::tm *const pTInfo = std::localtime(&t);
            std::string actualYear = std::to_string(1900 + pTInfo->tm_year);
            std::string valueYear = "";
            DI = myStation->getNima() + actualYear;
            int correlNumber = 0;
            std::string sql;
            getParamValue(sql, "NUMBER");
            log_message("(LOADING)(DI number creation) BD local -> " + sql, 1);
            if(!localDatabase.query(NULL, sql.c_str()))
            {
                std::vector <std::vector <std::string>> dataReturn = localDatabase.retData2();
                if(dataReturn.size())
                {
                    try
                    {
                        correlNumber = std::stoi(dataReturn[0].at(0));
                    }
                    catch(const std::exception& e)
                    {
                        std::cout << e.what() << '\n';
                        log_message("(LOADING)(DI number creation) Exception can't convert to number", 2);
                    }
                    valueYear = dataReturn[0].at(1);
                    if (correlNumber > 9999999)
                    {
                        std::cout << " correlNumber: " << correlNumber << " overflowed " << std::endl;
                        correlNumber = 0;
                        setParamValue(sql, "NUMBER", "0", std::to_string(1900 + pTInfo->tm_year));
                        log_message("(LOADING)(DI number creation)(Number overflowed) BD local -> " + sql, 1);
                        if(localDatabase.query(NULL, sql.c_str()))
                            log_message("(LOADING)(DI number creation) Query ERROR", 2);
                    }
                    if (std::stoi(valueYear) != std::stoi(actualYear))
                    {
                        std::cout << " valueYear: " << valueYear << " is different to the actual year: " << actualYear << std::endl;
                        correlNumber = 0;
                        setParamValue(sql, "NUMBER", "0", std::to_string(1900 + pTInfo->tm_year));
                        log_message("(LOADING)(DI number creation)(OLD year) BD local -> " + sql, 1);
                        if(localDatabase.query(NULL, sql.c_str()))
                            log_message("(LOADING)(DI number creation) Query ERROR", 2);
                    }
                }
                else
                {
                    std::cout << " NO DATA RETURNED " << std::endl;
                    correlNumber = 0;
                    setParamValue(sql, "NUMBER", "0", std::to_string(1900 + pTInfo->tm_year));
                    log_message("(LOADING)(DI number creation)(no data returned) BD local -> " + sql, 1);
                    if(localDatabase.query(NULL, sql.c_str()))
                        log_message("(LOADING)(DI number creation) Query ERROR", 2);
                }
            }
            else
            {
                std::cout << " QUERY ERROR " << std::endl;
                log_message("(LOADING)(DI number creation) Query ERROR", 2);
                correlNumber = 0;
                setParamValue(sql, "NUMBER", "0", std::to_string(1900 + pTInfo->tm_year));
                log_message("(LOADING)(DI number creation)(query error) BD local -> " + sql, 1);
                if(localDatabase.query(NULL, sql.c_str()))
                    log_message("(LOADING)(DI number creation) Query ERROR", 2);
            } 
            DI += zeroPadNumber(correlNumber, 7);
            if(!arrive)
                myDepMovement.DI = DI;

            std::cout << "(DI GENERATION): OPERATOR IS US, NO NPT CASE: 2 (OR TRANSFER MOVEMENT WITH NO NPT!), DI GENERATED = " << DI << std::endl;
        }
        else
        {
            if(movType == DEF_MOV_TRANSFER)
            {
                std::string sql;
                std::time_t t = std::time(nullptr);
                std::tm *const pTInfo = std::localtime(&t);
                int actualYear = 1900 + pTInfo->tm_year;
                int actualMonth = 1 + pTInfo->tm_mon;
                selStationDI(sql, actualMonth, actualYear);
                log_message("(LOADING)(DI number creation) BD local -> " + sql, 1);
                if(!localDatabase.query(NULL, sql.c_str()))
                {
                    std::vector <std::vector <std::string>> dataReturn = localDatabase.retData2();
                    if(dataReturn.size())
                    {
                        DI = dataReturn[0].at(0);
                    }
                    else
                    {
                        // NEED SYNCING!
                        std::cout << " NO DATA RETURNED " << std::endl;
                        log_message("(LOADING)(DI number creation)(no data returned NEED SYNCING) BD local -> " + sql, 1);                    
                        DI.clear();
                    }
                }
                else
                {
                    log_message("(LOADING)(DI number creation) Query ERROR", 2);
                    DI.clear();
                }
                if(arrive)
                    myArrMovement.DI = DI;
                else
                    myDepMovement.DI = DI;
                std::cout << "(DI GENERATION): TRANSFER MOVEMENT AND NPT! CASE: 4, DI GENERATED = " << DI << std::endl;
            }
            else
            {
                if (arrive)
                    DI = myArrMovement.DI;
                else
                    DI = myDepMovement.DI;
                std::cout << "(DI GENERATION): OPERATOR IS US, AND NPT! CASE: 3, DI GENERATED = " << DI << std::endl;
            }
        }
    }
    createDIFolder(DI, arrive);
    std::cout << "(DI GENERATION): FINAL DI GENERATED = " << DI << std::endl;
    return DI;
}

int outputForm::upgradeLocalIncremental(qtDatabase & localDatabase)
{
    int ret = 0;
    station *myStation = NULL;
    costumer *me = NULL;
    costumer *operCostumer = NULL;

    retOurStation(myStation);
    retOurId(me);
    retDepCostumer(operCostumer);

    int movType = retDepMovType();
    if(movType <= 0)
        movType = DEF_MOV_LOADING;

    // we ARE the operators
    if (me->getCode() == operCostumer->getCode())
    {
        // NP present?
        if(!myDepMovement.PERMISOS_PRODUCTO.FLAG_NPT)
        {
            std::time_t t = std::time(nullptr);
            std::tm *const pTInfo = std::localtime(&t);
            std::string actualYear = std::to_string(1900 + pTInfo->tm_year);
            std::string sql;
            int correlNumber = 0;
            getParamValue(sql, "NUMBER");
            log_message("(LOADING)(DI number creation) BD local -> " + sql, 1);
            if(!localDatabase.query(NULL, sql.c_str()))
            {
                std::vector <std::vector <std::string>> dataReturn = localDatabase.retData2();
                if(dataReturn.size())
                {
                    try
                    {
                        correlNumber = std::stoi(dataReturn[0].at(0));
                    }
                    catch(const std::exception& e)
                    {
                        std::cout << e.what() << '\n';
                        log_message("(LOADING)(DI number creation) Exception can't convert to number", 2);
                    }
                    correlNumber++;
                    if (correlNumber > 9999999)
                        correlNumber = 0;

                    setParamValue(sql, "NUMBER", std::to_string(correlNumber), actualYear);
                    log_message("(LOADING)(upgrading local index) BD local -> " + sql, 1);
                    if(localDatabase.query(NULL, sql.c_str()))
                        log_message("(LOADING)(upgrading local index) Query ERROR", 2);
                    ret = 1;
                }
                else
                {
                    correlNumber = 0;
                    setParamValue(sql, "NUMBER", "0", actualYear);
                    log_message("(LOADING)(upgrading local index) BD local -> " + sql, 1);
                    if(localDatabase.query(NULL, sql.c_str()))
                        log_message("(LOADING)(upgrading local index) Query ERROR", 2);
                    ret = 2;
                }
            }
            else
            {
                log_message("(LOADING)(upgrading local index) Query ERROR", 2);
                correlNumber = 0;
                setParamValue(sql, "NUMBER", "0", actualYear);
                log_message("(LOADING)(upgrading local index) BD local -> " + sql, 1);
                if(localDatabase.query(NULL, sql.c_str()))
                    log_message("(LOADING)(upgrading local index) Query ERROR", 2);
                ret = 3;
            } 
        }
    }
    return ret; 
}

// TODO: error handling not implemented
void outputForm::setAllDiData(qtDatabase & localDatabase, station *myStation, long ourCode, long defDriverCode)
{
    // common data
    // product information
    if(retDepProdCode()>0)
    {
        if(setAllProductData(localDatabase)) // TODO: error handling
	        std::cout << "*ERROR*" << std::endl;
        if(setDepNPTData(localDatabase, "SAL")) // TODO: error handling, always SAL?
            std::cout << "*ERROR*" << std::endl;        
    }
    // costumer information
    // pass
    // costumer-product information
    if(retDepProdCode()>0 && depCostumer->getCode() > 0)
    {
        if(setAllDepCosProdData(localDatabase, myStation))
	        std::cout << "*ERROR*" << std::endl;
    }
    // billing method and price
    if(set_all_billing_info(localDatabase))
        std::cout << "*ERROR*" << std::endl;
    // origin station, us!
    if(myStation)
        setDepOrigStation(myStation);
    // output movement
    if(retDepMovType() == DEF_MOV_LOADING)
    {
        getAllOrderInfo(localDatabase, myDepMovement.CODIGO_ORDEN);
    }
    else
    {
        // destination station
        if (depDestinationStation)
        {
            int value;
            depDestinationStation->getType(value);
            if(value == DEF_STATION_DEPOSIT) //movement to deposit
	        {
	            setDepMovType(DEF_MOV_TODEPOSITD5);
                depCostumer->setCostumer(defDriverCode, localDatabase);
	            depCostumer->setType(3);
	        }
            if(value == DEF_STATION_TRANSFER || value == DEF_STATION_MASTER) //movement of transference
	        {
	            setDepMovType(DEF_MOV_TRANSFER);
                depCostumer->setCostumer(ourCode, localDatabase);
	            depCostumer->setType(2);
	        }
        }
        // default driver loaded
        if (defDriverCode > 0) // if default driver configured
	    {
	        if (depDriver->getCode() <= 0)
	        {
	            setDriverByCode(defDriverCode, localDatabase);
	        }
	    }
    }
    return;
}
/*! function for managing all new information preset by the order*/
int outputForm::getAllOrderInfo(qtDatabase & localDatabase, long order_code)
{
    std::string sql;
    int numCol=0;
    long costumer_code = 0;
    long station_code = 0;
    selOrderById(sql, order_code);
    localDatabase.query(NULL, sql.c_str());

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
                depCostumer->setType(std::stoi(*col));
		    }
	        catch(...)
		    {
		        depCostumer->setType(1);
		    }
	    }
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
            depDestinationStation->setNima(*col);
	    }
        else if(numCol == 24) // INFO_DESTINO_CENTRO_N_INSC_REGISTRO
	    {
            if(!depDestinationStation)
                depDestinationStation = new station();
            depDestinationStation->setNumIns(*col);
	    }
        else if(numCol == 25) // INFO_DESTINO_CENTRO_TELEFONO
	    {
            if(!depDestinationStation)
                depDestinationStation = new station();
            depDestinationStation->setPhone(*col);
	    }
        else if(numCol == 26) // INFO_DESTINO_CENTRO_EMAIL
	    {
            if(!depDestinationStation)
                depDestinationStation = new station();
            depDestinationStation->setMail(*col);
	    }
        else if(numCol == 27) // INFO_AUTHORIZED_COSTUMER_NOMBRE
	    {
            if(!depAuthCostumer)
                depAuthCostumer = new costumer();
            depAuthCostumer->setName(*col);
	    }
        else if(numCol == 28) // INFO_AUTHORIZED_COSTUMER_NIF
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
                depAuthCostumer->setZip(std::stoul(*col));
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
            depAuthCostumer->setNima(*col);
	    }
        else if(numCol == 35) // INFO_DESTINO_AUTORIZADO_N_INSC_REGISTRO
	    {
            if(!depAuthCostumer)
                depAuthCostumer = new costumer();
            depAuthCostumer->setNumIns(*col);
	    }
        else if(numCol == 36) // INFO_DESTINO_AUTORIZADO_TELEFONO
	    {
            if(!depAuthCostumer)
                depAuthCostumer = new costumer();
            depAuthCostumer->setPhone(*col);
	    }
        else if(numCol == 37) // INFO_DESTINO_AUTORIZADO_EMAIL
	    {
            if(!depAuthCostumer)
                depAuthCostumer = new costumer();
            depAuthCostumer->setMail(*col);
	    }
        else if(numCol == 38) // NUMERODI
	    {
            std::string tmpDI = "";
            if(col->find_first_not_of(' ') != std::string::npos)
            {
                if(!col->empty())
                    tmpDI = *col;
            }
            setDepDi(tmpDI);
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
    if(depDriver->getCode() <= 0)
        ret = 0;
    //CODIGO_CLIENTE
    if(depCostumer->getCode() <= 0)
        ret = 0;
    //DESTINATION
    if(depDestinationStation->getCode() <= 0 && !depDestinationStation->isManuallyEdited())
        ret = 0;
    return ret;
}

void outputForm::createDocs(std::string printerId, std::string tkPrinterId, std::string ticketCode, qtDatabase & localDatabase)
{
    costumer *us = NULL;
    costumer *theCostumer = NULL;
    retDepCostumer(theCostumer);
    retOurId(us);
    std::cout << "checking if movement is transfer: " << retDepMovType() << " is different to: " << DEF_MOV_TRANSFER << ". and if operator: " << theCostumer->getCode() << ", is different to us: " << us->getCode() << std::endl;
    if(retDepMovType() != DEF_MOV_TRANSFER && theCostumer->getCode() != us->getCode())
    {
        createTicket(tkPrinterId, ticketCode, localDatabase);
    }
    else
    {
        createPdf(printerId);
    }
    if (us != NULL)
        delete us;
    if (theCostumer != NULL)
        delete theCostumer;
    return;
}

//////////////////////////////////////////////////////////////////
//PDF generation
//////////////////////////////////////////////////////////////////
/*! function for creating our document with all the stored info 
  about our movement*/
void outputForm::createPdf(std::string printerId)
{
    printable *myDi;
    std::string fileName = "último DI.pdf";
    myDi = new printableDi(fileName, printerId);

    myDi->setProductLer(std::to_string(retDepProdLER()));
    myDi->setProductDanger(retDepProdPeligro());
    myDi->setDiCode(retDepDi());
    myDi->setDiNpt(retDepPermitNpt());
    myDi->setDiDateTime(retDepDateTime());
    // ap4
    costumer *myCostumer = NULL;
    retDepCostumer(myCostumer);
    myDi->setAp4Cos(myCostumer);
    if(myCostumer)
    {
        delete myCostumer;
        myCostumer = NULL;
    }
    // ap 5
    station *myStation = NULL;
    if(retDepMovType() == DEF_MOV_TRANSFER || retDepMovType() == DEF_MOV_LOADING)
    {
        // station ours (actual local station indeed)
        retDepOriginStation(myStation);
        // costumer is us, we are managing the transport
        retOurId(myCostumer);
    }
    else
    {
        // station empty
        myStation = new station();
        // costumer is the departure costumer
        retDepCostumer(myCostumer);
    }
    myDi->setAp5Station(myStation);
    myDi->setAp5Cos(myCostumer);
    if (myStation)
    {
        delete myStation;
        myStation = NULL;
    }
    if (myCostumer)
    {
        delete myCostumer;
        myCostumer = NULL;
    }
    // ap 6
    retDepDestinationStation(myStation);
    if (depCostumer->getType() == 4 || depCostumer->getType() == 1) // special cases
    {
        retDepAuthCostumer(myCostumer);
    }
    else
    {
        retDepCostumer(myCostumer);
    }
    myDi->setAp6Station(myStation);
    myDi->setAp6Cos(myCostumer);
    
    if (myStation)
    {
        delete myStation;
        myStation = NULL;
    }
    if (myCostumer)
    {
        delete myCostumer;
        myCostumer = NULL;
    }
    // ap 7
    myDi->setAp7LER(std::to_string(retDepProdLER()));
    myDi->setAp7Name(retDepProdName1() + " " + retDepProdName2() + " " + retDepProdName3());
    if(retDepMovType() == DEF_MOV_TRANSFER)
        myDi->setNetWeight("-");
    else
        myDi->setNetWeight(std::to_string(retNetWeight()) + " Kg");
    myDi->setAp7Danger(retDepProdPeligro());

    // ap 8
    driver * myDriver = NULL;
    retDepDriver(myDriver);
    myDi->setAp8Driver(myDriver);
    if (myDriver)
    {
        delete myDriver;
        myDriver = NULL;
    }
    // ap 9
    myDi->setPlate(retDepPlate());
    myDi->setPlateAtt(retDepPlateAtt());
    // signing
    std::string _signature = retDepDiFolder() + "/firma.png";
    myDi->setSignaturePath(_signature);
    // operator comments
    myDi->setComment(getOutputComment());
    // weights
    if(retDepMovType() == DEF_MOV_TRANSFER)
    {
        myDi->setGrossWeight("-");
        myDi->setTareWeight("-");
    }
    else
    {
        myDi->setGrossWeight(std::to_string(retGrossWeight()) + " Kg");
        myDi->setTareWeight(std::to_string(retTareWeight()) + " Kg");
    }
    // staff
    myDi->setStaffCode(std::to_string(ret_staff_code()));
    myDi->setStampPath("image/sellotrans.png");
    // price
    if(retDepPayProcedure()==1)
    {
        double total_price_ = retNetWeight()*retDepPrice() / 1000.0;
        std::stringstream stream_;
        stream_ << std::fixed << std::setprecision(2) << total_price_;
        myDi->setFinalPrice(stream_.str() + " Euros");
    }

    myDi->composeFile();
    myDi->saveFile();
    myDi->saveFile(retDepDiFolder() + "/DI.pdf");
    myDi->printFile();
    delete myDi;
    return;
}

//////////////////////////////////////////////////////////////////
//TICKET generation
//////////////////////////////////////////////////////////////////
/*! function for creating our ticket document with all the stored info 
  about our movement*/
int outputForm::createTicket(std::string printerId, std::string ticketCode, qtDatabase &localDatabase)
{
    printable *myTicket;
    std::string fileName = "ticket.pdf";

    myTicket = new printableTicket(fileName, printerId);

    myTicket->setTicketType("REGISTRO DE SALIDA");
    myTicket->setTicketCode(ticketCode);
    costumer * our_costumer;
    retOurId(our_costumer);
    myTicket->setCostumerNif(our_costumer->getNif());
    station * localDestination;
    retDepOriginStation(localDestination);
    myTicket->setStationName(localDestination->getName());
    myTicket->setStationNIMA(localDestination->getNima());
    std::string diCode;
    costumer * depCostumer;
    retDepCostumer(depCostumer);
    if(our_costumer->getCode() != depCostumer->getCode())
        diCode = getMovCode(localDatabase, localDestination, retDepMovType());
    // else
    //   diCode = getDI();
    delete depCostumer;
    delete our_costumer;
    delete localDestination;
    myTicket->setMovCode(diCode);
    myTicket->setMovDate(retDepFinalDateTime().substr(0, retDepFinalDateTime().find(' ')));
    myTicket->setMovTime(retDepFinalDateTime().substr(retDepFinalDateTime().find(' '), retDepFinalDateTime().length()));
    station * destination;
    retDepDestinationStation(destination);
    myTicket->setCostumerName(destination->getName());
    delete destination;
    myTicket->setTransportName(depDriver->getName());
    myTicket->setTransportPlate(retDepPlate());
    myTicket->setProductName(retDepProdFullName());
    myTicket->setProductLER(std::to_string(retDepProdLER()));
    myTicket->setGrossWeight(std::to_string(retGrossWeight()));
    myTicket->setTareWeight(std::to_string(retTareWeight()));
    myTicket->setNetWeight(std::to_string(retNetWeight()));
    myTicket->setPayProcedure(retDepPayProcedure());
    double total_price = retNetWeight()*retDepPrice() / 1000.0;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << total_price;
    myTicket->setFinalPrice(stream.str());
    myTicket->setComment(getOutputComment());
    myTicket->setStaffCode(std::to_string(ret_staff_code()));
    std::string signaturePath = retDepDiFolder() + "/firma.png";
    myTicket->setSignaturePath(signaturePath);
    myTicket->composeFile();
    myTicket->saveFile();
    myTicket->saveFile(retDepDiFolder() + "/" + fileName);
    myTicket->printFile();
    delete myTicket;
    return 0;
}