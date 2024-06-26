/*
This file is part of PixResiduos.

Copyright 2017-2019, Pro Integra SL.
Copyright 2019-2022 Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023-2024 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

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

//***************************************************************************
//                          main.cpp  -  description
//                             -------------------
//  begin            : mié mar 8 12:47:31 2017
//  generated by     : pvdevelop (C) Lehrig Software Engineering
//  email            : lehrig@t-online.de
//***************************************************************************
#include "pvapp.h"
#include <QApplication>

// todo: comment me out. you can insert these objects as extern in your masks.
// Change "modbus"(Change if applicable) and "modbusdaemon_" with the "name" of your file "name.mkmodbus".
//rlModbusClient     modbus(modbusdaemon_MAILBOX,modbusdaemon_SHARED_MEMORY,modbusdaemon_SHARED_MEMORY_SIZE);
//rlSiemensTCPClient siemensTCP(siemensdaemon_MAILBOX,siemensdaemon_SHARED_MEMORY,siemensdaemon_SHARED_MEMORY_SIZE);
//rlPPIClient        ppi(ppidaemon_MAILBOX,ppidaemon_SHARED_MEMORY,ppidaemon_SHARED_MEMORY_SIZE);


const char* sVERSION = "piResiduos v0.3dev (2024xxxx)";


camera* camera1;
bascula * bascula1;
iniProcessor * miIni;
qtDatabase localDatabase;
qtDatabase remoteDatabase;
//smtp mail
myMail * mailClient;

baseForm* formEntrada = NULL;
baseForm* formSalida = NULL;
baseForm* formDI = NULL;


//global data
std::string type;
std::string nombre;
std::vector <std::string> console;
int codigo_estacion;

station * myStation;
RESOURCES myResources;
SYNC_DATA my_ssh_syncro_data;
SYNC_DATA my_syncro_data;

GLOBAL_DATA globalConfiguration;
std::vector <CAMERA_DATA> cameras;
std::vector <BASCULA_DATA> basculas;
MAIL_DATA mailData;
bascula* testBascula;
DATABASE_DATA localDatabaseData;
DATABASE_DATA remoteDatabaseData;
long DEF_BIORECICLAJE_CODE;
long DEF_TRANS_CODE;
float DEF_ERROR_SCALES;

int pvMain(PARAM *p)
{
int ret;

  pvSendVersion(p);
  pvSetCaption(p,sVERSION);
  //pvScreenHint(p,1024,768); // this may be used to automatically set the zoomfactor
  ret = 1;
  pvGetInitialMask(p);
  if(strcmp(p->initial_mask,"mask1") == 0) ret = 1;
  while(1)
  {
    if(trace) printf("show_mask%d\n", ret);
    switch(ret)
    {
      case 10:
        pvStatusMessage(p,-1,-1,-1,"mask10");
        ret = show_mask10(p);
        break;
      case 9:
        pvStatusMessage(p,-1,-1,-1,"mask9");
        ret = show_mask9(p);
        break;
      case 8:
        pvStatusMessage(p,-1,-1,-1,"mask8");
        ret = show_mask8(p);
        break;
      case 7:
        pvStatusMessage(p,-1,-1,-1,"mask7");
        ret = show_mask7(p);
        break;
      case 6:
        pvStatusMessage(p,-1,-1,-1,"mask6");
        ret = show_mask6(p);
        break;
      case 5:
        pvStatusMessage(p,-1,-1,-1,"mask5");
        ret = show_mask5(p);
        break;
      case 4:
        pvStatusMessage(p,-1,-1,-1,"mask4");
        ret = show_mask4(p);
        break;
      case 3:
        pvStatusMessage(p,-1,-1,-1,"mask3");
        ret = show_mask3(p);
        break;
      case 2:
	//pvResize(p,0,1920,1080);
        pvStatusMessage(p,-1,-1,-1,"mask2");
        ret = show_mask2(p);
        break;
      case 1:
	//pvResize(p,0,1920,1080);
        pvStatusMessage(p,-1,-1,-1,"mask1");
        ret = show_mask1(p);
        break;
      default:
        return 0;
    }
  }
}

#ifdef USE_INETD
int main(int ac, char **av)
{
PARAM p;

  pvInit(ac,av,&p);
  /* here you may interpret ac,av and set p->user to your data */
  pvMain(&p);
  return 0;
}
#else  // multi threaded server
int main(int ac, char **av)
{
  QApplication a(ac, av);
  PARAM p;
  int   s;

  pvInit(ac,av,&p);
  /* here you may interpret ac,av and set p->user to your data */
  while(1)
    {
      s = pvAccept(&p);
      if(s != -1) pvCreateThread(&p,s);
    }
  return 0;
}
#endif
