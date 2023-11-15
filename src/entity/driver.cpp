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
    nima = "";
    num_ins = "";
    phone = "";
    mail = "";
    return;
}
/*!built copied from another*/
driver::driver(driver * reference)
{
    code = reference->getCode();
    name = reference->getName();
    nif = reference->getNif();
    address = reference->getAddress();
    provence = reference->getProvence();  
    city = reference->getCity();
    region = reference->getRegion();
    zip = reference->getZip();
    nima = reference->getNima();
    num_ins = reference->getNumIns();
    phone = reference->getPhone();
    mail = reference->getMail();
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
    nima.clear();
    num_ins.clear();
    phone.clear();
    mail.clear();
    return;
}
/*! build by code and database query */
void driver::setDriver(long code, qtDatabase& my_database)
{
    std::string sql;

    selDriverDataByCode(sql, code);
    my_database.query(NULL,sql.c_str());	    
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
    return;
}
/*! build by data from database*/
void driver::setDriver(std::vector<std::string> databaseData)
{
    if(databaseData.size() >= 12)
    {
        std::vector <std::string>::iterator iter;
        int i = 0;    
        for(iter = databaseData.begin(); iter != databaseData.end(); ++iter)
        {
            if(i == 0) //CODE
            {
                try
                {
                    code = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "driver::setDriver In driver CODE field 0 = " << *iter <<  '\n';
                    code = 0;
                }
            }
            else if(i == 1) //NAME
                name = *iter;
            else if(i == 2) //NIF
                nif = *iter;
            else if(i == 3) //ADDRESS
                address = *iter;
            else if(i == 4) //PROVENCE
                provence = *iter;
            else if(i == 5) //CITY
                city = *iter;
            else if(i == 6) //ZIP CODE
            {
                try
                {
                    zip = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "driver::setDriver In driver POSTAL_CODE field 6 = " << *iter <<  '\n';
                    zip = 0;
                }
            }
            else if(i == 7) //REGION
                region = *iter;
            else if(i == 8) //NIMA
                nima = *iter;
            else if(i == 9) //NUM APPLYING
                num_ins = *iter;
            else if(i == 10) //PHONE
                phone = *iter;
            else if(i == 11) //MAIL
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

int driver::isManuallyEdited()
{
    //TODO
    int ret = 0;
    if(code == 0)
    {
	    ret = 1;
    }
    return ret;
}
