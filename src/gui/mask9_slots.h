/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
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
//# mask9_slots.h for ProcessViewServer created: vie mar 17 12:33:32 2017
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
#include "mask9_data.h"
#include "mask9_tools.h"
#include "mask_tools.h"

static int slotInit(PARAM *p, DATA *d)		
{
  if(p == NULL || d == NULL) return -1;

  //
  pvResize(p,0,1910,1020);
  //memset(d,0,sizeof(DATA));
  std::string wholeTitle = getTitle();
  pvSetText(p,LABTYPE,wholeTitle.c_str());

  std::vector<std::string> prodNames = formDI->retAllProds4Combo(localDatabase);
   
  //only if transfer we can choose product, other options simply watch already selected product
  if(formDI->retForm() == 2 && formDI->retDepMovType() == DEF_MOV_TRANSFER)
    {populateCombo(p,COMBOPRODUCTO,prodNames);
    pvShow (p,COMBOPRODUCTO);}
  else
    pvHide(p,COMBOPRODUCTO);

  if(formDI->retDepProdCode() == 0)
  pvShow(p,FRAME7RED);

  if(formDI->retDepProdCode() > 0)
    {
      pvHide(p,FRAME7RED);
      std::string fullName =  formDI->retDepProdFullName();
      std::string field = std::to_string(formDI->retDepProdLER());
      pvSetText(p,EDITLER,field.c_str());
      pvSetText(p,EDITDESCLER,fullName.c_str());
      pvSetText(p,EDITPELIGRO,formDI->retDepProdPeligro().c_str());
      std::string strPeso = std::to_string(formDI->retNetWeight());
      pvSetText(p,EDITPESO,strPeso.c_str());
      
      if(formDI->retForm() == 2 && formDI->retDepMovType() == DEF_MOV_TRANSFER)
	setComboBoxPos(p,COMBOPRODUCTO,prodNames, formDI->retDepProdFullName() + " " + std::to_string(formDI->retDepProdCode()));	  
    }

    //////////////////////////////////////////////
    //combobox drivers
    pvShow(p,COMBOTRANSPORTISTA);
    formDI->updteDrivers(localDatabase);
    std::vector <std::string> driversName = formDI->retAllDriversNames();
    populateCombo(p, COMBOTRANSPORTISTA, driversName);
    
    driver * myDriver;
    formDI->retDepDriver(myDriver);
    pvSetText(p, EDITNOMBRE, myDriver->getName().c_str());
    pvSetText(p, EDITNIF, myDriver->getNif().c_str());		//DNI
    pvSetText(p, EDITDIREC, myDriver->getAddress().c_str());	//Direccion	
    pvSetText(p, EDITCP, std::to_string(myDriver->getZip()).c_str()); 
    pvSetText(p, EDITMUNI, myDriver->getCity().c_str());	//Ciudad
    pvSetText(p, EDITPRO, myDriver->getProvence().c_str());		//Provincia
    pvSetText(p, EDITCA, myDriver->getRegion().c_str());		//Comunidad Autonoma
    pvSetText(p, EDITNIMA, myDriver->getNima().c_str());
    pvSetText(p, EDITREG, myDriver->getNumIns().c_str());			//Nº inscripcion en el registro	
    pvSetText(p, EDITTFN, myDriver->getPhone().c_str());	
    pvSetText(p, EDITEMAIL, myDriver->getMail().c_str());	//Email

    if(myDriver->getCode() == 0)
        pvShow(p,FRAME8RED);
    else
        pvHide(p,FRAME8RED);

    setComboBoxPos(p, COMBOTRANSPORTISTA, driversName, myDriver->getName());

    delete myDriver;  
    //console
    consoleRefresh(p,d);
    pvHide(p,LOADINGFORM);
  
    return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //máquina de cambio de estados Entrada PT
  std::cout << "#######DEBUG EDICION DI######" << std::endl;
 
  std::cout << "############" << std::endl;
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
            {                
	            if(formEntrada)
	                delete formEntrada;
	            formEntrada = new inputForm();
	            formEntrada->copyFrom(formDI);
	            if(formDI)
	                delete formDI;
	            formDI = NULL;
	            show_mask4(p);
	            break;
            }
	        case(2)://loading
            {
	            if(formSalida)
	                delete formSalida;
	            formSalida = new outputForm();	  
	            formSalida->copyFrom(formDI);
	            if(formDI)
	                delete formDI;
	            formDI = NULL;
	            show_mask5(p);
	            break;
            }
	        default://unknown
            {
	            if(formDI)
	                delete formDI;
	            formDI = NULL;
	            show_mask4(p);
	            break;
            }
	    }
    }
    else if(id == BUT2) //CANCEL
    {
        std::cout << "form reset" << std::endl;
        switch(formDI->retForm())
	    {
	        case(1):
            {
	            if(formDI)
	                delete formDI;
	            formDI = NULL;
	            show_mask4(p);
	            break;
            }
	        case(2):
            {
	            if(formDI)
	                delete formDI;
	            formDI = NULL;
	            show_mask5(p);
	            break;
            }
	        default:
            {
	            if(formDI)
	                delete formDI;
	            formDI = NULL;
	            show_mask4(p);
	            break;
            }
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
    if(id==COMBOTRANSPORTISTA)
    {
        std::string temporal;
        std::string name = text;
        // if(!name.compare("ELIJA")) //CLEAR DO NOTHING
        if(!name.compare("DEFINIDO A MANO")) //A MANO
	    {
	        pvSetText(p, EDITNOMBRE, "SUS DATOS EN COMENTARIO");
	        formDI->setDriverByCode(0, localDatabase);
	        pvSetText(p, EDITNIF, "");
	        pvSetText(p, EDITDIREC, "");
	        pvSetText(p, EDITCP, "");
	        pvSetText(p, EDITMUNI, "");
	        pvSetText(p, EDITPRO, "");
	        pvSetText(p, EDITCA, "");
	        pvSetText(p, EDITNIMA, "");
	        pvSetText(p, EDITREG, "");
	        pvSetText(p, EDITTFN, "");
	        pvSetText(p, EDITEMAIL, "");
	        pvHide(p, FRAME8RED);
	    }
        else
	    {
	        formDI->setDriverByName(name);
            driver * myDriver;
            formDI->retDepDriver(myDriver);
	        pvSetText(p, EDITNOMBRE, name.c_str());	  			//Nombre
	        pvSetText(p, EDITNIF, myDriver->getNif().c_str());		//DNI
	        pvSetText(p, EDITDIREC, myDriver->getAddress().c_str());	//Direccion
	        pvSetText(p, EDITCP, std::to_string(myDriver->getZip()).c_str());
	        pvSetText(p, EDITMUNI, myDriver->getCity().c_str());	//Ciudad
	        pvSetText(p, EDITPRO, myDriver->getProvence().c_str());		//Provincia
	        pvSetText(p, EDITCA, myDriver->getRegion().c_str());		//Comunidad Autonoma	
	        pvSetText(p, EDITNIMA, myDriver->getNima().c_str()); // NIMA
	        pvSetText(p, EDITREG, myDriver->getNumIns().c_str()); // Applying Number	
	        pvSetText(p, EDITTFN, myDriver->getPhone().c_str());	// Phone
	        pvSetText(p, EDITEMAIL, myDriver->getMail().c_str());	//Email
	        pvHide(p, FRAME8RED);
            delete myDriver;
	    }
        pvSetFocus(p,COMBOTRANSPORTISTA);
    }
    else if(id==COMBOPRODUCTO)
    {      
        std::string name = text;
        if(!name.compare("ELIJA")) //CLEAR
	    {
	        pvShow(p,FRAME7RED);	  
	        pvSetText(p,EDITLER,"");
	        pvSetText(p,EDITDESCLER,"");
	        pvSetText(p,EDITPELIGRO,"");
	        pvSetText(p,EDITPESO,"");
	        formDI->resetDepProduct();	    	 
	    }
        else
	    {
	        long prodCode = retCodeFromString(name," ");        
	        if(prodCode)
	        {
	            pvHide(p,FRAME7RED);
	            formDI->setDepProdCode(prodCode);
	            formDI->setAllProductData(localDatabase);
	            std::string field = std::to_string(formDI->retDepProdLER());
	            pvSetText(p,EDITLER,field.c_str());
	            pvSetText(p,EDITDESCLER,formDI->retDepProdFullName().c_str());
	            pvSetText(p,EDITPELIGRO,formDI->retDepProdPeligro().c_str());
	            std::string strPeso = std::to_string(formDI->retNetWeight());
	            pvSetText(p,EDITPESO,strPeso.c_str());
	        }
	        else
	        {
	            pvShow(p,FRAME7RED);
	            pvSetText(p,EDITLER,"");
	            pvSetText(p,EDITDESCLER,"");
	            pvSetText(p,EDITPELIGRO,"");
	            pvSetText(p,EDITPESO,"");
	            formDI->resetDepProduct();
	        }
	    }
        pvSetFocus(p,COMBOPRODUCTO);
    }
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
