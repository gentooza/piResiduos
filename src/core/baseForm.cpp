/*
This file is part of PiResiduos.

Copyright 2017-2019, Prointegra SL.
Copyright 2019 Pixelada S. Coop. And <info (at) pixelada (dot) org>
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

/**
@file baseForm.cpp
*/
#include "baseForm.h"

baseForm::baseForm(int type, int entrance)
{
    clearMovement(myArrMovement);
    clearMovement(myDepMovement);
    //pointers
    arrCostumer = new costumer();
    depCostumer = new costumer();
    arrOriginStation = new station();
    depOriginStation = new station ();
    arrDestinationStation = new station ();
    depDestinationStation = new station ();
    ourId = NULL;
    ourStation = NULL;
    staff_in_charge = new staff();
    depDriver = new driver();
    depAuthCostumer = NULL;
    /**TODO BORRAR NO NECESARIO**/
    formType = NOT_DEFINED;
    if(type == ET || type == PT)
    {
        formType = type;
        formState = -1;
    }
    /*****************/

    //plate dimensions
    maxPlateLength = 8;
    minPlateLength = 5;

    //departure movement index in matrix
    depMovIndex = -1;

    // weights
    tareWeight = 0;
    grossWeight = 0;
    netWeight = 0;

    return;
}
baseForm::baseForm()
{
    clearMovement(myArrMovement);
    clearMovement(myDepMovement);
    arrCostumer = NULL;
    depCostumer = NULL;
    arrOriginStation = NULL;
    depOriginStation = NULL;
    arrDestinationStation = NULL;
    depDestinationStation = NULL;
    ourId = NULL;
    ourStation = NULL;
    staff_in_charge = new staff();
    depDriver = NULL;
    depAuthCostumer = NULL;
    // weights
    tareWeight = 0;
    grossWeight = 0;
    netWeight = 0;
    return;
}
baseForm::~baseForm()
{
    if (arrCostumer)
        delete arrCostumer;
    if (depCostumer)
        delete depCostumer;
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
    if(depDriver)
        delete depDriver;
    if(depAuthCostumer)
        delete depAuthCostumer;
    resetDrivers();
    return;
}
void baseForm::copyFrom(baseForm * toCopy)
{
    myArrMovement = toCopy->retArrMovement();
    myDepMovement = toCopy->retDepMovement();

    toCopy->retArrCostumer(arrCostumer);
    toCopy->retDepCostumer(depCostumer);
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
    toCopy->retDepDriver(depDriver);
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
    // weights
    tareWeight = toCopy->retTareWeight();
    grossWeight = toCopy->retGrossWeight();
    netWeight = toCopy->retNetWeight();
    return;
}

void baseForm::resetForm(int departure)
{
    std::cout << "cleaning form, departure: " << std::to_string(departure) << std::endl;
    resetOurId();
    if(!departure) //arrival
    {
        formInicState=0;
        //forzado producto
        iIncidents.clear();
        iComment.clear();
        clearMovement(myArrMovement);
        resetArrCostumer();
        resetArrOrigin();
        resetArrDestination();
        clearArrDiFolder();
    }
    else //Departure
    {
        oIncidents.clear();
        oComment.clear();
        clearMovement(myDepMovement);
        resetDepCostumer();
        resetDepOrigin();
        resetDepDestination();
        clearDepDiFolder();
        resetDepDriver();
        resetStaff();
    }
    // weights
    tareWeight = 0;
    grossWeight = 0;
    netWeight = 0;
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
    myMovement.TIPO_DE_MOVIMIENTO = -1;
    myMovement.REPETIR = 0;
    return;
}
/*!function loading to movement our order information*/
void baseForm::setArrMov(struMovement myOrder, qtDatabase & localDatabase)
{
    clearMovement(myArrMovement);
    myArrMovement = myOrder;
    // entities
    if(myOrder.CODIGO_CLIENTE > 0)
    {
        costumer* arrCostumer = NULL;
        arrCostumer = new costumer(myOrder.CODIGO_CLIENTE, localDatabase);
        setArrCostumer(arrCostumer);
        if (arrCostumer != NULL)
            delete arrCostumer;
    }
    setArrDateTime(getCurrentDate());

    return;
}

