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
  FRAMEPERMISO,
  FRAMEPERMISOENTRADA,
  LABPERMISOENTRADA,
  IMICONPERMISOENTRADA,
  ICONPERM,
  LABPERM,
  ICONFECHCONTR,
  LABFECHCONTR,
  ICONFECHNPRT,
  LABFECHNPRT,
  ICONCB,
  LABCB,
  ICONCPeligro,
  LABCPeligro,
  ICONDCP,
  LABDCP,
  CHKFORZARPROD,
  FRAME7RED,
  FRAME7,
  FRAME7TITLE,
  LABFRAME7,
  FRAME7ROW1,
  LABLER,
  EDITLER,
  LABDESCLER,
  EDITDESCLER,
  LABPESO,
  EDITPESO,
  FRAME7ROW2,
  LABPELIGRO,
  EDITPELIGRO,
  FRAME8RED,
  FRAME8,
  FRAME8TITLE,
  LABFRAME8,
  FRAME8ROW1,
    LABNOMBRE,
    EDITNOMBRE,
    LABNIF,
    EDITNIF,
  FRAME8ROW2,
    LABDIREC,
    EDITDIREC,
    LABCP,
    EDITCP,
  FRAME8ROW3,
    LABMUNI,
    EDITMUNI,
    LABPRO,
    EDITPRO,
    LABCA,
    EDITCA,
  FRAME8ROW4,
    LABNIMA,
    EDITNIMA,
    LABREG,
    EDITREG,
  FRAME8ROW5,
    LABTFN,
    EDITTFN,
    LABEMAIL,
    EDITEMAIL,
  LABTIME,
  LABDATE,
  OUTPUT,
  LOGOBIO,
  LOGOPRO,
  COMBOPRODUCTO,
  COMBOTRANSPORTISTA,
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
  "FRAMEPERMISO",
  "FRAMEPERMISOENTRADA",
  "LABPERMISOENTRADA",
  "IMICONPERMISOENTRADA",
  "ICONPERM",
  "LABPERM",
  "ICONFECHCONTR",
  "LABFECHCONTR",
  "ICONFECHNPRT",
  "LABFECHNPRT",
  "ICONCB",
  "LABCB",
  "ICONCPeligro",
  "LABCPeligro",
  "ICONDCP",
  "LABDCP",
  "CHKFORZARPROD",
	"FRAME7RED",
	"FRAME7",
		  "FRAME7TITLE",
		  "LABFRAME7",
		  "FRAME7ROW1",
		  "LABLER",
		  "EDITLER",
		  "LABDESCLER",
		  "EDITDESCLER",
		  "LABPESO",
		  "EDITPESO",
		  "FRAME7ROW2",
		  "LABPELIGRO",
		  "EDITPELIGRO",
	"FRAME8RED",
 	 "FRAME8",
		  "FRAME8TITLE",
		  "LABFRAME8",
		  "FRAME8ROW1",
		  "LABNOMBRE",
		  "EDITNOMBRE",
		  "LABNIF",
		  "EDITNIF",
		 " FRAME8ROW2",
		   " LABDIREC",
		   " EDITDIREC",
		   " LABCP",
		   " EDITCP",
		  "FRAME8ROW3",
		    "LABMUNI",
		    "EDITMUNI",
		    "LABPRO",
		    "EDITPRO",
		    "LABCA",
		    "EDITCA",
		  "FRAME8ROW4",
		    "LABNIMA",
		    "EDITNIMA",
		    "LABREG",
		    "EDITREG",
		  "FRAME8ROW5",
		    "LABTFN",
		    "EDITTFN",
		    "LABEMAIL",
		    "EDITEMAIL",
  "LABTIME",
  "LABDATE",
  "OUTPUT",
  "LOGOBIO",
  "LOGOPRO",
  "COMBOPRODUCTO",
  "COMBOTRANSPORTISTA",
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
	TQFrame,//FRAMEPERMISO
		TQFrame,//FRAMEPERMISOENTRADA
			TQLabel,//LABPERMISOENTRADA
			TQImage,//IMICONPERMISOENTRADA
		TQImage,//ICONPERM
		TQLabel,//LABPERM
		TQImage,//ICONFECHCONTR
		TQLabel,//LABFECHCONTR
		TQImage,//ICONFECHNPRT
		TQLabel,//LABFECHNPRT
		TQImage,//ICONCB
		TQLabel,//LABCB
		TQImage,//ICONCPeligro
		TQLabel,//LABCPeligro
		TQImage,//ICONDCP
		TQLabel,//LABDCP
		TQCheck,//CHKFORZARPROD
  	TQFrame,
  	TQFrame,
  	TQFrame,
  		TQFrame,
 		  TQLabel,
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
 	TQFrame,
  		TQFrame,
  		  TQLabel,
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
  pvSetGeometry(p,LABTITLE,6,0,200,120);
  pvSetText(p,LABTITLE,pvtr("APTDOS. 7,8\nDI DEFINITIVO"));
  pvSetFont(p,LABTITLE,"Verdana",16,1,1,0,0);

  pvQLabel(p,LABTYPE,0);
  pvSetGeometry(p,LABTYPE,320,15,800,60);
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
  pvSetEnabled(p,BUT78,0);

  pvQPushButton(p,BUT910,CENTRALFORM);
  pvSetGeometry(p,BUT910,1140,750,140,40);
  pvSetText(p,BUT910,pvtr("APTDOS 9,10"));
  pvSetFont(p,BUT910,"Verdana",13,1,0,0,0);

