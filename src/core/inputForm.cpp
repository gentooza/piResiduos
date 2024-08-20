/*
This file is part of PiResiduos.

Copyright 2017-2019, Pro Integra SL.
Copyright 2019-2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023,2024 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

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
    std::string myMoveCode = storeMov(sqliteQuery,mysqlQuery,depDestinationStation,localDatabase);

    if(remote_host_connected) //SAVING MOVEMENT IN REMOTE SERVER
    {
        str_log_message = "(DESCARGA) en BD remota -> ";
        str_log_message += mysqlQuery;
        log_message(str_log_message, 1);
        if(!remoteDatabase.query(NULL, mysqlQuery.c_str())) //SYNCRONIZED
        {
            log_message("(DESCARGA) registro en BD remota parece OK ",1);
            int sync = 0;
            selLastMovCode(mysqlQuery, std::to_string(depDestinationStation->getCode()));
            str_log_message = "(DESCARGA) chequeo redundante en BD remota -> ";
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

    std::string query = createDINumber(myDatabase, 1); //DI
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
                    setDepMovType(DEF_MOV_UNLOADING);
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
/*! DI number in all unloading movements are the movement number */
std::string inputForm::createDINumber(qtDatabase & localDatabase, int arrive)
{
    station *myStation = NULL;
    if(arrive)
        retArrDestinationStation(myStation);
    else
        retDepDestinationStation(myStation);
    if(myStation->getCode() <= 0)
    {
        if (myStation)
            delete myStation;
        retOurStation(myStation);
    }
    int movType = DEF_MOV_UNLOADING;
    if(arrive)
        movType = retArrMovType();
    else
        movType = retDepMovType();

    if(movType <= 0)
        movType = DEF_MOV_UNLOADING;
    std::string DI = "";
    if(movType != DEF_MOV_TRANSFER)
        DI = getMovCode(localDatabase, myStation, movType);
    else
    {
        if(arrive)
            DI = retArrDi();
        else
            DI = retDepDi();
    }
    std::string folder;
    if(arrive)
    {
        if(retArrDateTime().empty())
            setArrDateTime(getCurrentDate());

        folder = DI + " " + retArrDateTime();
        setArrDiFolder(folder);
    }
    else
    {
        if(retDepDateTime().empty())
            setDepDateTime(getCurrentDate());

        folder = DI + " " + retDepDateTime();
        setDepDiFolder(folder);
    }
    return DI;
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
            case(DEF_MOV_UNLOADING):
            {
                depCostumer->setType(1); // waste producer
                break;
            }
            case(DEF_MOV_TRANSFER):
            {
                depCostumer->setType(2); // waste handling type 2
                break;
            }
            case(DEF_MOV_TODEPOSITD5):
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
    if (retArrMovType() == DEF_MOV_TRANSFER || retArrMovType() == DEF_MOV_TODEPOSITD5)
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
//TICKET generation
//////////////////////////////////////////////////////////////////
/*! function for creating our ticket document with all the stored info
  about our movement*/
int inputForm::createTicket(std::string printerId, std::string ticketCode, qtDatabase & localDatabase)
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
    std::string movCode;
    if(retDepMovType() == DEF_MOV_TRANSFER)
        movCode = retDepDi();
    else
        movCode = getMovCode(localDatabase, localDestination, retDepMovType());
    myTicket->setMovCode(movCode);
    if (localDestination != NULL)
        delete localDestination;
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