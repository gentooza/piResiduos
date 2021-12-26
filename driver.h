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
@file driver.h
''' driver class'''
*/

#ifndef _DRIVER_
#define _DRIVER_


#include <iostream>
#include <string>
#include <vector>
#include "database.h"
#include "qtdatabase.h"


class driver
{
 public:
  driver(long code, qtDatabase& my_database);
  driver(std::vector<std::string> database_data);
  driver();
  driver(driver * reference);
  ~driver(){};

  void reset();
  void _set(std::vector<std::string> database_data);
  int is_manually_edited();
  
  //values
  long get_code(){return code;};
  void set_code(long new_code){code = new_code;};
  
  std::string get_name(){return name;};
  void set_name(std::string newName){name = newName;};
    
  std::string get_nif(){return nif;};
  void set_nif(std::string new_nif){nif = new_nif;};
  
  std::string get_address(){return address;};
  void set_address(std::string new_address){address = new_address;};
  
  std::string get_provence(){return provence;};
  void set_provence(std::string new_provence){provence = new_provence;};
  
  std::string get_city(){return city;};
  void set_city(std::string new_city){city = new_city;};
  
  std::string get_region(){return region;};
  void set_region(std::string new_region){region = new_region; };
  
  long get_zip(){return zip;}
  void set_zip(long new_zip){zip = new_zip; };
  
  long get_nima(){return nima;};
  void set_nima(long new_nima){nima = new_nima;};
  
  long get_num_ins(){return num_ins;};
  void set_num_ins(long new_num_ins){num_ins = new_num_ins;};
  
  long get_phone(){return phone;};
  void set_phone(long new_phone){phone = new_phone;};
  
  std::string get_mail(){return mail;};
  void set_mail(std::string new_mail){mail=new_mail;};
    
 private:
  long code;
  std::string name;
  std::string nif;
  std::string address;
  std::string provence;
  std::string city;
  std::string region;
  long zip;
  long nima;
  long num_ins;
  long phone;
  std::string mail;
};

#endif
