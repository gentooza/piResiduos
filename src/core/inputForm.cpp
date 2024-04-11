/*
This file is part of PiResiduos.

Copyright 2017-2019, Pro Integra SL.
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
@file inputform.cpp
*/
#include "inputForm.h"
int inputForm::storeDepMov(qtDatabase & localDatabase,qtDatabase & remoteDatabase, int remote_host_connected)
{
    int ret = 1;
    std::string sqliteQuery,mysqlQuery;
    std::string str_log_message;

    setTareWeight(retDepScaleOut());
    setGrossWeight(retDepScaleIn());
    setNetWeight((long)(retDepScaleIn() - retDepScaleOut()));
    ////////////////////////////////////////
    storeMov(sqliteQuery,mysqlQuery,depDestinationStation,localDatabase);

    if(remote_host_connected) //SAVING MOVEMENT IN REMOTE SERVER
    {
        str_log_message = "(DESCARGA) en BD remota -> ";
        str_log_message += mysqlQuery;
        log_message(str_log_message, 1);
        if(!remoteDatabase.query(NULL,mysqlQuery.c_str())) //SYNCRONIZED
	    {
	        log_message("(DESCARGA) registro en BD remota parece OK ",1);
	        int sync=1;
	        //RECHECK!
	        check_last(mysqlQuery, depDestinationStation);
	        str_log_message = "(DESCARGA) chequeo redundante en BD remota -> ";
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
	            log_message("(DESCARGA) chequeo redundante en BD remota parece OK", 1);
	            sqliteQuery.replace(sqliteQuery.length()-2,1,"1");
	        }
	        else
	            log_message("(DESCARGA) chequeo redundante en BD remota parece que FALLÓ", 1);	  

	        str_log_message = "(DESCARGA) en BD local -> ";
	        str_log_message += sqliteQuery;
	        log_message(str_log_message, 1);
	        if(!localDatabase.query(NULL,sqliteQuery.c_str())) //REMOVED FROM LOCAL SERVER
	        {
	            log_message("(DESCARGA) registro en BD local parece OK", 1);
	            //DELETING TRANSIT
	            ret = 0;
	            mysqlQuery.clear();
	            mysqlQuery = "delete from transito where (FECHA_HORA =\"";
	            mysqlQuery += retDepDateTime();
	            mysqlQuery += "\" and CODIGO_ESTACION=";
	            mysqlQuery += std::to_string(depDestinationStation->getCode());
	            mysqlQuery += ")";
	            str_log_message = "(DESCARGA) en BD remota -> ";
	            str_log_message += mysqlQuery;
	            log_message(str_log_message, 1);
	            if(!remoteDatabase.query(NULL,mysqlQuery.c_str())) //OK
		        {
		            log_message("(DESCARGA) registro en BD remota parece OK", 1);
		        }
	            else //ERROR
		        {
		            log_message("(DESCARGA) registro en BD remota parece ERROR", 2);
		        }
	            sqliteQuery.clear();
	            sqliteQuery = "delete from TRANSITO where (FECHA_HORA =\"";
	            sqliteQuery += retDepDateTime();
	            sqliteQuery += "\")";
	            str_log_message = "(DESCARGA) en BD local -> ";
	            str_log_message += sqliteQuery;
	            log_message(str_log_message, 1);
	            if(!localDatabase.query(NULL,sqliteQuery.c_str()))
		        {
		            log_message("(DESCARGA) registro en BD local parece OK", 1);
		        }
	            else
		        {
		            log_message("(DESCARGA) registro en BD local parece ERROR", 2);
		        }
	            //if transfer, clean
	            if(!ret && retDepMovType() == DEF_MOV_TRANSFER)
		        {
		            char * sqlite;
		            char * mysql;
		            delTransfer(sqlite,mysql,depOriginStation->getCode(),depDestinationStation->getCode(),retDepProdCode(), retDepPlate().c_str());
		            str_log_message = "(DESCARGA) en BD remota -> ";
		            str_log_message += mysql;
		            log_message(str_log_message, 1);
		            if(remoteDatabase.query(NULL,mysql))
		            {
		                ret = -100;
		                log_message("(DESCARGA) registro en BD remota parece ERROR", 2);
		            }
		            else
		                log_message("(DESCARGA) registro en BD remota parece OK", 1);		  
		            str_log_message = "(DESCARGA) en BD local -> ";
		            str_log_message += sqlite;
		            log_message(str_log_message, 1);
		            if(localDatabase.query(NULL,sqlite))
		            {
		                ret=-10;
		                log_message("(DESCARGA) registro en BD local parece ERROR", 2);
		            }
		            else
		                log_message("(DESCARGA) registro en BD local parece OK", 1);		    
		            delete sqlite;
		            delete mysql;
		        }  	      
	        }
	        else
	        {
	            log_message("(DESCARGA) registro en BD local parece ERROR", 2);
	            ret = -2;
	        }
	    }
        else
	    {
	        ret = -1;
	        log_message("(DESCARGA)(guardando movimiento) BD remota ERROR(query)", 2);
        }
    }
    else
    {
        ret = -1;
        log_message("(DESCARGA)(guardando movimiento) BD remota ERROR(conexión)", 2);
    }
    if(ret < 0) //no remote saving
    {
        log_message("(DESCARGA)(guardando movimiento) Continuando sin salvar en el servidor remoto", 1);
        if(retDepMovType() != DEF_MOV_TRANSFER)
	    {
	        str_log_message = "(DESCARGA) en BD local -> ";
	        str_log_message += sqliteQuery;
	        log_message(str_log_message, 1);
	        if(!localDatabase.query(NULL,sqliteQuery.c_str())) //REMOVED FROM LOCAL SERVER
	        {
	            log_message("(DESCARGA) registro en BD local parece OK", 1);
	            //DELETING TRANSIT
	            sqliteQuery.clear();
	            sqliteQuery = "delete from TRANSITO where (FECHA_HORA =\"";
	            sqliteQuery += retDepDateTime();
	            sqliteQuery += "\")";	  
	            localDatabase.query(NULL,sqliteQuery.c_str());	      
	        }
	        else
	        {
	            log_message("(DESCARGA)(guardando movimiento) BD local ERROR", 1);
	            ret = -2;
	        }
	    }
        else
	        ret = -10;
    }
    log_message("(DESCARGA)(guardando movimiento) Terminado", 1);
    return ret;
}

