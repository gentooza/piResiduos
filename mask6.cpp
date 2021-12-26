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
// show_mask6 for ProcessViewServer created: vie mar 17 12:33:32 2017
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
  BUT2,
  CENTRALFORM,
  BUT1234,
  BUT5,
  BUT6,
  BUT78,
  BUT910,
	FRAME1,
	FRAME1ROW0,
	  	LABLER,
	  	EDITLER,
	FRAME1SELEC,
		CHK1_P,
		CHK1_NP,
	FRAME1ROW1,
		LABDI,
		EDITDI,
	FRAME1ROW2,
		LABNOTPRE,
		EDITNOTPRE,
	FRAME1ROW3,
		LABDATEINI,
		EDITDATEINI,
	FRAME4RED,
	FRAME4,
	  FRAME4TITLE,
	    LABFRAME4,
	  FRAME4SELEC,
	    FRAME4MarqueX,
	      LABFRAME4SELEC,
		CHK4_1,
	     	CHK4_2,
	     	CHK4_3,
	     	CHK4_4,
	     	CHK4_5,
	     	CHK4_6,
	  FRAME4ROW1,
	    LABNOMBRE,
	    EDITNOMBRE,
	    LABNIF,
	    EDITNIF,
	  FRAME4ROW2,
	    LABDIREC,
	    EDITDIREC,
	    LABCP,
	    EDITCP,
	  FRAME4ROW3,
	    LABMUNI,
	    EDITMUNI,
	    LABPRO,
	    EDITPRO,
	    LABCA,
	    EDITCA,
	  FRAME4ROW4,
	    LABNIMA,
	    EDITNIMA,
	    LABREG,
	    EDITREG,
	  FRAME4ROW5,
	    LABTFN,
	    EDITTFN,
	    LABEMAIL,
	    EDITEMAIL,
  LABTIME,
  LABDATE,
  OUTPUT,
  LOGOBIO,
  LOGOPRO,
  COMBOCLIENTE,
  LOADINGFORM,
  ID_END_OF_WIDGETS
};

