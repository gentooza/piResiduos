/*
This file is part of PiResiduos.

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

#ifndef _MASK4_STATEGUI_
#define _MASK4_STATEGUI_

static int stateGUI(PARAM *p,DATA* d, int estado)
{
  	switch(estado)
    {
    	case -100:
		{
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
	  		break;
		}
    	case(-2):  //animation state
    	case(98): //saving arrival data
    	case(1021)://analysing Signature
    	case(1035)://signing
    	case 1023: //retrieving all DI data
    	case(1097):
    	case (1098)://saving final data
		{
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
		}
    	case(0)://loading state 1
		{
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
		}
    	case(5)://Loading camera pos 1, aniamtion state
		{
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
		}
    	case(6): //ANIMATION STATE
		{
      		/**COMMON**/
      		toolsSetNAV(p,d,0);
      		break;
		}
    	case(10): // COSTUMER ELECTION
		{
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
		}
    	case(120): //PRODUCT ELECTION WHEN AUTORIZED CLIENT
    	case(20): //PRODUCT ELECTION
      	/**ARRIVAL**/
      	//Frame matricula
		{
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
		}
        case(121)://PRODUCT CHOSEN, AUTHORIZED CLIENT
        case(21)://PRODUCT CHOSEN
        {
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
        }
        case(122)://PRODUCT OK
        case(22)://PRODUCT OK
        {
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
        }
        /**TAKING TRUCK WEIGTH ANIMATION**/
        case 325:
        case 125://ANIMATION STATE
        case 25://ANIMATION STATE
        {
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
        }
        /**END TAKING TRUCK WEIGTH ANIMATION**/
        case(210):
        case(230):
        case(130):
        case(30): //ALL PRODUCTS ELECTION
        {
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
        }
        case(231):
        case(131):
        case(31): //PRODUCT-CLIENT-STATION CHOSEN PROCESSED
        {
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
        }
        case(232):
        case(132):
        case(32): //PRODUCT-CLIENT-STATION ALLOWED
        {
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
        }
        case(233):
        case(133):
        case(33): //PRODUCT-CLIENT-STATION NOT ALLOWED
        {
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
        }
        case 235:
        case 135:
        case 35: //ANIMATION STATE
        {
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
        }
        case 240:
        case 140:
        case 40: //ALL OK, WAITING TO PROCEED
        {
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
        }
        case 101: //PLATE NO REGISTERED
        {
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
        }
        case(110): //CLIENT ELECCION AFTER PLATE AUTHORIZATION
        {
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
        }
        case(321)://Internal transfer movement
        {
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
        }
        case(322)://PRODUCT OK in internal transfer movements
        {
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
        }
        case 1000: //CHOSING EXIT
        {
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
        }
        case(1010)://Loading camera pos 2, animation state
        {
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
        }
        case(1011): //ANIMATION STATE
        {
            /**COMMON**/
            toolsSetNAV(p,d,0);
            break;
        }
        case 1020: //TRUCK CHOSEN
        {
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
        }
        case 1022: //we have to sign the movement
        {
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
        }
        case(1025): //animation state
        {
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
        }
        case 1030: //DI READY
        {
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
        }
        case 1031: //DI NOT READY
        {
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
        }
        default:
            break;	       
    }
    return 0;
}

#endif