void inputForm::setDepMov(int index, qtDatabase & myDatabase)
{
  std::cout << "(DEBUG:) inside outputForm::setDepMov(int index)" << std::endl;
  if(index+1 <= (int)vctAllTransit.size())
    {
      depMovIndex = index;
      std::vector<std::string> movement = vctAllTransit.at(index);
      std::vector<std::string>::iterator iter;
      int field=1;
      //preresetting the struct
      clearDepMov();
      for(iter = movement.begin(); iter != movement.end(); ++iter)
	{
	  std::cout << "taking field nº:" << field << " = " << *iter << std::endl;
	  if(field==2)
	    {
	      myDepMovement.FECHA_HORA = *iter;
	    }
	  if(field==3) //TIPO_MOVIMIENTO
	    {
	      myDepMovement.TIPO_DE_MOVIMIENTO = std::stoi(*iter);
	    }
	  if(field==4)
	    {
	      myDepMovement.CODIGO_CLIENTE = std::stoi(*iter);
	    }
	  else if(field==5)
	    {
	      myDepMovement.CODIGO_PRODUCTO = std::stoi(*iter);
	    }
	  else if(field==6)
	    {
	      myDepMovement.PESO_ENTRADA = std::stoi(*iter);
	    }
	  else if(field==7)
	    {
	      myDepMovement.PRECIO_TN = std::stoi(*iter);
	    }
	  else if(field==8)
	    {
	      myDepMovement.MATRICULA = *iter;
	    }
	  else if(field==9)
	    {
	      myDepMovement.REMOLQUE = *iter;
	    }	  
	  else if(field==10)
	    {
	      try
		{
		  depOriginStation = new station(std::stol(*iter),myDatabase);
		}
	      catch(...)
		{
		  depOriginStation = new station();
		}		
	    }
	  else if(field==11)
	    {
	      setOutputIncidents(stringToVector(*iter,"; "));
	    }
	  else if(field==12)
	    {
	      setOutputComment(*iter);
	    }
	  else if(field==13)
	    {
	      myDepMovement.PESO_SALIDA = std::stoi(*iter);
	    }
	  field++;
	}
    }
  //std::cout << "(DEBUG:) inside outputForm::setOrder(int index), exiting" << std::endl;
  return;
}
//SCALES
int inputForm::isArrPesoOk()
{
  int ret = 0;
  std::cout << "TODO, COMPARANDO SI " << retArrScaleIn() << " > 2" << std::endl;
  if(retArrScaleIn() > 2)
    {
      ret = 1;
    }
  return ret;
}
int inputForm::isDepPesoOk()
{
  int ret = 0;
  if((retDepScaleOut() < retDepScaleIn()) && (retDepScaleOut() > 0))
    ret = 1;
  return ret;
}

/*! function to save and calculate total scale
TODO: USELESS to REMOVE */
void inputForm::setAndCalcScaleOut(unsigned int scale)
{
    setDepScaleOut(scale);
}

/*! function to save scale out in database*/
int inputForm::saveScaleOut(qtDatabase & myDatabase, qtDatabase &myRemoteDatabase, const char * remoteHost, int remotePort )
{
    int ret = 1;

    setAndCalcScaleOut(retDepScaleOut());
    char *sql = NULL;
    updtScaleOutTrans(sql, retDepDateTime().c_str(), depCostumer->getCode(), retDepProdCode(), retDepScaleOut(), getOutputComment().c_str(),vectorToString(getOutputIncidents(),";").c_str());
    
    if(!myDatabase.query(NULL,sql))
    {
        ret = 0;     
        if(isConnected(remoteHost, remotePort))
        {
            std::string another_sql;
            remote_updatePesoSalidaTransito(another_sql, depCostumer->getCode(), retDepDateTime().c_str(),ourStation->getCode(),retDepScaleOut(),getOutputComment().c_str(),vectorToString(getOutputIncidents(),";").c_str());
            myRemoteDatabase.query(NULL,another_sql.c_str());
        }
    }
    if (sql != NULL)
        delete[] sql;
    return ret;
}

///
int inputForm::setMovCode(std::string sLastCode, int stationCode, int movementTypeCode)
{
  long lastCode = std::stol(sLastCode);
  std::string newCode;
  std::string str_station_code;
  //costumer need, bad idea:
  //station codes of fixed size 2.
  //TODO REVCODES
  //if(stationCode <10)
  //  str_station_code = "0";
  //FIN TODO REVCODES
  str_station_code += std::to_string(stationCode);
  
  if (lastCode > 0 && sLastCode.size() > 11)
    {
      std::cout << "tenemos last code = " << lastCode << std::endl;
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
      std::cout << "no tenemos last code!!" << lastCode << std::endl;
      time_t myTime = time(NULL);
      struct tm *aTime = localtime(&myTime);
      int year = aTime->tm_year + 1900;

      newCode = std::to_string(year) + str_station_code + "000001" + std::to_string(movementTypeCode);
    }
  myDepMovement.CODIGO_MOVIMIENTO = newCode;
  return 0;
}
//transfer movements managment
int inputForm::isTrf(qtDatabase & myDatabase, station *& myStation)
{
    int ret = 0;
    if(!retArrPlate().empty())
    {
        char * sql = NULL;
        selAllTransfers(sql, myStation->getCode());
        if(!myDatabase.query(NULL,sql))
	    {
            std::vector<std::vector<std::string>> retData;
            std::vector<std::vector<std::string>>::iterator regs;
            std::vector<std::string>::iterator iter;
            int field = 0;
	        retData = myDatabase.retData2();
	        for(regs = retData.begin(); regs != retData.end(); ++regs)
	        {
	            for(iter = regs->begin(); iter != regs->end(); ++iter)
		        {
		            if(field==5) //MATRICULA!
		            {
		                //TODO BOOST TO UPPER, GENERIC TOOLS
		                if(!iter->compare(retArrPlate()))
			                ret=1;
		            }		  
		  
		            field++;
		        }
	            field=0;
	        }
	    }
        if (sql != NULL)
            delete[] sql;
    }
    return ret;
}

