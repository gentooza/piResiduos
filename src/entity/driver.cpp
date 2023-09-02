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
@file driver.cpp
''''''
*/
#include "driver.h"

/*!build by code and database query*/
driver::driver(long code, qtDatabase& myDatabase)
{
    this->setDriver(code, myDatabase);
    return;
}
/*! Class constructor, build by data from database*/
driver::driver(std::vector<std::string> databaseData)
{
    this->setDriver(databaseData);
    return;
}
/*!built blank*/
driver::driver()
{
    code = -1;
    name = "";
    nif = "";
    address = "";
    provence = "";
    city = "";
    region = "";
    zip = 0;
    nima = 0;
    num_ins = 0;
    phone = 0;
    mail = "";
    return;
}
/*!built copied from another*/
driver::driver(driver * reference)
{
    code = reference->get_code();
    name = reference->get_name();
    nif = reference->get_nif();
    address = reference->get_address();
    provence = reference->get_provence();  
    city = reference->get_city();
    region = reference->get_region();
    zip = reference->get_zip();
    nima = reference->get_nima();
    num_ins = reference->get_num_ins();
    phone = reference->get_phone();
    mail = reference->get_mail();
    return;
}
void driver::reset()
{
    code = -1;
    name.clear();
    nif.clear();
    address.clear();
    provence.clear();
    city.clear();
    region.clear();
    zip = 0;
    nima = 0;
    num_ins = 0;
    phone = 0;
    mail.clear();
    return;
}
/*! build by code and database query */
void driver::setDriver(long code, qtDatabase& my_database)
{
    char *sql = NULL;

    sel_driver_data_by_code(sql, code);
    my_database.query(NULL,sql);	    
    std::vector <std::vector <std::string>> data_return = my_database.retData2();
    if(data_return.size())
    {
        this->setDriver(data_return.at(0));
    }
    else
    {
        std::cerr << "ERROR: driver::setDriver wrong number of fields passed to constructor, NO DATA PASSED" <<  '\n';
        this->reset();
    }
    if(sql != NULL)
        delete [] sql;
    return;
}
/*! build by data from database*/
void driver::setDriver(std::vector<std::string> databaseData)
{
    if(databaseData.size() >= 15)
    {
        std::vector <std::string>::iterator iter;
        int i = 0;
        
        for(iter = databaseData.begin(); iter != databaseData.end(); ++iter)
        {
            if(i==0) //NAME
                name = *iter;
            else if(i==1) //NIF
                nif = *iter;
            else if(i==2) //ADDRESS
                address = *iter;
            else if(i==3) //PROVENCE
                provence = *iter;
            else if(i==4) //CITY
                city = *iter;
            else if(i==5) //ZIP CODE
            {
                try
                {
                    zip = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "driver::setDriver In driver POSTAL_CODE field 5 = " << *iter <<  '\n';
                    zip = 0;
                }
            }
            else if(i==6) //REGION
                region = *iter;
            else if(i==7) //NIMA
            {
                try
                {
                    nima = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "driver::setDriver In driver NIMA field 7 = " << *iter <<  '\n';
                    nima = 0;
                }
            }
            else if(i==8) //NUM APPLYING
            {
                try
                {
                    num_ins = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "driver::setDriver In driver NUM_INS field 8 = " << *iter <<  '\n';
                    num_ins = 0;
                }
            }
            else if(i==9) //PHONE
            {
                try
                {
                    phone = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "driver::setDriver In driver PHONE field 9 = " << *iter <<  '\n';
                    phone = 0;
                }
            }
            else if(i==10) //MAIL
                mail = *iter;
            i++;
        }
    }
    else
    {
        std::cerr << "ERROR: driver::setDriver wrong number of fields passed to constructor, needed 11, received " << databaseData.size() <<  '\n';
        this->reset();
    }
    return;
}

int driver::is_manually_edited()
{
  //TODO
  int ret = 0;
  if(code == 0)
    {
	ret = 1;
    }
  return ret;
}
