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

#ifndef _MASK5_TOOLS_
#define _MASK5_TOOLS_

enum{
  CTRL_NONE = 0,
  CTRL_PROCEDER,
  CTRL_PROCEDER_CANCELAR,
  CTRL_PROCEDER_CANCELAR_RETROCEDER,
  CTRL_PROCEDER_RETROCEDER,
  CTRL_CANCELAR_RETROCEDER,
  CTRL_CANCELAR,
  CTRL_RETROCEDER
};

enum{
  WEIGTH_DISABLED = 0,
  WEIGTH_ANALYSIS
};

static int isStrInProdsVector(std::vector < std::string> lista,std::vector < std::string> listaCodes, std::string cadena)
{
  int itIs=-1;
  int i = 0;
  std::vector<std::string>::iterator iter;
  std::vector<std::string>::iterator iterCodes;
  iterCodes = listaCodes.begin();
  for(iter = lista.begin(); iter != lista.end() && iterCodes != listaCodes.end(); ++iter)
    {
      std::string producto = *iter + " " + *iterCodes;
      if(producto.compare(cadena) == 0)
	itIs=i;
      i++;
      ++iterCodes;
    }
  
  return itIs;
}
//
static int populateProdsCombo(PARAM *p,int id, std::vector <std::vector < std::string>> lista, bool otros)
{
  pvClear(p,id);
  pvSetText(p,id,"ELIJA");
  std::vector < std::vector < std::string>>::iterator row;
  std::vector < std::string>::iterator col;
  std::string text;
  if(otros)
    pvSetText(p,id,"MOSTRAR TODOS");
  for(row = lista.begin(); row != lista.end(); ++row)
    {
      text.clear();
      for(col = row->begin(); col != row->end(); ++col)
	{		  
	  text += *col;
	  text+=" ";
	}
      pvSetText(p,id,text.c_str());
    }

  pvToolTip(p,id,"ELIJA");
  return 0;
}

static int populateCombo(PARAM *p,int id, std::vector <std::vector < std::string>> lista)
{
  pvClear(p,id);
  pvSetText(p,id,"ELIJA");
  for(int i = 0; i < lista.size();i++)
    for(int j=0;j< lista[i].size();j++)
      if(!lista[i][j].empty())
	pvSetText(p,id,lista[i][j].c_str());
  //TODO:deberíamos conservar una opción 0 de ningún cliente seleccionado?
  pvToolTip(p,id,"ELIJA");
  return 0;
}
//
static int populateCombo(PARAM *p,int id, std::vector < std::string> lista)
{
  pvClear(p,id);
  pvSetText(p,id,"ELIJA");
  for(int i = 0; i < lista.size();i++)
    if(!lista[i].empty())
      pvSetText(p,id,lista[i].c_str());
  pvToolTip(p,id,"ELIJA");
  return 0;
}
static int setComboBoxPos(PARAM *p,int id,std::vector< std::string> allValues, std::string value)
{
  int pos = 0;
  int done = -1;
  std::vector <std::string>::iterator iter;
  for(iter = allValues.begin(); iter != allValues.end(); ++iter)
    {
      pos++;
      if(!iter->compare(value))
	{
	  pvSetCurrentItem(p,id,pos);
	  done = pos;
	}
	
    }
  return done;
}
static int setComboBoxPosByField(PARAM *p,int id,std::vector <std::vector < std::string>> allValues, std::string value, int field)
{
  int pos = 0;
  int done = -1;
  if(field <0)
    field =0;
  if(field>=allValues.size())
    field = allValues.size()-1;
  
  for(int i=0; i != allValues.size(); ++i)
    {
      pos++;
      if(!allValues[i][field].compare(value))
	{
	  pvSetCurrentItem(p,id,pos);
	  done = pos;
	}
    }
  return done;
}

static void saveOperatorComment(PARAM *p,DATA* d,baseForm *& myForm,const char* text, int input)
{
  std::string newComment = text;
  if(input)
    myForm->setInputComment(newComment);
  else
    myForm->setOutputComment(newComment);
  return;
}

