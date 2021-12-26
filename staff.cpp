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
@file staff.cpp
''''''
*/
#include "staff.h"

/*!building entity data from database and id*/
staff::staff(long id_code,qtDatabase& my_database)
{
  
  code = id_code;
  char * sql =NULL;
  std::vector <std::vector <std::string>> data;

  sel_staff_data_by_code(sql,code);
  my_database.query(NULL,sql);
  data = my_database.retData2();

  if(data.size())
    {
      if (data[0].size()>=2) //we have returned data with minimun expected data
	{
	  status=1;
	  //nombre
	  try
	    {
	      name = data[0][0];
	    }
	  catch(...)
	    {
	      std::cerr << "Error using returned name from table staff" << '\n';
	      name="";
	      status = 0;
	    }
	  //nif
	  try
	    {
	      nif = data[0][1];
	    }
	  catch(...)
	    {
	      std::cerr << "Error using returned nif from table staff" << '\n';
	      nif="";
	      status=0;
	    }
	}
    }
  else
    {
      reset();
    }
  return;
  
}
void staff::set_staff(long id_code,qtDatabase& my_database)
{
  
  code = id_code;
  char * sql =NULL;
  std::vector <std::vector <std::string>> data;

  sel_staff_data_by_code(sql,code);
  my_database.query(NULL,sql);
  data = my_database.retData2();

  if(data.size())
    {
      if (data[0].size()>=2) //we have returned data with minimun expected data
	{
	  status=1;
	  //nombre
	  try
	    {
	      name = data[0][0];
	    }
	  catch(...)
	    {
	      std::cerr << "Error using returned name from table staff" << '\n';
	      name="";
	      status = 0;
	    }
	  //nif
	  try
	    {
	      nif = data[0][1];
	    }
	  catch(...)
	    {
	      std::cerr << "Error using returned nif from table staff" << '\n';
	      nif="";
	      status=0;
	    }
	}
    }
  else
    {
      reset();
    }
  return;
  
}
/*!building entity data from data vector*/
staff::staff(std::vector<std::string> data)
{
  if (data.size()>=2) //we have returned data with minimun expected data
    {
      status = 1;
      //nombre
      try
	{
	  name = data[0];
	}
      catch(...)
	{
	  std::cerr << "Error using returned name from table staff" << '\n';
	  name="";
	  status=0;
	}
      //nif
      try
	{
	  nif = data[1];
	}
      catch(...)
	{
	  std::cerr << "Error using returned nif from table staff" << '\n';
	  nif="";
	  status=0;
	}
    }
  else
    {
      reset();
    }
  return; 
}
/*!building empty entity data*/
staff::staff()
{
  code = 0;
  name = "";
  nif = "";
  status=0;
}
/*!building entity from other entity*/
staff::staff(staff * reference)
{
  
  code = reference->get_code();
  name = reference->get_name();
  nif = reference->get_nif();
  status = reference->get_status(); 
}
/*!reset values*/
void staff::reset()
{
  code = 0;
  name.clear();
  nif.clear();
  status=0;
}

