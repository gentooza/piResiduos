/*
This file is part of PiResiduos.

Copyright 2017-2019, Prointegra SL.
Copyright 2019 Pixelada S. Coop. And <info (at) pixelada (dot) org>

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

/**
@file formulario.cpp
*/
#include "formulario.h"

baseForm::baseForm(int type, int entrance)  
{
    clearMovement(myArrMovement);
    clearMovement(myDepMovement);
    //pointers
    arrOriginStation = new station();
    depOriginStation = new station ();
    arrDestinationStation = new station ();
    depDestinationStation = new station ();
    ourId = NULL;
    ourStation = NULL;
    staff_in_charge = new staff();
    dep_driver = new driver();
    depAuthCostumer = NULL;
    /**TODO BORRAR NO NECESARIO**/
    formType = NOT_DEFINED;
    if(type == ET || type == PT)
    {
        formType = type;
        formState = -1;
    }
    formLlegada = entrance;
    /*****************/

    //plate dimensions
    maxPlateLength = 8;
    minPlateLength = 5;

    //departure movement index in matrix
    depMovIndex = -1;
    
    return;
}
baseForm::baseForm()
{
    clearMovement(myArrMovement);
    clearMovement(myDepMovement);
    arrOriginStation = NULL;
    depOriginStation = NULL;
    arrDestinationStation = NULL;
    depDestinationStation = NULL;
    ourId = NULL;
    ourStation = NULL;
    staff_in_charge = new staff();
    dep_driver = NULL;
    depAuthCostumer = NULL;
    return;
}
baseForm::~baseForm()
{
    if(arrOriginStation)
        delete arrOriginStation;
    if(depOriginStation)
        delete depOriginStation;
    if(arrDestinationStation)
        delete arrDestinationStation;
    if(depDestinationStation)
        delete depDestinationStation;
    if(ourId)
        delete ourId;
    if(ourStation)
        delete ourStation;
    if(staff_in_charge)
        delete staff_in_charge;
    if(dep_driver)
        delete dep_driver;
    if(depAuthCostumer)
        delete depAuthCostumer;
    resetDrivers();
    return;
}
void baseForm::copyFrom(baseForm * toCopy)  
{
    myArrMovement = toCopy->retArrMovement();
    myDepMovement = toCopy->retDepMovement();

    toCopy->retArrOriginStation(arrOriginStation);
    toCopy->retDepOriginStation(depOriginStation);
    toCopy->retArrDestinationStation(arrDestinationStation);
    toCopy->retDepDestinationStation(depDestinationStation);
    toCopy->retOurId(ourId);
    toCopy->retOurStation(ourStation);

    setState(toCopy->getState());
    formSCADA = toCopy->retForm();
    arrFolder = toCopy->retArrDiFolder();
    depFolder = toCopy->retDepDiFolder();

    //incidents and comments 
    setInputIncidents(toCopy->getInputIncidents());
    setOutputIncidents(toCopy->getOutputIncidents());
    setInputComment(toCopy->getInputComment());
    setOutputComment(toCopy->getOutputComment());

    //ERROR_ACCEPTED_WEIGHT
    setErrorScale(toCopy->retErrorScale());

    //DRIVER
    toCopy->ret_dep_driver(dep_driver);
    //dep authorized costumer
    try 
    {
        toCopy->retDepAuthCostumer(depAuthCostumer);
    } 
    catch(...) 
    {
        std::cout << "TODO: memory error in redDepAuthCostumer" << std::endl;
        depAuthCostumer = new costumer();
    }

    return;
}

void baseForm::resetForm(int departure)
{
    resetOurId();
    if(!departure) //arrival
    {
        formInicState=0;
        //forzado producto   
        iIncidents.clear();
        iComment.clear();
        clearMovement(myArrMovement);
        resetArrOrigin();
        resetArrDestination();
        clearArrDiFolder();
    }
    else //Departure
    {
        //forced status
        //
        oIncidents.clear();
        oComment.clear();
        clearMovement(myDepMovement);
        resetDepOrigin();
        resetDepDestination();
        clearDepDiFolder();
        staff_in_charge->reset();
        dep_driver->reset();
    }
    return;
}

void baseForm::clearMovement(struMovement & myMovement)
{
    std::string empty;
    empty.clear();
    myMovement.CODIGO_ORDEN= -1;
    myMovement.ECOEMBES = -1;
    myMovement.CODIGO_CLIENTE = -1;
    myMovement.CLIENTE_NOMBRE.clear();
    myMovement.CLIENTE_NIF.clear();
    myMovement.CLIENTE_DIRECCION.clear();
    myMovement.CLIENTE_PROVINCIA.clear();
    myMovement.CLIENTE_POBLACION.clear();
    myMovement.CLIENTE_CP = 0;
    myMovement.CLIENTE_TIPO = -1;
    myMovement.CLIENTE_TIPO_DEF = -1;
    myMovement.CLIENTE_COMUNIDAD_AUTONOMA.clear();
    myMovement.CLIENTE_NIMA = -1;
    myMovement.CLIENTE_NUM_INSCRIPCION = -1;
    myMovement.CLIENTE_TELEFONO = -1;
    myMovement.CLIENTE_MAIL.clear();

    myMovement.CLIENTE_PARTICULAR_NOMBRE.clear();
    myMovement.CLIENTE_PARTICULAR_NIF.clear();
    myMovement.CLIENTE_PARTICULAR_DIRECCION.clear();
    myMovement.CLIENTE_PARTICULAR_PROVINCIA.clear();
    myMovement.CLIENTE_PARTICULAR_POBLACION.clear();
    myMovement.CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA.clear();
    myMovement.CLIENTE_PARTICULAR_CP = 0;
    myMovement.CLIENTE_PARTICULAR_TIPO = 0;
    myMovement.CLIENTE_PARTICULAR_TIPO_DEF = 0;
    myMovement.CLIENTE_PARTICULAR_NIMA = 0;
    myMovement.CLIENTE_PARTICULAR_NUM_INSCRIPCION = 0;
    myMovement.CLIENTE_PARTICULAR_TELEFONO = 0;
    myMovement.CLIENTE_PARTICULAR_MAIL.clear();
    
    myMovement.CODIGO_PRODUCTO = -1;
    myMovement.PRODUCTO_LER = -1;
    myMovement.PRODUCTO_NOMBRE.clear();
    myMovement.PRODUCTO_NOMBRE2.clear();
    myMovement.PRODUCTO_NOMBRE3.clear();
    myMovement.PRODUCTO_PELIGROSIDAD.clear();

    myMovement.CLIENTE_PRODUCTO_NPT = -1; 
    
    myMovement.FECHA_FIRMA.clear();
    myMovement.FECHA_PROGRAMADA.clear();
    myMovement.PRECIO_TN = -1;
    myMovement.FORMA_DE_PAGO = 0;  
    myMovement.PESO_A_RETIRAR = 0;

    myMovement.OPERACION_DE_TRATAMIENTO.clear();

    myMovement.FECHA_HORA.clear();
    myMovement.MATRICULA.clear();
    myMovement.IMAGEN_MATRICULA.clear();
    myMovement.REMOLQUE.clear();
    myMovement.PERMISOS_PRODUCTO = resetPermits();
    myMovement.DI.clear();
    myMovement.PESO_ENTRADA = 0;
    myMovement.PESO_SALIDA = 0;
    myMovement.CODIGO_MOVIMIENTO.clear();
    myMovement.TIPO_DE_MOVIMIENTO = -1;
    myMovement.REPETIR = 0;
    return;
}
/*!fucntion loading to movement our order information*/
void baseForm::setArrMov(struMovement myOrder)
{
    clearMovement(myArrMovement);
    myArrMovement = myOrder;
    setArrDateTime(getCurrentDate());

    return;
}
/*!prepare to save sql movement*/
void baseForm::storeMov(std::string & sqliteQuery, std::string & mysqlQuery,station *& myStation, qtDatabase & localDatabase)
{
    char * sql = NULL;

    //getting last movement code for this station and DI
    std::string sCodigo_estacion = std::to_string(myStation->getCode());
    selLastMovCode(sql,sCodigo_estacion.c_str());
    localDatabase.query(NULL,sql);
    if( sql != NULL)
        delete [] sql;
    std::vector<std::vector<std::string>> ourData = localDatabase.retData2();
    std::string codigo_mov = "-1";
    if(ourData.size())
    {
        codigo_mov = ourData.at(0).at(0);
    }	   
    std::cout << "DEBUG: actualizando el código del movimiento!!, código de la estación:" << myStation->getCode() << " ,último código:" << codigo_mov << std::endl;
    setMovCode(codigo_mov,myStation->getCode(),retDepMovType());
    std::cout << "DEBUG: nuevo código:" << retDepMovCode();
    //almacenamos en movimientos
    sqliteQuery = "insert into MOVIMIENTOS (CODIGO_MOV,DI,FECHA_HORA_INICIO, FECHA_HORA_FINAL,TIPO_MOV,CODIGO_CLIENTE,CODIGO_PRODUCTO,CODIGO_TRANSPORTISTA,CODIGO_BASCULISTA,PESO_NETO,PESO_TARA,PESO_BRUTO,PRECIO,VEHICULO,REMOLQUE,CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS,COMENTARIO_OPERADOR,CLIENTE_PARTICULAR_NOMBRE,CLIENTE_PARTICULAR_NIF,CLIENTE_PARTICULAR_DOMICILIO,CLIENTE_PARTICULAR_PROVINCIA,CLIENTE_PARTICULAR_POBLACION,CLIENTE_PARTICULAR_CODIGO_POSTAL,CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA,CLIENTE_PARTICULAR_NIMA,CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO,CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO, TIPO_CLIENTE, SINCRONIZADO ) values (\"";
    mysqlQuery = "insert into movimientos (CODIGO_MOV,DI,FECHA_HORA_INICIO, FECHA_HORA_FINAL,TIPO_MOVIMIENTO,CODIGO_CLIENTE,CODIGO_PRODUCTO,CODIGO_TRANSPORTISTA,CODIGO_BASCULISTA,PESO_NETO,PESO_TARA,PESO_BRUTO,PRECIO,VEHICULO,REMOLQUE,CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS,COMENTARIO_OPERADOR,CLIENTE_PARTICULAR_NOMBRE,CLIENTE_PARTICULAR_NIF,CLIENTE_PARTICULAR_DOMICILIO,CLIENTE_PARTICULAR_PROVINCIA,CLIENTE_PARTICULAR_POBLACION,CLIENTE_PARTICULAR_CODIGO_POSTAL,CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA,CLIENTE_PARTICULAR_NIMA,CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO,CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO, TIPO_CLIENTE) values (\"";
    //codigo movimiento
    std::string values = retDepMovCode();
    values += "\",\"";
    values +=  retDepDi();
    values += "\",\"";  
    values += retDepDateTime();
    values += "\",\"";
    setDepFinalDateTime(getCurrentDate());
    values += retDepFinalDateTime();
    values += "\",";
    values += std::to_string(retDepMovType());
    values += ",";
    values += std::to_string(retDepCosCode());
    values += ",";
    values += std::to_string(retDepProdCode());
    values += ",";
    values += std::to_string(retDepDriCode());
    values += ",";
    values += std::to_string(staff_in_charge->get_code());
    values += ",";
    values += std::to_string(retDepTotalWeight()); //PESO NETO
    values += ",";	    
    values += std::to_string(retDepScaleIn());  // PESO TARA
    values += ","; 
    values += std::to_string(retDepScaleOut()); //PESO BRUTO
    values += ",";
    values += std::to_string(retDepPrice());
    values += ",\"";
    values += retDepPlate();
    values += "\",\"";
    values += retDepPlateAtt(); 
    values += "\",";
    values += std::to_string(depOriginStation->getCode());
    values += ",";
    values += std::to_string(depDestinationStation->getCode());
    values += ",\"";
    values += vectorToString(getOutputIncidents(),"; ");
    values += "\",\"";
    values += getOutputComment();
    values += "\",\"";
    values += retDepPCosName();
    values += "\",\"";
    values += retDepPCosNif();
    values += "\",\""; 
    values += retDepPCosAddr();
    values += "\",\"";
    values += retDepPCosProv(); 
    values += "\",\"";
    values += retDepPCosCity();
    values += "\",";
    values += std::to_string(retDepPCosZip());
    values += ",\"";  
    values += retDepPCosReg();
    values += "\",";
    values += std::to_string(retDepPCosNima());
    values += ",";
    values += std::to_string(retDepPCosNumIns());
    values += ",";
    values += std::to_string(retDepPCosPhone());
    values += ",\"";    
    values += retDepPCosMail();
    values += "\",\"";
    values += depDestinationStation->getName();
    values += "\",\"";
    values += depDestinationStation->getNif();  
    values += "\",\"";
    values += depDestinationStation->getAddress();
    values += "\",\"";
    values += depDestinationStation->getProvence();
    values += "\",\"";
    values += depDestinationStation->getCity();
    values += "\",";
    values += std::to_string(depDestinationStation->getZip());
    values += ",\"";
    values += depDestinationStation->getRegion();
    values += "\",";
    values += std::to_string(depDestinationStation->getNima());
    values += ",";
    values += std::to_string(depDestinationStation->getNumIns());
    values += ",";
    values += std::to_string(depDestinationStation->getPhone());
    values += ",\"";
    values += depDestinationStation->getMail();
    values += "\",";
    values += std::to_string(retDepCosType());  

    sqliteQuery += values;
    sqliteQuery += ",0)"; 
    mysqlQuery += values;
    mysqlQuery += ")";

    return;
}

