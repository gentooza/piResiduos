/*
This file is part of PiResiduos.

Copyright 2017-2019, Pro Integra SL.
Copyright 2019-2022 Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

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

#ifndef _MASK5_STATEGUI_
#define _MASK5_STATEGUI_

static int stateGUI(PARAM *p,DATA* d, int estado)
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

#endif