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
@file staff.cpp
''''''
*/
#include "staff.h"

/*! Class constructor, building entity data from database and id */
staff::staff(long id_code, qtDatabase& my_database)
{
    this->setStaff(id_code, my_database);
    return;
}
/*! Class constructor, building entity data from data vector */
staff::staff(std::vector<std::string> data)
{
    this->setStaff(data);
    return; 
}
/*! Class constructor, building empty entity data */
staff::staff()
{
    code = 0;
    name = "";
    nif = "";
    status=0;
    return;
}
/*! Class constructor, building entity from other entity */
staff::staff(staff * reference)
{
    code = reference->get_code();
    name = reference->get_name();
    nif = reference->get_nif();
    status = reference->get_status();
    return;
}
/*! reset values */
void staff::reset()
{
    code = 0;
    name.clear();
    nif.clear();
    status=0;
    return;
}

/*! building entity data from database and id */
void staff::setStaff(long id_code, qtDatabase& my_database)
{
    char *sql = NULL;

    selAllStaffData(sql,id_code);
    my_database.query(NULL,sql);
    std::vector <std::vector <std::string>> data = my_database.retData2();

    if(data.size())
    {
        this->setStaff(data.at(0));
    }
    else
    {
        std::cerr << "ERROR: staff::setStaff wrong number of fields passed to constructor, NO DATA PASSED " << '\n';
        reset();
    }
    if (sql != NULL)
        delete [] sql;
    return;
}

/*! building entity data from data vector */
void staff::setStaff(std::vector<std::string> data)
{
    // minimun expected data
    if (data.size()>=3) 
    {
        std::vector <std::string>::iterator iter;
        int i = 0;
        // staff status always 1
        status = 1;
        for(iter = data.begin(); iter != data.end(); ++iter)
        {
            if(i==0) // CODE
            {
                try
                {
                    code = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "staff::setStaff In station CODE field 0 = " << *iter <<  '\n';
                    code = 0;
                }
            }
            if(i==1) // NAME
            {
                name = *iter;
            }
            if(i==2) // NIFF
            {
                nif = *iter;
            }
            i++;
        }
    }
    else
    {
        std::cerr << "ERROR: staff::setStaff wrong number of fields passed to constructor, needed 3, received " << data.size() <<  '\n';
        reset();
    }
    return; 
}