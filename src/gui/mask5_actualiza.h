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

#ifndef _MASK5_ACTUALIZA_
#define _MASK5_ACTUALIZA_

static int actualizaForm(PARAM *p,DATA* d, int estado)
{
  //std::cout << "ACTUALIZAMOS FORMULARIO AL ESTADO: " << estado << std::endl;
  switch(estado)
    {
    case -100:
       /**COMMON**/
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      //loading
      pvHide(p,LOADINGFORM);  
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EVEYTHING OFF**/
      toolsDeactivateGUI(p,d,3,formSalida);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0);  
      /****/
      break;
    case(98):
    case(-2)://animation state
    case(1121)://analysing Signature
    case(1123)://analysing DI
    case(1135)://signing
    case 1220:
    case 1223:
    case (1198)://saving final data
      /**COMMON**/
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      //loading
      pvSetMovie(p,LOADINGFORM,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGFORM,-2); // restart
      pvShow(p,LOADINGFORM);  
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EVEYTHING OFF**/
      toolsDeactivateGUI(p,d,3,formSalida);
      //FOCUS
      pvSetFocus(p,CHKENTRADA);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0);  
      /****/
      break;
    case(500):
      pvHide(p,LOADINGFORM);
      /**ARRIVAL**/
      //FRAMES
      setFrame(p,d,FRAMEORDERS,FRAME_SELECTED);
      setFrame(p,d,FRAMECAM_E1,FRAME_DISABLED);
      pvShow(p,IMCAM);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      setFrame(p,d,FRAMEMOV,FRAME_DISABLED);
      setFrame(p,d,FDIPROV,FRAME_DISABLED);			
      setFrame(p,d,FRAMEPESOENT,FRAME_DISABLED);
      setFrame(p,d,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      setFrame(p,d,FRAMECOMMENTENT,FRAME_DISABLED);
      //permits
      pvSetImage(p,ICONPERM,"image/grey.png");
      pvSetImage(p,ICONFECHCONTR,"image/grey.png");
      pvSetImage(p,ICONFECHNPRT,"image/grey.png");
      pvSetImage(p,ICONCB,"image/grey.png");
      pvSetImage(p,ICONCP,"image/grey.png");    
      pvSetImage(p,ICONDCP,"image/grey.png");
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);
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
      pvSetFocus(p,TABORDERS);
      /****/
      break;
    case(501):
      /**ARRIVAL**/
      //Frame matricula
       //FRAMES
      setFrame(p,d,FRAMEORDERS,FRAME_DISABLED);
      setFrame(p,d,FRAMECAM_E1,FRAME_DISABLED);
      pvShow(p,IMCAM);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      setFrame(p,d,FRAMEMOV,FRAME_DISABLED);
      setFrame(p,d,FDIPROV,FRAME_DISABLED);			
      setFrame(p,d,FRAMEPESOENT,FRAME_DISABLED);
      setFrame(p,d,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      //PERMITS
      refreshLerPerms(p,d,1,formSalida);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      setFrame(p,d,FRAMECOMMENTENT,FRAME_NORMAL);
      pvSetEnabled(p,CHKFORZARPROD,0);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,CHKENTRADA);
      /****/
      break;
    case(510):
      /**ARRIVAL**/
      //Frame matricula
       //FRAMES
      setFrame(p,d,FRAMEORDERS,FRAME_DISABLED);
      //
      setFrame(p,d,FRAMECAM_E1,FRAME_SELECTED);
      pvShow(p,IMCAM);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      pvSetEnabled(p,BUTCAM,1);
      pvSetEnabled(p,EDITCAM,1);
      pvSetEnabled(p,BUTEDITCAM1,1);
      //
      setFrame(p,d,FRAMEMOV,FRAME_NORMAL);
      pvSetEnabled(p,CHKFORZARPROD,0);
      setFrame(p,d,FDIPROV,FRAME_DISABLED);			
      setFrame(p,d,FRAMEPESOENT,FRAME_DISABLED);
      setFrame(p,d,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      setFrame(p,d,FRAMECOMMENTENT,FRAME_NORMAL);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTCAM);
      /****/
      break;
    case(511)://Loading camera pos 1, aniamtion state
      /*ARRIVAL*/
      //Frame matricula
      setFrame(p,d,FRAMECAM_E1,FRAME_WORKING);
      pvSetEnabled(p,IMCAM,0);
      pvHide(p,IMCAM);
      pvSetEnabled(p,BUTCAM,0);
      pvSetEnabled(p,EDITCAM,0);
      pvSetEnabled(p,BUTEDITCAM1,0);
      pvSetMovie(p,LOADINGCAM,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGCAM,-2); // restart
      pvShow(p,LOADINGCAM);
      //frame clientes-productos
      setFrame(p,d,FRAMEMOV,FRAME_DISABLED);
      //comentario
      setFrame(p,d,FRAMECOMMENTENT,FRAME_DISABLED);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
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
    case(512): //ANIMATION STATE
      /**COMMON**/
      toolsSetNAV(p,d,0);
      break;
    case(520):
      /**ARRIVAL**/
      //Frame matricula
       //FRAMES
      setFrame(p,d,FRAMEORDERS,FRAME_DISABLED);
      setFrame(p,d,FRAMECAM_E1,FRAME_DISABLED);
      pvShow(p,IMCAM);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      setFrame(p,d,FRAMEMOV,FRAME_NORMAL);
      setFrame(p,d,FDIPROV,FRAME_NORMAL);			
      setFrame(p,d,FRAMEPESOENT,FRAME_SELECTED);
      pvSetEnabled(p,BUTEDITPESOENT,1); 
      setFrame(p,d,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      setFrame(p,d,FRAMECOMMENTENT,FRAME_NORMAL);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      //FOCUS
      pvSetFocus(p,BUTPESOENT);
      /****/
      break;
    case(522):
      /**ARRIVAL**/
      //Frame matricula
       //FRAMES
      setFrame(p,d,FRAMEORDERS,FRAME_DISABLED);
      setFrame(p,d,FRAMECAM_E1,FRAME_DISABLED);
      pvShow(p,IMCAM);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      setFrame(p,d,FRAMEMOV,FRAME_NORMAL);
      setFrame(p,d,FDIPROV,FRAME_NORMAL);			
      setFrame(p,d,FRAMEPESOENT,FRAME_DISABLED);
      setFrame(p,d,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/green.png");
      setFrame(p,d,FRAMECOMMENTENT,FRAME_NORMAL);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_PROCEDER_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1); 
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      //FOCUS
      pvSetFocus(p,BUTPROCEDER_E1);
      /****/
      break;
    case 525: //ANIMATION STATE
      //coment
      setFrame(p,d,FRAMECOMMENTENT,FRAME_DISABLED);
      //starting animation
      pvSetEnabled(p,BUTPESOENT,0);
      pvSetMovie(p,LOADINGPESOENT,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGPESOENT,-2); // restart
      pvShow(p,LOADINGPESOENT);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0); 
      /**COMMON**/
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      break;
    case 526 ://END ANIMATION STATE
      break;
    case(610):
      /**ARRIVAL**/
      //Frame matricula
       //FRAMES
      setFrame(p,d,FRAMEORDERS,FRAME_DISABLED);
      setFrame(p,d,FRAMECAM_E1,FRAME_DISABLED);
      pvShow(p,IMCAM);
      pvSetText(p,LOADINGCAM,"");
      pvHide(p,LOADINGCAM);
      setFrame(p,d,FRAMEMOV,FRAME_NORMAL);
      setFrame(p,d,FDIPROV,FRAME_DISABLED);			
      setFrame(p,d,FRAMEPESOENT,FRAME_DISABLED);
      setFrame(p,d,FRAMEPERMISOENTRADA,FRAME_NORMAL);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      setFrame(p,d,FRAMECOMMENTENT,FRAME_NORMAL);
      pvSetEnabled(p,CHKFORZARPROD,1);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_CANCELAR_RETROCEDER);
      /**EXIT**/
      toolsDeactivateGUI(p,d,1,formEntrada);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      //FOCUS
      pvSetFocus(p,CHKFORZARPROD);
      /****/
      break;
    case 1200:
    case 1100: //DEPARTURES
      pvHide(p,LOADINGFORM);
      /**ARRIVAL**/
      toolsDeactivateGUI(p,d,0,formSalida);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      //Frame tipo salida
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_NORMAL);
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_NORMAL);
      //Frame matricula
      setFrame(p,d,FRAMECAM_E2,FRAME_SELECTED);
      pvSetEnabled(p,IMCAM_E2,1);
      pvShow(p,IMCAM_E2);
      pvSetEnabled(p,BUTCAM_E2,1);
      pvSetFocus(p,BUTCAM_E2);
      pvSetEnabled(p,EDITCAM_E2,1);
      pvSetEnabled(p,BUTEDITCAM2,1);
      pvSetText(p,LOADINGCAM2,"");
      pvHide(p,LOADINGCAM2);
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_DISABLED);
      pvSetEditable(p,EDITDIDEF,0);
      pvSetText(p,LABSTATUSDIDEF,pvtr("N/A"));
      pvSetFontColor(p,LABSTATUSDIDEF,220,220,220);
      pvSetEnabled(p,BUTEDITDIDEF,0);     
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_DISABLED);
      setPesoSal(p,d,WEIGTH_DISABLED,formSalida);
      //botones
      pvSetEnabled(p,BUTFIRMAR,0);
      pvSetEnabled(p,BUTRETENER,0);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_DISABLED);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,1);
      //FOCUS
      pvSetFocus(p,BUTCAM_E2);
      /****/
      break;
    case (1210):
    case(1110)://Loading camera pos 2, animation state
      /*ARRIVAL*/
      //Frame tipo salida
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_DISABLED);
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);
      //Frame matricula
      setFrame(p,d,FRAMECAM_E2,FRAME_WORKING);
      pvSetEnabled(p,IMCAM_E2,0);
      pvHide(p,IMCAM_E2);
      pvSetEnabled(p,BUTCAM_E2,0);
      pvSetEnabled(p,EDITCAM_E2,0);
      pvSetEnabled(p,BUTEDITCAM2,0);
      pvSetMovie(p,LOADINGCAM2,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGCAM2,-2); // restart
      pvShow(p,LOADINGCAM2);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_DISABLED);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      toolsDeactivateGUI(p,d,0,formSalida);
      toolsSetArrDep(p,d,1);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0); 
      /**COMMON**/
      toolsSetNAV(p,d,0);
      break;
    case(1211):
    case(1111): //ANIMATION STATE
      break;
    case 1120: //DEPARTURES
      /**ARRIVAL**/
      toolsDeactivateGUI(p,d,0,formSalida);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);
      /**EXIT**/
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);
      //Frame matricula
      setFrame(p,d,FRAMECAM_E2,FRAME_DISABLED);
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_NORMAL);
      pvSetEnabled(p,EDITDIDEF,0);
      pvSetText(p,LABSTATUSDIDEF,pvtr(""));
      pvSetEnabled(p,BUTEDITDIDEF,0);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_SELECTED);
      pvHide(p,LOADINGPESOSAL);
      pvSetEnabled(p,BUTPESOSAL,1);
      setPesoSal(p, d,WEIGTH_ANALYSIS,formSalida);
      //botones
      pvSetEnabled(p,BUTFIRMAR,0);
      pvSetEnabled(p,BUTRETENER,1);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPESOSAL);
      /****/
      break;
    case 1122: //we have to sign the movement
      pvHide(p,LOADINGFORM);
      /**ARRIVAL**/
      toolsDeactivateGUI(p,d,0,formSalida);
      /**CONTROL PANEL**/
      toolsSetControl(p,d,CTRL_NONE);   
      /**EXIT**/
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);
      //Frame matricula
      setFrame(p,d,FRAMECAM_E2,FRAME_DISABLED);
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_NORMAL);
      pvSetEnabled(p,BUTEDITDIDEF,0);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_NORMAL);
      pvHide(p,LOADINGPESOSAL);
      setPesoSal(p, d,WEIGTH_ANALYSIS,formSalida);
      //boton firma
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,1);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTFIRMAR);
      break;
    case 1125: //ANIMATION STATE
      /**COMMON**/
      toolsDeactivateGUI(p,d,2,formSalida);
      toolsSetNAV(p,d,0);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_NONE);
      //starting animation
      setFrame(p,d,FRAMEPESOSAL,FRAME_SELECTED); 
      pvSetEnabled(p,BUTPESOSAL,0);
      pvSetMovie(p,LOADINGPESOSAL,1,myResources.RES_LOADING.c_str());
      pvMovieControl(p,LOADINGPESOSAL,-2); // restart
      pvShow(p,LOADINGPESOSAL);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,0);
      pvSetEnabled(p,BUTSINCRONIZA,0);
      break;
    case 1126 ://END ANIMATION STATE
      break;
    case 1130: //DI READY
      pvHide(p,LOADINGFORM);
      //tipo de movimiento
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_DISABLED);
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_NORMAL);
      pvHide(p,LOADINGPESOSAL);
      setPesoSal(p,d,WEIGTH_ANALYSIS,formSalida);
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_SELECTED);
      pvSetText(p,LABSTATUSDIDEF,pvtr("DI COMPLETO"));
      pvSetFontColor(p,LABSTATUSDIDEF,60,220,60);
      pvSetEnabled(p,BUTEDITDIDEF,1);
      //botones
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_PROCEDER);
      toolsDeactivateGUI(p,d,0,formSalida);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,1);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPROCEDER_E1);
      /****/
      break;
    case 1230: //DI READY
       pvHide(p,LOADINGFORM);
      //transito
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_DISABLED);
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_DISABLED);
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_SELECTED);
      pvSetText(p,LABSTATUSDIDEF,pvtr("DI COMPLETO"));
      pvSetFontColor(p,LABSTATUSDIDEF,60,220,60);
      pvSetEnabled(p,BUTEDITDIDEF,1);
      //botones
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_PROCEDER);
      toolsDeactivateGUI(p,d,0,formSalida);
      /**SPECIAL**/
      pvSetEnabled(p,BUTTEST,1);
      pvSetEnabled(p,BUTSINCRONIZA,1);
      //FOCUS
      pvSetFocus(p,BUTPROCEDER_E1);   
      break;
    case 1131: //DI NOT READY
      pvHide(p,LOADINGFORM);
      //transito
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_DISABLED);
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_NORMAL);
      pvHide(p,LOADINGPESOSAL);
      setPesoSal(p,d,WEIGTH_ANALYSIS,formSalida);
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_SELECTED);
      pvSetText(p,LABSTATUSDIDEF,pvtr("DI INCOMPLETO"));
      pvSetFontColor(p,LABSTATUSDIDEF,220,60,60);
      pvSetEnabled(p,BUTEDITDIDEF,1);
      //botones
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_NONE);
      toolsDeactivateGUI(p,d,0,formSalida);
      //focus
      pvSetFocus(p,BUTEDITDIDEF);
      break;
    case 1231: //DI NOT READY
      pvHide(p,LOADINGFORM);
      //transito
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_DISABLED);
      //Frame transito
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_DISABLED);
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_SELECTED);
      pvSetText(p,LABSTATUSDIDEF,pvtr("DI INCOMPLETO"));
      pvSetFontColor(p,LABSTATUSDIDEF,220,60,60);
      pvSetEnabled(p,BUTEDITDIDEF,1);
      //botones
      pvSetEnabled(p,BUTFIRMAR,1);
      pvSetEnabled(p,BUTRETENER,1);
      //frames semáforos
      setFrame(p,d,FRAMESEMENTRADA,FRAME_NORMAL);
      setFrame(p,d,FRAMESEMSALIDA,FRAME_NORMAL);  
      //comentario
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_NORMAL);
      /**COMMON**/
      toolsSetNAV(p,d,1);
      toolsSetArrDep(p,d,0);
      toolsSetControl(p,d,CTRL_NONE);
      toolsDeactivateGUI(p,d,0,formSalida);
      /**SPECIAL**/
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
  if(d->enFutEstado != formSalida->getState())
    {
      switch(d->enFutEstado)
	{
	case -1: //no previous form
	  {
	    pvSetChecked(p,CHKENTRADA,1);
	    pvSetChecked(p,CHKSALIDA,0);
	    d->productoActual.clear();
	    d->llegada=1;	   
	    break;
	  }
	case 99:
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
	    
	    if(formSalida->storeTransit(localDatabase,remoteDatabase,myStation,remote_connected))
	      console.push_back("AVISO: no se consiguió escribir el movimiento a tránsito en la base de datos remota, sincronice cuando pueda");
	    cameraSemaphore(3,1,globalConfiguration.traffic_lights_enabled);
	    break;
	  }
	case 500: //waiting plate selection
	  {
	    //commons
	    popteTransito(p,d,TABLATRANSITO,formSalida);
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
	    //populate orders table
	    formSalida->setOrders(localDatabase, myStation->getCode());	   
	    popteOrders(p,d,TABORDERS,formSalida);
	    d->selectedOrder=-1;
	    break;
	  }
	case 501: //order selected
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
	    //COSTUMER NAME
	    pvSetText(p,EDITCLIENT,formSalida->retArrCosName().c_str());		
	    //PRODUCT NAME
	    pvSetText(p,EDITPRODUCT,formSalida->retArrProdFullName().c_str());		
	    //PERMITS
	    formSalida->setArrCosProdPermits(localDatabase);	    	   
	    break;
	  }
	case 510: //DI creation and folder saving
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
	    
	    pvSetText(p,EDITDIPROV,formSalida->createArrDi(localDatabase).c_str());	    
	    if(!formSalida->isIncArrPlateEdited())
	      formSalida->savePlateImage(3,"entrada");
	  break;
	case 511: //loading camera state
	  break;
	case 512: //taking plate!
	  {	    
	    std::string plate;
	    ret = useCamera(p, d, 3, plate, IMCAM);
	    if(!ret)
	      {
		pvSetText(p,EDITCAM,pvtr(plate.c_str()));
		formSalida->setArrPlate(plate);
		d->processTag=1;
	      }
	    else
	      {
		d->processTag=-1;
		sprintf(error,"*ERROR* imposible recibir matrícula de la cámara 3");
		console.push_back(error);
	      }
	    break;
	  }
	case 520: //good plate, waiting for taking weight and showing temporal DI
	case 522: 
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);	    	   	
	    break;
	  }

	case 525:
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
	    
	    char error[256];
	    bascula * testBascula = NULL;
	    //reseteamos peso
	    std::string sPesoTest = "-1";
	    pvSetText(p,EDITPESOENT,sPesoTest.c_str());
	    formSalida->setArrScaleIn(0);
	    formSalida->incArrScaleEdited(0);
	    //
	    sprintf(error,"(INFO) probando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, \nparidad:%s , control de flujo:%s y %s bits de parada...",3, basculas.at(2).port.c_str(),basculas.at(2).bauds,basculas.at(2).timeout , basculas.at(2).ask.c_str(), (basculas.at(2).parity==0?"ninguna":(basculas.at(2).parity==1?"impar":"par")),(basculas.at(2).ctrl==0?"ninguno":(basculas.at(2).ctrl==1?"software":"hardware")),(basculas.at(2).stopBits==0?"1":(basculas.at(2).stopBits==1?"1,5":"2")));
	    console.push_back(error);
	    testBascula = new bascula(basculas.at(2).port,basculas.at(2).bauds);
	    if(!basculas.at(2).ask.empty())
	      {
		testBascula->set_parity(basculas.at(2).parity);
		testBascula->set_flowControl(basculas.at(2).ctrl);
		testBascula->set_stopBits(basculas.at(2).stopBits);
		//no capturamos excepciones
		testBascula->setCommand(basculas.at(2).ask);	     
		std::cout << "(INFO) leyendo peso!" << std::endl;
		char* texto;
		try
		  {
		    int ret = testBascula->readPeso(basculas.at(2).timeout,texto);
		    std::string sPeso =  fromBufferAPeso(texto);
		    formSalida->setArrScaleIn(std::stoi(sPeso));		    
		    pvSetText(p,EDITPESOENT,sPeso.c_str());
		    if(ret)
		      {
			console.push_back("(AVISO) posible TIMEOUT o lectura errónea del puerto");
		      }
		    pvSetText(p,EDITPESOENT,sPeso.c_str());
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
	case 610:
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
	    if(formSalida->getFzCurrentProduct())
	      pvSetChecked(p,CHKFORZARPROD,1);
	    else
	      pvSetChecked(p,CHKFORZARPROD,0); 
	    break;
	  }
	case 1100:
	  popteTransito(p,d,TABLATRANSITO, formSalida);
	  //tipo de movimiento tránsito!
	  formSalida->setDepMovType(DEF_MOV_SALIDA);
	  d->transito_plate.clear();
	  d->post_transito_plate.clear();
	  break;
	case 1200:
	  //tipo de movimiento transferencia!
	  formSalida->setTransferMov(DEF_BIORECICLAJE_CODE,myStation);	  
	  break;
	case 1210:
	case 1110: //animation, camera 4
	  break;
	case 1211:
	case 1111: //taking plate camera 4
	  {  
	    std::string plate;	    
	    ret = useCamera(p, d, 4, plate, IMCAM_E2);
	    if(!ret)
	      {
		pvSetText(p,EDITCAM_E2,pvtr(plate.c_str()));
		d->processTag=1;
		formSalida->setDepPlate(plate);
	      }
	    else
	      {
		d->processTag=-1;
		sprintf(error,"*ERROR* imposible recibir matrícula de la cámara 4");
		console.push_back(error);
	      }
	    break;
	  }
	case 1120:
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);

	    pvSetText(p,EDITDIDEF,formSalida->createDepDi(localDatabase).c_str());    
	    if(!formSalida->isIncDepPlateEdited())	    
	      formSalida->savePlateImage(4,"salida");
	    std::string pesoSalida = std::to_string(formSalida->retDepScaleOut());
	    pvSetText(p,EDITPESOSAL,pesoSalida.c_str());
	    //default driver
	    if(formSalida->default_driver(localDatabase))
	      {
		driver *tmp_driver;
		formSalida->ret_dep_driver(tmp_driver);
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
	case 1121://we store scale in database
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
	    d->test= 0;
	    int DatabaseData_chkd;
	    try
	      {
		DatabaseData_chkd= std::stoi(remoteDatabaseData.db_port);
	      }
	    catch(...)
	      {
		DatabaseData_chkd = 0;
	      }
	    formSalida->saveScaleOut(localDatabase,remoteDatabase,remoteDatabaseData.db_host.c_str(), DatabaseData_chkd);
	  }
	  break;
	case 1223:
	  refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL); 
	  pvSetText(p,EDITCAM_E2,formSalida->retDepPlate().c_str());
	  pvSetText(p,EDITDIDEF,formSalida->retDepDi().c_str());
	  break;
	case(1123):
	  refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
	  break;
	case(1224):
	case(1124): //loading all DI information
	  {
	    costumer * ourId = new costumer(DEF_BIORECICLAJE_CODE,localDatabase);
	    formSalida->setOurId(ourId);
	    delete ourId;
	    formSalida->setAllDiData(localDatabase, myStation, DEF_BIORECICLAJE_CODE, DEF_TRANS_CODE);
	    break;
	  }
	case 1125: //transición pesaje2
	  break; 
	case 1126:
	  {	    
	    char error[256];
	    bascula * testBascula = NULL;
	    //reseteamos peso
	    std::string sPesoTest = "-1";
	    pvSetText(p,EDITPESOSAL,sPesoTest.c_str());
	    formSalida->setDepScaleOut(0);
	    //
	    sprintf(error,"(INFO) usando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, \nparidad:%s , control de flujo:%s y %s bits de parada...",4, basculas.at(3).port.c_str(),basculas.at(3).bauds,basculas.at(3).timeout , basculas.at(3).ask.c_str(), (basculas.at(3).parity==0?"ninguna":(basculas.at(3).parity==1?"impar":"par")),(basculas.at(3).ctrl==0?"ninguno":(basculas.at(3).ctrl==1?"software":"hardware")),(basculas.at(3).stopBits==0?"1":(basculas.at(3).stopBits==1?"1,5":"2")));
	    console.push_back(error);
	    testBascula = new bascula(basculas.at(3).port,basculas.at(3).bauds);
	    if(!basculas.at(3).ask.empty())
	      {
		testBascula->set_parity(basculas.at(3).parity);
		testBascula->set_flowControl(basculas.at(3).ctrl);
		testBascula->set_stopBits(basculas.at(3).stopBits);
		//no capturamos excepciones
		testBascula->setCommand(basculas.at(3).ask);	     
		std::cout << "(INFO) leyendo peso!" << std::endl;
		char* texto;
		try
		  {
		    int ret = testBascula->readPeso(basculas.at(3).timeout,texto);
		    std::string sPeso =  fromBufferAPeso(texto);
		    pvSetText(p,EDITPESOSAL,sPeso.c_str());
		    formSalida->setDepScaleOut(std::stoi(sPeso));		      
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
	case 1230:
	case 1130:
	  pvSetText(p,EDITCODETRANSP,std::to_string(formSalida->retDepDriCode()).c_str());
	  pvSetText(p,EDITNAMETRANSP,formSalida->retDepDriName().c_str());
	  refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);	  
	  break;
	case 1231:
	case 1131:
	  pvSetText(p,EDITCODETRANSP,std::to_string(formSalida->retDepDriCode()).c_str());
	  pvSetText(p,EDITNAMETRANSP,formSalida->retDepDriName().c_str());
	  refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
	  break;
	case 1136: //signing
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
	    //TODO
	    //REMOVE DATABASE QUERY FROM HERE
	    std::string cname;
	    std::string productText;
	    char * sql;
	    //COSTUMER
	    std::string clientCode = std::to_string(formSalida->retDepCosCode());
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
	    std::string productCode = std::to_string(formSalida->retDepProdCode());
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
		//TODO
		int pesoTotal =  formSalida->retDepScaleOut() - formSalida->retDepScaleIn();
		//TOTAL WEIGHT IS NOW MANAGED BY FORMULARIO CLASS, AND ITS DERIVED
		sprintf(speso,"%d",pesoTotal);
		std::string sspeso = speso;
		float precio = pesoTotal *  formSalida->retDepPrice()/1000.0;
		std::string sPrecio = std::to_string (precio);
		//std::cout << cname << "," << productText << std::endl;
		d->miTableta->setInfoShow(formSalida->retDepPlate(),cname,productText,sPrecio, sspeso);
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
		    console.push_back("**ERROR** desenchufe y vuelva a enchufar la tableta de firmas y vuélvalo a intentar");
		    if(!error)
		      d->miTableta->reset();
		    delete d->miTableta;
		    d->miTableta = NULL;
		  }
	      }
	    else
	      {

		console.push_back("**ERROR** ¡Tableta de firmas no detectada!");
		delete d->miTableta;
		d->miTableta = NULL;
	      }
	      
	  }
	  break;
	case 1221:
	  {
	    //operator comment
	    refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);	    
	    pvSetText(p,EDITDIDEF,formSalida->createDepDi(localDatabase).c_str());
	    //Create fake signature for transportist not present	    
	    formSalida->saveSignature("image/void.png");
	    //default driver
	    if(formSalida->default_driver(localDatabase))
	      {
		driver *tmp_driver;
		formSalida->ret_dep_driver(tmp_driver);
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
	case 1197:
	  formSalida->unsetStaff();
	  pvInputDialog(p,BUTPROCEDER_E1,"Inserte el código de basculista para proceder:","");
	  break;
	case 1199: //almacenaje del movimiento, impresión del pdf
	{
	  //to DATABASE
	  int DatabaseData_chkd;
	  int remote_connected = 0;
	  int error_check = 0;
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
	  d->ret = 0;

    std::string myPrinter;
    miIni->retPrinterId(myPrinter);
    if(myPrinter.empty())
		  console.push_back("**AVISO** no se va a imprimir el DI, al no tener configurada la impresora");
    // transfers movements
    if (formSalida->retDepMovType() == DEF_MOV_TRANSFER)
    {			
		  error_check = formSalida->storeDepTransfer(localDatabase, remoteDatabase,remote_connected);
			if(error_check == -2) //cathastrophic
	  	{
	    	console.push_back("*ERROR* no se pudo guardar la transferencia, contacte con mantenimiento");
	    	d->ret = 1;
	  	}
			else
			{
				formSalida->saveSignature(1);
	    	if(error_check == -1) //only remote error
	    	{
					console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
					console.push_back("*ERROR* ¡Necesita sincronizar! Si se trata de un movimiento de transferencia la estación de destino no lo verá");
				}
				formSalida->createPdf(myPrinter);
	    	d->ret = 0;
	  	}
    }
    // outcoming loading materials movements
    else
    {		
			error_check = formSalida->storeDepMov(localDatabase,remoteDatabase,remote_connected);
			if(!error_check)
	  	{
        console.push_back("INFO Movimiento generado correctamente");
	    	d->ret = 0;
	  	}
			else if(error_check == -1) //remote fail
	  	{
	    	console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
	    	console.push_back("*ERROR* ¡Necesita sincronizar! Si se trata de una orden de recogida necesitará que administración la borre manualmente");
	    	d->ret = 0;
	  	}
			else //Cathastrophic
	  	{
	    	console.push_back("*ERROR* ¡Fallo al guardar el movimiento!");
	    	d->ret =1;
	  	}	
      if(!d->ret)
      {
        // saving signature
        formSalida->saveSignature();
        // printing DI
        formSalida->createPdf(myPrinter);
        // sending incidents email
        if(mailClient->sendIncidentsMail(myStation,formSalida))
				  console.push_back("*ERROR* ¡Error en el sistema de envío de emails");
        // backing up files
        formSalida->backupFiles(formSalida->retDepMovCode().c_str());
      }
    }
    cameraSemaphore(4,1,globalConfiguration.traffic_lights_enabled);
    break;
	}
	default:
	  	break;
	}
      formSalida->setState(d->enFutEstado);
      actualizaForm(p,d,formSalida->getState());
      ret = 0;
    }
  return ret;
}


