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
  FRAME9,
  FRAME9TITLE,
  LABFRAME9,
  LABFRAME9_2,
  FRAME9ROW1,
  LABMATRICULA_ROW1,
  EDITMATRICULA_ROW1,
  LABREMOLQUE_ROW1,
  EDITREMOLQUE_ROW1,
  FRAME9ROW2,
  LABFRAME9ROW2,
  FRAME9ROW3,
  LABMATRICULA_ROW2,
  EDITMATRICULA_ROW2,
  LABREMOLQUE_ROW2,
  EDITREMOLQUE_ROW2,
  FRAME10,
    FRAME10TITLE,
    LABFRAME10,
  FRAME10ROW1,
    LABDATE_ENT,
    EDITDATE_ENT,
  FRAME10ROW2,
  LABACEPT_RES,
    FRAME10ROW2_SI,
      CHKSI,
       CHKNO,  
    FRAME10ROW2_1,
      LABDATE_ACEPT,
      EDITDATE_ACEPT,
      LABCANT_ACEPT,
      EDITCANT_ACEPT,
    FRAME10ROW2_2,
      LABDATE_RECH,
      EDITDATE_RECH,
      LABCANT_RECH,
      EDITCANT_RECH,
  FRAME10ROW3,
    LABNEWDATE,
    EDITNEWDATE,
  FRAME10ROW4,
    LABSRAP,
    EDITSRAP,
  LABTIME,
  LABDATE,
  OUTPUT,
  LOGOBIO,
  LOGOPRO,
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
  "FRAME9",
  "FRAME9TITLE",
  "LABFRAME9",
  "LABFRAME9_2",
  "FRAME9ROW1",
  " LABMATRICULA_ROW1",
  " EDITMATRICULA_ROW1",
  " LABREMOLQUE_ROW1",
  " EDITREMOLQUE_ROW1",
  " FRAME9ROW2",
  " LABFRAME9ROW2",
  " FRAME9ROW3",
  " LABMATRICULA_ROW2",
  " EDITMATRICULA_ROW2",
  " LABREMOLQUE_ROW2",
  " EDITREMOLQUE_ROW2",
    "FRAME10",
    "FRAME10TITLE",
    "LABFRAME10",
    " FRAME10ROW1",
   " LABDATE_ENT",
   " EDITDATE_ENT",
   " FRAME10ROW2",
   " LABACEPT_RES",
  " FRAME10ROW2_SI",
     " CHKSI",
     " CHKNO",
  " FRAME10ROW2_1",
     " LABDATE_ACEPT",
     " EDITDATE_ACEPT",
     " LABCANT_ACEPT",
     " EDITCANT_ACEPT",
   " FRAME10ROW2_2",
     " LABDATE_RECH",
     " EDITDATE_RECH",
     " LABCANT_RECH",
      "EDITCANT_RECH",
 " FRAME10ROW3",
   " LABNEWDATE",
   " EDITNEWDATE",
 " FRAME10ROW4",
   " LABSRAP",
   " EDITSRAP",
  "LABTIME",
  "LABDATE",
  "OUTPUT",
  "LOGOBIO",
  "LOGOPRO",
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
      TQFrame,
        TQLabel,
        TQLabel,
      TQFrame,
        TQLabel,
        TQLineEdit,
        TQLabel,
        TQLineEdit,
      TQFrame,
        TQLabel,
      TQFrame,
        TQLabel,
        TQLineEdit,
        TQLabel,
        TQLineEdit,
    TQFrame,
      TQFrame,
        TQLabel,
      TQFrame,
        TQLabel,
        TQLineEdit,
  TQFrame,
     TQLabel,
  TQFrame,
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
   TQFrame,
      TQLabel,
      TQLineEdit,
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
  pvSetText(p,LABTITLE,pvtr("APTDOS. 9,10\nDI DEFINITIVO"));
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

  pvSetEnabled(p,BUT910,0);

  pvQFrame(p,FRAME9,CENTRALFORM,Box,Plain,2,1);
  pvSetGeometry(p,FRAME9,350,120,1100,180);
  pvSetFont(p,FRAME9,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME9TITLE,FRAME9,Box,Plain,1,1);
  pvSetGeometry(p,FRAME9TITLE,0,0,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME9TITLE,220,220,220);
  pvSetFont(p,FRAME9TITLE,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME9,FRAME9TITLE);
  pvSetGeometry(p,LABFRAME9,10,5,1090,40);
  pvSetText(p,LABFRAME9,pvtr("9. INFORMACIÓN RELATIVA A LOS VEHÍCULOS Y REMOLQUES QUE INTERVIENEN EN EL TRASLADO"));
  pvSetFont(p,LABFRAME9,"Default",15,1,0,0,0);
  
  pvQFrame(p,FRAME9ROW1,FRAME9,Box,Plain,1,1);
  pvSetGeometry(p,FRAME9ROW1,0,50,1100,50);
  pvSetFont(p,FRAME9ROW1,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABMATRICULA_ROW1,FRAME9ROW1);
  pvSetGeometry(p,LABMATRICULA_ROW1,10,5,100,40);
  pvSetText(p,LABMATRICULA_ROW1,pvtr("Matrícula:"));
  pvSetFont(p,LABMATRICULA_ROW1,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITMATRICULA_ROW1,FRAME9ROW1);
  pvSetGeometry(p,EDITMATRICULA_ROW1,105,-1,445,50);
  pvSetFont(p,EDITMATRICULA_ROW1,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITMATRICULA_ROW1,0);

  pvQLabel(p,LABREMOLQUE_ROW1,FRAME9ROW1);
  pvSetGeometry(p,LABREMOLQUE_ROW1,560,5,100,40);
  pvSetText(p,LABREMOLQUE_ROW1,pvtr("Remolque:"));
  pvSetFont(p,LABREMOLQUE_ROW1,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITREMOLQUE_ROW1,FRAME9ROW1);
  pvSetGeometry(p,EDITREMOLQUE_ROW1,660,-1,439,50);
  pvSetFont(p,EDITREMOLQUE_ROW1,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITREMOLQUE_ROW1,0);

  pvQFrame(p,FRAME9ROW2,FRAME9,Box,Plain,1,1);
  pvSetGeometry(p,FRAME9ROW2,0,100,1100,30);
  pvSetPaletteBackgroundColor(p,FRAME9TITLE,220,220,220);
  pvSetFont(p,FRAME9ROW2,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME9ROW2,FRAME9ROW2);
  pvSetGeometry(p,LABFRAME9ROW2,10,5,1090,20);
  pvSetText(p,LABFRAME9ROW2,pvtr("INFORMACION EN CASO DE CAMBIO DE VEHICULO O REMOLQUE EN EL TRASLADO "));
  pvSetFont(p,LABFRAME9ROW2,"Default",13,1,0,0,0);
  
  pvQFrame(p,FRAME9ROW3,FRAME9,Box,Plain,1,1);
  pvSetGeometry(p,FRAME9ROW3,0,130,1100,50);
  pvSetFont(p,FRAME9ROW3,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABMATRICULA_ROW2,FRAME9ROW3);
  pvSetGeometry(p,LABMATRICULA_ROW2,10,5,100,40);
  pvSetText(p,LABMATRICULA_ROW2,pvtr("Matrícula:"));
  pvSetFont(p,LABMATRICULA_ROW2,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITMATRICULA_ROW2,FRAME9ROW3);
  pvSetGeometry(p,EDITMATRICULA_ROW2,105,-1,445,50);
  pvSetFont(p,EDITMATRICULA_ROW2,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITMATRICULA_ROW2,0);

  pvQLabel(p,LABREMOLQUE_ROW2,FRAME9ROW3);
  pvSetGeometry(p,LABREMOLQUE_ROW2,560,5,100,40);
  pvSetText(p,LABREMOLQUE_ROW2,pvtr("Remolque:"));
  pvSetFont(p,LABREMOLQUE_ROW2,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITREMOLQUE_ROW2,FRAME9ROW3);
  pvSetGeometry(p,EDITREMOLQUE_ROW2,660,-1,439,50);
  pvSetFont(p,EDITREMOLQUE_ROW2,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITREMOLQUE_ROW2,0);

  pvQFrame(p,FRAME10,CENTRALFORM,Box,Plain,2,1);
  pvSetGeometry(p,FRAME10,350,375,1100,300);
  pvSetFont(p,FRAME10,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAME10TITLE,FRAME10,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10TITLE,0,0,1100,50);
  pvSetPaletteBackgroundColor(p,FRAME10TITLE,220,220,220);
  pvSetFont(p,FRAME10TITLE,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABFRAME10,FRAME10TITLE);
  pvSetGeometry(p,LABFRAME10,10,5,1090,40);
  pvSetText(p,LABFRAME10,pvtr("10. OTRAS INFORMACIONES:"));
  pvSetFont(p,LABFRAME10,"Default",15,1,0,0,0);

  pvQFrame(p,FRAME10ROW1,FRAME10,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10ROW1,0,50,1100,50);
  pvSetFont(p,FRAME10ROW1,"Verdana",12,1,0,0,0);
  
  pvQLabel(p,LABDATE_ENT,FRAME10ROW1);
  pvSetGeometry(p,LABDATE_ENT,10,5,530,40);
  pvSetText(p,LABDATE_ENT,pvtr("Fecha de entrega de los residuos:"));
  pvSetFont(p,LABDATE_ENT,"Default",12,0,0,0,0);

  pvQLineEdit(p,EDITDATE_ENT,FRAME10ROW1);
  pvSetGeometry(p,EDITDATE_ENT,400,-1,699,50);
  pvSetFont(p,EDITDATE_ENT,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDATE_ENT,0);
  
  pvQFrame(p,FRAME10ROW2,FRAME10,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10ROW2,0,100,1100,100);
  pvSetFont(p,FRAME10ROW2,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABACEPT_RES,FRAME10ROW2);
  pvSetGeometry(p,LABACEPT_RES,25,25,160,50);
  pvSetText(p,LABACEPT_RES,pvtr("Aceptación\ndel residuo:"));
  pvSetFont(p,LABACEPT_RES,"Default",12,0,0,0,0);

  pvQFrame(p,FRAME10ROW2_SI,FRAME10ROW2,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10ROW2_SI,150,0,80,100);
  pvSetFont(p,FRAME10ROW2_SI,"Verdana",12,1,0,0,0);

  pvQRadioButton(p,CHKSI,FRAME10ROW2_SI);
  pvSetGeometry(p,CHKSI,8,5,80,40);
  pvSetText(p,CHKSI,pvtr(" SI"));
  pvSetFont(p,CHKSI,"Default",12,0,0,0,0);

  pvQRadioButton(p,CHKNO,FRAME10ROW2_SI);
  pvSetGeometry(p,CHKNO,8,55,80,40);
  pvSetText(p,CHKNO,pvtr(" NO"));
  pvSetFont(p,CHKNO,"Default",12,0,0,0,0);

  pvQFrame(p,FRAME10ROW2_1,FRAME10ROW2,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10ROW2_1,230,0,930,50);
  pvSetFont(p,FRAME10ROW2_1,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDATE_ACEPT,FRAME10ROW2_1);
  pvSetGeometry(p,LABDATE_ACEPT,10,5,170,40);
  pvSetText(p,LABDATE_ACEPT,pvtr("Fecha de aceptación:"));
  pvSetFont(p,LABDATE_ACEPT,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITDATE_ACEPT,FRAME10ROW2_1);
  pvSetGeometry(p,EDITDATE_ACEPT,170,-1,260,50);
  pvSetFont(p,EDITDATE_ACEPT,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDATE_ACEPT,0);

  pvQLabel(p,LABCANT_ACEPT,FRAME10ROW2_1);
  pvSetGeometry(p,LABCANT_ACEPT,440,5,200,40);
  pvSetText(p,LABCANT_ACEPT,pvtr("Cantidad aceptada(kg):"));
  pvSetFont(p,LABCANT_ACEPT,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITCANT_ACEPT,FRAME10ROW2_1);
  pvSetGeometry(p,EDITCANT_ACEPT,650,-1,219,50);
  pvSetFont(p,EDITCANT_ACEPT,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCANT_ACEPT,0);

  pvQFrame(p,FRAME10ROW2_2,FRAME10ROW2,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10ROW2_2,230,50,930,50);
  pvSetFont(p,FRAME10ROW2_2,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDATE_RECH,FRAME10ROW2_2);
  pvSetGeometry(p,LABDATE_RECH,10,5,170,40);
  pvSetText(p,LABDATE_RECH,pvtr("Fecha de rechazo:"));
  pvSetFont(p,LABDATE_RECH,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITDATE_RECH,FRAME10ROW2_2);
  pvSetGeometry(p,EDITDATE_RECH,170,-1,260,50);
  pvSetFont(p,EDITDATE_RECH,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITDATE_RECH,0);

  pvQLabel(p,LABCANT_RECH,FRAME10ROW2_2);
  pvSetGeometry(p,LABCANT_RECH,440,5,200,40);
  pvSetText(p,LABCANT_RECH,pvtr("Cantidad rechazada(kg):"));
  pvSetFont(p,LABCANT_RECH,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITCANT_RECH,FRAME10ROW2_2);
  pvSetGeometry(p,EDITCANT_RECH,650,-1,219,50);
  pvSetFont(p,EDITCANT_RECH,"Default",12,0,0,0,0);
  pvSetEditable(p,EDITCANT_RECH,0);
  
  pvQFrame(p,FRAME10ROW3,FRAME10,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10ROW3,0,200,1100,50);
  pvSetFont(p,FRAME10ROW3,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABNEWDATE,FRAME10ROW3);
  pvSetGeometry(p,LABNEWDATE,10,5,900,40);
  pvSetText(p,LABNEWDATE,pvtr("Si se opta por la devolución a la instalación de origen, indicar la fecha del nuevo traslado:"));
  pvSetFont(p,LABNEWDATE,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITNEWDATE,FRAME10ROW3);
  pvSetGeometry(p,EDITNEWDATE,880,-1,219,50);
  pvSetFont(p,EDITNEWDATE,"Default",11,0,0,0,0);
  pvSetEditable(p,EDITNEWDATE,0);

  pvQFrame(p,FRAME10ROW4,FRAME10,Box,Plain,1,1);
  pvSetGeometry(p,FRAME10ROW4,0,250,1100,50);
  pvSetFont(p,FRAME10ROW4,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSRAP,FRAME10ROW4);
  pvSetGeometry(p,LABSRAP,10,5,900,40);
  pvSetText(p,LABSRAP,pvtr("Sistema de Responsabilidad Ampliada del Productor que, en su caso, organiza el traslado:"));
  pvSetFont(p,LABSRAP,"Default",11,0,0,0,0);

  pvQLineEdit(p,EDITSRAP,FRAME10ROW4);
  pvSetGeometry(p,EDITSRAP,880,-1,219,50);
  pvSetFont(p,EDITSRAP,"Default",11,0,0,0,0);
  pvSetEditable(p,EDITSRAP,0);

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

#include "mask10_slots.h"

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


int show_mask10(PARAM *p)
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
