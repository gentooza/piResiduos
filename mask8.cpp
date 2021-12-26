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
        FRAME6RED_A,
	FRAME6,
	  FRAME6TITLE,
	    LABFRAME6TITLE,
	FRAME6_A,
	  FRAME6ROW_A,
	    LABROW_A,
	  FRAME6ROW1_A,
	    LABNOMBRE_A,
	    EDITNOMBRE_A,
	    LABNIF_A,
	    EDITNIF_A,
	  FRAME6ROW2_A,
	    LABDIREC_A,
	    EDITDIREC_A,
	    LABCP_A,
	    EDITCP_A,
	  FRAME6ROW3_A,
	    LABMUNI_A,
	    EDITMUNI_A,
	    LABPRO_A,
	    EDITPRO_A,
	    LABCA_A,
	    EDITCA_A,
	  FRAME6ROW4_A,
	    LABNIMA_A,
	    EDITNIMA_A,
	    LABREG_A,
	    EDITREG_A,
	    LABDR_A,
	    EDITDR_A,

	FRAME6_B,
	  FRAME6ROW_B,
	    LABROW_B,
	FRAME6ROW1_B,
	    LABNOMBRE_B,
	    EDITNOMBRE_B,
	    LABNIF_B,
	    EDITNIF_B,
	  FRAME6ROW2_B,
	    LABDIREC_B,
	    EDITDIREC_B,
	    LABCP_B,
	    EDITCP_B,
	  FRAME6ROW3_B,
	    LABMUNI_B,
	    EDITMUNI_B,
	    LABPRO_B,
	    EDITPRO_B,
	    LABCA_B,
	    EDITCA_B,
	  FRAME6ROW4_B,
	    LABNIMA_B,
	    EDITNIMA_B,
	    LABREG_B,
	    EDITREG_B,
	  FRAME6ROW5_B,
	    LABTFN_B,
	    EDITTFN_B,
	    LABEMAIL_B,
	    EDITEMAIL_B,

  LABTIME,
  LABDATE,
  OUTPUT,
  LOGOBIO,
  LOGOPRO,
  LOADINGFORM,
COMBOEMPAUTO2,
COMBOEMPAUTO1,
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
	"FRAME6RED_A",
	"FRAME6",
	  "FRAME6TITLE",
	    "LABFRAME6TITLE",
	"FRAME6_A",
	  "FRAME6ROW_A",
	    "LABROW_A",
	  "FRAME6ROW1_A",
	    "LABNOMBRE_A",
	    "EDITNOMBRE_A",
	    "LABNIF_A",
	    "EDITNIF_A",
	  "FRAME6ROW2_A",
	    "LABDIREC_A",
	    "EDITDIREC_A",
	    "LABCP_A",
	    "EDITCP_A",
	  "FRAME6ROW3_A",
	    "LABMUNI_A",
	    "EDITMUNI_A",
	    "LABPRO_A",
	    "EDITPRO_A",
	    "LABCA_A",
	    "EDITCA_A",
	  "FRAME6ROW4_A",
	    "LABNIMA_A",
	    "EDITNIMA_A",
	    "LABREG_A",
	    "EDITREG_A",
	    "LABDR_A",
	    "EDITDR_A",  //28

	"FRAME6_B",
	  "FRAME6ROW_B",
	    "LABROW_B",
	"FRAME6ROW1_B",
	    "LABNOMBRE_B",
	   "EDITNOMBRE_B",
	    "LABNIF_B",
	    "EDITNIF_B",
	  "FRAME6ROW2_B",
	    "LABDIREC_B",
	    "EDITDIREC_B",
	    "LABCP_B",
	    "EDITCP_B",
	  "FRAME6ROW3_B",
	    "LABMUNI_B",
	    "EDITMUNI_B",
	    "LABPRO_B",
	    "EDITPRO_B",
	    "LABCA_B",
	    "EDITCA_B",
	  "FRAME6ROW4_B",
	    "LABNIMA_B",
	    "EDITNIMA_B",
	    "LABREG_B",
	    "EDITREG_B",
	  "FRAME6ROW5_B",
	    "LABTFN_B",
	    "EDITTFN_B",
	    "LABEMAIL_B",
	    "EDITEMAIL_B", //30





  "LABTIME",
  "LABDATE",
  "OUTPUT",
  "LOGOBIO",
  "LOGOPRO",
  "LOADINGFORM",