enum {
  FRAME_DISABLED = 0,
  FRAME_SELECTED,
  FRAME_NORMAL,
  FRAME_WORKING
};

static int setFrame(PARAM *p,DATA* d, int id, int state)
{
  switch(state)
    {
    case(FRAME_DISABLED):
      pvSetEnabled(p,id,0);
      pvSetStyle(p,id,-1,1,1,-1);
      break;
    case(FRAME_SELECTED):
      pvSetEnabled(p,id,1);
      pvSetStyle(p,id,-1,1,5,-1);
      break;
    case(FRAME_NORMAL):
      pvSetEnabled(p,id,1);
      pvSetStyle(p,id,-1,1,1,-1);
      break;
    case(FRAME_WORKING):
      pvSetEnabled(p,id,1);
      pvSetStyle(p,id,-1,1,1,-1);
      break;
    default:
      break;
    }
  return 0;
}


//NO GENERIC
static int popteOrders(PARAM *p,DATA* d,int id, baseForm *& formulario)
{
  int ret = -1;
  std::cout << "inside popteOrders" << std::endl;
  std::vector <std::string >::iterator orders;
  std::vector<std::string> ordersTable = formulario->retOrdersTable();
  std::string icon = "image/small_truck_BW_icon_T.png";
  
  pvClear(p,id);
  for(orders = ordersTable.begin(); orders != ordersTable.end(); ++orders)
    {
      std::cout << "estamos insertando órdenes!!" << std::endl;
      if(orders->length() >= MAX_EVENT_LENGTH/16)
	*orders = orders->substr(0,MAX_EVENT_LENGTH/16-2);
      pvInsertItem(p,id,-1,icon.c_str(),orders->c_str(),1);
      ret = 0;
    }

  return ret;
}

static int popteTransito(PARAM *p,DATA* d,int id, baseForm *& formulario)
{
    //std::cout << "inside popteTransito" << std::endl;
    std::string sql;
    selAllTransitDep(sql);
    localDatabase.query(p, sql.c_str());
    std::vector<std::vector<std::string>> ourData = localDatabase.retData2();
    if(are2dMatrixDifferents(ourData,formulario->retTransit()))
    {
        formulario->setTransit(ourData);
    }
    std::vector <std::vector <std::string>>::iterator trucks;
    std::vector <std::string> ::iterator fields;
    std::string item;
    std::string tmpItem = "\n(";
    int column = 1;
    pvClear(p,id);
    //ICON, PLATE, FECHA_HORA
    std::string icon;
    std::string plate;
    std::string date;
    int weight;
    for(trucks = ourData.begin(); trucks != ourData.end(); ++trucks)
    {
        column = 1;
        item.clear();
        plate.clear();
        date.clear();
        icon = "image/small_truck_BW_icon_T.png";
        for(fields = trucks->begin(); fields != trucks->end(); ++fields)
	    {
	        if(column == 6) //plate
	        {
	            plate = *fields;
	        }
	        else if(column == 3) //costumer
	        {
	            date = *fields;
	        }	  
	        else if(column == 9)
	        {
	            std::cout << "WEIGHT TO INT: " << *fields << std::endl;
	            try
		        {
		            weight = std::stoi(*fields);
		        }
	            catch(...)
		        {
		            weight = 0;
		        }
	            if(weight>0)
		            icon = "image/small_truck_BW_icon_G.png";
	        }
	        column++;
	    }
        item = plate;
        item += "\n(";
        item += date;
        item += ")";
        //std::cout << item << std::endl;
        if(item.length() >= MAX_EVENT_LENGTH/16)
	        item = item.substr(0,MAX_EVENT_LENGTH/16-1);
        pvInsertItem(p,id,-1,icon.c_str(),item.c_str(),1);
        std::cout << "exiting!!" << std::endl;
    }
    return 0;
}