/*!function for checking last movement stored, for redundancy purposes*/
void baseForm::check_last(std::string& remoteSql,station *& myStation)
{
    remoteSql = "select * from movimientos where CODIGO_MOV = " + retDepMovCode();
    return;
}

void baseForm::savePlateImage(int pos,const char* entrada_salida)
{
    int ret;
    //std::cout << "debug: inside saveArrPlateImage()" << std::endl;
    ret = system("mkdir saves");

    std::string command = "mkdir \"";
    command += arrFolder + "\"";
    std::cout << "TERMINAL COMMAND: "<< command << std::endl;
    ret = system(command.c_str());
    
    
    command.clear();
    command = "convert camera/capture";
    command += std::to_string(pos);
    command += ".jpg";
    command += " -resize 50% \"";
    command += arrFolder;
    command += "/camara_";
    command += entrada_salida;
    command += ".png\"";
    ret = system(command.c_str());
    
    espera(1);
    
    command.clear();
    command = "rm  camera/capture";
    command += std::to_string(pos);
    command += ".jpg";
    
    return;
}

void baseForm::saveSignature(int blank_signature)
{
    int ret;
    ret = system("mkdir saves");

    std::string command = "mkdir \"";
    command += depFolder + "\"";
    std::cout << "TERMINAL COMMAND: " << command << std::endl;
    ret = system(command.c_str());

    if(!blank_signature)
    {
        command.clear();
        command = "convert FIRMA.ppm \"";
        command += depFolder;
        command += "/firma.png\"";
        std::cout << command << std::endl;
        ret = system(command.c_str());
    }
    else
    {
        std::string destination_path = depFolder + "/firma.png";
        ret = tools_copy("./image/void.png",destination_path.c_str());
    }
    return;
}

void baseForm::saveSignature(const char* file)
{
    int ret;
    ret = system("mkdir saves");

    std::string command = "mkdir ";
    command += "\"" + depFolder + "\"";
    std::cout << "TERMINAL COMMAND: " << command << std::endl;
    ret = system(command.c_str());
    
    command.clear();
    command = "cp ";
    command += file;
    command += " \"";
    command += depFolder;
    command += "/firma.png\"";
    std::cout << command << std::endl;
    ret = system(command.c_str());
    
    return;
}

int baseForm::isSignature()
{
    int exist = 0;

    std::string path = depFolder + "/firma.png";
    if( access( path.c_str(), F_OK ) != -1 )
        exist = 1;
        
    return exist;
}

void baseForm::backupFiles(const char* movFolder)
{
    int ret;
    ret = system("mkdir backup");

    std::string command = "mkdir \"backup/";
    command += movFolder;
    command +="\"";
    ret = system(command.c_str());

    command = "cp -R \"";
    command += depFolder;
    command += "\"/* ";
    command += "\"backup/";
    command += movFolder;
    command += "\"";
    ret = system(command.c_str());

    command = "rm -R \"";
    command += depFolder + "\" &";
    ret = system(command.c_str());

    if((retDepMovType() != DEF_MOV_TRANSFER) || formLlegada)
    {
        //remote copying
        copy_files_to_remote_server(movFolder);
    }
    return;
}

int baseForm::printType()
{
    int ret = -1;
    switch(formType)
    {
        case(1):
            std::cout << "formulario de Entrada a ET \n" << std::endl;
            ret = 0;
            break;
        default:
            std::cout << "formulario no definido \n" << std::endl;
            break;
    };
    return ret;
}

void baseForm::setProductPermits(std::vector <std::string> permits)
{
    std::vector <std::string>::iterator iter;
    int num;
    productPermits.clear();
    for(iter = permits.begin(); iter != permits.end(); ++iter)
    {
        num = 0;
        num = stoi(*iter);
        if(num == 0)
            productPermits.push_back(false);
        else
            productPermits.push_back(true);
    }
    return;
}
/*! TODO: function in spanish and for debugging purposes? */
int baseForm::showPermisos()
{
    int ret = 0;
    if(productPermits.size() == 6 && clientProductPermits.size() == 5)
    {
        for(int i=0; i < productPermits.size(); i++)
        {
            std::cout << "permiso: " << i+1 << std::endl;
            if(i==0)
            {
                std::cout << "Producto permitido? " << (productPermits.at(i)==true ? "Sí!" : "No!");
                std::cout << std::endl;
            }
            else
            {
                std::cout << "Nos lo piden? " << (productPermits.at(i)==true ? "Sí!" : "No!");
                std::cout << std::endl;
                std::cout << "permisovalor: " << clientProductPermits.at(i-1) << std::endl;	  
            }
        }
    }
    else
    {
        std::cout << "no tienen el tamaño establecido!, permisos producto:" << productPermits.size() << ", permisos cliente-producto:" << clientProductPermits.size() << std::endl;
        ret = 1;
    }
    return ret;
}

