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
//# mask1_slots.h for ProcessViewServer created: mié mar 8 12:47:31 2017
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
extern qtDatabase localDatabase;
extern myMail * mailClient;

extern std::vector <CAMERA_DATA> cameras;
extern std::vector <BASCULA_DATA> basculas;
extern MAIL_DATA mailData;

extern std::vector <std::string> console;
extern station * myStation;
extern RESOURCES myResources;
extern SYNC_DATA my_ssh_syncro_data;
extern SYNC_DATA my_syncro_data;

extern GLOBAL_DATA globalConfiguration;

std::string db_type;
std::string db_host;
std::string db_name;
std::string db_user;
std::string db_pass;
std::string db_port;
extern DATABASE_DATA localDatabaseData;
extern DATABASE_DATA remoteDatabaseData;
extern const char* sVERSION;

rlTime startT;
rlTime endT;

typedef struct // (todo: define your data structure here)
{
}
DATA;
#include "mask_tools.h"

//chequeamos y/o creamos las tablas de biorreciclaje
static int checkSchema(PARAM *p, DATA *d)
{
	int ret = -1;

	return ret;	
}

static int slotInit(PARAM *p, DATA *d)
{
    int ret = -1;
    if(p == NULL || d == NULL) return -1;
    //memset(d,0,sizeof(DATA));
    //pvSetGeometry(p,ID_MAIN_WIDGET,-200,-200,648,96);
    pvResize(p,0,1910,980);
    startT.getLocalTime();
    endT.getLocalTime();
    std::string welcome_message = "** INTIALIZATION piResiduos v:";
    welcome_message += sVERSION;
    welcome_message += " **";
    log_message(welcome_message,1);
    log_message("processing config.ini",1);
    //database! TODO, capture errors
    miIni = new iniProcessor("config.ini");
    int dbport = 0;
    miIni->databaseInfo("database local", localDatabaseData.db_type, localDatabaseData.db_host, localDatabaseData.db_port
                    , localDatabaseData.db_name, localDatabaseData.db_user, localDatabaseData.db_pass);
    if(!localDatabaseData.db_port.empty())
    {
        try
	    {
	        dbport = std::stoi(localDatabaseData.db_port);
	    }
        catch(...)
	    {
	        dbport = 0;
	    }
    }
    std::cout << "OPENING DB:" << localDatabaseData.db_type << " ," << localDatabaseData.db_host << std::endl;
    ret = localDatabase.open(localDatabaseData.db_type.c_str(),localDatabaseData.db_host.c_str(),localDatabaseData.db_name.c_str(),localDatabaseData.db_user.c_str(),localDatabaseData.db_pass.c_str(),dbport);
    miIni->databaseInfo("database remota", remoteDatabaseData.db_type, remoteDatabaseData.local_db_host, remoteDatabaseData.local_db_port
                    , remoteDatabaseData.db_name, remoteDatabaseData.db_user, remoteDatabaseData.db_pass);
    if(!remoteDatabaseData.local_db_port.empty())
    {
        try
	    {
	        dbport = std::stoi(remoteDatabaseData.local_db_port);
	    }
        catch(...)
	    {
	        dbport = 0;
	    }
    }
    else
        dbport=3306;
    miIni->realDatabaseInfo("database remota",  remoteDatabaseData.db_host, remoteDatabaseData.db_port);
    std::cout << "OPENING DB:" <<remoteDatabaseData.db_type<< " ," << remoteDatabaseData.local_db_host << std::endl;
    ret = remoteDatabase.open(remoteDatabaseData.db_type.c_str(),remoteDatabaseData.local_db_host.c_str(),remoteDatabaseData.db_name.c_str(),remoteDatabaseData.db_user.c_str(),remoteDatabaseData.db_pass.c_str(),dbport);
    checkSchema(p,d);
    /* station info */
    syncStations(p);
    DEF_BIORECICLAJE_CODE = 0;
    long station_code = 0;
    miIni->stationInfo(station_code, DEF_BIORECICLAJE_CODE);
    myStation = new station(station_code, localDatabase);
    /*************/
    // our transport info
    DEF_TRANS_CODE = 0;
    miIni->transInfo(DEF_TRANS_CODE);
    //
    //cameras! TODO, capture errors
    globalConfiguration.traffic_lights_enabled = 0;
    globalConfiguration.traffic_lights_enabled = miIni->retTrafficLightsEnable();
    int numCams = miIni->retCamNum();
    std::string ip;
    int port,timeout = 0, relayA, relayB;
    cameras.clear();
    for(int i =1; i <= numCams; i++)
    {
        ret = miIni->retCamData(i,ip,port,timeout, relayA,relayB);
        if(!ret)
	        cameras.push_back({ip,port,timeout,relayA,relayB,{std::chrono::steady_clock::now(),std::chrono::steady_clock::now(),10},1,0});
    }
    //cameraSemaphore(1,0);
    //cameraSemaphore(2,0);
    //cameraSemaphore(3,0);
    //cameraSemaphore(4,0);
    //scales!
    int numBas = miIni->retBasNum();
    std::string bport;
    int bbauds,btimeout = 0;
    std::string ask;
    int parity,stopBits,ctrl = 0;
    basculas.clear();
    for(int i =1; i <= numBas; i++)
    {
        ret = miIni->retBasData(i,bport,bbauds,btimeout,ask,parity,stopBits,ctrl);
        if(!ret)
	        basculas.push_back({bport,bbauds,btimeout,ask,parity,stopBits,ctrl});
    }
    DEF_ERROR_SCALES =  miIni->retErrScale();
    //mail client
    std::string smtpServer;
    std::string mailUser;
    std::string mailPass;
    int smtpPort;
    int smtpEncryption;
    std::vector <std::string> mailRecipients;
    std::string mailSenderName;
    ret = miIni->retMailData(smtpServer,mailUser,mailPass,smtpPort,smtpEncryption,mailRecipients,mailSenderName);
    //if(!ret)
    //  {
    MAIL_DATA tmpMail = {smtpServer,mailUser,mailPass,smtpPort,smtpEncryption,mailRecipients,mailSenderName};
    mailData = tmpMail;
    //  }
    //mail
    mailClient = new myMail();
    mailClient->setSmtpServer(smtpServer);
    mailClient->setSmtpPort(smtpPort);
    mailClient->setSmtpEncryption(smtpEncryption);
    mailClient->setMailUser(mailUser);
    mailClient->setMailPass(mailPass);
    mailClient->setMailSenderName(mailSenderName);
    mailClient->setMailRecipients(mailRecipients);
    //mailClient->sendTestMail(nombre,type);
    //
    if(!ret)
        console.push_back("INFO:configuración cargada sin problema!");
    //TODO
    //loading resources
    myResources.RES_LOADING = "loading.gif";
    pvDownloadFile(p,myResources.RES_LOADING.c_str());		//RES_LOADING
    myResources.RES_IMG_SELECT = "image/select.png";
    pvDownloadFile(p,myResources.RES_IMG_SELECT.c_str());		//RES_IMG_SELECT
    myResources.RES_IMG_DELETE = "image/edit-delete.png";
    pvDownloadFile(p,myResources.RES_IMG_DELETE.c_str());		//RES_IMG_DELETE
    myResources.RES_IMG_GREY = "image/grey.png";
    pvDownloadFile(p,myResources.RES_IMG_GREY.c_str());		//RES_IMG_GREY
    myResources.RES_IMG_IMAGE = "image/image.jpg";
    pvDownloadFile(p,myResources.RES_IMG_IMAGE.c_str());		//RES_IMG_IMAGE
    myResources.RES_IMG_EDIT = "image/edit.png";
    pvDownloadFile(p,myResources.RES_IMG_EDIT.c_str());		//RES_IMG_EDIT
    myResources.RES_IMG_LOGOBIO = "image/logo_bioreciclaje_trans.png";
    pvDownloadFile(p,myResources.RES_IMG_LOGOBIO.c_str());		//RES_IMG_LOGOBIO
    myResources.RES_IMG_LOGOPROINT = "image/log_nuevo_completo_transp_red.png";
    pvDownloadFile(p,myResources.RES_IMG_LOGOPROINT.c_str());		//RES_IMG_LOGOPROINT
    myResources.RES_IMG_RED = "image/red.png";
    pvDownloadFile(p,myResources.RES_IMG_RED.c_str());		//RES_IMG_RED
    myResources.RES_IMG_GREEN = "image/green.png";
    pvDownloadFile(p,myResources.RES_IMG_GREEN.c_str());		//RES_IMG_GREEN
    myResources.RES_IMG_VOID = "image/void.png";
    pvDownloadFile(p,myResources.RES_IMG_VOID.c_str());		//RES_IMG_VOID
    myResources.RES_IMG_DOWN_ARROW = "image/down_arrow.png";
    pvDownloadFile(p,myResources.RES_IMG_DOWN_ARROW.c_str());		//RES_IMG_DOWN_ARROW
    myResources.RES_IMG_UP_ARROW = "image/up_arrow.png";
    pvDownloadFile(p,myResources.RES_IMG_UP_ARROW.c_str());		//RES_IMG_UP_ARROW
    myResources.RES_IMG_MURALBIO = "image/mural_bioreciclaje.jpg";
    pvDownloadFile(p,myResources.RES_IMG_MURALBIO.c_str());		//RES_IMG_MURALBIO
    //
    //syncronization data,
    //TODO to config.ini?
    my_ssh_syncro_data.seconds = 1800; //1/2 hour?
    //mySyncroData.seconds = 120;
    my_ssh_syncro_data.begin = std::chrono::steady_clock::now();
    my_syncro_data.minutes =  miIni->ret_syncro_mins();
    my_syncro_data.begin = std::chrono::steady_clock::now(); 
    //
    log_message("END processing config.ini",1);
    return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  endT = endT - startT;
  if(endT.second >= 3)
    {
      int i = 0;
      myStation->getType(i);
      if(i > MIN_STATION_TYPE && i < MAX_STATION_TYPE)
	show_mask4(p);
      else
	show_mask2(p);
    }

  endT.getLocalTime();
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