//
  pvQFrame(p,FRAMEPERMISO,CENTRALFORM,Box,Plain,3,1);
  pvSetGeometry(p,FRAMEPERMISO,350,20,1100,120);
  pvSetFont(p,FRAMEPERMISO,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAMEPERMISOENTRADA,FRAMEPERMISO,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEPERMISOENTRADA,10,10,170,100);
  pvSetFont(p,FRAMEPERMISOENTRADA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABPERMISOENTRADA,FRAMEPERMISOENTRADA);
  pvSetGeometry(p,LABPERMISOENTRADA,15,15,140,30);
  pvSetText(p,LABPERMISOENTRADA,pvtr("PERMISO"));
  pvSetFont(p,LABPERMISOENTRADA,"Default",20,1,1,0,0);

  pvQImage(p,IMICONPERMISOENTRADA,FRAMEPERMISOENTRADA,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,IMICONPERMISOENTRADA,65,55,90,90);
  pvSetFont(p,IMICONPERMISOENTRADA,"Verdana",12,1,0,0,0);
  pvSetWhatsThis(p,IMICONPERMISOENTRADA,pvtr("image/grey.png"));
  pvSetEnabled(p,FRAMEPERMISOENTRADA,0);


  pvQImage(p,ICONPERM,FRAMEPERMISO,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONPERM,200,20,20,20);
  pvSetFont(p,ICONPERM,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONPERM,pvtr("image/grey.png"));

  pvQLabel(p,LABPERM,FRAMEPERMISO);
  pvSetGeometry(p,LABPERM,230,20,70,20);
  pvSetText(p,LABPERM,pvtr("Permiso"));
  pvSetFont(p,LABPERM,"Default",10,1,0,0,0);

  pvQImage(p,ICONFECHCONTR,FRAMEPERMISO,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONFECHCONTR,200,80,20,20);
  pvSetFont(p,ICONFECHCONTR,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONFECHCONTR,pvtr("image/grey.png"));

  pvQLabel(p,LABFECHCONTR,FRAMEPERMISO);
  pvSetGeometry(p,LABFECHCONTR,230,70,150,40);
  pvSetText(p,LABFECHCONTR,pvtr("Fecha contrato"));
  pvSetFont(p,LABFECHCONTR,"Default",10,1,0,0,0);

  pvQImage(p,ICONFECHNPRT,FRAMEPERMISO,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONFECHNPRT,450,20,20,20);
  pvSetFont(p,ICONFECHNPRT,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONFECHNPRT,pvtr("image/grey.png"));

  pvQLabel(p,LABFECHNPRT,FRAMEPERMISO);
  pvSetGeometry(p,LABFECHNPRT,480,10,150,40);
  pvSetText(p,LABFECHNPRT,pvtr("Fecha NPT"));
  pvSetFont(p,LABFECHNPRT,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABFECHNPRT,pvtr("image/grey.png"));

  pvQImage(p,ICONCB,FRAMEPERMISO,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONCB,450,80,20,20);
  pvSetFont(p,ICONCB,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONCB,pvtr("image/grey.png"));

  pvQLabel(p,LABCB,FRAMEPERMISO);
  pvSetGeometry(p,LABCB,480,70,200,40);
  pvSetText(p,LABCB,pvtr("Caracterización\nbásica"));
  pvSetFont(p,LABCB,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABCB,pvtr("image/grey.png"));

  pvQImage(p,ICONCPeligro,FRAMEPERMISO,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONCPeligro,700,20,20,20);
  pvSetFont(p,ICONCPeligro,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONCPeligro,pvtr("image/grey.png"));

  pvQLabel(p,LABCPeligro,FRAMEPERMISO);
  pvSetGeometry(p,LABCPeligro,730,10,200,40);
  pvSetText(p,LABCPeligro,pvtr("Caracterización\npeligro"));
  pvSetFont(p,LABCPeligro,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABCPeligro,pvtr("image/grey.png"));

  pvQImage(p,ICONDCP,FRAMEPERMISO,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONDCP,700,80,20,20);
  pvSetFont(p,ICONDCP,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONDCP,pvtr("image/grey.png"));

  pvQLabel(p,LABDCP,FRAMEPERMISO);
  pvSetGeometry(p,LABDCP,730,80,120,20);
  pvSetText(p,LABDCP,pvtr("DCP"));
  pvSetFont(p,LABDCP,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABDCP,pvtr("image/grey.png"));

  pvQCheckBox(p,CHKFORZARPROD,FRAMEPERMISO);
  pvSetGeometry(p,CHKFORZARPROD,930,20,300,80);
  pvSetText(p,CHKFORZARPROD,pvtr("Forzar\nautorización\nproducto"));
  pvSetFont(p,CHKFORZARPROD,"Default",12,1,0,0,0);
  pvSetWhatsThis(p,CHKFORZARPROD,pvtr("image/grey.png"));
  pvSetEnabled(p,FRAMEPERMISO,0);

