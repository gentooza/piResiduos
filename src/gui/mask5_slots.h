/*
This file is part of PixResiduos.

Copyright 2017-2018 Prointegra SL.
Copyright 2019-2021 Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

PixResiduos is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PixResiduos is distributed in the hope that it will 
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PixResiduos.  
If not, see <https://www.gnu.org/licenses/>.
*/

//###############################################################
//# mask5_slots.h for ProcessViewServer created: vie mar 17 12:33:39 2017
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//# PANTALLA DE SALIDAS ET!!! BIORRECICLAJE
//###############################################################
// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;  //Change if applicable
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
#include "tableta.h"

extern iniProcessor* miIni;
extern myMail * mailClient;
extern station * myStation;
extern DATABASE_DATA remoteDatabaseData;
extern RESOURCES myResources;
extern SYNC_DATA my_ssh_syncro_data;
extern SYNC_DATA my_syncro_data;
extern GLOBAL_DATA globalConfiguration;
#include <boost/algorithm/string.hpp>
#include "mask5_data.h"
#include "mask_tools.h"
#include "mask5_tools.h"
#include "mask5_stateGUI.h"
#include "mask5_stateNext.h"
#include "mask5_stateWork.h"


extern bascula* testBascula;


static int slotInit(PARAM *p, DATA *d)
{
    if(p == NULL || d == NULL) return -1;
    //memset(d,0,sizeof(DATA));
    pvResize(p,0,1910,1020);
    //memset(d,0,sizeof(DATA));
    std::string wholeTitle = getTitle();
    pvSetText(p,LABTYPE,wholeTitle.c_str());
    consoleRefresh(p,d);
    d->camionElegido = -1;
    if(formSalida == NULL)
    {
        if(!type.compare("PT"))
        formSalida = new outputForm(PT);
        else
        formSalida = new outputForm(ET);
        formSalida->setDepMovType(DEF_MOV_SALIDA);
        formSalida->setState(-99999);
        d->enFutEstado = -99999;
    }
    else
    {
        d->enFutEstado = formSalida->getState();
        formSalida->setState(-100); 
        d->enFutEstado = -100;  
    }
    formSalida->setOurStation(myStation);
    formSalida->setErrorScale(DEF_ERROR_SCALES);
        
    //reset triggers  
    d->plateTaking=0;
    d->retroceder=0;
    d->cancelar = 0;
    d->pesaje1 = 0;
    d->pesaje2 = 0;
    d->firmar = 0;
    d->proceder=0;
    d->test=0;
    d->editDI=0;
    
    return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
    if(p == NULL || d == NULL) return -1;
    std::cout << "#####DEBUG SALIDA DE MATERIAL#####" << std::endl;
    std::cout << "ESTADO ACTUAL:\"" << (formSalida?std::to_string(formSalida->getState()):"null") << "\", ESTADO FUTURO:\"" << d->enFutEstado << "\""<< std::endl;
    std::cout << "--DATOS ENTRADA A PLANTA--" << std::endl;
    std::cout << "MATRICULA:\"" << (formSalida?formSalida->retArrPlate():"null") << "\"";
    std::cout << " TIPO DE MOVIMIENTO:\"" << (formSalida?std::to_string(formSalida->retArrMovType()):"null") << "\"";
    std::cout << " CLIENTE CÓDIGO:\"" <<   (formSalida?std::to_string(formSalida->retArrCosCode()):"null")<<"\", CLIENTE NOMBRE:\""<<  (formSalida?formSalida->retArrCosName():"null")<<"\"";
    std::cout << std::endl;
    std::cout << "CÓDIGO PRODUCTO:\"" <<  (formSalida?std::to_string(formSalida->retArrProdCode()):"null") << "\" Permitido?:\"" << (formSalida?(formSalida->isArrProdPermit()?"si!":"no!"):"null") << "\" ," ;
    std::cout <<  std::endl;
    std::cout << "INCIDENCIAS:\"" << vectorToString(formSalida->getInputIncidents(),"  || ")  << std::endl;
    std::cout << "COMENTARIO:\"" << (formSalida?formSalida->getInputComment():"null") << "\"" << std::endl;
    std::cout << "CARPETA:\"" << (formSalida?formSalida->retArrDiFolder():"null") << std::endl;  
    std::cout << "**********" << std::endl;
    std::cout << "--DATOS SALIDA DE PLANTA--" << std::endl;
    std::cout << "MATRICULA:\"" << (formSalida?formSalida->retDepPlate():"null") << "\"";
    std::cout << " TIPO DE MOVIMIENTO:\"" << (formSalida?std::to_string(formSalida->retDepMovType()):"null") << "\"";
    std::cout << " CÓDIGO CLIENTE:\"" <<   (formSalida?std::to_string(formSalida->depCostumer->getCode()):"null")<<"\"";
    std::cout << std::endl;
    std::cout << "CÓDIGO PRODUCTO:\"" <<  (formSalida?std::to_string(formSalida->retDepProdCode()):"null") << "\"";
    std::cout << std::endl;
    std::cout << "TRANSPORTISTA:\"" << (formSalida?std::to_string(formSalida->retDepDriCode()):"null")  << "\"" << std::endl;
    //STATIONS
    station* origin = NULL;
    station* destination = NULL;
    formSalida->retDepOriginStation(origin);
    formSalida->retDepDestinationStation(destination); 
    std::cout << "ORIGEN:" << std::to_string(origin->getCode()) << "  DESTINATION:" << std::to_string(destination->getCode()) << std::endl;
    if (origin)
        delete origin;
    if(destination)
        delete destination;
    //
  std::cout << "INCIDENCIAS:\"" << vectorToString(formSalida->getOutputIncidents(),"||")  << std::endl;
  std::cout << "COMENTARIO:\"" << (formSalida?formSalida->getOutputComment():"null") << "\"" << std::endl;
  std::cout << "CARPETA:\"" << (formSalida?formSalida->retDepDiFolder():"null") << std::endl;
  std::cout << "----" << std::endl;
  std::cout << "############" << std::endl;
  //maquina de estados
  stateNext(p,d);
  stateWork(p,d);
  //semaphores
  cameraSemaphore(3, -1,globalConfiguration.traffic_lights_enabled);
  cameraSemaphore(4, -1,globalConfiguration.traffic_lights_enabled);
  refreshSemaphores(p,d);
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
  if(id == BUT1) // arrivals
  {
    pvText(p,EDITCOMMENTENT);
    pvText(p,EDITCOMMENTSAL);
    //PT type
    show_mask4(p);
  }
  if(id == BUT3) // configuration
  {
    pvText(p,EDITCOMMENTENT);
    pvText(p,EDITCOMMENTSAL);
    show_mask2(p);
  }
  if(id == BUTCAM || id == BUTCAM_E2)
  {	
    d->plateTaking = 1;
  }
  if(id == BUTCANCELAR_E1)
  {	
    //std::cout << "DEBUG: formulario cancelado" << std::endl;
    d->cancelar=1;
  }
  if(id == BUTRETROCEDER_E1)
  {
    d->retroceder=1;
  }
  if(id == BUTPROCEDER_E1)
  {
    pvText(p,EDITCOMMENTENT);
    pvText(p,EDITCOMMENTSAL);
    d->proceder=1;
  }
  if(id == BUTFIRMAR)
  {
    d->firmar = 1;
  }
  if(id == BUTPESOENT)
  {
    d->pesaje1 = 1;
  }
  else if(id == BUTEDITPESOENT)
  {
    pvInputDialog(p,BUTEDITPESOENT,"Inserte valor de pesaje en entrada a planta del transporte:","");
  }
  else if(id == BUTEDITPESOSAL)
  {
    pvInputDialog(p,BUTEDITPESOSAL,"Inserte valor de pesaje en salida de planta del transporte:","");
  }
  else if(id == BUTPESOSAL)
  {
    d->pesaje2 = 1;
  }
  else if (id == BUTRETENER)
  {
    d->retroceder = 1;
  }
  else if(id == BUTEDITDIDEF)
  {
    pvText(p,EDITCOMMENTENT);
    pvText(p,EDITCOMMENTSAL);
    d->editDI = 1;
  }
  else if(id == BUTSETORDER)
  {
    if(d->selectedOrder >=0)
	  {
	    formSalida->setArrMov(formSalida->selOrder(d->selectedOrder));
	    formSalida->setAllArrProductData(localDatabase);
	  }
  }
  else if(id == BUTEDITCAM1)
  {
    pvInputDialog(p,BUTEDITCAM1,"Inserte valor para la matrícula de entrada:","");
  }
  else if(id == BUTEDITCAM2)
  {
    pvInputDialog(p,BUTEDITCAM2,"Inserte valor para la matrícula de salida:","");
  }
  else if(id == BUTTEST)
  {
    d->test=1;
  }
  else if(id == BUTSINCRONIZA) //manual SINCRONIZATION
  {      
    globalSyncronization(p,d,formEntrada);
    formSalida->setOrders(localDatabase, myStation->getCode());
    popteOrders(p,d,TABORDERS,formSalida);
    //commons       
    popteTransito(p,d,TABLATRANSITO,formSalida);
    stateGUI(p,d, formSalida->getState());
  }
  else if(id == BUTDELETRANS)
  {
    std::cout << "BUTDELETRANS: camion elegido:" << d->camionElegido << std::endl;
    if(d->camionElegido >=0 && !d->pre_transito_plate.empty())
	  {
	    std::string message = "¿Desea eliminar el transporte con matrícula/código: " + d->pre_transito_plate + " de la tabla de tránsito interna?";
	    pvMessageBox(p,BUTDELETRANS,BoxWarning,message.c_str(),MessageBoxOk ,MessageBoxCancel,0);
	  }
  }
  // manual entrance trafficlights
  else if(id == BUTSEMENTRADA)
  {
    // enabled force to 1, last parameter
    cameraSemaphore(3,1,1);
  }
  // manual exit trafficlights
  else if(id == BUTSEMSALIDA)
  {
    // enabled force to 1, last parameter
    cameraSemaphore(4,1,1);
  }
  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  else if(id == BUTEDITCAM1)
    {
      if(strcmp(text,""))
	{
	  std::string receivedText = text;
	  boost::to_upper(receivedText);
	  formSalida->setArrPlate(receivedText);
	  formSalida->incArrPlateEdited(1);
	  pvSetText(p,EDITCAM,receivedText.c_str());
	}
    }
  else if(id == BUTEDITPESOENT)
    {
      if(strcmp(text,""))
	{
	  std::string receivedText = text;
	int peso;
	 try
	    {
	      peso = std::stoi(receivedText);
	    }
	  catch(...)
	    {
	      peso = 0;
	    }
	  formSalida->setArrScaleIn(peso);
	  formSalida->incArrScaleEdited(1);
	  pvSetText(p,EDITPESOENT,receivedText.c_str());
	}
    }
  else if(id == BUTEDITCAM2)
    {
      if(strcmp(text,""))
	{
	  std::string receivedText = text;
	  boost::to_upper(receivedText);
	  formSalida->setDepPlate(receivedText);
	  if(formSalida->retDepMovType() != DEF_MOV_TRANSFER)
	    formSalida->incDepPlateEdited(1);
	  else
	    formSalida->incDepPlateEdited(0);
	  pvSetText(p,EDITCAM_E2,receivedText.c_str());
	  d->camionElegido = -1;
	}
    }
  else if(id == BUTEDITPESOSAL)
    {
      if(strcmp(text,""))
	{
	  std::string receivedText = text;
	  int peso;
	  try
	    {
	      peso = std::stoi(receivedText);
	    }
	  catch(...)
	    {
	      peso = 0;
	    }
	  formSalida->setDepScaleOut(peso);
	  formSalida->incDepScaleEdited(1);
	  pvSetText(p,EDITPESOSAL,receivedText.c_str());
	  setPesoSal(p,d, WEIGTH_ANALYSIS, formSalida);
	  //experimental
	  //always we edit weigth we have to analys it again, state 1020
	  d->enFutEstado=1120;
	}
	
    }
  else if(id == TABLATRANSITO)
    {
      //	std::cout << "txt pressend on " << text << std::endl;
      std::string new_selection = text;
      new_selection.erase(std::remove(new_selection.begin(), new_selection.end(), '\n'), new_selection.end());
      new_selection.erase(std::remove(new_selection.begin(), new_selection.end(), ' '), new_selection.end());
      std::cout << "PREVIO pre: " << d->pre_transito_plate << " ,post: " << d->post_transito_plate << " ,final: " << d->transito_plate << std::endl;
      if(!d->pre_transito_plate.compare(new_selection)) //double check, caused by double effect when button released
	{
	  if(!d->post_transito_plate.compare(new_selection))
	    d->transito_plate = new_selection;
	  else
	    d->post_transito_plate = new_selection;
	}
    }
  else if(id == BUTPROCEDER_E1)
      {
	std::string temp = text;
	long code = -1;
	try
	  {
	    code = std::stol(temp);
	  }
	catch(...)
	  {	    
	    code = -1;
	  }
	formSalida->setStaff(code, localDatabase);
      }

  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
    if(id == BUTFIRMAR)
    {
      d->firmado = 1;
    }
    else if(id == BUTDELETRANS)
    {
      if (val == MessageBoxOk)
	    {
	      int port;
	      try
	      {
	        port = std::stoi(remoteDatabaseData.db_port);
	      }
	      catch(...)
	      {
	        port = 0;
	      }
	      d->plateElegida.clear();
	      if(formSalida->delTransit(d->camionElegido,d->plateElegida, localDatabase, remoteDatabase, remoteDatabaseData.db_host, port, myStation->getCode()))
	        console.push_back("*ERROR* incongruencias en los datos suministrados, el transporte no se borró de tránsito");
	      else
	      {
	        popteTransito(p,d,TABLATRANSITO, formSalida);
	        d->camionElegido=-1;
	        d->plateElegida.clear();
	      }
      }
    }
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  std::string myText = text;
  if(id == CHKFORZARPROD && !myText.compare("(1)"))
    formSalida->incArrProdFz(1);
  else if (id == CHKFORZARPROD && !myText.compare("(0)"))
    formSalida->incArrProdFz(0);
  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  if(id==CHKENTRADA && !strcmp(text,"(1)")) 
    d->llegada=1;
  else if(id==CHKSALIDA && !strcmp(text,"(1)"))
    d->llegada=0;
  else if(id==CHKTRANSITO && !strcmp(text,"(1)"))
    formSalida->setDepMovType(DEF_MOV_SALIDA);
  else if(id==CHKTRANSFERENCIA && !strcmp(text,"(1)"))
    formSalida->setDepMovType(DEF_MOV_TRANSFER);
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
  if(id == TABORDERS)
    {
      if(val >= 0 && strcmp(text,"(null)"))
	{	
	  d->selectedOrder = val;
	}
    }
  /*DEPRECATED
  else if(id == TABLATRANSITO)
    {
      if(val >= 0 && strcmp(text,"(null)"))
	{
	  d->camionElegido = val;
	  d->plateElegida = text;
	}
	}*/
  else if(id == TABLATRANSITO)
    {
      if(val >= 0 && strcmp(text,"(null)"))
	{
	  d->camionElegido = val;
	  d->post_transito_plate.clear();
	  d->transito_plate.clear();
	  //std::cout << "pressend on " << text << std::endl;
	  std::string new_selection = text;
	  new_selection.erase(std::remove(new_selection.begin(), new_selection.end(), '\n'), new_selection.end());
	  new_selection.erase(std::remove(new_selection.begin(), new_selection.end(), ' '), new_selection.end());	
	  d->pre_transito_plate = new_selection;
	}
    }
  return 0;
}

static int slotClipboardEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == -1 || d == NULL || val < -1000) return -1;
  if(id==EDITCOMMENTENT)
    {
      std::string text;
      text = p->clipboard;
      formSalida->setInputComment(text);
      pvClear(p,EDITCOMMENTENT);
    }
  else if(id==EDITCOMMENTSAL)
    {
      std::string text;
      text = p->clipboard;
      formSalida->setOutputComment(text);
      pvClear(p,EDITCOMMENTSAL);
    }
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
  else if(val == Key_F1 && d->f1Unloads)
    show_mask4(p);
  else if (val == Key_F3 && d->f3Config)
    show_mask2(p);
  else if(val == Key_F5 && d->f5Toggle && modifier==-1)
    {
      if(d->llegada)
	{
	  pvSetChecked(p,CHKSALIDA,1);
	  //d->entrarDescargar=0;
	}
      else
	{
	  pvSetChecked(p,CHKENTRADA,1);
	  //d->entrarDescargar=1;

	}
    }
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