//condiciones de cambio
static int maquinaEstados(PARAM *p, DATA *d)
{
  int ret = -1;
  switch(formSalida->getState()) 
    {
      case -100:
      {
	//selection checkbox arrives vs departures
	if(d->enFutEstado >=1100) //departures
	  {
	    d->llegada=0;
	    pvSetChecked(p,CHKSALIDA,1);
	    pvSetChecked(p,CHKENTRADA,0);
	    d->camionElegido = -1;
	    if(formSalida->retDepMovType() == DEF_MOV_TRANSFER)	      
	      pvSetChecked(p,CHKTRANSFERENCIA,1);	      
	    else
		pvSetChecked(p,CHKTRANSITO,1);
	    if(!formSalida->retDepDi().empty())
	      pvSetText(p,EDITDIDEF, formSalida->retDepDi().c_str());
	    if(formSalida->retDepScaleOut())	      
	      pvSetText(p,EDITPESOSAL, std::to_string(formSalida->retDepScaleOut()).c_str());
	    if(!formSalida->retDepPlate().empty())
	       pvSetText(p,EDITCAM_E2,formSalida->retDepPlate().c_str());	    	
	  }
	else //entrada a planta
	  {
	    d->llegada=1;
	    pvSetChecked(p,CHKSALIDA,0);
	    pvSetChecked(p,CHKENTRADA,1);
	    if(d->enFutEstado >= 501) //order selected
	      {
		popteTransito(p,d,TABLATRANSITO, formSalida);
		popteOrders(p,d,TABORDERS,formSalida);
		//COSTUMER NAME
		pvSetText(p,EDITCLIENT,formSalida->retArrCosName().c_str());
		//PRODUCT NAME
		pvSetText(p,EDITPRODUCT,formSalida->retArrProdFullName().c_str());
		//PERMITS
		formSalida->setArrCosProdPermits(localDatabase);
		refreshLerPerms(p,d,1,formSalida);
		if(formSalida->getFzCurrentProduct())
		  pvSetChecked(p,CHKFORZARPROD,1);
		else
		  pvSetChecked(p,CHKFORZARPROD,0);
		//plate
		pvSetText(p,EDITCAM,formSalida->retArrPlate().c_str());
		//DI and weight
		if(d->enFutEstado >= 520 && d->enFutEstado != 610)
		  {
		    pvSetText(p,EDITDIPROV,formSalida->retArrDi().c_str());
		    std::string sPeso = std::to_string(formSalida->retArrScaleIn());
		    pvSetText(p,EDITPESOENT,sPeso.c_str());
		  }
	      }
	  }
	break;
      }
    case -2:
      //LLegamos nuevos!
      d->llegada=1;
      pvSetChecked(p,CHKENTRADA,1);
      pvSetChecked(p,CHKTRANSITO,1);
      d->enFutEstado = -1;
      ret = 0;
      break; 
    case -1: //inicialización
      d->enFutEstado = 500;
      ret = 0;
      break;
    case 98: //animation
      d->enFutEstado = 99;
      break;
    case 99: //order in TRANSITO_SALIDAS
      d->enFutEstado=500;
      resetForm(p,d,formSalida);
      console.push_back("INFO: vehículo a tránsito interno!");
      break;
    case 500: //waiting order selection
      //auto-syncronization
      if(syncro_needed(&my_syncro_data))
	{
	  globalSyncronization(p,d,formSalida);
	  actualizaForm(p,d, formSalida->getState());
	  //commons
	  popteTransito(p,d,TABLATRANSITO,formSalida);
	  formSalida->setOrders(localDatabase, myStation->getCode());	   
	  popteOrders(p,d,TABORDERS,formSalida);
	  syncro_done(&my_syncro_data);
	}
      /////////////////////
      if(!d->llegada) //selector a finalizar
	{
	  if(formSalida->retDepMovType() == DEF_MOV_TRANSFER)
	    d->enFutEstado = 1200;
	  else
	    {
	      formSalida->setDepMovType(DEF_MOV_SALIDA);
	      pvSetChecked(p,CHKTRANSITO,1);
	      d->enFutEstado = 1100;	
	    }	    
	}
      else if(formSalida->isArrMov()>0)
	{
	  d->enFutEstado = 501;		       	  
	}
      break;
    case 501: //order selected is permited?

      if(formSalida->isArrProdPermit())
	{
	  d->enFutEstado = 510;
	}
      else
	{
	  d->enFutEstado = 610;
	}
      break;
    case 510: //order selected allowed
      //taking plate
      if(d->plateTaking)
	{
	  formSalida->incArrPlateEdited(0);
	  pvSetText(p,EDITCAM,"");
	  formSalida->setArrPlate("");
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado = 511;
	}
      //plate ok
       if(formSalida->isArrPlateOk())
      	  d->enFutEstado = 520;
      //cancel or back
       if(d->cancelar || (d->retroceder && !formSalida->isIncArrProdFz()))
	{
	  d->cancelar = d->retroceder = 0;
	  d->enFutEstado = 500; //cancelamos
	  d->selectedOrder = -1;
	  resetForm(p,d,formSalida);
	  formSalida->rmArrDiFolder();
	}
      else if(d->retroceder && formSalida->isIncArrProdFz())
	{
	  d->retroceder = 0;
	  d->enFutEstado = 610;
	  formSalida->rmArrDiFolder();
	}
      break;
    case 511: //animation state taking arrival plate
      d->enFutEstado = 512;
      break;
    case 512: //taking arrival plate
      d->enFutEstado = 510;
      break;
    case 520: //waiting to take weight
      //taking weigth
      if(d->pesaje1) //pesamos!
	{
	  d->pesaje1 = 0;
	  d->enFutEstado = 525;
	}  
      //tara ok
      if(formSalida->isArrPesoOk())
      	{
      	  d->enFutEstado = 522;
      	}
      if(d->cancelar)
	{
	  d->cancelar = 0;
	  d->enFutEstado = 500;
	  d->selectedOrder = -1;
	  resetForm(p,d,formSalida);
	  formSalida->rmArrDiFolder();
	  console.push_back("INFO: Formulario cancelado!");
	}
      //back
      if(d->retroceder)
	{
	  d->retroceder = 0;
	  d->enFutEstado = 510;
	  formSalida->resetArrPlate();
	  pvSetText(p,EDITCAM,"");
	}
      break;
    case 522: //weight taken, waiting to proceed
       if(d->proceder)
	{
	  d->proceder = 0;
	  d->enFutEstado = 98;
	}     
       else if(d->cancelar)
	{
	  d->cancelar = 0;
	  d->enFutEstado = 500;
	  d->selectedOrder = -1;
	  resetForm(p,d,formSalida);
	  formSalida->rmArrDiFolder();
	  console.push_back("INFO: Formulario cancelado!");
	}
      //back
       else if(d->retroceder)
	{
	  d->retroceder = 0;
	  d->enFutEstado = 520; 
	  //reset scale!
	  formSalida->setArrScaleIn(0);
	  formSalida->incArrScaleEdited(0);
	  pvSetText(p,EDITPESOENT,"0");
	}
      break;
    case 525:
      d->enFutEstado=526;
      break;
    case 526:
      d->enFutEstado=520;
      pvHide(p,LOADINGPESOENT);
      pvSetEnabled(p,BUTPESOENT,1);
      break;
    case 610: //order selected no allowed
      if(formSalida->isIncArrProdFz())
	  d->enFutEstado = 510;
      //cancel or back
      if(d->cancelar || d->retroceder)
	{
	  d->cancelar = d->retroceder = 0;
	  d->enFutEstado = 500; //cancelamos
	  d->selectedOrder = -1;
	  resetForm(p,d,formSalida);
	}
      break;
    case 1100:
      //auto-syncronization
      if(syncro_needed(&my_syncro_data))
	{
	  globalSyncronization(p,d,formSalida);
	  actualizaForm(p,d, formSalida->getState());
	  //commons
	  popteTransito(p,d,TABLATRANSITO, formSalida);
	  syncro_done(&my_syncro_data);
	}
      /////////////////////
      if(d->llegada) //selector to llegada
	{
	  d->enFutEstado = 500;
	}
      else if(formSalida->isPlateInTransit(formSalida->retDepPlate()))
	{
	  formSalida->setTransitMov(d->camionElegido,formSalida->retDepPlate(),localDatabase);
	  d->enFutEstado = 1120;
	}       
      else if(d->plateTaking) //si pulsamos en tomar maricula pasamos a capturarla
	{
	  d->camionElegido = -1;
	  formSalida->incDepPlateEdited(0);
	  pvSetText(p,EDITCAM_E2,"");
	  formSalida->setDepPlate("");
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado=1110;	    
	}
      else if(formSalida->retDepMovType() == DEF_MOV_TRANSFER)
	d->enFutEstado = 1200;
      else if(!d->transito_plate.empty())
	{
	  formSalida->setDepPlate(d->transito_plate);
	  pvSetText(p,EDITCAM_E2,d->transito_plate.c_str());
	}
      break;
    case 1200:
      if(d->llegada) //selector to llegada
	  d->enFutEstado = 500;
      else if(formSalida->retDepMovType() == DEF_MOV_SALIDA)
	d->enFutEstado = 1100;
      else if(d->plateTaking) //si pulsamos en tomar maricula pasamos a capturarla
	{
	  formSalida->incDepPlateEdited(0);
	  pvSetText(p,EDITCAM_E2,"");
	  formSalida->setDepPlate("");
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado=1210;	    
	}
      else if (!formSalida->retDepPlate().empty() &&  formSalida->retDepPlate().compare(""))
	d->enFutEstado = 1220;
      break;
    case 1110: //carga matricula cámara 4
      d->enFutEstado = 1111;
      break; 
    case 1111:     
      if(d->processTag != 0) //fin del proceso de toma de matrículas
	{
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado = 1100;
	}
      ret = 0;
      break;
    case 1210: //carga matricula cámara 4
      d->enFutEstado = 1211;
      break; 
    case 1211:     
      if(d->processTag != 0) //fin del proceso de toma de matrículas
	{
	  d->plateTaking = 0;
	  d->processTag = 0;
	  d->enFutEstado = 1200;
	}
      ret = 0;
      break;
    case 1120:
      //weigth ok
      if(formSalida->isDepPesoOk()==1)
	  d->enFutEstado = 1121;
      //taking weigth
      else if(d->pesaje2) //pesamos!
	{
	  formSalida->incDepScaleEdited(0);
	  d->pesaje2 = 0;
	  d->enFutEstado = 1125;
	}
      //cancelamos o retrocedemos
      else if(d->cancelar || d->retroceder)
	{
	  d->cancelar = d->retroceder = 0;
	  d->enFutEstado = 1100;
	  resetForm(p,d,formSalida);
	} 
      break;
    case 1121:
      if(formSalida->isSignature())
	d->enFutEstado = 1123; //it' s signed
      else
	d->enFutEstado = 1122; //no it isn't
      break;
    case 1122: //not signed
      if(d->pesaje2) //pesaje de tara
	{
	  formSalida->incDepScaleEdited(0);
	  d->pesaje2 = 0;
	  d->enFutEstado = 1125;
	}
      else if(d->cancelar || d->retroceder)
	{
	  d->cancelar = d->retroceder = 0;
	  d->enFutEstado = 1100; //cancelamos
	  pvSetText(p,EDITCAM_E2,"");
	  resetForm(p,d,formSalida);
	}
      else if(d->firmar)
	{
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1135;
	}
      else if(d->test)
	{
	  d->test = 0;
	  formSalida->saveSignature(1);
	  d->enFutEstado = 1123;
	}
      break;
    case 1123:
      d->enFutEstado = 1124;	
      break;
    case 1124: //DI ready?
      if(formSalida->isDiComplete())
	d->enFutEstado = 1130;
      else
	d->enFutEstado = 1131;	
      break;
    case 1220:
      d->enFutEstado = 1221;
      break;
    case 1221:
      d->enFutEstado = 1223;
      break;
    case 1223:
      d->enFutEstado = 1224;
      break;
    case 1224:
      if(formSalida->isDiComplete())
	d->enFutEstado = 1230;
      else
	d->enFutEstado = 1231;	
      break;    
    case 1125:
      d->enFutEstado=1126;
      break;
    case 1126:
      d->enFutEstado=1120;
      break;
    case 1130: //DI ready!
      if (d->pesaje2)
	{
	  d->pesaje2=0;
	  d->enFutEstado = 1125;
	}
      else if(d->firmar)
	{
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1135;
	}
      else if(d->retroceder || d->cancelar)
	{
	  d->retroceder = 0;
	  d->cancelar = 0;
	  d->enFutEstado = 1100;
	  pvSetText(p,EDITCAM_E2,"");
	  resetForm(p,d,formSalida);
	}
      else if(d->proceder)
	{
	  d->proceder =0;	  
	  d->enFutEstado = 1197;
	}
      else if(d->editDI)
	{
	  d->editDI=0;
	  formSalida->setState(1123);
	  formDI = new outputForm();
	  formDI->copyFrom(formSalida);
	  show_mask6(p);
	}
      break;
    case 1131: //DI INCOMPLETE
      if (d->pesaje2)
	{
	  d->pesaje2=0;
	  d->enFutEstado = 1125;
	}
      else if(d->firmar)
	{
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1135;
	}
      else if(d->retroceder || d->cancelar)
	{
	  d->retroceder = 0;
	  d->cancelar = 0;
	  d->enFutEstado = 1100;
	  pvSetText(p,EDITCAM_E2,"");
	  resetForm(p,d,formSalida);
	}
      else if(d->editDI)
	{
	  d->editDI=0;
	  formSalida->setState(1123);
	  formDI = new outputForm();
	  formDI->copyFrom(formSalida);
	  std::cout << "TIPO MOVIMIENTO ORIGINAL:" <<formSalida->retDepMovType() <<std::endl;
	  std::cout << "TIPO MOVIMIENTO COPIA DI:" <<formDI->retDepMovType() <<std::endl;
	  show_mask6(p);
	}
      break;
    case 1230: //DI ready!
      /*
      if(d->firmar)
	{
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1235;
	  }*/
      if(d->retroceder || d->cancelar)
	{
	  d->retroceder = 0;
	  d->cancelar = 0;
	  d->enFutEstado = 1200;
	  resetForm(p,d,formSalida);
	}
      else if(d->proceder)
	{
	  d->proceder =0;	  
	  d->enFutEstado = 1197;
	}
      else if(d->editDI)
	{
	  d->editDI=0;
	  formSalida->setState(1221);
	  if(formDI!= NULL)
	    delete formDI;
	  formDI = new outputForm();
	  formDI->copyFrom(formSalida);	  
	  show_mask6(p);
	}
      break;
    case 1231: //DI INCOMPLETE
      /*      else if(d->firmar)
	{
	  d->firmado = 0;
	  d->firmar = 0;
	  d->enFutEstado=1235;
	  }*/
      if(d->retroceder || d->cancelar)
	{
	  d->retroceder = 0;
	  d->cancelar = 0;
	  d->enFutEstado = 1200;
	  resetForm(p,d,formSalida);
	}
      else if(d->editDI)
	{
	  d->editDI=0;
	  formSalida->setState(1221);
	  if(formDI!= NULL)
	    delete formDI;
	  formDI = new outputForm();
	  formDI->copyFrom(formSalida);
	  show_mask6(p);	  
	}
      break;
    case 1197://staff selection screen
      if(formSalida->isStaffConfigured()>=0)
	{
	  if(formSalida->isStaffConfigured()>0)
	    d->enFutEstado = 1198;
	  else
	    {
	      pvMessageBox(p,BUTPROCEDER_E1,BoxWarning,"El código de basculista introducido no está registrado en el sistema",MessageBoxOk,0,0);
	      if(formSalida->retDepMovType() == DEF_MOV_TRANSFER)
		d->enFutEstado = 1230;
	      else
		d->enFutEstado = 1130;
	    }
	}
      break;
    case 1198://animation state
      d->enFutEstado = 1199;
      break;
    case 1199:
      if(!d->ret)
	{
	  resetForm(p,d,formSalida);
	  d->enFutEstado = 1100;
	  console.push_back("INFO: Formulario finalizado!");
	}
      else
	{
	  d->enFutEstado = 1230;
	  console.push_back("*ERROR* imposible cargar el movimiento, no hay conexión con la base de datos central");
	}
      break;
    case 1135: //start signing
      d->enFutEstado=1136;
      break;       
    case 1136: //fin de firma
      if(!d->miTableta)
	d->enFutEstado = 1121;
      else if(d->firmado)
	{
	  d->firmado = 0;
	  d->miTableta->stopCapture();
	  delete d->miTableta;
	  espera(1);
	  formSalida->saveSignature();
	  d->enFutEstado = 1123;
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
