/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2022 Pixelada S. Coop. And. <info (at) pixelada (dot) org>

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

#ifndef _MASK_TOOLS_
#define _MASK_TOOLS_
#include "generic_tools.h"


static void setTime(PARAM *p, DATA* d,int TIMELABEL)
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%I:%M",timeinfo);
  pvSetText(p,TIMELABEL,buffer);

  return;
}
static void setDate(PARAM *p, DATA* d,int DATELABEL)
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d/%m/%Y",timeinfo);
  pvSetText(p,DATELABEL,buffer);

  return;
}

static int useCamera(PARAM *p, DATA* d, int location, std::string & plate, int cameraFrame)
{
  int ret = -1;
  char error[128];
  int port;
  if((location <= cameras.size()) && (location > 0))
    {
      if(isConnected(cameras.at(location-1).ip.c_str(),cameras.at(location-1).port))
	{
	  camera* cameraInstance = new camera(cameras.at(location-1).ip,cameras.at(location-1).port);
	  try
	    {
	      std::cout << "(INFO) usando camera, ip:" << cameras.at(location-1).ip << " with port:" << cameras.at(location-1).port << std::endl;
	      cameraInstance->setRefTime(cameras.at(location-1).timeout);
	      ret = cameraInstance->connect();
	      std::cout << "(AVISO) Conexión a cámara retorna " << ret << std::endl;	  
	      if(ret > 0)
		{
		  //proceso de matrícula
		  if(!cameraInstance->askForPlate(plate))
		    {
		      sprintf(error,"(INFO) matrícula retornada: %s de la cámara %d",plate.c_str(),location);
		      console.push_back(error);
		      std::string imageStr;
		      std::string path = "camera/capture";
		      path += std::to_string(location);
		      path += ".jpg";
		      cameraInstance->takeImage(imageStr,path.c_str());
		      pvDownloadFile(p,path.c_str());
		      pvSetImage(p,cameraFrame,path.c_str());
		      ret = 0;			
		    }
		  else
		    {
		      ret = -1;
		      sprintf(error,"*ERROR* tiempo de espera agotado, recibiendo matrícula de la cámara %d",location);
		      console.push_back(error);
		      plate = "";
		    }
		  cameraInstance->disconnect();
		}
	      else
		{
		  console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
		}
	    }
	  catch(...)
	    {
	      console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
	    }	  
	  delete cameraInstance;
	}
	else
	  console.push_back("*ERROR* ¡Imposible conectar con la cámara!");
    }
  else
    {
      sprintf(error,"*ERROR* mala localización de la cámara o mala configuración en el .ini, localización:%d,cámaras en .ini:%zu", location, cameras.size());
      console.push_back(error);
    }
    
  return ret;
}