// our mask contains the following widget names
  static const char *widgetName[] = {
  "ID_MAIN_WIDGET",
  "LABTITLE",
  "LABTYPE",
  "BUT1",
  "BUT2",
  "CENTRALFORM",
  "BUT1234",
  "BUT5",
  "BUT6",
  "BUT78",
  "BUT910",
	"FRAME1",
	"FRAME1ROW0",
	  	"LABLER",
	  	"EDITLER",
	"FRAME1SELEC",
		"CHK1_P",
		"CHK1_NP",
	"FRAME1ROW1",
		"LABDI",
		"EDITDI",
	"FRAME1ROW2",
		"LABNOTPRE",
		"EDITNOTPRE",
	"FRAME1ROW3",
		"LABDATEINI",
		"EDITDATEINI",
	"FRAME4RED",
	"FRAME4",
	  "FRAME4TITLE",
	    "LABFRAME4",
	  "FRAME4SELEC",
	   "FRAME4MarqueX",
	    "LABFRAME4SELEC",
		"CHK4_1",
	     	"CHK4_2",
	     	"CHK4_3",
	     	"CHK4_4",
	     	"CHK4_5",
	     	"CHK4_6",
	  "FRAME4ROW1",
	    "LABNOMBRE",
	    "EDITNOMBRE",
	    "LABNIF",
	    "EDITNIF",
	  "FRAME4ROW2",
	    "LABDIREC",
	    "EDITDIREC",
	    "LABCP",
	    "EDITCP",
	  "FRAME4ROW3",
	    "LABMUNI",
	    "EDITMUNI",
	    "LABPRO",
	    "EDITPRO",
	    "LABCA",
	    "EDITCA",
	  "FRAME4ROW4",
	    "LABNIMA",
	    "EDITNIMA",
	    "LABREG",
	    "EDITREG",
	  "FRAME4ROW5",
	    "LABTFN",
	    "EDITTFN",
	    "LABEMAIL",
	    "EDITEMAIL",
  "LABTIME",
  "LABDATE",
  "OUTPUT",
  "LOGOBIO",
  "LOGOPRO",
  "COMBOCLIENTE",
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
  ""};

  static const int widgetType[ID_END_OF_WIDGETS+1] = {
  0,
  TQLabel,
  TQLabel,
  TQPushButton,
  TQPushButton,
  TQFrame,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  TQPushButton,
TQFrame,				//FRAME1,					
TQFrame,					//FRAME1ROW0,
TQLabel,					  	//LABLER,
TQLineEdit,					  	//EDITLER,
TQFrame,					//FRAME1SELEC,
TQRadio,						//CHK1_P,
TQRadio,						//CHK1_NP,
TQFrame,					//FRAME1ROW1,
TQLabel,						//LABDI,
TQLineEdit,						//EDITDI,
TQFrame,					//FRAME1ROW2,
TQLabel,						//LABNOTPRE,
TQLineEdit,						//EDITNOTPRE,
TQFrame,					//FRAME1ROW3,
TQLabel,						//LABDATEINI,
TQLineEdit,						//EDITDATEINI,
	TQFrame,				//FRAME4RED
	TQFrame,  				//Frame 4
  		TQFrame,
  		  TQLabel,
		TQFrame,
		TQFrame,
		  TQLabel,
			TQRadio,
		     	TQRadio,
		     	TQRadio,
		     	TQRadio,
		     	TQRadio,
		     	TQRadio,
  		TQFrame,
		  TQLabel,
		  TQLineEdit,
		  TQLabel,
		  TQLineEdit,
  		TQFrame,
		  TQLabel,
		  TQLineEdit,
		  TQLabel,
		  TQLineEdit,
  		TQFrame,
		  TQLabel,
		  TQLineEdit,
		  TQLabel,
		  TQLineEdit,
		  TQLabel,
		  TQLineEdit,
  		TQFrame,
		  TQLabel,
		  TQLineEdit,
		  TQLabel,
		  TQLineEdit,
  		TQFrame,
		  TQLabel,
		  TQLineEdit,
		  TQLabel,
		  TQLineEdit,
  TQLabel,
  TQLabel,
  TQMultiLineEdit,
  TQImage,
  TQImage,
  TQComboBox,
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
  pvSetGeometry(p,LABTITLE,6,0,220,120);
  pvSetText(p,LABTITLE,pvtr("APTDOS. 1,2,3,4\nDI DEFINITIVO"));
  pvSetFont(p,LABTITLE,"Verdana",16,1,1,0,0);

  pvQLabel(p,LABTYPE,0);
  pvSetGeometry(p,LABTYPE,320,15,800,60);
  pvSetText(p,LABTYPE,pvtr(""));
  pvSetPaletteForegroundColor(p,LABTYPE,90,100,100);
  pvSetFont(p,LABTYPE,"Verdana",30,1,1,0,0);

  pvQPushButton(p,BUT1,0);
  pvSetGeometry(p,BUT1,5,270,135,60);
  pvSetText(p,BUT1,pvtr("ACEPTAR"));
  pvSetFont(p,BUT1,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUT2,0);
  pvSetGeometry(p,BUT2,5,500,135,60);
  pvSetText(p,BUT2,pvtr("CANCELAR"));
  pvSetFont(p,BUT2,"Verdana",13,1,0,0,0);

  pvQFrame(p,CENTRALFORM,0,Panel,Sunken,4,1);
  pvSetGeometry(p,CENTRALFORM,150,100,1740,810);
  pvSetFont(p,CENTRALFORM,"Verdana",12,1,0,0,0);

  pvQPushButton(p,BUT1234,CENTRALFORM);
  pvSetGeometry(p,BUT1234,610,750,160,40);
  pvSetText(p,BUT1234,pvtr("APTDOS 1,2,3,4"));
  pvSetFont(p,BUT1234,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUT5,CENTRALFORM);
  pvSetGeometry(p,BUT5,780,750,100,40);
  pvSetText(p,BUT5,pvtr("APTDO 5"));
  pvSetFont(p,BUT5,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUT6,CENTRALFORM);
  pvSetGeometry(p,BUT6,890,750,100,40);
  pvSetText(p,BUT6,pvtr("APTDO 6"));
  pvSetFont(p,BUT6,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUT78,CENTRALFORM);
  pvSetGeometry(p,BUT78,1000,750,130,40);
  pvSetText(p,BUT78,pvtr("APTDOS 7,8"));
  pvSetFont(p,BUT78,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUT910,CENTRALFORM);
  pvSetGeometry(p,BUT910,1140,750,140,40);
  pvSetText(p,BUT910,pvtr("APTDOS 9,10"));
  pvSetFont(p,BUT910,"Verdana",13,1,0,0,0);

  pvSetEnabled(p,BUT1234,0);
    
  pvQFrame(p,FRAME1,CENTRALFORM,Box,Plain,2,1);
  pvSetGeometry(p,FRAME1,350,50,1100,200);
  pvSetFont(p,FRAME1,"Verdana",12,1,0,0,0);
  pvSetEditable(p,FRAME1,0);

  pvQFrame(p,FRAME1ROW0,FRAME1,Box,Plain,1,1);
  pvSetGeometry(p,FRAME1ROW0,0,0,550,50);
  pvSetPaletteBackgroundColor(p,FRAME1ROW0,220,220,220);
  pvSetFont(p,FRAME1ROW0,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABLER,FRAME1ROW0);
  pvSetGeometry(p,LABLER,10,5,790,40);
  pvSetText(p,LABLER,pvtr("Código LER:"));
  pvSetFont(p,LABLER,"Default",15,1,0,0,0);

  pvQLineEdit(p,EDITLER,FRAME1ROW0);
  pvSetGeometry(p,EDITLER,275,-1,275,50);
  pvSetFont(p,EDITLER,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITLER,0);

  pvQFrame(p,FRAME1SELEC,FRAME1,Box,Plain,1,1);
  pvSetGeometry(p,FRAME1SELEC,550,0,550,50);
  pvSetFont(p,FRAME1SELEC,"Verdana",12,1,0,0,0);

  pvQRadioButton(p,CHK1_P,FRAME1SELEC);
  pvSetGeometry(p,CHK1_P,150,5,200,40);
  pvSetText(p,CHK1_P,pvtr("Peligroso"));
  pvSetFont(p,CHK1_P,"Default",11,0,0,0,0);
  pvSetEditable(p,CHK1_P,0);

  pvQRadioButton(p,CHK1_NP,FRAME1SELEC);
  pvSetGeometry(p,CHK1_NP,300,5,200,40);
  pvSetText(p,CHK1_NP,pvtr("No peligroso"));
  pvSetFont(p,CHK1_NP,"Default",11,0,0,0,0);
  pvSetEditable(p,CHK1_NP,0);

  pvQFrame(p,FRAME1ROW1,FRAME1,Box,Plain,1,1);
  pvSetGeometry(p,FRAME1ROW1,0,50,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME1ROW1,220,220,220);
  pvSetFont(p,FRAME1ROW1,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDI,FRAME1ROW1);
  pvSetGeometry(p,LABDI,10,5,790,40);
  pvSetText(p,LABDI,pvtr("1. Nº de Documento de Identificación:"));
  pvSetFont(p,LABDI,"Default",13,1,0,0,0);

  pvQLineEdit(p,EDITDI,FRAME1ROW1);
  pvSetGeometry(p,EDITDI,550,-1,549,50);
  pvSetFont(p,EDITDI,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDI,0);

  pvQFrame(p,FRAME1ROW2,FRAME1,Box,Plain,1,1);
  pvSetGeometry(p,FRAME1ROW2,0,100,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME1ROW2,220,220,220);
  pvSetFont(p,FRAME1ROW2,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNOTPRE,FRAME1ROW2);
  pvSetGeometry(p,LABNOTPRE,10,5,790,40);
  pvSetText(p,LABNOTPRE,pvtr("2. Nº de Notificación Previa:"));
  pvSetFont(p,LABNOTPRE,"Default",13,1,0,0,0);

  pvQLineEdit(p,EDITNOTPRE,FRAME1ROW2);
  pvSetGeometry(p,EDITNOTPRE,550,-1,549,50);
  pvSetFont(p,EDITNOTPRE,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNOTPRE,0);

  pvQFrame(p,FRAME1ROW3,FRAME1,Box,Plain,1,1);
  pvSetGeometry(p,FRAME1ROW3,0,150,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME1ROW3,220,220,220);
  pvSetFont(p,FRAME1ROW3,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDATEINI,FRAME1ROW3);
  pvSetGeometry(p,LABDATEINI,10,5,790,40);
  pvSetText(p,LABDATEINI,pvtr("3. Fecha de inicio de traslado:"));
  pvSetFont(p,LABDATEINI,"Default",13,1,0,0,0);

  pvQLineEdit(p,EDITDATEINI,FRAME1ROW3);
  pvSetGeometry(p,EDITDATEINI,550,-1,549,50);
  pvSetFont(p,EDITDATEINI,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDATEINI,0);

//Cuadro 4
  pvQComboBox(p,COMBOCLIENTE,CENTRALFORM,0,AtBottom);
  pvSetGeometry(p,COMBOCLIENTE,40,300,300,40);
  pvSetFont(p,COMBOCLIENTE,"Default",12,1,0,0,0);
  pvHide(p,COMBOCLIENTE);
  
  pvHide(p,FRAME4RED);
  pvQFrame(p,FRAME4RED,CENTRALFORM,Box,Plain,3,1);
  pvSetGeometry(p,FRAME4RED,345,295,1110,430);
  pvSetFont(p,FRAME4RED,"Verdana",12,1,0,0,0);
  pvSetPaletteForegroundColor(p,FRAME4RED,216,96,136);
  pvHide(p,FRAME4RED);

  pvQFrame(p,FRAME4,CENTRALFORM,Box,Plain,2,1);
  pvSetGeometry(p,FRAME4,350,300,1100,420);
  pvSetFont(p,FRAME4,"Verdana",12,1,0,0,0);
  pvSetEditable(p,FRAME4,0);

  pvQFrame(p,FRAME4TITLE,FRAME4,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4TITLE,0,0,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME4TITLE,220,220,220);
  pvSetFont(p,FRAME4TITLE,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME4,FRAME4TITLE);
  pvSetGeometry(p,LABFRAME4,10,5,790,40);
  pvSetText(p,LABFRAME4,pvtr("4. INFORMACIÓN RELATIVA AL OPERADOR DEL TRASLADO:"));
  pvSetFont(p,LABFRAME4,"Default",15,1,0,0,0);

  pvQFrame(p,FRAME4SELEC,FRAME4,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4SELEC,0,50,1100,120);
  pvSetFont(p,FRAME4SELEC,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME4MarqueX,FRAME4SELEC,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4MarqueX,0,0,141,120);
  pvSetFont(p,FRAME4MarqueX,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME4SELEC,FRAME4MarqueX);
  pvSetGeometry(p,LABFRAME4SELEC,10,10,160,120);
  pvSetText(p,LABFRAME4SELEC,pvtr("Marque lo\nque proceda:"));
  pvSetFont(p,LABFRAME4SELEC,"Default",12,0,0,0,0);


  pvQRadioButton(p,CHK4_1,FRAME4SELEC);
  pvSetGeometry(p,CHK4_1,200,5,190,60);
  pvSetText(p,CHK4_1,pvtr("1º Productor\ndel residuo"));
  pvSetFont(p,CHK4_1,"Default",11,0,0,0,0);

  pvQRadioButton(p,CHK4_2,FRAME4SELEC);
  pvSetGeometry(p,CHK4_2,450,5,265,60);
  pvSetText(p,CHK4_2,pvtr("2º Gestor del almacén(resi-\nduos procedentes de distintos\nproductores o poseedores)"));
  pvSetFont(p,CHK4_2,"Default",11,0,0,0,0);

  pvQRadioButton(p,CHK4_3,FRAME4SELEC);
  pvSetGeometry(p,CHK4_3,800,5,255,60);
  pvSetText(p,CHK4_3,pvtr("3º Gestor del almacén (en el\ncaso de que se realice desde\nun almacén autorizado)"));
  pvSetFont(p,CHK4_3,"Default",11,0,0,0,0);


  pvQRadioButton(p,CHK4_4,FRAME4SELEC);
  pvSetGeometry(p,CHK4_4,200,65,200,60);
  pvSetText(p,CHK4_4,pvtr("4º Negociante"));
  pvSetFont(p,CHK4_4,"Default",11,0,0,0,0);

  pvQRadioButton(p,CHK4_5,FRAME4SELEC);
  pvSetGeometry(p,CHK4_5,450,65,265,60);
  pvSetText(p,CHK4_5,pvtr("5º Agente"));
  pvSetFont(p,CHK4_5,"Default",11,0,0,0,0);

  pvQRadioButton(p,CHK4_6,FRAME4SELEC);
  pvSetGeometry(p,CHK4_6,800,65,255,60);
  pvSetText(p,CHK4_6,pvtr("6º Poseedor (en los casos en\nque los sujetos anteriores sean"));
  pvSetFont(p,CHK4_6,"Default",11,0,0,0,0);

  pvQFrame(p,FRAME4ROW1,FRAME4,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4ROW1,0,170,1100,50);
  pvSetFont(p,FRAME4ROW1,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNOMBRE,FRAME4ROW1);
  pvSetGeometry(p,LABNOMBRE,10,5,135,40);
  pvSetText(p,LABNOMBRE,pvtr("Razón Social/\nNombre:"));
  pvSetFont(p,LABNOMBRE,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNOMBRE,FRAME4ROW1);
  pvSetGeometry(p,EDITNOMBRE,140,-1,609,50);
  pvSetFont(p,EDITNOMBRE,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNOMBRE,0);

  pvQLabel(p,LABNIF,FRAME4ROW1);
  pvSetGeometry(p,LABNIF,760,5,90,40);
  pvSetText(p,LABNIF,pvtr("N.I.F.:"));
  pvSetFont(p,LABNIF,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIF,FRAME4ROW1);
  pvSetGeometry(p,EDITNIF,860,-1,239,50);
  pvSetFont(p,EDITNIF,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIF,0);  

  pvQFrame(p,FRAME4ROW2,FRAME4,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4ROW2,0,220,1100,50);
  pvSetFont(p,FRAME4ROW2,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDIREC,FRAME4ROW2);
  pvSetGeometry(p,LABDIREC,10,5,135,40);
  pvSetText(p,LABDIREC,pvtr("Dirección:"));
  pvSetFont(p,LABDIREC,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITDIREC,FRAME4ROW2);
  pvSetGeometry(p,EDITDIREC,140,-1,609,50);
  pvSetFont(p,EDITDIREC,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDIREC,0);

  pvQLabel(p,LABCP,FRAME4ROW2);
  pvSetGeometry(p,LABCP,760,5,90,40);
  pvSetText(p,LABCP,pvtr("C.P.:"));
  pvSetFont(p,LABCP,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITCP,FRAME4ROW2);
  pvSetGeometry(p,EDITCP,860,-1,239,50);
  pvSetFont(p,EDITCP,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCP,0);  

  pvQFrame(p,FRAME4ROW3,FRAME4,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4ROW3,0,270,1100,50);
  pvSetFont(p,FRAME4ROW3,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABMUNI,FRAME4ROW3);
  pvSetGeometry(p,LABMUNI,10,5,135,40);
  pvSetText(p,LABMUNI,pvtr("Municipio:"));
  pvSetFont(p,LABMUNI,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITMUNI,FRAME4ROW3);
  pvSetGeometry(p,EDITMUNI,140,-1,240,50);
  pvSetFont(p,EDITMUNI,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITMUNI,0);

  
  pvQLabel(p,LABPRO,FRAME4ROW3);
  pvSetGeometry(p,LABPRO,390,5,150,40);
  pvSetText(p,LABPRO,pvtr("Provincia:"));
  pvSetFont(p,LABPRO,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITPRO,FRAME4ROW3);
  pvSetGeometry(p,EDITPRO,530,-1,220,50);
  pvSetFont(p,EDITPRO,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITPRO,0);  

  pvQLabel(p,LABCA,FRAME4ROW3);
  pvSetGeometry(p,LABCA,760,3,90,50);
  pvSetText(p,LABCA,pvtr("Comunidad\nAutónoma:"));
  pvSetFont(p,LABCA,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITCA,FRAME4ROW3);
  pvSetGeometry(p,EDITCA,860,-1,239,50);
  pvSetFont(p,EDITCA,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCA,0);  

  pvQFrame(p,FRAME4ROW4,FRAME4,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4ROW4,0,320,1100,50);
  pvSetFont(p,FRAME4ROW4,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNIMA,FRAME4ROW4);
  pvSetGeometry(p,LABNIMA,10,5,135,40);
  pvSetText(p,LABNIMA,pvtr("NIMA:"));
  pvSetFont(p,LABNIMA,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIMA,FRAME4ROW4);
  pvSetGeometry(p,EDITNIMA,140,-1,240,50);
  pvSetFont(p,EDITNIMA,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIMA,0);
  
  pvQLabel(p,LABREG,FRAME4ROW4);
  pvSetGeometry(p,LABREG,390,5,150,40);
  pvSetText(p,LABREG,pvtr("Nº inscripción\nen el Registro:"));
  pvSetFont(p,LABREG,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITREG,FRAME4ROW4);
  pvSetGeometry(p,EDITREG,530,-1,569,50);
  pvSetFont(p,EDITREG,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITREG,0);  

  pvQFrame(p,FRAME4ROW5,FRAME4,Box,Plain,1,1);
  pvSetGeometry(p,FRAME4ROW5,0,370,1100,50);
  pvSetFont(p,FRAME4ROW5,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABTFN,FRAME4ROW5);
  pvSetGeometry(p,LABTFN,10,5,135,40);
  pvSetText(p,LABTFN,pvtr("Teléfono:"));
  pvSetFont(p,LABTFN,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITTFN,FRAME4ROW5);
  pvSetGeometry(p,EDITTFN,140,-1,240,50);
  pvSetFont(p,EDITTFN,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITTFN,0);
  
  pvQLabel(p,LABEMAIL,FRAME4ROW5);
  pvSetGeometry(p,LABEMAIL,390,5,250,40);
  pvSetText(p,LABEMAIL,pvtr("Correo\nelectrónico:"));
  pvSetFont(p,LABEMAIL,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITEMAIL,FRAME4ROW5);
  pvSetGeometry(p,EDITEMAIL,530,-1,569,50);
  pvSetFont(p,EDITEMAIL,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITEMAIL,0);  
  
  pvQLabel(p,LABTIME,0);
  pvSetGeometry(p,LABTIME,1630,70,90,20);
  pvSetText(p,LABTIME,pvtr("hh:mm"));
  pvSetFont(p,LABTIME,"Default",10,1,0,0,0);

  pvQLabel(p,LABDATE,0);
  pvSetGeometry(p,LABDATE,1715,70,90,20);
  pvSetText(p,LABDATE,pvtr("dd/MM/yyyy"));
  pvSetFont(p,LABDATE,"Default",10,1,0,0,0);

  pvQMultiLineEdit(p,OUTPUT,0,0,6);
  pvSetGeometry(p,OUTPUT,5,915,1240,85);
  pvSetFont(p,OUTPUT,"Roboto",9,0,0,0,0);

  pvQImage(p,LOGOBIO,0,"image/logo_bioreciclaje_trans.png",&w,&h,&depth);
  pvSetGeometry(p,LOGOBIO,1255,915,275,95);
  pvSetFont(p,LOGOBIO,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,LOGOBIO,pvtr("image/logo_bioreciclaje_trans.png"));

  pvQImage(p,LOGOPRO,0,"image/log_nuevo_completo_transp_red.png",&w,&h,&depth);
  pvSetGeometry(p,LOGOPRO,1545,920,395,95);
  pvSetFont(p,LOGOPRO,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,LOGOPRO,pvtr(""));

  pvQLabel(p,LOADINGFORM,0);
  pvSetGeometry(p,LOADINGFORM,540,220,640,480);
  pvHide(p,LOADINGFORM);

  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask6_slots.h"

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


int show_mask6(PARAM *p)
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
