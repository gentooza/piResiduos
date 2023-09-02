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
@file bascula.h
''' class for communicationg with scales, using RS232 port and boost asio'''
*/

#ifndef _BASCULA_
#define _BASCULA_


#include <iostream>
#include <boost/asio.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <string>
#include <fstream>




class bascula
{
 public:
  bascula(std::string port,int baudRate);
  ~bascula(){};

  int readPeso(int timeout, char *&readbuffer);

  int setCommand(std::string command){sCommand = command; return 0;};
  std::string getCommand(){return sCommand;};
  int setBauds(int baudRate);
  int getBauds(){ return iBauds;};
  int setPort(std::string port);
  std::string getPort(){return sPort;};
  void set_parity(int parity);
/*!0-> none, 1-> software, 2-> hardware*/
  void set_flowControl(int flow);
/*!0-> one, 1-> onepointfive, 2-> two*/
  void set_stopBits(int stop);
  

 private:
  int iBauds;
  std::string sPort;
  std::string sCommand;
  int iFlow;
  int iStop;
  int iParity;

};

int baudRateOk(int baudRate);
#endif