static int resetForm(PARAM *p,DATA* d, baseForm *& myForm)
{
    int formType = 0;
    int movType = 1;
    if(myForm->getState() >= 1000)
    {
        formType=1;
        movType =  myForm->retDepMovType();
    }
    else
        movType =  myForm->retArrMovType();
    //triggers
    d->retroceder = 0;
    d->cancelar = 0;
    d->plateTaking = 0;
    d->processTag = 0;
    system("rm camera/capture.jpg");
    //concreto para entrada
    if(formType==0)
    {
        pvSetImage(p,IMCAM,myResources.RES_IMG_IMAGE.c_str());      //Camera
        d->productoCodeActual.clear();
        pvSetText(p,EDITCAM,"");
        pvSetText(p,EDITCLIENT,"");
        pvSetText(p,EDITPRODUCT,"");
        pvSetText(p,EDITDIPROV,"");
        pvSetText(p,EDITPESOENT,"");
        pvClear(p,EDITCOMMENTENT);
        pvSetChecked(p,CHKFORZARPROD,0);
    }
    else
    {
        pvSetImage(p,IMCAM_E2,myResources.RES_IMG_IMAGE.c_str());      //Camera
        pvSetText(p,EDITCAM_E2,"");
        pvSetText(p,EDITDIDEF,"");
        pvSetText(p,EDITPESOSAL,"");
        pvSetText(p,EDITCODETRANSP,"");
        pvSetText(p,EDITNAMETRANSP,"");      
        pvClear(p,EDITCOMMENTSAL);
        pvSetChecked(p,CHKTRANSITO,1);
        if(myForm->retDepMovType() == DEF_MOV_TRANSFER)
	        myForm->rmDepDiFolder();
    }
    //
    myForm->resetForm(formType);
    return 0;
}


//refresco y escritura de comentarios operador
static void refreshOperatorComment(PARAM *p,DATA* d,baseForm *& myForm,int editBox)
{
  std::string newComment;
  if(editBox == EDITCOMMENTENT) //entrada descarga
    newComment = myForm->getInputComment();
  else if(editBox = EDITCOMMENTSAL) //salida de descarga
    newComment = myForm->getOutputComment();
  pvClear(p,editBox);
  pvSetText(p,editBox,newComment.c_str());
  return;
}

// 
static int refreshLerPerms(PARAM *p, DATA* d, int enabled,baseForm *& myForm)
{
    if(enabled)
    {
        //PERMISO PLANTA
        if(myForm->isArrProdGralPermit())                       
            pvSetImage(p,ICONPERM,"image/green.png");
        else
            pvSetImage(p,ICONPERM,"image/red.png");
        //PERMISO FECHA CONTRATO	
        if(myForm->isArrProdDatePermit())                       
            pvSetImage(p,ICONFECHCONTR,"image/green.png");
        else
            pvSetImage(p,ICONFECHCONTR,"image/red.png");
        //PERMISO FECHA NPT	
        if(myForm->isArrProdNptPermit())                       
            pvSetImage(p,ICONFECHNPRT,"image/green.png");
        else
            pvSetImage(p,ICONFECHNPRT,"image/red.png");
        //PERMISO CARACTERIZACIÓN BÁSICA	
        if(myForm->isArrProdCbPermit())                       
            pvSetImage(p,ICONCB,"image/green.png");
        else
            pvSetImage(p,ICONCB,"image/red.png");
        //PERMISO CARACTERIZACIÓN DE PELIGRO	
        if(myForm->isArrProdCpPermit())                      
            pvSetImage(p,ICONCP,"image/green.png");
        else
            pvSetImage(p,ICONCP,"image/red.png");
        //PERMISO DCP
        if(myForm->isArrProdDcpPermit())                       
            pvSetImage(p,ICONDCP,"image/green.png");
        else
            pvSetImage(p,ICONDCP,"image/red.png");
    }
    else
    {
        pvSetImage(p,ICONPERM,"image/grey.png");			  
        pvSetImage(p,ICONFECHCONTR,"image/grey.png");			  
        pvSetImage(p,ICONFECHNPRT,"image/grey.png");			  
        pvSetImage(p,ICONCB,"image/grey.png");			  
        pvSetImage(p,ICONCP,"image/grey.png");
        pvSetImage(p,ICONCP,"image/grey.png");
    }
    return 0;
}


