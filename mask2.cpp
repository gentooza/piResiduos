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

////////////////////////////////////////////////////////////////////////////
//
// show_mask2 for ProcessViewServer created: mié mar 8 13:54:34 2017
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0,
  LABTITLE,
  LABTYPE,
  BUT1,
  BUT3,
  BUT2,
  CENTRALFORM,
  FRAMEGENERAL,
  LABGENERAL,
  COMBOSTATIONS,
  BUTSETSTATION,
  FRAMESTATION,
  LABSNAME,
  EDITSTNAME,
  LABSTYPE,
  COMBOSTTYPE,
  LABSTCODE,
  EDITSTCODE,
  /*FRAME CAMS*******/
  FRAMECAMS,  
  LABCAMS,  
  COMBOCAMERAS,
  CHCKTRAFFIC,
  FFCAMERA,
  LABCURRCAM,
  LABIP,
  EDITIP,
  BUTSAVEIP,
  LABPORT,
  EDITPORT,
  BUTSAVEPORT,
  LABTIMEOUT,
  EDITTIMEOUT,
  BUTSAVETIMEOUT,
  LABRELAY,
  COMBORELAY,
  LABRELAYB,
  COMBORELAYB,
  BUTSAVERELAY,
  BUTTESTCAM,
  EDITTESTCAM,
  IMSEMAPHORE,
  BUTTESTSEMAPHORE,
  IMTESTCAM,
  /****************/
  FRAMEBAS,
  LABBAS,
  COMBOBAS,
  LABERRPES,
  EDITERRPES,
  BUTERRPES,
  FFBAS,
  LABCURRBAS,
  LABTTY,
  EDITTTY,
  BUTSAVETTY,
  LABBAUDS,
  COMBOBAUDS,
  BUTSAVEBAUDS,
  LABBASTIMEOUT,
  EDITBASTIMEOUT,
  BUTSAVEBASTIMEOUT,
  LABBASASK,
  EDITBASASK,
  BUTSAVEBASASK,
  LABPARITY,
  COMBOPARITY,
  BUTSAVEPARITY,
  LABSTOP,
  COMBOSTOP,
  BUTSAVESTOP,
  LABFLUJO,
  COMBOFLUJO,
  BUTSAVEFLUJO,
  BUTTESTBAS,
  EDITTESTBAS,
  FRAMESMTPMAIL,
  LABSMTPMAIL,
  FFSMTPMAIL,
  LABSMTP,
  EDITSMTP,
  BUTSAVESMTP,
  LABSMTPPORT,
  EDITSMTPPORT,
  BUTSAVESMTPPORT,
  LABMAIL,
  EDITMAIL,
  BUTSAVEMAIL,
  LABMAILNAME,
  EDITMAILNAME,
  BUTSAVEMAILNAME,
  LABMAILPASS,
  EDITMAILPASS,
  BUTSAVEMAILPASS,
  LABMAILRECIPIENTS,
  EDITMAILRECIPIENTS,
  BUTSAVEMAILRECIPIENTS,
  // our identity
  FRAMEOURID,
  LABSELECOURID,
  COMBOOURID,
  BUTSETOURID,
  FRAMECODEID,
  LABCODEID,
  EDITCODEID,
  LABNIF,
  EDITNIF,
  // our transport for internal movements
  FRAMEOURTRANS,
  LABSELECOURTRANS,
  COMBOOURTRANS,
  BUTSETOURTRANS,
  FRAMETRANSDATA,
  LABCODETRANS,
  EDITCODETRANS,
  LABNIFTRANS,
  EDITNIFTRANS,
  //PRINTER
  FRAMEIMP,
  LABSELECIMP,
  COMBOIMP,
  BUTSETIMP,
  FRAMEACTUALIMP,
  LABACTUALIMP,
  EDITACTUALIMP,
  /////////
  //AUTOMATIC SYNCRONIZATION
  FRAMESYNCRO,
  LABSYNCRO,
  FRAMESYNCROINT,
  LABSYNCROMIN,
  EDITASYNCROMIN,
  BUTSAVESYNCROMIN,
  //////////////////////////
  BUTSINCRONIZA,
  LABTIME,
  LABDATE,
  OUTPUT,
  LOGOPRO,
  LOGOBIO,
  LOADINGFORM,
  ID_END_OF_WIDGETS
};

