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

#ifndef _MASK4_ACTUALIZA_
#define _MASK4_ACTUALIZA_

//aspecto
static int actualizaForm(PARAM *p,DATA* d,int estado)
{
  //std::cout << "ACTUALIZAMOS FORMULARIO AL ESTADO: " << estado << std::endl;
  switch(estado)
    {
    case(-1): //llegamos
      break;			
    case(0): //estado normal
      //navegación
      pvSetEnabled(p,BUT1,1);
      pvSetEnabled(p,BUT2,1);      
      //cámaras deshabilitadas
      pvSetEnabled(p,FFCAMERA,0);
      pvSetEnabled(p,FFBAS,0);
      //
      break;
    case(1): //estado cámara seleccionada
      //cámaras deshabilitadas
      pvSetEnabled(p,FFCAMERA,1);
      pvSetEnabled(p,FFBAS,0);
      pvSetCurrentItem(p,COMBOBAS,0);
      //
      break;
    case(2): //estado báscula seleccionada
      //cámaras deshabilitadas
      pvSetEnabled(p,FFCAMERA,0);
      pvSetEnabled(p,FFBAS,1);
      pvSetCurrentItem(p,COMBOCAMERAS,0);
      //   
      break;
    default: //con cámara seleccionada
      break;		
    }

  return 0;
}