static void toolsSetControl(PARAM *p, DATA *d,int setStatus)
{
  switch(setStatus)
    {
    case(CTRL_NONE):
      setFrame(p,d,FRAMEBUTTONS,FRAME_DISABLED);
      pvSetEnabled(p,BUTPROCEDER_E1,0);    
      pvSetEnabled(p,BUTCANCELAR_E1,0);
      pvSetEnabled(p,BUTRETROCEDER_E1,0);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,-1,-1,-1);    
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,-1,-1,-1); 
      break;
    case(CTRL_PROCEDER):
      setFrame(p,d,FRAMEBUTTONS,FRAME_SELECTED);
      pvSetEnabled(p,BUTPROCEDER_E1,1);    
      pvSetEnabled(p,BUTCANCELAR_E1,0);
      pvSetEnabled(p,BUTRETROCEDER_E1,0);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,0,125,0);
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,-1,-1,-1);
      break;
    case(CTRL_PROCEDER_CANCELAR):
      setFrame(p,d,FRAMEBUTTONS,FRAME_SELECTED);
      pvSetEnabled(p,BUTPROCEDER_E1,1);    
      pvSetEnabled(p,BUTCANCELAR_E1,1);
      pvSetEnabled(p,BUTRETROCEDER_E1,0);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,0,125,0);    
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,125,0,0); 
      break;
    case(CTRL_PROCEDER_CANCELAR_RETROCEDER):
      setFrame(p,d,FRAMEBUTTONS,FRAME_SELECTED);
      pvSetEnabled(p,BUTPROCEDER_E1,1);    
      pvSetEnabled(p,BUTCANCELAR_E1,1);
      pvSetEnabled(p,BUTRETROCEDER_E1,1);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,0,125,0);    
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,125,0,0);   
      break;
    case(CTRL_PROCEDER_RETROCEDER):
      setFrame(p,d,FRAMEBUTTONS,FRAME_SELECTED);
      pvSetEnabled(p,BUTPROCEDER_E1,1);    
      pvSetEnabled(p,BUTCANCELAR_E1,0);
      pvSetEnabled(p,BUTRETROCEDER_E1,1);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,0,125,0);
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,-1,-1,-1);
      break;
    case(CTRL_CANCELAR_RETROCEDER):
      setFrame(p,d,FRAMEBUTTONS,FRAME_SELECTED);
      pvSetEnabled(p,BUTPROCEDER_E1,0);    
      pvSetEnabled(p,BUTCANCELAR_E1,1);
      pvSetEnabled(p,BUTRETROCEDER_E1,1);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,-1,-1,-1);   
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,125,0,0);   
      break;
    case(CTRL_CANCELAR):
      setFrame(p,d,FRAMEBUTTONS,FRAME_SELECTED);
      pvSetEnabled(p,BUTPROCEDER_E1,0);    
      pvSetEnabled(p,BUTCANCELAR_E1,1);
      pvSetEnabled(p,BUTRETROCEDER_E1,0);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,-1,-1,-1); 
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,125,0,0); 
      break;
    case(CTRL_RETROCEDER):
      setFrame(p,d,FRAMEBUTTONS,FRAME_SELECTED);
      pvSetEnabled(p,BUTPROCEDER_E1,0);    
      pvSetEnabled(p,BUTCANCELAR_E1,0);
      pvSetEnabled(p,BUTRETROCEDER_E1,1);
      pvSetPaletteForegroundColor(p,BUTPROCEDER_E1,-1,-1,-1);
      pvSetPaletteForegroundColor(p,BUTCANCELAR_E1,-1,-1,-1);
      break;
    default:
      std::cout << "ERROR: state not defined in toolsSetControl, value:" << setStatus << std::endl;
      break;
    }
  return;
}