// our mask contains the following widget names
  static const char *widgetName[] = {
  "ID_MAIN_WIDGET",
  "LABTITLE",
  "LABTYPE",
  "BUT1",
  "BUT3",
  "BUT2",
  "CENTRALFORM",
  "FRAMEGENERAL",
  "LABGENERAL",
  "COMBOSTATIONS",
  "BUTSETSTATION",
  "FRAMESTATION",
  "LABSNAME",
  "EDITSTNAME",
  "LABSTYPE",
  "COMBOSTTYPE",
  "LABSTCODE",
  "EDITSTCODE",
  /**CAMERAS********/
  "FRAMECAMS",
  "LABCAMS",
  "COMBOCAMERAS",
  "CHCKTRAFFIC",
  "FFCAMERA",
  "LABCURRCAM",
  "LABIP",
  "EDITIP",
  "BUTSAVEIP",
  "LABPORT",
  "EDITPORT",
  "BUTSAVEPORT",
  "LABTIMEOUT",
  "EDITTIMEOUT",
  "BUTSAVETIMEOUT",
  "LABRELAY",
  "COMBORELAY",
  "LABRELAYB",
  "COMBORELAYB",
  "BUTSAVERELAY",
  "BUTTESTCAM",
  "EDITTESTCAM",
  "IMSEMAPHORE",
  "BUTTESTSEMAPHORE",
  "IMTESTCAM",
  /*****************/
    "FRAMEBAS",
  "LABBAS",
  "COMBOBAS",
  "LABERRPES",
  "EDITERRPES",
  "BUTERRPES",
  "FFBAS",
  "LABCURRBAS",
  "LABTTY",
  "EDITTTY",
  "BUTSAVETTY",
  "LABBAUDS",
  "COMBOBAUDS",
  "BUTSAVEBAUDS",
  "LABBASTIMEOUT",
  "EDITBASTIMEOUT",
  "BUTSAVEBASTIMEOUT",
  "LABBASASK",
  "EDITBASASK",
  "BUTSAVEBASASK",
  "LABPARITY",
  "COMBOPARITY",
  "BUTSAVEPARITY",
  "LABSTOP",
  "COMBOSTOP",
  "BUTSAVESTOP",
  "LABFLUJO",
  "COMBOFLUJO",
  "BUTSAVEFLUJO",
  "BUTTESTBAS",
  "EDITTESTBAS",
  "FRAMESMTPMAIL",
    "LABSMTPMAIL",
  "FFSMTPMAIL",
  "LABSMTP",
  "EDITSMTP",
  "BUTSAVESMTP",
  "LABSMTPPORT",
  "EDITSMTPPORT",
  "BUTSAVESMTPPORT",
  "LABMAIL",
  "EDITMAIL",
  "BUTSAVEMAIL",
  "LABMAILNAME",
  "EDITMAILNAME",
  "BUTSAVEMAILNAME",
  "LABMAILPASS",
  "EDITMAILPASS",
  "BUTSAVEMAILPASS",
  "LABMAILRECIPIENTS",
  "EDITMAILRECIPIENTS",
  "BUTSAVEMAILRECIPIENTS",
  // our identity
  "FRAMEOURID",
  "LABSELECOURID",
  "COMBOOURID",
  "BUTSETOURID",
  "FRAMECODEID",
  "LABCODEID",
  "EDITCODEID",
  "LABNIF",
  "EDITNIF",
  // our transport for internal movements
  "FRAMEOURTRANS",
  "LABSELECOURTRANS",
  "COMBOOURTRANS",
  "BUTSETOURTRANS",
  "FRAMETRANSDATA",
  "LABCODETRANS",
  "EDITCODETRANS",
  "LABNIFTRANS",
  "EDITNIFTRANS",
  //PRINTER
  "FRAMEIMP",
  "LABSELECIMP",
  "COMBOIMP",
  "BUTSETIMP",
  "FRAMEACTUALIMP",
  "LABACTUALIMP",
  "EDITACTUALIMP",
  /////////
  //AUTOMATIC SYNCRONIZATION
  "FRAMESYNCRO",
  "LABSYNCRO",
  "FRAMESYNCROINT",
  "LABSYNCROMIN",
  "EDITASYNCROMIN",
  "BUTSAVESYNCROMIN",
  //////////////////////////
  "BUTSINCRONIZA",
  "LABTIME",
  "LABDATE",
  "OUTPUT",
      "LOGOPRO",
  "LOGOBIO",
    "LOADINGFORM",
  "ID_END_OF_WIDGETS",
  ""};

  static const char *toolTip[] = {  
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
   "",
  "",
    "",
  "",
    "",
    "",
    "",
  "",
  "",
  "",
    "",
    "",
  "",
    "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
      "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
   "",
  "",
  "",
  "",
  "",
  "",
   "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
    "",
    "",
  "",
    "",
  "",
    "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
    "",
  "",
    "",
  "",
  "",
    "",
  "",
    "",
  "",
  "",
  "",
    "",
  "",
    "",
    "",
  ""};

  static const char *whatsThis[] = {
  "",
    "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
    "",
  "",
    "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
   "",
  "",
  "",
  "",
      "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
    "",
    "",
  "",
    "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
   "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
    "",
    "",
  "",
    "",
    "",
  "",
    "",
  "",
  "",
    "",
  "",
  "",
    "",
  "",
    "",
  ""};
  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQLabel,
  TQLabel,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQFrame,
  TQFrame,
  TQLabel,
  TQComboBox,
  TQPushButton,
  TQFrame,
  TQLabel,
  TQLineEdit,
  TQLabel,
  TQComboBox,
  TQLabel,
  TQLineEdit,
  /**CAMERAS*******/
  TQFrame,
  TQLabel,
  TQComboBox,
  TQCheck,
  TQFrame,
  TQLabel,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel, //RELAY
  TQComboBox, //RELAY
  TQLabel, //RELAY B
  TQComboBox, //RELAY B
  TQPushButton, //RELAY
  TQPushButton,
  TQLineEdit,
  TQImage, //RED //GREEN
  TQPushButton, //TEST
  TQImage,
  /*****************/
  TQFrame,
  TQLabel,
  TQComboBox,
  TQLabel,        //laberrpes
  TQLineEdit,     //editerrpes
  TQPushButton,  //buterrpes
  TQFrame,
  TQLabel,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel,
  TQComboBox,
  TQPushButton,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel,
  TQComboBox,
  TQPushButton,
    TQLabel,
  TQComboBox,
  TQPushButton,
  TQLabel,
  TQComboBox,
  TQPushButton,
  TQPushButton,
  TQLineEdit,
  TQFrame,
  TQLabel,
  TQFrame,
  TQLabel,
  TQLineEdit,
  TQPushButton,
   TQLabel,
  TQLineEdit,
  TQPushButton, 
   TQLabel,
  TQLineEdit,
  TQPushButton,  
   TQLabel,
  TQLineEdit,
  TQPushButton,   
   TQLabel,
  TQLineEdit,
  TQPushButton, 
   TQLabel,
  TQMultiLineEdit,
    TQPushButton,
  // our identity
  TQFrame,	  //FRAMEOURID,
  TQLabel,	  //LABSELECOURID,
  TQComboBox,	  //COMBOOURID,
  TQPushButton,	  //BUTSETOURID,
  TQFrame,	  //FRAMECODEID,
  TQLabel,	  //LABCODEID,
  TQLineEdit,	  //EDITCODEID,
  TQLabel,	//LABNIF,
  TQLineEdit,	//EDITNIF,
  TQFrame, //FRAMEOURTRANS
  TQLabel,	  //LABSELECOURTRANS,
  TQComboBox,	  //COMBOOURTRANS,
  TQPushButton,	  //BUTSETOURTRANS,
  TQFrame,	  //FRAMETRANSDATA,
  TQLabel,	  //LABCODETRANS,
  TQLineEdit,	  //EDITCODETRANS,
  TQLabel,	//LABNIFTRANS,
  TQLineEdit,	//EDITNIFTRANS,
  //PRINTER
  TQFrame,	//FRAMEIMP
  TQLabel,	//LABSELECIMP
  TQComboBox,	//COMBOIMP
  TQPushButton,	//BUTSETIMP
  TQFrame,	//FRAMEACTUALIMP
  TQLabel,	//LABACTUALIMP
  TQLineEdit,	//EDITACTUALIMP
  /////////
  //AUTOMATIC SYNCRONIZATION
  TQFrame,
  TQLabel,
  TQFrame,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  //////////////////////////
  TQPushButton,
  TQLabel,
  TQLabel,
  TQMultiLineEdit,
      TQImage,
    TQImage,
    TQLabel,
  -1 };

