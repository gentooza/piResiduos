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
//# mask2_slots.h for ProcessViewServer created: mié mar 8 13:54:34 2017
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;  //Change if applicable
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;

extern iniProcessor* miIni;
extern std::vector <CAMERA_DATA> cameras;
extern std::vector <BASCULA_DATA> basculas;
extern std::vector <std::string> console;
extern MAIL_DATA mailData;
extern station * myStation;
costumer *ourId;
driver *defTrans;
extern DATABASE_DATA remoteDatabaseData;
extern RESOURCES myResources;
std::vector <station> allStations;
std::vector <costumer> allCostumers;
std::vector <costumer> allTransports;
extern SYNC_DATA my_ssh_syncro_data;
extern SYNC_DATA my_syncro_data;
extern GLOBAL_DATA globalConfiguration;

#include "mask2_data.h"
#include "mask_tools.h"
#include "mask2_tools.h"
#include "mask2_actualiza.h"

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  pvResize(p,0,1910,1020);
  //memset(d,0,sizeof(DATA));
  std::string wholeTitle = getTitle();
  pvSetText(p,LABTYPE,wholeTitle.c_str());

  //stations
  retrieveStations(p);
  popteComboStations(p,COMBOSTATIONS, allStations, 1);
  
  std::vector <std::string> strTipos;
  strTipos.push_back("PT");
  strTipos.push_back("ET");
  strTipos.push_back("D5");
  strTipos.push_back("PL"); 
  populateCombo(p,COMBOSTTYPE, strTipos,0);
  setStationData(p,myStation->getCode(), allStations,1);
  d->selectedStation = myStation->getCode();
  //
  //cameras
  if(globalConfiguration.traffic_lights_enabled)
    pvSetChecked(p,CHCKTRAFFIC,1);
  std::vector <std::string> strCameras;
  strCameras.push_back("posición 1");
  strCameras.push_back("posición 2");
  strCameras.push_back("posición 3");
  strCameras.push_back("posición 4");
  populateCombo(p,COMBOCAMERAS, strCameras,1);

  std::vector <std::string> possibleRelays;
  possibleRelays.push_back("1");
  possibleRelays.push_back("2");
  possibleRelays.push_back("3");
  possibleRelays.push_back("4");
  possibleRelays.push_back("N/A");
  populateCombo(p,COMBORELAY, possibleRelays,0);
  populateCombo(p,COMBORELAYB, possibleRelays,0);
  //
  //basculas
  std::vector <std::string> strBas;
  strBas.push_back("posición 1");
  strBas.push_back("posición 2");
  strBas.push_back("posición 3");
  strBas.push_back("posición 4");

  populateCombo(p,COMBOBAS, strBas,1);

  std::vector <std::string> strBaudios;
  strBaudios.push_back("19200");
  strBaudios.push_back("9600");
  strBaudios.push_back("4800");
  populateCombo(p,COMBOBAUDS, strBaudios,0);

  std::vector <std::string> strParity;
  strParity.push_back("ninguna");
  strParity.push_back("impar");
  strParity.push_back("par");
  populateCombo(p,COMBOPARITY,strParity,0);

  std::vector <std::string> strStop;
  strStop.push_back("1");
  strStop.push_back("1.5");
  strStop.push_back("2");
  populateCombo(p,COMBOSTOP,strStop,0);

  std::vector <std::string> strFlujo;
  strFlujo.push_back("ninguno");
  strFlujo.push_back("software");
  strFlujo.push_back("hardware");
  populateCombo(p,COMBOFLUJO,strFlujo,0);

  d->error_scale = DEF_ERROR_SCALES;
  pvSetText(p,EDITERRPES,std::to_string(DEF_ERROR_SCALES).c_str());
  //
  //SMTP
  d->smtpServer = mailData.smtpServer;
  pvSetText(p,EDITSMTP,mailData.smtpServer.c_str());
  char text[16];
  sprintf(text,"%d",mailData.smtpPort);
  d->smtpPort = mailData.smtpPort;
  pvSetText(p,EDITSMTPPORT,text);
  d->mailUser = mailData.mailUser;
  pvSetText(p,EDITMAIL,mailData.mailUser.c_str());
  d->mailPass = mailData.mailPass;  
  pvSetText(p,EDITMAILPASS,mailData.mailPass.c_str());
  d->mailName = mailData.mailSenderName;  
  pvSetText(p,EDITMAILNAME,mailData.mailSenderName.c_str());
  populateMailRecipients(p,EDITMAILRECIPIENTS,mailData.mailRecipients,"\n");
  d->recipients = vectorToString(mailData.mailRecipients,"\n");
  //
  //our identity
  ourId = NULL;
  retrieveCostumers(p);
  popteComboCostumers(p,COMBOOURID, allCostumers, 1);

  ourId = new costumer(DEF_BIORECICLAJE_CODE,localDatabase);
  setCostumerData(p,ourId->getCode(), allCostumers,1);
  d->selectedId = ourId->getCode();
  // default transport
  defTrans = NULL;
  retrieveTransports(p);
  popteComboCostumers(p,COMBOOURTRANS, allTransports, 1);

  defTrans = new driver(DEF_TRANS_CODE,localDatabase);
  setTransData(p,defTrans->get_code(), allTransports,1);
  d->selectedTrans = defTrans->get_code();
  //
  //printers
  std::vector <std::string> strPrintersPos;
  strPrintersPos.push_back("impresora de DIs");
  strPrintersPos.push_back("impresora de tickets");
  populateCombo(p,COMBOIMP, strPrintersPos,1);
  populateCombo(p, COMBOACTUALIMP, retPrinters(), 1);
  /*
  miIni->retPrinterId(d->actualPrinter);
  if(!d->actualPrinter.empty())
    pvSetText(p,EDITACTUALIMP,d->actualPrinter.c_str());
  */
  //
  //auto-syncronization
  std::string str_minutes = std::to_string(my_syncro_data.minutes);
  d->syncro_minutes = my_syncro_data.minutes;
  pvSetText(p,EDITASYNCROMIN,str_minutes.c_str());
  //
  d->estadoFuturo=-1;
  //triggers
  d->f1Unloads=1;
  d->f2Loads=1;
  
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  std::cout << "estado actual:" << d->estadoActual << std::endl;
  std::cout << "estado futuro:" << d->estadoFuturo << std::endl;
  maquinaEstados(p,d);
  actualizaEstado(p,d);

  if(d->selectedStation == 0)
    pvSetEnabled(p,BUTSETSTATION,0);
  else
    pvSetEnabled(p,BUTSETSTATION,1);

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
 
  cameraSemaphore(1,-1,globalConfiguration.traffic_lights_enabled);
  cameraSemaphore(2,-1,globalConfiguration.traffic_lights_enabled);
  cameraSemaphore(3,-1,globalConfiguration.traffic_lights_enabled);
  cameraSemaphore(4,-1,globalConfiguration.traffic_lights_enabled);
  refreshSemaphores(p,d);
    
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
  if(id == BUT1) // a entradas
    {
      clearMask2();
      show_mask4(p);
    }
  if(id == BUT2) // a salidas
    {
      clearMask2();
      show_mask5(p);
    }
  if(id==BUTSAVEIP) //salvando el ip
    {
      cameras.at(d->camPos).ip = d->editedCamIp;
      miIni->setCamIp(d->camPos+1,cameras.at(d->camPos).ip);
    }
  if(id==BUTSAVEPORT) //salvando el puerto
    {
	  try
	    {
	      cameras.at(d->camPos).port = std::stoi(d->editedCamPort);
	    }
	  catch(...)
	    {
	      cameras.at(d->camPos).port = 0;
	    }
      miIni->setCamPort(d->camPos+1,cameras.at(d->camPos).port);
    }
    if(id==BUTSAVETIMEOUT) //salvando el timeout
    {
	  try
	    {
      	      cameras.at(d->camPos).timeout = std::stoi(d->editedCamTimeout);
	    }
	  catch(...)
	    {
	      cameras.at(d->camPos).timeout  = 0;
	    }

      miIni->setCamTimeout(d->camPos+1,cameras.at(d->camPos).timeout);
    }
    if(id==BUTSAVERELAY) //salvando 
    {      
      cameras.at(d->camPos).relayA = d->chsenCamRelay;
      miIni->setCamRelayA(d->camPos+1,cameras.at(d->camPos).relayA);
      cameras.at(d->camPos).relayB = d->chsenCamRelayB;
      miIni->setCamRelayB(d->camPos+1,cameras.at(d->camPos).relayB);
      if(d->chsenCamRelay == -1)
	pvSetCurrentItem(p,COMBORELAY,4);
      if(d->chsenCamRelayB == -1)
	pvSetCurrentItem(p,COMBORELAYB,4);
    }
 //test
  if(id == BUTTESTCAM) // test camara
    {
      //block gui
      pvSetMovie(p,LOADINGFORM,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGFORM,-2); // restart
      pvShow(p,LOADINGFORM);       
      /**desactive all**/
      toolsDeactivateGUI(p,d,1);
      /**COMMON**/
      toolsSetNAV(p,d,0);
      /**special**/
      pvSetEnabled(p,BUTSINCRONIZA,0);

      std::string plate;
      int ret = useCamera(p, d, d->camPos+1, plate, IMTESTCAM);
      if(!ret)
	{
	  pvSetText(p,EDITTESTCAM,pvtr(plate.c_str()));
	  formEntrada->setArrPlate(plate);
	}
      else
	{
	  console.push_back("*ERROR* imposible recibir matrícula de la cámara");
	  pvSetText(p,EDITTESTCAM,"FALLÓ!");
	  pvSetImage(p,IMTESTCAM,"image/image.jpg");
	}
      //recover gui
      /**special**/
      pvSetEnabled(p,BUTSINCRONIZA,1);
      pvHide(p,LOADINGFORM);
      toolsDeactivateGUI(p,d,0);
      toolsSetNAV(p,d,1);
    }
  if(id==BUTTESTSEMAPHORE) //prueba de semaforo
    {
      cameraSemaphore(d->camPos+1,1,globalConfiguration.traffic_lights_enabled);
      refreshSemaphores(p,d);
    }
  if(id==BUTSAVETTY) //salvando el puerto de comunicación con báscula
    {
      basculas.at(d->basPos).port = d->editedBasPort;
      miIni->setBasPort(d->basPos+1,basculas.at(d->basPos).port);
    }
  if(id==BUTSAVEBAUDS) //salvando 
    {
      basculas.at(d->basPos).bauds = d->chsenBasBauds;
      miIni->setBasBauds(d->basPos+1,basculas.at(d->basPos).bauds);
    }
  if(id==BUTSAVEBASTIMEOUT) //salvando 
    {
      basculas.at(d->basPos).timeout = d->editedBasTimeout;
      miIni->setBasTimeout(d->basPos+1,basculas.at(d->basPos).timeout);
      char value[32];
      sprintf(value,"%d",d->editedBasTimeout);
      pvSetText(p,EDITBASTIMEOUT,value);
    }
  if(id==BUTSAVEBASASK) //salvando 
    {
      basculas.at(d->basPos).ask = d->editedBasAsk;
      miIni->setBasAsk(d->basPos+1,basculas.at(d->basPos).ask);
    }
  if(id==BUTSAVEPARITY) //salvando 
    {
      basculas.at(d->basPos).parity = d->chsenBasParity;
      miIni->setBasParity(d->basPos+1,basculas.at(d->basPos).parity);
    }
  if(id==BUTSAVESTOP) //salvando 
    {
      basculas.at(d->basPos).stopBits = d->chsenBasStopBits;
      miIni->setBasStopBits(d->basPos+1,basculas.at(d->basPos).stopBits);
    }
  if(id==BUTSAVEFLUJO) //salvando 
    {
      basculas.at(d->basPos).ctrl = d->chsenBasFlow;
      miIni->setBasCtrl(d->basPos+1,basculas.at(d->basPos).ctrl);
    }
  if(id==BUTTESTBAS) //test báscula
    {
      //block gui
      pvSetMovie(p,LOADINGFORM,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGFORM,-2); // restart
      pvShow(p,LOADINGFORM);       
      /**desactive all**/
      toolsDeactivateGUI(p,d,1);
      /**COMMON**/
      toolsSetNAV(p,d,0);
      /**special**/
      pvSetEnabled(p,BUTSINCRONIZA,0);
      
      char error[256];
      bascula * testBascula = NULL;
      sprintf(error,"**INFO: probando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, \nparidad:%s , control de flujo:%s y %s bits de parada...",d->basPos+1, basculas.at(d->basPos).port.c_str(),basculas.at(d->basPos).bauds,basculas.at(d->basPos).timeout , basculas.at(d->basPos).ask.c_str(), (basculas.at(d->basPos).parity==0?"ninguna":(basculas.at(d->basPos).parity==1?"impar":"par")),(basculas.at(d->basPos).ctrl==0?"ninguno":(basculas.at(d->basPos).ctrl==1?"software":"hardware")),(basculas.at(d->basPos).stopBits==0?"1":(basculas.at(d->basPos).stopBits==1?"1,5":"2")));
      console.push_back(error);
      testBascula = new bascula(basculas.at(d->basPos).port,basculas.at(d->basPos).bauds);
      if(!basculas.at(d->basPos).ask.empty())
	{
	  testBascula->set_parity(basculas.at(d->basPos).parity);
	  testBascula->set_flowControl(basculas.at(d->basPos).ctrl);
	  testBascula->set_stopBits(basculas.at(d->basPos).stopBits);
	  //no capturamos excepciones
	  testBascula->setCommand(basculas.at(d->basPos).ask);	     
	  std::cout << "INFO: leyendo peso!" << std::endl;
	  char* texto;
	  try
	    {
	      int ret = testBascula->readPeso(basculas.at(d->basPos).timeout,texto);
	      std::cout << "retornamos" << std::endl;
	      std::cout << texto << std::endl;
	      std::string sPeso =  fromBufferAPeso(texto);
	      if(ret)
		{
		  console.push_back("**WARNING: posible TIMEOUT o lectura errónea del puerto");
		}
	      pvSetText(p,EDITTESTBAS,sPeso.c_str());
	    }
	  catch(...)
	    {
	      console.push_back("**ERROR: error de entrada/salida, puerto correcto y conectado?");
	    }
	}
      if(testBascula != NULL)
	delete testBascula;
      
      //recover gui
      /**special**/
      pvSetEnabled(p,BUTSINCRONIZA,1);
      pvHide(p,LOADINGFORM);
      toolsDeactivateGUI(p,d,0);
      toolsSetNAV(p,d,1);
    }
  //SMTP
  if(id == BUTSAVESMTP)
    {
      mailData.smtpServer = d->smtpServer;
      miIni->setSmtpAddr(mailData.smtpServer);
    }
  if(id == BUTSAVESMTPPORT)
    {
      mailData.smtpPort = d->smtpPort;
      miIni->setSmtpPort(mailData.smtpPort);
    }
  if(id == BUTSAVEMAIL)
    {
      mailData.mailUser = d->mailUser;
      miIni->setMailUser(mailData.mailUser);
    }
  if(id == BUTSAVEMAILPASS)
    {
      mailData.mailPass = d->mailPass;
      miIni->setMailPass(mailData.mailPass);
    }
  if(id == BUTSAVEMAILNAME)
    {
      mailData.mailSenderName = d->mailName;
      miIni->setMailName(mailData.mailSenderName);  
    }
  if(id == BUTSAVEMAILRECIPIENTS)
    {
      pvText(p,EDITMAILRECIPIENTS); 
    }
  else if(id == BUTSETSTATION)
    {
      delete myStation;
      myStation = new station(d->selectedStation,localDatabase);
      miIni->setStation(d->selectedStation);
      std::string wholeTitle = getTitle();
      pvSetText(p,LABTYPE,wholeTitle.c_str());
      pvMessageBox(p,BUTSETSTATION,BoxWarning,"Tendrás que sincronizar la abse de datos para aplicar el cambio de estación, ¿desea sincronizar ahora?",MessageBoxYes,MessageBoxNo,0);
    }
  else if(id == BUTSETOURID)
    {
      if(ourId)
	delete ourId;
      
      ourId = new costumer(d->selectedId,localDatabase);
      miIni->setCosCode(d->selectedId);
      DEF_BIORECICLAJE_CODE = d->selectedId;
    }
    else if(id == BUTSETOURTRANS)
    {
      if(defTrans)
	delete defTrans;
      std::cout << "transportista seleccionado: " << d->selectedTrans << std::endl;
      defTrans = new driver(d->selectedTrans,localDatabase);
      miIni->setTrans(d->selectedTrans);
      DEF_TRANS_CODE = d->selectedTrans;
    }
  else if(id == BUTSETIMP)
  {
    if(!strcmp(d->selectedPrinter.c_str(), "impresora de DIs")) 
			miIni->setPrinterId(d->actualPrinter);
		if(!strcmp(d->selectedPrinter.c_str(), "impresora de tickets"))
			miIni->setTicketPrinterId(d->actualPrinter);   
  }
  else if(id == BUTERRPES)
    { 
      DEF_ERROR_SCALES = d->error_scale;
      miIni->setErrScale(DEF_ERROR_SCALES);
    }
  else if(id == BUTSINCRONIZA) //manual SINCRONIZATION
    pvSendUserEvent(p,BUTSINCRONIZA,"");
  else if(id == BUTSAVESYNCROMIN)
    {
      my_syncro_data.minutes = d->syncro_minutes;
      miIni->set_syncro_mins(my_syncro_data.minutes);
    }

  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  if(id == COMBOSTATIONS)
    {
      d->selectedStation = atol(text);
      setStationData(p, d->selectedStation, allStations,0);
    }
  if(id ==COMBOOURID)
    {
      d->selectedId = retCodeFromString(text," ");
      setCostumerData(p, d->selectedId, allCostumers,0); 
    }
  if(id ==COMBOOURTRANS)
    {
      d->selectedTrans = retCodeFromString(text," ");
      setTransData(p, d->selectedTrans, allTransports,0);
    }
  if(id== COMBOCAMERAS)
    {
      if(strcmp(text,"ELIJA"))
	d->selectedCam = text;
      else
	d->selectedCam.clear();
    }
  if(id== COMBOBAS)
    {
      if(strcmp(text,"ELIJA"))
	d->selectedBas = text;
      else
	d->selectedBas.clear();
    }
  if(id== COMBOIMP)
  {
    if(strcmp(text,"ELIJA"))
	    d->selectedPrinter = text;
    else
	    d->selectedPrinter.clear();
  }
  if(id == EDITIP)
    {
      d->editedCamIp = text;
    }
  if(id == EDITPORT)
    {
      d->editedCamPort = text;
    }
  if(id == EDITTIMEOUT)
    {
      d->editedCamTimeout = text;
    }
  if(id == COMBORELAY)
    {
      d->chsenCamRelay = atoi(text);
      if(d->chsenCamRelay == cameras.at(d->camPos).relayB)
	d->chsenCamRelay = -1;
    }
  if(id == COMBORELAYB)
    {
      d->chsenCamRelayB = atoi(text);
      if(d->chsenCamRelayB == cameras.at(d->camPos).relayA)
	d->chsenCamRelayB = -1;
    }
  if(id == EDITTTY)
    {
      d->editedBasPort = text;
    }
  else if(id == EDITERRPES)
    {
      std::string newError = text;
      try
	{
	  d->error_scale = std::stof(newError);
	}
      catch(...)
	{
	  newError = std::to_string(d->error_scale);
	  pvSetText(p,EDITERRPES,newError.c_str());
	}
    }
  if(id == COMBOBAUDS)
    {
      d->chsenBasBauds = atoi(text);
    }
  if(id == EDITBASTIMEOUT)
    {
      d->editedBasTimeout = atoi(text);
    }
  if(id == EDITBASASK)
    {
      d->editedBasAsk = text;
    }
  if(id == COMBOPARITY)
    {
      if(!strcmp(text,"ninguna"))
	d->chsenBasParity = 0;
      else if(!strcmp(text,"impar"))
	d->chsenBasParity = 1;
      else if(!strcmp(text,"par"))
	d->chsenBasParity = 2;      
    }
  if(id == COMBOSTOP)
    {
      if(!strcmp(text,"1"))
	d->chsenBasStopBits = 0;
      else if(!strcmp(text,"1.5"))
	d->chsenBasStopBits = 1;
      else if(!strcmp(text,"2"))
	d->chsenBasStopBits = 2;
    }
  if(id == COMBOFLUJO)
    {
      if(!strcmp(text,"ninguno"))
	d->chsenBasFlow = 0;
      else if(!strcmp(text,"software"))
	d->chsenBasFlow = 1;
      else if(!strcmp(text,"hardware"))
	d->chsenBasFlow = 2;
    }
  //SMTP
  if(id == EDITSMTP)
    d->smtpServer = text;
  if(id == EDITSMTPPORT)
    {
      std::cout << "modificando puerto!" << text << std::endl;
      d->smtpPort = atoi(text);
      if(d->smtpPort < 0)
	d->smtpPort=0;
      if(d->smtpPort > 100000)
	d->smtpPort=100000;
      char newText[32];
      sprintf(newText,"%d",d->smtpPort);
      pvSetText(p,EDITSMTPPORT,newText);
    }
  if(id == EDITMAIL)
    d->mailUser = text;    
  if(id == EDITMAILPASS)
    d->mailPass = text;
  if(id == EDITMAILNAME)
    d->mailName = text;
  else if(id == COMBOACTUALIMP)
  {
    std::string myText = text;
    if(!myText.compare("ELIJA"))
	    d->actualPrinter.clear();
    else
	    d->actualPrinter = myText;
  }
  
  else if(id == EDITASYNCROMIN)
    {
      std::string my_text = text;
      int minutes;
      if(!my_text.empty())
	{
	  try
	    {
	      minutes = std::stoi(my_text);
	    }
	  catch(...)
	    {
	      pvSetText(p,EDITASYNCROMIN,std::to_string(d->syncro_minutes).c_str());
	    }
	}
      if(minutes <0)
	{
	  pvSetText(p,EDITASYNCROMIN,std::to_string(d->syncro_minutes).c_str());	 
	}
      else
	{
	  d->syncro_minutes = minutes;
	}
    }       
 
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  else if(id == BUTSETSTATION)
    if(val ==MessageBoxYes)
      pvSendUserEvent(p,BUTSINCRONIZA,"");
  else if(id == BUTSINCRONIZA) //manual SINCRONIZATION
    pvSendUserEvent(p,BUTSINCRONIZA,"");
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  if(id == CHCKTRAFFIC)
    {
      //text is of type (0) or (1)
      int value = text[1] - '0';
      globalConfiguration.traffic_lights_enabled = value;
      miIni->setTraficLightsEnable(value);
    }
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
  else if(id == EDITMAILRECIPIENTS)
    {
      d->recipients = p->clipboard;
      mailData.mailRecipients = stringToVector(d->recipients,"\n");
      miIni->setMailRecipients(mailData.mailRecipients);  
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

    if(val == Key_F1 && d->f1Unloads) // a entradas
    {
      clearMask2();
      show_mask4(p);
    }
  if(val == Key_F2 && d->f2Loads) // a salidas
    {
      clearMask2();
      show_mask5(p);
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
  if(id == BUTSINCRONIZA)
    {     
      globalSyncronization(p,d);
      actualizaForm(p,d,d->estadoActual);
    }
  return 0;
}
