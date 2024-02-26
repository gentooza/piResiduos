/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2023 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

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
        void setDriver(long code, qtDatabase& my_database);
        void setDriver(std::vector<std::string> database_data);
        void setDriver(driver * reference);
        int isManuallyEdited();
        
        //values
        long getCode(){return code;};
        void setCode(long new_code){code = new_code;};
        
        std::string getName(){return name;};
        void setName(std::string newName){name = newName;};
            
        std::string getNif(){return nif;};
        void setNif(std::string new_nif){nif = new_nif;};
        
        std::string getAddress(){return address;};
        void setAddress(std::string new_address){address = new_address;};
        
        std::string getProvence(){return provence;};
        void setProvence(std::string new_provence){provence = new_provence;};
        
        std::string getCity(){return city;};
        void setCity(std::string new_city){city = new_city;};
        
        std::string getRegion(){return region;};
        void setRegion(std::string new_region){region = new_region; };
        
        long getZip(){return zip;}
        void setZip(long new_zip){zip = new_zip; };
        
        std::string getNima(){return nima;};
        void setNima(std::string new_nima){nima = new_nima;};
        
        std::string getNumIns(){return num_ins;};
        void setNumIns(std::string new_num_ins){num_ins = new_num_ins;};
        
        std::string getPhone(){return phone;};
        void setPhone(std::string new_phone){phone = new_phone;};
        
        std::string getMail(){return mail;};
        void setMail(std::string new_mail){mail = new_mail;};
    
    private:
        long code;
        std::string name;
        std::string nif;
        std::string address;
        std::string provence;
        std::string city;
        std::string region;
        long zip;
        std::string nima;
        std::string num_ins;
        std::string phone;
        std::string mail;
};

#endif
