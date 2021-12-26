/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.

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
@file ini.h
'''configuracion.ini file processing'''
*/

#ifndef _INI_CLASS_
#define _INI_CLASS_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "rlinifile.h"


struct mensaje
{
  std::string message;
  int priority;
};


class iniProcessor
{
 public:
  iniProcessor(const char*);
  ~iniProcessor();

  int anyError(){return errors;};
  int getMessage(std::string &, int);
  /*station*/
  int stationInfo(long &codigo_estacion, long &costumer_code);
  int setStation(long codigo_estacion);
  int setCosCode(long costumer_code);
  /********/
  // default transport info
  int transInfo(long &default_transport_code);
  int setTrans(long default_transport_code);
  /*deprecated*/
  int setName(const char* name);
  int setType(const char* type);
  /********/
  int databaseInfo(const char *dbLocalRemota, std::string & driver, std::string & host, std::string & port,std::string & nombre , std::string & usuario , std::string & pass);
  int realDatabaseInfo(const char *dbLocalRemota, std::string & host, std::string & port);
  
  //cameras
  int retCamNum();
  int retCamData(int index, std::string & ip, int & port, int & timeout, int & relayA, int & relayB);
  int setCamIp(int index, std::string ip);
  int setCamPort(int index, int port);
  int setCamTimeout(int index, int timeout);
  int setCamRelayA(int index, int relay);
  int setCamRelayB(int index, int relay);
  int retTrafficLightsEnable();
  int setTraficLightsEnable(int value);
  
  //basculas
  int retBasNum();
  int retBasData(int index, std::string & port, int & bauds, int & timeout, std::string & ask, int & parity, int & stopBits, int & ctrl);
  int setBasPort(int index, std::string port);
  int setBasBauds(int index, int bauds);
  int setBasTimeout(int index, int timeout);
  int setBasAsk(int index, std::string ask);
  int setBasParity(int index, int parity);
  int setBasStopBits(int index, int stopBits);
  int setBasCtrl(int index, int ctrl);
  float retErrScale();
  int setErrScale(float);

  //smtp mail
  int retMailData(std::string &smtpServer, std::string & mailUser,std::string & mailPass,int & smtpPort,int & smtpEncryption,std::vector <std::string> & mailRecipients,std::string &mailSenderName);
  int setSmtpAddr(std::string address);
  int setSmtpPort(int port);
  int setMailUser(std::string user);
  int setMailPass(std::string pass);
  int setMailName(std::string name);
  int setMailRecipients(std::vector <std::string> recipients);

  //printer
  int retPrinterId(std::string & printerId);
  int setPrinterId(std::string printerId);

  //automatic sycnronization
  int ret_syncro_mins();
  int set_syncro_mins(int new_minutes);

 private:
  rlIniFile configIni;
  int errors;
  std::vector<mensaje> messages;
};

#endif