/*!prepare to save sql movement*/
std::string baseForm::storeMov(std::string & sqliteQuery, std::string & mysqlQuery,station *& myStation, qtDatabase & localDatabase)
{
    std::string movCode = getMovCode(localDatabase, myStation, retDepMovType());
    //almacenamos en movimientos
    std::string fields = "(CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, ";
    fields += "CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, CODIGO_BASCULISTA, PESO_NETO, ";
    fields += "PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, CENTRO_DESTINO, ";
    fields += "INCIDENCIAS,COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, ";
    fields += "CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, ";
    fields += "CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, ";
    fields += "CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, ";
    fields += "CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, ";
    fields += "CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, ";
    fields += "DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, ";
    fields += "DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, ";
    fields += "DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO, TIPO_CLIENTE, TRANSPORTISTA_NOMBRE, ";
    fields += "TRANSPORTISTA_NIF, TRANSPORTISTA_DIRECCION, TRANSPORTISTA_PROVINCIA, ";
    fields += "TRANSPORTISTA_POBLACION, TRANSPORTISTA_CP, TRANSPORTISTA_COMUNIDAD_AUTONOMA, ";
    fields += "TRANSPORTISTA_NIMA, TRANSPORTISTA_NUM_INSCRIPCION, TRANSPORTISTA_TELEFONO, ";
    fields += "TRANSPORTISTA_MAIL";
    sqliteQuery = "insert into MOVIMIENTOS " + fields + ", SINCRONIZADO) values (\"";
    mysqlQuery = "insert into movimientos " + fields + " ) values (\"";;
    //codigo movimiento
    std::string values = movCode;
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
    values += std::to_string(depCostumer->getCode());
    values += ",";
    values += std::to_string(retDepProdCode());
    values += ",";
    values += std::to_string(depDriver->getCode());
    values += ",";
    values += std::to_string(staff_in_charge->get_code());
    values += ",";
    values += std::to_string(retNetWeight());
    values += ",";
    values += std::to_string(retTareWeight());
    values += ",";
    values += std::to_string(retDepScaleOut());
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
    values += depCostumer->getName();
    values += "\",\"";
    values += depCostumer->getNif();
    values += "\",\"";
    values += depCostumer->getAddress();
    values += "\",\"";
    values += depCostumer->getProvence();
    values += "\",\"";
    values += depCostumer->getCity();
    values += "\",\"";
    values += std::to_string(depCostumer->getZip());
    values += "\",\"";
    values += depCostumer->getRegion();
    values += "\",\"";
    values += depCostumer->getNima();
    values += "\",\"";
    values += depCostumer->getNumIns();
    values += "\",\"";
    values += depCostumer->getPhone();
    values += "\",\"";
    values += depCostumer->getMail();
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
    values += "\",\"";
    values += std::to_string(depDestinationStation->getZip());
    values += "\",\"";
    values += depDestinationStation->getRegion();
    values += "\",\"";
    values += depDestinationStation->getNima();
    values += "\",\"";
    values += depDestinationStation->getNumIns();
    values += "\",\"";
    values += depDestinationStation->getPhone();
    values += "\",\"";
    values += depDestinationStation->getMail();
    values += "\",";
    values += std::to_string(depCostumer->getType());
    values += ",\"";
    values += depDriver->getName();
    values += "\",\"";
    values += depDriver->getNif();
    values += "\",\"";
    values += depDriver->getAddress();
    values += "\",\"";
    values += depDriver->getProvence();
    values += "\",\"";
    values += depDriver->getCity();
    values += "\",\"";
    values += std::to_string(depDriver->getZip());
    values += "\",\"";
    values += depDriver->getRegion();
    values += "\",\"";
    values += depDriver->getNima();
    values += "\",\"";
    values += depDriver->getNumIns();
    values += "\",\"";
    values += depDriver->getPhone();
    values += "\",\"";
    values += depDriver->getMail();
    values += "\"";
    sqliteQuery += values;
    sqliteQuery += ",0)";
    mysqlQuery += values;
    mysqlQuery += ")";

    return movCode;
}
/*!  Folder creation for saving images, signatures, files... 
 inputs DI code for folder generation, arrive flag if arriving or leaving facility */