static void toolsSetSpecials(PARAM *p, DATA* d, int setStatus)
{
  if(setStatus) //for now only on/off, more states could be easly aggregated
    {
      pvSetEnabled(p,BUTSINCRONIZA,1);
      d->f4Sincro = 1;
    }
  else
    {
      pvSetEnabled(p,BUTSINCRONIZA,0);
      d->f4Sincro = 0;
    }
  return;
}

static void toolsSetNAV(PARAM *p, DATA* d, int setStatus)
{
  if(setStatus) //for now only on/off, more states could be easly aggregated
    {
	pvSetEnabled(p,BUT1,1);
	pvSetEnabled(p,BUT3,1);
	d->f1Unloads = 1;
	d->f3Config = 1;
    }
  else
    {
	pvSetEnabled(p,BUT1,0);
	pvSetEnabled(p,BUT3,0);
	d->f1Unloads = 0;
	d->f3Config = 0;
    }
  return;
}

static void toolsSetArrDep(PARAM *p, DATA* d, int setStatus)
{
  if(setStatus) //for now only on/off, more states could be easly aggregated
    {
      pvSetEnabled(p,CHKENTRADA,1);
      pvSetEnabled(p,CHKSALIDA,1);
      d->f5Toggle = 1;
    }
  else
    {
      pvSetEnabled(p,CHKENTRADA,0);
      pvSetEnabled(p,CHKSALIDA,0);
      d->f5Toggle = 0;
    }
  return;

}

