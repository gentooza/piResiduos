/*
This file is part of PiResiduos.

Copyright 2017-2019, Prointegra SL.
Copyright 2019-2020, Pixelada S. Coop. And. <info (at) pixelada (dot) org>

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
//# mask6_slots.h for ProcessViewServer created: vie mar 17 12:33:32 2017
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
#include "mask6_data.h"
#include "mask6_tools.h"
#include "mask_tools.h"


static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;

  //
  pvResize(p,0,1910,1020);
  //memset(d,0,sizeof(DATA));
  std::string wholeTitle = getTitle();
  pvSetText(p,LABTYPE,wholeTitle.c_str());
  //LER
  std::string myText = std::to_string(formDI->retDepProdLER());
  pvSetText(p,EDITLER,myText.c_str());  
  myText.clear();
  //DANGER
  myText = formDI->retDepProdPeligro();
  if(myText.empty() || !myText.compare(""))
    {
      pvSetChecked(p,CHK1_NP,1);
    }
  else
    {
      pvSetChecked(p,CHK1_P,1);
    }
  myText.clear();
  //1.- DI
  myText = formDI->retDepDi();
  pvSetText(p,EDITDI,myText.c_str());
  myText.clear();
  //2.- NPT
  myText = std::to_string(formDI->retDepPermitNPT());
  pvSetText(p,EDITNOTPRE,myText.c_str());
  myText.clear();
  //3.- DATE TIME
  myText = removeTime(formDI->retDepDateTime());
  pvSetText(p,EDITDATEINI,myText.c_str());
  myText.clear();
  //4.- COSTUMER

  //only if costumer "OTROS" we can choose costumer, other options simply watch already selected costumer
  if(formDI->retDepCosCode() <= 0 && formDI->retDepCosName() == "OTROS")
    {
      std::vector<std::string> cos_names = formDI->ret_all_cos_4_combo(localDatabase);
      populateCombo(p,COMBOCLIENTE,cos_names);
      pvShow (p,COMBOCLIENTE);
    }
  else
    pvHide(p,COMBOCLIENTE);

  switch(formDI->retDepCosType())
    {
    case(1):
      pvSetChecked(p,CHK4_1,1);
      break;
    case(2):
      pvSetChecked(p,CHK4_2,1);
      break;     
    case(3):
      pvSetChecked(p,CHK4_3,1);
      break;
    case(4):
      pvSetChecked(p,CHK4_4,1);
      break;
    case(5):
      pvSetChecked(p,CHK4_5,1);
      break;
    case(6):
      pvSetChecked(p,CHK4_6,1);
      break;
    default:
      {
	switch(formDI->retDepCosTypeDef())
	  {
	  case(2):
	    pvSetChecked(p,CHK4_2,1);
	    break;     
	  case(3):
	    pvSetChecked(p,CHK4_3,1);
	    break;
	  case(4):
	    pvSetChecked(p,CHK4_4,1);
	    break;
	  case(5):
	    pvSetChecked(p,CHK4_5,1);
	    break;
	  case(6):
	    pvSetChecked(p,CHK4_6,1);
	    break;
	  default:
	    {
	      pvSetChecked(p,CHK4_1,1);
	      formDI->setDepCosTypeDef(1);
	    }
	    break;
	  }
      }
      break;
    }
  ///TYPE
  if(formDI->retDepMovType() == DEF_MOV_SALIDA) //only editable when no an output order movement
  {
    pvSetEnabled(p,CHK4_1,0);
    pvSetEnabled(p,CHK4_2,0);
    pvSetEnabled(p,CHK4_3,0);
    pvSetEnabled(p,CHK4_4,0);
    pvSetEnabled(p,CHK4_5,0);
    pvSetEnabled(p,CHK4_6,0);
  }
  if(formDI->retDepCosName().compare("OTROS"))
    {
	pvHide(p,FRAME4RED);
      myText = formDI->retDepCosName();
      pvSetText(p,EDITNOMBRE,myText.c_str());
      myText.clear();
      myText = formDI->retDepCosNif();
      pvSetText(p,EDITNIF,myText.c_str());
      myText.clear();
      myText = formDI->retDepCosAddr();
      pvSetText(p,EDITDIREC,myText.c_str());
      myText.clear();
      myText = std::to_string(formDI->retDepCosZip());
      pvSetText(p,EDITCP,myText.c_str());
      myText.clear();
      myText = formDI->retDepCosCity();
      pvSetText(p,EDITMUNI,myText.c_str());
      myText.clear();  
      myText = formDI->retDepCosProv();
      pvSetText(p,EDITPRO,myText.c_str());
      myText.clear();
      myText = formDI->retDepCosReg();
      pvSetText(p,EDITCA,myText.c_str());
      myText.clear();
      myText = std::to_string(formDI->retDepCosNima());
      pvSetText(p,EDITNIMA,myText.c_str());
      myText.clear();
      myText = std::to_string(formDI->retDepCosNumIns());
      pvSetText(p,EDITREG,myText.c_str());
      myText.clear();
      myText = std::to_string(formDI->retDepCosPhone());
      pvSetText(p,EDITTFN,myText.c_str());
      myText.clear();
      myText = formDI->retDepCosMail();
      pvSetText(p,EDITEMAIL,myText.c_str());
      myText.clear();
    }
  else
    {	

        myText = formDI->retDepPCosName();
        pvSetText(p,EDITNOMBRE,myText.c_str());
      	myText.clear();

        myText = formDI->retDepPCosNif();
        pvSetText(p,EDITNIF,myText.c_str());
      	myText.clear();


        myText = formDI->retDepPCosAddr();
        pvSetText(p,EDITDIREC,myText.c_str());
      	myText.clear();


        myText = std::to_string(formDI->retDepPCosZip());
        pvSetText(p,EDITCP,myText.c_str());
      	myText.clear();

        myText = formDI->retDepPCosCity();
        pvSetText(p,EDITMUNI,myText.c_str());
      	myText.clear();

        myText = formDI->retDepPCosProv();
        pvSetText(p,EDITPRO,myText.c_str());
      	myText.clear();

        myText = formDI->retDepPCosReg();
        pvSetText(p,EDITCA,myText.c_str());
      	myText.clear();

        myText = std::to_string(formDI->retDepPCosNima());
        pvSetText(p,EDITNIMA,myText.c_str());
      	myText.clear();

        myText = std::to_string(formDI->retDepPCosNumIns());
        pvSetText(p,EDITREG,myText.c_str());
      	myText.clear();

        myText = std::to_string(formDI->retDepPCosPhone());
        pvSetText(p,EDITTFN,myText.c_str());
      	myText.clear();

        myText = formDI->retDepPCosMail();
        pvSetText(p,EDITEMAIL,myText.c_str());
      	myText.clear();

if(formDI->retDepPCosName().empty() || formDI->retDepPCosNif().empty() || formDI->retDepPCosAddr().empty() || formDI->retDepPCosZip() == 0 || formDI->retDepPCosCity().empty() || formDI->retDepPCosProv().empty() || formDI->retDepPCosReg().empty() || formDI->retDepPCosNima() == 0 || formDI->retDepPCosNumIns() == 0 || formDI->retDepPCosPhone() == 0 || formDI->retDepPCosMail().empty())
	pvShow(p,FRAME4RED);
else
	pvHide(p,FRAME4RED);

pvSetEditable(p,EDITNOMBRE,1);
pvSetEditable(p,EDITNIF,1);
pvSetEditable(p,EDITDIREC,1);
pvSetEditable(p,EDITCP,1);
pvSetEditable(p,EDITMUNI,1);
pvSetEditable(p,EDITPRO,1);
pvSetEditable(p,EDITCA,1);
pvSetEditable(p,EDITNIMA,1);
pvSetEditable(p,EDITREG,1);
pvSetEditable(p,EDITTFN,1);
pvSetEditable(p,EDITEMAIL,1);
      //TODO RODRIGO, A COMPLETAR
      //
    }
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
  std::string myString = text;
  if(id == EDITNOMBRE)
    formDI->setDepPCosName(myString);

  else if(id == EDITNIF)
    formDI->setDepPCosNif(myString);
  else if(id == EDITDIREC)
    formDI->setDepPCosAddr(myString);
  else if(id == EDITCP)
 	  try             			
	    {
	     formDI->setDepPCosZip(std::stol(myString));
	    }
	  catch(...)
	    {
	      formDI->setDepPCosZip(0);
	    }
  else if(id == EDITMUNI)
    formDI->setDepPCosCity(myString);
  else if(id == EDITPRO)
    formDI->setDepPCosProv(myString);
  else if(id == EDITCA)
    formDI->setDepPCosReg(myString);
  else if(id == EDITNIMA)
 	  try             			
	    {
	     formDI->setDepPCosNima(std::stol(myString));
	    }
	  catch(...)
	    {
	      formDI->setDepPCosNima(0);
	    }
  else if(id == EDITREG)
 	  try             			
	    {
	     formDI->setDepPCosNumIns(std::stol(myString));
	    }
	  catch(...)
	    {
	      formDI->setDepPCosNumIns(0);
	    }
  else if(id == EDITTFN)
 	  try             			
	    {
	     formDI->setDepPCosPhone(std::stol(myString));
	    }
	  catch(...)
	    {
	      formDI->setDepPCosPhone(0);
	    }
  else if(id == EDITEMAIL)
    formDI->setDepPCosMail(myString);


  if(!formDI->retDepCosName().compare("OTROS") && formDI->retDepPCosName().empty()) // || formDI->retDepPCosNif().empty() || formDI->retDepPCosAddr().empty() || formDI->retDepPCosZip() == 0 || formDI->retDepPCosCity().empty() || formDI->retDepPCosProv().empty() || formDI->retDepPCosReg().empty() || formDI->retDepPCosNima() == 0 || formDI->retDepPCosNumIns() == 0 || formDI->retDepPCosPhone() == 0 || formDI->retDepPCosMail().empty()))
    pvShow(p,FRAME4RED);
  else
    pvHide(p,FRAME4RED);
  //COMBO SELECCION MANUAL CLIENTE
  if(id==COMBOCLIENTE)
    {
      std::string temporal;
      std::string name = text;
      if(name.compare("ELIJA O A MANO")) //CLEAR
	{	  
	  long cos_code = retCodeFromString(name," ");

	  formDI->set_dep_p_costumer_code(cos_code);
	  formDI->set_dep_p_costumer_data(localDatabase, cos_code);
	  
	  
	  pvSetText(p,EDITNOMBRE,formDI->retDepPCosName().c_str());
	  pvSetText(p,EDITNIF,formDI->retDepPCosNif().c_str());
	  pvSetText(p,EDITDIREC,formDI->retDepPCosAddr().c_str());
	  pvSetText(p,EDITCP,std::to_string(formDI->retDepPCosZip()).c_str());
	  pvSetText(p,EDITMUNI,formDI->retDepPCosCity().c_str());
	  pvSetText(p,EDITPRO,formDI->retDepPCosProv().c_str());
	  pvSetText(p,EDITCA,formDI->retDepPCosReg().c_str());
	  pvSetText(p,EDITNIMA,std::to_string(formDI->retDepPCosNima()).c_str());
	  pvSetText(p,EDITREG,std::to_string(formDI->retDepPCosNumIns()).c_str());
	  pvSetText(p,EDITTFN,std::to_string(formDI->retDepPCosPhone()).c_str());
	  pvSetText(p,EDITEMAIL,formDI->retDepPCosMail().c_str());
	  	
	}
      pvSetFocus(p,COMBOCLIENTE);
     
    }

 

  //TODO RODRIGO
  //else if(id ==
  //
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
  std::string myText = text;
  if(id==CHK4_1 && !myText.compare("(1)"))
      formDI->setDepCosType(1);
  else if(id==CHK4_2 && !myText.compare("(1)"))
      formDI->setDepCosType(2);
  else if(id==CHK4_3 && !myText.compare("(1)"))
      formDI->setDepCosType(3);
  else if(id==CHK4_4 && !myText.compare("(1)"))
      formDI->setDepCosType(4);
  else if(id==CHK4_5 && !myText.compare("(1)"))
      formDI->setDepCosType(5);
  else if(id==CHK4_6 && !myText.compare("(1)"))
      formDI->setDepCosType(6);
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