static int generated_defineMask(PARAM *p)
{
  int w,h,depth;

  if(p == NULL) return 1;
  if(widgetName[0] == NULL) return 1; // suppress unused warning
  w = h = depth = strcmp(toolTip[0],whatsThis[0]);
  if(widgetType[0] == -1) return 1;
  if(w==h) depth=0; // fool the compiler
  pvStartDefinition(p,ID_END_OF_WIDGETS);

  pvQLabel(p,LABTITLE,0);
  pvSetGeometry(p,LABTITLE,6,0,200,120);
  pvSetText(p,LABTITLE,pvtr("CONFIGURACIÓN"));
  pvSetFont(p,LABTITLE,"Verdana",16,1,1,0,0);

  pvQLabel(p,LABTYPE,0);
  pvSetGeometry(p,LABTYPE,320,15,800,60);
  pvSetText(p,LABTYPE,pvtr(""));
  pvSetFont(p,LABTYPE,"Verdana",30,1,1,0,0);
  pvSetPaletteForegroundColor(p,LABTYPE,90,100,100);

  pvQPushButton(p,BUT1,0);
  pvSetGeometry(p,BUT1,5,270,135,60);
  pvSetText(p,BUT1,pvtr("ENTRADAS\n(F1)"));
  pvSetFont(p,BUT1,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUT2,0);
  pvSetGeometry(p,BUT2,5,500,135,60);
  pvSetText(p,BUT2,pvtr("SALIDAS\n(F2)"));
  pvSetFont(p,BUT2,"Verdana",13,1,0,0,0);
  
  pvQPushButton(p,BUT3,0);
  pvSetGeometry(p,BUT3,5,710,135,60);
  pvSetText(p,BUT3,pvtr("CONFIGU-\nRACIÓN(F3)"));
  pvSetFont(p,BUT3,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,BUT3,0);

  pvQFrame(p,CENTRALFORM,0,Panel,Sunken,4,1);
  pvSetGeometry(p,CENTRALFORM,150,100,1740,810);
  pvSetFont(p,CENTRALFORM,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAMEGENERAL,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEGENERAL,110,10,375,400);
  pvSetFont(p,FRAMEGENERAL,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABGENERAL,FRAMEGENERAL);
  pvSetGeometry(p,LABGENERAL,10,5,120,30);
  pvSetText(p,LABGENERAL,pvtr("GENERAL"));
  pvSetFontColor(p,LABGENERAL,215,215,215);
  pvSetFont(p,LABGENERAL,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOSTATIONS,FRAMEGENERAL,0,AtBottom);
  pvSetGeometry(p,COMBOSTATIONS,10,40,200,30);
  pvSetFont(p,COMBOSTATIONS,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSETSTATION,FRAMEGENERAL);
  pvSetGeometry(p,BUTSETSTATION,220,35,120,40);
  pvSetText(p,BUTSETSTATION,pvtr("ESTABLECER"));
  
  pvQFrame(p,FRAMESTATION,FRAMEGENERAL,Box,Raised,2,1);
  pvSetGeometry(p,FRAMESTATION,4,80,365,315);
  pvSetFont(p,FRAMESTATION,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSNAME,FRAMESTATION);
  pvSetGeometry(p,LABSNAME,10,5,120,30);
  pvSetText(p,LABSNAME,pvtr("NOMBRE:"));
  pvSetFont(p,LABSNAME,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITSTNAME,FRAMESTATION);
  pvSetGeometry(p,EDITSTNAME,10,35,345,30);
  pvSetText(p,EDITSTNAME,pvtr(""));
  pvSetFont(p,EDITSTNAME,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITSTNAME,0);

  pvQLabel(p,LABSTYPE,FRAMESTATION);
  pvSetGeometry(p,LABSTYPE,10,70,120,30);
  pvSetText(p,LABSTYPE,pvtr("TIPO:"));
  pvSetFont(p,LABSTYPE,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOSTTYPE,FRAMESTATION,0,AtBottom);
  pvSetGeometry(p,COMBOSTTYPE,10,100,100,30);
  pvSetFont(p,COMBOSTTYPE,"Default",12,1,0,0,0);

  pvQLabel(p,LABSTCODE,FRAMESTATION);
  pvSetGeometry(p,LABSTCODE,130,70,120,30);
  pvSetText(p,LABSTCODE,pvtr("CÓDIGO:"));
  pvSetFont(p,LABSTCODE,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITSTCODE,FRAMESTATION);
  pvSetGeometry(p,EDITSTCODE,130,100,100,30);
  pvSetText(p,EDITSTCODE,pvtr(""));
  pvSetFont(p,EDITSTCODE,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITSTCODE,0);

  pvQFrame(p,FRAMECAMS,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECAMS,490,10,590,400);
  pvSetFont(p,FRAMECAMS,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABCAMS,FRAMECAMS);
  pvSetGeometry(p,LABCAMS,10,5,120,30);
  pvSetText(p,LABCAMS,pvtr("CÁMARAS"));
  pvSetFontColor(p,LABCAMS,215,215,215);
  pvSetFont(p,LABCAMS,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOCAMERAS,FRAMECAMS,0,AtBottom);
  pvSetGeometry(p,COMBOCAMERAS,10,40,200,30);
  pvSetFont(p,COMBOCAMERAS,"Default",12,1,0,0,0);

  pvQCheckBox(p,CHCKTRAFFIC,FRAMECAMS);
  pvSetGeometry(p,CHCKTRAFFIC,230,40,320,30);
  pvSetText(p,CHCKTRAFFIC,pvtr("HABILITAR USO DE SEMÁFORO"));
  pvSetFont(p,CHCKTRAFFIC,"Default",12,1,0,0,0);

  pvQFrame(p,FFCAMERA,FRAMECAMS,Box,Raised,2,1);
  pvSetGeometry(p,FFCAMERA,4,80,580,315);
  pvSetFont(p,FFCAMERA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABCURRCAM,FFCAMERA);
  pvSetGeometry(p,LABCURRCAM,10,5,260,30);
  pvSetText(p,LABCURRCAM,pvtr("Elija una"));
  pvSetFont(p,LABCURRCAM,"Default",12,1,1,0,0);

  pvQLabel(p,LABIP,FFCAMERA);
  pvSetGeometry(p,LABIP,10,35,345,30);
  pvSetText(p,LABIP,pvtr("IP: "));
  pvSetFont(p,LABIP,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITIP,FFCAMERA);
  pvSetGeometry(p,EDITIP,10,65,180,30);
  pvSetText(p,EDITIP,pvtr("NUEVA IP"));
  pvSetFont(p,EDITIP,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEIP,FFCAMERA);
  pvSetGeometry(p,BUTSAVEIP,200,63,70,38);
  pvSetPixmap(p,BUTSAVEIP,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEIP,pvtr("salvar"));

  pvQLabel(p,LABPORT,FFCAMERA);
  pvSetGeometry(p,LABPORT,10,100,345,30);
  pvSetText(p,LABPORT,pvtr("PUERTO: "));
  pvSetFont(p,LABPORT,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITPORT,FFCAMERA);
  pvSetGeometry(p,EDITPORT,10,130,180,30);
  pvSetText(p,EDITPORT,pvtr("NUEVO PUERTO"));
  pvSetFont(p,EDITPORT,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEPORT,FFCAMERA);
  pvSetGeometry(p,BUTSAVEPORT,200,128,70,38);
  pvSetPixmap(p,BUTSAVEPORT,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEPORT,pvtr("salvar"));

  pvQLabel(p,LABTIMEOUT,FFCAMERA);
  pvSetGeometry(p,LABTIMEOUT,10,165,345,30);
  pvSetText(p,LABTIMEOUT,pvtr("TIMEOUT: "));
  pvSetFont(p,LABTIMEOUT,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITTIMEOUT,FFCAMERA);
  pvSetGeometry(p,EDITTIMEOUT,10,195,180,30);
  pvSetText(p,EDITTIMEOUT,pvtr("NUEVO TIMEOUT"));
  pvSetFont(p,EDITTIMEOUT,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVETIMEOUT,FFCAMERA);
  pvSetGeometry(p,BUTSAVETIMEOUT,200,193,70,38);
  pvSetPixmap(p,BUTSAVETIMEOUT,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVETIMEOUT,pvtr("salvar"));

  pvQLabel(p,LABRELAY,FFCAMERA);
  pvSetGeometry(p,LABRELAY,10,230,80,30);
  pvSetText(p,LABRELAY,pvtr("RELÉ R:"));
  pvSetFont(p,LABRELAY,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBORELAY,FFCAMERA,0,AtBottom);
  pvSetGeometry(p,COMBORELAY,10,260,80,30);
  pvSetFont(p,COMBORELAY,"Default",12,1,0,0,0);

  pvQLabel(p,LABRELAYB,FFCAMERA);
  pvSetGeometry(p,LABRELAYB,100,230,80,30);
  pvSetText(p,LABRELAYB,pvtr("RELÉ V:"));
  pvSetFont(p,LABRELAYB,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBORELAYB,FFCAMERA,0,AtBottom);
  pvSetGeometry(p,COMBORELAYB,100,260,80,30);
  pvSetFont(p,COMBORELAYB,"Default",12,1,0,0,0);
  
  pvQPushButton(p,BUTSAVERELAY,FFCAMERA);
  pvSetGeometry(p,BUTSAVERELAY,200,258,70,38);
  pvSetPixmap(p,BUTSAVERELAY,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVERELAY,pvtr("salvar"));

  pvQPushButton(p,BUTTESTCAM,FFCAMERA);
  pvSetGeometry(p,BUTTESTCAM,375,10,70,50);
  pvSetText(p,BUTTESTCAM,pvtr("Probar"));
  pvSetFont(p,BUTTESTCAM,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITTESTCAM,FFCAMERA);
  pvSetGeometry(p,EDITTESTCAM,260,10,110,50);
  pvSetFont(p,EDITTESTCAM,"Default",12,1,0,0,0);

  pvQImage(p,IMSEMAPHORE,FFCAMERA,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,IMSEMAPHORE,455,20,40,40);
  pvSetEnabled(p,IMSEMAPHORE,0);

  pvQPushButton(p,BUTTESTSEMAPHORE,FFCAMERA);
  pvSetGeometry(p,BUTTESTSEMAPHORE,500,10,70,50);
  pvSetText(p,BUTTESTSEMAPHORE,pvtr("Probar"));
  pvSetFont(p,BUTTESTSEMAPHORE,"Default",12,1,0,0,0);
  
  pvQImage(p,IMTESTCAM,FFCAMERA,"image/image.jpg",&w,&h,&depth);
  pvSetGeometry(p,IMTESTCAM,285,70,288,216);
  pvSetFont(p,IMTESTCAM,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,IMTESTCAM,pvtr("image/image.jpg"));

  //BASCULA

  pvQFrame(p,FRAMEBAS,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEBAS,1085,10,590,400);
  pvSetFont(p,FRAMEBAS,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABBAS,FRAMEBAS);
  pvSetGeometry(p,LABBAS,10,5,120,30);
  pvSetText(p,LABBAS,pvtr("BÁSCULAS"));
  pvSetFontColor(p,LABBAS,215,215,215);
  pvSetFont(p,LABBAS,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOBAS,FRAMEBAS,0,AtBottom);
  pvSetGeometry(p,COMBOBAS,10,40,200,30);
  pvSetFont(p,COMBOBAS,"Default",12,1,0,0,0);


  pvQLabel(p,LABERRPES,FRAMEBAS);
  pvSetGeometry(p,LABERRPES,240,5,340,30);
  pvSetText(p,LABERRPES,pvtr("ERROR DE PESO PERMITIDO (%)"));
  pvSetFontColor(p,LABERRPES,215,215,215);
  pvSetFont(p,LABERRPES,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITERRPES,FRAMEBAS);
  pvSetGeometry(p,EDITERRPES,240,40,240,30);
  pvSetFont(p,EDITERRPES,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTERRPES,FRAMEBAS);
  pvSetGeometry(p,BUTERRPES,490,38,70,38);
  pvSetPixmap(p,BUTERRPES,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTERRPES,pvtr("salvar"));

  pvQFrame(p,FFBAS,FRAMEBAS,Box,Raised,2,1);
  pvSetGeometry(p,FFBAS,4,80,580,315);
  pvSetFont(p,FFBAS,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABCURRBAS,FFBAS);
  pvSetGeometry(p,LABCURRBAS,10,5,260,30);
  pvSetText(p,LABCURRBAS,pvtr("Elija una"));
  pvSetFont(p,LABCURRBAS,"Default",12,1,1,0,0);

  pvQLabel(p,LABTTY,FFBAS);
  pvSetGeometry(p,LABTTY,10,35,345,30);
  pvSetText(p,LABTTY,pvtr("PUERTO SERIE: "));
  pvSetFont(p,LABTTY,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITTTY,FFBAS);
  pvSetGeometry(p,EDITTTY,10,65,180,30);
  pvSetText(p,EDITTTY,pvtr("NUEVO PUERTO"));
  pvSetFont(p,EDITTTY,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVETTY,FFBAS);
  pvSetGeometry(p,BUTSAVETTY,200,63,70,38);
  pvSetPixmap(p,BUTSAVETTY,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVETTY,pvtr("salvar"));

  pvQLabel(p,LABBAUDS,FFBAS);
  pvSetGeometry(p,LABBAUDS,10,100,345,30);
  pvSetText(p,LABBAUDS,pvtr("BAUDIOS: "));
  pvSetFont(p,LABBAUDS,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOBAUDS,FFBAS,0,AtBottom);
  pvSetGeometry(p,COMBOBAUDS,10,130,180,30);
  pvSetFont(p,COMBOBAUDS,"Default",12,1,0,0,0);
  
  pvQPushButton(p,BUTSAVEBAUDS,FFBAS);
  pvSetGeometry(p,BUTSAVEBAUDS,200,128,70,38);
  pvSetPixmap(p,BUTSAVEBAUDS,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEBAUDS,pvtr("salvar"));

  pvQLabel(p,LABBASTIMEOUT,FFBAS);
  pvSetGeometry(p,LABBASTIMEOUT,10,165,345,30);
  pvSetText(p,LABBASTIMEOUT,pvtr("TIMEOUT: "));
  pvSetFont(p,LABBASTIMEOUT,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITBASTIMEOUT,FFBAS);
  pvSetGeometry(p,EDITBASTIMEOUT,10,195,180,30);
  pvSetText(p,EDITBASTIMEOUT,pvtr("NUEVO TIMEOUT"));
  pvSetFont(p,EDITBASTIMEOUT,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEBASTIMEOUT,FFBAS);
  pvSetGeometry(p,BUTSAVEBASTIMEOUT,200,193,70,38);
  pvSetPixmap(p,BUTSAVEBASTIMEOUT,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEBASTIMEOUT,pvtr("salvar"));

  pvQLabel(p,LABBASASK,FFBAS);
  pvSetGeometry(p,LABBASASK,10,230,345,30);
  pvSetText(p,LABBASASK,pvtr("COMANDO PREGUNTA:"));
  pvSetFont(p,LABBASASK,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITBASASK,FFBAS);
  pvSetGeometry(p,EDITBASASK,10,260,180,30);
  pvSetText(p,EDITBASASK,pvtr("NUEVO COMANDO"));
  pvSetFont(p,EDITBASASK,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEBASASK,FFBAS);
  pvSetGeometry(p,BUTSAVEBASASK,200,258,70,38);
  pvSetPixmap(p,BUTSAVEBASASK,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEBASASK,pvtr("salvar"));

  pvQLabel(p,LABPARITY,FFBAS);
  pvSetGeometry(p,LABPARITY,290,100,345,30);
  pvSetText(p,LABPARITY,pvtr("PARIDAD: "));
  pvSetFont(p,LABPARITY,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOPARITY,FFBAS,0,AtBottom);
  pvSetGeometry(p,COMBOPARITY,290,130,180,30);
  pvSetFont(p,COMBOPARITY,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEPARITY,FFBAS);
  pvSetGeometry(p,BUTSAVEPARITY,480,128,70,38);
  pvSetPixmap(p,BUTSAVEPARITY,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEPARITY,pvtr("salvar"));

  pvQLabel(p,LABSTOP,FFBAS);
  pvSetGeometry(p,LABSTOP,290,165,345,30);
  pvSetText(p,LABSTOP,pvtr("BITS DE PARADA: "));
  pvSetFont(p,LABSTOP,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOSTOP,FFBAS,0,AtBottom);
  pvSetGeometry(p,COMBOSTOP,290,195,180,30);
  pvSetFont(p,COMBOSTOP,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVESTOP,FFBAS);
  pvSetGeometry(p,BUTSAVESTOP,480,193,70,38);
  pvSetPixmap(p,BUTSAVESTOP,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVESTOP,pvtr("salvar"));

  pvQLabel(p,LABFLUJO,FFBAS);
  pvSetGeometry(p,LABFLUJO,290,230,345,30);
  pvSetText(p,LABFLUJO,pvtr("CONTROL DE FLUJO: "));
  pvSetFont(p,LABFLUJO,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOFLUJO,FFBAS,0,AtBottom);
  pvSetGeometry(p,COMBOFLUJO,290,260,180,30);
  pvSetFont(p,COMBOFLUJO,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEFLUJO,FFBAS);
  pvSetGeometry(p,BUTSAVEFLUJO,480,258,70,38);
  pvSetPixmap(p,BUTSAVEFLUJO,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEFLUJO,pvtr("salvar"));

  pvQPushButton(p,BUTTESTBAS,FFBAS);
  pvSetGeometry(p,BUTTESTBAS,440,10,120,50);
  pvSetText(p,BUTTESTBAS,pvtr("Probar"));
  pvSetFont(p,BUTTESTBAS,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITTESTBAS,FFBAS);
  pvSetGeometry(p,EDITTESTBAS,295,10,120,50);
  pvSetFont(p,EDITTESTBAS,"Default",12,1,0,0,0);
  
		//EMAIL
		
  pvQFrame(p,FRAMESMTPMAIL,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMESMTPMAIL,110,425,590,380);
  pvSetFont(p,FRAMESMTPMAIL,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSMTPMAIL,FRAMESMTPMAIL);
  pvSetGeometry(p,LABSMTPMAIL,10,5,280,30);
  pvSetText(p,LABSMTPMAIL,pvtr("CORREO DE INCIDENCIAS"));
  pvSetFontColor(p,LABSMTPMAIL,215,215,215);
  pvSetFont(p,LABSMTPMAIL,"Default",14,1,1,0,0);
  
  pvQFrame(p,FFSMTPMAIL,FRAMESMTPMAIL,Box,Raised,2,1);
  pvSetGeometry(p,FFSMTPMAIL,4,40,580,315);
  pvSetFont(p,FFSMTPMAIL,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSMTP,FFSMTPMAIL);
  pvSetGeometry(p,LABSMTP,10,25,345,30);
  pvSetText(p,LABSMTP,pvtr("SERVIDOR SMTP:"));
  pvSetFont(p,LABSMTP,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITSMTP,FFSMTPMAIL);
  pvSetGeometry(p,EDITSMTP,10,55,180,30);
  pvSetText(p,EDITSMTP,pvtr(""));
  pvSetFont(p,EDITSMTP,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVESMTP,FFSMTPMAIL);
  pvSetGeometry(p,BUTSAVESMTP,200,53,70,38);
  pvSetPixmap(p,BUTSAVESMTP,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVESMTP,pvtr("salvar"));
  
  pvQLabel(p,LABSMTPPORT,FFSMTPMAIL);
  pvSetGeometry(p,LABSMTPPORT,290,25,345,30);
  pvSetText(p,LABSMTPPORT,pvtr("PUERTO SMTP:"));
  pvSetFont(p,LABSMTPPORT,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITSMTPPORT,FFSMTPMAIL);
  pvSetGeometry(p,EDITSMTPPORT,290,55,180,30);
  //pvSetText(p,EDITSMTPPORT,pvtr(""));
  pvSetFont(p,EDITSMTPPORT,"Default",12,1,0,0,0);  

  pvQPushButton(p,BUTSAVESMTPPORT,FFSMTPMAIL);
  pvSetGeometry(p,BUTSAVESMTPPORT,500,53,70,38);
  pvSetPixmap(p,BUTSAVESMTPPORT,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVESMTPPORT,pvtr("salvar"));
  
  pvQLabel(p,LABMAIL,FFSMTPMAIL);
  pvSetGeometry(p,LABMAIL,10,100,345,30);
  pvSetText(p,LABMAIL,pvtr("CORREO:"));
  pvSetFont(p,LABMAIL,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITMAIL,FFSMTPMAIL);
  pvSetGeometry(p,EDITMAIL,10,135,180,30);
  pvSetText(p,EDITMAIL,pvtr(""));
  pvSetFont(p,EDITMAIL,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEMAIL,FFSMTPMAIL);
  pvSetGeometry(p,BUTSAVEMAIL,200,133,70,38);
  pvSetPixmap(p,BUTSAVEMAIL,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEMAIL,pvtr("salvar"));

  pvQLabel(p,LABMAILNAME,FFSMTPMAIL);
  pvSetGeometry(p,LABMAILNAME,10,230,345,30);
  pvSetText(p,LABMAILNAME,pvtr("NOMBRE:"));
  pvSetFont(p,LABMAILNAME,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITMAILNAME,FFSMTPMAIL);
  pvSetGeometry(p,EDITMAILNAME,10,260,180,30);
  pvSetText(p,EDITMAILNAME,pvtr(""));
  pvSetFont(p,EDITMAILNAME,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVEMAILNAME,FFSMTPMAIL);
  pvSetGeometry(p,BUTSAVEMAILNAME,200,258,70,38);
  pvSetPixmap(p,BUTSAVEMAILNAME,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEMAILNAME,pvtr("salvar"));

  pvQLabel(p,LABMAILPASS,FFSMTPMAIL);
  pvSetGeometry(p,LABMAILPASS,10,165,345,30);
  pvSetText(p,LABMAILPASS,pvtr("CONTRASEÑA:"));
  pvSetFont(p,LABMAILPASS,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITMAILPASS,FFSMTPMAIL);
  pvSetGeometry(p,EDITMAILPASS,10,200,180,30);
  pvSetText(p,EDITMAILPASS,pvtr(""));
  pvSetFont(p,EDITMAILPASS,"Default",12,1,0,0,0);
  pvSetEchoMode(p,EDITMAILPASS,2); //password type

  pvQPushButton(p,BUTSAVEMAILPASS,FFSMTPMAIL);
  pvSetGeometry(p,BUTSAVEMAILPASS,200,193,70,38);
  pvSetPixmap(p,BUTSAVEMAILPASS,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEMAILPASS,pvtr("salvar"));
  
  pvQLabel(p,LABMAILRECIPIENTS,FFSMTPMAIL);
  pvSetGeometry(p,LABMAILRECIPIENTS,290,100,345,30);
  pvSetText(p,LABMAILRECIPIENTS,pvtr("CC:(correo por línea)"));
  pvSetFont(p,LABMAILRECIPIENTS,"Default",14,1,1,0,0);

  pvQMultiLineEdit(p,EDITMAILRECIPIENTS,FFSMTPMAIL,1,5);
  pvSetGeometry(p,EDITMAILRECIPIENTS,290,135,200,150);
  pvSetFont(p,EDITMAILRECIPIENTS,"Sans Serif",9,0,0,0,0);

  pvQPushButton(p,BUTSAVEMAILRECIPIENTS,FFSMTPMAIL);
  pvSetGeometry(p,BUTSAVEMAILRECIPIENTS,500,253,70,38);
  pvSetPixmap(p,BUTSAVEMAILRECIPIENTS,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVEMAILRECIPIENTS,pvtr("salvar"));

		//OUR IDENTITY

  pvQFrame(p,FRAMEOURID,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEOURID,705,425,590,185);
  pvSetFont(p,FRAMEOURID,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSELECOURID,FRAMEOURID);
  pvSetGeometry(p,LABSELECOURID,10,5,420,30);
  pvSetText(p,LABSELECOURID,pvtr("SELLECIONE NUESTRA IDENTIDAD"));
  pvSetFontColor(p,LABSELECOURID,215,215,215);
  pvSetFont(p,LABSELECOURID,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOOURID,FRAMEOURID,0,AtBottom);
  pvSetGeometry(p,COMBOOURID,10,40,440,30);
  pvSetFont(p,COMBOOURID,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSETOURID,FRAMEOURID);
  pvSetGeometry(p,BUTSETOURID,460,35,120,40);
  pvSetText(p,BUTSETOURID,pvtr("ESTABLECER"));
  pvSetFont(p,BUTSETOURID,"Verdana",12,1,0,0,0);
  
  pvQFrame(p,FRAMECODEID,FRAMEOURID,Box,Raised,2,1);
  pvSetGeometry(p,FRAMECODEID,4,80,582,75);
  pvSetFont(p,FRAMECODEID,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABCODEID,FRAMECODEID);
  pvSetGeometry(p,LABCODEID,10,5,276,30);
  pvSetText(p,LABCODEID,pvtr("CODIGO CLIENTE:"));
  pvSetFont(p,LABCODEID,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITCODEID,FRAMECODEID);
  pvSetGeometry(p,EDITCODEID,10,35,276,30);
  pvSetText(p,EDITCODEID,pvtr(""));
  pvSetFont(p,EDITCODEID,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITCODEID,0);

  pvQLabel(p,LABNIF,FRAMECODEID);
  pvSetGeometry(p,LABNIF,296,5,276,30);
  pvSetText(p,LABNIF,pvtr("NIF:"));
  pvSetFont(p,LABNIF,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITNIF,FRAMECODEID);
  pvSetGeometry(p,EDITNIF,296,35,276,30);
  pvSetText(p,EDITNIF,pvtr(""));
  pvSetFont(p,EDITNIF,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITNIF,0);

  // OUR TRANSPORT

  pvQFrame(p,FRAMEOURTRANS,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEOURTRANS,705,620,590,185);
  pvSetFont(p,FRAMEOURTRANS,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSELECOURTRANS,FRAMEOURTRANS);
  pvSetGeometry(p,LABSELECOURTRANS,10,5,420,30);
  pvSetText(p,LABSELECOURTRANS,pvtr("SELLECIONE NUESTRO TRANSPORTISTA"));
  pvSetFontColor(p,LABSELECOURTRANS,215,215,215);
  pvSetFont(p,LABSELECOURTRANS,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOOURTRANS,FRAMEOURTRANS,0,AtBottom);
  pvSetGeometry(p,COMBOOURTRANS,10,40,440,30);
  pvSetFont(p,COMBOOURTRANS,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSETOURTRANS,FRAMEOURTRANS);
  pvSetGeometry(p,BUTSETOURTRANS,460,35,120,40);
  pvSetText(p,BUTSETOURTRANS,pvtr("ESTABLECER"));
  pvSetFont(p,BUTSETOURTRANS,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAMETRANSDATA,FRAMEOURTRANS,Box,Raised,2,1);
  pvSetGeometry(p,FRAMETRANSDATA,4,80,582,75);
  pvSetFont(p,FRAMETRANSDATA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABCODETRANS,FRAMETRANSDATA);
  pvSetGeometry(p,LABCODETRANS,10,5,276,30);
  pvSetText(p,LABCODETRANS,pvtr("CODIGO TRANSPORTISTA:"));
  pvSetFont(p,LABCODETRANS,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITCODETRANS,FRAMETRANSDATA);
  pvSetGeometry(p,EDITCODETRANS,10,35,276,30);
  pvSetText(p,EDITCODETRANS,pvtr(""));
  pvSetFont(p,EDITCODETRANS,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITCODETRANS,0);

  pvQLabel(p,LABNIFTRANS,FRAMETRANSDATA);
  pvSetGeometry(p,LABNIFTRANS,296,5,276,30);
  pvSetText(p,LABNIFTRANS,pvtr("NIF:"));
  pvSetFont(p,LABNIFTRANS,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITNIFTRANS,FRAMETRANSDATA);
  pvSetGeometry(p,EDITNIFTRANS,296,35,276,30);
  pvSetText(p,EDITNIFTRANS,pvtr(""));
  pvSetFont(p,EDITNIFTRANS,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITNIFTRANS,0);

  // IMPRESORA

  pvQFrame(p,FRAMEIMP,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEIMP,1300,425,375,160);
  pvSetFont(p,FRAMEIMP,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSELECIMP,FRAMEIMP);
  pvSetGeometry(p,LABSELECIMP,10,5,350,30);
  pvSetText(p,LABSELECIMP,pvtr("SELECCIONE IMPRESORA"));
  pvSetFontColor(p,LABSELECIMP,215,215,215);
  pvSetFont(p,LABSELECIMP,"Default",14,1,1,0,0);

  pvQComboBox(p,COMBOIMP,FRAMEIMP,0,AtBottom);
  pvSetGeometry(p,COMBOIMP,10,40,225,30);
  pvSetFont(p,COMBOIMP,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSETIMP,FRAMEIMP);
  pvSetGeometry(p,BUTSETIMP,245,35,120,40);
  pvSetText(p,BUTSETIMP,pvtr("ESTABLECER"));
  pvSetFont(p,BUTSETIMP,"Verdana",12,1,0,0,0);
  
  pvQFrame(p,FRAMEACTUALIMP,FRAMEIMP,Box,Raised,2,1);
  pvSetGeometry(p,FRAMEACTUALIMP,4,80,365,75);
  pvSetFont(p,FRAMEACTUALIMP,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABACTUALIMP,FRAMEACTUALIMP);
  pvSetGeometry(p,LABACTUALIMP,10,5,350,30);
  pvSetText(p,LABACTUALIMP,pvtr("IMPRESORA ACTUAL:"));
  pvSetFont(p,LABACTUALIMP,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITACTUALIMP,FRAMEACTUALIMP);
  pvSetGeometry(p,EDITACTUALIMP,10,35,345,30);
  pvSetText(p,EDITACTUALIMP,pvtr(""));
  pvSetFont(p,EDITACTUALIMP,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITACTUALIMP,0);

  //AUTOMATIC SYNCRONIZATION
  pvQFrame(p,FRAMESYNCRO,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMESYNCRO,1300,595,375,150);
  pvSetFont(p,FRAMESYNCRO,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSYNCRO,FRAMESYNCRO);
  pvSetGeometry(p,LABSYNCRO,10,5,350,30);
  pvSetText(p,LABSYNCRO,pvtr("SINCRONIZACIÓN AUTOMÁTICA"));
  pvSetFontColor(p,LABSYNCRO,215,215,215);
  pvSetFont(p,LABSYNCRO,"Default",14,1,1,0,0);

  pvQFrame(p,FRAMESYNCROINT,FRAMESYNCRO,Box,Raised,2,1);
  pvSetGeometry(p,FRAMESYNCROINT,4,40,365,105);
  pvSetFont(p,FRAMESYNCROINT,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSYNCROMIN,FRAMESYNCROINT);
  pvSetGeometry(p,LABSYNCROMIN,10,5,350,50);
  pvSetText(p,LABSYNCROMIN,pvtr("INTERVALO EN MINUTOS\n(0 DESACTIVA):"));
  pvSetFont(p,LABSYNCROMIN,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITASYNCROMIN,FRAMESYNCROINT);
  pvSetGeometry(p,EDITASYNCROMIN,10,60,270,30);
  pvSetText(p,EDITASYNCROMIN,pvtr(""));
  pvSetFont(p,EDITASYNCROMIN,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTSAVESYNCROMIN,FRAMESYNCROINT);
  pvSetGeometry(p,BUTSAVESYNCROMIN,280,59,70,38);
  pvSetPixmap(p,BUTSAVESYNCROMIN,"./image/gnome-dev-floppy.png",1);
  pvSetWhatsThis(p,BUTSAVESYNCROMIN,pvtr("salvar"));
  //////////////////////////

  pvQPushButton(p,BUTSINCRONIZA,0);
  pvSetGeometry(p,BUTSINCRONIZA,1400,30,165,60);
  pvSetText(p,BUTSINCRONIZA,pvtr("SINCRONIZAR\nBASE DE DATOS"));
  pvSetFont(p,BUTSINCRONIZA,"Verdana",13,1,0,0,0);

  pvQLabel(p,LABTIME,0);
  pvSetGeometry(p,LABTIME,1630,70,90,20);
  pvSetText(p,LABTIME,pvtr("hh:mm"));
  pvSetFont(p,LABTIME,"Default",10,1,0,0,0);

  pvQLabel(p,LABDATE,0);
  pvSetGeometry(p,LABDATE,1715,70,90,20);
  pvSetText(p,LABDATE,pvtr("dd/MM/yyyy"));
  pvSetFont(p,LABDATE,"Default",10,1,0,0,0);

  pvQMultiLineEdit(p,OUTPUT,0,0,5);
  pvSetGeometry(p,OUTPUT,5,940,1240,70);
  pvSetFont(p,OUTPUT,"Sans Serif",9,0,0,0,0);

  pvQImage(p,LOGOBIO,0,"image/logo_bioreciclaje_trans.png",&w,&h,&depth);
  pvSetGeometry(p,LOGOBIO,1250,935,255,75);
  pvSetFont(p,LOGOBIO,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,LOGOBIO,pvtr("image/image.jpg"));

  pvQImage(p,LOGOPRO,0,"image/log_nuevo_completo_transp_red.png",&w,&h,&depth);
  pvSetGeometry(p,LOGOPRO,1515,940,375,75);
  pvSetFont(p,LOGOPRO,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,LOGOPRO,pvtr("image/image.jpg"));

  pvQLabel(p,LOADINGFORM,0);
  pvSetGeometry(p,LOADINGFORM,540,220,640,480);
  pvHide(p,LOADINGFORM);

  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask2_slots.h"

static int defineMask(PARAM *p)
{
  if(p == NULL) return 1;
  generated_defineMask(p);
  // (todo: add your code here)
  return 0;
}


static int showData(PARAM *p, DATA *d)
{
  if(p == NULL) return 1;
  if(d == NULL) return 1;
  return 0;
}

static int readData(DATA *d) // from shared memory, database or something else
{
  if(d == NULL) return 1;
  // (todo: add your code here)
  return 0;
}


int show_mask2(PARAM *p)
{
  DATA d;
  char event[MAX_EVENT_LENGTH];
  char text[MAX_EVENT_LENGTH];
  char str1[MAX_EVENT_LENGTH];
  int  i,w,h,val,x,y,button,ret;
  float xval, yval;

  defineMask(p);
  //rlSetDebugPrintf(1);
  if((ret=slotInit(p,&d)) != 0) return ret;
  readData(&d); // from shared memory, database or something else
  showData(p,&d);
  pvClearMessageQueue(p);
  while(1)
  {
    pvPollEvent(p,event);
    switch(pvParseEvent(event, &i, text))
    {
      case NULL_EVENT:
        readData(&d); // from shared memory, database or something else
        showData(p,&d);
        if((ret=slotNullEvent(p,&d)) != 0) return ret;
        break;
      case BUTTON_EVENT:
        if(trace) printf("BUTTON_EVENT id=%d\n",i);
        if((ret=slotButtonEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_PRESSED_EVENT:
        if(trace) printf("BUTTON_PRESSED_EVENT id=%d\n",i);
        if((ret=slotButtonPressedEvent(p,i,&d)) != 0) return ret;
        break;
      case BUTTON_RELEASED_EVENT:
        if(trace) printf("BUTTON_RELEASED_EVENT id=%d\n",i);
        if((ret=slotButtonReleasedEvent(p,i,&d)) != 0) return ret;
        break;
      case TEXT_EVENT:
        if(trace) printf("TEXT_EVENT id=%d %s\n",i,text);
        if((ret=slotTextEvent(p,i,&d,text)) != 0) return ret;
        break;
      case SLIDER_EVENT:
        sscanf(text,"(%d)",&val);
        if(trace) printf("SLIDER_EVENT val=%d\n",val);
        if((ret=slotSliderEvent(p,i,&d,val)) != 0) return ret;
        break;
      case CHECKBOX_EVENT:
        if(trace) printf("CHECKBOX_EVENT id=%d %s\n",i,text);
        if((ret=slotCheckboxEvent(p,i,&d,text)) != 0) return ret;
        break;
      case RADIOBUTTON_EVENT:
        if(trace) printf("RADIOBUTTON_EVENT id=%d %s\n",i,text);
        if((ret=slotRadioButtonEvent(p,i,&d,text)) != 0) return ret;
        break;
      case GL_INITIALIZE_EVENT:
        if(trace) printf("you have to call initializeGL()\n");
        if((ret=slotGlInitializeEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_PAINT_EVENT:
        if(trace) printf("you have to call paintGL()\n");
        if((ret=slotGlPaintEvent(p,i,&d)) != 0) return ret;
        break;
      case GL_RESIZE_EVENT:
        sscanf(text,"(%d,%d)",&w,&h);
        if(trace) printf("you have to call resizeGL(w,h)\n");
        if((ret=slotGlResizeEvent(p,i,&d,w,h)) != 0) return ret;
        break;
      case GL_IDLE_EVENT:
        if((ret=slotGlIdleEvent(p,i,&d)) != 0) return ret;
        break;
      case TAB_EVENT:
        sscanf(text,"(%d)",&val);
        if(trace) printf("TAB_EVENT(%d,page=%d)\n",i,val);
        if((ret=slotTabEvent(p,i,&d,val)) != 0) return ret;
        break;
      case TABLE_TEXT_EVENT:
        sscanf(text,"(%d,%d,",&x,&y);
        pvGetText(text,str1);
        if(trace) printf("TABLE_TEXT_EVENT(%d,%d,\"%s\")\n",x,y,str1);
        if((ret=slotTableTextEvent(p,i,&d,x,y,str1)) != 0) return ret;
        break;
      case TABLE_CLICKED_EVENT:
        sscanf(text,"(%d,%d,%d)",&x,&y,&button);
        if(trace) printf("TABLE_CLICKED_EVENT(%d,%d,button=%d)\n",x,y,button);
        if((ret=slotTableClickedEvent(p,i,&d,x,y,button)) != 0) return ret;
        break;
      case SELECTION_EVENT:
        sscanf(text,"(%d,",&val);
        pvGetText(text,str1);
        if(trace) printf("SELECTION_EVENT(column=%d,\"%s\")\n",val,str1);
        if((ret=slotSelectionEvent(p,i,&d,val,str1)) != 0) return ret;
        break;
      case CLIPBOARD_EVENT:
        sscanf(text,"(%d",&val);
        if(trace) printf("CLIPBOARD_EVENT(id=%d)\n",val);
        if((ret=slotClipboardEvent(p,i,&d,val)) != 0) return ret;
        break;
      case RIGHT_MOUSE_EVENT:
        if(trace) printf("RIGHT_MOUSE_EVENT id=%d text=%s\n",i,text);
        if((ret=slotRightMouseEvent(p,i,&d,text)) != 0) return ret;
        break;
      case KEYBOARD_EVENT:
        sscanf(text,"(%d",&val);
        if(trace) printf("KEYBOARD_EVENT modifier=%d key=%d\n",i,val);
        if((ret=slotKeyboardEvent(p,i,&d,val,i)) != 0) return ret;
        break;
      case PLOT_MOUSE_MOVED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_MOVE %f %f\n",xval,yval);
        if((ret=slotMouseMovedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_PRESSED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_PRESSED %f %f\n",xval,yval);
        if((ret=slotMousePressedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case PLOT_MOUSE_RELEASED_EVENT:
        sscanf(text,"(%f,%f)",&xval,&yval);
        if(trace) printf("PLOT_MOUSE_RELEASED %f %f\n",xval,yval);
        if((ret=slotMouseReleasedEvent(p,i,&d,xval,yval)) != 0) return ret;
        break;
      case MOUSE_OVER_EVENT:
        sscanf(text,"%d",&val);
        if(trace) printf("MOUSE_OVER_EVENT %d\n",val);
        if((ret=slotMouseOverEvent(p,i,&d,val)) != 0) return ret;
        break;
      case USER_EVENT:
        if(trace) printf("USER_EVENT id=%d %s\n",i,text);
        if((ret=slotUserEvent(p,i,&d,text)) != 0) return ret;
        break;
      default:
        if(trace) printf("UNKNOWN_EVENT id=%d %s\n",i,text);
        break;
    }
  }
}