/// toolsDeactivateGUI function for disabling GUI, 
//0 for arrive
//1 for depart
//2 for everything
///
/// toolsDeactivateGUI function for disabling GUI, 
//0 for arrive
//1 for depart
//2 for everything
///
static void toolsDeactivateGUI(PARAM *p, DATA* d, int entrada_salida_all, baseForm* myForm)
{
  if(entrada_salida_all == 0)
    {
      //Frame matricula
      setFrame(p,d,FRAMECAM_E1,FRAME_DISABLED);
      //
      //frame orders
      setFrame(p,d,FRAMEORDERS,FRAME_DISABLED);
      //
      //frame Movement briefing
      setFrame(p,d,FRAMEMOV,FRAME_DISABLED);
      //
      //frame DI PROVISIONAL
      setFrame(p,d,FDIPROV,FRAME_DISABLED);			
      //frame PESO
      setFrame(p,d,FRAMEPESOENT,FRAME_DISABLED);
      //frame permiso de entrada
      pvSetEnabled(p,FRAMEPERMISOENTRADA,1);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //comentario operador
      setFrame(p,d,FRAMECOMMENTENT,FRAME_DISABLED);

    }
  else if (entrada_salida_all == 1)
    {
      //Frame tipo salida
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_DISABLED);
      //Frame matricula
      setFrame(p,d,FRAMECAM_E2,FRAME_DISABLED);
      ////tabla de tránsito visible?
      setFrame(p,d,FRAMETRANSITO,FRAME_NORMAL);   
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_DISABLED);
      pvSetEnabled(p,BUTEDITDIDEF,0);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_DISABLED);
      //setPesoSal(p, d,WEIGTH_DISABLED,myForm);
      //botones firma y retener
      setFrame(p,d,BUTFIRMAR,FRAME_DISABLED);
      setFrame(p,d,BUTRETENER,FRAME_DISABLED);      
      //comentario operador
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_DISABLED);
    }
  else
    {
      //Frame matricula
      setFrame(p,d,FRAMECAM_E1,FRAME_DISABLED);
      //
      //frame orders
      setFrame(p,d,FRAMEORDERS,FRAME_DISABLED);
      //
      //frame Movement briefing
      setFrame(p,d,FRAMEMOV,FRAME_DISABLED);
      //
      //frame DI PROVISIONAL
      setFrame(p,d,FDIPROV,FRAME_DISABLED);			
      //frame PESO
      setFrame(p,d,FRAMEPESOENT,FRAME_DISABLED);
      //frame permiso de entrada
      pvSetEnabled(p,FRAMEPERMISOENTRADA,1);
      pvSetImage(p,IMICONPERMISOENTRADA,"image/red.png");
      //comentario operador
      setFrame(p,d,FRAMECOMMENTENT,FRAME_DISABLED);
      //Frame tipo salida
      setFrame(p,d,FRAMETIPOSALIDA,FRAME_DISABLED);
      //Frame matricula
      setFrame(p,d,FRAMECAM_E2,FRAME_DISABLED);
      ////tabla de tránsito visible?
      setFrame(p,d,FRAMETRANSITO,FRAME_DISABLED);   
      //frame DI DEFINITIVO
      setFrame(p,d,FDIDEF,FRAME_DISABLED);
      pvSetEnabled(p,BUTEDITDIDEF,0);
      //frame TARA
      setFrame(p,d,FRAMEPESOSAL,FRAME_DISABLED);
      //setPesoSal(p, d,WEIGTH_DISABLED,myForm);
      //botones firma y retener
      setFrame(p,d,BUTFIRMAR,FRAME_DISABLED);
      setFrame(p,d,BUTRETENER,FRAME_DISABLED);      
      //comentario operador
      setFrame(p,d,FRAMECOMMENTSAL,FRAME_DISABLED);
    }
  return;
}
static void setPesoSal(PARAM *p, DATA* d, int status, baseForm *& myForm)
{
  //std::cout << "debug: inside Mask5 setPesoSal:" << std::endl;
  std::string myPeso = std::to_string(formSalida->retDepScaleOut());
  pvSetText(p,EDITPESOSAL,myPeso.c_str());
  
  if(status == WEIGTH_ANALYSIS)
    {
      std::string inTheoryWeight = "(" + std::to_string(myForm->retDepScaleExpected()) + ")";
      if(myForm->isDepPesoOk() == 0) //it' s above
	{
	  pvSetImage(p,ICONPERMISOPESOSAL,"image/red.png");
	  pvSetImage(p,ICONSATUSPESOSAL,"image/up_arrow.png");
	  pvSetText(p,LABDEFAULTPESOSAL,inTheoryWeight.c_str());
	}
      else if(myForm->isDepPesoOk()< 0) //it's under limit
	{
	  pvSetImage(p,ICONPERMISOPESOSAL,"image/red.png");
	  pvSetImage(p,ICONSATUSPESOSAL,"image/down_arrow.png");
	  pvSetText(p,LABDEFAULTPESOSAL,inTheoryWeight.c_str());
	}
      else //it's ok
	{
	  std::cout << "weigth ok!" << std::endl;
	  pvSetImage(p,ICONPERMISOPESOSAL,"image/green.png");
	  pvSetImage(p,ICONSATUSPESOSAL,"image/void.png");
	  pvSetText(p,LABDEFAULTPESOSAL,inTheoryWeight.c_str());	  
	}
    }
  else //disabled
    {	  
      pvSetImage(p,ICONPERMISOPESOSAL,"image/grey.png");
      pvSetImage(p,ICONSATUSPESOSAL,"image/void.png");
      pvSetText(p,LABDEFAULTPESOSAL,"()");
    }
}

/*! function for refreshing semaphores icons*/
static void refreshSemaphores(PARAM *p,DATA *d)
{
  if(cameras.at(2).statusB) //green	
    pvSetImage(p,IMICONSEMENTRADA,myResources.RES_IMG_GREEN.c_str());
  else if(cameras.at(0).statusA) //red
    pvSetImage(p,IMICONSEMENTRADA,myResources.RES_IMG_RED.c_str());
  else //grey
    pvSetImage(p,IMICONSEMENTRADA,myResources.RES_IMG_GREY.c_str());	

  if(cameras.at(3).statusB) //green	
    pvSetImage(p,IMICONSEMSALIDA,myResources.RES_IMG_GREEN.c_str());
  else if(cameras.at(1).statusA) //red
    pvSetImage(p,IMICONSEMSALIDA,myResources.RES_IMG_RED.c_str());
  else //grey
    pvSetImage(p,IMICONSEMSALIDA,myResources.RES_IMG_GREY.c_str());
}