//acciones
static int actualizaEstado(PARAM *p, DATA *d)
{
  int ret = -1;
  char error[128];
  if(d->estadoActual != d->estadoFuturo)
    {
      switch(d->estadoFuturo)
	{
	case -1:
	  ret = 0;
	  break;
	case 0:
	  ret = 0;
	  break;
	case 1:
	  {

	  try
	    {
		d->camPos = std::stoi(d->selectedCam.substr(10,1));
	    }
	  catch(...)
	    {
	      d->camPos = 0;
	    }

	    if(d->camPos >0 && d->camPos <= 4)
	      d->camPos--;
	    else
	      d->camPos=0;
	    
	    pvSetText(p,EDITIP,cameras.at(d->camPos).ip.c_str());
	    d->editedCamIp=cameras.at(d->camPos).ip.c_str();
	    
	    char port[10];
	    sprintf(port,"%d",cameras.at(d->camPos).port);
	    pvSetText(p,EDITPORT,port);
	    d->editedCamPort=port;
	    
	    char timeout[10];
	    sprintf(timeout,"%d",cameras.at(d->camPos).timeout);
	    pvSetText(p,EDITTIMEOUT,timeout);
	    d->editedCamTimeout=timeout;
	    
	    ///relays
	    if((cameras.at(d->camPos).relayA == cameras.at(d->camPos).relayB) && (cameras.at(d->camPos).relayA != -1))
	      {
		cameras.at(d->camPos).relayB = -1;
		miIni->setCamRelayB(d->camPos+1,cameras.at(d->camPos).relayB);
	      }
	    switch(cameras.at(d->camPos).relayA)
	      {
	      case(1):
		d->chsenCamRelay = cameras.at(d->camPos).relayA;
		pvSetCurrentItem(p,COMBORELAY,0);
		break;
	      case(2):
		d->chsenCamRelay = cameras.at(d->camPos).relayA;
		pvSetCurrentItem(p,COMBORELAY,1);
		break;
	      case(3):
		d->chsenCamRelay = cameras.at(d->camPos).relayA;
		pvSetCurrentItem(p,COMBORELAY,2);
		break;
	      case(4):
		d->chsenCamRelay = cameras.at(d->camPos).relayA;
		pvSetCurrentItem(p,COMBORELAY,3);
		break;
	      default:
		d->chsenCamRelay = cameras.at(d->camPos).relayA = -1;
		pvSetCurrentItem(p,COMBORELAY,4);
		miIni->setCamRelayA(d->camPos+1,cameras.at(d->camPos).relayA);
		break;
	      }
	    switch(cameras.at(d->camPos).relayB)
	      {
	      case(1):
		d->chsenCamRelayB = cameras.at(d->camPos).relayB;
		pvSetCurrentItem(p,COMBORELAYB,0);
		break;
	      case(2):
		d->chsenCamRelayB = cameras.at(d->camPos).relayB;
		pvSetCurrentItem(p,COMBORELAYB,1);
		break;
	      case(3):
		d->chsenCamRelayB = cameras.at(d->camPos).relayB;
		pvSetCurrentItem(p,COMBORELAYB,2);
		break;
	      case(4):
		d->chsenCamRelayB = cameras.at(d->camPos).relayB;
		pvSetCurrentItem(p,COMBORELAYB,3);
		break;
	      default:
		d->chsenCamRelayB = cameras.at(d->camPos).relayB = -1;
		pvSetCurrentItem(p,COMBORELAYB,4);
		miIni->setCamRelayB(d->camPos+1,cameras.at(d->camPos).relayB);
		break;
	      }
	    ret = 0;
	  
	  break;
	  }
	case 2:
	  {

	  try
	    {
	      d->basPos = std::stoi(d->selectedBas.substr(10,1));
	    }
	  catch(...)
	    {
	      d->basPos = 0;
	    }

	   
	    if(d->basPos >0 && d->basPos <= 4)
	      d->basPos--;
	    else
	      d->basPos=0;

	    //cargamos los datos de la báscula
	    ///puerto
	    pvSetText(p,EDITTTY,basculas.at(d->basPos).port.c_str());
	    d->editedBasPort=basculas.at(d->basPos).port;
	    ///baudios
	    switch(basculas.at(d->basPos).bauds)
	      {
	      case(4800):
		d->chsenBasBauds = basculas.at(d->basPos).bauds;
		pvSetCurrentItem(p,COMBOBAUDS,0);
		break;
	      case(9600):
		d->chsenBasBauds = basculas.at(d->basPos).bauds;
		pvSetCurrentItem(p,COMBOBAUDS,1);
		break;
	      case(19200):
		d->chsenBasBauds = basculas.at(d->basPos).bauds;
		pvSetCurrentItem(p,COMBOBAUDS,2);
		break;
	      default:
		d->chsenBasBauds = basculas.at(d->basPos).bauds = 9600;	    
		pvSetCurrentItem(p,COMBOBAUDS,1);
		miIni->setBasBauds(d->basPos+1,basculas.at(d->basPos).bauds);
		break;
	      }
	    ///timeout
	    char editbox[32];
	    sprintf(editbox,"%d",basculas.at(d->basPos).timeout);
	    pvSetText(p,EDITBASTIMEOUT,editbox);
	    d->editedBasTimeout = basculas.at(d->basPos).timeout;
	    ///comando
	    pvSetText(p,EDITBASASK,basculas.at(d->basPos).ask.c_str());
	    d->editedBasAsk=basculas.at(d->basPos).ask;
	    ///paridad
	    switch(basculas.at(d->basPos).parity)
	      {
	      case(0):
		d->chsenBasParity = basculas.at(d->basPos).parity;
		pvSetCurrentItem(p,COMBOPARITY,0);
		break;
	      case(1):
		d->chsenBasParity = basculas.at(d->basPos).parity;
		pvSetCurrentItem(p,COMBOPARITY,1);
		break;
	      case(2):
		d->chsenBasParity = basculas.at(d->basPos).parity;
		pvSetCurrentItem(p,COMBOPARITY,2);
		break;
	      default:		
		d->chsenBasParity = basculas.at(d->basPos).parity = 0;
		pvSetCurrentItem(p,COMBOPARITY,0);
		miIni->setBasParity(d->basPos+1,basculas.at(d->basPos).parity);
		break;
	      }
	    ///bits de parada
	    switch(basculas.at(d->basPos).stopBits)
	      {
	      case(0):
		d->chsenBasStopBits = basculas.at(d->basPos).stopBits;
		pvSetCurrentItem(p,COMBOSTOP,0);
		break;
	      case(1):
		d->chsenBasStopBits = basculas.at(d->basPos).stopBits;
		pvSetCurrentItem(p,COMBOSTOP,1);
		break;
	      case(2):
		d->chsenBasStopBits = basculas.at(d->basPos).stopBits;
		pvSetCurrentItem(p,COMBOSTOP,2);
		break;
	      default:		
		d->chsenBasStopBits = basculas.at(d->basPos).stopBits = 0;
		pvSetCurrentItem(p,COMBOSTOP,0);
		miIni->setBasStopBits(d->basPos+1,basculas.at(d->basPos).stopBits);
		break;
	      }
	    ///Flow control
	    switch(basculas.at(d->basPos).ctrl)
	      {
	      case(0):
		d->chsenBasFlow = basculas.at(d->basPos).ctrl;
		pvSetCurrentItem(p,COMBOFLUJO,0);
		break;
	      case(1):
		d->chsenBasFlow = basculas.at(d->basPos).ctrl;
		pvSetCurrentItem(p,COMBOFLUJO,1);
		break;
	      case(2):
		d->chsenBasFlow = basculas.at(d->basPos).ctrl;
		pvSetCurrentItem(p,COMBOFLUJO,2);
		break;
	      default:		
		d->chsenBasFlow = basculas.at(d->basPos).ctrl = 0;
		pvSetCurrentItem(p,COMBOFLUJO,0);
		miIni->setBasCtrl(d->basPos+1,basculas.at(d->basPos).ctrl);
		break;
	      }
	    //
	    ret = 0;
	  
	  break;
	  }
	default:
	  ret = -1;
	  break;
	}
      d->estadoActual = d->estadoFuturo;
      actualizaForm(p,d,d->estadoActual);
    }

  return ret;
}