"COMBOEMPAUTO2",
"COMBOEMPAUTO1",
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
 TQFrame,
 TQFrame,					//FRAME6,
 TQFrame,					  //FRAME6TITLE
 TQLabel,					    //LABFRAME6TITLE
 TQFrame,					//FRAME6_A,
 TQFrame,					  //FRAME6ROW_A,
 TQLabel,					    //LABROW_A,
 TQFrame,					  //FRAME6ROW1_A,
 TQLabel,					    //LABNOMBRE_A,
 TQLineEdit,					    //EDITNOMBRE_A,
 TQLabel,					    //LABNIF_A,
 TQLineEdit,					    //EDITNIF_A,
 TQFrame,					  //FRAME6ROW2_A,
 TQLabel,					    //LABDIREC_A,
 TQLineEdit,					    //EDITDIREC_A,
 TQLabel,					    //LABCP_A,
 TQLineEdit,					    //EDITCP_A,
 TQFrame,					  //FRAME6ROW3_A,
 TQLabel,					    //LABMUNI_A,
 TQLineEdit,					    //EDITMUNI_A,
 TQLabel,					    //LABPRO_A,
 TQLineEdit,					    //EDITPRO_A,
 TQLabel,					    //LABCA_A,
 TQLineEdit,					    //EDITCA_A,
 TQFrame,					  //FRAME6ROW4_A,
 TQLabel,					    //LABNIMA_A,
 TQLineEdit,					    //EDITNIMA_A,
 TQLabel,					    //LABREG_A,
 TQLineEdit,					    //EDITREG_A,
 TQLabel,					    //LABDR_A,
 TQLineEdit,					    //EDITDR_A,

 TQFrame,					//FRAME6_B,
 TQFrame,					  //FRAME6ROW_B,
 TQLabel,					    //LABROW_B,
 TQFrame,					//FRAME6ROW1_B,
 TQLabel,					    //LABNOMBRE_B,
 TQLineEdit,					    //EDITNOMBRE_B,
 TQLabel,					    //LABNIF_B,
 TQLineEdit,					    //EDITNIF_B,
 TQFrame,					  //FRAME6ROW2_B,
 TQLabel,					    //LABDIREC_B,
 TQLineEdit,					    //EDITDIREC_B,
 TQLabel,					    //LABCP_B,
 TQLineEdit,					    //EDITCP_B,
 TQFrame,					  //FRAME6ROW3_B,
 TQLabel,					    //LABMUNI_B,
 TQLineEdit,					    //EDITMUNI_B,
 TQLabel,					    //LABPRO_B,
 TQLineEdit,					    //EDITPRO_B,
 TQLabel,					    //LABCA_B,
 TQLineEdit,					    //EDITCA_B,
 TQFrame,					  //FRAME6ROW4_B,
 TQLabel,					    //LABNIMA_B,
 TQLineEdit,					    //EDITNIMA_B,
 TQLabel,					    //LABREG_B,
 TQLineEdit,					    //EDITREG_B,
 TQFrame,					  //FRAME6ROW5_B,
 TQLabel,					    //LABTFN_B,
 TQLineEdit,					    //EDITTFN_B,
 TQLabel,					    //LABEMAIL_B,
 TQLineEdit,					    //EDITEMAIL_B,

  TQLabel,
  TQLabel,
  TQMultiLineEdit,
  TQImage,
  TQImage,
    TQLabel,
  TQComboBox,
  TQComboBox,
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
  pvSetText(p,LABTITLE,pvtr("APARTADO 6\nDI DEFINITIVO"));
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

  pvSetEnabled(p,BUT6,0);  

  pvQFrame(p,FRAME6RED_A,CENTRALFORM,Box,Plain,3,1);
  pvSetGeometry(p,FRAME6RED_A,345,45,1110,310);
  pvSetFont(p,FRAME6RED_A,"Verdana",12,1,0,0,0);
  pvSetPaletteForegroundColor(p,FRAME6RED_A,216,96,136);
  pvHide(p,FRAME6RED_A);
  
  pvQFrame(p,FRAME6,CENTRALFORM,Box,Plain,2,1);
  pvSetGeometry(p,FRAME6,350,50,1100,600);
  pvSetFont(p,FRAME6,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME6TITLE,FRAME6,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6TITLE,0,0,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME6TITLE,220,220,220);
  pvSetFont(p,FRAME6TITLE,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME6TITLE,FRAME6TITLE); 	
  pvSetGeometry(p,LABFRAME6TITLE,10,5,1090,40);
  pvSetText(p,LABFRAME6TITLE,pvtr("6. INFORMACIÓN RELATIVA AL DESTINO DEL TRASLADO:"));
  pvSetFont(p,LABFRAME6TITLE,"Default",15,1,0,0,0);

  pvQFrame(p,FRAME6_A,FRAME6,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6_A,0,50,1100,250);
  pvSetFont(p,FRAME6_A,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME6ROW_A,FRAME6_A,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW_A,0,0,1100,50);
  pvSetFont(p,FRAME6ROW_A,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABROW_A,FRAME6ROW_A);
  pvSetGeometry(p,LABROW_A,10,5,1100,40);
  pvSetText(p,LABROW_A,pvtr("a)Información de la instalación de destino:"));
  pvSetFont(p,LABROW_A,"Default",12,1,0,0,0);

  pvQFrame(p,FRAME6ROW1_A,FRAME6_A,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW1_A,0,50,1100,50);
  pvSetFont(p,FRAME6ROW1_A,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNOMBRE_A,FRAME6ROW1_A);
  pvSetGeometry(p,LABNOMBRE_A,10,5,135,40);
  pvSetText(p,LABNOMBRE_A,pvtr("Razón Social/\nNombre:"));
  pvSetFont(p,LABNOMBRE_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNOMBRE_A,FRAME6ROW1_A);
  pvSetGeometry(p,EDITNOMBRE_A,140,-1,609,50);
  pvSetFont(p,EDITNOMBRE_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNOMBRE_A,0);

  pvQLabel(p,LABNIF_A,FRAME6ROW1_A);
  pvSetGeometry(p,LABNIF_A,760,5,90,40);
  pvSetText(p,LABNIF_A,pvtr("N.I.F.:"));
  pvSetFont(p,LABNIF_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIF_A,FRAME6ROW1_A);
  pvSetGeometry(p,EDITNIF_A,860,-1,239,50);
  pvSetFont(p,EDITNIF_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIF_A,0);  


  pvQFrame(p,FRAME6ROW2_A,FRAME6_A,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW2_A,0,100,1100,50);
  pvSetFont(p,FRAME6ROW2_A,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDIREC_A,FRAME6ROW2_A);
  pvSetGeometry(p,LABDIREC_A,10,5,135,40);
  pvSetText(p,LABDIREC_A,pvtr("Dirección:"));
  pvSetFont(p,LABDIREC_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITDIREC_A,FRAME6ROW2_A);
  pvSetGeometry(p,EDITDIREC_A,140,-1,609,50);
  pvSetFont(p,EDITDIREC_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDIREC_A,0);

  pvQLabel(p,LABCP_A,FRAME6ROW2_A);
  pvSetGeometry(p,LABCP_A,760,5,90,40);
  pvSetText(p,LABCP_A,pvtr("C.P.:"));
  pvSetFont(p,LABCP_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITCP_A,FRAME6ROW2_A);
  pvSetGeometry(p,EDITCP_A,860,-1,239,50);
  pvSetFont(p,EDITCP_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCP_A,0);  

  pvQFrame(p,FRAME6ROW3_A,FRAME6_A,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW3_A,0,150,1100,50);
  pvSetFont(p,FRAME6ROW3_A,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABMUNI_A,FRAME6ROW3_A);
  pvSetGeometry(p,LABMUNI_A,10,5,135,40);
  pvSetText(p,LABMUNI_A,pvtr("Municipio:"));
  pvSetFont(p,LABMUNI_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITMUNI_A,FRAME6ROW3_A);
  pvSetGeometry(p,EDITMUNI_A,140,-1,240,50);
  pvSetFont(p,EDITMUNI_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITMUNI_A,0);

  pvQLabel(p,LABPRO_A,FRAME6ROW3_A);
  pvSetGeometry(p,LABPRO_A,390,5,150,40);
  pvSetText(p,LABPRO_A,pvtr("Provincia:"));
  pvSetFont(p,LABPRO_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITPRO_A,FRAME6ROW3_A);
  pvSetGeometry(p,EDITPRO_A,530,-1,220,50);
  pvSetFont(p,EDITPRO_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITPRO_A,0);  

  pvQLabel(p,LABCA_A,FRAME6ROW3_A);
  pvSetGeometry(p,LABCA_A,760,3,90,50);
  pvSetText(p,LABCA_A,pvtr("Comunidad\nAutónoma:"));
  pvSetFont(p,LABCA_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITCA_A,FRAME6ROW3_A);
  pvSetGeometry(p,EDITCA_A,860,-1,239,50);
  pvSetFont(p,EDITCA_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCA_A,0);  

  pvQFrame(p,FRAME6ROW4_A,FRAME6_A,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW4_A,0,200,1100,50);
  pvSetFont(p,FRAME6ROW4_A,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNIMA_A,FRAME6ROW4_A);
  pvSetGeometry(p,LABNIMA_A,10,5,135,40);
  pvSetText(p,LABNIMA_A,pvtr("NIMA:"));
  pvSetFont(p,LABNIMA_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIMA_A,FRAME6ROW4_A);
  pvSetGeometry(p,EDITNIMA_A,140,-1,240,50);
  pvSetFont(p,EDITNIMA_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIMA_A,0);
  
  pvQLabel(p,LABREG_A,FRAME6ROW4_A);
  pvSetGeometry(p,LABREG_A,390,5,150,40);
  pvSetText(p,LABREG_A,pvtr("Nº inscripción\nen el Registro:"));
  pvSetFont(p,LABREG_A,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITREG_A,FRAME6ROW4_A);
  pvSetGeometry(p,EDITREG_A,530,-1,220,50);
  pvSetFont(p,EDITREG_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITREG_A,0);  

  pvQLabel(p,LABDR_A,FRAME6ROW4_A);
  pvSetGeometry(p,LABDR_A,760,2,90,48);
  pvSetText(p,LABDR_A,pvtr("Operación de\ntratamiento\n(D/R):"));
  pvSetFont(p,LABDR_A,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITDR_A,FRAME6ROW4_A);
  pvSetGeometry(p,EDITDR_A,860,-1,239,50);
  pvSetFont(p,EDITDR_A,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDR_A,0); 

  pvQFrame(p,FRAME6_B,FRAME6,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6_B,0,300,1100,300);
  pvSetFont(p,FRAME6_B,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME6ROW_B,FRAME6_B,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW_B,0,0,1100,50);
  pvSetFont(p,FRAME6ROW_B,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABROW_B,FRAME6ROW_B);
  pvSetGeometry(p,LABROW_B,10,5,1100,45);
   pvSetText(p,LABROW_B,pvtr("b)Información de la empresa autorizada para realizar operaciones de tratamiento de residuos,incluido\nel almacenamiento en la instalación de destino:"));
  pvSetFont(p,LABROW_B,"Default",12,1,0,0,0);

  pvQFrame(p,FRAME6ROW1_B,FRAME6_B,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW1_B,0,50,1100,50);
  pvSetFont(p,FRAME6ROW1_B,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNOMBRE_B,FRAME6ROW1_B);
  pvSetGeometry(p,LABNOMBRE_B,10,5,135,40);
  pvSetText(p,LABNOMBRE_B,pvtr("Razón Social/\nNombre:"));
  pvSetFont(p,LABNOMBRE_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNOMBRE_B,FRAME6ROW1_B);
  pvSetGeometry(p,EDITNOMBRE_B,140,-1,609,50);
  pvSetFont(p,EDITNOMBRE_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNOMBRE_B,0);

  pvQLabel(p,LABNIF_B,FRAME6ROW1_B);
  pvSetGeometry(p,LABNIF_B,760,5,90,40);
  pvSetText(p,LABNIF_B,pvtr("N.I.F.:"));
  pvSetFont(p,LABNIF_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIF_B,FRAME6ROW1_B);
  pvSetGeometry(p,EDITNIF_B,860,-1,239,50);
  pvSetFont(p,EDITNIF_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIF_B,0);  


  pvQFrame(p,FRAME6ROW2_B,FRAME6_B,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW2_B,0,100,1100,50);
  pvSetFont(p,FRAME6ROW2_B,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDIREC_B,FRAME6ROW2_B);
  pvSetGeometry(p,LABDIREC_B,10,5,135,40);
  pvSetText(p,LABDIREC_B,pvtr("Dirección:"));
  pvSetFont(p,LABDIREC_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITDIREC_B,FRAME6ROW2_B);
  pvSetGeometry(p,EDITDIREC_B,140,-1,609,50);
  pvSetFont(p,EDITDIREC_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDIREC_B,0);

  pvQLabel(p,LABCP_B,FRAME6ROW2_B);
  pvSetGeometry(p,LABCP_B,760,5,90,40);
  pvSetText(p,LABCP_B,pvtr("C.P.:"));
  pvSetFont(p,LABCP_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITCP_B,FRAME6ROW2_B);
  pvSetGeometry(p,EDITCP_B,860,-1,239,50);
  pvSetFont(p,EDITCP_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCP_B,0);  

  pvQFrame(p,FRAME6ROW3_B,FRAME6_B,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW3_B,0,150,1100,50);
  pvSetFont(p,FRAME6ROW3_B,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABMUNI_B,FRAME6ROW3_B);
  pvSetGeometry(p,LABMUNI_B,10,5,135,40);
  pvSetText(p,LABMUNI_B,pvtr("Municipio:"));
  pvSetFont(p,LABMUNI_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITMUNI_B,FRAME6ROW3_B);
  pvSetGeometry(p,EDITMUNI_B,140,-1,240,50);
  pvSetFont(p,EDITMUNI_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITMUNI_B,0);

  
  pvQLabel(p,LABPRO_B,FRAME6ROW3_B);
  pvSetGeometry(p,LABPRO_B,390,5,150,40);
  pvSetText(p,LABPRO_B,pvtr("Provincia:"));
  pvSetFont(p,LABPRO_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITPRO_B,FRAME6ROW3_B);
  pvSetGeometry(p,EDITPRO_B,530,-1,220,50);
  pvSetFont(p,EDITPRO_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITPRO_B,0);  

  pvQLabel(p,LABCA_B,FRAME6ROW3_B);
  pvSetGeometry(p,LABCA_B,760,3,90,50);
  pvSetText(p,LABCA_B,pvtr("Comunidad\nAutónoma:"));
  pvSetFont(p,LABCA_B,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITCA_B,FRAME6ROW3_B);
  pvSetGeometry(p,EDITCA_B,860,-1,239,50);
  pvSetFont(p,EDITCA_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCA_B,0);  

  pvQFrame(p,FRAME6ROW4_B,FRAME6_B,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW4_B,0,200,1100,50);
  pvSetFont(p,FRAME6ROW4_B,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNIMA_B,FRAME6ROW4_B);
  pvSetGeometry(p,LABNIMA_B,10,5,135,40);
  pvSetText(p,LABNIMA_B,pvtr("NIMA:"));
  pvSetFont(p,LABNIMA_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITNIMA_B,FRAME6ROW4_B);
  pvSetGeometry(p,EDITNIMA_B,140,-1,240,50);
  pvSetFont(p,EDITNIMA_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITNIMA_B,0);
  
  pvQLabel(p,LABREG_B,FRAME6ROW4_B);
  pvSetGeometry(p,LABREG_B,390,5,150,40);
  pvSetText(p,LABREG_B,pvtr("Nº inscripción\nen el Registro:"));
  pvSetFont(p,LABREG_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITREG_B,FRAME6ROW4_B);
  pvSetGeometry(p,EDITREG_B,530,-1,569,50);
  pvSetFont(p,EDITREG_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITREG_B,0);  

  pvQFrame(p,FRAME6ROW5_B,FRAME6_B,Box,Plain,1,1);
  pvSetGeometry(p,FRAME6ROW5_B,0,250,1100,50);
  pvSetFont(p,FRAME6ROW5_B,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABTFN_B,FRAME6ROW5_B);
  pvSetGeometry(p,LABTFN_B,10,5,135,40);
  pvSetText(p,LABTFN_B,pvtr("Teléfono:"));
  pvSetFont(p,LABTFN_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITTFN_B,FRAME6ROW5_B);
  pvSetGeometry(p,EDITTFN_B,140,-1,240,50);
  pvSetFont(p,EDITTFN_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITTFN_B,0);
  
  pvQLabel(p,LABEMAIL_B,FRAME6ROW5_B);
  pvSetGeometry(p,LABEMAIL_B,390,5,150,40);
  pvSetText(p,LABEMAIL_B,pvtr("Correo\nelectrónico:"));
  pvSetFont(p,LABEMAIL_B,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITEMAIL_B,FRAME6ROW5_B);
  pvSetGeometry(p,EDITEMAIL_B,530,-1,569,50);
  pvSetFont(p,EDITEMAIL_B,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITEMAIL_B,0);



  
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
   
  pvQComboBox(p,COMBOEMPAUTO2,CENTRALFORM,0,AtBottom);
  pvSetGeometry(p,COMBOEMPAUTO2,40,350,300,40);
  pvSetFont(p,COMBOEMPAUTO2,"Default",12,1,0,0,0);
  pvHide(p,COMBOEMPAUTO2);

  pvQComboBox(p,COMBOEMPAUTO1,CENTRALFORM,0,AtBottom);
  pvSetGeometry(p,COMBOEMPAUTO1,40,100,300,40);
  pvSetFont(p,COMBOEMPAUTO1,"Default",12,1,0,0,0);

  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask8_slots.h"

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


int show_mask8(PARAM *p)
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