int baseForm::checkPermisos()
{
    int ret = 0;
    if(productPermits.size() == 6 && clientProductPermits.size() == 5)
    {
        for(int i=0; i < productPermits.size(); i++)
        {
            //std::cout << "permiso: " << i+1 << std::endl;
            if(i==0)
                overallProductPermit = productPermits.at(i);
            else if (i==1) //fecha contrato
            {
                if(productPermits.at(1))
                    setDatePermit(clientProductPermits.at(0));
                else
                    contractDatePermit = true;
            }
            else if (i==2) //NPT
            {
                nptPermit=true;
                if(productPermits.at(2))
                {
                    if(std::stoi(clientProductPermits.at(1))==1)
                        nptPermit=true;
                    else
                        nptPermit=false;		    
                }
            }
            else if (i==3) //CB
            {
                cbPermit=true;
                if(productPermits.at(3))
                {
                    if(std::stoi(clientProductPermits.at(2))==1)
                        cbPermit=true;
                    else
                        cbPermit=false;		    
                }
            }
            else if (i==4) //CP
            {
                cpPermit=true;
                if(productPermits.at(4))
                {
                    if(std::stoi(clientProductPermits.at(3))==1)
                        cpPermit=true;
                    else
                        cpPermit=false;		    
                }
            }
            else if (i==5) //DCP
            {
                dcpPermit=true;
                if(productPermits.at(5))
                {
                    if(std::stoi(clientProductPermits.at(4))==1)
                        dcpPermit=true;
                    else
                        dcpPermit=false;		    
                }
        
            }
        }
    }
    else
    {
        std::cout << "no tienen el tamaño establecido!, permisos producto:" << productPermits.size() << ", permisos cliente-producto:" << clientProductPermits.size() << std::endl;
        ret = 1;
    }
    return ret;
}

void baseForm::setDatePermit(std::string strDate)
{
    bool permit = false;
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    
    std::string strYear = strDate.substr(0,4);
    std::string strMonth = strDate.substr(5,2);
    std::string strDay = strDate.substr(8,2);

    int strYear_chkd;
    int strMonth_chkd;
    int strDay_chkd;

    try
    {
        strYear_chkd = std::stoi(strYear);
    }
    catch(...)
    {
        strYear_chkd = 0;
    }
    try
    {
        strMonth_chkd = std::stoi(strMonth);
    }
    catch(...)
    {
        strMonth_chkd = 0;
    }
    try
    {
        strDay_chkd = std::stoi(strDay);
    }
    catch(...)
    {
        strDay_chkd = 0;
    }
    if(strYear_chkd > (timePtr->tm_year + 1900))
        permit = true;
    else if(strYear_chkd == (timePtr->tm_year + 1900))
    {
        if( strMonth_chkd > (timePtr->tm_mon + 1))
            permit = true;
        else if(strMonth_chkd == (timePtr->tm_mon + 1))
        {
            if( strDay_chkd >= (timePtr->tm_mday))
                permit = true;	  
        }
    }
    contractDatePermit = permit;
    return;
}

std::string baseForm::createArrDi(qtDatabase & localDatabase)
{
    std::string di;
    //our year
    time_t myTime = time(NULL);
    struct tm *aTime = localtime(&myTime);
    int year = aTime->tm_year + 1900;
            
    char * sql = NULL;
    std::string temporalDI;
    std::string temporalDIDate;
    std::vector<std::vector<std::string>> ourData;
    //LAST DI
    selLastDiFromMovementsByClientProduct(sql,retArrCosCode(),retArrProdCode());  
    localDatabase.query(NULL,sql);
    ourData = localDatabase.retData2();
    if(ourData.size())
    {
        temporalDI = ourData.at(0).at(0);
        temporalDIDate = ourData.at(0).at(1);
    }
    if (sql != NULL)
        delete [] sql;
    //REFRESH COSTUMER NIF
    setAllArrCostumerData(localDatabase);	   
    if(isNewYear(temporalDIDate,year)) //new year, new DI
        temporalDI.clear();	    
    di = generateDi(temporalDI,1);
    setArrDi(di);
    //FOLDER
    if(retArrDateTime().empty())
        setArrDateTime(getCurrentDate());
    std::string folder =retArrDi() + " "+ retArrDateTime();
    setArrDiFolder(folder);
        
    return retArrDi();
}

std::string baseForm::createDepDi(qtDatabase & localDatabase)
{
    std::string oldDi = retDepDi();
    std::string di;
    //our year
    time_t myTime = time(NULL);
    struct tm *aTime = localtime(&myTime);
    int year = aTime->tm_year + 1900;
            
    char * sql = NULL;
    std::string temporalDI;
    std::string temporalDIDate;
    std::vector<std::vector<std::string>> ourData;
    //LAST DI
    selLastDiFromMovementsByClientProduct(sql,retDepCosCode(),retDepProdCode());  
    localDatabase.query(NULL,sql);
    ourData = localDatabase.retData2();
    if(ourData.size())
    {
        temporalDI = ourData.at(0).at(0);
        temporalDIDate = ourData.at(0).at(1);
    }
    if (sql != NULL)
    {
        delete[] sql;
    }
    
    //REFRESH COSTUMER NIF
    setAllDepCostumerData(localDatabase);	   
    if(isNewYear(temporalDIDate,year)) //new year, new DI
        temporalDI.clear();	    
    di = generateDi(temporalDI, 0);

    if(oldDi.compare(di)) //COPYING DATA
    {
        std::string oldFolder = "\"saves/" + retDepDi();
        std::string newFolder = "\"saves/" + di;
        if(!retDepDateTime().empty())
        {
            oldFolder += " " + retDepDateTime();
            newFolder += " " + retDepDateTime();
        }
        oldFolder += "\"";
        newFolder += "\""; 
        
        std::string command = "mkdir " + newFolder;
        system(command.c_str());
        command = "cp " + oldFolder + "/* " + newFolder;
        system(command.c_str());
        command = "rm -r " + oldFolder;
        system(command.c_str());
    }
    setDepDi(di);
    //FOLDER
    std::string folder = retDepDi();
    if(!retDepDateTime().empty())
        folder += " "+ retDepDateTime();
    setDepDiFolder(folder);

    return retDepDi();
}

std::string baseForm::generateDi(std::string lastDi, int arrive)
{
  std::string di;
  std::string NIF;

  std::string actualYear = getCurrentDate().substr(0,4);
  if(arrive)
     NIF = retArrCosNif();
  else
    NIF = retDepCosNif();
  if (NIF.empty())
    NIF = "AXXXXXXXX";
  if(!lastDi.empty())
    {
      if(lastDi.length()>= 18) //DI(2)+NIF(9)+YYYY+XXXXXXX(7)
	{
	  int lastnumber_chkd;
	  try
	    {
	      lastnumber_chkd = std::stoi(lastDi.substr(lastDi.length() - 7));
	    }
	  catch(...)
	    {
	      lastnumber_chkd = 0;
	    }


	  int lastNumber = lastnumber_chkd;
	  lastNumber++;
	  if(lastNumber > 9999999)
	    lastNumber = 9999999;
	  di = "di"+NIF+actualYear+zeroPadNumber(lastNumber,7);	  
	}
      else
	di = "di"+NIF+actualYear+"0000001";
    }
  else
      di = "di"+NIF+actualYear+"0000001";
  
  return di;
}
/******************************/
//INCIDENTS GENERATION FUNCTIONS

void baseForm::checkInIncident(int edited,std::string incidentCode, std::string message)
{
  std::vector<std::string>::iterator iter;
  int alreadyDone = 0;

  if(!incidentCode.empty() && !message.empty())
    {
      if(edited)
	{
	  for(iter=iIncidents.begin();iter!=iIncidents.end() && !alreadyDone;++iter)
	    {
	      std::string code = iter->substr(0,incidentCode.length());
	      if(!code.compare(incidentCode))
		{
		  iIncidents.erase(iter);
		  alreadyDone=1;
		}
	    }
	  iIncidents.push_back(message);
	}
      else
	{
	  for(iter=iIncidents.begin();iter!=iIncidents.end();)
	    {
	      std::string code = iter->substr(0,incidentCode.length());
	      if(!code.compare(incidentCode))
		iter= iIncidents.erase(iter);
	      else
		++iter;
	    }
	}
    }
}

void baseForm::checkOutIncident(int edited,std::string incidentCode, std::string message)
{
  std::vector<std::string>::iterator iter;
  int alreadyDone = 0;

  if(!incidentCode.empty() && !message.empty())
    {
      if(edited)
	{
	  for(iter=oIncidents.begin();iter!=oIncidents.end() && !alreadyDone;++iter)
	    {
	      std::string code = iter->substr(0,incidentCode.length());
	      if(!code.compare(incidentCode))
		{
		  iter= oIncidents.erase(iter);
		  alreadyDone=1;
		}
	    }
	  oIncidents.push_back(message);
	}
      else
	{
	  for(iter=oIncidents.begin();iter!=oIncidents.end();)
	    {
	      std::string code = iter->substr(0,incidentCode.length());
	      if(!code.compare(incidentCode))
		iter= oIncidents.erase(iter);
	      else
		++iter;
	    }
	}
    }
}
int baseForm::isInIncident(std::string incidentCode)
{
  int exists = 0;
  std::vector<std::string>::iterator iter;

  for(iter=iIncidents.begin();iter!=iIncidents.end() && !exists;++iter)
    {
      std::string code = iter->substr(0,incidentCode.length());
      if(!code.compare(incidentCode))
	exists = 1;       
    }

  return exists;
}

int baseForm::isOutIncident(std::string incidentCode)
{
  int exists = 0;
  std::vector<std::string>::iterator iter;

  for(iter=oIncidents.begin();iter!=oIncidents.end() && !exists;++iter)
    {
      std::string code = iter->substr(0,incidentCode.length());
      if(!code.compare(incidentCode))
	exists = 1;       
    }

  return exists;
}

/*! plates incidents
 */
void baseForm::incArrPlateEdited(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00001"; //arrive plate incident code

      std::string message = sIncidentCode;
      message +=": matrícula de entrada a planta, editada a mano, valor = ";
      message += retArrPlate();

      checkInIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncArrPlateEdited()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00001"; //arrive plate incident code

      alreadyDone = isInIncident(sIncidentCode);
    }
  return alreadyDone;
}

