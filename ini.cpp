/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>

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
@file ini.cpp
'''configuracion.ini file processing'''
*/
#include "ini.h"


iniProcessor::iniProcessor(const char* filename)
{
  errors = 0;
  if(configIni.read(filename))
    {
      errors++;
      char buff[100];
      snprintf(buff, sizeof(buff), "ERROR: no podemos leer el archivo .ini: %s", filename);
      mensaje x;
      x.message = buff;
      x.priority=1;
      messages.push_back(x);
    }
}

int iniProcessor::getMessage(std::string & message, int priority)
{
  int ret = 0;
  if(!messages.empty())
    {
      mensaje x;
      x = messages.back();
      message = x.message;
      priority = x.priority;
      ret = 1;
      errors--;
      if(errors < 0)
	errors = 0;
	
    }
  
  return ret;
}

int iniProcessor::stationInfo(long & codigo_estacion, long & costumer_code)
{
  int ret = 0;
  std::string strCodigo_estacion = configIni.text("estacion","codigo_estacion");
  try
    {
      codigo_estacion = std::stol(strCodigo_estacion);
    }
  catch(...)
    {
      codigo_estacion = 0;
      ret = 1;
    }
  std::string strCosCode = configIni.text("estacion","nuestro_codigo_cliente");
  try
    {
      costumer_code = std::stol(strCosCode);
    }
  catch(...)
    {
      costumer_code = 0;
      ret = 1;
    }
   
  return ret;
}
int iniProcessor::setStation(long code)
{
  char text[128];
  sprintf(text,"%lu",code);
  configIni.setText("estacion","codigo_estacion",text);
  configIni.write("config.ini");
  return 0;
}

int iniProcessor::transInfo(long &default_transport_code)
{
  int ret = 0;
  std::string strDefault_transport_code = configIni.text("estacion", "codigo_transportista");
  try
    {
      default_transport_code = std::stol(strDefault_transport_code);
    }
  catch(...)
    {
      default_transport_code = 0;
      ret = 1;
    }
  return ret;
}

int iniProcessor::setTrans(long default_transport_code)
{
  char text[128];
  sprintf(text, "%lu", default_transport_code);
  configIni.setText("estacion", "codigo_transportista", text);
  configIni.write("config.ini");
  return 0;
}

int iniProcessor::setCosCode(long code)
{
  char text[128];
  sprintf(text,"%lu",code);
  configIni.setText("estacion","nuestro_codigo_cliente",text);
  configIni.write("config.ini");
  return 0;
}
int iniProcessor::setName(const char* name)
{
  configIni.setText("estacion","nombre",name);
  configIni.write("config.ini");
  return 0;
}

int iniProcessor::setType(const char* type)
{
  configIni.setText("estacion","tipo",type);
  configIni.write("config.ini");  
  return 0;
}

int iniProcessor::databaseInfo(const char *dbLocalRemote, std::string & driver, std::string & host, std::string & port,std::string & name , std::string & user , std::string & pass)
{
  int ret = 0;
  char buff[100];
  mensaje x;
  if(dbLocalRemote != NULL)
    {
      driver = configIni.text(dbLocalRemote,"tipo");
      if(driver.compare("QMYSQL") && driver.compare("QSQLITE"))
	{
	  errors++;
	  snprintf(buff, sizeof(buff), "ERROR: driver de base de datos no válido, elija QMYSQL o QSQLITE");
	  x.message = buff;
	  x.priority=1;
	  messages.push_back(x);
	  ret = 1;
	}
      host = configIni.text(dbLocalRemote,"host");
      name = configIni.text(dbLocalRemote,"nombre");
      if(name.empty())
	{
	  errors++;
	  snprintf(buff, sizeof(buff), "ERROR: base de datos sin nombre!");
	  x.message = buff;
	  x.priority=1;
	  messages.push_back(x);
	  ret = 1;
	}
      user = configIni.text(dbLocalRemote,"usuario");
      pass = configIni.text(dbLocalRemote,"pass");
      port = configIni.text(dbLocalRemote,"puerto");
    }
  return ret;
}
/*! int realDataBaseInfo(const char *dbLocalRemota, std::string & host, std::string & port)
function for getting the real database connection, for databases through a ssh tunneling
*/
int iniProcessor::realDatabaseInfo(const char *dbLocalRemote, std::string & host, std::string & port)
{
  int ret = 0;
  char buff[100];
  mensaje x;
  if(dbLocalRemote != NULL)
    {
      host = configIni.text(dbLocalRemote,"host_real");
      port = configIni.text(dbLocalRemote,"port_real");
    }
  return ret;
}  