//////////
//////////
//DATABASES syncronization
static void syncReconnectIfNeeded()
{
  //bug in qt isOpen! https://bugreports.qt.io/browse/QTBUG-223
  //if(!remoteDatabase.isOpen())
  remoteDatabase.reOpen();
  return;
}
static int syncCostumers(PARAM *p)
{
  int ret = 0;
  std::string str_log_message;
  char * sql;
  str_log_message = "(SINCRO) syncing costumers table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> dataReturn;
      //clientes
      rmt_sel_all_costumers(sql);
      str_log_message = "(SINCRO) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  log_message("(SINCRO) BD local -> delete from clientes", 1);
	  if(localDatabase.query(p,"delete from clientes"))
	    log_message("(SINCRO) Error BD local", 2);
	  dataReturn = remoteDatabase.retData2();
	  std::string str_sql = sqlLoadCostumers(dataReturn);
	  str_log_message = "(SINCRO) BD local -> ";
	  str_log_message += str_sql;
	  log_message(str_log_message, 1);
	  if(localDatabase.query(p,str_sql.c_str()))
	    log_message("(SINCRO) Error BD local", 2);
	}
      else
	{
	  log_message("(SINCRO)(tb clientes) Error BD remota (query)", 2);
	  ret = -2;
	}
      delete sql;
    }
  else
    {
      log_message("(SINCRO)(tb clientes) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int syncProducts(PARAM *p)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing products table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> dataReturn;
      char* sql;
      //productos
      remote_selectAllProducts(sql);
      str_log_message = "(SINCRO) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  delete sql;
	  log_message("(SINCRO) BD local -> delete from productos", 1);
	  if(localDatabase.query(p,"delete from productos"))
	    log_message("(SINCRO) Error BD local", 2);
	  dataReturn = remoteDatabase.retData2();
	  sqlLoadProducts(sql,dataReturn);
	  str_log_message = "(SINCRO) BD local -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  if(localDatabase.query(p,sql))
	    log_message("(SINCRO) Error BD local", 2);   
	}
      else
	{
	  log_message("(SINCRO)(productos) Error BD remota (query)", 2);
	  ret = -2;
	}
      delete sql;
    }
  else
    {
      log_message("(SINCRO)(productos) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int syncCostumersProducts(PARAM *p)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing costumers-products table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> dataReturn;
      char* sql;
      //clientes-productos
      rmt_sel_all_cos_prod(sql);
      str_log_message = "(SINCRO) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  delete sql;
	  log_message("(SINCRO) BD local -> delete from clientes_productos", 1);
	  if(localDatabase.query(p,"delete from clientes_productos"))
	    log_message("(SINCRO) Error BD local", 2);
	  dataReturn = remoteDatabase.retData2();
	  load_cos_prod(sql,dataReturn);
	  str_log_message = "(SINCRO) BD local -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  if(localDatabase.query(p,sql))
	    log_message("(SINCRO) Error BD local", 2);
	}
      else
	{
	  log_message("(SINCRO)(clientes-productos) Error BD remota (query)", 2);
	  ret = -2;
	}
      delete sql;
    }
  else
    {
      log_message("(SINCRO)(clientes-productos) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int syncBilling(PARAM *p)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing billing entities table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> dataReturn;
      char* sql;
      //entidades de facturación
      rmt_sel_all_billing(sql);
      str_log_message = "(SINCRO) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  delete sql;
	  log_message("(SINCRO) BD local -> delete from entidades_facturacion", 1);
	  if(localDatabase.query(p,"delete from entidades_facturacion"))
	    log_message("(SINCRO) Error BD local", 2);
	  dataReturn = remoteDatabase.retData2();
	  load_billing(sql,dataReturn);
	  str_log_message = "(SINCRO) BD local -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  if(localDatabase.query(p,sql))
	    log_message("(SINCRO) Error BD local", 2);
	}
      else
	{
	  ret = -2;
	  log_message("(SINCRO)(entidades facturación) Error BD remota (query)", 2);
	}
      delete sql;
    }
  else
    {
      log_message("(SINCRO)(entidades facturación) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int syncCars(PARAM *p)
{
  int ret=0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing trucks table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> dataReturn;
      char* sql;
      //vehiculos
      rmt_sel_all_cars(sql);
      str_log_message = "(SINCRO) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  delete sql;
	  log_message("(SINCRO) BD local -> delete from vehiculos", 1);
	  if(localDatabase.query(p,"delete from vehiculos"))
	    log_message("(SINCRO) Error BD local", 2);
	  dataReturn = remoteDatabase.retData2();
	  load_cars(sql,dataReturn);
	  str_log_message = "(SINCRO) BD local -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  if(localDatabase.query(p,sql))
	    log_message("(SINCRO)(vehículos) Error BD local", 2);
	}
      else
	{
	  log_message("(SINCRO)(vehículos) Error BD remota (query)", 2);
	  ret = -2;
	}
      delete sql;
    }
  else
    {
      log_message("(SINCRO) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int syncTransfers(PARAM *p, long codigo_estacion)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing transfers table... ";
  if(remoteDatabase.isOpen())
    {
      //1 - choosing all unsyncronized local transfers
      std::vector <std::vector <std::string>> dataReturn;
      char* sql;
      sel_all_unsyncro_transfers(sql);
      str_log_message = "(SINCRO) BD local -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!localDatabase.query(p,sql))
	{
	  dataReturn = localDatabase.retData2();
	  if(dataReturn.size()) //if there is local movements to sync
	    {
	      delete sql;
	      //1b - udpdating remote movements table
	      rmt_updt_transfers(sql,dataReturn);
	      str_log_message = "(SINCRO)(transferencias) BD remota -> ";
	      str_log_message += sql;
	      log_message(str_log_message, 1);
	      if(remoteDatabase.query(p,sql))
		{
		  log_message("(SINCRO)(transferencias) Error BD remota (query)", 2);
		  ret=-2;
		}
	    }
	  if(!ret) //if sincronizing remote movements with local's success, EVEN with no data
	    {
	      //1c - set local movements as syncronized (NOT NEED, WE ARE GONNA CLEAN THEM ALL)
	      //delete sql;
	      //upd_all_unsyncro_transfers(sql);
	      //localDatabase.query(p,sql);

	      //2 updating local transfers with possible new remote ones
	      delete sql;
	      rmt_sel_all_transfers(sql,codigo_estacion);
	      str_log_message = "(SINCRO)(transferencias) BD remota -> ";
	      str_log_message += sql;
	      log_message(str_log_message, 1);
	      if(remoteDatabase.query(p,sql))
		log_message("(SINCRO)(transferencias) Error BD remota (query)", 2);
	      else
		{
		  dataReturn = remoteDatabase.retData2();
		  log_message("(SINCRO)(transferencias) BD local -> delete from transferencias", 1);
		  if(localDatabase.query(p,"delete from transferencias"))
		    log_message("(SINCRO)(transferencias) Error BD local", 2);
		  delete sql;
		  sqlLoadTransfers(sql,dataReturn);
		  str_log_message = "(SINCRO)(transferencias) BD local -> ";
		  str_log_message += sql;
		  log_message(str_log_message, 1);
		  if(localDatabase.query(p,sql))
		    log_message("(SINCRO)(transferencias) Error BD local", 2);
		}
	       
	    }    
	  delete sql;
	  
	}
      else //no unsyncro data
	{
	  log_message("(SINCRO)(transferencias) Error BD local", 2);
	  ret = -2;
	  delete sql;
	}
    }
  else
    {
      log_message("(SINCRO)(transferencias) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  
  return ret;
}

static int syncOrders(PARAM *p)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing orders table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> dataReturn;
      char * sql;
      std::string str_codigo_estacion = std::to_string(myStation->getCode());
      remote_selectAllOrders(sql,str_codigo_estacion.c_str());
      str_log_message = "(SINCRO) remote BD -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  localDatabase.query(p,"delete from ordenes");
	  log_message("(SINCRO) local BD -> delete from ordenes", 1);
	  dataReturn = remoteDatabase.retData2();
	  if(dataReturn.size())
	   {
	     delete sql;
	     sqlLoadOrders(sql,dataReturn);
	     str_log_message = "(SINCRO) local BD  -> ";
	     str_log_message += sql;
	     log_message(str_log_message, 1);
	     if(localDatabase.query(p,sql))
	       ret = -1;
	    }
	  else
	    {
	      log_message("(SINCRO)(orders) NO ORDERS TO SYNC!", 2);
	    }
	}
      else
	{
	  log_message("(SINCRO)(orders) Error remote BD (query?)", 2);
	  ret = -2;
	}
      delete sql;
    }
  else
    {
      log_message("(SINCRO)(orders) Error remote DB(connection?)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int syncDrivers(PARAM *p)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing drivers table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> dataReturn;
      //clientes
      char* sql;
      remote_selectAllDrivers(sql);
      str_log_message = "(SINCRO) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  delete sql;
	  localDatabase.query(p,"delete from transportistas");
	  log_message("(SINCRO) BD local -> delete from transportistas", 1);
	  dataReturn = remoteDatabase.retData2();
	  sqlLoadDrivers(sql,dataReturn);
	  str_log_message = "(SINCRO) BD local -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  localDatabase.query(p,sql);
	}
      else
	{
	  log_message("(SINCRO)(conductoras) Error BD remota (query)", 2);
	  ret = -2;
	}
    }
  else
    {
      log_message("(SINCRO)(conductoras) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int sync_staff(PARAM *p)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing staff table... ";
  if(remoteDatabase.isOpen())
    {
      std::vector <std::vector <std::string>> data_return;
      //clientes
      char* sql;
      rmt_sel_all_staff(sql);
      str_log_message = "(SINCRO)(basculistas) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  delete sql;
	  localDatabase.query(p,"delete from BASCULISTAS");
	  log_message("(SINCRO)(basculistas) BD local -> delete from BASCULISTAS", 1);
	  data_return = remoteDatabase.retData2();
	  load_staff(sql,data_return);
	  str_log_message = "(SINCRO)(basculistas) BD local -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  localDatabase.query(p,sql);
	}
      else
	{
	  log_message("(SINCRO)(basculistas) Error BD remota (query)", 2);
	  ret = -2;
	}
    }
  else
    {
      log_message("(SINCRO)(basculistas) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}

static int syncMovements(PARAM *p,long codigo_estacion)
{
  int ret = 0;
  std::string str_log_message;
  str_log_message = "(SINCRO) syncing movements table... ";
  if(remoteDatabase.isOpen())
    {
      //1 - choosing all unsyncronized local movements
      std::vector <std::vector <std::string>> dataReturn;
      char* sql;
      sel_all_unsyncro_movements(sql);
      str_log_message = "(SINCRO) BD local -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!localDatabase.query(p,sql))
	{
	  dataReturn = localDatabase.retData2();
	  if(dataReturn.size()) //if there is local movements to sync
	    {
	      delete sql;
	      //1b - udpdating remote movements table
	      rmt_updtMovements(sql,dataReturn);
	      str_log_message = "(SINCRO) BD remota -> ";
	      str_log_message += sql;
	      log_message(str_log_message, 1);
	      if(remoteDatabase.query(p,sql))
		{
		  log_message("(SINCRO)(movimientos) Error BD remota (query)", 2);
		  ret=-2;
		}
	      else //if sincronizing remote movements with local's success
		{
		  //uploading files!
		  upload_movement_files_from_sql(dataReturn,0);
		  //1c - set local movements as syncronized
		  delete sql;
		  upd_all_unsyncro_movements(sql);
		  str_log_message = "(SINCRO) BD local -> ";
		  str_log_message += sql;
		  log_message(str_log_message, 1);
		  localDatabase.query(p,sql);
		}
	    }
	  delete sql;
	  
	}
      else
	{
	  log_message("(SINCRO)(movimientos) Error BD remota (query)", 2);
	  ret = -2;
	  delete sql;
	}
      //2 - only selecting last movement in station, in remote database
      time_t t = time(NULL);
      tm* timePtr = localtime(&t);
      int year =  timePtr->tm_year+1900;
      
      rmt_sel_last_movement(sql,codigo_estacion,year);
      str_log_message = "(SINCRO) BD remota -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!remoteDatabase.query(p,sql))
	{
	  dataReturn = remoteDatabase.retData2();
	  if(dataReturn.size()) //if there is remote movements to sync
	    {
	      delete sql;
	      //2b update in local database
	      upd_syncro_movements(sql,dataReturn);
	      str_log_message = "(SINCRO) BD local -> ";
	      str_log_message += sql;
	      log_message(str_log_message, 1);
	      if(localDatabase.query(p,sql))
		ret=-3;
	    }
	  delete sql;
	}
      else
	{
	  log_message("(SINCRO)(movimientos) Error BD remota (query)", 2);	  
	  ret = -3;
	  delete sql;
	}
    }
  else
    {
      log_message("(SINCRO)(movimientos) Error BD remota (conexión)", 2);
      std::cout << "DATABASE not opened!" << std::endl;
      ret = -1;
    }
  return ret;
}
static int syncTransit(PARAM *p, int codigo_estacion)
{
  int ret = 0;
  char* sql;
  std::string str_log_message;
  std::vector< std::vector< std::string>> all_transit_data;
  str_log_message = "(SINCRO) syncing transit table... ";
  //local transit priority over remote!!
  sel_all_transito(sql);
  str_log_message = "(SINCRO)(transito) BD local -> ";
  str_log_message += sql;
  log_message(str_log_message, 1);
  if(!localDatabase.query(p,sql))
    {
      log_message("(SINCRO) BD local OK", 1);
      all_transit_data = localDatabase.retData2();
      if(remoteDatabase.isOpen())
	{
	  delete sql;
	  rmt_del_transito(sql, codigo_estacion);
	  str_log_message = "(SINCRO)(transito) BD remota -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  if(!remoteDatabase.query(p,sql))
	    {
	      log_message("(SINCRO) BD remota OK", 1);
	      delete sql;
	      rmt_updtTransito(sql, all_transit_data, codigo_estacion);
	      str_log_message = "(SINCRO)(transito) BD remota -> ";
	      str_log_message += sql;
	      log_message(str_log_message, 1);
	      if(!remoteDatabase.query(p,sql))
		{
		  log_message("(SINCRO) BD remota OK", 1);
		}
	      else
		{
		  ret = -1;
		  log_message("(SINCRO)(tránsito) BD remota ERROR(query)", 2);
		}

	    }
	  else
	    {
	      ret = -1;
	      log_message("(SINCRO)(tránsito) BD remota ERROR(query)", 2);
	    }
	}
      else
	{
	  ret = -1;
	  log_message("(SINCRO)(tránsito) BD remota ERROR(conexión)", 2);
	}
    }
  else
    {
      ret = -1;
      log_message("(SINCRO) BD local ERROR(query)", 2);
    }

  delete sql;
  return ret;    
}

/*!
1- select all local transit
2- write it to remote
3- select all from remote
4- write it to local
*/
static int syncTransitDep(PARAM *p, int codigo_estacion)
{ 
  int ret = 0;
  char* sql;
  std::string str_log_message;
  std::vector< std::vector< std::string>> all_transit_data;
  str_log_message = "(SINCRO) syncing transit-departures table... ";
  //local transit priority over remote!!
  sel_all_transito_dep(sql);
  str_log_message = "(SINCRO)(transito_salidas) BD local -> ";
  str_log_message += sql;
  log_message(str_log_message, 1);
  if(!localDatabase.query(p,sql))
    {
      log_message("(SINCRO) BD local OK", 1);
      all_transit_data = localDatabase.retData2();
      if(remoteDatabase.isOpen())
	{
	  delete sql;
	  rmt_del_transito_dep(sql, codigo_estacion);
	  str_log_message = "(SINCRO)(transito_salidas) BD remota -> ";
	  str_log_message += sql;
	  log_message(str_log_message, 1);
	  if(!remoteDatabase.query(p,sql))
	    {
	      log_message("(SINCRO) BD remota OK", 1);
	      delete sql;
	      rmt_updtTransitoSalidas(sql, all_transit_data, codigo_estacion);
	      str_log_message = "(SINCRO)(transito_salidas) BD remota -> ";
	      str_log_message += sql;
	      log_message(str_log_message, 1);
	      if(!remoteDatabase.query(p,sql))
		{
		  log_message("(SINCRO) BD remota OK", 1);
		}
	      else
		{
		  ret = -1;
		  log_message("(SINCRO)(transito_salidas) BD remota ERROR(query)", 2);
		}

	    }
	  else
	    {
	      ret = -1;
	      log_message("(SINCRO)(transito_salidas) BD remota ERROR(query)", 2);
	    }
	}
      else
	{
	  ret = -1;
	  log_message("(SINCRO)(transito_salidas) BD remota ERROR(conexión)", 2);
	}
    }
  else
    {
      ret = -1;
      log_message("(SINCRO) BD local ERROR(query)", 2);
    }

  delete sql;
  return ret;  
}

/*!function for syncing stations from central Database*/
static int syncStations(PARAM *p)
{
	int ret = 0;
	char* sql = NULL;
  	std::string str_log_message;
  	str_log_message = "(SINCRO) syncing stations table... ";
  	if(remoteDatabase.isOpen())
	{
    	std::vector <std::vector <std::string>> dataReturn;
    	//stations
    	rmt_selAllStations(sql);
    	str_log_message = "(SINCRO) BD remota -> ";
    	str_log_message += sql;
    	log_message(str_log_message, 1);
    	if(!remoteDatabase.query(p,sql))
		{
	  		delete[] sql;
	  		localDatabase.query(p,"delete from centros");
	  		log_message("(SINCRO) BD local -> delete from centros", 1);
	  		dataReturn = remoteDatabase.retData2();
	  		sqlLoadStations(sql,dataReturn);
	  		str_log_message = "(SINCRO) BD local -> ";
	  		str_log_message += sql;
	  		log_message(str_log_message, 1);
	  		localDatabase.query(p,sql);
			delete[] sql;
		}
      	else
		{
	  		log_message("(SINCRO)(centros) Error BD remota (query)", 2);
	  		ret = -2;
		}
    }
  	else
    {
    	log_message("(SINCRO)(centros) Error BD remota (conexión)", 2);
      	ret = -1;
    }
  	return ret;
}


/*! function for automatic formatting title based in our station data*/
static std::string getTitle()
{
  std::string type;
  std::string title;

  myStation->getType(type);
  title = type + ": " + myStation->getName();

  return title;
}

/*! Function for reopening the ssh tunnel*/
static int reconnectSSH(SYNC_DATA* syncData)
{
  int ret = 0;
  std::string str_log_message;
  if(syncData)
    {
      syncData->end = std::chrono::steady_clock::now();
      ret = -10;
      if(std::chrono::duration_cast<std::chrono::seconds>(syncData->end - syncData->begin).count() >= syncData->seconds)
	{
	  ret = system("sh extras/scripts/relaunch-ssh.sh");
	  syncData->begin = syncData->end;
	  str_log_message = "(SYSTEM) re-executing SSH: \"sh extras/scripts/relaunch-ssh.sh\" ret:" + std::to_string(ret);
	  log_message(str_log_message, 1);
	  syncReconnectIfNeeded();
	  ret = 1;
	}
    }
  else
    {
      ret = system("sh extras/scripts/relaunch-ssh.sh");
      ret = 1;
    }
  return ret;
}

/*! Function for checking if a new syncro is needed*/
static int syncro_needed(SYNC_DATA* syncData)
{
  int ret = 0;
  std::string str_log_message;
  if(syncData)
    {
      if(syncData->minutes >0)
	{
	  syncData->end = std::chrono::steady_clock::now();
	  if(std::chrono::duration_cast<std::chrono::minutes>(syncData->end - syncData->begin).count() >= syncData->minutes)
	    {	  
	      str_log_message = "(SYNCRO) New syncronization is needed";
	      log_message(str_log_message, 1);
	      ret = 1;
	    }
	}
    }
  return ret;
}

/*! Function for setting a new syncro as done*/
static int syncro_done(SYNC_DATA* syncData)
{
  int ret = 0;
  std::string str_log_message;
  if(syncData)
    {
      syncData->begin = syncData->end;
      ret = 1;
    }
  return ret;
}

/*! Function for turning on or off or check green ligth
on = 1
off = 0
check = else
*/
static void cameraSemaphore(int location, int on_off_check, int traffic_lights_enabled)
{
  	int ret = -1;
  	char error[128];
  	int port;
	std::string str_log_message = "(CAMERA'S TRAFFIC LIGHTS)(INFO) starting... location: " + std::to_string(location) + ", action: " + std::to_string(on_off_check) + " , are cameras enabled?: " + std::to_string(traffic_lights_enabled);
	// log_message(str_log_message, 1);
  	if(traffic_lights_enabled)
    {
      	if((location <= cameras.size()) && (location > 0))
		{
      	  
	  		switch(on_off_check)
	    	{
	    		case(0): //switching off
	      			if(cameras.at(location-1).statusB)
					{
		  				if(isConnected(cameras.at(location-1).ip.c_str(),cameras.at(location-1).port))
		    			{
							camera* cameraInstance = new camera(cameras.at(location-1).ip,cameras.at(location-1).port);	 
							try
							{
								std::cout << "(INFO) usando camera, ip:" << cameras.at(location-1).ip << " with port:" << cameras.at(location-1).port << std::endl;	      
								cameraInstance->setRefTime(cameras.at(location-1).timeout);
								ret = cameraInstance->connect();
								std::cout << "(AVISO) Conexión a cámara retorna " << ret << std::endl;
								if(ret > 0)
								{
									if(!cameraInstance->setRelayOn(cameras.at(location-1).relayB, 0))
									{			   
										cameras.at(location-1).statusB = 0;
										sleep(1); //testing
										if(!cameraInstance->setRelayOn(cameras.at(location-1).relayA, -1))
											cameras.at(location-1).statusA = 1;
									}
								}
								else
								{
									console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
								}
							}
							catch(...)
							{
								console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
							}
							cameraInstance->disconnect();
							delete cameraInstance;			      
						}
						else
							console.push_back("*ERROR* ¡Imposible conectar con la cámara!");
					}
					else 
					{
						str_log_message = "(CAMERA'S TRAFFIC LIGHTS)(*ERROR*) camera statusB bit activated!, cancelling switching OFF";
						log_message(str_log_message, 2);
					}		      
					break;
				case(1): //on
					if(!cameras.at(location-1).statusB)
					{
						if(isConnected(cameras.at(location-1).ip.c_str(),cameras.at(location-1).port))
						{
							camera* cameraInstance = new camera(cameras.at(location-1).ip,cameras.at(location-1).port);	 
							try
							{
								std::cout << "(INFO) usando camera, ip:" << cameras.at(location-1).ip << " with port:" << cameras.at(location-1).port << std::endl;	      
								cameraInstance->setRefTime(cameras.at(location-1).timeout);
								ret = cameraInstance->connect();
								std::cout << "(AVISO) Conexión a cámara retorna " << ret << std::endl;
								if(ret > 0)
								{
									// if(!cameraInstance->setRelayOn(cameras.at(location-1).relayB,cameras.at(location-1).lastGreen.seconds*1000))
									if(!cameraInstance->setRelayOn(cameras.at(location-1).relayB, -1))
									{
										cameras.at(location-1).statusB = 1;
										cameras.at(location-1).lastGreen.begin =  std::chrono::steady_clock::now();
										sleep(1); //testing
										if(!cameraInstance->setRelayOn(cameras.at(location-1).relayA, 0))
											cameras.at(location-1).statusA = 0;
									}
								}
								else
								{
									console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
								}
							}
							catch(...)
							{
								console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
							}
							cameraInstance->disconnect();
							delete cameraInstance;			      
						}
						else
							console.push_back("*ERROR* ¡Imposible conectar con la cámara!");
					}
					else 
					{
						str_log_message = "(CAMERA'S TRAFFIC LIGHTS)(*ERROR*) camera statusB bit activated!, cancelling switching ON";
						log_message(str_log_message, 2);
					}		
					break;
				default: //CHECK
					if(cameras.at(location-1).statusB)
					{
						if(isConnected(cameras.at(location-1).ip.c_str(),cameras.at(location-1).port))
						{
							camera* cameraInstance = new camera(cameras.at(location-1).ip,cameras.at(location-1).port);	 
							try
							{
								std::cout << "(INFO) usando camera, ip:" << cameras.at(location-1).ip << " with port:" << cameras.at(location-1).port << std::endl;	      
								cameraInstance->setRefTime(cameras.at(location-1).timeout);
								ret = cameraInstance->connect();
								std::cout << "(AVISO) Conexión a cámara retorna " << ret << std::endl;
								if(ret > 0)
								{
									cameras.at(location-1).lastGreen.end = std::chrono::steady_clock::now();
									if(std::chrono::duration_cast<std::chrono::seconds>(cameras.at(location-1).lastGreen.end - cameras.at(location-1).lastGreen.begin).count() >= cameras.at(location-1).lastGreen.seconds)
									{
										if(!cameraInstance->setRelayOn(cameras.at(location-1).relayB, 0))
										{
											cameras.at(location-1).statusB = 0;
											if(!cameraInstance->setRelayOn(cameras.at(location-1).relayA, -1))
												cameras.at(location-1).statusA = 1;
										}
									}
								}
								else
								{
									console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
								}
							}
							catch(...)
							{
								console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
							}
							cameraInstance->disconnect();
							delete cameraInstance;			      
						}
						else
							console.push_back("*ERROR* ¡Imposible conectar con la cámara!");
					}	
					else 
					{
						str_log_message = "(CAMERA'S TRAFFIC LIGHTS)(*ERROR*) camera statusB bit activated!, cancelling CHECK";
						log_message(str_log_message, 2);
					}	
					break;
	    	}
		  
		}
      	else
		{
	  		sprintf(error,"*ERROR* mala localización de la cámara o mala configuración en el .ini, localización:%d,cámaras en .ini:%zu", location, cameras.size());
	  		console.push_back(error);
			str_log_message = "(CAMERA'S TRAFFIC LIGHTS)(*ERROR*) wrong camera location! location:" + std::to_string(location) + " cameras in ini file:" + std::to_string(cameras.size());
			log_message(str_log_message, 2);
		}
    }
  	else
	{
    	str_log_message = "(CAMERA'S TRAFFIC LIGHTS)(WARNING!) camera's traffic lights not enabled, check your configuration";
		log_message(str_log_message, 1);
		if((location <= cameras.size()) && (location > 0))
		{
	  		if(on_off_check == -1) // only checking when not enabled, for turning them off
	    	{
				if(cameras.at(location-1).statusB)
				{
					if(isConnected(cameras.at(location-1).ip.c_str(),cameras.at(location-1).port))
					{
						camera* cameraInstance = new camera(cameras.at(location-1).ip,cameras.at(location-1).port);	 
						try
						{
							std::cout << "(INFO) usando camera, ip:" << cameras.at(location-1).ip << " with port:" << cameras.at(location-1).port << std::endl;	      
							cameraInstance->setRefTime(cameras.at(location-1).timeout);
							ret = cameraInstance->connect();
							std::cout << "(AVISO) Conexión a cámara retorna " << ret << std::endl;
							if(ret > 0)
							{
								cameras.at(location-1).lastGreen.end = std::chrono::steady_clock::now();
								if(std::chrono::duration_cast<std::chrono::seconds>(cameras.at(location-1).lastGreen.end - cameras.at(location-1).lastGreen.begin).count() >= cameras.at(location-1).lastGreen.seconds)
								{
									if(!cameraInstance->setRelayOn(cameras.at(location-1).relayB, 0))
									{
										cameras.at(location-1).statusB = 0;
										if(!cameraInstance->setRelayOn(cameras.at(location-1).relayA, -1))
											cameras.at(location-1).statusA = 1;
									}
								}
							}
							else
							{
								console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
							}
						}
						catch(...)
						{
							console.push_back("*ERROR* imposible usar la cámara, IP o puerto correctos? estamos en la misma red?");
						}
						cameraInstance->disconnect();
						delete cameraInstance;			      
					}
					else
						console.push_back("*ERROR* ¡Imposible conectar con la cámara!");
				}	
				else 
				{
					str_log_message = "(CAMERA'S TRAFFIC LIGHTS)(*ERROR*) camera statusB bit activated!, cancelling CHECK";
					log_message(str_log_message, 2);
				}	
			}
		}
	}
  	return; 
}

#endif
