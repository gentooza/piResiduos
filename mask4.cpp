/*
This file is part of PixResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2021, Pixelada S. Coop. And. <info (at) pixelada (dot) org>

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

////////////////////////////////////////////////////////////////////////////
//
// show_mask4 for ProcessViewServer created: vie mar 17 12:33:32 2017
//
////////////////////////////////////////////////////////////////////////////
#include "pvapp.h"

// _begin_of_generated_area_ (do not edit -> use ui2pvc) -------------------

// our mask contains the following objects
enum {
  ID_MAIN_WIDGET = 0, //0
  LABTITLE, //1
  LABTYPE, //2
  BUT1, //3
  BUT2, //4
  BUT3, //5
  BUTSINCRONIZA, //6
  CENTRALFORM, //7
  CHKENTRADA, //8
  CHKSALIDA, //9
  FRAMECAM_E1, //10
  IMCAM, //11
  LOADINGCAM, //12
  BUTCAM, //13
  BUTEDITCAM, //14
  EDITCAM, //15
  ICONAUTMATRI, //16
  LABAUTMATRI, //17
  CHCKAUTMATRI, //18
  CHCKNOREGISTRADO, //19
  FRAMECLIENTES, //20
  FFCLIENTES, //21
  COMBOCLIENTES, //22
  LABCLIENTES, //23
  EDITCLIENTES, //24
  FFPRODUCTOS, //25
  LABPRODUCTOS, //26
  COMBOPRODUCTOS, //27
  EDITPRODUCTOS, //28
  FFALLPRODUCTOS, //29
  LABLERS, //30
  COMBOLERS, //31
  EDITLERS, //32
  ICONPERM, //33
  LABPERM, //34
  ICONFECHCONTR, //35
  LABFECHCONTR, //36
  ICONFECHNPRT, //37
  LABFECHNPRT, //38
  ICONCB, //39
  LABCB, //40
  ICONCP, //41
  LABCP, //42
  ICONDCP, //43
  LABDCP, //44
  CHKFORZARPROD, //45
  FDIPROV, //46
  LABDIPROV, //47
  EDITDIPROV, //48
  /*FRAME DEL SEMÁFORO DE ENTRADA*/
  FRAMESEMENTRADA,
  LABSEMENTRADA,
  IMICONSEMENTRADA,
  BUTSEMENTRADA,
  /********************/
  /*FRAME CON EL ICONO DEL PERMISO DE ENTRADA*/
  FRAMEPERMISOENTRADA, //49
  LABPERMISOENTRADA, //50
  IMICONPERMISOENTRADA, //51
  /*******************************************/
  FRAMEPESOENT, //52
  LABPESOENT, //53
  EDITPESOENT, //54
  BUTEDITPESOENT, //55
  LOADINGPESOENT, //56
  LABKGENT, //57
  BUTPESOENT, //58
  FRAMECOMMENTENT, //59
  LABCOMMENTENT, //60
  EDITCOMMENTENT, //61
  FRAMESEPARACION, //62
  /********************/
  /*FRAME CON LOS BOTONES DE CONTROL*/
  FRAMEBUTTONS, //63
  LABBUTTONS, //64
  BUTPROCEDER_E1, //65
  BUTCANCELAR_E1, //66
  BUTRETROCEDER_E1,
  /**********************************/
  FRAMETRANSITO,
  LABTRANSITO,
BUTDELETRANS,
  TABLATRANSITO,
  FRAMECAM_E2,
  IMCAM_E2,
  BUTCAM_E2,
  EDITCAM_E2,
  LOADINGCAM2,
  BUTEDITCAM2,
  FDIDEF,//DI DEFINITIVO
  LABDIDEF,
  EDITDIDEF,
  LABSTATUSDIDEF,
  BUTEDITDIDEF,
  LABTRANSP,
  EDITCODETRANSP,
  EDITNAMETRANSP, //FIN DI DEFINITIVO
  FRAMEPESOTARA,
  LABPESOTARA,
  EDITPESOTARA,
  BUTEDITPESOSAL,
  LOADINGPESOTARA,
  LABKGTARA,
  BUTPESOTARA,
  ICONPERMISOPESOSAL,
  ICONSATUSPESOSAL,
  LABDEFAULTPESOSAL,
  BUTFIRMAR,
  BUTRETENER,
  FRAMECOMMENTSAL,
  LABCOMMENTSAL,
  EDITCOMMENTSAL,
  /*FRAME DEL SEMÁFORO DE SALIDA*/
  FRAMESEMSALIDA,
  LABSEMSALIDA,
  IMICONSEMSALIDA,
  BUTSEMSALIDA,
  /********************/
  LABTIME, //-7
  LABDATE, //-6
  OUTPUT, //-5
  LOGOBIO, //-4
  LOGOPRO, //-3
  LOADINGFORM, //-2
  BUTTEST, //-1
  ID_END_OF_WIDGETS //-0
};

