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
@file station.cpp
''''''
*/
#include "station.h"

station::station(long stationCode, qtDatabase& myDatabase)
{
    this->setStation(stationCode, myDatabase);
    return;
}
station::station(std::vector<std::string> databaseData)
{
    this->setStation(databaseData);
    return;
}
station::station()
{
    code = 0;
    type = 0;	       
    name = "";
    nif = "";
    address = "";
    provence = "";
    city = "";
    cp = 0;
    region = "";
    nima = 0;
    num_ins = 0;
    phone = 0;
    mail = "";
    return;
}
station::station(station * reference)
{
    code = reference->getCode();
    reference->getType(type);
    reference->getType(sType); 
    name = reference->getName();
    nif = reference->getNif();
    address = reference->getAddress();
    provence = reference->getProvence();
    city = reference->getCity();
    cp = reference->getZip();
    region = reference->getRegion();
    nima = reference->getNima();
    num_ins = reference->getNumIns();
    phone = reference->getPhone();
    mail = reference->getMail();
    return;
}
void station::reset()
{
    code = 0;
    type = 0;	       
    name.clear();
    nif.clear();
    address.clear();
    provence.clear();
    city.clear();
    cp = 0;
    region.clear();
    nima = 0;
    num_ins = 0;
    phone = 0;
    mail.clear();
    return;
}
void station::setStation(long stationCode, qtDatabase& myDatabase)
{
    char * sql = NULL;
    selAllDatFrmCenter(sql,code);
    myDatabase.query(NULL,sql);    
    std::vector <std::vector <std::string>> dataReturn = myDatabase.retData2();
    if (dataReturn.size())
    {
        this->setStation(dataReturn.at(0));
    }
    else
    {
        std::cerr << "ERROR: station::setStation wrong number of fields passed to constructor NO DATA PASSED " << '\n';
        this->reset();
    }
    refreshStationType();
    if (sql != NULL)
        delete [] sql;
    return;
}
void station::setStation(std::vector<std::string> databaseData)
{
    if(databaseData.size() >= 12)
    {
        std::vector <std::string>::iterator iter;
        int i = 0;
        for(iter = databaseData.begin(); iter != databaseData.end(); ++iter)
        {
            if(i==0) //CODE
            {
                try
                {
                    code = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "station::setStation In station CODE field 0 = " << *iter <<  '\n';
                    code = 0;
                }
            }
            if(i==1) //TYPE
            {
                try
                {
                    type = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "station::setStation In station TYPE field 0 = " << *iter <<  '\n';
                    type = 0;
                }
            }
            else if(i==2) //name	       
                name = *iter;
            else if(i==3) //nif
                nif = *iter;
            else if(i==4) //address
                address = *iter;
            else if(i==5) //provence
                provence = *iter;
            else if(i==6) //city
                city = *iter;
            else if(i==7) //postal code
                try
                {
                    cp = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "station::setStation In station POSTAL_CODE field 7 = " << *iter <<  '\n';
                    cp = 0;
                }
            else if(i==8) //region
                region = *iter;
            else if(i==9) //NIMA
            {
                try
                {
                    nima = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "station::setStation In station NIMA field 9 = " << *iter <<  '\n';
                    nima = 0;
                }
            }
            else if(i==10) //num ins
            {
                try
                {
                    num_ins = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "station::setStation In station NUM_INS field 10 = " << *iter <<  '\n';
                    num_ins = 0;
                }
            }
            else if(i==11) //phone
            {
                try
                {
                    phone = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "station::setStation In station PHONE field 11 = " << *iter <<  '\n';
                    phone = 0;
                }
            }
            else if(i==12) //mail
                mail = *iter;
            i++;
        }
    }
    else
    {
        std::cerr << "ERROR: station::setStation wrong number of fields passed to constructor, needed 12, received " << databaseData.size() <<  '\n';
        this->reset();
    }
    return;
}

void  station::refreshStationType()
{

  if(type == 1)
    sType = "PT";
  else if(type == 2)
    sType = "ET";
  else if(type == 3)
    sType = "D5";
  else if(type == 4)
    sType = "PL";
  else if(type == 5)
    sType = "EXTERNO";
  else
    sType = "undefined";

  return;
}
int station::isManuallyEdited()
{
  int ret = 0;
  if(code == 0)
    {
      if(!name.empty() || !nif.empty() || !address.empty() || !provence.empty() || !city.empty() || !region.empty() || !mail.empty())
	ret = 1;
      if(cp != 0 || nima != 0 || num_ins != 0 || phone != 0)
	ret = 1;
    }
  return ret;
}