void baseForm::incDepPlateEdited(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00002"; //departure plate incident code

      std::string message = sIncidentCode;
      message +=": matrícula de salida de planta, editada a mano, valor = ";
      message += retDepPlate();

      checkOutIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncDepPlateEdited()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00002"; //departure plate incident code

      alreadyDone = isOutIncident(sIncidentCode);
    }
  return alreadyDone;
}

//authorized manually
void baseForm::incArrPlateAuto(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00011"; //arrive plate autorized incident code

      std::string message = sIncidentCode;
      message +=": matrícula de entradas a planta, no registrada y autorizada manualmente, valor = ";
      message += retArrPlate();

      checkInIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncArrPlateAuto()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00011"; //departure plate incident code

      alreadyDone = isInIncident(sIncidentCode);
    }
  return alreadyDone;
}

//////
//particular costumer
void baseForm::incArrParticular(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00012"; //arrive particular costumer incident code

      std::string message = sIncidentCode;
      message +=": transporte definido como cliente particular que no está registrado";

      checkInIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncArrParticular()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00012"; //arrive particular costumer incident code

      alreadyDone = isInIncident(sIncidentCode);
    }
  return alreadyDone;
}
////products
void baseForm::incArrProdFz( int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00020"; //arrive product permissions forced

      std::string message = sIncidentCode;
      message +=": los permisos del producto se han forzado para poder descargar en la planta";

      checkInIncident(edited,sIncidentCode,message);
    }
}
int baseForm::isIncArrProdFz()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00020"; //arrive product permissions forced

      alreadyDone = isInIncident(sIncidentCode);
    }
  return alreadyDone;
}
void baseForm::incDepProdFz( int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00021"; //departure product permissions forced

      std::string message = sIncidentCode;
      message +=": los permisos del producto se han forzado para poder sacarlo de la planta";

      checkOutIncident(edited,sIncidentCode,message);
    }
}
int baseForm::isIncDepProdFz()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00021"; //departure product permissions forced

      alreadyDone = isOutIncident(sIncidentCode);
    }
  return alreadyDone;
}

//scales
void baseForm::incArrScaleEdited(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00005"; //arrive scale edited

      std::string message = sIncidentCode;
      message +=": peso en entrada a planta editado a mano, valor = ";
      message += std::to_string(retArrScaleIn());

      checkInIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncArrScaleEdited()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00005"; //arrive scale edited

      alreadyDone = isInIncident(sIncidentCode);
    }
  return alreadyDone;
}

void baseForm::incDepScaleEdited(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00006"; //departure scale edited

      std::string message = sIncidentCode;
      message +=": peso en salida de planta editado a mano, valor = ";
      message += std::to_string(retDepScaleOut());

      checkOutIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncDepScaleEdited()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00006"; //departure scale edited

      alreadyDone = isOutIncident(sIncidentCode);
    }
  return alreadyDone;
}

////destination manually edited
void baseForm::incDestEdited(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00030"; //destino del transporte editado a mano

      std::string message = sIncidentCode;
      message +=": destino del transporte editado a mano";

      checkOutIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncDestEdited()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00030"; //destino del transporte editado a mano

      alreadyDone = isOutIncident(sIncidentCode);
    }
  return alreadyDone;
}

void baseForm::incNoSigned(int edited)
{
  if(ourStation)
    {
      std::string sStationCode = std::to_string(ourStation->getCode());
      std::string incident,sIncidentCode;

      sIncidentCode = sStationCode;
      sIncidentCode += "-";
      sIncidentCode += "00040"; //sin firmar

      std::string message = sIncidentCode;
      message +=": la persona encargada del transporte no ha firmado";

      checkOutIncident(edited,sIncidentCode,message);
    }
}

int baseForm::isIncNoSigned()
{
  int alreadyDone = 0;
  if(ourStation)
    {
      std::string sIncidentCode = std::to_string(ourStation->getCode());
      sIncidentCode += "-";
      sIncidentCode += "00040"; //sin firmar

      alreadyDone = isOutIncident(sIncidentCode);
    }
  return alreadyDone;
}

void baseForm::inputConcatenate(std::vector<std::string> newIncidents)
{
  std::vector<std::string>::iterator iter;
  std::string code;

  for(iter = newIncidents.begin(); iter != newIncidents.end(); ++iter)
    {
      //getting incident code
      code = extractIncidentCode(*iter);
      if(!isInIncident(code))
	iIncidents.push_back(*iter);
    }
}
void baseForm::outputConcatenate(std::vector<std::string> newIncidents)
{
  std::vector<std::string>::iterator iter;
  std::string code;

  for(iter = newIncidents.begin(); iter != newIncidents.end(); ++iter)
    {
      //getting incident code
      code = extractIncidentCode(*iter);
      if(!isOutIncident(code))
	oIncidents.push_back(*iter);
    }
}

/***********************************************/

/**PLATES**/
int baseForm::isArrPlateRegistered(qtDatabase & myDatabase)
{
    int reg = 0;

    if(!retArrPlate().empty())
    {
        char* sql = NULL;
        sel_all_cars(sql);
        if(!myDatabase.query(NULL,sql))
        {
            std::vector<std::vector<std::string>> retData;
            std::vector<std::vector<std::string>>::iterator iter;
            retData = myDatabase.retData2();     
            for(iter=retData.begin();iter!=retData.end()&&!reg;++iter)
            {
                if(iter->size())
                {
                    boost::to_upper(iter->at(0));
                    if(!retArrPlate().compare(iter->at(0)))
                    {
                        reg=1;
                    }
                }
            }
        }
        if (sql != NULL)
        {
            delete[] sql;
        }
    }
    return reg;
}

void baseForm::insertProduct(std::vector<std::string> record)
{
  struProduct newProduct;
  if(record.size() >=30)
    {   

long indi0_chkd;long indi1_chkd;
int indi5_chkd;int indi6_chkd;int indi7_chkd;int indi8_chkd;int indi9_chkd;
int indi10_chkd;int indi11_chkd;int indi12_chkd;int indi13_chkd;int indi14_chkd;int indi15_chkd;int indi16_chkd;int indi17_chkd;int indi18_chkd;int indi19_chkd;
int indi20_chkd;int indi21_chkd;int indi22_chkd;int indi23_chkd;int indi24_chkd;int indi25_chkd;int indi26_chkd;int indi27_chkd;int indi28_chkd;


	  try
	    {
	      indi0_chkd = std::stol(record.at(0));
	    }
	  catch(...)
	    {
	      indi0_chkd = 0;
	    }

	  try
	    {
	      indi1_chkd = std::stol(record.at(1));
	    }
	  catch(...)
	    {
	      indi1_chkd = 0;
	    }

	  try             			//5
	    {
	      indi5_chkd = std::stoi(record.at(5));
	    }
	  catch(...)
	    {
	      indi5_chkd = 0;
	    }

	  try             			//6
	    {
	      indi6_chkd = std::stoi(record.at(6));
	    }
	  catch(...)
	    {
	      indi6_chkd = 0;
	    }

	  try             			//7
	    {
	      indi7_chkd = std::stoi(record.at(7));
	    }
	  catch(...)
	    {
	      indi7_chkd = 0;
	    }

	  try             			//8
	    {
	      indi8_chkd = std::stoi(record.at(8));
	    }
	  catch(...)
	    {
	      indi8_chkd = 0;
	    }

	  try             			//9
	    {
	      indi9_chkd = std::stoi(record.at(9));
	    }
	  catch(...)
	    {
	      indi9_chkd = 0;
	    }

	  try             			//10
	    {
	      indi10_chkd = std::stoi(record.at(10));
	    }
	  catch(...)
	    {
	      indi10_chkd = 0;
	    }

	  try             			//11
	    {
	      indi11_chkd = std::stoi(record.at(11));
	    }
	  catch(...)
	    {
	      indi11_chkd = 0;
	    }

	  try             			//12
	    {
	      indi12_chkd = std::stoi(record.at(12));
	    }
	  catch(...)
	    {
	      indi12_chkd = 0;
	    }

	  try             			//13
	    {
	      indi13_chkd = std::stoi(record.at(13));
	    }
	  catch(...)
	    {
	      indi13_chkd = 0;
	    }

	  try             			//14
	    {
	      indi14_chkd = std::stoi(record.at(14));
	    }
	  catch(...)
	    {
	      indi14_chkd = 0;
	    }

	  try             			//15
	    {
	      indi15_chkd = std::stoi(record.at(15));
	    }
	  catch(...)
	    {
	      indi15_chkd = 0;
	    }

	  try             			//16
	    {
	      indi16_chkd = std::stoi(record.at(16));
	    }
	  catch(...)
	    {
	      indi16_chkd = 0;
	    }

	  try             			//17
	    {
	      indi17_chkd = std::stoi(record.at(17));
	    }
	  catch(...)
	    {
	      indi17_chkd = 0;
	    }

	  try             			//18
	    {
	      indi18_chkd = std::stoi(record.at(18));
	    }
	  catch(...)
	    {
	      indi18_chkd = 0;
	    }

	  try             			//19
	    {
	      indi19_chkd = std::stoi(record.at(19));
	    }
	  catch(...)
	    {
	      indi19_chkd = 0;
	    }

	  try             			//20
	    {
	      indi20_chkd = std::stoi(record.at(20));
	    }
	  catch(...)
	    {
	      indi20_chkd = 0;
	    }

	  try             			//21
	    {
	      indi21_chkd = std::stoi(record.at(21));
	    }
	  catch(...)
	    {
	      indi21_chkd = 0;
	    }

	  try             			//22
	    {
	      indi22_chkd = std::stoi(record.at(22));
	    }
	  catch(...)
	    {
	      indi22_chkd = 0;
	    }

	  try             			//23
	    {
	      indi23_chkd = std::stoi(record.at(23));
	    }
	  catch(...)
	    {
	      indi23_chkd = 0;
	    }

	  try             			//24
	    {
	      indi24_chkd = std::stoi(record.at(24));
	    }
	  catch(...)
	    {
	      indi24_chkd = 0;
	    }

	  try             			//25
	    {
	      indi25_chkd = std::stoi(record.at(25));
	    }
	  catch(...)
	    {
	      indi25_chkd = 0;
	    }

	  try             			//26
	    {
	      indi26_chkd = std::stoi(record.at(26));
	    }
	  catch(...)
	    {
	      indi26_chkd = 0;
	    }

	  try             			//27
	    {
	      indi27_chkd = std::stoi(record.at(27));
	    }
	  catch(...)
	    {
	      indi27_chkd = 0;
	    }


	  try             			//28
	    {
	      indi28_chkd = std::stoi(record.at(28));
	    }
	  catch(...)
	    {
	      indi28_chkd = 0;
	    }



      newProduct = struProduct{.CODIGO = indi0_chkd,.CODIGO_LER = indi1_chkd, .NOMBRE = record.at(2),.NOMBRE2 = record.at(3),
			       .NOMBRE3 = record.at(4),.PERMISO_PT = indi5_chkd,.CONTRATO_PT = indi6_chkd
			       ,.NPT_PT = indi7_chkd,.CB_PT = indi8_chkd
			       ,.CP_PT = indi9_chkd,.DCP_PT = indi10_chkd
			      ,.PERMISO_ET = indi11_chkd,.CONTRATO_ET = indi12_chkd
			       ,.NPT_ET = indi13_chkd,.CB_ET = indi14_chkd
			       ,.CP_ET = indi15_chkd,.DCP_ET = indi16_chkd 
			     ,.PERMISO_D5 = indi17_chkd,.CONTRATO_D5 = indi18_chkd
			       ,.NPT_D5 = indi19_chkd,.CB_D5 = indi20_chkd
			       ,.CP_D5 = indi21_chkd,.DCP_D5 = indi22_chkd
			       ,.PERMISO_SAL = indi23_chkd,.CONTRATO_SAL = indi24_chkd
			       ,.NPT_SAL = indi25_chkd,.CB_SAL = indi26_chkd
			       ,.CP_SAL = indi27_chkd,.DCP_SAL = indi28_chkd
			       ,.CARACTERISTICA_PELIGRO = record.at(29)};
      
      allProducts.push_back(newProduct);
    }
  return;

  
}

