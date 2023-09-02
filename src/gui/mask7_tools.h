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

#ifndef _MASK7_TOOLS_
#define _MASK7_TOOLS_
enum{
  CTRL_NONE = 0,
  CTRL_PROCEDER,
  CTRL_PROCEDER_CANCELAR,
  CTRL_PROCEDER_CANCELAR_RETROCEDER,
  CTRL_PROCEDER_RETROCEDER,
  CTRL_CANCELAR_RETROCEDER,
  CTRL_CANCELAR,
  CTRL_RETROCEDER
};


static int isStrInProdsVector(std::vector < std::string> lista,std::vector < std::string> listaCodes, std::string cadena)
{
  int itIs=-1;
  int i = 0;
  std::vector<std::string>::iterator iter;
  std::vector<std::string>::iterator iterCodes;
  iterCodes = listaCodes.begin();
  for(iter = lista.begin(); iter != lista.end() && iterCodes != listaCodes.end(); ++iter)
    {
      std::string producto = *iter + " " + *iterCodes;
      //std::cout << i << " comparando cadena: " << cadena << std::endl;
      //std::cout << "con conjunción: " << *iter << " " << *iterCodes << std::endl;
      if(producto.compare(cadena) == 0)
	itIs=i;
      i++;
      ++iterCodes;
    }
  
  return itIs;
}
//
static int populateProdsCombo(PARAM *p,int id, std::vector <std::vector < std::string>> lista, bool otros)
{
  pvClear(p,id);
  pvSetText(p,id,"ELIJA");
  std::vector < std::vector < std::string>>::iterator row;
  std::vector < std::string>::iterator col;
  std::string text;
  if(otros)
    pvSetText(p,id,"MOSTRAR TODOS");
  for(row = lista.begin(); row != lista.end(); ++row)
    {
      text.clear();
      for(col = row->begin(); col != row->end(); ++col)
	{		  
	  text += *col;
	  text+=" ";
	}
      pvSetText(p,id,text.c_str());
    }

  pvToolTip(p,id,"ELIJA");
  return 0;
}

static int populateCombo(PARAM *p,int id, std::vector <std::vector < std::string>> lista)
{
  pvClear(p,id);
  pvSetText(p,id,"ELIJA");
  for(int i = 0; i < lista.size();i++)
    for(int j=0;j< lista[i].size();j++)
      if(!lista[i][j].empty())
	pvSetText(p,id,lista[i][j].c_str());
  pvToolTip(p,id,"ELIJA");
  return 0;
}
//
static int populateCombo(PARAM *p,int id, std::vector < std::string> lista)
{
  pvClear(p,id);
  pvSetText(p,id,"ELIJA");
  for(int i = 0; i < lista.size();i++)
    if(!lista[i].empty())
      pvSetText(p,id,lista[i].c_str());
  pvToolTip(p,id,"ELIJA");
  return 0;
}
static int setComboBoxPos(PARAM *p,int id,std::vector< std::string> allValues, std::string value)
{
  int pos = 0;
  int done = -1;
  std::vector <std::string>::iterator iter;
  for(iter = allValues.begin(); iter != allValues.end(); ++iter)
    {
      pos++;
      std::cout << "dentro de SETOCOMBOBOXPOS, comparando:" << *iter << " , CON:" << value << std::endl;
      if(!iter->compare(value))
	{
	  pvSetCurrentItem(p,id,pos);
	  done = pos;
	}
	
    }
  return done;
}
static int setComboBoxPosByField(PARAM *p,int id,std::vector <std::vector < std::string>> allValues, std::string value, int field)
{
  int pos = 0;
  int done = -1;
  if(field <0)
    field =0;
  if(field>=allValues.size())
    field = allValues.size()-1;
  
  for(int i=0; i != allValues.size(); ++i)
    {
      pos++;
      //std::cout << "dentro de SETOCOMBOBOXPOSBYFIELD, comparando:" << allValues[i][field] << " , CON:" << value;
      if(!allValues[i][field].compare(value))
	{
	  pvSetCurrentItem(p,id,pos);
	  done = pos;
	}
    }
  return done;
}
static int populateListView(PARAM *p, int id, std::vector<std::vector <std::string>> allValues)
{
  std::cout << "dentro de populatelistview" << std::endl;
  std::vector < std::vector < std::string>>::iterator camiones;
  std::vector <std::string> ::iterator fields;
  std::string time_and_date;
  std::string plate;
  std::string wholeInfo;
  int column = 1;
  pvClear(p,id);
  std::string camion;
  for(camiones = allValues.begin(); camiones != allValues.end(); ++camiones)
    {
      column = 1;
      camion.clear();
      wholeInfo.clear();
      for(fields = camiones->begin(); fields != camiones->end(); ++fields)
	{	  
	  if(column == 2) //time and date
	    {
	     time_and_date = *fields;
	    }
	  if(column == 8) //plate
	    {
	      plate = *fields;
	    }
	  if(column == 13) //output weigth
	    {
	      int tara;
	  try
	    {
	      tara = std::stoi(*fields);
	    }
	  catch(...)
	    {
	      tara = 0;
	    }

	      if(tara > 0)
		camion = "image/small_truck_BW_icon_G.png";
	      else
		camion = "image/small_truck_BW_icon_T.png";
	    }
	  column++;
	}
      wholeInfo = "(" + time_and_date + ")\n";
      wholeInfo += plate;
      pvInsertItem(p,id,-1,camion.c_str(),wholeInfo.c_str(),1);
    }
  std::cout << "fuera de populatelistview" << std::endl;
}

/////////////////////
//HERRAMIENTAS ESTÉTICAS Y DE INTERFAZ
////////////////////
//aspecto
enum {
  FRAME_DISABLED = 0,
  FRAME_SELECTED,
  FRAME_NORMAL,
  FRAME_WORKING
};

static int setFrame(PARAM *p,DATA* d, int id, int state)
{
  switch(state)
    {
    case(FRAME_DISABLED):
      pvSetEnabled(p,id,0);
      pvSetStyle(p,id,-1,1,1,-1);
      //pvSetBackgroundColor(p,id,200,200,200);
      //pvSetFontColor(p,id,-1,-1,-1);
      break;
    case(FRAME_SELECTED):
      pvSetEnabled(p,id,1);
      pvSetStyle(p,id,-1,1,5,-1);
      //pvSetBackgroundColor(p,id,200,225,200);
      //pvSetFontColor(p,id,50,50,50);
      break;
    case(FRAME_NORMAL):
      pvSetEnabled(p,id,1);
      pvSetStyle(p,id,-1,1,1,-1);
      //pvSetBackgroundColor(p,id,-1,-1,-1);
      //pvSetFontColor(p,id,-1,-1,-1);
      break;
    case(FRAME_WORKING):
      pvSetEnabled(p,id,1);
      pvSetStyle(p,id,-1,1,1,-1);
      //pvSetBackgroundColor(p,id,200,200,225);
      //pvSetFontColor(p,id,-1,-1,-1);
      break;
    default:
      break;
    }
  return 0;
}

static int consoleRefresh(PARAM *p, DATA * d)
{
  int ret = -1;
  //console
  std::vector <std::string>::iterator iter;
  unsigned int i=0;    
  if(d->localConsole.size() != console.size())
    {
      if(console.size()>6)
	console.erase(console.begin(), console.end()-6);
      d->localConsole = console;
      for(iter = console.begin(); iter != console.end() ; ++iter)
	{
	  pvSetText(p,OUTPUT,iter->c_str());
	  ret = 0;
	}
    }
  return ret;
}
#endif
