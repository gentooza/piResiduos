/*
This file is part of PiResiduos.

Copyright 2017-2019, Pro Integra SL, Pixelada S. Coop. And <info@pixelada.org>.

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

#ifndef _MASK4_ACTUALIZA_
#define _MASK4_ACTUALIZA_

static int actualizaForm(PARAM *p,DATA* d, int estado)
{
  //std::cout << "ACTUALIZAMOS FORMULARIO AL ESTADO: " << estado << std::endl;
  switch(estado)
    {
    case -100:
      //loading
      pvHide(p,LOADINGFORM);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      toolsDeactivateGUI(p,d,2,formEntrada);
      /**COMMON**/
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0);    
      /****/    
    case(-2):  //animation state
    case(98): //saving arrival data
    case(1021)://analysing Signature
    case(1035)://signing
    case 1023: //retrieving all DI data
    case(1097):
    case (1098)://saving final data
      pvSetMovie(p,LOADINGFORM,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGFORM,-2); // restart
      pvShow(p,LOADINGFORM);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      toolsDeactivateGUI(p,d,2,formEntrada);
      /**COMMON**/
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0);    
      /****/
      break;			
    case(0)://loading state 1
      pvHide(p,LOADINGFORM);
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_SELECTED);
      pvSetEnabled(p,CHCKAUTMATRI,0);
      pvSetEnabled(p,CHCKNOREGISTRADO,0);
      pvSetEnabled(p,IMCAM,1);
      pvShow(p,IMCAM);
      pvSetEnabled(p,BUTCAM,1);
      pvSetFocus(p,BUTCAM);
      pvSetEnabled(p,EDITCAM,1);
      pvSetEnabled(p,BUTEDITCAM,1);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      pvSetImage(p,ICONAUTMATRI,"image/grey.png");
      //frame clientes-productos
      setFrame(p,FRAMECLIENTES,FRAME_DISABLED);
      //frame DI PROVISIONAL
      setFrame(p,FDIPROV,FRAME_DISABLED);			
      //frame PESO
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);     
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_DISABLED);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      //FOCUS
      pvSetFocus(p,BUTCAM);
      /****/
      break;
    case(5)://Loading camera pos 1, aniamtion state
      /*ARRIVAL*/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_WORKING);
      pvSetEnabled(p,CHCKAUTMATRI,0);
      pvSetEnabled(p,CHCKNOREGISTRADO,0);
      pvSetEnabled(p,IMCAM,0);
      pvHide(p,IMCAM);
      pvSetEnabled(p,BUTCAM,0);
      pvSetEnabled(p,EDITCAM,0);
      pvSetEnabled(p,BUTEDITCAM,0);
      pvSetMovie(p,LOADINGCAM,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGCAM,-2); // restart
      pvShow(p,LOADINGCAM);
      pvSetImage(p,ICONAUTMATRI,"image/grey.png");
      //frame clientes-productos
      pvSetEnabled(p,FRAMECLIENTES,0);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_DISABLED);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0); 
      /**COMMON**/
      toolsSetNAV(p,d,0);
      break;
    case(6): //ANIMATION STATE
      /**COMMON**/
      toolsSetNAV(p,d,0);
      break;
    case(10): // COSTUMER ELECTION
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_NORMAL);      
      pvShow(p,IMCAM);
      pvSetEnabled(p,BUTCAM,1);
      pvSetEnabled(p,EDITCAM,1);	
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      pvSetImage(p,ICONAUTMATRI,"image/green.png");
      pvSetEnabled(p,CHCKAUTMATRI,0);
      pvSetEnabled(p,CHCKNOREGISTRADO,0);
      //frame clientes-productos
      pvSetEnabled(p,FRAMECLIENTES,1);
      pvSetEnabled(p,COMBOCLIENTES,1);
      setFrame(p,FFCLIENTES,FRAME_SELECTED);
      //pvSetEnabled(p,COMBOPRODUCTOS,0);
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED); 
      //frame DI PROVISIONAL
      setFrame(p,FDIPROV,FRAME_DISABLED);			
      //frame PESO
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);  
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      //FOCUS
      pvSetFocus(p,COMBOCLIENTES);
      break;
    case(120): //PRODUCT ELECTION WHEN AUTORIZED CLIENT
    case(20): //PRODUCT ELECTION
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,FRAMECLIENTES,FRAME_SELECTED);
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      //pvSetEnabled(p,COMBOCLIENTES,0);
      pvSetEnabled(p,EDITCLIENTES,0);
      //pvSetEnabled(p,COMBOPRODUCTOS,1);
      setFrame(p,FFPRODUCTOS,FRAME_SELECTED);
      //pvSetEditable(p,EDITPRODUCTOS,0);
      pvClear(p,COMBOLERS);
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      refreshLerPerms(p,0,formEntrada);
      //pvSetEnabled(p,CHKFORZARPROD,0);
      //frame DI PROVISIONAL
      setFrame(p,FDIPROV,FRAME_DISABLED);			
      //frame PESO
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      //FOCUS
      pvSetFocus(p,COMBOPRODUCTOS);
      break;
    case(121)://PRODUCT CHOSEN, AUTHORIZED CLIENT
    case(21)://PRODUCT CHOSEN
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,FRAMECLIENTES, FRAME_DISABLED);
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      pvSetEnabled(p,EDITCLIENTES,0);
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      pvSetText(p,EDITPRODUCTOS,formEntrada->get_arr_whole_product().c_str());
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      pvSetImage(p,ICONPERM,"image/grey.png");
      pvSetImage(p,ICONFECHCONTR,"image/grey.png");
      pvSetImage(p,ICONFECHNPRT,"image/grey.png");
      pvSetImage(p,ICONCB,"image/grey.png");
      pvSetImage(p,ICONCP,"image/grey.png");    
      pvSetImage(p,ICONDCP,"image/grey.png");
      pvSetEnabled(p,CHKFORZARPROD,0);
      //frame DI PROVISIONAL
      setFrame(p,FDIPROV,FRAME_NORMAL);
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_SELECTED);
      pvSetEnabled(p,BUTPESOENT,1);
      pvHide(p,LOADINGPESOENT);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      //FOCUS
      pvSetFocus(p,BUTPESOENT);
      break;
    case(122)://PRODUCT OK
    case(22)://PRODUCT OK
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      pvSetEnabled(p,EDITCLIENTES,0);
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      ///autorización forzada
      pvSetEnabled(p,CHKFORZARPROD,0);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_NORMAL);
      pvSetEnabled(p,EDITPESOENT,0);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_PROCEDER_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      //FOCUS
      pvSetFocus(p,BUTPROCEDER_E1);
      break;
      /**TAKING TRUCK WEIGTH ANIMATION**/
    case 325:
    case 125://ANIMATION STATE
    case 25://ANIMATION STATE
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_DISABLED);
      //empezamos animación peso
      pvSetEnabled(p,BUTPESOENT,0);
      pvSetMovie(p,LOADINGPESOENT,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGPESOENT,-2); // restart
      pvShow(p,LOADINGPESOENT);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**COMMON**/
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0); 
      break;
    case 326:
    case 126://ANIMATION STATE END
    case 26://ANIMATION STATE END
      break;
      /**END TAKING TRUCK WEIGTH ANIMATION**/
    case(210):
    case(230):
    case(130):
    case(30): //ALL PRODUCTS ELECTION
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //CLIENTS & PRODUCTS FRAMES
      setFrame(p,FRAMECLIENTES,FRAME_SELECTED);	    
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      setFrame(p,EDITCLIENTES,FRAME_DISABLED);
      pvSetText(p,COMBOPRODUCTOS,"MOSTRAR TODOS");
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);      
      setFrame(p,FFALLPRODUCTOS,FRAME_SELECTED);
      setFrame(p,COMBOLERS,FRAME_NORMAL);     
      ///permisos
      refreshLerPerms(p,0,formEntrada);
      ///autorización forzada
      pvSetEnabled(p,CHKFORZARPROD,0);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      pvSetEnabled(p,EDITPESOENT,0);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      //FOCUS
      pvSetFocus(p,COMBOLERS);
      break;
    case(231):
    case(131):
    case(31): //PRODUCT-CLIENT-STATION CHOSEN PROCESSED
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,COMBOCLIENTES,FRAME_DISABLED);
      pvSetEnabled(p,EDITCLIENTES,0);
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      pvSetText(p,COMBOPRODUCTOS,"MOSTRAR TODOS");
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      pvSetEnabled(p,EDITPRODUCTOS,0);
      pvSetText(p,EDITPRODUCTOS,"N/A");
      setFrame(p,FFALLPRODUCTOS,FRAME_SELECTED);
      pvSetEnabled(p,COMBOLERS,1);
      ///permisos
      refreshLerPerms(p,1,formEntrada);
      ///autorización forzada
      pvSetEnabled(p,CHKFORZARPROD,0);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      pvSetEnabled(p,EDITPESOENT,0);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      //where?¿?
      break;
    case(232):
    case(132):
    case(32): //PRODUCT-CLIENT-STATION ALLOWED
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      setFrame(p,FRAMECLIENTES,FRAME_DISABLED);
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      pvSetText(p,COMBOPRODUCTOS,"MOSTRAR TODOS");
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      ///permisos
      refreshLerPerms(p,1,formEntrada);
      ///autorización forzada
      pvSetEnabled(p,CHKFORZARPROD,0);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_SELECTED);
      pvSetEnabled(p,BUTPESOENT,1);
      pvHide(p,LOADINGPESOENT);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPESOENT);
      break;
    case(233):
    case(133):
    case(33): //PRODUCT-CLIENT-STATION NOT ALLOWED
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,COMBOCLIENTES,FRAME_DISABLED);
      pvSetEnabled(p,EDITCLIENTES,0);
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      pvSetText(p,COMBOPRODUCTOS,"MOSTRAR TODOS");
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      pvSetEnabled(p,EDITPRODUCTOS,0);
      pvSetText(p,EDITPRODUCTOS,"N/A");
      setFrame(p,FFALLPRODUCTOS,FRAME_SELECTED);
      pvSetEnabled(p,COMBOLERS,0);
      ///permisos
      refreshLerPerms(p,1,formEntrada);
      ///autorización forzada
      pvSetEnabled(p,CHKFORZARPROD,1);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      pvSetEnabled(p,EDITPESOENT,0);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,CHKFORZARPROD);
      break;
    case 235:
    case 135:
    case 35: //ANIMATION STATE
      //coment
      setFrame(p,FRAMECOMMENTENT,FRAME_DISABLED);
      //starting animation
      pvSetEnabled(p,BUTPESOENT,0);
      pvSetMovie(p,LOADINGPESOENT,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGPESOENT,-2); // restart
      pvShow(p,LOADINGPESOENT);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**COMMON**/
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0);
      break;
    case 236:
    case 136:
    case 36 ://END ANIMATION STATE
      break;
    case 240:
    case 140:
    case 40: //ALL OK, WAITING TO PROCEED
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      pvSetEnabled(p,EDITCLIENTES,0);
      pvSetText(p,COMBOPRODUCTOS,"MOSTRAR TODOS");
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);      
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      ///autorización forzada
      pvSetEnabled(p,CHKFORZARPROD,0);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      //botones
      setFrame(p,FRAMEBUTTONS,FRAME_SELECTED);
      setFrame(p,BUTPROCEDER_E1,FRAME_SELECTED);
      pvSetEnabled(p,BUTCANCELAR_E1,1);
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,125,0,0);
      pvSetEnabled(p,BUTRETROCEDER_E1,1);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,0,125,0);
      pvSetEnabled(p,BUTRETROCEDER_E1,1);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_PROCEDER_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPROCEDER_E1);
      break;
    case 101: //PLATE NO REGISTERED
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_SELECTED);
      pvSetEnabled(p,CHCKAUTMATRI,1);
      pvSetEnabled(p,CHCKNOREGISTRADO,1);
      pvSetEnabled(p,IMCAM,1);
      pvShow(p,IMCAM);
      pvSetEnabled(p,BUTCAM,1);
      pvSetEnabled(p,EDITCAM,1);
      pvSetEnabled(p,BUTEDITCAM,1);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      pvSetImage(p,ICONAUTMATRI,"image/red.png");
      //frame clientes-productos
      setFrame(p,FRAMECLIENTES,FRAME_DISABLED);
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame DI PROVISIONAL
      pvSetEnabled(p,FDIPROV,0);			
      //frame PESO
      pvSetEnabled(p,FRAMEPESOENT,0);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,1);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTCAM);
      /****/
      break;
    case(110): //CLIENT ELECCION AFTER PLATE AUTHORIZATION
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      pvSetImage(p,ICONAUTMATRI,"image/red.png");
      //frame clientes-productos
      setFrame(p,FRAMECLIENTES,FRAME_SELECTED);
      setFrame(p,FFCLIENTES,FRAME_SELECTED);
      pvSetEnabled(p,COMBOCLIENTES,1);
      setFrame(p,EDITCLIENTES,FRAME_DISABLED);
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      //frame DI PROVISIONAL
      setFrame(p,FDIPROV,FRAME_DISABLED);			
      //frame PESO
      setFrame(p,FRAMEPESOENT,FRAME_DISABLED);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,COMBOCLIENTES);
      break;
      /***case 120 is the same as 20***/
      /***case 121 is the same as 21***/
    case(321)://Internal transfer movement
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,FRAMECLIENTES, FRAME_DISABLED);
      //frame DI PROVISIONAL
      setFrame(p,FDIPROV,FRAME_NORMAL);
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_SELECTED);
      pvSetEnabled(p,BUTPESOENT,1);
      pvHide(p,LOADINGPESOENT);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPESOENT);
      break;
    case(322)://PRODUCT OK in internal transfer movements
      /**ARRIVAL**/
      //Frame matricula
      setFrame(p,FRAMECAM_E1,FRAME_DISABLED);
      //frame clientes-productos
      setFrame(p,FFCLIENTES,FRAME_DISABLED);
      pvSetEnabled(p,EDITCLIENTES,0);
      setFrame(p,FFPRODUCTOS,FRAME_DISABLED);
      setFrame(p,FFALLPRODUCTOS,FRAME_DISABLED);
      ///autorización forzada
      pvSetEnabled(p,CHKFORZARPROD,0);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //frame permiso de entrada
      setFrame(p,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      //frame peso
      setFrame(p,FRAMEPESOENT,FRAME_NORMAL);
      pvSetEnabled(p,EDITPESOENT,0);
      //comentario
      setFrame(p,FRAMECOMMENTENT,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_PROCEDER_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      toolsSetArrDep(p,d,0);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      //where?
      break;
    case 1000: //CHOSING EXIT
      pvHide(p,LOADINGFORM);
      /**ARRIVAL**/
      toolsDeactivateGUI(p,d,0,formEntrada);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      //Frame transito
      setFrame(p,FRAMETRANSITO,FRAME_NORMAL); 
      //Frame matricula
      setFrame(p,FRAMECAM_E2,FRAME_SELECTED);
      pvSetEnabled(p,IMCAM_E2,1);
      pvShow(p,IMCAM_E2);
      pvSetEnabled(p,BUTCAM_E2,1);
      pvSetFocus(p,BUTCAM_E2);
      pvSetEnabled(p,EDITCAM_E2,1);
      pvSetEnabled(p,BUTEDITCAM2,1);
      pvSetText(p,LOADINGCAM2,"");
      pvHide(p,LOADINGCAM2);
      //frame DI DEFINITIVO
      setFrame(p,FDIDEF,FRAME_DISABLED);
      pvSetEditable(p,EDITDIDEF,0);
      pvSetText(p,LABSTATUSDIDEF,pvtr("N/A"));
      pvSetFontColor(p,LABSTATUSDIDEF,220,220,220);
      pvSetEnabled(p,BUTEDITDIDEF,0);
      //frame TARA
      setFrame(p,FRAMEPESOTARA,FRAME_DISABLED);
      setPesoSal(p, d,WEIGTH_DISABLED,formEntrada);
      //botones
      pvSetEnabled(p,BUTFIRMAR,0);
      //comentario
      setFrame(p,FRAMECOMMENTSAL,FRAME_DISABLED);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTCAM_E2);
      /****/
      break;
    case(1010)://Loading camera pos 2, animation state
      /*ARRIVAL*/
      //Frame transito
      setFrame(p,FRAMETRANSITO,FRAME_DISABLED);
      //Frame matricula
      setFrame(p,FRAMECAM_E2,FRAME_WORKING);
      pvSetEnabled(p,IMCAM_E2,0);
      pvHide(p,IMCAM_E2);
      pvSetEnabled(p,BUTCAM_E2,0);
      pvSetEnabled(p,EDITCAM_E2,0);
      pvSetEnabled(p,BUTEDITCAM2,0);
      pvSetMovie(p,LOADINGCAM2,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGCAM2,-2); // restart
      pvShow(p,LOADINGCAM2);
      //comentario
      setFrame(p,FRAMECOMMENTSAL,FRAME_DISABLED);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      toolsDeactivateGUI(p,d,0,formEntrada);
      toolsSetArrDep(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0); 
      /**COMMON**/
      toolsSetNAV(p,d,0);
      break;
    case(1011): //ANIMATION STATE
      /**COMMON**/
      toolsSetNAV(p,d,0);
      break;
    case 1020: //TRUCK CHOSEN
      pvHide(p,LOADINGFORM);
      /**ARRIVAL**/
      toolsDeactivateGUI(p,d,0,formEntrada);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      //Frame transito
      setFrame(p,FRAMETRANSITO,FRAME_DISABLED);  
      //Frame matricula
      setFrame(p,FRAMECAM_E2,FRAME_DISABLED);
      //frame DI DEFINITIVO
      setFrame(p,FDIDEF,FRAME_NORMAL);
      pvSetEnabled(p,EDITDIDEF,0);
      pvSetText(p,LABSTATUSDIDEF,pvtr(""));
      pvSetEnabled(p,BUTEDITDIDEF,0);
      //frame TARA
      setFrame(p,FRAMEPESOTARA,FRAME_SELECTED);
      pvHide(p,LOADINGPESOTARA);
      pvSetEnabled(p,BUTPESOTARA,1);
      setPesoSal(p, d,WEIGTH_ANALYSIS,formEntrada);
      //botones firma y retener
      pvSetEnabled(p,BUTFIRMAR,0);
      pvSetEnabled(p,BUTRETENER,1);
      //comentario
      setFrame(p,FRAMECOMMENTSAL,FRAME_NORMAL);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPESOTARA);
      /****/
      break;
    case 1022: //we have to sign the movement
      pvHide(p,LOADINGFORM);
      /**ARRIVAL**/
      toolsDeactivateGUI(p,d,0,formEntrada);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);   
      /**EXIT**/
      //Frame transito
      setFrame(p,FRAMETRANSITO,FRAME_DISABLED);  
      //Frame matricula
      setFrame(p,FRAMECAM_E2,FRAME_DISABLED);
      //frame DI DEFINITIVO
      setFrame(p,FDIDEF,FRAME_NORMAL);
      pvSetEnabled(p,BUTEDITDIDEF,0);
      //frame TARA
      setFrame(p,FRAMEPESOTARA,FRAME_NORMAL);
      pvHide(p,LOADINGPESOTARA);
      setPesoSal(p, d,WEIGTH_ANALYSIS,formEntrada);
      //boton firma
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //comentario
      setFrame(p,FRAMECOMMENTSAL,FRAME_NORMAL);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,1);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTFIRMAR);
      break;
    case(1025): //animation state
      /**COMMON**/
      toolsDeactivateGUI(p,d,2,formEntrada);
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_NONE);
      //empezamos animación peso
      setFrame(p,FRAMEPESOTARA,FRAME_SELECTED);     
      pvSetEnabled(p,BUTPESOTARA,0);
      pvSetMovie(p,LOADINGPESOTARA,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGPESOTARA,-2); // restart
      pvShow(p,LOADINGPESOTARA);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0);
      //FOCUS
      break;
    case(1026): //END ANIMATION STATE
      break;
    case 1030: //DI READY
      pvHide(p,LOADINGFORM);
      //Frame transito
      setFrame(p,FRAMETRANSITO,FRAME_DISABLED); 
      //frame TARA
      setFrame(p,FRAMEPESOTARA,FRAME_NORMAL);
      pvHide(p,LOADINGPESOTARA);
      setPesoSal(p, d,WEIGTH_ANALYSIS,formEntrada);
      //frame DI DEFINITIVO
      setFrame(p,FDIDEF,FRAME_SELECTED);
      pvSetText(p,LABSTATUSDIDEF,pvtr("DI COMPLETO"));
      pvSetFontColor(p,LABSTATUSDIDEF,60,220,60);
      pvSetEnabled(p,BUTEDITDIDEF,1);
      //botones
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //comentario
      setFrame(p,FRAMECOMMENTSAL,FRAME_NORMAL);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_PROCEDER);
      toolsDeactivateGUI(p,d,0,formEntrada);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,1);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPROCEDER_E1);
      break;
    case 1031: //DI NOT READY
      pvHide(p,LOADINGFORM);
      //Frame transito
      setFrame(p,FRAMETRANSITO,FRAME_DISABLED); 
      //frame TARA
      setFrame(p,FRAMEPESOTARA,FRAME_NORMAL);
      pvHide(p,LOADINGPESOTARA);
      setPesoSal(p, d,WEIGTH_ANALYSIS,formEntrada);
      //frame DI DEFINITIVO
      setFrame(p,FDIDEF,FRAME_SELECTED);
      pvSetText(p,LABSTATUSDIDEF,pvtr("DI INCOMPLETO"));
      pvSetFontColor(p,LABSTATUSDIDEF,220,60,60);
      pvSetEnabled(p,BUTEDITDIDEF,1);
      //botones
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //frames semáforos
      setFrame(p,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,FRAMESEMSALIDA,FRAME_NORMAL);
      //comentario
      setFrame(p,FRAMECOMMENTSAL,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_NONE);
      toolsDeactivateGUI(p,d,0,formEntrada);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //focus
      pvSetFocus(p,BUTEDITDIDEF);
      break;		
    default:
      break;	       
    }
  return 0;
}