static void globalSyncronization(PARAM *p, DATA* d, baseForm *& myForm)
{
  //block gui
  pvSetMovie(p,LOADINGFORM,1,myResources.RES_LOADING.c_str());
  pvMovieControl(p,LOADINGFORM,-2); // restart
  pvShow(p,LOADINGFORM);       
  /**CONTROL PANEL**/
  toolsSetControl(p,d,CTRL_NONE);
  /**desactive all**/
  toolsDeactivateGUI(p,d,2,myForm);
  /**COMMON**/
  toolsSetNAV(p,d,0);
  toolsSetArrDep(p,d,0);
  /**special**/
  pvSetEnabled(p,BUTSINCRONIZA,0);
  pvSetEnabled(p,TABLATRANSITO,0);
  //syncronize
  console.push_back("(INFO) sincronizando con la base de datos central...");

  int DatabaseData_chkd;
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
      //syncReconnectIfNeeded();
      reconnectSSH(NULL);
      int wasError=0;
      int error = syncCostumers(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de clientes!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncProducts(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de productos!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncCostumersProducts(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de clientes-productos!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncCars(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de vehiculos!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncOrders(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de ordenes!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncDrivers(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de transportistas!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncMovements(p,myStation->getCode());
      if(error)
	console.push_back("¡Error al sincronizar la tabla de movimientos!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncTransitDep(p,myStation->getCode());
      if(error)
	console.push_back("¡Error al sincronizar la tabla de transito de cargas de material!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncStations(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de centros!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncTransfers(p,myStation->getCode());
      if(error)
	console.push_back("¡Error al sincronizar la tabla de centros!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncBilling(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de entidades de facturación!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;
      error = syncStaff(p);
      if(error)
	console.push_back("¡Error al sincronizar la tabla de basculistas!");
      if(error == -1)
	reconnectSSH(NULL);
      wasError = wasError + error;   
	  	      
      if(wasError)
	console.push_back("*ERROR* ¡Hubo errores al conectarse y/o procesar tablas!");
      else
	console.push_back("(INFO) ¡Sincronización completada!");
    }
  else
    {
      log_message("(SINCRO) fallo en ping al servidor remoto", 2);   
      console.push_back("*ERROR* ¡No podemos conectar con la base de datos central!");
      reconnectSSH(NULL);
    }
  //recover gui
  /**special**/
  pvSetEnabled(p,BUTSINCRONIZA,1);
  pvSetEnabled(p,TABLATRANSITO,1);
  pvHide(p,LOADINGFORM);
  /**/
  return;
}

/*
static int populateTransito(PARAM *p, DATA* d, formulario *& myForm)
{
  std::string sql = "select * from TRANSITO";
  localDatabase.query(p,sql.c_str());
  myForm->allTransitoInfo.clear();
  myForm->allTransitoInfo = localDatabase.retData2();
  populateListView(p,TABLATRANSITO,myForm->allTransitoInfo);
  d->camionElegido = -1;	    
  pvClear(p,EDITDIDEF);
  pvClear(p,EDITPESOTARA); 
  return 0;
}

*/
//////////
//////////
static int consoleRefresh(PARAM *p, DATA * d)
{
    int ret = -1;
    //console
    std::vector <std::string>::iterator iter;  
    if(d->localConsole.size() != console.size())
    {
        if(console.size()>6)
	        console.erase(console.begin(), console.end()-6);
        d->localConsole = console;
        pvClear(p,OUTPUT);
        for(iter = console.begin(); iter != console.end() ; ++iter)
	    {
	        pvSetText(p,OUTPUT,iter->c_str());
	        ret = 0;
	    }
    }
    return ret;
}
#endif