//cámaras
int iniProcessor::retCamNum()
{
  int ret = -1;
  ret = atoi(configIni.text("cameras","num"));
  return ret;
}

int iniProcessor::retCamData(int index, std::string & ip, int & port, int & timeout, int & relayA, int & relayB)
{
  int ret = -1;
  char linea[32];

  if(index > 0)
    {
      sprintf(linea,"camera%d_ip",index);
      ip = configIni.text("cameras",linea);
      sprintf(linea,"camera%d_port",index);
      port = atoi(configIni.text("cameras",linea));
      sprintf(linea,"camera%d_timeout",index);
      timeout = atoi(configIni.text("cameras",linea));
      sprintf(linea,"camera%d_releeV",index);
      relayA = atoi(configIni.text("cameras",linea));
      sprintf(linea,"camera%d_releeR",index);
      relayB = atoi(configIni.text("cameras",linea));     
      ret = 0;
    }

  return ret;
}

int iniProcessor::setCamIp(int index, std::string ip)
{
  int ret = -1;
  char linea[32];
  if(index > 0)
    {
      sprintf(linea,"camera%d_ip",index);
      configIni.setText("cameras",linea,ip.c_str());
      configIni.write("config.ini");
      ret = 0;
    }
  return ret;
}
int iniProcessor::setCamPort(int index, int port)
{
  int ret = -1;
  char linea[32];
  char value[32]; 
  if(index > 0)
    {
      sprintf(linea,"camera%d_port",index);
      sprintf(value,"%d",port);
      configIni.setText("cameras",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}
int iniProcessor::setCamTimeout(int index, int timeout)
{
  int ret = -1;
  char linea[32];
  char value[32];
  if(index > 0)
    {
      sprintf(linea,"camera%d_timeout",index);
      sprintf(value,"%d",timeout);
      configIni.setText("cameras",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}
int iniProcessor::setCamRelayA(int index, int relay)
{
  int ret = -1;
  char linea[32];
  char value[32];
  if(index > 0)
    {
      sprintf(linea,"camera%d_releeV",index);
      sprintf(value,"%d",relay);
      configIni.setText("cameras",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}
int iniProcessor::setCamRelayB(int index, int relay)
{
  int ret = -1;
  char linea[32];
  char value[32];
  if(index > 0)
    {
      sprintf(linea,"camera%d_releeR",index);
      sprintf(value,"%d",relay);
      configIni.setText("cameras",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}

/*!are traffic lights enabled?*/
int iniProcessor::retTrafficLightsEnable()
{

  int ret = -1;
  char linea[32];
  int enabled = 0;

  sprintf(linea,"traffic_lights_enabled");
  enabled = atoi(configIni.text("cameras",linea));
     
  return enabled;
  
}

/*! enable (value != 0) or disable (value ==0) traffic lights control*/
int iniProcessor::setTraficLightsEnable(int value)
{
  int ret = -1;
  char linea[32];
  char textValue[32];

  sprintf(linea,"traffic_lights_enabled");
  sprintf(textValue,"%d",value);
  configIni.setText("cameras",linea,textValue);
  configIni.write("config.ini");
  ret = 0;

  return ret;
}

//básculas
int iniProcessor::retBasNum()
{
  int ret = -1;
  ret = atoi(configIni.text("basculas","num"));
  return ret;
}

int iniProcessor::retBasData(int index, std::string & port, int & bauds, int & timeout, std::string & ask, int & parity, int & stopBits, int & ctrl)
{
  int ret = -1;
  char linea[32];

  if(index > 0)
    {
      sprintf(linea,"bascula%d_port",index);
      port = configIni.text("basculas",linea);
      
      sprintf(linea,"bascula%d_baud",index);
      bauds = atoi(configIni.text("basculas",linea));
      
      sprintf(linea,"bascula%d_timeout",index);
      timeout = atoi(configIni.text("basculas",linea));

      sprintf(linea,"bascula%d_ask",index);
      ask = configIni.text("basculas",linea);

      sprintf(linea,"bascula%d_parity",index);
      parity = atoi(configIni.text("basculas",linea));

      sprintf(linea,"bascula%d_stopbit",index);
      stopBits = atoi(configIni.text("basculas",linea));

      sprintf(linea,"bascula%d_ctrl",index);
      ctrl = atoi(configIni.text("basculas",linea));
      
      ret = 0;
    }

  return ret;
}

int iniProcessor::setBasPort(int index, std::string port)
{
  int ret = -1;
  char linea[32];
  if(index > 0)
    {
      sprintf(linea,"bascula%d_port",index);
      configIni.setText("basculas",linea,port.c_str());
      configIni.write("config.ini");
      ret = 0;
    }
  return ret;
}

int iniProcessor::setBasBauds(int index, int bauds)
{
  int ret = -1;
  char linea[32];
  char value[32]; 
  if(index > 0)
    {
      sprintf(linea,"bascula%d_baud",index);
      sprintf(value,"%d",bauds);
      configIni.setText("basculas",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}

int iniProcessor::setBasTimeout(int index, int timeout)
{
  int ret = -1;
  char linea[32];
  char value[32];
  if(index > 0)
    {
      sprintf(linea,"bascula%d_timeout",index);
      sprintf(value,"%d",timeout);
      configIni.setText("basculas",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}

int iniProcessor::setBasAsk(int index, std::string ask)
{
  int ret = -1;
  char linea[32];
  if(index > 0)
    {
      sprintf(linea,"bascula%d_ask",index);
      configIni.setText("basculas",linea,ask.c_str());
      configIni.write("config.ini");
      ret = 0;
    }
  return ret;
}

int iniProcessor::setBasParity(int index, int parity)
{
  int ret = -1;
  char linea[32];
  char value[32];
  if(index > 0)
    {
      sprintf(linea,"bascula%d_parity",index);
      sprintf(value,"%d",parity);
      configIni.setText("basculas",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}

int iniProcessor::setBasStopBits(int index, int iValue)
{
  int ret = -1;
  char linea[32];
  char value[32];
  if(index > 0)
    {
      sprintf(linea,"bascula%d_stopbit",index);
      sprintf(value,"%d", iValue);
      configIni.setText("basculas",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}

int iniProcessor::setBasCtrl(int index, int iValue)
{
  int ret = -1;
  char linea[32];
  char value[32];
  if(index > 0)
    {
      sprintf(linea,"bascula%d_ctrl",index);
      sprintf(value,"%d",iValue);
      configIni.setText("basculas",linea,value);
      configIni.write("config.ini");
      ret = 0;
    }

  return ret;
}
float iniProcessor::retErrScale()
{
  float error;
  std::string strError = configIni.text("basculas","err_scale");
  try
    {
     error  = std::stof(strError);
    }
  catch(...)
    {
      error = 0.0;
    }
  return error;
}
int iniProcessor::setErrScale(float error)
{
  char text[128];
  sprintf(text,"%.1f",error);
  configIni.setText("basculas","err_scale",text);
  configIni.write("config.ini");
  return 0;
}

//
int iniProcessor::retMailData(std::string &smtpServer, std::string & mailUser,std::string & mailPass,int & smtpPort,int & smtpEncryption,std::vector <std::string> & mailRecipients,std::string &mailSenderName)
{
  int ret = -1;
  char linea[64];
  int index = 0;

  sprintf(linea,"smtp_server_address");
  smtpServer.clear();
  smtpServer = configIni.text("mail",linea);

  sprintf(linea,"mail_address");
  mailUser.clear();
  mailUser = configIni.text("mail",linea);

  sprintf(linea,"mail_name");
  mailSenderName.clear();
  mailSenderName = configIni.text("mail",linea);

  sprintf(linea,"mail_pass");
  mailPass.clear();
  mailPass = configIni.text("mail",linea);

  sprintf(linea,"smtp_server_port");
  smtpPort = atoi(configIni.text("mail",linea));

  //encryption to do, now by default
  smtpEncryption = 1;
  sprintf(linea,"num_recipients");
  index = atoi(configIni.text("mail",linea));

  mailRecipients.clear();
  if(index > 0)
    {
      for(int i= 1; i <= index; i++)
	{
	  sprintf(linea,"recipient%d",i);
	  std::string recipient =  configIni.text("mail",linea);
	  mailRecipients.push_back(recipient);
	}
    }
  
  return ret;
}

int iniProcessor::setSmtpAddr(std::string address)
{
  configIni.setText("mail","smtp_server_address",address.c_str());
  configIni.write("config.ini");
  return 0;
}
int iniProcessor::setSmtpPort(int port)
{
  char sPort[32];
  sprintf(sPort,"%d",port);
  configIni.setText("mail","smtp_server_port",sPort);
  configIni.write("config.ini");
  return 0;
}
int iniProcessor::setMailUser(std::string user)
{
  configIni.setText("mail","mail_address",user.c_str());
  configIni.write("config.ini");
  return 0;
}
int iniProcessor::setMailPass(std::string pass)
{
  configIni.setText("mail","mail_pass",pass.c_str());
  configIni.write("config.ini");
  return 0;
}
int iniProcessor::setMailName(std::string name)
{
  configIni.setText("mail","mail_name",name.c_str());
  configIni.write("config.ini");
  return 0;
}
int iniProcessor::setMailRecipients(std::vector <std::string> recipients)
{
  std::cout << "DEBUG: in setMailRecipients" << std::endl;
  char text[32];
  unsigned int size;
  std::string sSize;
  unsigned int newSize = recipients.size();
  
  //removing
  sSize = configIni.text("mail","num_recipients");
  try
    {
      size = std::stoi(sSize);
    }
  catch(...)
    {
      size =0;
    }
  std::cout << "Checking if remove recipients, old size = " << size << " , new size = " << newSize << std::endl;
  if(size > newSize)
    {
      for(unsigned int i= newSize +1; i <= size; i++)
	{
	  sprintf(text,"recipient%d",i);
	  std::cout << "removing [mail] -> " << text << std::endl;
	  configIni.remove("mail",text);
	}
    }
  //writting
  unsigned int j=1;
  std::vector <std::string>::iterator iter;
  
  if (newSize)
    {
      std::cout << "writting new recipients,  " << newSize << std::endl;
      sSize = std::to_string(newSize);
      configIni.setText("mail","num_recipients",sSize.c_str());
      for(iter = recipients.begin(); iter != recipients.end(); ++iter)
	{
	  sprintf(text,"recipient%d",j);
	  std::cout << "writting [mail] -> " << text << "  (value: "<< *iter << ")" << std::endl;
	  configIni.setText("mail",text,iter->c_str());
	  j++;
	}
      configIni.write("config.ini");
    }
  std::cout << "DEBUG: OUT of setMailRecipients" << std::endl;
  return 0;
}

//printers
int iniProcessor::retPrinterId(std::string & printerId)
{
  int ret = 0;
  
  printerId.clear();
  printerId = configIni.text("extras","impresora");
  if (printerId.empty())
    ret = 1;
  
  return ret;
}
int iniProcessor::setPrinterId(std::string printerId)
{
  configIni.setText("extras","impresora",printerId.c_str());
  configIni.write("config.ini");
  return 0;
}
int iniProcessor::retTicketPrinterId(std::string & printerId)
{
  int ret = 0;
  
  printerId.clear();
  printerId = configIni.text("extras","tickets_printer");
  if (printerId.empty())
    ret = 1;
  
  return ret;
}
int iniProcessor::setTicketPrinterId(std::string printerId)
{
  configIni.setText("extras","tickets_printer",printerId.c_str());
  configIni.write("config.ini");
  return 0;
}
/*! function for setting and getting the station header code of tickets */
int iniProcessor::retTicketCode(std::string & code)
{
  int ret = 0;
  
  code.clear();
  code = configIni.text("extras","tickets_code");
  if (code.empty())
  {
    // setting to default code
    code = "AAI/CA/026/M1 - GRU:292";
    ret = 1;
  }
  return ret;
}
int iniProcessor::setTicketCode(std::string code)
{
  configIni.setText("extras","tickets_code",code.c_str());
  configIni.write("config.ini");
  return 0;
}
///
//automatic sycnronization
int iniProcessor::ret_syncro_mins()
{
  int minutes;
  
  std::string str_minutes = configIni.text("extras","auto-syncronization");
  if (str_minutes.empty())
    minutes = 0;
  else
    {
      try
	{
	  minutes = std::stoi(str_minutes);
	}
      catch(...)
	{
	  minutes = 0;
	}
    }
  if(minutes <0)
    minutes = 0;
  
  return minutes;
}
int iniProcessor::set_syncro_mins(int new_minutes)
{
  if(new_minutes<0)
    new_minutes = 0;
  configIni.setText("extras","auto-syncronization",std::to_string(new_minutes).c_str());
  configIni.write("config.ini");

  return 0;
}
