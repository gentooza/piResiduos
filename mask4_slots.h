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
//# mask4_slots.h for ProcessViewServer created: vie mar 17 12:33:32 2017
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//# PANTALLA DE ENTRADAS PT!!! BIORRECICLAJE
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
extern std::vector <CAMERA_DATA> cameras;
extern RESOURCES myResources;
extern SYNC_DATA my_ssh_syncro_data;
extern SYNC_DATA my_syncro_data;
extern GLOBAL_DATA globalConfiguration;

#include "mask4_data.h"
#include "mask_tools.h"
#include "mask4_tools.h"
#include "mask4_stateGUI.h"
#include "mask4_stateWork.h"
#include "mask4_stateNext.h"

extern bascula* testBascula;


static int slotInit(PARAM *p, DATA *d)
{
    if(p == NULL || d == NULL) return -1;

    //
    pvResize(p,0,1910,1020);
    //memset(d,0,sizeof(DATA));
    std::string wholeTitle = getTitle();
    pvSetText(p,LABTYPE,wholeTitle.c_str());

    consoleRefresh(p,d);
    d->camionElegido = -1;
    if(formEntrada == NULL)
    {
        if(!type.compare("PT"))
            formEntrada = new inputForm(PT);
        else
            formEntrada = new inputForm(ET);	
        formEntrada->setState(-99999);
        d->enFutEstado = -99999;
    }
    else
    {
        d->enFutEstado = formEntrada->getState();
        formEntrada->setState(-100);
        d->enFutEstado = -100;
    }
    formEntrada->setOurStation(myStation);
    
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
    //máquina de cambio de estados Entrada PT
    std::cout << "#####DEBUG DESCARGA MATERIAL#####" << std::endl;
    std::cout << "ESTADO ACTUAL:\"" << ((formEntrada)?std::to_string(formEntrada->getState()):"null") << "\", ESTADO FUTURO:\"" << d->enFutEstado << "\""<< std::endl;
    std::cout << "--DATOS ENTRADA A PLANTA--" << std::endl;
    std::cout << "MATRICULA:\"" << (formEntrada?formEntrada->retArrPlate():"null") << "\"";
    std::cout << " TIPO DE MOVIMIENTO:\"" << (formEntrada?std::to_string(formEntrada->retArrMovType()):"null") << "\""; 
    std::cout << " CLIENTE CÓDIGO:\"" <<   (formEntrada?std::to_string(formEntrada->retArrCosCode()):"null")<<"\"";
    std::cout << std::endl;
    std::cout << "PRODUCTO CÓDIGO:\"" <<  (formEntrada?std::to_string(formEntrada->retArrProdCode()):"null") << "\" Permitido?:\"" << (formEntrada?(formEntrada->isArrProdPermit()?"si!":"no!"):"null") << "\"";
    std::cout << std::endl;
    std::cout << "INCIDENCIAS:\"" << vectorToString(formEntrada->getInputIncidents(),"  || ")  << std::endl;
    std::cout << "COMENTARIO:\"" << (formEntrada?formEntrada->getInputComment():"null") << "\"" << std::endl;
    std::cout << "CARPETA:\"" << (formEntrada?formEntrada->retArrDiFolder():"null") << std::endl;
    std::cout << "D->COMBOPRODUCTO:" << d->comboProducto << std::endl;
    std::cout << "**********" << std::endl;
    std::cout << "--DATOS SALIDA DE PLANTA--" << std::endl;
    std::cout << " MATRICULA:\"" << (formEntrada?formEntrada->retDepPlate():"null") << "\"";
    std::cout << " TIPO DE MOVIMIENTO:\"" << (formEntrada?std::to_string(formEntrada->retDepMovType()):"null") << "\"";  
    std::cout << " CLIENTE CÓDIGO:\"" <<   (formEntrada?std::to_string(formEntrada->retDepCosCode()):"null")<<"\"";
    std::cout << std::endl;
    std::cout << "PRODUCTO CÓDIGO:\"" <<  (formEntrada?std::to_string(formEntrada->retDepProdCode()):"null") << "\"";
    std::cout << std::endl;
    std::cout << "TRANSPORTISTA:\"" << (formEntrada?std::to_string(formEntrada->retDepDriCode()):"null")  << "\"" << std::endl;
    std::cout << "INCIDENCIAS:\"" << vectorToString(formEntrada->getOutputIncidents(),"||")  << std::endl;
    std::cout << "COMENTARIO:\"" << (formEntrada?formEntrada->getOutputComment():"null") << "\"" << std::endl;
    std::cout << "CARPETA:\"" << (formEntrada?formEntrada->retDepDiFolder():"null") << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "############" << std::endl;
    stateNext(p,d);
    stateWork(p,d);
    //semaphores
    cameraSemaphore(1, -1,globalConfiguration.traffic_lights_enabled);
    cameraSemaphore(2, -1,globalConfiguration.traffic_lights_enabled);
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
  if(id == BUTCAM)
  {
    if(formEntrada->getState()  == 0 || formEntrada->getState()  == 2 || formEntrada->getState()  == 101)
	  {
	    d->plateTaking = 1;
	  }
  }
  else if(id == BUTEDITCAM)
  {
    pvInputDialog(p,BUTEDITCAM,"Inserte valor para la matrícula de entrada:","");
  }
  else if(id == BUTCANCELAR_E1)
  {   
    //std::cout << "DEBUG: formulario cancelado" << std::endl;
    d->cancelar=1;
  }
  else if(id == BUTRETROCEDER_E1)
  {
    d->retroceder=1;
  }
  else if(id == BUTPROCEDER_E1)
  {   
    pvText(p,EDITCOMMENTENT);
    pvText(p,EDITCOMMENTSAL);
    d->proceder=1;
  }
  else if(id == BUT2) // a salidas
  {
    //PT type
    pvText(p,EDITCOMMENTENT);
    pvText(p,EDITCOMMENTSAL);
    show_mask5(p);
  }
  else if(id == BUT3) // a configuración
  {
    pvText(p,EDITCOMMENTENT);
    pvText(p,EDITCOMMENTSAL);
    show_mask2(p);
  }
  else if(id == BUTFIRMAR)
  {
    d->firmar = 1;
  }
  else if(id == BUTPESOENT)
  {
    d->pesaje1 = 1;
  }
  else if(id == BUTEDITPESOENT)
  {
    pvInputDialog(p,BUTEDITPESOENT,"Inserte valor de pesaje en entrada a planta del transporte:","");
  }
  else if(id == BUTPESOTARA)
  {
    d->pesaje2 = 1;
  }
  else if(id == BUTEDITPESOSAL)
  {
    pvInputDialog(p,BUTEDITPESOSAL,"Inserte valor de pesaje en salida de planta del transporte:","");      
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
  else if(id == BUTTEST)
  {
    d->test=1;
  }
  else if(id == BUTSINCRONIZA) //manual SINCRONIZATION
  {
    globalSyncronization(p,d,formEntrada);
    stateGUI(p,d, formEntrada->getState());
    //commons
    popteTransito(p,d,TABLATRANSITO,formEntrada);
  }
  else if(id == BUTCAM_E2)
  {	
    if(formEntrada->getState()  == 1000)
	  {
	    d->plateTaking = 1;
	  }
  }
  else if(id == BUTEDITCAM2)
  {
    pvInputDialog(p,BUTEDITCAM2,"Inserte valor para la matrícula de entrada:","");
  }
  else if(id == BUTDELETRANS)
  {
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
    cameraSemaphore(1,1,1);
  }
  // manual exit trafficlights
  else if(id == BUTSEMSALIDA)
  {
    // enabled force to 1, last parameter
    cameraSemaphore(2,1,1);
  }

  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  if(id == COMBOCLIENTES)
    {
      if(strcmp(text,"ELIJA") && strcmp(text,d->formEnCliente.c_str())) //elegimos uno
	{
	  d->comboCliente = text;
	  pvToolTip(p,id,d->comboCliente.c_str());
	}
      else
	{
	  d->comboCliente.clear();
	  pvToolTip(p,id,"ELIJA");
	}
    }
  else if(id == COMBOPRODUCTOS)
    {
      if(!strcmp(text,"ELIJA")) //deselegimos
	{
	  d->comboProducto.clear();
	}
      else if(!strcmp(text,"MOSTRAR TODOS"))
	{
	  d->comboProducto = text;
	  pvToolTip(p,id,"ELIJA");
	}
      else //hemos definitivamente elegido uno
	{
	  d->comboProducto = text;
	}
    }  
  else if(id == COMBOLERS)
    {
      if(!strcmp(text,"ELIJA")) //des elegimos
	{
	  d->comboProducto2.clear();
	}
      else //hemos definitivamente elegido uno
	{
	  d->comboProducto2 = text;
	}
    }
  else if(id == EDITCLIENTES)
    {
      std::string receivedText = text;
      d->tmpClient = text;
    }
  else if(id == BUTEDITCAM)
    {
      if(strcmp(text,""))
	{
	  std::string receivedText = text;
	  boost::to_upper(receivedText);
	  formEntrada->setArrPlate(receivedText);
	  formEntrada-> incArrPlateEdited(1);
	  pvSetText(p,EDITCAM,receivedText.c_str());
	  d->enFutEstado=0;
	}
    }
    else if(id == BUTEDITPESOENT)
      {
	if(strcmp(text,""))
	  {
	    std::string receivedText = text;
	    long peso = 0;
	    try
	      {
		peso = std::stol(receivedText);
	      }
	    catch(...)
	      {
		std::cout << "*ERROR*: stol falló, mask4_slots.h, en slotTextEvent, intentado transformar:" << receivedText << std::endl;
	      }
	    formEntrada->setArrScaleIn(peso);
	    formEntrada->incArrScaleEdited(1);
	    pvSetText(p,EDITPESOENT,receivedText.c_str());
	  }
      }
    else if(id == BUTEDITCAM2)
    {
      if(strcmp(text,""))
	{
	  std::string receivedText = text;
	  boost::to_upper(receivedText);
	  formEntrada->setDepPlate(receivedText);
	  formEntrada->incDepPlateEdited(1);
	  pvSetText(p,EDITCAM_E2,receivedText.c_str());
	  d->camionElegido = -1;
	}
    }
    else if(id == BUTEDITPESOSAL)
      {
	if(strcmp(text,""))
	  {
	    std::string receivedText = text;
	    long peso = 0;
	    try
	      {
		peso = std::stol(receivedText);
	      }
	    catch(...)
	      {
		std::cout << "*ERROR*: stol falló, mask4_slots.h, en slotTextEvent, intentado transformar:" << receivedText << std::endl;
	      }
	    formEntrada->setDepScaleOut(peso);
	    formEntrada->incDepScaleEdited(1);
	    pvSetText(p,EDITPESOTARA,receivedText.c_str());
	    setPesoSal(p,d, WEIGTH_ANALYSIS, formEntrada);
	    //experimental
	    //always we edit weigth we have to analys it again, state 1020
	    d->enFutEstado=1020;
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
	formEntrada->setStaff(code, localDatabase);
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
	  if(formEntrada->delTransit(d->camionElegido,d->pre_transito_plate, localDatabase, remoteDatabase, remoteDatabaseData.db_host, port, myStation->getCode()))
	    console.push_back("*ERROR* incongruencias en los datos suministrados, el transporte no se borró de tránsito");
	  else
	    {
	      popteTransito(p,d,TABLATRANSITO, formEntrada);
	      d->camionElegido=-1;
	    }
	}
    }
  else if (id== BUTPROCEDER_E1)
    {
      if ( val == MessageBoxOk)
	std::cout << "retorno del cajón y no hacemos nada, si no que volvemos a cargar el estado 1030" << std::endl;
    }
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  std::string myText = text;
  if(id==CHCKAUTMATRI && !myText.compare("(1)")) 
    formEntrada->incArrPlateAuto(1);
  else if(id==CHCKAUTMATRI && !myText.compare("(0)")) 
    formEntrada->incArrPlateAuto(0);
  
  else if(id==CHCKNOREGISTRADO && !myText.compare("(1)")) 
    formEntrada->incArrParticular(1);
  else if(id==CHCKNOREGISTRADO  && !myText.compare("(0)")) 
    formEntrada->incArrParticular(0);
  
  else if(id == CHKFORZARPROD && !myText.compare("(1)"))
    formEntrada->incArrProdFz(1);
  else if(id == CHKFORZARPROD && !myText.compare("(0)"))
    formEntrada->incArrProdFz(0);

  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  else if(id==CHKENTRADA && !strcmp(text,"(1)"))  
    d->entrarDescargar=1;
  else if(id==CHKSALIDA && !strcmp(text,"(1)"))
    d->entrarDescargar=0;
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
      formEntrada->setInputComment(text);
      pvClear(p,EDITCOMMENTENT);
    }
  else if(id==EDITCOMMENTSAL)
    {
      std::string text;
      text = p->clipboard;
      formEntrada->setOutputComment(text);
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
  if((val == 16777220 || val == 16777221) && modifier == 1) //tecla enter por proceso empírico :-e
    {
      //en los estados 10 y 110 se refiere al combobox de clientes
      if(formEntrada->getState() == 10 || formEntrada->getState() == 110)
	{
	  if(strcmp(d->comboCliente.c_str(),"ELIJA") && (strcmp(d->comboCliente.c_str(), formEntrada->retArrCosName().c_str()))) //elegimos uno
	    {
	      formEntrada->setArrCosName(d->comboCliente);	  
	      int pos = isStrInVector(d->allClientes,d->comboCliente.c_str());
	      if(pos >= 0 && pos < d->allClientesCodes.size())
		{
		  try
		    {
		      formEntrada->setArrCosCode(std::stol(d->allClientesCodes.at(pos)));
		    }
		  catch(...)
		    {
		      std::cout << "*ERROR*: stol falló, mask4_slots.h, en slotKeyboardEvent, intentado transformar:" << d->allClientesCodes.at(pos) << std::endl;
		    }
		}
	      else
		std::cout << "*ERROR*: combobox clientes, pos:" << pos <<" allClientesCodes size:"<<  d->allClientesCodes.size() << std::endl;
	      pvToolTip(p,id,d->comboCliente.c_str());
	    }
	    else if(!strcmp(d->comboCliente.c_str(),"ELIJA"))
	    {
	      formEntrada->resetArrCostumer();
	      pvToolTip(p,id,"ELIJA");
	    }
	}
      //states 20 and 120, we have choosen a product related to our client
      else if(formEntrada->getState() == 20 || formEntrada->getState() == 120)
	{
	  std::cout << "COMBO PRODUCTOS VALE:" << d->comboProducto << std::endl;
	  if(d->comboProducto.empty()) //deselegimos
	    formEntrada->resetArrProduct();
	  else if(!d->comboProducto.compare("MOSTRAR TODOS") || !d->comboProducto.compare("MOSTRAR TODOS!")) //hemos definitivamente elegido uno
	    {
	      d->comboProducto = "MOSTRAR TODOS!";
	      std::cout << "se mantiene" << std::endl;
	    }
	  else
	    {
	      formEntrada->setArrProdCode(retCodeFromString(d->comboProducto," "));
	      d->comboProducto.clear();
	      std::cout << "se borra" << std::endl;
	    }
	}
      //states 30 && 130 && 230 ENTER for chosing product
      else if(formEntrada->getState() == 30 || formEntrada->getState() == 130 ||  formEntrada->getState() == 230)
	{
	  if(!d->comboProducto2.compare("ELIJA")) //remove chosen if any
	    formEntrada->resetArrProduct();
	  else //we have chosen
	    formEntrada->setArrProdCode(retCodeFromString(d->comboProducto2," "));
	  //	  d->comboProducto2.clear();
	  std::cout << "product code chosen:" << formEntrada->retArrProdCode() << std::endl;
	}
      //at state 210 is when a client name is via keyboard defined
      else if(formEntrada->getState() == 210)
	d->editClient = d->tmpClient;

    }
  else if(val == Key_F2 && d->f2Loads)
    show_mask5(p);
  else if (val == Key_F3 && d->f3Config)
    show_mask2(p);
  else if(val == Key_F5 && d->f5Toggle && modifier==-1)
    {
      if(d->entrarDescargar)
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