/*! function for returning complete name of products + code for
populating comboboxes, from database*/
std::vector<std::string> baseForm::ret_all_cos_4_combo(qtDatabase & my_database)
{
  char * sql =NULL;
  std::vector <std::vector <std::string>> data_return;
  std::vector <std::vector <std::string>>::iterator cos;
  std::vector<std::string>::iterator cos_field;
  int field = 0;
  std::string full_name;
  std::vector <std::string> costumers_name;
  long code;

  selAllDatFrmCostumers(sql);
  if(!my_database.query(NULL,sql))
    {
      data_return = my_database.retData2();
      for(cos = data_return.begin(); cos != data_return.end(); ++cos)
	{
	  full_name.clear();
	  code = 0;
	  for(cos_field = cos->begin(); cos_field != cos->end(); ++cos_field)
	    {
	      if(field == 0)
		{
		  try
		    {
		      code = std::stol(*cos_field);
		    }
		  catch(...)
		    {
		      code = 0;
		    }
		}
	      else if (field == 1)
		{
		  full_name += *cos_field;
		  full_name += " ";
		}	      
	      field++;
	    }
	  field = 0;
	  full_name += std::to_string(code);
	  costumers_name.push_back(full_name);
	}
	  	  	  
    }
  delete sql;
  return costumers_name;
}

/*! function for returning complete name of products + code for
populating comboboxes, from database, selected by plate*/
std::vector<std::string> baseForm::ret_all_cos_by_plate_4_combo(qtDatabase & my_database, std::string plate)
{
  char * sql =NULL;
  std::vector <std::vector <std::string>> data_return;
  std::vector <std::vector <std::string>>::iterator cos;
  std::vector<std::string>::iterator cos_field;
  int field = 0;
  std::string full_name;
  std::vector <std::string> costumers_name;
  long code;

  selAllDatFrmCostumers(sql);
  if(!my_database.query(NULL,sql))
    {
      data_return = my_database.retData2();
      for(cos = data_return.begin(); cos != data_return.end(); ++cos)
	{
	  full_name.clear();
	  code = 0;
	  for(cos_field = cos->begin(); cos_field != cos->end(); ++cos_field)
	    {
	      if(field == 0)
		{
		  try
		    {
		      code = std::stol(*cos_field);
		    }
		  catch(...)
		    {
		      code = 0;
		    }
		}
	      else if (field == 1)
		{
		  full_name += *cos_field;
		  full_name += " ";
		}	      
	      field++;
	    }
	  field = 0;
	  full_name += std::to_string(code);
	  costumers_name.push_back(full_name);
	}
	  	  	  
    }
  delete sql;
  return costumers_name;
}

std::vector<std::string> baseForm::retAllProds4Combo(qtDatabase & myDatabase)
{
    char * sql =NULL;
    std::vector <std::string> productsName;
 
    selAllProds(sql);
    if(!myDatabase.query(NULL,sql))
    {
        std::vector <std::vector <std::string>> dataReturn = myDatabase.retData2();
        std::vector <std::vector <std::string>>::iterator prod;
        for(prod = dataReturn.begin(); prod != dataReturn.end(); ++prod)
        {
            std::string fullName;
            long code = 0;
            int field = 0;
            std::vector<std::string>::iterator prodField;
            for(prodField = prod->begin(); prodField != prod->end(); ++prodField)
            {
                if(field == 0)
                {
                    try
                    {
                        code = std::stol(*prodField);
                    }
                    catch(...)
                    {
                        code = 0;
                    }
                }
                else if ((field == 2) || (field==3) || (field==4))
                {
                    fullName += *prodField;
                    fullName += " ";
                }	      
                field++;
            }
            fullName += std::to_string(code);
            productsName.push_back(fullName);
        }             
    }
    if (sql != NULL)
        delete[] sql;
    return productsName;
}

/*! function for returning the product code of a product, searched by full name*/
long baseForm::retProductCode(std::string fullName)
{

  std::vector<struProduct>::iterator iter;
  int found = 0;
  long productCode;
  std::string fullNameToCompare;

  for(iter = allProducts.begin(); iter != allProducts.end() && !found; iter++)
    {
      fullNameToCompare.clear();
      fullNameToCompare = iter->NOMBRE;
      fullNameToCompare += " ";
      fullNameToCompare += iter->NOMBRE2;
      fullNameToCompare += " ";
      fullNameToCompare += iter->NOMBRE3; 
      if(!fullNameToCompare.compare(fullName))
	{
	  productCode = iter->CODIGO;
	  found = 1;
	}
    }
  return productCode;
}
/*! function for returning the product full name, searched by its code*/
std::string baseForm::retProductFullName(long code)
{
  std::vector<struProduct>::iterator iter;
  int found = 0;
  std::string fullName;

  for(iter = allProducts.begin(); iter != allProducts.end() && !found; iter++)
    {
      if(iter->CODIGO == code)
	{
	  fullName = iter->NOMBRE;
	  fullName += " ";
	  fullName += iter->NOMBRE2;
	  fullName += " ";
	  fullName += iter->NOMBRE3; 
	  found = 1;
	}
    }
  return fullName;
}
/*! function for returning the LER code of a product, searched by full name*/
long baseForm::retProductLer(std::string fullName)
{

  std::vector<struProduct>::iterator iter;
  int found = 0;
  long productLer;
  std::string fullNameToCompare;

  for(iter = allProducts.begin(); iter != allProducts.end() && !found; iter++)
    {
      fullNameToCompare.clear();
      fullNameToCompare = iter->NOMBRE;
      fullNameToCompare += " ";
      fullNameToCompare += iter->NOMBRE2;
      fullNameToCompare += " ";
      fullNameToCompare += iter->NOMBRE3; 
      if(!fullNameToCompare.compare(fullName))
	{
	  productLer = iter->CODIGO_LER;
	  found = 1;
	}
    }
  return productLer;
}
/*! function for returning the dangerous characteristic of a product, searched by full name*/
std::string baseForm::retProductCaracteristica(std::string fullName)
{

  std::vector<struProduct>::iterator iter;
  int found = 0;
  std::string caracteristica;
  std::string fullNameToCompare;

  for(iter = allProducts.begin(); iter != allProducts.end() && !found; iter++)
    {
      fullNameToCompare.clear();
      fullNameToCompare = iter->NOMBRE;
      fullNameToCompare += " ";
      fullNameToCompare += iter->NOMBRE2;
      fullNameToCompare += " ";
      fullNameToCompare += iter->NOMBRE3; 
      if(!fullNameToCompare.compare(fullName))
	{
	  caracteristica = iter->CARACTERISTICA_PELIGRO;
	  found = 1;
	}
    }
  return caracteristica;
}

