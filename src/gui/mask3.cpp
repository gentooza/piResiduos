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
// show_mask3 for ProcessViewServer created: vie mar 17 10:49:57 2017
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
  CHKENTRADA,
  CHKSALIDA,
  FRAMECLIENTES,
  COMBOCLIENTES,
  COMBOLERS,
  LABCLIENTES,
  LABLERS,
  EDITCLIENTES,
  EDITLERS,
  EDITPRODUCTO,
  ICONPERM,
  LABPERM,
  ICONFECHCONTR,
  LABFECHCONTR,
  ICONFECHNPRT,
  LABFECHNPRT,
  ICONCB,
  LABCB,
  ICONCP,
  LABCP,
  FRAMECAM_E1,
  IMCAM,
  BUTCAM,
  EDITCAM,
  BUTCANCELAR_E1,
  FRAMEPERMISOENTRADA,
  LABPERMISOENTRADA,
  IMICONPERMISOENTRADA,
  FRAMEPESOENT,
  LABPESOENT,
  EDITPESOENT,
  LABKGENT,
  BUTPROCEDER_E1,
  BUTRETROCEDER_E1,
  TABLATRANSITO,
  FRAMECAM_E2,
  IMCAM_E2,
  BUTCAM_E2,
  EDITCAM_E2,
  OUTPUT,
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
  "CHKENTRADA",
  "CHKSALIDA",
  "FRAMECLIENTES",
  "COMBOCLIENTES",
  "COMBOLERS",
  "LABCLIENTES",
  "LABLERS",
  "EDITCLIENTES",
  "EDITLERS",
  "EDITPRODUCTO",
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
  "FRAMECAM_E1",
  "IMCAM",
  "BUTCAM",
  "EDITCAM",
  "BUTCANCELAR_E1",
  "FRAMEPERMISOENTRADA",
  "LABPERMISOENTRADA",
  "IMICONPERMISOENTRADA",
  "FRAMEPESOENT",
  "LABPESOENT",
  "EDITPESOENT",
  "LABKGENT",
  "BUTPROCEDER_E1",
  "BUTRETROCEDER_E1",
  "TABLATRANSITO",
  "FRAMECAM_E2",
  "IMCAM_E2",
  "BUTCAM_E2",
  "EDITCAM_E2",
  "OUTPUT",
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
  "image/grey.png",
  "",
  "image/grey.png",
  "",
  "image/grey.png",
  "",
  "image/grey.png",
  "",
  "image/grey.png",
  "",
  "image/image.jpg",
  "image/image.jpg",
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
  "image/image.jpg",
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
  TQRadio,
  TQRadio,
  TQFrame,
  TQComboBox,
  TQComboBox,
  TQLabel,
  TQLabel,
  TQLineEdit,
  TQLineEdit,
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
  TQFrame,
  TQImage,
  TQPushButton,
  TQLineEdit,
  TQPushButton,
  TQFrame,
  TQLabel,
  TQImage,
  TQFrame,
  TQLabel,
  TQLineEdit,
  TQLabel,
  TQPushButton,
  TQPushButton,
  TQListView,
  TQFrame,
  TQImage,
  TQPushButton,
  TQLineEdit,
  TQMultiLineEdit,
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
  pvSetGeometry(p,LABTITLE,6,6,200,50);
  pvSetText(p,LABTITLE,pvtr("SALIDAS"));
  pvSetFont(p,LABTITLE,"Verdana",16,1,1,0,0);

  pvQLabel(p,LABTYPE,0);
  pvSetGeometry(p,LABTYPE,300,6,600,50);
  pvSetText(p,LABTYPE,pvtr("TIPO DE ESTACIÓN Y NOMBRE"));
  pvSetFont(p,LABTYPE,"Verdana",20,1,1,0,0);

  pvQPushButton(p,BUT1,0);
  pvSetGeometry(p,BUT1,1,220,120,50);
  pvSetText(p,BUT1,pvtr("ENTRADAS"));
  pvSetFont(p,BUT1,"Verdana",12,1,0,0,0);

  pvQPushButton(p,BUT3,0);
  pvSetGeometry(p,BUT3,1,500,120,50);
  pvSetText(p,BUT3,pvtr("CONFIG."));
  pvSetFont(p,BUT3,"Verdana",12,1,0,0,0);

  pvQPushButton(p,BUT2,0);
  pvSetGeometry(p,BUT2,1,360,120,50);
  pvSetText(p,BUT2,pvtr("SALIDAS"));
  pvSetFont(p,BUT2,"Verdana",12,1,0,0,0);

  pvQFrame(p,CENTRALFORM,0,Panel,Sunken,2,1);
  pvSetGeometry(p,CENTRALFORM,135,60,1800,800);
  pvSetFont(p,CENTRALFORM,"Verdana",12,1,0,0,0);

  pvQRadioButton(p,CHKENTRADA,CENTRALFORM);
  pvSetGeometry(p,CHKENTRADA,25,192,120,40);
  pvSetText(p,CHKENTRADA,pvtr("EMPEZAR\nDESCARGA"));
  pvSetFont(p,CHKENTRADA,"Courier",12,1,0,0,0);

  pvQRadioButton(p,CHKSALIDA,CENTRALFORM);
  pvSetGeometry(p,CHKSALIDA,25,576,120,40);
  pvSetText(p,CHKSALIDA,pvtr("FINALIZAR\nDESCARGA"));
  pvSetFont(p,CHKSALIDA,"Courier",12,1,0,0,0);

  pvQFrame(p,FRAMECLIENTES,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECLIENTES,140,10,275,300);
  pvSetFont(p,FRAMECLIENTES,"Verdana",12,1,0,0,0);

  pvQComboBox(p,COMBOCLIENTES,FRAMECLIENTES,0,AtBottom);
  pvSetGeometry(p,COMBOCLIENTES,10,35,125,30);
  pvSetFont(p,COMBOCLIENTES,"Default",12,1,0,0,0);

  pvQComboBox(p,COMBOLERS,FRAMECLIENTES,0,AtBottom);
  pvSetGeometry(p,COMBOLERS,10,105,125,30);
  pvSetFont(p,COMBOLERS,"Default",12,1,0,0,0);

  pvQLabel(p,LABCLIENTES,FRAMECLIENTES);
  pvSetGeometry(p,LABCLIENTES,115,5,99,30);
  pvSetText(p,LABCLIENTES,pvtr("Cliente"));
  pvSetFont(p,LABCLIENTES,"Default",12,1,0,0,0);

  pvQLabel(p,LABLERS,FRAMECLIENTES);
  pvSetGeometry(p,LABLERS,130,75,99,30);
  pvSetText(p,LABLERS,pvtr("LER"));
  pvSetFont(p,LABLERS,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITCLIENTES,FRAMECLIENTES);
  pvSetGeometry(p,EDITCLIENTES,150,35,115,30);
  pvSetFont(p,EDITCLIENTES,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITLERS,FRAMECLIENTES);
  pvSetGeometry(p,EDITLERS,150,105,115,30);
  pvSetFont(p,EDITLERS,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITPRODUCTO,FRAMECLIENTES);
  pvSetGeometry(p,EDITPRODUCTO,10,155,255,30);
  pvSetFont(p,EDITPRODUCTO,"Default",12,1,0,0,0);


  pvQImage(p,ICONPERM,FRAMECLIENTES,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONPERM,10,195,20,20);
  pvSetFont(p,ICONPERM,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONPERM,pvtr("image/grey.png"));

  pvQLabel(p,LABPERM,FRAMECLIENTES);
  pvSetGeometry(p,LABPERM,35,195,70,20);
  pvSetText(p,LABPERM,pvtr("Permiso"));
  pvSetFont(p,LABPERM,"Default",10,1,0,0,0);


  pvQImage(p,ICONFECHCONTR,FRAMECLIENTES,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONFECHCONTR,10,230,20,20);
  pvSetFont(p,ICONFECHCONTR,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONFECHCONTR,pvtr("image/grey.png"));

  pvQLabel(p,LABFECHCONTR,FRAMECLIENTES);
  pvSetGeometry(p,LABFECHCONTR,35,220,80,40);
  pvSetText(p,LABFECHCONTR,pvtr("Fecha \ncontrato"));
  pvSetFont(p,LABFECHCONTR,"Default",10,1,0,0,0);


  pvQImage(p,ICONFECHNPRT,FRAMECLIENTES,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONFECHNPRT,10,265,20,20);
  pvSetFont(p,ICONFECHNPRT,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONFECHNPRT,pvtr("image/grey.png"));

  pvQLabel(p,LABFECHNPRT,FRAMECLIENTES);
  pvSetGeometry(p,LABFECHNPRT,35,255,80,40);
  pvSetText(p,LABFECHNPRT,pvtr("Fecha \nNPT"));
  pvSetFont(p,LABFECHNPRT,"Default",10,1,0,0,0);


  pvQImage(p,ICONCB,FRAMECLIENTES,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONCB,120,210,20,20);
  pvSetFont(p,ICONCB,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONCB,pvtr("image/grey.png"));

  pvQLabel(p,LABCB,FRAMECLIENTES);
  pvSetGeometry(p,LABCB,145,200,120,40);
  pvSetText(p,LABCB,pvtr("Caracterización \nbásica"));
  pvSetFont(p,LABCB,"Default",10,1,0,0,0);


  pvQImage(p,ICONCP,FRAMECLIENTES,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,ICONCP,120,245,20,20);
  pvSetFont(p,ICONCP,"Sans Serif",9,0,0,0,0);
  pvSetWhatsThis(p,ICONCP,pvtr("image/grey.png"));

  pvQLabel(p,LABCP,FRAMECLIENTES);
  pvSetGeometry(p,LABCP,145,235,120,40);
  pvSetText(p,LABCP,pvtr("Caracterización \npeligro"));
  pvSetFont(p,LABCP,"Default",10,1,0,0,0);

  pvQFrame(p,FRAMECAM_E1,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECAM_E1,425,10,300,300);
  pvSetFont(p,FRAMECAM_E1,"Verdana",12,1,0,0,0);
  pvSetWhatsThis(p,FRAMECAM_E1,pvtr("image/image.jpg"));


  pvQImage(p,IMCAM,FRAMECAM_E1,"image/image.jpg",&w,&h,&depth);
  pvSetGeometry(p,IMCAM,5,70,288,216);
  pvSetFont(p,IMCAM,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,IMCAM,pvtr("image/image.jpg"));

  pvQPushButton(p,BUTCAM,FRAMECAM_E1);
  pvSetGeometry(p,BUTCAM,25,10,120,50);
  pvSetText(p,BUTCAM,pvtr("Tomar \nMatrícula"));
  pvSetFont(p,BUTCAM,"Default",12,1,0,0,0);

  pvQLineEdit(p,EDITCAM,FRAMECAM_E1);
  pvSetGeometry(p,EDITCAM,160,10,120,50);
  pvSetText(p,EDITCAM,pvtr("MATRICULA"));
  pvSetFont(p,EDITCAM,"Default",12,1,0,0,0);

  pvQPushButton(p,BUTCANCELAR_E1,CENTRALFORM);
  pvSetGeometry(p,BUTCANCELAR_E1,800,205,160,40);
  pvSetText(p,BUTCANCELAR_E1,pvtr("CANCELAR"));
  pvSetFont(p,BUTCANCELAR_E1,"Default",12,1,0,0,0);

  pvQFrame(p,FRAMEPERMISOENTRADA,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEPERMISOENTRADA,735,10,150,90);
  pvSetFont(p,FRAMEPERMISOENTRADA,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABPERMISOENTRADA,FRAMEPERMISOENTRADA);
  pvSetGeometry(p,LABPERMISOENTRADA,5,5,140,30);
  pvSetText(p,LABPERMISOENTRADA,pvtr("PERMISO"));
  pvSetFont(p,LABPERMISOENTRADA,"Default",20,1,1,0,0);


  pvQImage(p,IMICONPERMISOENTRADA,FRAMEPERMISOENTRADA,"image/grey.png",&w,&h,&depth);
  pvSetGeometry(p,IMICONPERMISOENTRADA,55,40,90,90);
  pvSetWhatsThis(p,IMICONPERMISOENTRADA,pvtr("image/grey.png"));

  pvQFrame(p,FRAMEPESOENT,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMEPESOENT,895,10,160,90);
  pvSetFont(p,FRAMEPESOENT,"Verdana",12,1,0,0,0);

  pvQLabel(p,LABPESOENT,FRAMEPESOENT);
  pvSetGeometry(p,LABPESOENT,30,5,80,30);
  pvSetText(p,LABPESOENT,pvtr("PESO"));
  pvSetFont(p,LABPESOENT,"Default",20,1,1,0,0);

  pvQLineEdit(p,EDITPESOENT,FRAMEPESOENT);
  pvSetGeometry(p,EDITPESOENT,5,40,110,30);
  pvSetText(p,EDITPESOENT,pvtr("Kg"));
  pvSetFont(p,EDITPESOENT,"Default",12,1,0,0,0);

  pvQLabel(p,LABKGENT,FRAMEPESOENT);
  pvSetGeometry(p,LABKGENT,115,40,40,30);
  pvSetText(p,LABKGENT,pvtr("Kg"));
  pvSetFont(p,LABKGENT,"Default",18,1,1,0,0);

  pvQPushButton(p,BUTPROCEDER_E1,CENTRALFORM);
  pvSetGeometry(p,BUTPROCEDER_E1,800,140,160,40);
  pvSetText(p,BUTPROCEDER_E1,pvtr("PROCEDER"));
  pvSetFont(p,BUTPROCEDER_E1,"Verdana",13,1,0,0,0);

  pvQPushButton(p,BUTRETROCEDER_E1,CENTRALFORM);
  pvSetGeometry(p,BUTRETROCEDER_E1,800,270,160,40);
  pvSetText(p,BUTRETROCEDER_E1,pvtr("<-RETROCEDER"));
  pvSetFont(p,BUTRETROCEDER_E1,"Default",13,1,0,0,0);

  pvQListView(p,TABLATRANSITO,CENTRALFORM);
  pvSetGeometry(p,TABLATRANSITO,162,498,180,260);
  pvSetMultiSelection(p,TABLATRANSITO,0);
  pvSetFont(p,TABLATRANSITO,"Verdana",12,1,0,0,0);

  pvQFrame(p,FRAMECAM_E2,CENTRALFORM,Box,Plain,1,1);
  pvSetGeometry(p,FRAMECAM_E2,360,498,300,280);
  pvSetFont(p,FRAMECAM_E2,"Verdana",12,1,0,0,0);


  pvQImage(p,IMCAM_E2,FRAMECAM_E2,"image/image.jpg",&w,&h,&depth);
  pvSetGeometry(p,IMCAM_E2,5,50,288,216);
  pvSetFont(p,IMCAM_E2,"Default",9,0,0,0,0);
  pvSetWhatsThis(p,IMCAM_E2,pvtr("image/image.jpg"));

  pvQPushButton(p,BUTCAM_E2,FRAMECAM_E2);
  pvSetGeometry(p,BUTCAM_E2,25,5,120,40);
  pvSetText(p,BUTCAM_E2,pvtr("Tomar \nMatrícula"));
  pvSetFont(p,BUTCAM_E2,"Default",10,1,0,0,0);

  pvQLineEdit(p,EDITCAM_E2,FRAMECAM_E2);
  pvSetGeometry(p,EDITCAM_E2,160,5,120,40);
  pvSetText(p,EDITCAM_E2,pvtr("MATRICULA"));
  pvSetFont(p,EDITCAM_E2,"Default",11,1,0,0,0);

  pvQMultiLineEdit(p,OUTPUT,0,0,5);
  pvSetGeometry(p,OUTPUT,5,900,1420,60);
  pvSetFont(p,OUTPUT,"Sans Serif",9,0,0,0,0);


  pvEndDefinition(p);
  return 0;
}

// _end_of_generated_area_ (do not edit -> use ui2pvc) ---------------------

#include "mask3_slots.h"

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


int show_mask3(PARAM *p)
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
