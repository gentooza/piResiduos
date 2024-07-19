/*
This file is part of PiResiduos.

Copyright 2017-2019, Pro Integra SL.
Copyright 2019-2022 Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023-2024 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

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

#ifndef _MASK4_STATENEXT_
#define _

//condiciones de cambio
static int stateNext(PARAM *p, DATA *d)
{
    int ret = -1;
    switch(formEntrada->getState())
    {
        case -100:
        {
            // commons
            popteTransito(p,d,TABLATRANSITO, formEntrada);
            // checkbox de entrada
            if(d->enFutEstado >=1000) //finalizando entrada ET
            {
                d->entrarDescargar=0;
                pvSetChecked(p,CHKSALIDA,1);
                pvSetChecked(p,CHKENTRADA,0);
                d->camionElegido = -1;
                if(d->enFutEstado >= 1020)
                {
                    //Saving destination where files are stored
                    std::string di = formEntrada->createDINumber(localDatabase, 0);
                    pvSetText(p, EDITDIDEF, di.c_str());
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
        {
              //LLegamos nuevos!
              d->entrarDescargar=1;
              pvSetChecked(p,CHKSALIDA,0);
              pvSetChecked(p,CHKENTRADA,1);
              d->enFutEstado = -1;
              d->proceder=0;
              ret = 0;
              break;
        }
        case -1: //inicialización
        {
              //LLegamos nuevos!
              d->enFutEstado = 0;
              d->proceder=0;
              ret = 0;
              break;
        }
        case 0:
        {
            //auto-syncronization
            if(syncro_needed(&my_syncro_data))
            {
                globalSyncronization(p,d,formEntrada);
                stateGUI(p,d, formEntrada->getState());
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
            break;
        }
        case 5: //carga matricula cámara 1
        {
            d->enFutEstado = 6;
            ret = 0;
            break;
        }
        case 6:
        {
            if(d->processTag != 0) //fin del proceso de toma de matrículas
            {
                d->plateTaking = 0;
                d->processTag = 0;
                d->enFutEstado = 0;
            }
            ret = 0;
            break;
        }
        case 10://elección cliente
        {
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
        }
        case 20: //product selection related to client
        {
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
            }
            else if(d->cancelar) //cancel form
            {
                resetForm(p,d,formEntrada);
                d->enFutEstado = 0;
            }
            break;
        }
        case 21: //waiting for taking weight, chosen product by normal path
        {
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
        }
        case 22: //peso ok
        {
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
        }
        case 25: //transición pesaje báscula 1
        {
            d->enFutEstado = 26;
            break;
        }
        case 26: //pesaje báscula puesto 1
        {
            d->enFutEstado = 21;
            break;
        }
        case 30: //elegimos entre todos los productos
        {
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
        }
        case 31: //hemos elegido un producto y mostramos sus permisos
        {
            //si está autorizado a estado 32
            if(formEntrada->isArrProdPermit())
                d->enFutEstado=32;
            else //si no lo está a estado 33
                d->enFutEstado=33;
            break;
        }
        case 32: //producto permitido
        {
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
        }
        case 33: //producto no permitido, hay que autorizarlo!
        {
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
        }
        case 35:
        {
            d->enFutEstado=36;
            break;
        }
        case 36:
        {
            d->enFutEstado=32;
            break;
        }
        case 40: //peso ok
        {
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
                d->enFutEstado = 98;
                d->proceder = 0;
            }
            break;
        }
        case 98: //estado de animación
        {
            d->enFutEstado = 99;
            break;
        }
    case 99: //descarga realizada correctamente, vamos a transición
      resetForm(p,d,formEntrada);
      d->enFutEstado = 0;
      cameraSemaphore(1,1,globalConfiguration.traffic_lights_enabled);
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
        {
            if(formEntrada->isArrPesoOk()) //si damos por válido según criterios el peso de entrada
                d->enFutEstado = 140;
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
        }
        case 133: //product not allowed, authorize?
        {
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
        }
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
        {
            //auto-syncronization
            if(syncro_needed(&my_syncro_data))
            {
                globalSyncronization(p,d,formEntrada);
                stateGUI(p,d, formEntrada->getState());
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
        }
        case 1010: //carga matricula cámara 1
        {
            d->enFutEstado = 1011;
            break;
        }
        case 1011:
        {
            if(d->processTag != 0) //fin del proceso de toma de matrículas
            {
                d->plateTaking = 0;
                d->processTag = 0;
                d->enFutEstado = 1000;
            }
            ret = 0;
            break;
        }
        case 1020: //camión elegido
        {
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
        }
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
        {
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
        }
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
              pvSetText(p,EDITDIDEF,"");
              pvSetText(p,EDITPESOTARA,"");
              pvSetText(p,EDITCAM_E2,"");
              resetForm(p,d,formEntrada);
              d->enFutEstado = 1000;
        cameraSemaphore(2,1,globalConfiguration.traffic_lights_enabled);
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
