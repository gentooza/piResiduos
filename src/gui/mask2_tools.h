/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
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

#ifndef _MASK4_TOOLS_
#define _MASK4_TOOLS_

static std::vector<std::string> retPrinters()
{
    http_t* http = NULL;
    int num_dests,status;
    cups_dest_t *dests;
    std::vector<std::string> printerList;
    
    http = httpConnectEncrypt(cupsServer(), ippPort(),
                                        cupsEncryption());
    num_dests = cupsGetDests(&dests);

    for(int i = 0; i< num_dests; i++)
    {
        printerList.push_back(dests[i].name);
    }
    return printerList;
}

/*! function for refreshing semaphores icons*/
static void refreshSemaphores(PARAM *p,DATA *d)
{
    if(d->camPos >= 0 && d->camPos < 4)
    {
        if(cameras.at(d->camPos).statusB) //green	
            pvSetImage(p,IMSEMAPHORE,myResources.RES_IMG_GREEN.c_str());
        else if(cameras.at(d->camPos).statusA) //red
            pvSetImage(p,IMSEMAPHORE,myResources.RES_IMG_RED.c_str());
        else //grey
            pvSetImage(p,IMSEMAPHORE,myResources.RES_IMG_GREY.c_str());	
    }
    return;
}
  
static int populateCombo(PARAM *p,int id, std::vector <std::vector < std::string>> lista)
{
    pvClear(p,id);
    pvSetText(p,id,"ELIJA");
    for(int i = 0; i < lista.size();i++)
    {
        for(int j=0;j< lista[i].size();j++)
        {
            if(!lista[i][j].empty())
                pvSetText(p,id,lista[i][j].c_str());
        }
    }
    //TODO: option 0 no costumer chosen?
    pvToolTip(p,id,"ELIJA");
    return 0;
}
//
static int populateCombo(PARAM *p,int id, std::vector < std::string> lista, bool elija)
{
    std::vector<std::string>::iterator iter;
    pvClear(p,id);
    if(elija)
        pvSetText(p,id,"ELIJA");
    for(iter = lista.begin(); iter != lista.end(); iter++)
    {
        if(!iter->empty())
            pvSetText(p,id,iter->c_str());
    }
    pvToolTip(p,id,"ELIJA");
    return 0;
}

static void popteComboStations(PARAM *p,int id, std::vector<station> lista, bool elija)
{
    std::vector<station>::iterator iter;
    pvClear(p,id);
    if(elija)
        pvSetText(p,id,"ELIJA");
    for(iter = lista.begin(); iter != lista.end(); iter++)
    {
        pvSetText(p,id,std::to_string(iter->getCode()).c_str());
    }
    pvToolTip(p,id,"ELIJA");
    return;
}

static void popteComboCostumers(PARAM *p,int id, std::vector<costumer> lista, bool elija)
{
    std::vector<costumer>::iterator iter;
    std::string name;
    pvClear(p,id);
    if(elija)
        pvSetText(p,id,"ELIJA");

    for(iter = lista.begin(); iter != lista.end(); iter++)
    {
        name.clear();
        name = iter->getName();
        name += " ";
        name += std::to_string(iter->getCode());
        pvSetText(p,id,name.c_str());
    }
    pvToolTip(p,id,"ELIJA");
    return;
}

static int  populateMailRecipients(PARAM *p,int id, std::vector<std::string> mailRecipients, const char* separator)
{
    std::vector <std::string>::iterator iter;
    std::string text;
    for(iter = mailRecipients.begin(); iter != mailRecipients.end(); ++iter)
    {
        text += *iter;
        text += separator;
    }
    pvSetText(p,id,text.c_str());
    return 0;
}

static void toolsSetNAV(PARAM *p, DATA* d, int setStatus)
{
    if(setStatus) //for now only on/off, more states could be easly aggregated
    {
        pvSetEnabled(p,BUT1,1);
        pvSetEnabled(p,BUT2,1);
        d->f1Unloads = 1;
        d->f2Loads = 1;
    }
    else
    {
        pvSetEnabled(p,BUT1,0);
        pvSetEnabled(p,BUT2,0);
        d->f1Unloads = 0;
        d->f2Loads = 0;
    }
    return;
}

