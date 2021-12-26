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
@file camera.h
'''class for communicating with Imagina CPLR cameras by TCP/IP socket'''
*/

#ifndef _PIR_CAMERA_
#define _PRI_CAMERA_

#include <rltime.h>
#include <rlsocket.h>
#include <iostream>
#include <string>
#include <fstream>

#define ERROR_CHECK 5

#define ASCII_INICIO 2
#define ASCII_DELIMITER 31
#define ASCII_FIN 3
#define ASCII_DATO 4

enum
  {
    STATUS = 1,
    RESET,
    TAKEPLATE
  };

class camera
{
 public:
  camera(std::string ip,int port);
  ~camera();

  int connect();
  int disconnect();

  int setRefTime(int ms);
  int checkStatus();
  int reset();

  //production
  int askPlate();
  int askForPlate(std::string &plate);
  int takePlate(std::string& plate, int timeout = 500);
  int takeImage(std::string& image, const char* imageFile);

  int sendCommand(std::string message);
  int getReponse(std::string& message,std::string& data);
  int getMessageHeader(std::string& message);
  int getMessageBody(std::string& message);
  int getMessageData(std::string& data);
  int readReponse(std::string& message,std::string& data, int timeout);
  
  int isCapturing(){return capturing;};

  std::string getIp(){ std::cout << camIp << std::endl; return camIp;}
  int getPort(){return camPort;}
  int getTimeout() { return camMs;}

  //relays
  int resetRelaysStatus();
  void setPreferredRelay(int preferred){(preferred>=1 && preferred<=4)?iRelay=preferred:iRelay=-1;};
  int setRelayOn(int relay, int milli);
  int setRelayOn(int seconds);
  
  //tools
  std::string translate(std::string);
  int prepareCommand(int commandId, std::string & command);
  int prepareRelayCommand(int relayNum, int state, int milli,  std::string & command);
  int timeout();
 
  
 private:
  int capturing;
  rlSocket * 	s;
  int camMs;
  rlTime* referenceT;
  rlTime startT;
  std::string lastJpg;
  std::string camIp;
  int camPort;
  int iRelay;
};

#endif
