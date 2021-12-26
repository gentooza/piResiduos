/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2020, Pixelada S. Coop. And. <info (at) pixelada (dot) org>

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
@file station.h
''' recycling center information'''
*/

#ifndef _STATION_
#define _STATION_


#include <iostream>
#include <string>
#include <vector>
#include "database.h"
#include "qtdatabase.h"

enum //station type
  {
    DEF_STATION_UNDEFINED = 0,
    DEF_STATION_MASTER, // PT
    DEF_STATION_TRANSFER, // ET
    DEF_STATION_DEPOSIT, // D5
    DEF_STATION_PL, // PL
    DEF_STATION_EXTERN, // extern
  };

class station
{
 public:
  station(long stationCode, qtDatabase& myDatabase);
  station(std::vector<std::string> databaseData);
  station();
  station(station * reference);
  ~station(){};

  void reset();
  void setStation(long stationCode, qtDatabase& myDatabase);
  void setStation(std::vector<std::string> databaseData);
  void refreshStationType();
  int isManuallyEdited();
  
  //values
  long getCode(){return code;};
  std::string getName(){return name;};
  void setName(std::string newName){name = newName;};
  void getType(std::string & value){value = sType;};
  void getType(int & value){value = type;};
  void setExternalType(){type = DEF_STATION_EXTERN; refreshStationType();};
  std::string getNif(){return nif;};
  void setNif(std::string newNif){nif = newNif;};
  std::string getAddress(){return address;};
  void setAddress(std::string newAddress){address = newAddress;};
  std::string getProvence(){return provence;};
  void setProvence(std::string newProvence){provence = newProvence;};
  std::string getCity(){return city;};
  void setCity(std::string newCity){city = newCity;};
  std::string getRegion(){return region;};
  void setRegion(std::string newRegion){region = newRegion; };
  long getZip(){return cp;}
  void setZip(long newZip){cp = newZip; };
  long getNima(){return nima;};
  void setNima(long newNima){nima = newNima;};
  long getNumIns(){return num_ins;};
  void setNumIns(long newNumIns){num_ins = newNumIns;};
  long getPhone(){return phone;};
  void setPhone(long newPhone){phone = newPhone;};
  std::string getMail(){return mail;};
  void setMail(std::string newMail){mail=newMail;};
    
 private:
  long code;
  std::string name;
  std::string sType;
  int type;
  std::string nif;
  std::string address;
  std::string provence;
  std::string city;
  std::string region;
  long cp;
  long nima;
  long num_ins;
  long phone;
  std::string mail;
};

#endif