//acciones
static int actualizaEstado(PARAM *p, DATA *d)
{
  int ret = -1;
  char error[128];
  if(d->enFutEstado != formEntrada->getState())
    {
      switch(d->enFutEstado)
	{
	case -1: //entramos sin un formulario previo
	  {
	    pvSetChecked(p,CHKENTRADA,1);
	    pvSetChecked(p,CHKSALIDA,0);
	    d->productoActual.clear();
	    d->entrarDescargar=1;
	    //globalSyncronization(p,d, formEntrada);	    
	    break;
	  }
	case 0:
	  {
	    popteTransito(p,d,TABLATRANSITO,formEntrada);
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    break;
	  }
	case -100: 	
	    //NUNCA ENTRAREMOS AQUI	  
	  break;
	case 5: //carga cámara 1 	    
	    break;
	case 6: //tomando matrícula
	  {  
	    std::string plate;
	    ret = useCamera(p, d, 1, plate, IMCAM);
	    if(!ret)
	      {
		pvSetText(p,EDITCAM,pvtr(plate.c_str()));
		formEntrada->setArrPlate(plate);
		d->processTag=1;
	      }
	    else
	      {
		d->processTag=-1;
		sprintf(error,"*ERROR* imposible recibir matrícula de la cámara 1");
		console.push_back(error);
	      }
	    break;
	  }
	case 10: //matrícula registrada
	  {
	    //TODO, va fuera!!
	    //seleccionamos clientes para la matrícula seleccionada
	    char * sql =NULL;
	    sel_all_cos_from_car(sql,formEntrada->retArrPlate().c_str());
	    localDatabase.query(p,sql);
	    d->allClientes.clear();
	    d->allClientesCodes.clear();	    
	    std::vector <std::vector <std::string>> dataReturn = localDatabase.retData2();	 
	    for(int i=0;i<dataReturn.size();i++)
	      {
		if(dataReturn[i][0].compare("0"))
		  d->allClientesCodes.push_back(dataReturn[i][0]);
	      }
	    
	    delete sql;
	    for(std::vector <std::string>::iterator iter = d->allClientesCodes.begin(); iter != d->allClientesCodes.end(); ++iter)
	      {
		if(!iter->empty())
		  {
		    selectClientNameByCode(sql,iter->c_str());
		    localDatabase.query(p,sql);
		    dataReturn.clear();
		    dataReturn = localDatabase.retData2();
		    if(dataReturn.size())
		      	d->allClientes.push_back(dataReturn[0][0]);
		    delete sql;
		  }
	      }
	    d->allClientes.push_back("OTROS");
	    d->allClientesCodes.push_back("0");
	    populateCombo(p,COMBOCLIENTES,d->allClientes);
	    /////
	    break;
	  }
	case 120: //AUTHORIZED CLIENT SELECTED, WE SHOW IT'S PRODUCTS ASSOCIATED ALLOWED
	case 20: //cliente seleccionado mostramos todos los productos de ese cliente!
	  {
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);

	    //TODO
	    //fuera de aquí el acceso a la base de datos!
	    char * sql =NULL;
	    std::string clientCode = std::to_string(formEntrada->retArrCosCode());
	    int istation_type = 0;
	    myStation->getType(istation_type);
	    if(formEntrada->retArrCosCode() == DEF_BIORECICLAJE_CODE) //SI ES UNA TRANSFERENCIA LO DEFINIMOS COMO TIPO DE MOVIMIENTO AQUI
	      formEntrada->setArrMovType(DEF_MOV_TRANSFER);
	    else if(istation_type == 3) //deposit
	      formEntrada->setArrMovType(DEF_MOV_INTERNOD5);	      
	    else
	      formEntrada->setArrMovType(DEF_MOV_ENTRADA);

	    std::string strstation_type;
	    myStation->getType(strstation_type);
	    selProdsAllowedToClient(sql,clientCode.c_str(),strstation_type.c_str(),true);
	    localDatabase.query(p,sql);
	    localDatabase.query(p,"select * from resultado");	
	    populateProdsCombo(p,COMBOPRODUCTOS,localDatabase.retData2(),true);
	    localDatabase.query(p,"drop table resultado");
	    d->pesaje1 = 0;
	    break;
	  }
	case 121: //waiting taking weigth, product chosen from authorized client
	case 21: //waiting weigth, product chosen by normal path
	  {
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);	    
	    std::string myDI = formEntrada->createArrDi(localDatabase);
	    //if(!formEntrada->isIncArrPlateEdited()) //chequeo de imagen
	      formEntrada->savePlateImage(1,"entrada");
	    pvSetText(p,EDITDIPROV,myDI.c_str());	    
	  }
	  break;
	case 322:
	case 122: //weigth ok, waiting for proceed
	case 40:
	case 22:
	  refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	  break;
	case 235:
	case 135:
	case 35:
	case 325:
	case 125: //ANIMATION STATE TAKING TRUCK WEIGHT
	case 25: //ANIMATION STATE
	  break;
	case 236:
	case 136:
      	case 36:
	case 326:
	case 126://communication and taking weight
      	case 26: //comm
	  {
	    char error[256];
	    bascula * testBascula = NULL;
	    //reseteamos peso
	    std::string sPesoTest = "0";
	    pvSetText(p,EDITPESOENT,sPesoTest.c_str());
	    formEntrada->setArrScaleIn(0);
	    formEntrada->incArrScaleEdited(0);
	    //
	    sprintf(error,"(INFO) usando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, paridad:%s , control de flujo:%s y %s bits de parada...",1, basculas.at(0).port.c_str(),basculas.at(0).bauds,basculas.at(0).timeout , basculas.at(0).ask.c_str(), (basculas.at(0).parity==0?"ninguna":(basculas.at(0).parity==1?"impar":"par")),(basculas.at(0).ctrl==0?"ninguno":(basculas.at(0).ctrl==1?"software":"hardware")),(basculas.at(0).stopBits==0?"1":(basculas.at(0).stopBits==1?"1,5":"2")));
	    console.push_back(error);
	    testBascula = new bascula(basculas.at(0).port,basculas.at(0).bauds);
	    if(!basculas.at(0).ask.empty())
	      {
		testBascula->set_parity(basculas.at(0).parity);
		testBascula->set_flowControl(basculas.at(0).ctrl);
		testBascula->set_stopBits(basculas.at(0).stopBits);
		//no capturamos excepciones
		testBascula->setCommand(basculas.at(0).ask);	     
		std::cout << "(INFO) leyendo peso!" << std::endl;
		char* texto;
		try
		  {
		    int ret = testBascula->readPeso(basculas.at(0).timeout,texto);
		    std::string sPeso =  fromBufferAPeso(texto);
		    try
		      {
		        formEntrada->setArrScaleIn(std::stoi(sPeso));
		      }
		    catch (...)
		      {
			formEntrada->setArrScaleIn(0);
			sPeso = "0";
		      }
		    pvSetText(p,EDITPESOENT,sPeso.c_str());
		    if(ret)
		      {
			console.push_back("(AVISO) posible TIMEOUT o lectura errónea del puerto");
		      }
		  }
		catch(...)
		  {
		    console.push_back("*ERROR* error de entrada/salida, puerto correcto y conectado?");
		  }
	      }
	    if(testBascula != NULL)
	      delete testBascula;
	  }
	  break;
	case 230:
	case 130: //all products chosen
	case 30:
	  {
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);	    
	    //
	    std::string type;
	    myStation->getType(type);
	    //TODO database inside formulario
	    //formEntrada->updtAllProducts(localDatabase,type.c_str());
	    //	    
	    char * sql =NULL;
	    selAllProdsCodesPermsFromProductos(sql,type.c_str());
	    localDatabase.query(p,sql);
	    d->allProductos.clear();
	    d->allProductos2.clear();
	    d->allProductos3.clear();
	    d->allProductosCodes.clear();
	    d->allProductosLers.clear();
	    d->allPermisosNecesariosProducto.clear();
	    std::vector <std::vector <std::string>> dataReturn;
	    dataReturn = localDatabase.retData2();
	    std::vector<std::vector<std::string>>::iterator iRows;
	    std::vector<std::string>::iterator iCols;
	    int col = 0;
	    for(iRows = dataReturn.begin(); iRows != dataReturn.end(); ++iRows)
	      {
		col = 0;
		for(iCols = iRows->begin(); iCols != iRows->end(); ++iCols)
		  {
		    //std::cout << "col:" << col << " valor:" << *iCols << std::endl;
		    if(col == 0) //codigo
		      d->allProductosCodes.push_back(*iCols);
		    else if(col==1) //codigo ler
		      d->allProductosLers.push_back(*iCols);
		    else if(col == 2) //nombre 1
		      d->allProductos.push_back(*iCols);
		    else if(col == 3) //nombre 2
		      d->allProductos2.push_back(*iCols);
		    else if(col == 4) //nombre 3
		      d->allProductos3.push_back(*iCols);
		    col++;
		  }
	      }
	    formEntrada->allProductos.clear();
	    formEntrada->allProductos = d->allProductos;
	    formEntrada->allProductos2.clear();
	    formEntrada->allProductos2 = d->allProductos2;
	    formEntrada->allProductos3.clear();
	    formEntrada->allProductos3 = d->allProductos3;
	    formEntrada->allProductosCodes.clear();
	    formEntrada->allProductosCodes = d->allProductosCodes;
	    formEntrada->allProductosLers.clear();
	    formEntrada->allProductosLers = d->allProductosLers;	    

	    std::vector <std::string> allProdsCodes4Combo;
	    for (int i=0; i < d->allProductos.size(); i++)
	      allProdsCodes4Combo.push_back(d->allProductosLers[i]  + " " + d->allProductos[i] + " " + d->allProductos2[i] + " " + d->allProductos3[i]+ " " + d->allProductosCodes[i]);
	    populateCombo(p,COMBOLERS,allProdsCodes4Combo);
	    d->comboProducto2.clear();
	  }	   
	  break;
	case 231:
	case 131:
	case 31: //Product selected and its permits shown
	  {
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    //
	    std::string type;
	    myStation->getType(type);
	    formEntrada->setArrCosProdPermits(localDatabase, type.c_str());	   
	  }	   
	  break;
	case 232:
	case 132: //product authorized
	case 32:
	  {
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    //	    
	    std::string myDI = formEntrada->createArrDi(localDatabase);
	    //if(!formEntrada->isIncArrPlateEdited())//chequeo de imagen
	      formEntrada->savePlateImage(1,"entrada");
	    pvSetText(p,EDITDIPROV,myDI.c_str());
	  }
	  break;
	case 99: //Vehículo a tránsito y borramos formulario
	  {
	    int DatabaseData_chkd;
	    int remote_connected = 0;
	    try
	      {
		DatabaseData_chkd = std::stoi(remoteDatabaseData.db_port);
	      }
	    catch(...)
	      {
		DatabaseData_chkd = 0;
	      }	    
	    if(isConnected(remoteDatabaseData.db_host.c_str(), DatabaseData_chkd))
	      remote_connected = 1;
	    
	    if(formEntrada->storeTransit(localDatabase,remoteDatabase,myStation,remote_connected))
	      {
		 console.push_back("AVISO: no se consiguió escribir el movimiento a tránsito en la base de datos remota, sincronice cuando pueda");
		 
		 console.push_back("AVISO: tenga en cuenta que si es un movimiento de transferencia, este seguirá en el sistema, pida a administración que lo borren");
	      }
	    cameraSemaphore(1,1,globalConfiguration.traffic_lights_enabled);
	  }
	  break;
	case 101: //matrícula no registrada
	  refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	  break;
	case 110: //matrícula no registrada AUTORIZADA elegir cliente
	  {
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    //seleccionamos todos los clientes
	    char * sql;
	    selAllDatFrmCostumers(sql);
	    localDatabase.query(p,sql);
	    delete sql;
	    d->allClientes.clear();
	    d->allClientesCodes.clear();
	    std::vector <std::vector <std::string>> dataReturn;
	    dataReturn = localDatabase.retData2();
	    int row,col=0;
	    for(row=0;row<dataReturn.size();row++)
	      {
		for(col=0;col<dataReturn[row].size();col++)
		  {
		    if(col==1)
		      d->allClientes.push_back(dataReturn[row][col]);
		    if(col==0)
		      d->allClientesCodes.push_back(dataReturn[row][col]);
		  }
	      }
	    populateCombo(p,COMBOCLIENTES,d->allClientes);
	    break;
	  }
	case 210: //Particular client
	  {//TODO revisar estado, sql va fuera
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    //cleaning possible garbage
	    d->editClient.clear();
	    //Client "OTROS" selection
	    char * sql = "select CODIGO_CLIENTE from CLIENTES where NOMBRE = \'OTROS\'";
	    localDatabase.query(p,sql);
	    std::vector <std::vector <std::string>> dataReturn;
	    dataReturn = localDatabase.retData2();

	    //TODO TO IMPROVE // ERROR CATCHING
	    if(dataReturn.size())
	      {
		try
		  {
		    formEntrada->setArrCosCode(std::stoi(dataReturn[0][0]));
		  }
		catch (...)
		  {
		    formEntrada->setArrCosCode(0);
		  }
	      }
	    //////
	    pvClear(p,COMBOCLIENTES);
	    pvSetText(p,COMBOCLIENTES,"OTROS"); //lo miramos en base de datos?
	    break;
	  }
	case 321: //transfer movement
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    //COSTUMER
	    formEntrada->setArrCosCode(DEF_BIORECICLAJE_CODE);	    
	    formEntrada->setAllArrCostumerData(localDatabase);
	    pvSetText(p,EDITCLIENTES,formEntrada->retArrCosName().c_str());	    
	    //PRODUCT
	    formEntrada->setAllArrProductData(localDatabase);	    
	    std::string productText = "(";
	    productText += formEntrada->retArrProdLER();
	    productText +=  ") ";
	    productText += formEntrada->retArrProdName1();
	    productText += " ";
	    productText += formEntrada->retArrProdName2();
	    productText += " ";
	    productText += formEntrada->retArrProdName3(); 
	    pvSetText(p,EDITPRODUCTOS,productText.c_str());		
	    //DI and folder
	    std::string myDI = formEntrada->createArrDi(localDatabase);
	    //if(!formEntrada->isIncArrPlateEdited())//chequeo de imagen
	      formEntrada->savePlateImage(1,"entrada");
	    pvSetText(p,EDITDIPROV,myDI.c_str());
	  }	   
	  break;
	  
	case 1000: //salida de descargar
	  {
	    if(syncro_needed(&my_syncro_data))
	      {
		globalSyncronization(p,d,formEntrada);
		actualizaForm(p,d, formEntrada->getState());
		syncro_done(&my_syncro_data);
	      }
	    //commons
	    popteTransito(p,d,TABLATRANSITO, formEntrada);
	    d->transito_plate.clear();
	    d->post_transito_plate.clear();
	  }
	  break;
	case 1010: //animation, camera 2
	  break;
	case 1011: //taking plate camera2
	  {  
	    std::string plate;	    
	    ret = useCamera(p, d, 2, plate, IMCAM_E2);
	    if(!ret)
	      {
		pvSetText(p,EDITCAM_E2,pvtr(plate.c_str()));
		formEntrada->setDepPlate(plate);
		d->processTag=1;
	      }
	    else
	      {
		d->processTag=-1;
		sprintf(error,"**ERROR** imposible recibir matrícula de la cámara 2");
		console.push_back(error);
	      }
	    break;
	  }
	case 1020: //hemos seleccionado un transporte de la tabla de tránsito
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	    //load DI
	    formEntrada->createDepDi(localDatabase);	    
	    pvSetText(p,EDITDIDEF,formEntrada->retDepDi().c_str());
	    //if(!formEntrada->isIncDepPlateEdited())//chequeo de imagen
	    formEntrada->savePlateImage(2,"salida");
	    std::string pesoSalida = std::to_string(formEntrada->retDepScaleOut());
	    pvSetText(p,EDITPESOTARA,pesoSalida.c_str());
	    //default driver
	    if(formEntrada->default_driver(localDatabase))
	      {
		driver *tmp_driver;
		formEntrada->ret_dep_driver(tmp_driver);
		pvSetText(p,EDITCODETRANSP,std::to_string(tmp_driver->get_code()).c_str());
		pvSetText(p,EDITNAMETRANSP,tmp_driver->get_name().c_str());
		delete tmp_driver;
	      }
	    else
	      {
		pvSetText(p,EDITCODETRANSP,"N/A");
		pvSetText(p,EDITNAMETRANSP,"N/A");
	      }
	  }
	  break;
	case 1021: //almacenamos la tara en DB
	  {
	    //saving weight!
	    d->test = 0;
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	    int DatabaseData_chkd;
	    try
	      {
		DatabaseData_chkd= std::stoi(remoteDatabaseData.db_port);
	      }
	    catch(...)
	      {
		DatabaseData_chkd = 0;
	      }
	    formEntrada->saveScaleOut(localDatabase,remoteDatabase,remoteDatabaseData.db_host.c_str(), DatabaseData_chkd);
	  }
	  break;
	case(1022):
	  refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	  break;
	case 1024://retrieving all DI data
	  {
	    costumer * ourId = new costumer(DEF_BIORECICLAJE_CODE,localDatabase);
	    formEntrada->setOurId(ourId);
	    delete ourId;
	    formEntrada->setAllDiData(localDatabase, myStation, DEF_BIORECICLAJE_CODE, DEF_TRANS_CODE);
	  }
	  break;
	case 1025: //transición pesaje2
	  break;
      	case 1026: //pesaje2
	  {
	    char error[256];
	    bascula * testBascula = NULL;
	    //reseteamos peso
	    std::string sPesoTest = "0";
	    pvSetText(p,EDITPESOTARA,sPesoTest.c_str());
	    formEntrada->setDepScaleOut(0);
	    formEntrada->incDepScaleEdited(0);
	    //
	    sprintf(error,"(INFO) usando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, paridad:%s , control de flujo:%s y %s bits de parada...",2, basculas.at(1).port.c_str(),basculas.at(1).bauds,basculas.at(1).timeout , basculas.at(1).ask.c_str(), (basculas.at(1).parity==0?"ninguna":(basculas.at(1).parity==1?"impar":"par")),(basculas.at(1).ctrl==0?"ninguno":(basculas.at(1).ctrl==1?"software":"hardware")),(basculas.at(1).stopBits==0?"1":(basculas.at(1).stopBits==1?"1,5":"2")));
	    console.push_back(error);
	    testBascula = new bascula(basculas.at(1).port,basculas.at(1).bauds);
	    if(!basculas.at(1).ask.empty())
	      {
		testBascula->set_parity(basculas.at(1).parity);
		testBascula->set_flowControl(basculas.at(1).ctrl);
		testBascula->set_stopBits(basculas.at(1).stopBits);
		//no capturamos excepciones
		testBascula->setCommand(basculas.at(1).ask);	     
		std::cout << "(INFO) leyendo peso!" << std::endl;
		char* texto;
		try
		  {
		    int ret = testBascula->readPeso(basculas.at(1).timeout,texto);
		    std::string sPeso =  fromBufferAPeso(texto);
		    try
		      {
		        formEntrada->setDepScaleOut(std::stoi(sPeso));
		      }
		    catch (...)
		      {
			formEntrada->setDepScaleOut(0);
			sPeso = "0";
		      }
		    pvSetText(p,EDITPESOTARA,sPeso.c_str());
		    if(ret)
		      {
			console.push_back("(AVISO) posible TIMEOUT o lectura errónea del puerto");
		      }
		  }
		catch(...)
		  {
		    console.push_back("*ERROR* error de entrada/salida, puerto correcto y conectado?");
		  }

	      }
	    if(testBascula != NULL)
	      delete testBascula;
	  }
	  break;
	case 1030:
	  pvSetText(p,EDITCODETRANSP,std::to_string(formEntrada->retDepDriCode()).c_str());
	  pvSetText(p,EDITNAMETRANSP,formEntrada->retDepDriName().c_str());
	  refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);	  
	  break;
	case 1031:
	  pvSetText(p,EDITCODETRANSP,std::to_string(formEntrada->retDepDriCode()).c_str());
	  pvSetText(p,EDITNAMETRANSP,formEntrada->retDepDriName().c_str());
	  refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	  break;
	case 1036: //firma del movimiento
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	    
	    std::string cname;
	    std::string productText;
	    char * sql;
	    //COSTUMER
	    std::string clientCode = std::to_string(formEntrada->retDepCosCode());
	    selectClientNameByCode(sql,clientCode.c_str());
	    localDatabase.query(p,sql);
	    std::vector<std::vector<std::string>> ourData = localDatabase.retData2();
	    if(ourData.size() >= 1)
	      {
	        cname = ourData.at(0).at(0);		
	      }	   
	    delete sql;
	    //
	    //PRODUCT
	    std::string productCode = std::to_string(formEntrada->retDepProdCode());
	    selectProductBasisByCode(sql,productCode.c_str());
	    localDatabase.query(p,sql);
	    ourData.clear();
	    ourData = localDatabase.retData2();
	    if(ourData.size() >= 1)
	      {
		std::string ler = ourData.at(0).at(0);
		std::string pname = ourData.at(0).at(1);
		std::string pname2 = ourData.at(0).at(2);
		std::string pname3 = ourData.at(0).at(3);

	        productText = "(" + ler + ") " + pname + " " + pname2 + " " + pname3; 		
	      }
	    delete sql;
	    //
	    int error = 0;	    
	    d->miTableta = new tableta(error);
	    if(!error)
	      {
		//d->miTableta->init();
		//std::cout << "estableciendo la imagen" << std::endl;
		char speso[100];
		int pesoTotal =  formEntrada->retDepScaleIn() - formEntrada->retDepScaleOut();
		sprintf(speso,"%d",pesoTotal);
		std::string sspeso = speso;
		float precio = pesoTotal *  formEntrada->retDepPrice()/1000.0;
		std::string sPrecio = std::to_string (precio);
		//std::cout << cname << "," << productText << std::endl;
		d->miTableta->setInfoShow(formEntrada->retDepPlate(),cname,productText,sPrecio, sspeso);
		//std::cout << "fin de establecer la imagen" << std::endl;
		int tries = 3;
		int i=0;
		int done=0;
		while(i<tries && !done && !error)
		  {
		    d->miTableta->init();
		    if(!d->miTableta->loadInfo())
		      done = 1;
		    else
		      {
			espera(1);
			d->miTableta->reset();
			delete d->miTableta;
			d->miTableta = new tableta(error);
		      }
		    i++;
		  }
		if(done)
		  {
		    d->miTableta->startCapture();
		    pvMessageBox(p,BUTFIRMAR,BoxInformation,"Pulsa OK, y toque con el lápiz la tableta cuando haya terminado de firmar",MessageBoxOk,0,0);
		  }
		else
		  {
		    console.push_back("*ERROR* error en la tableta, desenchufe y vuelva a enchufarla e intente firmar de nuevo");
		    if(!error)
		      d->miTableta->reset();
		    delete d->miTableta;
		    d->miTableta = NULL;
		  }
	      }
	    else
	      {
		console.push_back("ERROR* ¡Tableta de firmas no detectada!");
		delete d->miTableta;
		d->miTableta = NULL;
	      }
	  }
	  
	  break;       
	case 1097:
	  formEntrada->unsetStaff();
	  pvInputDialog(p,BUTPROCEDER_E1,"Inserte el código de basculista para proceder:","");
	  break;
	case 1099: //almacenaje del movimiento, impresión del pdf
	  {
	    //copia archivo firma
	    formEntrada->saveSignature();
	    //to DATABASE
	    int DatabaseData_chkd;
	    int remote_connected = 0;
	    try
	    {
			DatabaseData_chkd = std::stoi(remoteDatabaseData.db_port);
	    }
	    catch(...)
	    {
			DatabaseData_chkd = 0;
	    }	    
	    if(isConnected(remoteDatabaseData.db_host.c_str(), DatabaseData_chkd))
	    {
			try
		  	{
		    	DatabaseData_chkd = std::stoi(remoteDatabaseData.local_db_port);
		  	}
			catch(...)
		  	{
		    	DatabaseData_chkd = 0;
		  	}
			if(isConnected(remoteDatabaseData.local_db_host.c_str(), DatabaseData_chkd))
		  		remote_connected = 1;
	    }

	    int error = formEntrada->storeDepMov(localDatabase,remoteDatabase,remote_connected);
	    if(!error)
	    {
			std::string myPrinter;
			miIni->retPrinterId(myPrinter);
			if(myPrinter.empty())
		  	{
		    	console.push_back("AVISO: no se va a imprimir el documento, al no tener configurada la impresora");
		  	}
			formEntrada->createPdf(myPrinter);
			mailClient->sendIncidentsMail(myStation,formEntrada);
			formEntrada->backupFiles(formEntrada->retDepMovCode().c_str());
	    }
	    else if(error ==-1)
	    {
			console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
			console.push_back("*ERROR* ¡Necesita sincronizar para actualizar el movimiento en el servidor central!");
			std::string myPrinter;
			miIni->retPrinterId(myPrinter);
			if(myPrinter.empty())
		  	{
		    	console.push_back("AVISO: no se va a imprimir el documento, al no tener configurada la impresora");
		  	}
			formEntrada->createPdf(myPrinter);
			mailClient->sendIncidentsMail(myStation,formEntrada);
			formEntrada->backupFiles(formEntrada->retDepMovCode().c_str());
	    }
	    else if(error == -10)
	    {
			console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
			console.push_back("*ERROR* ¡Necesita sincronizar! Vuelva a intentarlo");
			d->error = 1;
	    }
	    else
	      console.push_back("*ERROR* ¡Fallo al guardar el movimiento!");
	    
	    break;
	  }
	default:
	  break;
	}
      formEntrada->setState(d->enFutEstado);
      actualizaForm(p,d,formEntrada->getState());
      ret = 0;
    }
  return ret;
}