//Frame UI
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
        {
            pvSetEnabled(p,id,0);
            pvSetStyle(p,id,-1,1,1,-1);
            break;
        }
        case(FRAME_SELECTED):
        {
            pvSetEnabled(p,id,1);
            pvSetStyle(p,id,-1,1,5,-1);
            break;
        }
        case(FRAME_NORMAL):
        {
            pvSetEnabled(p,id,1);
            pvSetStyle(p,id,-1,1,1,-1);
            break;
        }
        case(FRAME_WORKING):
        {
            pvSetEnabled(p,id,1);
            pvSetStyle(p,id,-1,1,1,-1);
            break;
        }
        default:
            break;
        }
    return 0;
}

static int setStationData(PARAM *p,long code, std::vector<station> list, int setAlsoStationCombo)
{
    int ret = -1;
    int found = 0;
    int i = 1;
    std::vector<station>::iterator iter;

    for(iter = list.begin(); iter != list.end() && !found; iter++)
    {
        if(iter->getCode()== code)
        {
            if(setAlsoStationCombo)
                pvSetCurrentItem(p,COMBOSTATIONS,i);
            pvSetText(p,EDITSTNAME,iter->getName().c_str());
            pvSetText(p,EDITSTCODE,std::to_string(code).c_str());
            int type;
            iter->getType(type);
            if(type <5 && type >0)
                pvSetCurrentItem(p,COMBOSTTYPE,type-1);	      
        }
        i++;
    }
    return ret;
}

static int setCostumerData(PARAM *p,long code, std::vector<costumer> list, int setAlsoCostumerCombo)
{
    int ret = -1;
    int found = 0;
    int i = 1;
    std::vector<costumer>::iterator iter;  

    for(iter = list.begin(); iter != list.end() && !found; iter++)
    {
        if(iter->getCode()== code)
        {
            if(setAlsoCostumerCombo)
                pvSetCurrentItem(p,COMBOOURID,i);
            pvSetText(p,EDITCODEID,std::to_string(code).c_str());
            pvSetText(p,EDITNIF,iter->getNif().c_str());
        }
        i++;
    }
    return ret;
}

static int setTransData(PARAM *p,long code, std::vector<costumer> list, int setAlsoCostumerCombo)
{
    int ret = -1;
    int found = 0;
    int i = 1;
    std::vector<costumer>::iterator iter;

    for(iter = list.begin(); iter != list.end() && !found; iter++)
    {
        if(iter->getCode()== code)
        {
            if(setAlsoCostumerCombo)
                pvSetCurrentItem(p,COMBOOURTRANS,i);
            pvSetText(p,EDITCODETRANS,std::to_string(code).c_str());
            pvSetText(p,EDITNIFTRANS,iter->getNif().c_str());
        }
        i++;
    }
    return ret;
}

static void toolsDeactivateGUI(PARAM *p, DATA* d, int deactivate)
{
    if(deactivate)
    {
        setFrame(p,d,FRAMEGENERAL,FRAME_DISABLED);
        setFrame(p,d,FRAMECAMS,FRAME_DISABLED);
        setFrame(p,d,FRAMEBAS,FRAME_DISABLED);
        setFrame(p,d,FRAMESMTPMAIL,FRAME_DISABLED);
        setFrame(p,d,FRAMEIMP,FRAME_DISABLED);
        setFrame(p,d,FRAMEOURID,FRAME_DISABLED);
        
    }
    else
    {
        setFrame(p,d,FRAMEGENERAL,FRAME_NORMAL);
        setFrame(p,d,FRAMECAMS,FRAME_NORMAL);
        setFrame(p,d,FRAMEBAS,FRAME_NORMAL);
        setFrame(p,d,FRAMESMTPMAIL,FRAME_NORMAL);
        setFrame(p,d,FRAMEIMP,FRAME_NORMAL);
        setFrame(p,d,FRAMEOURID,FRAME_NORMAL);
    }
    return;
}