int baseForm::setProductByCode(long code, struMovement& myMovement)
{
  //TODO
  return 0;
}
int baseForm::setProductByIndex(long index, struMovement& myMovement)
{
  //TODO
  return 0;
}
/*! function to refresh all prdouct data from product code*/
int baseForm::setAllProductData(qtDatabase & myDatabase)
{
  char * sql;
  int ret = -1;
  std::vector<std::vector<std::string>> retData;
    
  selProdDataByCode(sql, retDepProdCode());
  if(!myDatabase.query(NULL,sql))
    {
      retData = myDatabase.retData2();
      if(retData.size())
	{
	  setDepProdDATA(retData[0]);		 
	  ret = 0;
	}  
    }
  return ret;
}
void baseForm::setDepProdDATA(std::vector <std::string> newDATA)
{
  std::vector<std::string>::iterator iter;
  int field=1;
  for(iter=newDATA.begin();iter!=newDATA.end();++iter)
    {
      if(field==1) //Nombre1
	setDepProdName1(*iter);
      else if(field==2) //Nombre2
	setDepProdName2(*iter);
      else if(field==3) //Nombre3
	setDepProdName3(*iter);
      else if(field==4) //Ler	
	{
	  try
	    {
	      setDepProdLER(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setDepProdLER(0);		
	    }
	}
      else if(field==5) //Descripcion de peligro
	setDepProdPeligro(*iter);
      else if(field == 6) //default price
	{
	  try
	    {
	      setDepPrice(std::stof(*iter));
	    }
	  catch(...)
	    {
	      setDepPrice(1.0);
	    }
	}
      field++;
    }
  return;
}
/*! function to refresh all prdouct data from product code*/
int baseForm::setAllArrProductData(qtDatabase & myDatabase)
{
  char * sql;
  int ret = -1;
  std::vector<std::vector<std::string>> retData;
    
  selProdDataByCode(sql, retArrProdCode());
  if(!myDatabase.query(NULL,sql))
    {
      retData = myDatabase.retData2();
      if(retData.size())
	{
	  setArrProdDATA(retData[0]);		 
	  ret = 0;
	}  
    }
  return ret;
}
void baseForm::setArrProdDATA(std::vector <std::string> newDATA)
{
  std::vector<std::string>::iterator iter;
  int field=1;
  for(iter=newDATA.begin();iter!=newDATA.end();++iter)
    {
      if(field==1) //Nombre1
	setArrProdName1(*iter);
      else if(field==2) //Nombre2
	setArrProdName2(*iter);
      else if(field==3) //Nombre3
	setArrProdName3(*iter);
      else if(field==4) //Ler	
	{
	  try
	    {
	      setArrProdLER(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setArrProdLER(0);		
	    }
	}
      else if(field==5) //Comunidad
	setArrProdPeligro(*iter);   
      field++;
    }
  return;
}
void baseForm::setArrCosProdPermitsBase(qtDatabase & myDatabase, const char* type)
{
  char * sql;
  std::vector<std::vector<std::string>> ourData;
  int ret = 0;

  resetArrProdPermits();
  selProdPermits(sql, type, retArrProdCode());
  if(!myDatabase.query(NULL,sql))
    {      
      ourData = myDatabase.retData2();
      if(ourData.size())
	{
	  ret = setArrPermitsFlags(ourData[0]);
	}
    }
  delete sql;
  if(!ret)
    {
      selProdCosPermits(sql, type, retArrProdCode(), retArrCosCode());
       if(!myDatabase.query(NULL,sql))
	 {      
	   ourData = myDatabase.retData2();
	   if(ourData.size())
	     {
	       ret = setArrPermits(ourData[0]);
	     }
	 }
       delete sql;
    }
}
int baseForm::setArrPermitsFlags(std::vector<std::string> ourData)
{
  int ret = 0;
  if(ourData.size() == 6)
    {
      //GENERAL
      try
	{
	  setArrPermitGralFlag(std::stoi(ourData[0]));
	}
      catch(...)
	{
	  ret = 1;
	  setArrPermitGralFlag(0);
	}	      
      //CONTRATO
      try
	{
	  setArrPermitDateFlag(std::stoi(ourData[1]));
	}
      catch(...)
	{
	  ret = 1;
	  setArrPermitGralFlag(0);
	}
      //NPT
      try
	{
	  setArrPermitNptFlag(std::stoi(ourData[2]));
	}
      catch(...)
	{
	  ret = 1;
	  setArrPermitNptFlag(0);
	}	      
      //CB
      try
	{
	  setArrPermitCbFlag(std::stoi(ourData[3]));
	}
      catch(...)
	{
	  ret = 1;
	  setArrPermitCbFlag(0);
	}	      
      //CP
      try
	{
	  setArrPermitCpFlag(std::stoi(ourData[4]));
	}
      catch(...)
	{
	  ret = 1;
	  setArrPermitCpFlag(0);
	}	      
      //DCP
      try
	{
	  setArrPermitDcpFlag(std::stoi(ourData[5]));
	}
      catch(...)
	{
	  ret = 1;
	  setArrPermitDcpFlag(0);
	}
    }
  else
    ret = 1;
  return ret;
}
int baseForm::setArrPermits(std::vector<std::string> ourData)
{
  int ret = 1;
  std::vector<std::string>::iterator iter;
  int field=0;
  
  for(iter = ourData.begin(); iter != ourData.end(); ++iter)
    {
      if(field==0)//CONTRATO
	setArrPermitDate(ourData[0]);
      else if (field == 1)//NPT
	{
	  try
	    {
	      setArrPermitNpt(std::stoul(ourData[1]));
	    }
	  catch(...)
	    {
	      ret = 1;
	      setArrPermitNpt(0);
	    }
	}
      else if(field==2)//CB
	{
	  try
	    {
	      setArrPermitCb(std::stoi(ourData[2]));
	    }
	  catch(...)
	    {
	      ret = 1;
	      setArrPermitCb(0);
	    }
	}
      else if(field==3)//CP
	{
	  try
	    {
	      setArrPermitCp(std::stoi(ourData[3]));
	    }
	  catch(...)
	    {
	      ret = 1;
	      setArrPermitCp(0);
	    }
	}
      else if(field==4)//DCP
	{
	  try
	    {
	      setArrPermitDcp(std::stoi(ourData[4]));
	    }
	  catch(...)
	    {
	      ret = 1;
	      setArrPermitDcp(0);
	    }
	}
      field++;
      ret = 0;
    }
  return ret;
}
int baseForm::isArrProdDatePermit()
{
  int ret = 1;  
  std::string date,current;


  if(retArrPermitDateFlag() >0)
    {
      date = retArrPermitDate();
      current = getCurrentDate();
      ret = compareDates(date, current);
      if(ret >=0)
	ret = 1;
      else
	ret = 0;
    }
  return ret;
}
int baseForm::isArrProdNptPermit()
{
  int ret = 1;
  if(retArrPermitNptFlag() > 0)
    {
      if(retArrPermitNpt() <= 0)	
	ret = 0;	  
    }
  return ret;
}
int baseForm::isArrProdCbPermit()
{
  int ret = 1;
  if(retArrPermitCbFlag() > 0)
    {
      if(retArrPermitCb() <= 0)	
	ret = 0;	  
    }
  return ret;
}
int baseForm::isArrProdCpPermit()
{
  int ret = 1;
  if(retArrPermitCpFlag() > 0)
    {
      if(retArrPermitCp() <= 0)	
	ret = 0;	  
    }
  return ret;
}
int baseForm::isArrProdDcpPermit()
{
  int ret = 1;
  if(retArrPermitDcpFlag() > 0)
    {
      if(retArrPermitDcp() <= 0)	
	ret = 0;	  
    }
  return ret;
}
////COSTUMER DATA
/*! functions to refresh all costumer data from costumer code*/
int baseForm::set_dep_p_costumer_data(qtDatabase & myDatabase, long code)
{
  char * sql;
  int ret = -1;
  std::vector<std::vector<std::string>> retData;
    
  selCosDataByCode(sql, code);
  if(!myDatabase.query(NULL,sql))
    {
      retData = myDatabase.retData2();
      if(retData.size())
	{
	  set_dep_p_costumer_data(retData[0]);
	  ret = 0;
	}  
    }
  return ret;

}
int baseForm::setAllDepCostumerData(qtDatabase & myDatabase)
{
  char * sql;
  int ret = -1;
  std::vector<std::vector<std::string>> retData;
    
  selCosDataByCode(sql, retDepCosCode());
  if(!myDatabase.query(NULL,sql))
    {
      retData = myDatabase.retData2();
      if(retData.size())
	{
	  setDepCosDATA(retData[0]);
	  ret = 0;
	}  
    }
  return ret;
}
int baseForm::setAllArrCostumerData(qtDatabase & myDatabase)
{
  char * sql;
  int ret = -1;
  std::vector<std::vector<std::string>> retData;
    
  selCosDataByCode(sql, retArrCosCode());
  if(!myDatabase.query(NULL,sql))
    {
      retData = myDatabase.retData2();
      if(retData.size())
	{
	  setArrCosDATA(retData[0]);
	  ret = 0;
	}  
    }
  return ret;
}
/*! function to refresh all costumer-product data
NPT is what we need*/
int baseForm::setAllDepCosProdData(qtDatabase & myDatabase,  station* myStation)
{
    int ret = -1;
    char * sql = NULL;
    std::string station_type;
    myStation->getType(station_type);
    sel_DIbasis_cos_prod(sql,station_type.c_str(), retDepCosCode(), retDepProdCode());
    if(!myDatabase.query(NULL,sql))
    {
        std::vector<std::vector<std::string>> retData = myDatabase.retData2();
        if(retData.size())
        {
            float price;
            std::vector <std::string> result = retData.at(0);
            try //NPT
            {
                setDepPermitNPT(std::stoul(result.at(0)));
            }
            catch(...)
            {
                setDepPermitNPT(0);	    
            }
            try //price
            {
                price = std::stof(result.at(1));
            }
            catch(...)
            {
                price = 0.0;
            }
            if(price > 0.0)
                setDepPrice(price);
            ret=0;
        }
        else
        {
            setDepPermitNPT(0);
            //no costumer - product price defined
        }
    }
    if (sql != NULL)
    {
        delete[] sql;
    }
    return ret;
}
int baseForm::setAllArrCosProdData(qtDatabase & myDatabase,  station* myStation)
{
  /*TODO IMPROVE FOR ALL PERMITS!*/
  int ret = -1;
  char * sql = NULL;
  std::vector<std::vector<std::string>> retData;

  std::string station_type;
  myStation->getType(station_type);
  sel_DIbasis_cos_prod(sql,station_type.c_str(), retArrCosCode(), retArrProdCode());
  if(!myDatabase.query(NULL,sql))
    {
      retData = myDatabase.retData2();
      if(retData.size())
	{
	  std::vector <std::string> result = retData.at(0);
	  try //NPT
	    {
	      setArrPermitNpt(std::stoul(result.at(0)));
	    }
	  catch(...)
	    {
	      setArrPermitNpt(0);	    
	    }
	  ret=0;
	}
      else
	setArrPermitNpt(0);
    }
  delete sql;
}
/*!
database dependant
 */
void baseForm::set_dep_p_costumer_data(std::vector <std::string> newDATA)
{
  std::vector<std::string>::iterator iter;
  int field=1;
  
  for(iter=newDATA.begin();iter!=newDATA.end();++iter)
    {
      if(field==1) //NOmbre
	setDepPCosName(*iter);
      else if(field==2) //NIF
	setDepPCosNif(*iter);
      else if(field==3) //DIRECCION
	setDepPCosAddr(*iter);
      else if(field==4) //PROVINCIA
	setDepPCosProv(*iter);
      else if(field==5) //POBLACIÓN
	setDepPCosCity(*iter);
      else if(field==6) //CP	
	{
	  try
	    {
	      setDepPCosZip(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setDepPCosZip(0);		
	    }
	}
      //  else if(field==9) //Type
      //	{
	  /*particular costumer has no type defined
	  try
	    {
	      setDepPCosTypeDef(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setDepPCosTypeDef(0);		
	    }
	  */
      //	}
      else if(field==10) //Comunidad
	setDepPCosReg(*iter);
      else if(field==11) //NIMA
	{
	  try
	    {
	      setDepPCosNima(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setDepPCosNima(0);		
	    }
	}
      else if(field==12) //NUM INSCRIPCIÓN EN EL REGISTRO
	{
	  try
	    {
	      setDepPCosNumIns(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setDepPCosNumIns(0);		
	    }
	}
      else if(field==13) //TELEFONO
	{
	  try
	    {
	      setDepPCosPhone(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setDepPCosPhone(0);		
	    }
	}     
      else if(field==14) //MAIL
        setDepPCosMail(*iter);     
      field++;
    }
  return;
}

void baseForm::setDepCosDATA(std::vector <std::string> newDATA)
{
  std::vector<std::string>::iterator iter;
  int field=1;
  for(iter=newDATA.begin();iter!=newDATA.end();++iter)
    {
      if(field==1) //NOmbre
	setDepCosName(*iter);
      else if(field==2) //NIF
	setDepCosNif(*iter);
      else if(field==3) //DIRECCION
	setDepCosAddr(*iter);
      else if(field==4) //PROVINCIA
	setDepCosProv(*iter);
      else if(field==5) //POBLACIÓN
	setDepCosCity(*iter);
      else if(field==6) //CP	
	{
	  try
	    {
	      setDepCosZip(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setDepCosZip(0);		
	    }
	}
      else if(field==9) //Type
	{
	  try
	    {
	      setDepCosTypeDef(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setDepCosTypeDef(0);		
	    }
	}
      else if(field==10) //Comunidad
	setDepCosReg(*iter);
      else if(field==11) //NIMA
	{
	  try
	    {
	      setDepCosNima(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setDepCosNima(0);		
	    }
	}
      else if(field==12) //NUM INSCRIPCIÓN EN EL REGISTRO
	{
	  try
	    {
	      setDepCosNumIns(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setDepCosNumIns(0);		
	    }
	}
      else if(field==13) //TELEFONO
	{
	  try
	    {
	      setDepCosPhone(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setDepCosPhone(0);		
	    }
	}     
      else if(field==14) //MAIL
        setDepCosMail(*iter);     
      field++;
    }
  return;
}
void baseForm::setArrCosDATA(std::vector <std::string> newDATA)
{
  std::vector<std::string>::iterator iter;
  int field=1;
  for(iter=newDATA.begin();iter!=newDATA.end();++iter)
    {
      if(field==1) //NOmbre
	setArrCosName(*iter);
      else if(field==2) //NIF
	setArrCosNif(*iter);
      else if(field==3) //DIRECCION
	setArrCosAddr(*iter);
      else if(field==4) //PROVINCIA
	setArrCosProv(*iter);
      else if(field==5) //POBLACIÓN
	setArrCosCity(*iter);
      else if(field==6) //CP	
	{
	  try
	    {
	      setArrCosZip(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setArrCosZip(0);		
	    }
	}
      else if(field==9) //Type
	{
	  try
	    {
	      setArrCosTypeDef(std::stoul(*iter));
	    }
	  catch (...)
	    {
	      setArrCosTypeDef(0);		
	    }
	}
      else if(field==10) //Comunidad
	setArrCosReg(*iter);
      else if(field==11) //NIMA
	{
	  try
	    {
	      setArrCosNima(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setArrCosNima(0);		
	    }
	}
      else if(field==12) //NUM INSCRIPCIÓN EN EL REGISTRO
	{
	  try
	    {
	      setArrCosNumIns(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setArrCosNumIns(0);		
	    }
	}
      else if(field==13) //TELEFONO
	{
	  try
	    {
	      setArrCosPhone(std::stol(*iter));
	    }
	  catch (...)
	    {
	      setArrCosPhone(0);		
	    }
	}     
      else if(field==14) //MAIL
        setArrCosMail(*iter);     
      field++;
    }
  return;
}
//Drivers Data
int baseForm::updteDrivers(qtDatabase& myDatabase)
{
    char * sql = NULL;
    int ret = -1;
    
    selAllDrivers(sql);
    if(!myDatabase.query(NULL,sql))
    {
        std::vector<std::vector<std::string>> dataReturn = myDatabase.retData2();
        resetDrivers();
        for(unsigned int i=0;i<dataReturn.size();i++)
        {
            insertDriver(dataReturn[i]);
        }
        ret = 0;
    }
    if (sql != NULL)
        delete[] sql;

    return ret;
}

//clears Drivers Data
void baseForm::resetDrivers()
{
  for (std::vector< driver* >::iterator it = allDrivers.begin() ; it != allDrivers.end(); ++it)
    {
      delete (*it);
    } 
  allDrivers.clear();
}

      
void baseForm::insertDriver(std::vector<std::string> record)
{

  long new_code;
  
  if(record.size() >=12)
    {
      //only code needed
      try             			//0
	{
	  new_code = std::stol(record.at(0));
	}
      catch(...)
	{
	  new_code = 0;
	}
      if(new_code)
	{
	  record.erase(record.begin()); //first element is code
	  allDrivers.push_back(new driver(record));
	  driver* iter = allDrivers.back();
	  iter->set_code(new_code);
	}
    }
  return;

}

std::vector<std::string> baseForm::retAllDriversNames()
{
  std::vector<driver*>::iterator iter;
  std::vector<std::string> names;
  names.clear();
  if(!allDrivers.empty())
    {
      for (iter = allDrivers.begin(); iter != allDrivers.end();++iter)
	{
	  names.push_back((*iter)->get_name());
	}
    }
  return names;
}


int baseForm::setDriverByName(std::string name)
{
  int ret = -1,done=0;
  std::vector<driver*>::iterator iter;
  iter = allDrivers.begin();
 
  while(iter != allDrivers.end() && !done)
    {
      if(!(*iter)->get_name().compare(name))
	{
	  if(dep_driver)
	    delete dep_driver;
	  dep_driver = new driver(*iter);
	  done=1;
	}
      ++iter;
    }

  return ret;
}

int baseForm::setDriverByCode(long code,qtDatabase & local_database)
{
  if(code > 0)
    {
      if(dep_driver)
	delete dep_driver;
      dep_driver = new driver(code, local_database);
    }
  else if (code == 0)
    {
      if(dep_driver)
	delete dep_driver;
      dep_driver = new driver();
      dep_driver->set_code(0);
    }
  else
    {
     if(dep_driver)
       dep_driver->reset();
     else
       dep_driver = new driver();
    }

  return 0;
}

int baseForm::default_driver(qtDatabase & local_database)
{
    int set = 0;

    if(retDepCosCode()>0)
    {
        char * sql = NULL;
        long driver_code = 0;
        std::vector< std::vector< std::string>> ret_data;
        sel_default_driver(sql,retDepCosCode());
        if(!local_database.query(NULL,sql))
        {
            ret_data = local_database.retData2();
            if(ret_data.size())
            {
                if(ret_data[0].size())
                {
                    try
                    {
                        driver_code = std::stol(ret_data[0][0]);
                    }
                    catch(...)
                    {
                        driver_code = 0;
                    }
                    if(driver_code)
                    {
                        set = 1;
                        if(dep_driver)
                            delete dep_driver;
                        dep_driver = new driver(driver_code, local_database);
                    }
                }
            }
        }
        delete [] sql;
    }   
    return set;
}

/*! function for returning a complete list external stations with format:
center.NAME + " " + center.CODE
to be used in comboboxes for example*/
std::vector<std::string> baseForm::retStationsLst(qtDatabase & myDatabase, int internal)
{
    char * sql = NULL;
    std::vector<std::string> myList;

    if(internal)
        selIntCentersNameCode(sql);
    else
        selExtCentersNameCode(sql);   
    if(!myDatabase.query(NULL,sql))
    {
        std::vector<std::vector<std::string>> myData = myDatabase.retData2();
        if(myData.size())
        {
            std::vector<std::vector<std::string>>::iterator row;
            std::string myText;
            std::vector<std::string>::iterator col;
            for(row = myData.begin(); row != myData.end(); ++row)
            {
                myText.clear();
                for(col = row->begin(); col != row->end(); ++col)
                {
                    myText += *col;
                    myText += " ";
                }
                myText = myText.substr(0,myText.size()-1);
                myList.push_back(myText);
            }
        }
    }
    if( sql != NULL)
        delete[] sql;
    return myList;
}
/*!function for getting the billing method*/
int baseForm::set_all_billing_info(qtDatabase & local_database)
{
  char* sql;
  unsigned int paying_method = 1; //paying method by cash
  std::string str_log_message;
  std::vector< std::vector< std::string>> returned_data;
  
  //paying method;
  if(retDepCosCode()>0)
    {
      sel_fp_by_cos_code(sql,retDepCosCode());
      str_log_message = "(DI DATA) local db -> ";
      str_log_message += sql;
      log_message(str_log_message, 1);
      if(!local_database.query(NULL,sql))
	{
	  log_message("(DI DATA) local OK", 1);
	  returned_data = local_database.retData2();
	  if(returned_data.size())
	    {
	      if(returned_data[0].size())
		 {
		   try
		     {
		       paying_method = std::stoi(returned_data[0][0]);
		     }
		   catch(...)
		     {
		       paying_method = 1;

		     }
		 }
	    }
	}
      else
	{
	  log_message("(DI DATA) local ERROR", 2);
	}
    }
  //setting paying method;
  setDepPayProcedure(paying_method);

  return 0;
}

/****RESET FUNCTIONS****/
void baseForm::resetArrCostumer()
{
  myArrMovement.CODIGO_CLIENTE = -1;
  myArrMovement.CLIENTE_NOMBRE.clear();
  myArrMovement.CLIENTE_NIF.clear();
  myArrMovement.CLIENTE_DIRECCION.clear();
  myArrMovement.CLIENTE_PROVINCIA.clear();
  myArrMovement.CLIENTE_POBLACION.clear();
  myArrMovement.CLIENTE_COMUNIDAD_AUTONOMA.clear();
  myArrMovement.CLIENTE_CP = 0;
  myArrMovement.CLIENTE_TIPO = 0;
  myArrMovement.CLIENTE_TIPO_DEF = 0;
  myArrMovement.CLIENTE_NIMA = 0;
  myArrMovement.CLIENTE_NUM_INSCRIPCION = 0;
  myArrMovement.CLIENTE_TELEFONO = 0;
  myArrMovement.CLIENTE_MAIL.clear();
}
void baseForm::resetDepCostumer()
{
  myDepMovement.CODIGO_CLIENTE = 0;
  myDepMovement.CLIENTE_NOMBRE.clear();
  myDepMovement.CLIENTE_NIF.clear();
  myDepMovement.CLIENTE_DIRECCION.clear();
  myDepMovement.CLIENTE_PROVINCIA.clear();
  myDepMovement.CLIENTE_POBLACION.clear();
  myDepMovement.CLIENTE_COMUNIDAD_AUTONOMA.clear();
  myDepMovement.CLIENTE_CP = 0;
  myDepMovement.CLIENTE_TIPO = 0;
  myDepMovement.CLIENTE_TIPO_DEF = 0;
  myDepMovement.CLIENTE_NIMA = 0;
  myDepMovement.CLIENTE_NUM_INSCRIPCION = 0;
  myDepMovement.CLIENTE_TELEFONO = 0;
  myDepMovement.CLIENTE_MAIL.clear();
}
void baseForm::resetArrProduct()
{
  myArrMovement.CODIGO_PRODUCTO = 0;
  myArrMovement.PRODUCTO_LER = 0;
  myArrMovement.PRODUCTO_NOMBRE.clear();
  myArrMovement.PRODUCTO_NOMBRE2.clear();
  myArrMovement.PRODUCTO_NOMBRE3.clear();
  myArrMovement.PRODUCTO_PELIGROSIDAD.clear();

  myArrMovement.CLIENTE_PRODUCTO_NPT = 0;
  resetArrProdPermits();
  incArrProdFz(0);
}
void baseForm::resetDepProduct()
{
  myDepMovement.CODIGO_PRODUCTO = 0;
  myDepMovement.PRODUCTO_LER = 0;
  myDepMovement.PRODUCTO_NOMBRE.clear();
  myDepMovement.PRODUCTO_NOMBRE2.clear();
  myDepMovement.PRODUCTO_NOMBRE3.clear();
  myDepMovement.PRODUCTO_PELIGROSIDAD.clear();

  myDepMovement.CLIENTE_PRODUCTO_NPT = 0;
  resetDepProdPermits();
  incDepProdFz(0);
}

void baseForm::resetArrScale()
{
  myArrMovement.PESO_ENTRADA = 0;
  incArrScaleEdited(0);
}

void baseForm::resetDepScale()
{
  myDepMovement.PESO_SALIDA = 0;
  myDepMovement.PESO_CARGA = 0;
  incDepScaleEdited(0); 
}

void baseForm::resetArrPlate()
{
  std::string emptyPlate;
  emptyPlate.clear();
  setArrPlate(emptyPlate);
  incArrPlateEdited(0);
  incArrPlateAuto(0);
  incArrParticular(0);
 
  std::string command;
  command ="rm \"";
  command += arrFolder;
  command += "/camara_entrada.png\"";
  system(command.c_str());
}
void baseForm::resetDepPlate()
{
  std::string emptyPlate;
  emptyPlate.clear();
  setDepPlate(emptyPlate);
  incDepPlateEdited(0);

  std::string command;
  command ="rm \"";
  command += arrFolder;
  command += "/camara_salida.png\"";
  system(command.c_str());
}


void baseForm::resetArrDi()
{
  std::string empty;

  empty.clear();
  setArrDi(empty);
  //rmArrDiFolder();
  clearArrDiFolder();
}
void baseForm::resetDepDi()
{
  std::string empty;

  empty.clear();
  setDepDi(empty);
  clearDepDiFolder();
}

void baseForm::resetArrOrigin()
{
  if(arrOriginStation != NULL)
    arrOriginStation->reset();
  else    
    arrOriginStation = new station();
}

void baseForm::resetDepOrigin()
{
  if(depOriginStation != NULL)
    depOriginStation->reset();
  else
    depOriginStation = new station();
}

void baseForm::resetArrDestination()
{
  if(arrDestinationStation != NULL)
    arrDestinationStation->reset();
  else
    arrDestinationStation = new station();
}

void baseForm::resetDepDestination()
{
  if(depDestinationStation != NULL)
    depDestinationStation->reset();
  else
    depDestinationStation = new station();
  
  incDestEdited(0);
}

void baseForm::resetOurId()
{
  if(ourId != NULL)
    {
      ourId->reset();
    }
  else
    ourId = new costumer();
}
/**************************/

/*! function for writting adaptative text in several lines, and flexible size for libharu*/
int baseForm::set_di_text(HPDF_Page & my_page,float font_size,int max_size, HPDF_Font my_font,std::string my_text,int start_x,int start_y)
{
  std::vector< std::string > paragraph;
  int ret = 0;

  if (my_text.length() > max_size) //2 lines
    {
      //recalculating max size and font size
      HPDF_Page_SetFontAndSize (my_page, my_font, font_size-1);
      max_size = (int)(max_size/(font_size-1)) * font_size;
      
      HPDF_Page_BeginText (my_page);
      paragraph = ret_paragraph_with_lines_return(my_text,max_size);
      my_text = paragraph.at(0);
      std::string my_text2 = paragraph.at(1);
      if (my_text2.length() >= 45)
	{
	  my_text2[45] = '\0';
	  my_text2[44] = '.';
	  my_text2[43] = '.';
	  my_text2[42] = '.';
	}
      HPDF_Page_MoveTextPos (my_page, start_x, start_y+7);
      HPDF_Page_ShowText (my_page, my_text.c_str());
      HPDF_Page_EndText (my_page);
      HPDF_Page_BeginText (my_page);
      HPDF_Page_MoveTextPos (my_page, start_x, start_y-4);
      HPDF_Page_ShowText (my_page, my_text2.c_str());
      ret = 1;
    }
  else //one line
    {
      HPDF_Page_BeginText (my_page);
      HPDF_Page_MoveTextPos (my_page, start_x, start_y);
      HPDF_Page_ShowText (my_page, my_text.c_str());       
    }
  HPDF_Page_EndText (my_page);
  HPDF_Page_SetFontAndSize (my_page, my_font, font_size);
  
  return ret;
}
