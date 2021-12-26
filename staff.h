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
@file staff.h
''' staff technician information'''
*/

#ifndef _STAFF_
#define _STAFF_


#include <iostream>
#include <string>
#include <vector>
#include "database.h"
#include "qtdatabase.h"


class staff
{
 public:
  staff(long id_code, qtDatabase&);
  staff(std::vector<std::string> database_data);
  staff();
  staff(staff * reference);
  ~staff(){};

  void reset();
  void set_staff(long id_code, qtDatabase&);
  void set_staff(std::vector<std::string> database_data);
  //values
  long get_code(){return code;};
  
  std::string get_name(){return name;};
  void set_name(std::string new_name){name = new_name;};
   
  std::string get_nif(){return nif;};
  void set_nif(std::string new_nif){nif = new_nif;};

  int get_status(){return status;};
  void set_status(int new_status){status = new_status;};
    
 private:
  long code;
  std::string name;
  std::string nif;
  int status;
};

#endif