int baseForm::createDIFolder(std::string DI, int arrive)
{
    int ret = 0;
    std::string folder;
    if(arrive)
    {
        if(retArrDiFolder().empty())
        {
            if(retArrDateTime().empty())
                setArrDateTime(getCurrentDate());

            folder = DI + " " + retArrDateTime();
            setArrDiFolder(folder);
            ret = 1;
        }
    }
    else
    {
        if(retDepDiFolder().empty())
        {
            if(retDepDateTime().empty())
                setDepDateTime(getCurrentDate());

            folder = DI + " " + retDepDateTime();
            setDepDiFolder(folder);
            ret = 1;
        }
    }

    return ret;
}
void baseForm::savePlateImage(int pos,const char* entrada_salida)
{
    int ret;
    // std::cout << "debug: inside saveArrPlateImage()" << std::endl;
    ret = system("mkdir -p saves");

    std::string command = "mkdir -p \"";
    command += arrFolder + "\"";
    // std::cout << "TERMINAL COMMAND: "<< command << std::endl;
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
    ret = system("mkdir -p saves");

    std::string command = "mkdir -p \"";
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
    ret = system("mkdir -p saves");

    std::string command = "mkdir -p ";
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

void baseForm::backupFiles(std::string movFolder, int entranceMov)
{
    int ret;
    ret = system("mkdir -p backup");

    std::string command = "mkdir -p \"backup/";
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
    std::cout << "backing up files to server? is retDepMovtype != DEF_MOV_TRANSFER?" << retDepMovType() << "!=" << DEF_MOV_TRANSFER << std::endl;
    std::cout << "OR It's an entrance? " << entranceMov << std::endl;
    if((retDepMovType() != DEF_MOV_TRANSFER) || entranceMov)
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

/*! function for returning complete name of products + code for
populating comboboxes, from database*/
std::vector<std::string> baseForm::ret_all_cos_4_combo(qtDatabase & my_database)
{
    char * sql = NULL;
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
    if (sql != NULL)
        delete [] sql;
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
/*! function to refresh all prdouct data from product code*/
int baseForm::setAllProductData(qtDatabase & myDatabase)
{
    char * sql = NULL;
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
    if (sql != NULL)
        delete [] sql;
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
    char * sql = NULL;
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
    if (sql != NULL)
        delete [] sql;
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
    std::string sql;
    std::vector<std::vector<std::string>> ourData;
    int ret = 0;

    resetArrProdPermits();
    selProdPermits(sql, type, retArrProdCode());
    if(!myDatabase.query(NULL, sql.c_str()))
    {
        ourData = myDatabase.retData2();
        if(ourData.size())
        {
            ret = setArrPermitsFlags(ourData[0]);
        }
    }
    if(!ret)
    {
        selProdCosPermits(sql, type, retArrProdCode(), retArrCosCode());
        if(!myDatabase.query(NULL, sql.c_str()))
        {
            ourData = myDatabase.retData2();
            if(ourData.size())
            {
                ret = setArrPermits(ourData[0]);
            }
        }
    }
    return;
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
                setArrPermitNpt(ourData[1]);
            }
            catch(...)
            {
                ret = 1;
                setArrPermitNpt("");
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
        if(retArrPermitNpt().empty())
            ret = 0;
    }
    return ret;
}

int baseForm::isDepProdNptPermit()
{
    int ret = 1;
    if(retDepPermitNptFlag() > 0)
    {
        if(retDepPermitNpt().empty())
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

int baseForm::setAllArrCostumerData(qtDatabase & myDatabase)
{
    std::string sql;
    int ret = -1;
    std::vector<std::vector<std::string>> retData;

    selCosDataByCode(sql, retArrCosCode());
    if(!myDatabase.query(NULL, sql.c_str()))
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
    std::vector<std::vector<std::string>> retData;
    float price;

    std::string station_type;
    myStation->getType(station_type);
    sel_DIbasis_cos_prod(sql, station_type.c_str(), depCostumer->getCode(), retDepProdCode());
    if(!myDatabase.query(NULL,sql))
    {
        retData = myDatabase.retData2();
        if(retData.size())
        {
            std::vector <std::string> result = retData.at(0);
            //NPT
            setDepPermitNpt(result.at(0));
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
            setDepPermitNpt("");
            //no costumer - product price defined
        }
    }
    if (sql)
    {
        delete [] sql;
        sql = NULL;
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
            //NPT
            setArrPermitNpt(result.at(0));
        }
        else
            setArrPermitNpt("");
    }
    delete sql;
    return ret;
}

void baseForm::setArrCosDATA(std::vector <std::string> newDATA)
{
    std::vector<std::string>::iterator iter;
    int field=0;
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
    std::string sql;
    int ret = -1;
    selAllDrivers(sql);
    if(!myDatabase.query(NULL, sql.c_str()))
    {
        std::vector<std::vector<std::string>> dataReturn = myDatabase.retData2();
        resetDrivers();
        for(unsigned int i=0;i<dataReturn.size();i++)
        {
            insertDriver(dataReturn[i]);
        }
        ret = 0;
    }
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
    try
    {
        allDrivers.push_back(new driver(record));
    }
    catch(...)
    {
        std::cout << "baseForm::insertDriver, NOT a driver database data row provided, passing..." << std::endl;
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
            names.push_back((*iter)->getName());
        }
    }
    return names;
}

int baseForm::setDriverByName(std::string name)
{
    int ret = 0;
    std::vector<driver*>::iterator iter;
    iter = allDrivers.begin();

    while(iter != allDrivers.end() && !ret)
    {
        if(!(*iter)->getName().compare(name))
        {
            if(depDriver)
                delete depDriver;
            depDriver = new driver(*iter);
            ret = 1;
        }
        ++iter;
    }
    return ret;
}

int baseForm::setDriverByCode(long code, qtDatabase & local_database)
{
    if(code > 0)
    {
        if(depDriver)
            delete depDriver;
        depDriver = new driver(code, local_database);
    }
    else
    {
        if(depDriver)
            depDriver->reset();
        else
            depDriver = new driver();
    }
    return 0;
}

int baseForm::default_driver(qtDatabase & local_database)
{
    int set = 0;
    long costumerCode = depCostumer->getCode();

    if(costumerCode > 0)
    {
        char * sql = NULL;
        long driver_code = 0;
        std::vector< std::vector< std::string>> ret_data;
        sel_default_driver(sql, costumerCode);
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
                        if(depDriver)
                            delete depDriver;
                        depDriver = new driver(driver_code, local_database);
                    }
                }
            }
        }
        if (sql)
        {
            delete [] sql;
            sql = NULL;
        }
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
    unsigned int paying_method = 1; //paying method by cash
    long costumerCode = depCostumer->getCode();

    if(costumerCode > 0)
    {
        char* sql = NULL;
        std::string str_log_message;
        std::vector< std::vector< std::string>> returned_data;

        sel_fp_by_cos_code(sql, costumerCode);
        str_log_message = "(DI DATA) local db -> ";
        str_log_message += sql;
        log_message(str_log_message, 1);
        if(!local_database.query(NULL, sql))
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
        if(sql)
        {
            delete [] sql;
            sql = NULL;
        }
    }
    //setting paying method;
    setDepPayProcedure(paying_method);
    return 0;
}