// our mask contains the following widget names
static const char *widgetName[] = {
  "ID_MAIN_WIDGET", //0
  "LABTITLE", //1
  "LABTYPE", //2
  "BUT1", //3
  "BUT2", //4
  "BUT3", //5
  "BUTSINCRONIZA", //6
  "CENTRALFORM", //7
  "CHKENTRADA", //8
  "CHKSALIDA", //9
  "FRAMECAM_E1", //10
  "IMCAM", //11
  "LOADINGCAM", //12
  "BUTCAM", //13
  "BUTEDITCAM", //14
  "EDITCAM", //15
  "ICONAUTMATRI", //16
  "LABAUTMATRI", //17
  "CHCKAUTMATRI", //18
  "CHCKNOREGISTRADO", //19
  "FRAMECLIENTES", //20
  "FFCLIENTES", //21
  "COMBOCLIENTES", //22
  "LABCLIENTES", //23
  "EDITCLIENTES", //24
  "FFPRODUCTOS", //25
  "LABPRODUCTOS", //26
  "COMBOPRODUCTOS", //27
  "EDITPRODUCTOS", //28
  "FFALLPRODUCTOS", //29
  "LABLERS", //30
  "COMBOLERS",
  "EDITLERS",
  "ICONPERM",
  "LABPERM",
  "ICONFECHCONTR",
  "LABFECHCONTR",
  "ICONFECHNPRT",
  "LABFECHNPRT",
  "ICONCB",
  "LABCB",
  "ICONCP",
  "LABCP",
  "ICONDCP",
  "LABDCP",
  "CHKFORZARPROD",
  "FDIPROV",
  "LABDIPROV",
  "EDITDIPROV",
  /*FRAME DEL SEMÁFORO DE ENTRADA*/
  "FRAMEPERMISOENTRADA",
  "LABPERMISOENTRADA",
  "IMICONPERMISOENTRADA",
  "BUTSEMENTRADA",
  /********************/
  /*FRAME CON EL ICONO DEL PERMISO DE ENTRADA*/
  "FRAMEPERMISOENTRADA",
  "LABPERMISOENTRADA",
  "IMICONPERMISOENTRADA",
  /*******************************************/
  "FRAMEPESOENT",
  "LABPESOENT",
  "EDITPESOENT",
  "BUTEDITPESOENT",
  "LOADINGPESOENT",
  "LABKGENT",
  "BUTPESOENT",
  "FRAMECOMMENTENT",
  "LABCOMMENTENT",
  "EDITCOMMENTENT",
  "FRAMESEPARACION",
  /********************/
  /*FRAME CON LOS BOTONES DE CONTROL*/
  "FRAMEBUTTONS",
  "LABBUTTONS",
  "BUTPROCEDER_E1",
  "BUTCANCELAR_E1",
  "BUTRETROCEDER_E1",
  /**********************************/
  "FRAMETRANSITO",
  "LABTRANSITO",
  "BUTDELETRANS",
  "TABLATRANSITO",
  "FRAMECAM_E2",
  "IMCAM_E2",
  "BUTCAM_E2",
  "EDITCAM_E2",
  "LOADINGCAM2",
  "BUTEDITCAM2",
  "FDIDEF", //FRAME DI DEFINITIVO
  "LABDIDEF",
  "EDITDIDEF",
  "LABSTATUSDIDEF",
  "BUTEDITDIDEF",
  "LABTRANSP",
  "EDITCODETRANSP",
  "EDITNAMETRANSP", //FIN DI DEFINITIVO
  "FRAMEPESOTARA",
  "LABPESOTARA",
  "EDITPESOTARA",
  "BUTEDITPESOSAL",
  "LOADINGPESOTARA",
  "LABKGTARA",
  "BUTPESOTARA",
  "ICONPERMISOPESOSAL",
  "ICONSATUSPESOSAL",
  "LABDEFAULTPESOSAL",
  "BUTFIRMAR",
  "BUTRETENER",
  "FRAMECOMMENTSAL",
  "LABCOMMENTSAL",
  "EDITCOMMENTSAL",
  /*FRAME DEL SEMÁFORO DE SALIDA*/
  "FRAMESEMSALIDA",
  "LABSEMSALIDA",
  "IMICONSEMSALIDA",
  "BUTSEMSALIDA",
  /********************/
  "LABTIME",
  "LABDATE",
  "OUTPUT",
  "LOGOBIO",
  "LOGOPRO",
  "LOADINGFORM",
  "ID_END_OF_WIDGETS",
  "BUT_TEST",
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
  "image/image.jpg",
  "image/image.jpg",
  "image/image.jpg",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "image/grey.png",
  "",
  "image/grey.png",
  "",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "image/grey.png",
  "",
  "",
  "",
    "",
    "",
  "",
  "",
    "",
  "",
  "image/grey.png",
  "image/grey.png",
  "",
    "",
    "",
  "",
  "",
  "",
  "",
  "image/grey.png",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
    "",
  "",
  "",
  "image/image.jpg",
  "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
  "",
  "",
    "",
  "",
  "",
  "",
    "",
  "",
  "",
    "",
    "",
  "",
      "",
  "",
  "",
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
  TQPushButton,
  TQFrame,
  TQRadio,
  TQRadio,
  TQFrame,
  TQImage,
  TQLabel,
  TQPushButton,
  TQPushButton,
  TQLineEdit,
  TQImage,
  TQLabel,
  TQCheck,
  TQCheck,
  TQFrame,
  TQFrame,
  TQComboBox,
  TQLabel,
  TQLineEdit,
  TQFrame,
  TQLabel,
  TQComboBox,
  TQLineEdit,
  TQFrame,
  TQLabel,
  TQComboBox,
  TQLineEdit,
  TQImage,
  TQLabel,
  TQImage,
  TQLabel,
  TQImage,
  TQLabel,
  TQImage,
  TQLabel,
  TQImage,
  TQLabel,
  TQImage,
  TQLabel,
  TQCheck,
  TQFrame,
  TQLabel,
  TQLineEdit,
  /* FRAME DEL SEMÁFORO DE ENTRADA*/
  TQFrame,
  TQLabel,
  TQImage,
  TQPushButton,
  /*******************************************/
  /* FRAME CON EL ICONO DE PERMISO DE ENTRADA*/
  TQFrame,
  TQLabel,
  TQImage,
  /*******************************************/
  TQFrame,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel,
  TQLabel,
  TQPushButton,
  TQFrame,
  TQLabel,
  TQMultiLineEdit,
  TQFrame,
  /********************/
  /*FRAME CON LOS BOTONES DE CONTROL*/
  TQFrame,
  TQLabel,
  TQPushButton,
  TQPushButton,
  TQPushButton,
  /*******************************************/
  TQFrame,
  TQLabel,
  TQPushButton,
  TQListBox,
  TQFrame,
  TQImage,
  TQPushButton,
  TQLineEdit,
  TQLabel,
  TQPushButton,
  TQFrame, //FRAME DI DEFINITIVO
  TQLabel,
  TQLineEdit,
  TQLabel,
  TQPushButton,
  TQLabel,
  TQLineEdit,
  TQLineEdit, //FIN FRAME DI DEFINITIVO
  TQFrame,
  TQLabel,
  TQLineEdit,
  TQPushButton,
  TQLabel,
  TQLabel,
  TQPushButton,
  TQImage,
  TQImage,
  TQLabel,
  TQPushButton,
  TQPushButton,
  TQFrame,
  TQLabel,
  TQMultiLineEdit,
  /* FRAME DEL SEMÁFORO DE SALIDA*/
  TQFrame,
  TQLabel,
  TQImage,
  TQPushButton,
  /*******************************************/
  TQLabel,
  TQLabel,
  TQMultiLineEdit,
  TQImage,
  TQImage,
    TQLabel,
    TQPushButton,
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
  pvSetText(p,LABTITLE,pvtr("ENTRADA\nDE\nPRODUCTO"));
  pvSetFont(p,LABTITLE,"Verdana",16,1,1,0,0);

  pvQLabel(p,LABTYPE,0);
  pvSetGeometry(p,LABTYPE,320,15,800,60);
  pvSetText(p,LABTYPE,pvtr(""));
  pvSetPaletteForegroundColor(p,LABTYPE,90,100,100);
  pvSetFont(p,LABTYPE,"Verdana",30,1,1,0,0);

  pvQPushButton(p,BUT1,0);
  pvSetGeometry(p,BUT1,5,270,135,60);
  pvSetText(p,BUT1,pvtr("ENTRADAS\n(F1)"));
  pvSetFont(p,BUT1,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,BUT1,0);

  pvQPushButton(p,BUT2,0);
  pvSetGeometry(p,BUT2,5,500,135,60);
  pvSetText(p,BUT2,pvtr("SALIDAS\n(F2)"));
  pvSetFont(p,BUT2,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,BUT2,0);
  
  pvQPushButton(p,BUT3,0);
  pvSetGeometry(p,BUT3,5,710,135,60);
  pvSetText(p,BUT3,pvtr("CONFIGU-\nRACIÓN(F3)"));
  pvSetFont(p,BUT3,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,BUT3,0);
  
  pvQFrame(p,CENTRALFORM,0,Panel,Sunken,4,1);
  pvSetGeometry(p,CENTRALFORM,150,100,1740,810);
  pvSetFont(p,CENTRALFORM,"Verdana",12,1,0,0,0);

  pvQRadioButton(p,CHKENTRADA,CENTRALFORM);
  pvSetGeometry(p,CHKENTRADA,20,192,130,60);
  pvSetText(p,CHKENTRADA,pvtr("ENTRADA\nPLANTA\n(F5)"));
  pvSetFont(p,CHKENTRADA,"Verdana",12,1,0,0,0);
  pvSetEnabled(p,CHKENTRADA,0);

  pvQRadioButton(p,CHKSALIDA,CENTRALFORM);
  pvSetGeometry(p,CHKSALIDA,20,616,130,60);
  pvSetText(p,CHKSALIDA,pvtr("SALIDA\nPLANTA\n(F5)"));
  pvSetFont(p,CHKSALIDA,"Verdana",12,1,0,0,0);
  pvSetEnabled(p,CHKSALIDA,0);

  pvQFrame(p,FRAMECAM_E1,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECAM_E1,155,10,320,390);
  pvSetFont(p,FRAMECAM_E1,"Verdana",12,1,0,0,0);  

  pvQImage(p,IMCAM,FRAMECAM_E1,"image/image.jpg",&w,&h,&depth);
  pvSetGeometry(p,IMCAM,15,70,288,216);
  pvSetFont(p,IMCAM,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,IMCAM,pvtr("image/image.jpg"));

  pvQLabel(p,LOADINGCAM,FRAMECAM_E1);
  pvSetGeometry(p,LOADINGCAM,-65,40,441,291);
  pvSetFont(p,LOADINGCAM,"Verdana",12,1,0,0,0);
  pvSetWhatsThis(p,LOADINGCAM,pvtr("image/image.jpg"));

  pvQPushButton(p,BUTCAM,FRAMECAM_E1);
  pvSetGeometry(p,BUTCAM,15,10,120,50);
  pvSetText(p,BUTCAM,pvtr("Tomar \nMatrícula"));
  pvSetFont(p,BUTCAM,"Default",12,1,0,0,0);
  pvSetWhatsThis(p,BUTCAM,pvtr("image/image.jpg"));

  pvQPushButton(p,BUTEDITCAM,FRAMECAM_E1);
  pvSetGeometry(p,BUTEDITCAM,140,10,43,50);
  pvSetPixmap(p,BUTEDITCAM,"image/edit.png",0);

  pvQLineEdit(p,EDITCAM,FRAMECAM_E1);
  pvSetGeometry(p,EDITCAM,183,10,120,50);
  pvSetFont(p,EDITCAM,"Default",12,1,0,0,0);
  pvSetWhatsThis(p,EDITCAM,pvtr("image/grey.png"));
  pvSetEditable(p,EDITCAM,0);

  pvQImage(p,ICONAUTMATRI,FRAMECAM_E1,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONAUTMATRI,15,320,30,30);
  pvSetFont(p,ICONAUTMATRI,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,ICONAUTMATRI,pvtr("image/grey.png"));

  pvQLabel(p,LABAUTMATRI,FRAMECAM_E1);
  pvSetGeometry(p,LABAUTMATRI,50,315,120,40);
  pvSetText(p,LABAUTMATRI,pvtr("Matrícula \nregistrada"));
  pvSetFont(p,LABAUTMATRI,"Default",11,1,0,0,0);
  pvSetWhatsThis(p,LABAUTMATRI,pvtr("image/grey.png"));

  pvQCheckBox(p,CHCKAUTMATRI,FRAMECAM_E1);
  pvSetGeometry(p,CHCKAUTMATRI,150,295,155,30);
  pvSetText(p,CHCKAUTMATRI,pvtr("Autorizar"));
  pvSetFont(p,CHCKAUTMATRI,"Default",12,1,0,0,0);

  pvQCheckBox(p,CHCKNOREGISTRADO,FRAMECAM_E1);
  pvSetGeometry(p,CHCKNOREGISTRADO,150,340,155,40);
  pvSetText(p,CHCKNOREGISTRADO,pvtr("Cliente partic.\nno registrado"));
  pvSetFont(p,CHCKNOREGISTRADO,"Default",12,1,0,0,0);
  pvSetEnabled(p,FRAMECAM_E1,0);

  pvQFrame(p,FRAMECLIENTES,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECLIENTES,500,10,815,290);
  pvSetFont(p,FRAMECLIENTES,"Verdana",12,1,0,0,0);

  pvQFrame(p,FFCLIENTES,FRAMECLIENTES,Box,Plain,2,1);
  pvSetGeometry(p,FFCLIENTES,10,5,389,120);
  pvSetFont(p,FFCLIENTES,"Verdana",12,1,0,0,0);

  pvQComboBox(p,COMBOCLIENTES,FFCLIENTES,0,AtBottom);
  pvSetGeometry(p,COMBOCLIENTES,20,35,349,30);
  pvSetFont(p,COMBOCLIENTES,"Default",12,1,0,0,0);

  pvQLabel(p,LABCLIENTES,FFCLIENTES);
  pvSetGeometry(p,LABCLIENTES,30,5,180,30);
  pvSetText(p,LABCLIENTES,pvtr("Seleccione Cliente:"));
  pvSetFont(p,LABCLIENTES,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITCLIENTES,FFCLIENTES);
  pvSetGeometry(p,EDITCLIENTES,20,80,349,30);
  pvSetText(p,EDITCLIENTES,pvtr("N/A"));
  pvSetFont(p,EDITCLIENTES,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITCLIENTES,0);

  pvQFrame(p,FFPRODUCTOS,FRAMECLIENTES,Box,Plain,2,1);
  pvSetGeometry(p,FFPRODUCTOS,10,130,389,150);
  pvSetFont(p,FFPRODUCTOS,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABPRODUCTOS,FFPRODUCTOS);
  pvSetGeometry(p,LABPRODUCTOS,30,5,240,50);
  pvSetText(p,LABPRODUCTOS,pvtr("Seleccione producto\npermitido para el cliente:"));
  pvSetFont(p,LABPRODUCTOS,"Default",12,1,0,0,0);

  pvQComboBox(p,COMBOPRODUCTOS,FFPRODUCTOS,0,AtBottom);
  pvSetGeometry(p,COMBOPRODUCTOS,20,55,349,30);
  pvSetFont(p,COMBOPRODUCTOS,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITPRODUCTOS,FFPRODUCTOS);
  pvSetGeometry(p,EDITPRODUCTOS,20,100,349,30);
  pvSetText(p,EDITPRODUCTOS,pvtr("N/A"));
  pvSetFont(p,EDITPRODUCTOS,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITPRODUCTOS,0);

  pvQFrame(p,FFALLPRODUCTOS,FRAMECLIENTES,Box,Plain,2,1);
  pvSetGeometry(p,FFALLPRODUCTOS,415,5,390,275);
  pvSetFont(p,FFALLPRODUCTOS,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABLERS,FFALLPRODUCTOS);
  pvSetGeometry(p,LABLERS,30,5,200,30);
  pvSetText(p,LABLERS,pvtr("Seleccione Producto:"));
  pvSetFont(p,LABLERS,"Default",12,1,0,0,0);

  pvQComboBox(p,COMBOLERS,FFALLPRODUCTOS,0,AtBottom);
  pvSetGeometry(p,COMBOLERS,20,35,350,30);
  pvSetFont(p,COMBOLERS,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITLERS,FFALLPRODUCTOS);
  pvSetGeometry(p,EDITLERS,20,70,350,30);
  pvSetText(p,EDITLERS,pvtr("N/A"));
  pvSetFont(p,EDITLERS,"Default",12,1,0,0,0);

  pvQImage(p,ICONPERM,FFALLPRODUCTOS,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONPERM,30,115,20,20);
  pvSetFont(p,ICONPERM,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONPERM,pvtr("image/grey.png"));

  pvQLabel(p,LABPERM,FFALLPRODUCTOS);
  pvSetGeometry(p,LABPERM,55,115,70,20);
  pvSetText(p,LABPERM,pvtr("Permiso"));
  pvSetFont(p,LABPERM,"Default",10,1,0,0,0);

  pvQImage(p,ICONFECHCONTR,FFALLPRODUCTOS,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONFECHCONTR,30,150,20,20);
  pvSetFont(p,ICONFECHCONTR,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONFECHCONTR,pvtr("image/grey.png"));

  pvQLabel(p,LABFECHCONTR,FFALLPRODUCTOS);
  pvSetGeometry(p,LABFECHCONTR,55,140,80,40);
  pvSetText(p,LABFECHCONTR,pvtr("Fecha \ncontrato"));
  pvSetFont(p,LABFECHCONTR,"Default",10,1,0,0,0);

  pvQImage(p,ICONFECHNPRT,FFALLPRODUCTOS,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONFECHNPRT,30,185,20,20);
  pvSetFont(p,ICONFECHNPRT,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONFECHNPRT,pvtr("image/grey.png"));

  pvQLabel(p,LABFECHNPRT,FFALLPRODUCTOS);
  pvSetGeometry(p,LABFECHNPRT,55,175,80,40);
  pvSetText(p,LABFECHNPRT,pvtr("Fecha \nNPT"));
  pvSetFont(p,LABFECHNPRT,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABFECHNPRT,pvtr("image/grey.png"));

  pvQImage(p,ICONCB,FFALLPRODUCTOS,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONCB,140,115,20,20);
  pvSetFont(p,ICONCB,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONCB,pvtr("image/grey.png"));

  pvQLabel(p,LABCB,FFALLPRODUCTOS);
  pvSetGeometry(p,LABCB,165,105,120,40);
  pvSetText(p,LABCB,pvtr("Caracterización \nbásica"));
  pvSetFont(p,LABCB,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABCB,pvtr("image/grey.png"));

  pvQImage(p,ICONCP,FFALLPRODUCTOS,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONCP,140,150,20,20);
  pvSetFont(p,ICONCP,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONCP,pvtr("image/grey.png"));

  pvQLabel(p,LABCP,FFALLPRODUCTOS);
  pvSetGeometry(p,LABCP,165,140,120,40);
  pvSetText(p,LABCP,pvtr("Caracterización \npeligro"));
  pvSetFont(p,LABCP,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABCP,pvtr("image/grey.png"));

  pvQImage(p,ICONDCP,FFALLPRODUCTOS,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONDCP,140,185,20,20);
  pvSetFont(p,ICONDCP,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONDCP,pvtr("image/grey.png"));

  pvQLabel(p,LABDCP,FFALLPRODUCTOS);
  pvSetGeometry(p,LABDCP,165,185,120,20);
  pvSetText(p,LABDCP,pvtr("DCP"));
  pvSetFont(p,LABDCP,"Default",10,1,0,0,0);
  pvSetWhatsThis(p,LABDCP,pvtr("image/grey.png"));

  pvQCheckBox(p,CHKFORZARPROD,FFALLPRODUCTOS);
  pvSetGeometry(p,CHKFORZARPROD,75,220,200,40);
  pvSetText(p,CHKFORZARPROD,pvtr("Forzar autorización \nproducto"));
  pvSetFont(p,CHKFORZARPROD,"Default",12,1,0,0,0);
  pvSetWhatsThis(p,CHKFORZARPROD,pvtr("image/grey.png"));
  pvSetEnabled(p,FFALLPRODUCTOS,0);

  pvQFrame(p,FDIPROV,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FDIPROV,500,310,370,90);
  pvSetFont(p,FDIPROV,"Verdana",12,1,0,0,0);
  pvSetWhatsThis(p,FDIPROV,pvtr("image/grey.png"));

  pvQLabel(p,LABDIPROV,FDIPROV);
  pvSetGeometry(p,LABDIPROV,30,5,220,30);
  pvSetText(p,LABDIPROV,pvtr("DI. PROVISIONAL"));
  pvSetFont(p,LABDIPROV,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITDIPROV,FDIPROV);
  pvSetGeometry(p,EDITDIPROV,20,40,330,30);
  pvSetFont(p,EDITDIPROV,"Default",12,1,0,0,0);
  pvSetEnabled(p,FDIPROV,0);

  /*FRAME DEL SEMÁFORO DE ENTRADA*/    
  pvQFrame(p,FRAMESEMENTRADA,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMESEMENTRADA,1340,10,190,90);
  pvSetFont(p,FRAMESEMENTRADA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSEMENTRADA,FRAMESEMENTRADA);
  pvSetGeometry(p,LABSEMENTRADA,10,5,140,30);
  pvSetText(p,LABSEMENTRADA,pvtr("SEMÁFORO:"));
  pvSetFont(p,LABSEMENTRADA,"Default",14,1,1,0,0);

  pvQImage(p,IMICONSEMENTRADA,FRAMESEMENTRADA,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,IMICONSEMENTRADA,60,40,90,90);

  pvQPushButton(p,BUTSEMENTRADA,FRAMESEMENTRADA);
  pvSetGeometry(p,BUTSEMENTRADA,115,35,70,50);
  pvSetText(p,BUTSEMENTRADA,pvtr("ENCENCIDO\nMANUAL"));
  pvSetFont(p,BUTSEMENTRADA,"Verdana",7,1,0,0,0);
  
  pvSetEnabled(p,FRAMESEMENTRADA,1);
  /*******************************************/
  /*FRAME CON EL ICONO DEL PERMISO DE ENTRADA*/
  pvQFrame(p,FRAMEPERMISOENTRADA,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEPERMISOENTRADA,1540,10,170,90);
  pvSetFont(p,FRAMEPERMISOENTRADA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABPERMISOENTRADA,FRAMEPERMISOENTRADA);
  pvSetGeometry(p,LABPERMISOENTRADA,15,5,140,30);
  pvSetText(p,LABPERMISOENTRADA,pvtr("PERMISO"));
  pvSetFont(p,LABPERMISOENTRADA,"Default",20,1,1,0,0);

  pvQImage(p,IMICONPERMISOENTRADA,FRAMEPERMISOENTRADA,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,IMICONPERMISOENTRADA,65,40,90,90);
  pvSetFont(p,IMICONPERMISOENTRADA,"Verdana",12,1,0,0,0);
  pvSetWhatsThis(p,IMICONPERMISOENTRADA,pvtr("image/grey.png"));
  pvSetEnabled(p,FRAMEPERMISOENTRADA,0);
  /*******************************************/
  pvQFrame(p,FRAMEPESOENT,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEPESOENT,895,310,365,90);
  pvSetFont(p,FRAMEPESOENT,"Verdana",12,1,0,0,0);
  pvSetWhatsThis(p,FRAMEPESOENT,pvtr("image/grey.png"));

  pvQLabel(p,LABPESOENT,FRAMEPESOENT);
  pvSetGeometry(p,LABPESOENT,40,5,85,30);
  pvSetText(p,LABPESOENT,pvtr("PESO"));
  pvSetFont(p,LABPESOENT,"Default",20,1,1,0,0);

  pvQLineEdit(p,EDITPESOENT,FRAMEPESOENT);
  pvSetGeometry(p,EDITPESOENT,58,40,110,40);
  pvSetFont(p,EDITPESOENT,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITPESOENT,0);

  pvQPushButton(p,BUTEDITPESOENT,FRAMEPESOENT);
  pvSetGeometry(p,BUTEDITPESOENT,15,40,43,40);
  pvSetPixmap(p,BUTEDITPESOENT,"image/edit.png",0);

  pvQLabel(p,LOADINGPESOENT,FRAMEPESOENT);
  pvSetGeometry(p,LOADINGPESOENT,5,-15,180,140);
  pvSetFont(p,LOADINGPESOENT,"Default",18,1,1,0,0);
  pvSetWhatsThis(p,LOADINGPESOENT,pvtr("image/grey.png"));

  pvQLabel(p,LABKGENT,FRAMEPESOENT);
  pvSetGeometry(p,LABKGENT,168,45,40,30);
  pvSetText(p,LABKGENT,pvtr("Kg"));
  pvSetFont(p,LABKGENT,"Default",18,1,1,0,0);

  pvQPushButton(p,BUTPESOENT,FRAMEPESOENT);
  pvSetGeometry(p,BUTPESOENT,213,30,140,50);
  pvSetText(p,BUTPESOENT,pvtr("PESAR"));
  pvSetFont(p,BUTPESOENT,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,FRAMEPESOENT,0);

  pvQFrame(p,FRAMECOMMENTENT,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECOMMENTENT,1340,110,370,185);
  pvSetFont(p,FRAMECOMMENTENT,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABCOMMENTENT,FRAMECOMMENTENT);
  pvSetGeometry(p,LABCOMMENTENT,30,5,220,30);
  pvSetText(p,LABCOMMENTENT,pvtr("COMENTARIO:"));
  pvSetFont(p,LABCOMMENTENT,"Default",14,1,1,0,0);

  pvQMultiLineEdit(p,EDITCOMMENTENT,FRAMECOMMENTENT,1,-1);
  pvSetGeometry(p,EDITCOMMENTENT,10,35,350,140);
  pvSetFont(p,EDITCOMMENTENT,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAMESEPARACION,CENTRALFORM,Box,Plain,4,1);
  pvSetGeometry(p,FRAMESEPARACION,10,423,1730,4);
  pvSetPaletteForegroundColor(p,FRAMESEPARACION,200,200,200);
  pvSetFont(p,FRAMESEPARACION,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAMEBUTTONS,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEBUTTONS,1455,310,260,250);
  pvSetPaletteBackgroundColor(p,FRAMEBUTTONS,200,220,220);
  pvSetFont(p,FRAMEBUTTONS,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABBUTTONS,FRAMEBUTTONS);
  pvSetGeometry(p,LABBUTTONS,7,7,160,30);
  pvSetText(p,LABBUTTONS,pvtr("Controles"));
  pvSetFont(p,LABBUTTONS,"Default",20,1,1,0,0);

  pvQPushButton(p,BUTPROCEDER_E1,FRAMEBUTTONS);
  pvSetGeometry(p,BUTPROCEDER_E1,15,47,230,60);
  pvSetText(p,BUTPROCEDER_E1,pvtr("PROCEDER"));
  pvSetFont(p,BUTPROCEDER_E1,"Verdana",18,1,0,0,0);

  pvQPushButton(p,BUTCANCELAR_E1,FRAMEBUTTONS);
  pvSetGeometry(p,BUTCANCELAR_E1,15,114,230,60);
  pvSetText(p,BUTCANCELAR_E1,pvtr("CANCELAR"));
  pvSetFont(p,BUTCANCELAR_E1,"Default",16,1,0,0,0);

  pvQPushButton(p,BUTRETROCEDER_E1,FRAMEBUTTONS);
  pvSetGeometry(p,BUTRETROCEDER_E1,15,181,230,60);
  pvSetText(p,BUTRETROCEDER_E1,pvtr("<-RETROCEDER"));
  pvSetFont(p,BUTRETROCEDER_E1,"Default",16,1,0,0,0);
  pvSetEnabled(p,FRAMEBUTTONS,0);

  pvQFrame(p,FRAMETRANSITO,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMETRANSITO,155,480,260,320);
  pvSetFont(p,FRAMETRANSITO,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABTRANSITO,FRAMETRANSITO);
  pvSetGeometry(p,LABTRANSITO,15,5,180,40);
  pvSetText(p,LABTRANSITO,pvtr("Vehículos en\ntránsito"));
  pvSetFont(p,LABTRANSITO,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTDELETRANS,FRAMETRANSITO);
  pvSetGeometry(p,BUTDELETRANS,207,5,43,50);
  pvSetPixmap(p,BUTDELETRANS,"image/edit-delete.png",0);

  pvQListBox(p,TABLATRANSITO,FRAMETRANSITO);
  pvSetGeometry(p,TABLATRANSITO,10,60,240,250);
  pvSetMultiSelection(p,TABLATRANSITO,0);
  pvSetFont(p,TABLATRANSITO,"Verdana",12,1,0,0,0);
  pvSetEnabled(p,FRAMETRANSITO,0);

  pvQFrame(p,FRAMECAM_E2,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECAM_E2,440,480,320,320);
  pvSetFont(p,FRAMECAM_E2,"Verdana",12,1,0,0,0);

  pvQImage(p,IMCAM_E2,FRAMECAM_E2,"image/image.jpg",&w,&h,&depth);
  pvSetGeometry(p,IMCAM_E2,15,70,288,216);
  pvSetFont(p,IMCAM_E2,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,IMCAM_E2,pvtr("image/image.jpg"));

  pvQPushButton(p,BUTCAM_E2,FRAMECAM_E2);
  pvSetGeometry(p,BUTCAM_E2,15,10,120,50);
  pvSetText(p,BUTCAM_E2,pvtr("Tomar \nMatrícula"));
  pvSetFont(p,BUTCAM_E2,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITCAM_E2,FRAMECAM_E2);
  pvSetGeometry(p,EDITCAM_E2,183,10,120,50);
  //pvSetText(p,EDITCAM_E2,pvtr("MATRICULA"));
  pvSetFont(p,EDITCAM_E2,"Default",12,1,0,0,0);
  pvSetEditable(p,EDITCAM_E2,0);

  pvQLabel(p,LOADINGCAM2,FRAMECAM_E2);
  pvSetGeometry(p,LOADINGCAM2,-65,40,441,291);
  pvSetFont(p,LOADINGCAM2,"Verdana",12,1,0,0,0);
  pvSetWhatsThis(p,LOADINGCAM2,pvtr("image/image.jpg"));

  pvQPushButton(p,BUTEDITCAM2,FRAMECAM_E2);
  pvSetGeometry(p,BUTEDITCAM2,140,10,43,50);
  pvSetPixmap(p,BUTEDITCAM2,"image/edit.png",0);
  pvSetEnabled(p,FRAMECAM_E2,0);

  /* FRAME DI DEFINITIVO*/
  pvQFrame(p,FDIDEF,CENTRALFORM,Box,Plain,1,1); 
  pvSetGeometry(p,FDIDEF,785,480,500,160);
  pvSetFont(p,FDIDEF,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABDIDEF,FDIDEF);
  pvSetGeometry(p,LABDIDEF,30,5,220,30);
  pvSetText(p,LABDIDEF,pvtr("DI. DEFINITIVO  >>"));
  pvSetFont(p,LABDIDEF,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITDIDEF,FDIDEF);
  pvSetGeometry(p,EDITDIDEF,20,40,320,30);
  pvSetFont(p,EDITDIDEF,"Default",12,1,0,0,0);

  pvQLabel(p,LABSTATUSDIDEF,FDIDEF);
  pvSetGeometry(p,LABSTATUSDIDEF,250,5,220,30);
  pvSetText(p,LABSTATUSDIDEF,pvtr("N/A"));
  pvSetFont(p,LABSTATUSDIDEF,"Default",14,1,1,0,0);
  pvSetFontColor(p,LABSTATUSDIDEF,220,220,220);

  pvQPushButton(p,BUTEDITDIDEF,FDIDEF);
  pvSetGeometry(p,BUTEDITDIDEF,345,35,145,40);
  pvSetText(p,BUTEDITDIDEF,pvtr("EDITAR"));
  pvSetFont(p,BUTEDITDIDEF,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,FDIDEF,0);

  pvQLabel(p,LABTRANSP,FDIDEF);
  pvSetGeometry(p,LABTRANSP,30,85,220,30);
  pvSetText(p,LABTRANSP,pvtr("TRANSPORTISTA"));
  pvSetFont(p,LABTRANSP,"Default",14,1,1,0,0);

  pvQLineEdit(p,EDITCODETRANSP,FDIDEF);
  pvSetGeometry(p,EDITCODETRANSP,20,120,100,30);
  pvSetFont(p,EDITCODETRANSP,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITNAMETRANSP,FDIDEF);
  pvSetGeometry(p,EDITNAMETRANSP,125,120,365,30);
  pvSetFont(p,EDITNAMETRANSP,"Default",12,1,0,0,0); 
  
  /*FIN FRAME DI DEFINITIVO*/
  
  pvQFrame(p,FRAMEPESOTARA,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEPESOTARA,785,655,360,145);
  pvSetFont(p,FRAMEPESOTARA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABPESOTARA,FRAMEPESOTARA);
  pvSetGeometry(p,LABPESOTARA,40,5,120,30);
  pvSetText(p,LABPESOTARA,pvtr("TARA"));
  pvSetFont(p,LABPESOTARA,"Default",20,1,1,0,0);

  pvQLineEdit(p,EDITPESOTARA,FRAMEPESOTARA);
  pvSetGeometry(p,EDITPESOTARA,58,40,110,40);
  pvSetFont(p,EDITPESOTARA,"Default",12,1,0,0,0);
  pvSetEnabled(p,EDITPESOTARA,0);

  pvQPushButton(p,BUTEDITPESOSAL,FRAMEPESOTARA);
  pvSetGeometry(p,BUTEDITPESOSAL,15,40,43,40);
  pvSetPixmap(p,BUTEDITPESOSAL,"image/edit.png",0);

  pvQLabel(p,LOADINGPESOTARA,FRAMEPESOTARA);
  pvSetGeometry(p,LOADINGPESOTARA,38,-15,180,140);
  pvSetFont(p,LOADINGPESOTARA,"Default",18,1,1,0,0);

  pvQLabel(p,LABKGTARA,FRAMEPESOTARA);
  pvSetGeometry(p,LABKGTARA,168,45,40,30);
  pvSetText(p,LABKGTARA,pvtr("Kg"));
  pvSetFont(p,LABKGTARA,"Default",18,1,1,0,0);

  pvQPushButton(p,BUTPESOTARA,FRAMEPESOTARA);
  pvSetGeometry(p,BUTPESOTARA,208,30,140,50);
  pvSetText(p,BUTPESOTARA,pvtr("PESAR"));
  pvSetFont(p,BUTPESOTARA,"Verdana",13,1,0,0,0);

  pvQImage(p,ICONPERMISOPESOSAL,FRAMEPESOTARA,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONPERMISOPESOSAL,15,90,45,45);
  pvSetWhatsThis(p,ICONPERMISOPESOSAL,pvtr(""));

  pvQImage(p,ICONSATUSPESOSAL,FRAMEPESOTARA,"image/void.png",&w,&h,&depth);
  pvSetGeometry(p,ICONSATUSPESOSAL,65,95,35,35);
  pvSetWhatsThis(p,ICONSATUSPESOSAL,pvtr(""));
  
  pvQLabel(p,LABDEFAULTPESOSAL,FRAMEPESOTARA);
  pvSetGeometry(p,LABDEFAULTPESOSAL,100,95,250,30);
  pvSetText(p,LABDEFAULTPESOSAL,pvtr("()"));
  pvSetFont(p,LABDEFAULTPESOSAL,"Default",16,1,1,0,0);
  pvSetEnabled(p,FRAMEPESOTARA,0);

  pvQPushButton(p,BUTFIRMAR,CENTRALFORM);
  pvSetGeometry(p,BUTFIRMAR,1160,655,170,70);
  pvSetText(p,BUTFIRMAR,pvtr("FIRMAR\nMOVIMIENTO"));
  pvSetFont(p,BUTFIRMAR,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,BUTFIRMAR,0);

  pvQPushButton(p,BUTRETENER,CENTRALFORM);
  pvSetGeometry(p,BUTRETENER,1160,735,170,70);
  pvSetText(p,BUTRETENER,pvtr("RETENER\nTRANSPORTE"));
  pvSetFont(p,BUTRETENER,"Verdana",13,1,0,0,0);
  pvSetEnabled(p,BUTRETENER,0);

  pvQFrame(p,FRAMECOMMENTSAL,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECOMMENTSAL,1350,575,360,190);
  pvSetFont(p,FRAMECOMMENTSAL,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABCOMMENTSAL,FRAMECOMMENTSAL);
  pvSetGeometry(p,LABCOMMENTSAL,30,5,220,30);
  pvSetText(p,LABCOMMENTSAL,pvtr("COMENTARIO:"));
  pvSetFont(p,LABCOMMENTSAL,"Default",14,1,1,0,0);

  pvQMultiLineEdit(p,EDITCOMMENTSAL,FRAMECOMMENTSAL,1,-1);
  pvSetGeometry(p,EDITCOMMENTSAL,10,35,340,145);
  pvSetFont(p,EDITCOMMENTSAL,"Verdana",12,1,0,0,0);

  /*FRAME DEL SEMÁFORO DE SALIDA*/    
  pvQFrame(p,FRAMESEMSALIDA,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMESEMSALIDA,1292,480,155,90);
  pvSetFont(p,FRAMESEMSALIDA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABSEMSALIDA,FRAMESEMSALIDA);
  pvSetGeometry(p,LABSEMSALIDA,15,5,140,30);
  pvSetText(p,LABSEMSALIDA,pvtr("SEMÁFORO:"));
  pvSetFont(p,LABSEMSALIDA,"Default",14,1,1,0,0);

  pvQImage(p,IMICONSEMSALIDA,FRAMESEMSALIDA,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,IMICONSEMSALIDA,30,40,90,90);

  pvQPushButton(p,BUTSEMSALIDA,FRAMESEMSALIDA);
  pvSetGeometry(p,BUTSEMSALIDA,80,35,70,50);
  pvSetText(p,BUTSEMSALIDA,pvtr("ENCENCIDO\nMANUAL"));
  pvSetFont(p,BUTSEMSALIDA,"Verdana",7,1,0,0,0);
 
  pvSetEnabled(p,FRAMESEMSALIDA,0);
  /*******************************************/

  pvQPushButton(p,BUTSINCRONIZA,0);
  pvSetGeometry(p,BUTSINCRONIZA,1400,30,165,60);
  pvSetText(p,BUTSINCRONIZA,pvtr("SINCRONIZAR\nBASE DE DATOS"));
  pvSetFont(p,BUTSINCRONIZA,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUTTEST,0);
  pvSetGeometry(p,BUTTEST,1220,30,165,60);
  pvSetText(p,BUTTEST,pvtr("TEST\nFIRMA"));
  pvSetFont(p,BUTTEST,"Verdana",13,1,0,0,0);

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
  pvSetWhatsThis(p,LOGOBIO,pvtr("image/logo_costumer_trans.png"));


  pvQImage(p,LOGOPRO,0,"image/log_nuevo_completo_transp_red.png",&w,&h,&depth);
  pvSetGeometry(p,LOGOPRO,1545,920,395,95);
  pvSetFont(p,LOGOPRO,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,LOGOPRO,pvtr(""));

  pvQLabel(p,LOADINGFORM,0);
  pvSetGeometry(p,LOADINGFORM,540,220,640,480);
  
  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask4_slots.h"

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


int show_mask4(PARAM *p)
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