//
  pvQFrame(p,FRAME7RED,CENTRALFORM,Box,Plain,3,1);
  pvSetGeometry(p,FRAME7RED,345,165,1110,160);
  pvSetFont(p,FRAME7RED,"Verdana",12,1,0,0,0);
  pvSetPaletteForegroundColor(p,FRAME7RED,216,96,136);
  pvHide(p,FRAME7RED);

  pvQFrame(p,FRAME7,CENTRALFORM,Box,Plain,2,1);
  pvSetGeometry(p,FRAME7,350,170,1100,150);
  pvSetFont(p,FRAME7,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME7TITLE,FRAME7,Box,Plain,1,1);
  pvSetGeometry(p,FRAME7TITLE,0,0,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME7TITLE,220,220,220);
  pvSetFont(p,FRAME7TITLE,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME7,FRAME7TITLE);
  pvSetGeometry(p,LABFRAME7,10,5,1085,40);
  pvSetText(p,LABFRAME7,pvtr("7. CARACTERÍSTICAS DEL RESIDUO QUE SE TRASLADA:"));
  pvSetFont(p,LABFRAME7,"Default",15,1,0,0,0);

  pvQFrame(p,FRAME7ROW1,FRAME7,Box,Plain,1,1);
  pvSetGeometry(p,FRAME7ROW1,0,50,1100,50);
  pvSetFont(p,FRAME7ROW1,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABLER,FRAME7ROW1);
  pvSetGeometry(p,LABLER,10,5,60,40);
  pvSetText(p,LABLER,pvtr("LER:"));
  pvSetFont(p,LABLER,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITLER,FRAME7ROW1);
  pvSetGeometry(p,EDITLER,60,-1,159,50);
  pvSetFont(p,EDITLER,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITLER,0);

  pvQLabel(p,LABDESCLER,FRAME7ROW1);
  pvSetGeometry(p,LABDESCLER,230,5,130,40);
  pvSetText(p,LABDESCLER,pvtr("Descripción del\nresiduo:"));
  pvSetFont(p,LABDESCLER,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITDESCLER,FRAME7ROW1);
  pvSetGeometry(p,EDITDESCLER,370,-1,499,50);
  pvSetFont(p,EDITDESCLER,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDESCLER,0);

  pvQLabel(p,LABPESO,FRAME7ROW1);
  pvSetGeometry(p,LABPESO,880,5,40,40);
  pvSetText(p,LABPESO,pvtr("Kg:"));
  pvSetFont(p,LABPESO,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITPESO,FRAME7ROW1);
  pvSetGeometry(p,EDITPESO,940,-1,159,50);
  pvSetFont(p,EDITPESO,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITPESO,0);

  pvQFrame(p,FRAME7ROW2,FRAME7,Box,Plain,1,1);
  pvSetGeometry(p,FRAME7ROW2,0,100,1100,50);
  pvSetFont(p,FRAME7ROW2,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABPELIGRO,FRAME7ROW2);
  pvSetGeometry(p,LABPELIGRO,10,5,245,40);
  pvSetText(p,LABPELIGRO,pvtr("Característica peligrosidad:"));
  pvSetFont(p,LABPELIGRO,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITPELIGRO,FRAME7ROW2);
  pvSetGeometry(p,EDITPELIGRO,250,-1,849,50);
  pvSetFont(p,EDITPELIGRO,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITPELIGRO,0);

  pvQComboBox(p,COMBOPRODUCTO,CENTRALFORM,0,AtBottom);
  pvSetGeometry(p,COMBOPRODUCTO,40,170,300,40);
  pvSetFont(p,COMBOPRODUCTO,"Default",12,1,0,0,0);
  pvHide(p,COMBOPRODUCTO);

  pvQComboBox(p,COMBOTRANSPORTISTA,CENTRALFORM,0,AtBottom);
  pvSetGeometry(p,COMBOTRANSPORTISTA,40,350,300,40);
  pvSetFont(p,COMBOTRANSPORTISTA,"Default",12,1,0,0,0);
  pvHide(p,COMBOTRANSPORTISTA);

  pvQFrame(p,FRAME8RED,CENTRALFORM,Box,Plain,3,1);
  pvSetGeometry(p,FRAME8RED,345,345,1110,310);
  pvSetFont(p,FRAME8RED,"Verdana",12,1,0,0,0);
  pvSetPaletteForegroundColor(p,FRAME8RED,216,96,136);
  pvHide(p,FRAME8RED);	

  pvQFrame(p,FRAME8,CENTRALFORM,Box,Plain,2,1);
  pvSetGeometry(p,FRAME8,350,350,1100,300);
  pvSetFont(p,FRAME8,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME8TITLE,FRAME8,Box,Plain,1,1);
  pvSetGeometry(p,FRAME8TITLE,0,0,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME8TITLE,220,220,220);
  pvSetFont(p,FRAME8TITLE,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME8,FRAME8TITLE);
  pvSetGeometry(p,LABFRAME8,10,5,1090,40);
  pvSetText(p,LABFRAME8,pvtr("8. INFORMACIÓN RELATIVA A LOS TRANSPORTISTAS QUE INTERVIENEN EN EL TRASLADO:"));
  pvSetFont(p,LABFRAME8,"Default",15,1,0,0,0);

  pvQFrame(p,FRAME8ROW1,FRAME8,Box,Plain,1,1);
  pvSetGeometry(p,FRAME8ROW1,0,50,1100,50);
  pvSetFont(p,FRAME8ROW1,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNOMBRE,FRAME8ROW1);
  pvSetGeometry(p,LABNOMBRE,10,5,135,40);
  pvSetText(p,LABNOMBRE,pvtr("Razón Social/\nNombre:"));
  pvSetFont(p,LABNOMBRE,"Default",12,0,0,0,0);


  pvQLineEdit(p,EDITNOMBRE,FRAME8ROW1);
  pvSetGeometry(p,EDITNOMBRE,140,-1,609,50);
  pvSetFont(p,EDITNOMBRE,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNOMBRE,0);


  pvQLabel(p,LABNIF,FRAME8ROW1);
  pvSetGeometry(p,LABNIF,760,5,90,40);
  pvSetText(p,LABNIF,pvtr("N.I.F.:"));
  pvSetFont(p,LABNIF,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIF,FRAME8ROW1);
  pvSetGeometry(p,EDITNIF,860,-1,239,50);
  pvSetFont(p,EDITNIF,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIF,0);  


  pvQFrame(p,FRAME8ROW2,FRAME8,Box,Plain,1,1);
  pvSetGeometry(p,FRAME8ROW2,0,100,1100,50);
  pvSetFont(p,FRAME8ROW2,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDIREC,FRAME8ROW2);
  pvSetGeometry(p,LABDIREC,10,5,135,40);
  pvSetText(p,LABDIREC,pvtr("Dirección:"));
  pvSetFont(p,LABDIREC,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITDIREC,FRAME8ROW2);
  pvSetGeometry(p,EDITDIREC,140,-1,609,50);
  pvSetFont(p,EDITDIREC,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDIREC,0);

  pvQLabel(p,LABCP,FRAME8ROW2);
  pvSetGeometry(p,LABCP,760,5,90,40);
  pvSetText(p,LABCP,pvtr("C.P.:"));
  pvSetFont(p,LABCP,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITCP,FRAME8ROW2);
  pvSetGeometry(p,EDITCP,860,-1,239,50);
  pvSetFont(p,EDITCP,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCP,0);  

  pvQFrame(p,FRAME8ROW3,FRAME8,Box,Plain,1,1);
  pvSetGeometry(p,FRAME8ROW3,0,150,1100,50);
  pvSetFont(p,FRAME8ROW3,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABMUNI,FRAME8ROW3);
  pvSetGeometry(p,LABMUNI,10,5,135,40);
  pvSetText(p,LABMUNI,pvtr("Municipio:"));
  pvSetFont(p,LABMUNI,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITMUNI,FRAME8ROW3);
  pvSetGeometry(p,EDITMUNI,140,-1,240,50);
  pvSetFont(p,EDITMUNI,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITMUNI,0);

  
  pvQLabel(p,LABPRO,FRAME8ROW3);
  pvSetGeometry(p,LABPRO,390,5,150,40);
  pvSetText(p,LABPRO,pvtr("Provincia:"));
  pvSetFont(p,LABPRO,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITPRO,FRAME8ROW3);
  pvSetGeometry(p,EDITPRO,530,-1,220,50);
  pvSetFont(p,EDITPRO,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITPRO,0);  

  pvQLabel(p,LABCA,FRAME8ROW3);
  pvSetGeometry(p,LABCA,760,3,100,50);
  pvSetText(p,LABCA,pvtr("Comunidad\nAutónoma:"));
  pvSetFont(p,LABCA,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITCA,FRAME8ROW3);
  pvSetGeometry(p,EDITCA,860,-1,239,50);
  pvSetFont(p,EDITCA,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCA,0);  

  pvQFrame(p,FRAME8ROW4,FRAME8,Box,Plain,1,1);
  pvSetGeometry(p,FRAME8ROW4,0,200,1100,50);
  pvSetFont(p,FRAME8ROW4,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNIMA,FRAME8ROW4);
  pvSetGeometry(p,LABNIMA,10,5,135,40);
  pvSetText(p,LABNIMA,pvtr("NIMA:"));
  pvSetFont(p,LABNIMA,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIMA,FRAME8ROW4);
  pvSetGeometry(p,EDITNIMA,140,-1,240,50);
  pvSetFont(p,EDITNIMA,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIMA,0);
  
  pvQLabel(p,LABREG,FRAME8ROW4);
  pvSetGeometry(p,LABREG,390,5,150,40);
  pvSetText(p,LABREG,pvtr("Nº inscripción\nen el Registro:"));
  pvSetFont(p,LABREG,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITREG,FRAME8ROW4);
  pvSetGeometry(p,EDITREG,530,-1,569,50);
  pvSetFont(p,EDITREG,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITREG,0);  

  pvQFrame(p,FRAME8ROW5,FRAME8,Box,Plain,1,1);
  pvSetGeometry(p,FRAME8ROW5,0,250,1100,50);
  pvSetFont(p,FRAME8ROW5,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABTFN,FRAME8ROW5);
  pvSetGeometry(p,LABTFN,10,5,135,40);
  pvSetText(p,LABTFN,pvtr("Teléfono:"));
  pvSetFont(p,LABTFN,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITTFN,FRAME8ROW5);
  pvSetGeometry(p,EDITTFN,140,-1,240,50);
  pvSetFont(p,EDITTFN,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITTFN,0);
  
  pvQLabel(p,LABEMAIL,FRAME8ROW5);
  pvSetGeometry(p,LABEMAIL,390,5,150,40);
  pvSetText(p,LABEMAIL,pvtr("Correo\nelectrónico:"));
  pvSetFont(p,LABEMAIL,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITEMAIL,FRAME8ROW5);
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

  pvQImage(p,LOGOBIO,0,"image/logo_costumer_trans.png",&w,&h,&depth);
  pvSetGeometry(p,LOGOBIO,1255,915,275,95);
  pvSetFont(p,LOGOBIO,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,LOGOBIO,pvtr(""));

  pvQImage(p,LOGOPRO,0,"image/log_nuevo_completo_transp_red.png",&w,&h,&depth);
  pvSetGeometry(p,LOGOPRO,1545,920,395,95);
  pvSetFont(p,LOGOPRO,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,LOGOPRO,pvtr(""));

  pvQLabel(p,LOADINGFORM,0);
  pvSetGeometry(p,LOADINGFORM,540,220,640,480);
  pvSetFont(p,LOADINGFORM,"Sans Serif",9,0,0,0,0);

  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask9_slots.h"

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


int show_mask9(PARAM *p)
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