std::string baseForm::getLastMovCode(qtDatabase &localDatabase, station *myStation)
{
    std::string sql;
    std::string lastMovCode = "0";

    //getting last movement code for this station and DI
    std::string sCodigo_estacion = std::to_string(myStation->getCode());
    selLastMovCode(sql, sCodigo_estacion);
    localDatabase.query(NULL, sql.c_str());

    std::vector<std::vector<std::string>> ourData = localDatabase.retData2();
    if(ourData.size())
    {
        lastMovCode = ourData.at(0).at(0);
    }
    return lastMovCode;
}

///
std::string baseForm::getMovCode(qtDatabase & myDatabase, station *myStation, int movementTypeCode)
{
    std::string sLastCode = getLastMovCode(myDatabase, myStation);
    long lastCode = std::stol(sLastCode);
    std::string newCode;
    std::string str_station_code = std::to_string(myStation->getCode());

    if (lastCode > 0 && sLastCode.size() > 11)
    {
        // std::cout << "(DEBUG) Have last code = " << lastCode << std::endl;
        std::string prefix = sLastCode.substr(0,sLastCode.size()-7);
        std::string sIndex = sLastCode.substr(sLastCode.size()-7,6);

        std::string prefix_year = prefix.substr(0,4);
        long index = std::stol(sIndex);
        index++;
        if(index > 999999)
            index = 999999;
        std::string newIndex = zeroPadNumber(index,6);
        newCode = prefix_year + str_station_code + newIndex + std::to_string(movementTypeCode);
        // std::cout << "(DEBUG) newcode is: (prefix_year)" << prefix_year << " (str_station_code)" << str_station_code;
        // std::cout << " (newIndex)" << newIndex << "(movementTypeCode)" << std::to_string(movementTypeCode) << std::endl;
    }
    else
    {
        // std::cout << "(DEBUG) NO last code!!" << lastCode << std::endl;
        time_t myTime = time(NULL);
        struct tm *aTime = localtime(&myTime);
        int year = aTime->tm_year + 1900;

        newCode = std::to_string(year) + str_station_code + "000001" + std::to_string(movementTypeCode);
        // std::cout << "(DEBUG) newcode is: (year)" << std::to_string(year) << " (str_station_code)" << str_station_code;
        // std::cout << " 000001" << "(movementTypeCode)" << std::to_string(movementTypeCode) << std::endl;
    }
    return newCode;
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

    if(arrCostumer != NULL)
        arrCostumer->reset();
    else
        arrCostumer = new costumer();
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

    if(depCostumer != NULL)
        depCostumer->reset();
    else
        depCostumer = new costumer();
}
void baseForm::resetArrProduct()
{
  myArrMovement.CODIGO_PRODUCTO = 0;
  myArrMovement.PRODUCTO_LER = 0;
  myArrMovement.PRODUCTO_NOMBRE.clear();
  myArrMovement.PRODUCTO_NOMBRE2.clear();
  myArrMovement.PRODUCTO_NOMBRE3.clear();
  myArrMovement.PRODUCTO_PELIGROSIDAD.clear();

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
void baseForm::resetStaff()
{
    if(staff_in_charge != NULL)
        staff_in_charge->reset();
    else
        staff_in_charge = new staff();
}
void baseForm::resetDepDriver()
{
    if(depDriver != NULL)
        depDriver->reset();
    else
        depDriver = new driver();
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
