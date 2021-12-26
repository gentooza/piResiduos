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
@file costumer.h
''' costumer interface class'''
*/

#ifndef _COSTUMER_
#define _COSTUMER_


#include <iostream>
#include <string>
#include <vector>
#include "database.h"
#include "qtdatabase.h"


class costumer
{
 public:
  costumer(long cosCode, qtDatabase& myDatabase);
  costumer(std::vector<std::string> databaseData);
  costumer();
  costumer(costumer * reference);
  ~costumer(){};

  void reset();
  void setCostumer(long cosCode, qtDatabase& myDatabase);
  void setCostumer(std::vector<std::string> databaseData);
  int isManuallyEdited();
  
  //values
  long getCode(){return code;};
  
  std::string getName(){return name;};
  void setName(std::string newName){name = newName;};
  
  int getType(){return type;};
  void setType(int newType){((newType>0 && newType <7)?type = newType:type=type);};
  
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
  
  long getCp(){return cp;}
  void setCp(long newZip){cp = newZip; };

  long getBillin(){return billin_code;}
  void setBillin(long newBillinCode){billin_code = newBillinCode; };

  int getCbc(){return cbc;};
  void setCbc(int newCbc){cbc=newCbc;};
  
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
  std::string nif;
  std::string address;
  std::string provence;
  std::string city;
  std::string region;
  long cp;
  long billin_code;
  int cbc;
  int type;
  long nima;
  long num_ins;
  long phone;
  std::string mail;
};

#endif
