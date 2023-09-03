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
@file costumer.cpp
''''''
*/
#include "costumer.h"

costumer::costumer(long cosCode, qtDatabase& myDatabase)
{
    this->setCostumer(cosCode, myDatabase);
    return; 
}
costumer::costumer(std::vector<std::string> databaseData)
{
    this->setCostumer(databaseData);
    return;
}
costumer::costumer()
{
    code = 0;
    name = "";
    nif = "";
    address = "";
    provence = "";
    city = "";
    region = "";
    cp = 0;
    billin_code = 0;
    cbc = 0;
    type = 0;
    nima = 0;
    num_ins = 0;
    phone = 0;
    mail = "";
    return;
}
costumer::costumer(costumer * reference)
{
    code = reference->getCode();
    try {
        name = reference->getName();
    } catch(...) {
        name = "";
    }
    nif = reference->getNif();
    address = reference->getAddress();
    provence = reference->getProvence();  
    city = reference->getCity();
    region = reference->getRegion();
    cp = reference->getCp();
    billin_code = reference->getBillin();
    cbc = reference->getCbc();   
    type = reference->getType();
    nima = reference->getNima();
    num_ins = reference->getNumIns();
    phone = reference->getPhone();
    mail = reference->getMail();
    return;
}
void costumer::reset()
{
    code = 0;
    name.clear();
    nif.clear();
    address.clear();
    provence.clear();
    city.clear();
    region.clear();
    cp = 0;
    billin_code = 0;
    cbc = 0;
    type = 0;
    nima = 0;
    num_ins = 0;
    phone = 0;
    mail.clear();
    return;
}
void costumer::setCostumer(long cosCode, qtDatabase& myDatabase)
{
    char *sql = NULL;

    selCosDataByCode(sql, cosCode);
    myDatabase.query(NULL, sql);	    
    std::vector <std::vector <std::string>> dataReturn = myDatabase.retData2(); 
    if (dataReturn.size())
    {
        this->setCostumer(dataReturn.at(0));
    }
    else
    {
        std::cerr << "ERROR: costumer::setCostumer wrong number of fields passed to constructor, needed 15, NO DATA RECEIVED" <<  '\n';
        reset();
    }
    return;
}
void costumer::setCostumer(std::vector<std::string> databaseData)
{
    if(databaseData.size() >= 15)
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
                std::cerr << "costumer::setCostumer In costumer CODE field 0 = " << *iter <<  '\n';
                code = 0;
                }
            }
            if(i==1) //NAME
                name = *iter;
            else if(i==2) //nif
                nif = *iter;
            else if(i==3) //address
                address = *iter;
            else if(i==4) //provence
                provence = *iter;
            else if(i==5) //city
                city = *iter;
            else if(i==6) //postal code
            {
                try
                {
                    cp = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "costumer::setCostumer In costumer POSTAL_CODE field 6 = " << *iter <<  '\n';
                    cp = 0;
                }
            }
            else if(i==7) //billing id
            {
                try
                {
                    billin_code = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "costumer::setCostumer In costumer BILLING_CODE field 7 = " << *iter <<  '\n';
                    billin_code = 0;
                }
            }
            else if(i==8) //CBC
            {
                try
                {
                    cbc = std::stoi(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "costumer::setCostumer In costumer CBC field 8 = " << *iter <<  '\n';
                    cbc = 0;
                }
            }
            else if(i==9) //type
            {
                try
                {
                    type = std::stoi(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "costumer::setCostumer In costumer TYPE field 9 = " << *iter <<  '\n';
                    type = 0;
                }
            }
            else if(i==10) //region
                region = *iter;
            else if(i==11) //NIMA
            {
                try
                {
                    nima = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "costumer::setCostumer In costumer NIMA field 11 = " << *iter <<  '\n';
                    nima = 0;
                }
            }
            else if(i==12) //num ins
            {
                try
                {
                    num_ins = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "costumer::setCostumer In costumer NUM_INS field 12 = " << *iter <<  '\n';
                    num_ins = 0;
                }
            }	      
            else if(i==13) //phone
            {
                try
                {
                    phone = std::stol(*iter);
                }
                catch(const std::invalid_argument& ia)
                {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    std::cerr << "costumer::setCostumer In costumer PHONE field 13 = " << *iter <<  '\n';
                    phone = 0;
                }
            }
            else if(i==14) //mail
                mail = *iter;
            i++;
            }
    }
    else
    {
        std::cerr << "ERROR: costumer::setCostumer wrong number of fields passed to constructor, needed 15, received " << databaseData.size() <<  '\n';
        this->reset();
    }
    return;
}

int costumer::isManuallyEdited()
{
    //TODO: to improve?
    int ret = 0;
    if(code == 0)
    {
        ret = 1;
    }
    return ret;
}