//condiciones de cambio
static int maquinaEstados(PARAM *p, DATA *d)
{
  int ret = 0;
  switch(d->estadoActual) 
    {
    case -1: //llegada a configuración
      d->estadoFuturo= 0;
      ret = 0;
      break;
    case 0: //reposo, nada seleccionado
      if(d->selectedCam.compare("ELIJA") && !d->selectedCam.empty() )
	{
	  std::cout << " que nos vamos al estado 1!" << std::endl;
	  pvSetText(p,LABCURRCAM,pvtr("1 y 2 entradas, 3 y 4 salidas"));
	  d->loadedCam = d->selectedCam;
	  d->estadoFuturo= 1;
	}
      if(d->selectedBas.compare("ELIJA") && !d->selectedBas.empty() )
	{
	  std::cout << " que nos vamos al estado 2!" << std::endl;
	  pvSetText(p,LABCURRBAS,pvtr("1 y 2 entradas, 3 y 4 salidas"));
	  d->loadedBas = d->selectedBas;
	  d->estadoFuturo= 2;
	}
      ret = 0;
      break;
    case 1: //info de cámara cargada
      if(d->selectedCam.compare(d->loadedCam))
	{
	  pvSetText(p,LABCURRCAM,pvtr("Elija una"));
	  d->estadoFuturo= 0;
	}
      if(d->selectedBas.compare(d->loadedBas))
	{
	  pvSetText(p,LABCURRCAM,pvtr("Elija una"));
	  d->selectedCam.clear();
	  d->loadedCam.clear();
	  d->estadoFuturo= 0;
	}
      ret = 0;
      break;
    case 2: //info de báscula cargada
      if(d->selectedBas.compare(d->loadedBas))
	{
	  pvSetText(p,LABCURRBAS,pvtr("Elija una"));
	  d->estadoFuturo= 0;
	}
      if(d->selectedCam.compare(d->loadedCam))
	{
	  pvSetText(p,LABCURRBAS,pvtr("Elija una"));
	  d->selectedBas.clear();
	  d->loadedBas.clear();
	  d->estadoFuturo= 0;
	}
      ret = 0;
      break; 
    default:
      ret = -1;
      break;
    }
  return ret;
}

#endif
