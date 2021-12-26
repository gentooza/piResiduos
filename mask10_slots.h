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

//###############################################################
//# mask10_slots.h for ProcessViewServer created: vie mar 17 12:33:32 2017
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//# PANTALLA DE EDICION DE DI
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;  //Change if applicable
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
extern std::string type;
extern std::string nombre;
extern station * myStation;
extern SYNC_DATA my_ssh_syncro_data;
extern GLOBAL_DATA globalconfiguration;
#include <boost/algorithm/string.hpp>
#include "mask10_data.h"
#include "mask10_tools.h"
#include "mask_tools.h"



static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
//
  pvResize(p,0,1910,1020);
  //memset(d,0,sizeof(DATA));
  std::string wholeTitle = getTitle();
  pvSetText(p,LABTYPE,wholeTitle.c_str());
  
  //9
  pvSetText(p,EDITMATRICULA_ROW1,formDI->retDepPlate().c_str());
  pvSetText(p,EDITREMOLQUE_ROW1,formDI->retDepPlateAtt().c_str());

  //10
  std::string strPeso = std::to_string(formDI->retDepTotalWeight());
  pvSetText(p,EDITCANT_ACEPT,strPeso.c_str());
     
  std::string myText;
  myText = removeTime(formDI->retDepDateTime());
  pvSetText(p,EDITDATE_ENT,myText.c_str());
  pvSetText(p,EDITDATE_ACEPT,myText.c_str());
  myText.clear();



  //console
  consoleRefresh(p,d);
  
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //máquina de cambio de estados Entrada PT
  std::cout << "#######DEBUG EDICION DI######" << std::endl;
 
  std::cout << "############" << std::endl;
  //maquinaEstados(p,d);
  //actualizaEstado(p,d);
  //console
  consoleRefresh(p,d);
  //date and Time
  setDate(p,d,LABDATE);
  setTime(p,d,LABTIME);
  //syncronization
  int i = reconnectSSH(&my_ssh_syncro_data);
  if(i == -1)
    console.push_back("*ERROR* hubo un error intentando reconectar el tunel ssh, ejecute el script manualmente");
  else if (i>=0)
    console.push_back("(INFO) reconexión del tunel ssh para la base de datos central, efectuada");
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonPressedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonReleasedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
    if(id == BUT1) //salvar
    {
      std::cout << "form save" << std::endl;
      switch(formDI->retForm())
	{
	case(1): //unloading
	  if(formEntrada)
	    delete formEntrada;
	  formEntrada = new inputForm();
	  formEntrada->copyFrom(formDI);
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	case(2)://loading
	  if(formSalida)
	    delete formSalida;
	  formSalida = new outputForm();	  
	  formSalida->copyFrom(formDI);
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask5(p);
	  break;
	default://unknown
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	}
    }
    else if(id == BUT2) //CANCEL
    {
      std::cout << "form reset" << std::endl;
      switch(formDI->retForm())
	{
	case(1):
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	case(2):
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask5(p);
	  break;
	default:
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	}
    }
  else if(id == BUT1234)
    show_mask6(p);
  else if(id == BUT5)
    show_mask7(p);    
  else if(id == BUT6)
    show_mask8(p);    
  else if(id == BUT78)
    show_mask9(p);
  else if(id == BUT910)
    show_mask10(p);
  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotGlInitializeEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlPaintEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlResizeEvent(PARAM *p, int id, DATA *d, int width, int height)
{
  if(p == NULL || id == 0 || d == NULL || width < 0 || height < 0) return -1;
  return 0;
}

static int slotGlIdleEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotTabEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotTableTextEvent(PARAM *p, int id, DATA *d, int x, int y, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || text == NULL) return -1;
  return 0;
}

static int slotTableClickedEvent(PARAM *p, int id, DATA *d, int x, int y, int button)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || button < 0) return -1;
  return 0;
}

static int slotSelectionEvent(PARAM *p, int id, DATA *d, int val, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || text == NULL) return -1;
  return 0;
}

static int slotClipboardEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == -1 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotRightMouseEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  //pvPopupMenu(p,-1,"Menu1,Menu2,,Menu3");
  return 0;
}

static int slotKeyboardEvent(PARAM *p, int id, DATA *d, int val, int modifier)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || modifier < -1000) return -1;
  return 0;
}

static int slotMouseMovedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseOverEvent(PARAM *p, int id, DATA *d, int enter)
{
  if(p == NULL || id == 0 || d == NULL || enter < -1000) return -1;
  return 0;
}

static int slotUserEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}
