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
//# mask8_slots.h for ProcessViewServer created: vie mar 17 12:33:32 2017
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
station * myDestStation;
costumer * myAuthCostumer;
extern SYNC_DATA my_ssh_syncro_data;
extern GLOBAL_DATA globalconfiguration;
#include <boost/algorithm/string.hpp>
#include "mask8_data.h"
#include "mask8_tools.h"
#include "mask_tools.h"


static int slotInit(PARAM *p, DATA *d)
{
    if(p == NULL || d == NULL) return -1;
    myDestStation = NULL;
    myAuthCostumer = NULL;
    //
    pvResize(p,0,1910,1020);
    std::string wholeTitle = getTitle();
    pvSetText(p,LABTYPE,wholeTitle.c_str());
    //memset(d,0,sizeof(DATA));
    //dynamic GUI construction
    std::string myString;
    std::string temp;
    formDI->retDepDestinationStation(myDestStation);
    formDI->retDepAuthCostumer(myAuthCostumer);
    if(formDI->retDepMovType() == DEF_MOV_SALIDA)
    {
	    //a) un centro desde la base de datos + campo D/R
		pvSetEditable(p, FRAME6_A,0);
		pvHide(p, COMBOEMPAUTO1); 
		pvHide(p, FRAME6RED_A);

		pvSetText(p, EDITNOMBRE_A, myDestStation->getName().c_str());
		pvSetText(p, EDITDIREC_A, myDestStation->getAddress().c_str());
		pvSetText(p, EDITPRO_A, myDestStation->getProvence().c_str());
		pvSetText(p, EDITNIF_A, myDestStation->getNif().c_str());
		pvSetText(p, EDITCA_A, myDestStation->getRegion().c_str());
		pvSetText(p, EDITMUNI_A, myDestStation->getCity().c_str());
		pvSetText(p, EDITNIMA_A, myDestStation->getNima().c_str());
		pvSetText(p, EDITREG_A, myDestStation->getNumIns().c_str());
		temp = std::to_string(myDestStation->getZip());
		pvSetText(p, EDITCP_A, temp.c_str());
		//EDITDR_A falta
		//}
		//b) nuestro cliente NO EDITABLE
		if (formDI->retDepCosType() == 4 || formDI->retDepCosType() == 1) //special cases in orders
		{
			pvSetText(p, EDITNOMBRE_B, myAuthCostumer->getName().c_str());
			pvSetText(p, EDITNIF_B, myAuthCostumer->getNif().c_str());
			pvSetText(p, EDITDIREC_B, myAuthCostumer->getAddress().c_str());
			temp = std::to_string(myAuthCostumer->getCp());
			pvSetText(p, EDITCP_B, temp.c_str());
			pvSetText(p, EDITMUNI_B, myAuthCostumer->getCity().c_str());
			pvSetText(p, EDITPRO_B, myAuthCostumer->getProvence().c_str());
			pvSetText(p, EDITCA_B, myAuthCostumer->getRegion().c_str());
			pvSetText(p, EDITNIMA_B, myAuthCostumer->getNima().c_str());
			pvSetText(p, EDITREG_B, myAuthCostumer->getNumIns().c_str());
			pvSetText(p, EDITTFN_B, myAuthCostumer->getPhone().c_str());
			pvSetText(p, EDITEMAIL_B, myAuthCostumer->getMail().c_str());
		}
		else
		{
			pvSetText(p,EDITNOMBRE_B,formDI->retDepCosName().c_str());
			pvSetText(p,EDITNIF_B,formDI->retDepCosNif().c_str());
			pvSetText(p,EDITDIREC_B,formDI->retDepCosAddr().c_str());
			temp = std::to_string(formDI->retDepCosZip());
			pvSetText(p,EDITCP_B,temp.c_str());
			pvSetText(p,EDITMUNI_B,formDI->retDepCosCity().c_str());
			pvSetText(p,EDITPRO_B,formDI->retDepCosProv().c_str());
			pvSetText(p,EDITCA_B,formDI->retDepCosReg().c_str());
			temp = std::to_string(formDI->retDepCosNima());
			pvSetText(p,EDITNIMA_B,temp.c_str());
			temp = std::to_string(formDI->retDepCosNumIns());
			pvSetText(p,EDITREG_B,temp.c_str());
			temp = std::to_string(formDI->retDepCosPhone());
			pvSetText(p,EDITTFN_B,temp.c_str());
			pvSetText(p,EDITEMAIL_B,formDI->retDepCosMail().c_str());
		}
    }
	else if(formDI->retDepMovType() == DEF_MOV_TRANSFER)
    {
		pvSetEditable(p,FRAME6_A,0);
		if(formDI->getFormType() == LOAD_FORM)
			d->comboList = popteInternalCenters(p,COMBOEMPAUTO1,formDI,localDatabase);
		else
			pvHide(p,COMBOEMPAUTO1);
		if(myDestStation->getCode() != 0) //ONE CHOSEN
		{
            pvHide(p, FRAME6RED_A);
	        d->comboCode = myDestStation->getCode();
	        setComboCenters(p, d, COMBOEMPAUTO1);  
	        pvSetText(p, EDITNOMBRE_A, myDestStation->getName().c_str());
	        pvSetText(p, EDITDIREC_A, myDestStation->getAddress().c_str());
	        pvSetText(p, EDITPRO_A, myDestStation->getProvence().c_str());
	        pvSetText(p, EDITNIF_A, myDestStation->getNif().c_str());
	        pvSetText(p, EDITCA_A, myDestStation->getRegion().c_str());
	        pvSetText(p, EDITMUNI_A, myDestStation->getCity().c_str());
            pvSetText(p, EDITNIMA_A, myDestStation->getNima().c_str());
            pvSetText(p, EDITREG_A, myDestStation->getNumIns().c_str());
	        temp = std::to_string(myDestStation->getZip());
	        pvSetText(p, EDITCP_A, temp.c_str());
	    }
        //B)
        costumer * us;
        formDI->retOurId(us);
        pvSetText(p, EDITNOMBRE_B, us->getName().c_str());
        pvSetText(p, EDITNIF_B, us->getNif().c_str());
        pvSetText(p, EDITDIREC_B, us->getAddress().c_str());
        temp = std::to_string(us->getCp());
        pvSetText(p, EDITCP_B, temp.c_str());
        pvSetText(p, EDITMUNI_B, us->getCity().c_str());
        pvSetText(p, EDITPRO_B, us->getProvence().c_str());
        pvSetText(p, EDITCA_B, us->getRegion().c_str());
        pvSetText(p, EDITNIMA_B, us->getNima().c_str());
        pvSetText(p, EDITREG_B, us->getNumIns().c_str());
        pvSetText(p, EDITTFN_B, us->getPhone().c_str());
        pvSetText(p, EDITEMAIL_B, us->getMail().c_str());
        delete us;
    }
    else //descarga de materiales
    {
        //a) nuestro centro NO EDITABLE + campo D/R
        pvHide(p, COMBOEMPAUTO1);
        pvHide(p, FRAME6RED_A);
        pvSetEditable(p, FRAME6_A, 0);            
        pvSetText(p, EDITNOMBRE_A, myDestStation->getName().c_str());
        pvSetText(p, EDITDIREC_A, myDestStation->getAddress().c_str());
        pvSetText(p, EDITPRO_A, myDestStation->getProvence().c_str());
        pvSetText(p, EDITNIF_A, myDestStation->getNif().c_str());
        pvSetText(p, EDITCA_A, myDestStation->getRegion().c_str());
        pvSetText(p, EDITMUNI_A, myDestStation->getCity().c_str());
        pvSetText(p, EDITNIMA_A, myDestStation->getNima().c_str());
        pvSetText(p, EDITREG_A, myDestStation->getNumIns().c_str());
        temp = std::to_string(myDestStation->getZip());
        pvSetText(p, EDITCP_A, temp.c_str());
        //b) our costumer NO EDITABLE
        pvSetEditable(p,FRAME6_B,0);
        costumer * us;
        formDI->retOurId(us);
        pvSetText(p, EDITNOMBRE_B, us->getName().c_str());
        pvSetText(p, EDITNIF_B, us->getNif().c_str());
        pvSetText(p, EDITDIREC_B, us->getAddress().c_str());
	    temp = std::to_string(us->getCp());
        pvSetText(p, EDITCP_B, temp.c_str());
        pvSetText(p, EDITMUNI_B, us->getCity().c_str());
        pvSetText(p, EDITPRO_B, us->getProvence().c_str());
        pvSetText(p, EDITCA_B, us->getRegion().c_str());
        pvSetText(p, EDITNIMA_B, us->getNima().c_str());
        pvSetText(p, EDITREG_B, us->getNumIns().c_str());
        pvSetText(p, EDITTFN_B, us->getPhone().c_str());
        pvSetText(p, EDITEMAIL_B, us->getMail().c_str());
        delete us;
    }
    //A) CAMPO D/R
    pvSetEditable(p,EDITDR_A,1);
    pvSetText(p,EDITDR_A,formDI->retDepDestStationDR().c_str());
    //console
    consoleRefresh(p,d);

    return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
    if(p == NULL || d == NULL) return -1;
    //máquina de cambio de estados Entrada PT
    std::cout << "#######DEBUG EDICION DI######" << std::endl;
    std::cout << "TIPO DE MOVIMIENTO: " << formDI->retDepMovType() << std::endl;
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
      saveStation(p, d, formDI, myDestStation);
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
      if(myDestStation)
	delete myDestStation;
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
      {
	saveStation(p, d, formDI, myDestStation);
	show_mask6(p);
      }
    else if(id == BUT5)
      {
	saveStation(p, d, formDI, myDestStation);
	show_mask7(p);
      }
    else if(id == BUT6)
      {
	saveStation(p, d, formDI, myDestStation);
	show_mask8(p);
      }
    else if(id == BUT78)
      {
	saveStation(p, d, formDI, myDestStation);
	show_mask9(p);
      }
    else if(id == BUT910)
      {
	saveStation(p, d, formDI, myDestStation);
	show_mask10(p);
      }
      return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
    if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
    std::string myText = text;
    if(id == COMBOEMPAUTO1)
    {
        if(d->comboSet.compare(myText))
	    {
	        pvSetEditable(p,EDITNOMBRE_A,0);	
	        pvSetEditable(p,EDITDIREC_A,0);
	        pvSetEditable(p,EDITPRO_A,0);
	        pvSetEditable(p,EDITNIF_A,0);
	        pvSetEditable(p,EDITCA_A,0);
	        pvSetEditable(p,EDITMUNI_A,0);
	        pvSetEditable(p,EDITNIMA_A,0);
	        pvSetEditable(p,EDITREG_A,0);
	        pvSetEditable(p,EDITCP_A,0);
	        if(!myText.compare("ELIJA"))
	        {
	            pvShow(p,FRAME6RED_A);
	            d->comboSet.clear();
	            d->comboCode = 0;
	            if(myDestStation)
		            delete myDestStation;
	            myDestStation = new station();
	            pvSetText(p,EDITNOMBRE_A,"");
	            pvSetText(p,EDITDIREC_A,"");
	            pvSetText(p,EDITPRO_A,"");
	            pvSetText(p,EDITNIF_A,"");
	            pvSetText(p,EDITCA_A,"");
	            pvSetText(p,EDITMUNI_A,"");
	            pvSetText(p,EDITNIMA_A,"");
	            pvSetText(p,EDITREG_A,"");
	            pvSetText(p,EDITCP_A,"");
	        }
	        else if(!myText.compare("DEFINIDO A MANO"))
	        {
	            pvShow(p,FRAME6RED_A);
	            pvShow(p,FRAME6);
	            d->comboSet= myText;
	            d->comboCode = 0;
	            if(!myDestStation->isManuallyEdited())
		        {
		            if(myDestStation)
		                delete myDestStation;
		        }
	            myDestStation = new station();
	            pvSetEditable(p,EDITNOMBRE_A,1);	
	            pvSetEditable(p,EDITDIREC_A,1);
	            pvSetEditable(p,EDITPRO_A,1);
	            pvSetEditable(p,EDITNIF_A,1);
	                pvSetEditable(p,EDITCA_A,1);
	            pvSetEditable(p,EDITMUNI_A,1);
	            pvSetEditable(p,EDITNIMA_A,1);
	            pvSetEditable(p,EDITREG_A,1);
	            pvSetEditable(p,EDITCP_A,1);
	        }
	        else
	        {
	            std::cout << "estamos en estacion:" << myText<< std::endl;
                pvHide(p,FRAME6RED_A);
	            d->comboSet =  myText;
	            size_t posCode = myText.find_last_of(" ");
	            try
		        {
		            d->comboCode = std::stol(myText.substr(posCode+1));
		        }
	            catch(...)
		        {
		            std::cout << "in Mask8_slots.h, cant convert!" << myText.substr(posCode+1) << std::endl;
		            d->comboCode = 0;
		        }
	            if(myDestStation)
		            delete myDestStation;
	            myDestStation = new station(d->comboCode,localDatabase);
	            saveStation(p, d, formDI, myDestStation);
	            // check automatic changes in other DI fields
	            formDI->setAllDiData(localDatabase, NULL, DEF_BIORECICLAJE_CODE, DEF_TRANS_CODE);
	        }
	        refStationData(p,d,myDestStation);
	    }      
    }
    if(id == EDITNOMBRE_A)
        myDestStation->setName(myText);
    else if(id == EDITDIREC_A)
        myDestStation->setAddress(myText);
    else if(id == EDITPRO_A)
        myDestStation->setProvence(myText);
    else if(id == EDITCA_A)
        myDestStation->setRegion(myText);
    else if(id == EDITMUNI_A)
        myDestStation->setCity(myText);
    else if(id == EDITNIF_A)
        myDestStation->setNif(myText);
    else if(id == EDITNIMA_A)
	    myDestStation->setNima(myText);
    else if(id == EDITREG_A)
	    myDestStation->setNumIns(myText);
    else if(id == EDITCP_A)
    {
 	    try             			
	    {
	        myDestStation->setZip(std::stol(myText));
	    }
	    catch(...)
	    {
	        myDestStation->setZip(0);
	    }
    }
    else if(id == EDITDR_A)
      formDI->setDepDestStationDR(myText);

    //Check para quitar el frame rojo
    if(myDestStation->getCode() == 0 && (myDestStation->getName().empty() || myDestStation->getAddress().empty() || myDestStation->getProvence().empty() || myDestStation->getNif().empty() || myDestStation->getRegion().empty() || myDestStation->getCity().empty() || myDestStation->getNima().empty() || myDestStation->getNumIns().empty() || myDestStation->getZip() == 0 ))
	    pvShow(p,FRAME6RED_A);
	else
	    pvHide(p,FRAME6RED_A);
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
