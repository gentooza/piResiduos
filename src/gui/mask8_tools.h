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


#ifndef _MASK8_TOOLS_
#define _MASK8_TOOLS_
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


static std::vector<std::string> popteExternalCenters(PARAM *p,int id, baseForm *& myForm, qtDatabase & myDatabase)
{
  std::vector<std::string> myList;
  std::vector<std::string> stationsList = myForm->retStationsLst(myDatabase,0);
  std::vector<std::string>::iterator iter;
  
  pvClear(p,id);
  myList.push_back("ELIJA");
  myList.push_back("DEFINIDO A MANO");
  myList.insert(myList.end(),stationsList.begin(),stationsList.end());
  for(iter = myList.begin(); iter != myList.end(); ++iter)
    pvSetText(p,id,iter->c_str());
  pvToolTip(p,id,"ELIJA");
  
  return myList;
}


static std::vector<std::string> popteInternalCenters(PARAM *p,int id, baseForm *& myForm, qtDatabase & myDatabase)
{
  std::vector<std::string> myList;
  std::vector<std::string> stationsList = myForm->retStationsLst(myDatabase,1);
  std::vector<std::string>::iterator iter;
  
  pvClear(p,id);
  myList.push_back("ELIJA");
  myList.insert(myList.end(),stationsList.begin(),stationsList.end());
  for(iter = myList.begin(); iter != myList.end(); ++iter)
    pvSetText(p,id,iter->c_str());
  pvToolTip(p,id,"ELIJA");

  return myList;
}

static int setComboCenters(PARAM * p,DATA *d, int id)
{
  int ret = -1;
  int pos = findCodeInList(d->comboList,d->comboCode);
  if(pos >= 0)
    {
      pvSetCurrentItem(p,id,pos);
      ret = 0;
    }
  else
    pvSetCurrentItem(p,id,pos);   
  return ret;      
}

static void saveStation(PARAM * p, DATA* d,baseForm *& myForm,station *&myStation)
{
  myForm->setDepDestStation(myStation); 
}

/*! FUNCTION for set all text data from selected station*/
static void  refStationData(PARAM * p, DATA* d,station *&myStation)
{
    pvSetText(p, EDITNOMBRE_A, myStation->getName().c_str());
    pvSetText(p, EDITDIREC_A, myStation->getAddress().c_str());
    pvSetText(p, EDITPRO_A, myStation->getProvence().c_str());
    pvSetText(p, EDITNIF_A, myStation->getNif().c_str());
    pvSetText(p, EDITCA_A, myStation->getRegion().c_str());
    pvSetText(p, EDITMUNI_A, myStation->getCity().c_str());
    pvSetText(p, EDITNIMA_A, myStation->getNima().c_str());
    pvSetText(p, EDITREG_A, myStation->getNumIns().c_str());
    std::string temp = std::to_string(myStation->getZip());
    pvSetText(p, EDITCP_A,temp.c_str());
}

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