int inputForm::setTrfMov(qtDatabase & myDatabase, station *& myStation)
{
  int ret = 0;
  char * sql;
  std::vector<std::vector<std::string>> retData;
  std::vector<std::string>::iterator iter;
  std::vector<std::vector<std::string>>::iterator reg;
  int field = 0;
  
  if(!retArrPlate().empty())
    {
      selAllTransfers(sql, myStation->getCode());
      if(!myDatabase.query(NULL,sql))
	{
	  retData = myDatabase.retData2();
	  if(retData.size())
	    {
	      for(reg = retData.begin(); reg != retData.end(); ++reg)
		{
		  if(reg->size()>=10)
		    {		  
		      for(iter = reg->begin(); iter != reg->end(); ++iter)
			{
			  boost::to_upper(reg->at(5));
			  if(!reg->at(5).compare(retArrPlate())) //PLATE FOUND
			    {
			      setArrMovType(DEF_MOV_TRANSFER);
			      setArrDestStation(myStation);
			      if(field == 0) //DI			   
				setArrDi(*iter);				 
			      else if(field==1) //FECHA_HORA
				{
				  setArrDateTime(mysql2sqliteDate(*iter));
				  //DI FOLDER
				  std::string folder =retArrDi() + " "+ retArrDateTime();
				  setArrDiFolder(folder);
				}
			      else if(field==2)//CODIGO_ORIGEN
				{
				  try
				    {
				      station * tmpStation = new station(std::stol(*iter),myDatabase);
				      setArrOrigStation(tmpStation);
				      delete tmpStation;
				    }
				  catch(...)
				    {
				      std::cout << "**ERROR** error trying to build origin station with code:" << *iter << std::endl;
				    }
				}
			      else if(field==3)//CODIGO PRODUCTO
				{
				  try
				    {
				      std::cout << "SETTING ARRIVE PRODCT CODE: "<< *iter << std::endl;
				      setArrProdCode(std::stol(*iter));
				    }
				  catch(...)
				    {
				      setArrProdCode(0);
				    }		      
				}        
			      else if(field==6) //REMOLQUE
				setArrPlateAtt(*iter);
			      else if(field==7) //INCIDENTS
				{
				  std::vector<std::string> newIncidents = getInputIncidents();
				  setInputIncidents( stringToVector(*iter,";"));
				  inputConcatenate(newIncidents);	    
				}
			      else if(field==8) //COMENTARIO
				setInputComment(*iter);
			      else if(field==9) //D/R
				setArrDestStationDR(*iter);
				 	       
			      field++;			     
			    }
			}
		    }
		}
	    }
	}
      delete sql;
    }

  return ret;

}

//transit movements management
int inputForm::storeTransit(qtDatabase & myDatabase,qtDatabase & remoteDatabase, station * myStation, int remote_host_connected)
{
    int ret = 0;	    

    std::string str_log_message;
    //mysql && sqlite
    std::string my_mysql = "insert into transito (DI,FECHA_HORA,TIPO_MOVIMIENTO,CODIGO_CLIENTE,CODIGO_PRODUCTO,PESO_ENTRADA,PRECIO,MATRICULA,REMOLQUE,CODIGO_ORIGEN,INCIDENCIAS,COMENTARIO_OPERADOR,PESO_SALIDA,CODIGO_ESTACION) values (\"";
    std::string my_sqlite = "insert into transito (DI,FECHA_HORA,TIPO_MOVIMIENTO,CODIGO_CLIENTE,CODIGO_PRODUCTO,PESO_ENTRADA,PRECIO,MATRICULA,REMOLQUE,CODIGO_ORIGEN,INCIDENCIAS,COMENTARIO_OPERADOR,PESO_SALIDA,CODIGO_ESTACION, SINCRONIZADO) values (\"";
  
    std::string query = retArrDi(); //DI 
    query += "\",\"";  
    //  query += getCurrentDate();   BUG esto nos rompe la definción de la carpeta de save de documentos
    query += retArrDateTime();
    query += "\",";
    query += std::to_string(retArrMovType());
    query += ",";
    query += std::to_string(retArrCosCode());
    query += ",";
    query += std::to_string(retArrProdCode());
    query += ",";
    query += std::to_string(retArrScaleIn());  
    query += ",";
    query += std::to_string(retArrPrice());
    query += ",\"";
    query += retArrPlate();
    query += "\",\"";
    query += retArrPlateAtt(); 
    query += "\",";
    query += std::to_string(arrOriginStation->getCode());
    query += ",\"";
    query += vectorToString(getInputIncidents(),"; ");
    query += "\",\"";
    query += getInputComment();
    query += "\",0 ,"; // no Scale out yet 
    query += std::to_string(myStation->getCode());

    my_mysql += query;
    my_mysql += ")";

    my_sqlite += query;

    if(remote_host_connected)
    {
        str_log_message = "(DESCARGA) remote db -> ";
        str_log_message += my_mysql;
        log_message(str_log_message, 1);
        if(!remoteDatabase.query(NULL,my_mysql.c_str()))
	    {
	        log_message("(DESCARGA) registro en BD remota parece OK", 1);
	        my_sqlite += ",1)";
	    }
        else
	    {
	        log_message("(DESCARGA) registro en BD remota parece ERROR", 2);
	        ret = -1;
	        my_sqlite += ",0)";
	    }
        str_log_message = "(DESCARGA) local db -> ";
        str_log_message += my_sqlite;
        log_message(str_log_message, 1);
        if(!myDatabase.query(NULL,my_sqlite.c_str()))
	        log_message("(DESCARGA) registro en BD local parece OK", 1);
        else
	        log_message("(DESCARGA) registro en BD local parece ERROR (NO SE HACE NADA)", 2);
    }
    else
    {
        log_message("(DESCARGA) registro en BD remota parece ERROR", 2);
        ret = -1;
        my_sqlite += ",0)";
        str_log_message = "(DESCARGA) local db -> ";
        str_log_message += my_sqlite;
        log_message(str_log_message, 1);
        if(!myDatabase.query(NULL,my_sqlite.c_str()))
	        log_message("(DESCARGA) registro en BD local parece OK", 1);
        else
	        log_message("(DESCARGA) registro en BD local parece ERROR (NO SE HACE NADA)", 2);
        }
    return ret;
}