//condiciones de cambio
static int maquinaEstados(PARAM *p, DATA *d)
{
  int ret = -1;
  switch(formEntrada->getState()) 
    {
    case -100:
      {
	//comunes
	popteTransito(p,d,TABLATRANSITO, formEntrada);	
	//checkbox de entrada
	if(d->enFutEstado >=1000) //finalizando entrada ET
	  {
	    d->entrarDescargar=0;
	    pvSetChecked(p,CHKSALIDA,1);
	    pvSetChecked(p,CHKENTRADA,0);
	    d->camionElegido = -1;
	    if(d->enFutEstado >= 1020)
	      {
		//Saving destination where files are stored
		pvSetText(p,EDITDIDEF, formEntrada->retDepDi().c_str());
		std::string peso = std::to_string(formEntrada->retDepScaleOut());
		pvSetText(p,EDITPESOTARA,peso.c_str());
		pvSetText(p,EDITCAM_E2,formEntrada->retDepPlate().c_str());
	      }
	  }
	else//comenzando una entrada ET
	  {
	    d->entrarDescargar=1;
	    pvSetChecked(p,CHKSALIDA,0);
	    pvSetChecked(p,CHKENTRADA,1);
	    //plate
	    std::string myPlate = formEntrada->retArrPlate();
	    if(!myPlate.empty())
	      {
		//matrículas
		pvSetText(p,EDITCAM,myPlate.c_str());
		if(!formEntrada->isArrPlateRegistered(localDatabase))
		  pvSetImage(p,ICONAUTMATRI,"image/red.png");
		else
		  pvSetImage(p,ICONAUTMATRI,"image/green.png");
	      }
	    //forced status
	    if(formEntrada->isIncArrPlateAuto())
	      pvSetChecked(p,CHCKAUTMATRI,1);
	    //particular costumer
	    if(formEntrada->isIncArrParticular())
	      pvSetChecked(p,CHCKNOREGISTRADO,1);
	    //comboclientes	    
	    if(formEntrada->retArrCosCode()>0)
	      {
	        formEntrada->setAllArrCostumerData(localDatabase);
		std::string costumer = formEntrada->retArrCosName();
		if(!costumer.empty())
		  pvSetText(p,COMBOCLIENTES,costumer.c_str());
	      }
	    //combos productos	    
	    if(formEntrada->retArrProdCode()>0)
	      {
		std::cout << formEntrada->retArrProdCode() << std::endl;
		formEntrada->setAllArrProductData(localDatabase);
		if(formEntrada->isArrProdPermit())
		    pvSetText(p,COMBOPRODUCTOS,formEntrada->retArrProdFullName().c_str());
		else
		  {
		    pvSetText(p,COMBOPRODUCTOS,"MOSTRAR TODOS");
		    pvSetText(p,COMBOLERS,formEntrada->retArrProdFullName().c_str());
		    refreshLerPerms(p,1,formEntrada);
		  }
		//product forced
		if(formEntrada-> isIncArrProdFz())
		  pvSetChecked(p,CHKFORZARPROD,1);		
	      }
	    
	    //scale in
	    std::string sPeso = std::to_string(formEntrada->retArrScaleIn());
	    pvSetText(p,EDITPESOENT,sPeso.c_str());
	    //DI
	    pvSetText(p,EDITDIPROV,formEntrada->retArrDi().c_str());
	    if(formEntrada->retArrMovType() == DEF_MOV_TRANSFER)
	      {
		pvClear(p,COMBOCLIENTES);
		pvClear(p,COMBOPRODUCTOS);
		pvSetText(p,EDITCLIENTES,formEntrada->retArrCosName().c_str());
		pvSetText(p,EDITPRODUCTOS,formEntrada->retArrProdFullName().c_str());					   
	      }	    
	  }
	pvHide(p,LOADINGFORM);
	break;
      }
    case -2:
      //LLegamos nuevos!
      d->entrarDescargar=1;
      pvSetChecked(p,CHKSALIDA,0);
      pvSetChecked(p,CHKENTRADA,1);
      d->enFutEstado = -1;
      d->proceder=0;
      ret = 0;
      break;
    case -1: //inicialización
      //LLegamos nuevos!
      d->enFutEstado = 0;
      d->proceder=0;
      ret = 0;
      break;
    case 0:
      {
	//auto-syncronization
	if(syncro_needed(&my_syncro_data))
	  {
	    globalSyncronization(p,d,formEntrada);
	    actualizaForm(p,d, formEntrada->getState());
	    //commons
	    popteTransito(p,d,TABLATRANSITO,formEntrada);
	    syncro_done(&my_syncro_data);
	  }
	/////////////////////
	formEntrada->setUnloadMov();	
	if(!d->entrarDescargar) //selector a salirDescargar
	    d->enFutEstado = 1000;
	else if(d->plateTaking) //si pulsamos en tomar maricula pasamos a capturarla	
	{
	  formEntrada->incArrPlateEdited(0);
	  d->plateTaking=0;
	  d->processTag=0;
	  d->enFutEstado = 5;
	}
	else if(formEntrada->isTrf(localDatabase, myStation))
	  {
	    formEntrada->incArrPlateEdited(0);
	    formEntrada->setTrfMov(localDatabase, myStation);
	    log_message("(DESCARGA) Llegada de una transferencia", 1);
	    log_message("(DESCARGA) Matrícula: "+ formEntrada->retArrPlate(),  1);
	    d->enFutEstado=321;
	  }	
	else if(formEntrada->isArrPlateRegistered(localDatabase))//if registered
	  {
	    log_message("(DESCARGA) Llegada de una vehículo registrado", 1);
	    log_message("(DESCARGA) Matrícula: "+ formEntrada->retArrPlate(),  1);
	    d->enFutEstado=10;
	  }
	else if(!formEntrada->retArrPlate().empty()) //if not empty, not registered
	  d->enFutEstado=101;	  
	ret = 0;
      }
      break;		
    case 5: //carga matricula cámara 1
      d->enFutEstado = 6;
      ret = 0;
      break;   
    case 6:     
      if(d->processTag != 0) //fin del proceso de toma de matrículas
	{
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado = 0;
	}
      ret = 0;
      break;      
    case 10://elección cliente
      if(d->plateTaking) //si pulsamos en tomar maricula pasamos a capturarla
	{
	  formEntrada->incArrPlateEdited(0);
	  d->plateTaking=0;
	  d->processTag=0;
	  pvClear(p,COMBOCLIENTES);
	  d->allClientes.clear();
	  d->enFutEstado = 5;
	}
      else if(!formEntrada->isArrPlateRegistered(localDatabase) || formEntrada->retArrPlate().empty()) //si modificamos la maricula a mano vovlermos a revisar su registro
	{
	  d->enFutEstado=0;
	  pvClear(p,COMBOCLIENTES);
	  d->allClientes.clear();
	}
      else if(formEntrada->retArrCosCode()>=0) //si tenemos elegido un cliente pasamos al estado 
	{
	  pvClear(p,COMBOCLIENTES);
	  pvSetText(p,COMBOCLIENTES,formEntrada->retArrCosName().c_str());
	  d->enFutEstado=20;
	}
      else if(d->cancelar)
	{
      	   d->cancelar=0;	   
	   resetForm(p,d,formEntrada);
	   d->enFutEstado = 0;
	   console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;	
      
    case 20: //product selection related to client
      if(formEntrada->retArrProdCode()>0)
	d->enFutEstado = 21;
      else if(!d->comboProducto.compare("MOSTRAR TODOS!")) //if we prefer a new list between ALL products
	{
	  formEntrada->resetArrProduct();
	  d->comboProducto.clear();
	  d->enFutEstado = 30;
	}      
      else if(d->retroceder) //back to state 10
	{
	  d->retroceder = 0;
	  formEntrada->resetArrCostumer();
	  d->enFutEstado = 10;
	  pvClear(p,COMBOPRODUCTOS);
	  formEntrada->allClienteProds.clear();
	}
      else if(d->cancelar) //cancel form
	{
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	}
      break;
      case 21: //waiting for taking weight, chosen product by normal path
      if(formEntrada->isArrPesoOk()) //si damos por válido según criterios el peso de entrada
	{
	  d->enFutEstado = 22;
	}
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 25;
	}      
      if(d->retroceder) //volvemos al estado 20
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 20;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOPRODUCTOS,0);
	  //reseteamos peso!
	  formEntrada->resetArrScale();
	  pvSetText(p,EDITPESOENT,"0");
	  //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;     
     case 22: //peso ok
       if(d->pesaje1) //pesamos!
	 {
	   d->pesaje1 = 0;
	   d->enFutEstado = 25;
	 }    
       if(d->retroceder) //volvemos al estado 10
	 {
	   d->retroceder = 0;
	   formEntrada->resetArrProduct();
	   d->enFutEstado = 20;
	   d->productoCodeActual.clear();
	   pvSetCurrentItem(p,COMBOPRODUCTOS,0);
	   //reseteamos peso!
	   formEntrada->resetArrScale();
	   pvSetText(p,EDITPESOENT,"0");
	   //di
	   formEntrada->resetArrDi();
	   formEntrada->rmArrDiFolder();
	 }
       if(d->cancelar) //cancelamos el formulario de entrada
	 {
	   resetForm(p,d,formEntrada);
	   formEntrada->rmArrDiFolder();
	   d->enFutEstado = 0;
	   console.push_back("INFO: Formulario cancelado!");
	 }
       if( d->proceder) //a tránsito
	 {
	   d->enFutEstado = 98;
	   d->proceder = 0;
	 }
      break;
    case 25: //transición pesaje báscula 1
      d->enFutEstado = 26;
      break;         
    case 26: //pesaje báscula puesto 1
      d->enFutEstado = 21;
      break;
    case 30: //elegimos entre todos los productos
      if(formEntrada->retArrProdCode()>0)
	d->enFutEstado = 31;
      if(d->retroceder) //volvemos al estado 20
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 20;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOPRODUCTOS,0);
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      break;
    case 31: //hemos elegido un producto y mostramos sus permisos
      //si está autorizado a estado 32
      if(formEntrada->isArrProdPermit())
	d->enFutEstado=32;
      else //si no lo está a estado 33
	d->enFutEstado=33;
      break;
    case 32: //producto permitido
      if(formEntrada->isArrPesoOk()) //si damos por válido según criterios el peso de entrada
	{
	  d->enFutEstado = 40;
	}
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 35;
	}      
      if(d->retroceder) //volvemos al estado 30
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 30;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOLERS,0);
	  formEntrada->unforceCurrentProduct();
	  pvSetChecked(p,CHKFORZARPROD,0);
	  //reseteamos peso!
	  formEntrada->resetArrScale();
	  pvSetText(p,EDITPESOENT,"0");
	  //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;
    case 33: //producto no permitido, hay que autorizarlo!
      if(formEntrada->isIncArrProdFz())
	  d->enFutEstado = 32;
      if(d->retroceder) //volvemos al estado 30
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 30;
	  pvSetCurrentItem(p,COMBOLERS,0);
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      break;
    case 35:
      d->enFutEstado=36;
      break;
    case 36:
      d->enFutEstado=32;
      break;
    case 40: //peso ok
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 35;
	}    
      if(d->retroceder) //volvemos al estado 30
	{
	  d->retroceder = 0;
	  d->enFutEstado = 32;
	  //reseteamos peso!
	  formEntrada->resetArrScale();
	  pvSetText(p,EDITPESOENT,"0");
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      if( d->proceder) //a tránsito
	{
	//   \/   \/  Edit Rodri
	 /*  std::string text;
	   text = p->clipboard;
	   formEntrada->setInputComment(text);*/
	//   /\   /\  Edit Rodri  
	  d->enFutEstado = 98;
	  d->proceder = 0;
	}
      break;
    case 98: //estado de animación
      d->enFutEstado = 99;
      break;
    case 99: //descarga realizada correctamente, vamos a transición
      resetForm(p,d,formEntrada);
	  cameraSemaphore(1,1,globalConfiguration.traffic_lights_enabled);
      d->enFutEstado = 0;
      console.push_back("INFO: vehículo a tránsito interno");
      break;       
    case 101:
      {
	if(!d->entrarDescargar) //selector a salirDescargar
	  {
	    resetForm(p,d,formEntrada);
	    d->enFutEstado = 1000;	    
	  }
	else if(d->plateTaking) //si pulsamos en tomar maricula pasamos a capturarla
	  {
	    pvSetText(p,EDITCAM,"");
	    formEntrada->resetArrPlate();
	    formEntrada->incArrPlateEdited(0);
	    d->plateTaking = 0;
	    d->processTag = 0;
	    d->enFutEstado=5;	    
	  }		  
	else if(formEntrada->isIncArrPlateAuto())
	  {
	    d->enFutEstado=110;
	    log_message("(DESCARGA) Matrícula autorizada", 1);
	    log_message("(DESCARGA) Matrícula: "+ formEntrada->retArrPlate(),  1);
	  }
	else if(formEntrada->isIncArrParticular())
	  {
	    d->enFutEstado=210;
	    log_message("(DESCARGA) Cliente particular no registrado", 1);
	    log_message("(DESCARGA) Matrícula: "+ formEntrada->retArrPlate(),  1);
	  }
	else if(d->cancelar)
	  {
	    d->cancelar=0;
	    resetForm(p,d,formEntrada);
	    d->enFutEstado = 0;
	    console.push_back("INFO: Formulario cancelado!");
	  }
	ret = 0;
      }
      break;
      
      //autorizamos una matrícula no registrada
    case 110:      
      if(d->retroceder) //retroceder a estado 101
	{
	  d->retroceder=0;
	  d->enFutEstado=101;
	  d->allClientes.clear();
	  pvClear(p,COMBOCLIENTES);
	  formEntrada->incArrPlateAuto(0);
	  pvSetChecked(p,CHCKAUTMATRI,0);
	}
      if(d->cancelar) //Cancelamos
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      if(formEntrada->retArrCosCode()>0) //si tenemos elegido un cliente pasamos al estado 
	{
	  pvClear(p,COMBOCLIENTES);
	  pvSetText(p,COMBOCLIENTES,formEntrada->retArrCosName().c_str());
	  d->enFutEstado=120;
	}
      ret = 0;
      break;
    case 120: //product choosing from client    (plate manually authorized)
      if(formEntrada->retArrProdCode()>0)
	d->enFutEstado = 21;
      std::cout << "PRODUCTO:" << d->comboProducto << std::endl;
      if(!d->comboProducto.compare("MOSTRAR TODOS!")) //if we prefer a new list between ALL products
	{
	  formEntrada->resetArrProduct();
	  d->comboProducto.clear();
	  d->enFutEstado = 130;
	}
      
      if(d->retroceder) //back to state 10
	{
	  d->retroceder = 0;
	  formEntrada->resetArrCostumer();
	  d->enFutEstado = 110;
	  pvClear(p,COMBOPRODUCTOS);
	  formEntrada->allClienteProds.clear();
	}
      if(d->cancelar) //cancel form
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;
    case(121): //waiting for taking weight, chosen product by authorized client
      if(formEntrada->isArrPesoOk()) //si damos por válido según criterios el peso de entrada
	{
	  d->enFutEstado = 122;
	}
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 125;
	}      
      if(d->retroceder) //volvemos al estado 20
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 120;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOPRODUCTOS,0);
	  //reseteamos peso!
	  formEntrada->resetArrScale();
	  pvSetText(p,EDITPESOENT,"0");
	  //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;
    case 122: //weigth ok, waiting to proceed
      if(d->pesaje1) //pesamos!
	 {
	   d->pesaje1 = 0;
	   d->enFutEstado = 125;
	 }    
       if(d->retroceder) //volvemos al estado 120
	 {
	   d->retroceder = 0;
	   formEntrada->resetArrProduct();
	   d->enFutEstado = 120;
	   d->productoCodeActual.clear();
	   pvSetCurrentItem(p,COMBOPRODUCTOS,0);
	   //reseteamos peso!
	   formEntrada->resetArrScale();
	   pvSetText(p,EDITPESOENT,"0");
	   //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	 }
       if(d->cancelar) //cancelamos el formulario de entrada
	 {
	   d->cancelar=0;	   
	   resetForm(p,d,formEntrada);
	   formEntrada->rmArrDiFolder();
	   d->enFutEstado = 0;
	   console.push_back("INFO: Formulario cancelado!");
	 }
       if( d->proceder) //a tránsito
	 {
	//   \/   \/  Edit Rodri
	  /* std::string text;
	   text = p->clipboard;
	   formEntrada->setInputComment(text);*/
	//   /\   /\  Edit Rodri  
	   d->enFutEstado = 98;
	   d->proceder = 0;
	 }
      break;
    case(125): //animation state scale 1
      d->enFutEstado = 126;
      break;         
    case(126): //taking weigth scale 1 (blocking state)
      d->enFutEstado = 121;
      break;
    case 130: //CHOOSING IN ALL PRODUCTS AVAILABLE IN STATION
      if(formEntrada->retArrProdCode()>0)	      
	d->enFutEstado = 131;
      if(d->retroceder) //volvemos al estado 20
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 120;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOPRODUCTOS,0);
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      break;
    case 131: //PRODUCT CHOSEN, PERMITS SHOWN
      //if authorized to state 132
      if(formEntrada->isArrProdPermit())
	d->enFutEstado=132;
      else //if not authorized to state 133
	d->enFutEstado=133;
      break;
    case 132: //product allowed by type-client-station (or being forced)
      if(formEntrada->isArrPesoOk()) //si damos por válido según criterios el peso de entrada
	{
	  d->enFutEstado = 140;
	}
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 135;
	}      
      if(d->retroceder) //volvemos al estado 30
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 130;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOLERS,0);
	  formEntrada->unforceCurrentProduct();
	  pvSetChecked(p,CHKFORZARPROD,0);
	  //reseteamos peso!
	  formEntrada->resetArrScale();
	  pvSetText(p,EDITPESOENT,"0");
	  //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	}      
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;
    case 133: //product not allowed, authorize?
      if(formEntrada->isIncArrProdFz())
	  d->enFutEstado = 132;
      if(d->retroceder) //volvemos al estado 30
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 130;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOLERS,0);
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      break;
      
    case 135:
      d->enFutEstado=136;
      break;
    case 136:
      d->enFutEstado=132;
      break;
    case 140: //peso ok
       if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 135;
	}    
      if(d->retroceder) //volvemos al estado 132
	{
	  d->retroceder = 0;
	  d->enFutEstado = 132;
	  //reset scale!
	  formEntrada->resetArrScale();
	  pvSetText(p,EDITPESOENT,"0");
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      if( d->proceder) //a tránsito
	{
	//   \/   \/  Edit Rodri
	 /*  std::string text;
	   text = p->clipboard;
	   formEntrada->setInputComment(text);*/
	//   /\   /\  Edit Rodri  
	  d->enFutEstado = 98;
	  d->proceder = 0;
	}
      break;
      //particular client
    case 210:      
      d->enFutEstado = 230;
      ret = 0;
      break;
      //particular client product choosing
    case 230:
      if(formEntrada->retArrProdCode()>0)	      
	d->enFutEstado = 231;
      if(d->retroceder) //back to state 210
	{
	  formEntrada->resetArrCostumer();
	  pvClear(p,COMBOCLIENTES);
	  d->retroceder=0;
	  d->enFutEstado=101;     
	  formEntrada->incArrParticular(0);
	  pvSetChecked(p,CHCKNOREGISTRADO,0);
	}
      if(d->cancelar) //Cancel
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;
    case 231: //PRODUCT CHOSEN, PERMITS SHOWN
      //if authorized to state 232
      if(formEntrada->isArrProdPermit())
	d->enFutEstado=232;
      else //if not authorized to state 233
	d->enFutEstado=233;
      break;
    case 232: //product allowed by type-client-station (or being forced)
      if(formEntrada->isArrPesoOk()) //if weigth ok
	{
	  d->enFutEstado = 240;
	}
      if(d->pesaje1) //to scale!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 235;
	}      
      if(d->retroceder) //back to 130
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 230;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOLERS,0);
	  formEntrada->incArrProdFz(0);
	  pvSetChecked(p,CHKFORZARPROD,0);
	  //reset scale!
	  formEntrada->resetArrScale(); 
	  pvSetText(p,EDITPESOENT,"0");
	  //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	}
      if(d->cancelar) //form canceled
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      ret = 0;
      break;
    case 233: //product not allowed, authorize?
      if(formEntrada->isIncArrProdFz())
	  d->enFutEstado = 232;
      if(d->retroceder) //back to state 130
	{
	  d->retroceder = 0;
	  formEntrada->resetArrProduct();
	  d->enFutEstado = 230;
	  d->productoCodeActual.clear();
	  pvSetCurrentItem(p,COMBOLERS,0);
	}
      if(d->cancelar) //form canceled
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      break;
    case 235:
      d->enFutEstado=236;
      break;
    case 236:
      d->enFutEstado=232;
      break;
    case 240: //peso ok
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 235;
	}    
      if(d->retroceder) //volvemos al estado 232
	{
	  d->retroceder = 0;
	  d->enFutEstado = 232;
	  //reset scale!
	  formEntrada->resetArrScale(); 
	  pvSetText(p,EDITPESOENT,"0");
	}
      if(d->cancelar) //cancelamos el formulario de entrada
	{
	  d->cancelar=0;
	  resetForm(p,d,formEntrada);
	  formEntrada->rmArrDiFolder();
	  d->enFutEstado = 0;
	  console.push_back("INFO: Formulario cancelado!");
	}
      if( d->proceder) //a tránsito
	{
	//   \/   \/  Edit Rodri
	/*   std::string text;
	   text = p->clipboard;
	   formEntrada->setInputComment(text);*/
	//   /\   /\  Edit Rodri  
	  d->enFutEstado = 98;
	  d->proceder = 0;
	}
      break;
    case 321: //waiting for taking weight, chosen product by internal transfer movement
      if(formEntrada->isArrPesoOk()) //si damos por válidos egúnc riterios el peso de entrada
	{
	  d->enFutEstado = 322;
	}
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 325;
	}	  
      if(d->retroceder || d-> cancelar) //volvemos al estado 0
	{
	  d->retroceder = 0;
	  d->cancelar = 0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  //reset scale!
	  formEntrada->incArrScaleEdited(0);
	  pvSetText(p,EDITPESOENT,"0");
	  //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	}
      ret = 0;
      break;
    case 322: //peso ok
       if(d->pesaje1) //pesamos!
	 {
	   d->pesaje1 = 0;
	   d->enFutEstado = 325;
	 }    
       if( d->proceder) //a tránsito
	 {
	   log_message("(DESCARGA) Transporte de entrada a tránsito", 1);
	   log_message("(DESCARGA) Matrícula: "+ formEntrada->retArrPlate(),  1);
	   d->enFutEstado = 98;
	   d->proceder = 0;	   
	 }
       if(d->retroceder || d-> cancelar) //volvemos al estado 0
	{
	  d->retroceder = 0;
	  d->cancelar = 0;
	  resetForm(p,d,formEntrada);
	  d->enFutEstado = 0;
	  //reset scale!
	  formEntrada->incArrScaleEdited(0);
	  pvSetText(p,EDITPESOENT,"0");
	  //di
	  formEntrada->resetArrDi();
	  formEntrada->rmArrDiFolder();
	}
      break;
    case 325: //transición pesaje báscula 1
      d->enFutEstado = 326;
      break;         
    case 326: //pesaje báscula puesto 1
      d->enFutEstado = 321;
      break;
    case 1000: //salida de descargar
      //auto-syncronization
      if(syncro_needed(&my_syncro_data))
	{
	  globalSyncronization(p,d,formEntrada);
	  actualizaForm(p,d, formEntrada->getState());
	  //commons
	  popteTransito(p,d,TABLATRANSITO, formEntrada);
	  syncro_done(&my_syncro_data);
	}
      /////////////////////
      if(d->entrarDescargar) //selector a salirDescargar
	{
	  d->enFutEstado = 0;
	}
      else if(formEntrada->isPlateInTransit(formEntrada->retDepPlate()))
	{
	  formEntrada->setTransitMov(d->camionElegido,formEntrada->retDepPlate(),localDatabase);
	  if(formEntrada->retDepMovType() == DEF_MOV_TRANSFER)
	    formEntrada->incDepPlateEdited(0);
	  d->enFutEstado = 1020;
	}
       
      else if(d->plateTaking) //si pulsamos en tomar maricula pasamos a capturarla
	{
	  formEntrada->incDepPlateEdited(0);
	  pvSetText(p,EDITCAM_E2,"");
	  formEntrada->setDepPlate("");
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado=1010;
	  d->camionElegido=-1;
	}
      else if(!d->transito_plate.empty())
	{
	  formEntrada->setDepPlate(d->transito_plate);
	  pvSetText(p,EDITCAM_E2,d->transito_plate.c_str());
	}
       
      break;
    case 1010: //carga matricula cámara 1
      d->enFutEstado = 1011;
      break; 
    case 1011:     
      if(d->processTag != 0) //fin del proceso de toma de matrículas
	{
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado = 1000;
	}
      ret = 0;
      break;
    case 1020: //camión elegido
      //correctamente tarado o no?
      if(formEntrada->isDepPesoOk())	
	d->enFutEstado = 1021; //correctamente tarado
      else if(d->pesaje2) //pesaje de tara
	{
	  d->pesaje2 = 0;
	  d->enFutEstado = 1025;
	}
      //cancelamos o retrocedemos
      else if(d->cancelar || d->retroceder)
	{
	  pvSetText(p,EDITCAM_E2,"");
	  d->cancelar = d->retroceder = 0;
	  d->enFutEstado = 1000; //cancelamos
	  resetForm(p,d,formEntrada);
	}
      break;
    case 1021: //truck scaled
      if(formEntrada->isSignature())
	d->enFutEstado = 1023; //it' s signed
      else
	d->enFutEstado = 1022; //no it isn't	
      break;
    case 1022: //not signed
      if(d->pesaje2) //pesaje de tara
	{
	  d->pesaje2 = 0;
	  d->enFutEstado = 1025;
	}
      else if(d->cancelar || d->retroceder)
	{
	  d->cancelar = d->retroceder = 0;
	  d->enFutEstado = 1000; //cancelamos
	  pvSetText(p,EDITCAM_E2,"");
	  pvSetText(p,EDITDIDEF,"");
	  resetForm(p,d,formEntrada);
	}
      else if(d->firmar)
	{
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1035;
	}
      else if(d->test)
	{
	  d->test = 0;
	  formEntrada->saveSignature(1);
	  d->enFutEstado = 1023;
	}
      break;
    case 1023: //animation DI ready?
      d->enFutEstado = 1024;	
      break;
    case 1024: //DI ready?
      if(formEntrada->isDiComplete())
	d->enFutEstado = 1030;
      else
	d->enFutEstado = 1031;	
      break;

    case 1025: //transición pesaje báscula 2
      d->enFutEstado = 1026;
      break;         
    case 1026: //pesaje báscula puesto 2
      d->enFutEstado = 1020;
      break;
 
    case 1030: //DI ready!
      if (d->pesaje2)
	{
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->pesaje2=0;
	  d->enFutEstado = 1025;
	}
      else if(d->firmar)
	{
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1035;
	}
      else if(d->retroceder || d->cancelar)
	{
	  d->retroceder = 0;
	  d->cancelar = 0;
	  d->enFutEstado = 1000;
	  pvSetText(p,EDITCAM_E2,"");
	  pvSetText(p,EDITDIDEF,"");
	  resetForm(p,d,formEntrada);
	}
      else if(d->proceder)
	{
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->proceder =0;	  
	  d->enFutEstado = 1097;
	  //d->enFutEstado = 1098; //deprecated
	  /////////////////////////
	}
      else if(d->editDI)
	{
	  std::cout << "NOS VAMOS A EDICION DEL DI!!" << std::endl;
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->editDI=0;
	  formEntrada->setState(1023);
	  if(formDI!= NULL)
	    delete formDI;
	  formDI = new inputForm();
	  formDI->copyFrom(formEntrada);
	  show_mask6(p);
	}
      break;
    case 1031: //DI INCOMPLETE
      if (d->pesaje2)
	{
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->pesaje2=0;
	  d->enFutEstado = 1025;
	}
      else if(d->firmar)
	{
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1035;
	}
      else if(d->retroceder || d->cancelar)
	{
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->retroceder = 0;
	  d->cancelar = 0;
	  d->enFutEstado = 1000;
	  pvSetText(p,EDITCAM_E2,"");
	  pvSetText(p,EDITDIDEF,"");
	  resetForm(p,d,formEntrada);
	}
      else if(d->editDI)
	{
	  pvSetEnabled(p,BUTEDITDIDEF,0);
	  d->editDI=0;
	  formEntrada->setState(1023);
	  if(formDI!= NULL)
	    delete formDI;
	  formDI = new inputForm();
	  formDI->copyFrom(formEntrada);
	  show_mask6(p);
	}
      break;
    case 1097://staff selection screen
      if(formEntrada->isStaffConfigured()>=0)
	{
	  if(formEntrada->isStaffConfigured()>0)
	    d->enFutEstado = 1098;
	  else
	    {
	      pvMessageBox(p,BUTPROCEDER_E1,BoxWarning,"El código de basculista introducido no está registrado en el sistema",MessageBoxOk,0,0);
	      d->enFutEstado = 1030;
	    }
	}
      break;
    case 1098://animation state
      d->error=0;
      d->enFutEstado = 1099;
      break;
    case 1099:
    	if(!d->error)
		{
			cameraSemaphore(1,1,globalConfiguration.traffic_lights_enabled);
	  		pvSetText(p,EDITDIDEF,"");
	  		pvSetText(p,EDITPESOTARA,"");
	  		pvSetText(p,EDITCAM_E2,"");
	  		resetForm(p,d,formEntrada);
	  		d->enFutEstado = 1000;
	  		console.push_back("INFO: Formulario finalizado!");
		}
      	else
		{
	  		d->error=0;
	  		d->enFutEstado = 1030;
		}
    	break;
      
    case 1035: //fin de firma
      d->enFutEstado = 1036;
      break;
      
    case 1036: //fin de firma
      if(!d->miTableta)
	d->enFutEstado = 1021;
      else if(d->firmado)
	{
	  d->firmado = 0;
	  d->miTableta->stopCapture();
	  delete d->miTableta;
	  espera(1);
	  formEntrada->saveSignature();
	  d->enFutEstado = 1023;
	}
      break;

    default:
      //no state, we reset!
      d->enFutEstado = -2;
      break;
    }
  return ret;
}

#endif