static void globalSyncronization(PARAM *p, DATA* d)
{
    //block gui
    pvSetMovie(p,LOADINGFORM,1,myResources.RES_LOADING.c_str());
    pvMovieControl(p,LOADINGFORM,-2); // restart
    pvShow(p,LOADINGFORM);       
    /**desactive all**/
    toolsDeactivateGUI(p,d,1);
    /**COMMON**/
    toolsSetNAV(p,d,0);
    /**special**/
    pvSetEnabled(p,BUTSINCRONIZA,0);
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
        syncReconnectIfNeeded();
        int wasError=0;
        int error = syncCostumers(p);
        if(error != -1)
        {
            if(error)
                console.push_back("¡Error al sincronizar la tabla de clientes!");
            wasError = wasError + error;
            error = syncProducts(p);
            if(error)
                console.push_back("¡Error al sincronizar la tabla de productos!");
            wasError = wasError + error;
            error = syncCostumersProducts(p);
            if(error)
                console.push_back("¡Error al sincronizar la tabla de clientes-productos!");
            wasError = wasError + error;
            error = syncCars(p);
            if(error)
                console.push_back("¡Error al sincronizar la tabla de vehiculos!");
            wasError = wasError + error;
            error = syncOrders(p);
            if(error)
                console.push_back("¡Error al sincronizar la tabla de ordenes!");
            wasError = wasError + error;
            error = syncDrivers(p);
            if(error)
                console.push_back("¡Error al sincronizar la tabla de transportistas!");
            wasError = wasError + error;
            error = syncMovements(p,myStation->getCode());
            if(error)
                console.push_back("¡Error al sincronizar la tabla de movimientos!");
            wasError = wasError + error;
            error = syncTransitDep(p,myStation->getCode());
            if(error)
                console.push_back("¡Error al sincronizar la tabla de transito de cargas de material!");
            wasError = wasError + error;
            error = syncStations(p);
            if(error)
                console.push_back("¡Error al sincronizar la tabla de centros!");
            wasError = wasError + error;
            error = syncTransfers(p,myStation->getCode());
            if(error)
                console.push_back("¡Error al sincronizar la tabla de transferencias!");
            wasError = wasError + error;
        }
        else
            console.push_back("*ERROR* ¡Error en la conexión con la base de datos central!");	      
        if(wasError)
            console.push_back("*ERROR* ¡Hubo errores al conectarse y/o procesar tablas!");
        else
            console.push_back("(INFO) ¡Sincronización completada!");
    }
    else
    {
        console.push_back("*ERROR* ¡No podemos conectar con la base de datos central!");
        system("extras/scripts/relaunch-ssh.sh");
    }
    //recover gui
    /**special**/
    pvSetEnabled(p,BUTSINCRONIZA,1);
    pvHide(p,LOADINGFORM);
    toolsDeactivateGUI(p,d,0);
    toolsSetNAV(p,d,1);
    /**/
    return;
}

static void retrieveStations(PARAM *p)
{	    
    char * sql = NULL;

    selAllDatFrmLocalCenters(sql);
    if(!localDatabase.query(p,sql))
    {
        std::vector<std::vector<std::string>>  dataReturn = localDatabase.retData2();
        std::vector<std::vector<std::string>>::iterator iter;
        allStations.clear();
        for(iter = dataReturn.begin(); iter != dataReturn.end(); ++iter)
            allStations.push_back(station(*iter));	 
    }
    if( sql != NULL)
        delete [] sql;
    return;
}

static void retrieveCostumers(PARAM *p)
{	    
    char * sql = NULL;

    selAllDatFrmCostumers(sql);		    
    if(!localDatabase.query(p,sql))
    {
        std::vector<std::vector<std::string>> dataReturn = localDatabase.retData2();
        std::vector<std::vector<std::string>>::iterator iter;
        allCostumers.clear();
        for(iter = dataReturn.begin(); iter != dataReturn.end(); ++iter)
            allCostumers.push_back(costumer(*iter));	 
    }
    if( sql != NULL)
        delete [] sql;
    return;
}

static void retrieveTransports(PARAM *p)
{
    char * sql = NULL;

    selAllDatFrmCostumers(sql);
    if(!localDatabase.query(p,sql))
    {
        std::vector<std::vector<std::string>> dataReturn = localDatabase.retData2();
        std::vector<std::vector<std::string>>::iterator iter;
        allTransports.clear();
        for(iter = dataReturn.begin(); iter != dataReturn.end(); ++iter)
            allTransports.push_back(costumer(*iter));
    }
    if( sql != NULL)
        delete [] sql;
    return;
}

static int consoleRefresh(PARAM *p, DATA * d)
{
    int ret = -1;
    //console
    std::vector <std::string>::iterator iter;
    unsigned int i=0;
    if(d->localConsole.size() != console.size())
    {
        for(iter = console.begin(); iter != console.end() ; ++iter)
        {
            if(!iter->empty() && i >= d->localConsole.size())
            {
                d->localConsole.push_back(*iter);
                pvSetText(p,OUTPUT,iter->c_str());
                ret = 0;
            }
            i++;
        }
    }
    return ret;
}

static void clearMask2()
{
    if (ourId)
        delete ourId;
    if (defTrans)
        delete defTrans;
    return;
}
#endif