int inputForm::isPlateInTransit(std::string plate)
{
  int ret = 0;
  std::vector<std::vector<std::string>>::iterator row;
  int index = 0;
  
  row = vctAllTransit.begin();
   if(!plate.empty() && plate.compare(""))
    {
      while(row != vctAllTransit.end())
	{
	  if(row->size() > 7) //DATABASE DEPENDANT
	    {
	      if(!plate.compare(row->at(7))) //DATABASE DEPENDANT
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

int inputForm::delTransit(int index,std::string plate, qtDatabase & myDatabase, qtDatabase & myRemoteDatabase, std::string host, int port, long station_code)
{
  int ret = 1;
  std::string fecha_hora,di,str_log_message;

  if(index >= 0)
    {
      if(vctAllTransit.size() > index)
	{
	  if(vctAllTransit.at(index).size() >= 13) //transit database dependant
	    {
	      di = vctAllTransit.at(index).at(0); //DI
	      plate = vctAllTransit.at(index).at(7); //PLATE
	      fecha_hora = vctAllTransit.at(index).at(1); //DATE
	    }
	}
    }

  
  std::string sql = "delete from transito where matricula = \"";
  sql += plate;
  sql += "\" and FECHA_HORA=\"";
  sql += fecha_hora;
  sql += "\"";
  std::string mysql = sql + " and codigo_estacion=";
  mysql += std::to_string(station_code);

  str_log_message = "(DESCARGA)(borrando tránsito) db local -> ";
  str_log_message += sql;
  log_message(str_log_message, 1);

  if(!myDatabase.query(NULL,sql.c_str()))
    {
      log_message("(DESCARGA)(borrando tránsito) db local OK", 1);
      ret = 0;
    }
  else
    {
      log_message("(DESCARGA)(borrando tránsito) db local ERROR", 2);
      ret = 1;
    }

  str_log_message = "(DESCARGA)(borrando tránsito) db remota -> ";
  str_log_message += mysql;
  log_message(str_log_message, 1);
  
  if(isConnected(host.c_str(), port))
    {
      if(!myRemoteDatabase.query(NULL,mysql.c_str()))
	log_message("(DESCARGA)(borrando tránsito) db remota OK", 1);
      else
	log_message("(DESCARGA)(borrando tránsito) db remota ERROR (query error)", 2);
    }
  else
    log_message("(DESCARGA)(borrando tránsito) db remota ERROR (connection error)", 2);
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
int inputForm::setTransitMov(int index, std::string byPlate, qtDatabase & myDatabase)
{
    int ret = -1, num_of_row = 0;
    std::vector<std::vector<std::string>>::iterator row;
    row = vctAllTransit.begin();
 
    while(row != vctAllTransit.end())
    {
        if(row->size() > 7) //DATABASE DEPENDANT
	    {
	        if(!byPlate.compare(row->at(7))&& (num_of_row >= index || index == -1) ) //DATABASE DEPENDANT
	        {
	            clearDepMov();
	            setDepDi(row->at(0)); //DI
	            setDepDateTime(row->at(1)); //FECHA_HORA
	            try
		        {
		            setDepMovType(std::stoi(row->at(2))); //TIPO_MOVIMIENTO
		        }
	            catch(...)
		        {
		            setDepMovType(DEF_MOV_ENTRADA);
		        }
                try // COSTUMER
		        {
		            if(depCostumer)
		                delete depCostumer;
		            depCostumer = new costumer(std::stol(row->at(3)),myDatabase);
		        }
	            catch(...)
		        {
		            if(depCostumer)
		                delete depCostumer;
		            depCostumer = new costumer();
		        }
	            try
		        {
		            setDepProdCode(std::stol(row->at(4))); //CODIGO PRODUCTO
		        }
	            catch(...)
		        {
		            setDepProdCode(0);
		        }
	            try
		        {
		            setDepScaleIn(std::stoul(row->at(5))); //PESO_ENTRADA
		        }
	            catch(...)
		        {
		            setDepScaleIn(0); //PESO_ENTRADA
		        }
	            try
		        {
		            setDepPrice(std::stof(row->at(6))); //PRECIO
		        }
	            catch(...)
		        {
		            setDepPrice(0.0);
		        }
	            setDepPlate(row->at(7)); //MATRICULA
	            setDepPlateAtt(row->at(8)); //REMOLQUE
	            try//ORIGEN
		        {
		            if(depOriginStation)
		                delete depOriginStation;
		            depOriginStation = new station(std::stol(row->at(9)),myDatabase);
		        }
	            catch(...)
		        {
		            if(depOriginStation)
		                delete depOriginStation;
		            depOriginStation = new station();
		        }
	            //incidents
	            std::vector<std::string> newIncidents = getOutputIncidents();
	            setOutputIncidents( stringToVector(row->at(10),";"));
	            outputConcatenate(newIncidents);
	            //
	            setOutputComment(row->at(11));  //COMENTARIO OPERADOR
	            try
		        {
		            setDepScaleOut(std::stoul(row->at(12))); //PESO_SALIDA
		        }
	            catch(...)
		        {
		            setDepScaleOut(0);
		        }
	            ret = 0;
	            break;
	        }
	    }
        ++row;
        num_of_row++;
    }
    return ret;
}
//TODO
//costumer functions
/*! this function return a list of possible costumers linked to a plate*/
std::vector<std::string> inputForm::retAllCos4Combo(qtDatabase & myDatabase)
{
  std::string myPlate;
  std::vector<std::string> allCostumers;
  char * sql;

  myPlate = retArrPlate(); 
  if(!myPlate.empty())
    {
      // sel_all_costumers_from_car(sql,myPlate.c_str());
      allCostumers.push_back("empty, TODO!");
      
    }
  return allCostumers;
}
//
void inputForm::forceCurrentProduct()
{
  std::vector<std::string>::iterator iter;
  int alreadyDone = 0;

  for(iter=iIncidents.begin();iter!=iIncidents.end() && !alreadyDone;++iter)
    {
      std::string code = iter->substr(0,5);
      if(!code.compare("00033"))
	alreadyDone=1;       
    }
  if(!alreadyDone)
    iIncidents.push_back("00033: Se ha forzado el permiso de descarga del producto, ya que el cliente no lo tenía permitido para esta estación");
      
  return;
}
void inputForm::unforceCurrentProduct()
{
  std::vector<std::string>::iterator iter;
  
  for(iter=iIncidents.begin();iter!=iIncidents.end();)
    {
      std::string code = iter->substr(0,5);
      if(!code.compare("00033"))
	iter= iIncidents.erase(iter);
      else
	++iter;
    }
  return;
}
int inputForm::getFzCurrentProduct()
{
  std::vector<std::string>::iterator iter;
  int isForced = 0;
  
  for(iter=iIncidents.begin();(iter!=iIncidents.end() && !isForced);)
    {
      std::string code = iter->substr(0,5);
      if(!code.compare("00033"))
	isForced=1;
      else
	++iter;
    }
  
  return isForced;
}
void inputForm::setAllDiData(qtDatabase & localDatabase,station * myStation, long ourCode, long defDriverCode)
{
    //TODO fix error handling
    //product information
    if(retDepProdCode()>0)
    {
        if(setAllProductData(localDatabase))
	    std::cout << "*ERROR*" << std::endl;
    }
    //costumer-product information
    if(depCostumer->getCode() > 0 && retDepProdCode() > 0)
    {
        if(setAllDepCosProdData(localDatabase, myStation))
	        std::cout << "*ERROR*" << std::endl;
    }
    //productor type depending of movement type
    if(depCostumer->getType() <= 0 )
    {
        // TODO movement type?
        switch(retArrMovType())
	    {
	        case(DEF_MOV_ENTRADA):
            {
	            depCostumer->setType(1); // waste producer
	            break;
            }
	        case(DEF_MOV_TRANSFER):
            {
	            depCostumer->setType(2); // waste handling type 2
	            break;
            }
	        case(DEF_MOV_INTERNOD5):
            {
	            depCostumer->setType(3); // waste handling type 3
	            break;
            }
	        default:
	            // do nothing
	            break;
	    }
    }
    //billing method and price
    if(set_all_billing_info(localDatabase))
        std::cout << "*ERROR*" << std::endl;
    //origin information (FILLED IN DI EDITION)
    // default driver loaded
    if (retArrMovType() == DEF_MOV_TRANSFER || retArrMovType() == DEF_MOV_INTERNOD5)
    {
        if (defDriverCode > 0) // if default driver configured
	    {
	        if (depDriver->getCode() <= 0)
	        {
	            setDriverByCode(defDriverCode, localDatabase);
	        }
	    }
    }
    //destination information (our station)
    setDepDestStation(myStation);
    return;
}

/*is DI complete?*/
int inputForm::isDiComplete()
{
    int ret = 1;
    //COMMON ANALYSIS
    //CODIGO_PRODUCTO
    if(myDepMovement.CODIGO_PRODUCTO <= 0)
        ret = 0;
    //CODIGO_TRANSPORTISTA
    if(depDriver->getCode() < 0)
        ret = 0;
    //COSTUMER
    if(!depCostumer->isDefined())
        ret = 0;
    return ret;
}
//////////////////////////////////////////////////////////////////
//PDF generation
//////////////////////////////////////////////////////////////////
/*! function for creating our document with all the stored info 
  about our movement*/
void inputForm::createPdf(std::string printerId)
{
  std::cout << "entrando en el método novedosísimo y patentadísimo de CREATE PDF!! es brooma ;-)" << std::endl;
  
  std::string titulo = "Ticket cliente: ";

  HPDF_Doc  pdf;
  HPDF_Font font;
  HPDF_Page page1,page2;
  HPDF_Image templatePage1,templatePage2;
  char fname[512];
  char signature[512];
  float fsize = 14;

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
  /* set compression mode */
  HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);
  HPDF_UseUTFEncodings(pdf); 

  /* create default-font */
  //font = HPDF_GetFont (pdf, "Helvetica","ISO8859-15");
  font = HPDF_GetFont (pdf, HPDF_LoadTTFontFromFile (pdf, "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf", HPDF_TRUE),"UTF-8");
  /* add pages objects */
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

  /*LER*/
  HPDF_Page_BeginText (page1);
  HPDF_Page_MoveTextPos (page1, 480, 1034);
  myText = std::to_string(retDepProdLER());
  HPDF_Page_ShowText (page1, myText.c_str());
  HPDF_Page_EndText (page1);

  /*PELIGRO*/
  HPDF_Page_BeginText (page1);
  myText = retDepProdPeligro();

  if(myText.empty() || !myText.compare(""))   
    HPDF_Page_MoveTextPos (page1, 672, 1034);    
  else
    HPDF_Page_MoveTextPos (page1, 562, 1034);
  HPDF_Page_ShowText (page1, "X");
  HPDF_Page_EndText (page1);

  /*DI*/
  HPDF_Page_BeginText (page1);
  myText = retDepDi();
  HPDF_Page_MoveTextPos (page1, 558, 1015);
  HPDF_Page_ShowText (page1, myText.c_str());
  HPDF_Page_EndText (page1);

  /*NPT*/
  HPDF_Page_BeginText (page1);
  myText = std::to_string(retDepPermitNPT());
  HPDF_Page_MoveTextPos (page1, 558, 995);
  HPDF_Page_ShowText (page1, myText.c_str());
  HPDF_Page_EndText (page1);

  /*DATE TIME*/
  HPDF_Page_BeginText (page1);
  myText = retDepDateTime();
  HPDF_Page_MoveTextPos (page1, 558, 975);
  HPDF_Page_ShowText (page1, removeTime(myText).c_str());
  HPDF_Page_EndText (page1);

    /*4. COSTUMER DATA*/

    //Posiciones de la X
    HPDF_Page_BeginText (page1);
    myText = "X";

    if(depCostumer->getType() == 2)
    {
        HPDF_Page_MoveTextPos (page1, 290, 913);
    }
    else if(depCostumer->getType() == 3)
    {
        HPDF_Page_MoveTextPos (page1, 509, 925);;
    }	  
    else if(depCostumer->getType() == 4)
    {
        HPDF_Page_MoveTextPos (page1, 183, 880);	
    }	  
    else if(depCostumer->getType() == 5)
    {
        HPDF_Page_MoveTextPos (page1, 290, 880);
    }
    else if(depCostumer->getType() == 6)
    {
        HPDF_Page_MoveTextPos (page1, 509, 880);
    }
    else { // if type 1 or no type present (by default)
        HPDF_Page_MoveTextPos (page1, 183, 925);
    }	 
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1);

    //NAME
    set_di_text(page1, fsize, 47, font, depCostumer->getName(), 188, 841);
    //NIF
    HPDF_Page_BeginText (page1);     
    HPDF_Page_MoveTextPos (page1, 648, 841);
    HPDF_Page_ShowText (page1, depCostumer->getNif().c_str());
    HPDF_Page_EndText (page1);
    //CP
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 816);
    HPDF_Page_ShowText (page1, std::to_string(depCostumer->getZip()).c_str());
    HPDF_Page_EndText (page1);
    //COMUNIDAD AUTONOMA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 792);
    HPDF_Page_ShowText (page1, depCostumer->getRegion().c_str());
    HPDF_Page_EndText (page1);
    //DIRECCION
    set_di_text(page1, fsize, 47, font, depCostumer->getAddress(), 188, 816);
    //MUNICIPIO
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 792);
    HPDF_Page_ShowText (page1, depCostumer->getCity().c_str());
    HPDF_Page_EndText (page1);
    //NIMA
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 764);
    HPDF_Page_ShowText (page1, depCostumer->getNima().c_str());
    HPDF_Page_EndText (page1);
    //TELEFONO
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 737);
    HPDF_Page_ShowText (page1, depCostumer->getPhone().c_str());
    HPDF_Page_EndText (page1);
    //PROVINCIA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 792);
    HPDF_Page_ShowText (page1, depCostumer->getProvence().c_str());
    HPDF_Page_EndText (page1);
    //Nº INSC REGISTRO
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 764);
    HPDF_Page_ShowText (page1, depCostumer->getNumIns().c_str());
    HPDF_Page_EndText (page1);
    //EMAIL
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 737);
    HPDF_Page_ShowText (page1, depCostumer->getMail().c_str());
    HPDF_Page_EndText (page1);

    station * localOrigin;
    // 5.ORIGIN DATA
    if(retDepMovType() == DEF_MOV_TRANSFER || retDepMovType() == DEF_MOV_SALIDA)
    {
        retDepOriginStation(localOrigin);
    }
    else
    {
        // empty
        localOrigin = new station();
    }
    // A) PRODUCT CENTER
    //NAME
    set_di_text(page1, fsize, 47, font, localOrigin->getName(), 188, 638);
    //DIRECCION
    set_di_text(page1, fsize, 47, font, localOrigin->getAddress(), 188, 614);
    //MUNICIPIO
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 589);
    HPDF_Page_ShowText (page1, localOrigin->getCity().c_str());
    HPDF_Page_EndText (page1);
    //NIMA
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 562);
    HPDF_Page_ShowText (page1, localOrigin->getNima().c_str());
    HPDF_Page_EndText (page1);
    //PROVINCIA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 589);
    HPDF_Page_ShowText (page1, localOrigin->getProvence().c_str());
    HPDF_Page_EndText (page1);
    //Nº INSC REGISTRO
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 562);
    HPDF_Page_ShowText (page1, localOrigin->getNumIns().c_str());
    HPDF_Page_EndText (page1);
    //NIF
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 638);
    HPDF_Page_ShowText (page1, localOrigin->getNif().c_str());
    HPDF_Page_EndText (page1);
    // ZIP
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 614);
    HPDF_Page_ShowText (page1, std::to_string(localOrigin->getZip()).c_str());
    HPDF_Page_EndText (page1);
    //COMUNIDAD AUTONOMA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 589);
    HPDF_Page_ShowText (page1, localOrigin->getRegion().c_str());
    HPDF_Page_EndText (page1);
    //CNAE
    HPDF_Page_BeginText (page1);
    myText = "";
    HPDF_Page_MoveTextPos (page1, 648, 562);
    HPDF_Page_ShowText (page1, myText.c_str());
    HPDF_Page_EndText (page1); 
    delete localOrigin;
        
    // B) EMPRESA

    //NAME 
    set_di_text(page1, fsize, 47, font, depCostumer->getName(), 188, 512);     
    //DIRECCION
    set_di_text(page1, fsize, 47, font, depCostumer->getAddress(), 188, 487);     
    //MUNICIPIO
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 462);
    HPDF_Page_ShowText (page1, depCostumer->getCity().c_str());
    HPDF_Page_EndText (page1);
    //NIMA
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 437);
    HPDF_Page_ShowText (page1, depCostumer->getNima().c_str());
    HPDF_Page_EndText (page1);	 
    //TELEFON0
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 411);
    HPDF_Page_ShowText (page1, depCostumer->getPhone().c_str());
    HPDF_Page_EndText (page1);
    //PROVINCIA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 462);
    HPDF_Page_ShowText (page1, depCostumer->getProvence().c_str());
    HPDF_Page_EndText (page1);
    //Nº INSC REGISTRO
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 437);
    HPDF_Page_ShowText (page1, depCostumer->getNumIns().c_str());
    HPDF_Page_EndText (page1);
    //EMAIL
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 411);
    HPDF_Page_ShowText (page1, depCostumer->getMail().c_str());
    HPDF_Page_EndText (page1);
    //NIF
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 512);
    HPDF_Page_ShowText (page1, depCostumer->getNif().c_str());
    HPDF_Page_EndText (page1);	  
    //CP
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 487);
    HPDF_Page_ShowText (page1, std::to_string(depCostumer->getZip()).c_str());
    HPDF_Page_EndText (page1);
    //COMUNIDAD AUTONOMA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 462);
    HPDF_Page_ShowText (page1, depCostumer->getRegion().c_str());
    HPDF_Page_EndText (page1);
	
    //6. DESTINATION INFO
    // A) Center Info
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
 myText = localDestination->getNima();
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
 myText = localDestination->getNumIns();
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

 // B) Costumer (our costumer in this case)
 costumer * our_costumer;
 retOurId(our_costumer);
 //NAME
 myText = our_costumer->getName();
 set_di_text(page1,fsize,47,font,myText,188,187);
 
 //DIRECCION
 myText = our_costumer->getAddress();
 set_di_text(page1,fsize,47,font,myText,188,162);

 //MUNICIPIO
 //TODO: to adjust with new set_di_text function
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getCity();
 HPDF_Page_MoveTextPos (page1, 188, 137);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //NIMA
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getNima();
 HPDF_Page_MoveTextPos (page1, 188, 112);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //TELEFONO
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getPhone();
 HPDF_Page_MoveTextPos (page1, 188, 86);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //PROVINCIA
 //TODO: to adjust with new set_di_text function
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getProvence();
 HPDF_Page_MoveTextPos (page1, 465, 137);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //Nº INSC REGISTRO
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getNumIns();
 HPDF_Page_MoveTextPos (page1, 465, 112);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //EMAIL
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getMail();
 HPDF_Page_MoveTextPos (page1, 465, 86);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //NIF
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getNif();
 HPDF_Page_MoveTextPos (page1, 648, 187);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);
  
 //CP
 HPDF_Page_BeginText (page1);
 myText = std::to_string(our_costumer->getZip());
 HPDF_Page_MoveTextPos (page1, 648, 162);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 //COMUNIDAD AUTONOMA
 //TODO: to adjust with new set_di_text function
 HPDF_Page_BeginText (page1);
 myText = our_costumer->getRegion();
 HPDF_Page_MoveTextPos (page1, 648, 137);
 HPDF_Page_ShowText (page1, myText.c_str());
 HPDF_Page_EndText (page1);

 delete our_costumer;

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
 myText = std::to_string(retNetWeight());
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
    set_di_text(page2, fsize, 47, font, depDriver->getName(), 188, 980);
    //DIRECCION
    set_di_text(page2, fsize, 47, font, depDriver->getAddress(), 188, 955);
 
    //MUNICIPIO
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page2);    
    HPDF_Page_MoveTextPos (page2, 188, 930);
    HPDF_Page_ShowText (page2, depDriver->getCity().c_str());
    HPDF_Page_EndText (page2);

    //NIMA
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 188, 904);
    HPDF_Page_ShowText (page2, depDriver->getNima().c_str());
    HPDF_Page_EndText (page2);

    //TELEFONO
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 188, 877);
    HPDF_Page_ShowText (page2, depDriver->getPhone().c_str());
    HPDF_Page_EndText (page2);

    //PROVINCIA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 465, 930);
    HPDF_Page_ShowText (page2, depDriver->getProvence().c_str());
    HPDF_Page_EndText (page2);

    //Nº INSC REGISTRO
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 465, 904);
    HPDF_Page_ShowText (page2, depDriver->getNumIns().c_str());
    HPDF_Page_EndText (page2);

    //EMAIL
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 465, 877);
    HPDF_Page_ShowText (page2, depDriver->getMail().c_str());
    HPDF_Page_EndText (page2);

    //NIF
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 648, 980);
    HPDF_Page_ShowText (page2, depDriver->getNif().c_str());
    HPDF_Page_EndText (page2);
  
    //CP
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 648, 955);
    HPDF_Page_ShowText (page2, std::to_string(depDriver->getZip()).c_str());
    HPDF_Page_EndText (page2);

    //COMUNIDAD AUTONOMA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page2);
    HPDF_Page_MoveTextPos (page2, 648, 930);
    HPDF_Page_ShowText (page2, depDriver->getRegion().c_str());
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
  myText = "";
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
  myText = "";
  HPDF_Page_MoveTextPos (page2, 468, 763);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

  // 10.Otras informaciones

  //POSICION DE LA X EN SI O NO

  //SI
  HPDF_Page_BeginText (page2);
  myText = "X";
  HPDF_Page_MoveTextPos (page2, 220, 664);
  HPDF_Page_ShowText (page2, myText.c_str());
  HPDF_Page_EndText (page2);

 //NO
 HPDF_Page_BeginText (page2);
 myText = "";
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
 myText = removeTime(retDepDateTime());
 HPDF_Page_MoveTextPos (page2, 395, 665);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //CANTIDADACEPTADA
 HPDF_Page_BeginText (page2);
 myText = std::to_string(retNetWeight());
 HPDF_Page_MoveTextPos (page2, 650, 665);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //FECHARECHAZO
 HPDF_Page_BeginText (page2);
 myText = "";
 HPDF_Page_MoveTextPos (page2, 395, 640);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //CANTIDADRECHAZADA
 HPDF_Page_BeginText (page2);
 myText = "";
 HPDF_Page_MoveTextPos (page2, 650, 640);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //FECHANEWTR
 HPDF_Page_BeginText (page2);
 myText = "";
 HPDF_Page_MoveTextPos (page2, 650, 614);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //SRAP
 HPDF_Page_BeginText (page2);
 myText = "";
 HPDF_Page_MoveTextPos (page2, 650, 583);
 HPDF_Page_ShowText (page2, myText.c_str());
 HPDF_Page_EndText (page2);

 //11 Final and extra info

  // Signature
  strcpy (signature,  retDepDiFolder().c_str());
  strcat (signature, "/firma.png");
  draw_image (pdf, signature, 100, HPDF_Page_GetHeight (page2) - 900,"Firma transportista",0);

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
 /*! BUG, its the opposite ScaleOut vs ScaleIn, dirty quick fix*/
 ///tara
 myText = std::to_string(retTareWeight());
 myText += " Kg";
 HPDF_Page_MoveTextPos (page2, 412, 360);
 HPDF_Page_ShowText (page2, myText.c_str());
 ///bruto
 myText = std::to_string(retGrossWeight());
 myText += " Kg";
 HPDF_Page_MoveTextPos (page2, 139, 0); 
 HPDF_Page_ShowText (page2, myText.c_str());
 ///neto
 myText = std::to_string(retNetWeight());
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

     double total_price = retNetWeight()*retDepPrice() / 1000.0;
     std::stringstream stream;
     stream << std::fixed << std::setprecision(2) << total_price;
     std::string precio_final = stream.str();
 
     precio_final += " Euros";
 
     HPDF_Page_MoveTextPos(page2, 20, -45);
     HPDF_Page_ShowText(page2, precio_final.c_str());   
     HPDF_Page_EndText (page2);
   }
 //END PRICE BLOCK

 /* save the document to a file */
 std::cout << "INFO: saving to file: " << fname << std::endl;
 HPDF_SaveToFile (pdf, fname);
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
 //std::cout << "FIN CREATE PDF!!" << std::endl;
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
int inputForm::createTicket(std::string printerId, std::string ticketCode)
{
    printable * myTicket = NULL;
    std::string fileName = "ticket.pdf";
    myTicket = new printableTicket(fileName, printerId);
    myTicket->setTicketType("REGISTRO DE ENTRADA");
    myTicket->setTicketCode(ticketCode);
    costumer * ourCostumer = NULL;
    retOurId(ourCostumer);
    myTicket->setOurCIF(ourCostumer->getNif());
    if (ourCostumer != NULL)
        delete ourCostumer;
    station * localDestination = NULL;
    retDepDestinationStation(localDestination);
    myTicket->setStationName(localDestination->getName());
    myTicket->setStationNIMA(localDestination->getNima());
    if (localDestination != NULL)
        delete localDestination;
    myTicket->setMovCode(retDepMovCode());
    myTicket->setMovDate(retDepFinalDateTime().substr(0, retDepFinalDateTime().find(' ')));
    myTicket->setMovTime(retDepFinalDateTime().substr(retDepFinalDateTime().find(' '), retDepFinalDateTime().length()));
    myTicket->setCostumerName(depCostumer->getName());
    myTicket->setCostumerNif(depCostumer->getNif());
    myTicket->setTransportName(depDriver->getName());
    myTicket->setTransportPlate(retDepPlate());
    myTicket->setProductName(retDepProdFullName());
    myTicket->setProductLER(std::to_string(retDepProdLER()));
    myTicket->setGrossWeight(std::to_string(retGrossWeight()));
    myTicket->setTareWeight(std::to_string(retTareWeight()));
    myTicket->setNetWeight(std::to_string(retNetWeight()));
    myTicket->setPayProcedure(retDepPayProcedure());
    double total_price = (retNetWeight()*retDepPrice()) / 1000.0;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << total_price;
    myTicket->setFinalPrice(stream.str());
    myTicket->setComment(getOutputComment());
    myTicket->setStaffCode(std::to_string(ret_staff_code()));
    std::string signaturePath = retDepDiFolder() + "/firma.png";
    myTicket->setSignaturePath(signaturePath);
    myTicket->composeFile();
    int ret = myTicket->saveFile();
    ret += myTicket->printFile();
    if (myTicket != NULL)
        delete myTicket;
    return ret;
}