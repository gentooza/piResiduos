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

#ifndef _MASK5_STATENEXT_
#define _MASK5_STATENEXT_

static int stateNext(PARAM *p, DATA *d)
{
    int ret = -1;
    switch(formSalida->getState()) 
    {
        case(-100):
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
        {
            //LLegamos nuevos!
            d->llegada=1;
            pvSetChecked(p,CHKENTRADA,1);
            pvSetChecked(p,CHKTRANSITO,1);
            d->enFutEstado = -1;
            ret = 0;
            break;
        } 
        case -1: //inicialización
        {
            d->enFutEstado = 500;
            ret = 0;
            break;
        }
        case 98: //animation
        {
            d->enFutEstado = 99;
            break;
        }
        case 99: //order in TRANSITO_SALIDAS
        {
            d->enFutEstado=500;
            resetForm(p,d,formSalida);
            console.push_back("INFO: vehículo a tránsito interno!");
            break;
        }
        case 500: //waiting order selection
        {
            // auto-syncronization
            if(syncro_needed(&my_syncro_data))
	        {
	            globalSyncronization(p,d,formSalida);
	            stateGUI(p,d, formSalida->getState());
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
        }
        case 501: //order selected is permited?
        {
            if(formSalida->isArrProdPermit())
	        {
	            d->enFutEstado = 510;
	        }
            else
	        {
	            d->enFutEstado = 610;
	        }
            break;
        }
        case 510: //order selected allowed
        {
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
        }
        case 511: //animation state taking arrival plate
        {
            d->enFutEstado = 512;
            break;
        }
        case 512: //taking arrival plate
        {
            d->enFutEstado = 510;
            break;
        }
        case 520: //waiting to take weight
        {
            //taking weigth
            if(d->pesaje1)
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
        }
        case 522: //weight taken, waiting to proceed
        {
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
        }
        case 525:
        {
            d->enFutEstado=526;
            break;
        }
        case 526:
        {
            d->enFutEstado=520;
            pvHide(p,LOADINGPESOENT);
            pvSetEnabled(p,BUTPESOENT,1);
            break;
        }
        case 610: //order selected no allowed
        {
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
        }
        case 1100:
        {
            //auto-syncronization
            if(syncro_needed(&my_syncro_data))
	        {
	            globalSyncronization(p,d,formSalida);
	            stateGUI(p,d, formSalida->getState());
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
        }
        case 1200:
        {
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
        }
        case 1110: //carga matricula cámara 4
        {
            d->enFutEstado = 1111;
            break;
        }
        case 1111:
        {
            if(d->processTag != 0) //fin del proceso de toma de matrículas
	        {
	            d->plateTaking = 0;
	            d->processTag = 0;
	            d->enFutEstado = 1100;
	        }
            ret = 0;
            break;
        }
        case 1210: //carga matricula cámara 4
        {
            d->enFutEstado = 1211;
            break; 
        }
        case 1211:
        {
            if(d->processTag != 0) //fin del proceso de toma de matrículas
	        {
	            d->plateTaking = 0;
	            d->processTag = 0;
	            d->enFutEstado = 1200;
	        }
            ret = 0;
            break;
        }
        case 1120:
        {
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
        }
        case 1121:
        {
            if(formSalida->isSignature())
	            d->enFutEstado = 1123; //it' s signed
            else
	        d->enFutEstado = 1122; //no it isn't
            break;
        }
        case 1122: //not signed
        {
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
        }
        case 1123:
        {
            d->enFutEstado = 1124;	
            break;
        }
        case 1124: //DI ready?
        {
            if(formSalida->isDiComplete())
	            d->enFutEstado = 1130;
            else
	            d->enFutEstado = 1131;	
            break;
        }
        case 1220:
        {
            d->enFutEstado = 1221;
            break;
        }
        case 1221:
        {
            d->enFutEstado = 1223;
            break;
        }
        case 1223:
        {
            d->enFutEstado = 1224;
            break;
        }
        case 1224:
        {
            if(formSalida->isDiComplete())
	            d->enFutEstado = 1230;
            else
	            d->enFutEstado = 1231;	
            break;
        }
        case 1125:
        {
            d->enFutEstado=1126;
            break;
        }
        case 1126:
        {
            d->enFutEstado=1120;
            break;
        }
        case 1130: //DI ready!
        {
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
        }
        case 1131: //DI INCOMPLETE
        {
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
        }
        case 1230: //DI ready!
        {
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
        }
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