/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
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
@file baseForm.h
Facade class for managing every entity in database
*/
#ifndef _BASE_FORM_
#define _BASE_FORM_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cups/cups.h>
#include <unistd.h>

#include <math.h>
#include <setjmp.h>
#include "hpdf.h"
#include "generic_tools.h"
#include "qtdatabase.h"
#include "database.h"
#include "station.h"
#include "costumer.h"
#include "staff.h"
#include "driver.h"
#include "printable.h"
#include "printableTicket.h"
#include "printableDi.h"


enum
{
    NOT_DEFINED = -1,
    ET = 1,
    PT,
};


enum
{
    DEF_MOV_UNLOADING = 1,
    DEF_MOV_TRANSFER,
    DEF_MOV_LOADING,
    DEF_MOV_TODEPOSITD5,
};

enum //form type
{
    VOID_FORM = 0,
    DISCHARGE_FORM,
    LOAD_FORM,
};

typedef struct struPermits
{
    int FLAG_GENERAL;
    
    int FLAG_CONTRATO;
    std::string CONTRATO;
    
    int FLAG_NPT;
    std::string NPT;
    
    int FLAG_CP;
    int CP;
    
    int FLAG_CB;
    int CB;
    
    int FLAG_DCP;
    int DCP;
};
static struPermits resetPermits()
{
    struPermits myPermits = {0,0,"",0,"",0,0,0,0,0,0};
    return myPermits;
}

typedef struct struMovement
{
    long CODIGO_CLIENTE;
    std::string CLIENTE_NOMBRE;
    std::string CLIENTE_NIF;
    std::string CLIENTE_DIRECCION;
    std::string CLIENTE_PROVINCIA;
    std::string CLIENTE_POBLACION;
    std::string CLIENTE_COMUNIDAD_AUTONOMA;
    long CLIENTE_CP;
    int CLIENTE_TIPO;
    int CLIENTE_TIPO_DEF;
    long CLIENTE_NIMA;
    long CLIENTE_NUM_INSCRIPCION;
    long CLIENTE_TELEFONO;
    std::string CLIENTE_MAIL;

    long CLIENTE_PARTICULAR_CODIGO_CLIENTE;
    std::string CLIENTE_PARTICULAR_NOMBRE;
    std::string CLIENTE_PARTICULAR_NIF;
    std::string CLIENTE_PARTICULAR_DIRECCION;
    std::string CLIENTE_PARTICULAR_PROVINCIA;
    std::string CLIENTE_PARTICULAR_POBLACION;
    std::string CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA;
    long CLIENTE_PARTICULAR_CP;
    int CLIENTE_PARTICULAR_TIPO;
    int CLIENTE_PARTICULAR_TIPO_DEF;
    long CLIENTE_PARTICULAR_NIMA;
    long CLIENTE_PARTICULAR_NUM_INSCRIPCION;
    long CLIENTE_PARTICULAR_TELEFONO;
    std::string CLIENTE_PARTICULAR_MAIL;
    
    long CODIGO_PRODUCTO;
    long PRODUCTO_LER;
    std::string PRODUCTO_NOMBRE;
    std::string PRODUCTO_NOMBRE2;
    std::string PRODUCTO_NOMBRE3;
    std::string PRODUCTO_PELIGROSIDAD;

    long CLIENTE_PRODUCTO_NPT;

    long CODIGO_ORDEN;
    int ECOEMBES;
    std::string FECHA_FIRMA;
    std::string FECHA_PROGRAMADA;
    float PRECIO_TN;
    int FORMA_DE_PAGO;
    unsigned int PESO_A_RETIRAR;
    std::string OPERACION_DE_TRATAMIENTO;
    std::string FECHA_HORA;
    std::string FECHA_HORA_FINAL;
    std::string MATRICULA;
    std::string IMAGEN_MATRICULA;
    std::string REMOLQUE;
    struPermits PERMISOS_PRODUCTO;
    std::string DI;
    unsigned int PESO_ENTRADA;
    unsigned int PESO_SALIDA;
    int TIPO_DE_MOVIMIENTO;
    int REPETIR;

    long CODIGO_ORIGEN;
};

class  baseForm 
{
    public:
        baseForm(int type, int);
        baseForm(); 
        virtual ~baseForm();

        void copyFrom(baseForm *reference);
        virtual void resetForm(int departure);
        //state navigation
        virtual int setState(int state){ formState = state; (state>=1000?formFinalState=state:formInicState=state); return 0;};
        virtual int getState(){return formState;};  
        int printType();
        virtual int retForm(){return formSCADA;};
        virtual int getFormType(){return VOID_FORM;};
        void clearMovement(struMovement & myMovement);
        virtual int storeTransit(qtDatabase & myDatabase,qtDatabase & remoteDatabase, station * myStation, int remote_host_connected){return -1;};
        virtual int delTransit(int index, std::string plate, qtDatabase & myDatabase, qtDatabase & myRemoteDatabase, std::string host, int port, long station_code){return -1;};
        std::string storeMov(std::string& localSql,std::string& remoteSql,station *& myStation, qtDatabase & localDatabase);

        virtual int storeDepMov(qtDatabase & localDatabase,qtDatabase & remoteDatabase, int remote_host_connected){return -1;};
        virtual int storeDepTransfer(qtDatabase & my_local_database, qtDatabase & my_remote_database, int remote_host_connected){return -1;};
        //plates
        virtual int isArrPlateOk(){int ret;(retArrPlate().empty()?ret=0:ret=1); return ret;};
        int isArrPlateRegistered(qtDatabase & myDatabase);
        void savePlateImage(int pos,const char* entrada_salida);
        /////////////
            
        //product permits
        virtual void setProductPermits(std::vector <std::string> permits);
        virtual int checkPermisos();
        //
        //forzados incidentes
        void checkInIncident(int edited,std::string incidentCode, std::string message);
        void checkOutIncident(int edited,std::string incidentCode, std::string message);
        int isInIncident(std::string incidentCode);
        int isOutIncident(std::string incidentCode); 
        ////plates
        void incArrPlateEdited(int edited);
        int isIncArrPlateEdited();
        void incDepPlateEdited(int edited);
        int isIncDepPlateEdited();
        ////special costumers
        void incArrPlateAuto(int edited);
        int isIncArrPlateAuto();
        void incArrParticular(int edited);
        int isIncArrParticular();
        ////products
        void incArrProdFz(int edited);
        int isIncArrProdFz();
        void incDepProdFz(int edited);
        int isIncDepProdFz(); 
        ////scales
        void incArrScaleEdited(int edited);
        int isIncArrScaleEdited();  
        void incDepScaleEdited(int edited);
        int isIncDepScaleEdited();
        ////destination manually edited
        void incDestEdited(int edited);
        int isIncDestEdited();
        ////movimiento sin firmar
        void incNoSigned(int edited);
        int isIncNoSigned();  
        
        void setInputIncidents(std::vector<std::string> newIncidents){iIncidents = newIncidents; return;};
        void setOutputIncidents(std::vector<std::string> newIncidents){oIncidents = newIncidents; return;};
        std::vector <std::string> getInputIncidents(){return iIncidents;};
        std::vector <std::string> getOutputIncidents(){return oIncidents;};
        void inputConcatenate(std::vector<std::string> newIncidents);
        void outputConcatenate(std::vector<std::string> newIncidents);
        ////products 
        virtual void forceCurrentProduct(){};
        virtual void unforceCurrentProduct(){};
        virtual int getFzCurrentProduct(){return 0;}
        //
        void setDatePermit(std::string strdate);

        //DI CODE GENERATION
        virtual std::string createDINumber(qtDatabase & localDatabase, qtDatabase & remoteDatabase, int arrive){return "";};
        std::string createArrDi(qtDatabase & localDatabase);
        std::string createDepDi(qtDatabase & localDatabase);
        std::string generateDi(std::string lastDi, int arrive);

        //FOLDER TO SAVE CAPTURES, SIGNATURE, DI...
        void setArrDiFolder(std::string folder){arrFolder = "saves/" + folder; return;};
        void clearArrDiFolder(){arrFolder.clear(); return;};
        void rmArrDiFolder(){if(!arrFolder.empty()){std::string command = "rm -r \"" +arrFolder +"\""; system(command.c_str());}};
        std::string retArrDiFolder(){return arrFolder;};
        void setDepDiFolder(std::string folder){depFolder = "saves/" + folder; return;};
        void clearDepDiFolder(){depFolder.clear(); return;};
        void rmDepDiFolder(){if(!depFolder.empty()){std::string command = "rm -r \""+depFolder +"\""; system(command.c_str());}};
        std::string retDepDiFolder(){return depFolder;};  
        
        //DI INFORMATION
        virtual void setAllDiData(qtDatabase & localDatabase,station  *myStation, long ourCode, long defDriverCode) {return;};
        virtual int isDiComplete(){return 0;};
        virtual int set_all_billing_info(qtDatabase & local_database);//virtual implemented
        
        //OPERATOR COMMENTS
        void setInputComment(std::string comment){iComment = comment;};
        std::string getInputComment(){return iComment;};
        void setOutputComment(std::string comment){oComment = comment;};
        std::string getOutputComment(){return oComment;};

        //OPERATOR INFO
        int isStaffConfigured(){return staff_in_charge->get_status();};
        void setStaff(long code, qtDatabase & localDatabase){staff_in_charge->setStaff(code, localDatabase); return;};
        void unsetStaff(){staff_in_charge->set_status(-1);};
        long ret_staff_code(){long my_id; (staff_in_charge?my_id = staff_in_charge->get_code():my_id=-1); return my_id;};
        
        //arrive of unload movements managment
        virtual void setUnloadMov(){setArrMovType(DEF_MOV_UNLOADING);};
        
        //arrive of transfer movements managment
        virtual int isTrf(qtDatabase & myDatabase, station*& myStation){ return -1;};
        virtual int setTrfMov(qtDatabase & myDatabase, station *& myStation){return -1;};
        //virtual int setTrfMov(int){return -1;};
        virtual void setTransferMov(costumer *& myCostumer, station *& myStation){};
        //
        //TODO
        //virtual void setOrders(qtDatabase & myDatabase, long station_code){return 0;};
        //
        virtual void setOrders(qtDatabase & myDatabase, long station_code){return;};
        virtual std::vector<std::string> retOrdersTable(){std::vector<std::string> empty; return empty;};
        virtual std::vector<struMovement> retOrders(){std::vector<struMovement> empty; return empty;};
        virtual struMovement selOrder(unsigned int index){struMovement myOrder; return myOrder;};
        void setArrMov(struMovement myOrder);

        virtual void setTransit(std::vector<std::vector<std::string>> transit){return;};
        virtual std::vector<std::vector<std::string>> retTransit(){std::vector<std::vector<std::string>> empty; return empty;};
        virtual int isPlateInTransit(std::string){return 0;};
        virtual int setTransitMov(int,std::string,qtDatabase & myDatabase) {return 0;};
        virtual int isArrMov(){return 0;};
        
        virtual void setDepMov(std::vector<std::vector<std::string>> transit){return;};
        virtual void setDepMov(int index){ return;};
        virtual std::vector<std::vector<std::string>> retDepMov(){std::vector<std::vector<std::string>> empty; return empty;};
        int retDepMovIndex(){return depMovIndex;};
        virtual void clearArrMov(){return;};
        virtual void clearDepMov(){return;};
        //
        //codigo movimiento
        std::string getLastMovCode(qtDatabase &localDatabase, station *myStation);
        std::string getMovCode(qtDatabase & myDatabase, station *myStation, int movementTypeCode);
        // virtual int setMovCode(std::string lastCode, int stationCode, int movementTypeCode){return 0;};
        //
        
        virtual void saveSignature(int blank_signature = 0);
        virtual void saveSignature(const char* file);  
        virtual int isSignature();
        virtual void createPdf(std::string printerId){};
        virtual int createTicket(std::string printerId, std::string ticketCode, qtDatabase & localDatabase){};
        int set_di_text(HPDF_Page & my_page,float font_size,int max_size, HPDF_Font my_font,std::string my_text,int start_x,int start_y);
        void backupFiles(std::string movFolder);

        //test
        int showPermisos();
        //
        
        //drivers
        int updteDrivers(qtDatabase& myDatabase);
        void resetDrivers();
        std::vector<std::string> retAllDriversNames();
        void insertDriver(std::vector<std::string> record);

        //costumers
        // TODO: rename and / or move it out here
        std::vector<std::string> ret_all_cos_4_combo(qtDatabase & my_database);
        //
        //products
        //TODO all accesing database by taking care of station, permits, etc.
        std::vector<std::string> retAllProds4Combo(qtDatabase & myDatabase);
        //
        ///////////////////////////////////////////////////
        //MOVEMENTS DATA RETURN/SET
        ///////////////////////////////////////////////////
        struMovement retArrMovement(){return myArrMovement;};
        struMovement retDepMovement(){return myDepMovement;};  
        ////COSTUMER DATA
        costumer* arrCostumer;
        costumer* depCostumer;
        void setArrCostumer(costumer* newCostumer){if(arrCostumer) delete arrCostumer; arrCostumer = new costumer(); *arrCostumer = *newCostumer; return;}; 
        void setDepCostumer(costumer* newCostumer){if(depCostumer) delete depCostumer; depCostumer = new costumer(); *depCostumer = *newCostumer; return;};
        void retArrCostumer(costumer *& newCostumer){ (arrCostumer?newCostumer = new costumer(arrCostumer):newCostumer = new costumer());};
        void retDepCostumer(costumer *& newCostumer){ (depCostumer?newCostumer = new costumer(depCostumer):newCostumer = new costumer());};

        void setOurCosDATA(long code, qtDatabase &myDatabase);
        void setArrCosDATA(std::vector <std::string> newDATA);
        int setAllArrCostumerData(qtDatabase & myDatabase);
        int setAllDepCosProdData(qtDatabase & myDatabase, station* myStation);
        int setAllArrCosProdData(qtDatabase & myDatabase, station* myStation); 
        //costumer's code
        long retArrCosCode(){return  myArrMovement.CODIGO_CLIENTE;};
        void setArrCosCode(long code){myArrMovement.CODIGO_CLIENTE = code; return;};
        ////particular
        //costumer's name
        std::string retArrCosName(){return myArrMovement.CLIENTE_NOMBRE;};
        void setArrCosName(std::string name){myArrMovement.CLIENTE_NOMBRE = name;};
        ////particular
        std::string retArrPCosName(){return myArrMovement.CLIENTE_PARTICULAR_NOMBRE;};
        void setArrPCosName(std::string name){myArrMovement.CLIENTE_PARTICULAR_NOMBRE = name;}; 
        //costumer's nif
         std::string retArrCosNif(){return myArrMovement.CLIENTE_NIF;};
        void setArrCosNif(std::string nif){myArrMovement.CLIENTE_NIF = nif;};
        ////particular
        std::string retArrPCosNif(){return myArrMovement.CLIENTE_PARTICULAR_NIF;};
        void setArrPCosNif(std::string nif){myArrMovement.CLIENTE_PARTICULAR_NIF = nif;};  
        //costumer's address
        std::string retArrCosAddr(){return myArrMovement.CLIENTE_DIRECCION;};
        void setArrCosAddr(std::string address){myArrMovement.CLIENTE_DIRECCION = address;};
        ////particular
        std::string retArrPCosAddr(){return myArrMovement.CLIENTE_PARTICULAR_DIRECCION;};
        void setArrPCosAddr(std::string address){myArrMovement.CLIENTE_PARTICULAR_DIRECCION = address;};  
        //costumer's provence
        std::string retArrCosProv(){return myArrMovement.CLIENTE_PROVINCIA;};
        void setArrCosProv(std::string provence){myArrMovement.CLIENTE_PROVINCIA = provence;};
        ////particular
        std::string retArrPCosProv(){return myArrMovement.CLIENTE_PARTICULAR_PROVINCIA;};
        void setArrPCosProv(std::string provence){myArrMovement.CLIENTE_PARTICULAR_PROVINCIA = provence;};
        //costumer's city
        std::string retArrCosCity(){return myArrMovement.CLIENTE_POBLACION;};
        void setArrCosCity(std::string city){myArrMovement.CLIENTE_POBLACION = city;};
        ////particular
        std::string retArrPCosCity(){return myArrMovement.CLIENTE_PARTICULAR_POBLACION;};
        void setArrPCosCity(std::string city){myArrMovement.CLIENTE_PARTICULAR_POBLACION = city;};  
        //costumer's region
        std::string retArrCosReg(){return myArrMovement.CLIENTE_COMUNIDAD_AUTONOMA;};
        void setArrCosReg(std::string region){myArrMovement.CLIENTE_COMUNIDAD_AUTONOMA = region;};
        ////particular
        std::string retArrPCosReg(){return myArrMovement.CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA;};
        void setArrPCosReg(std::string region){myArrMovement.CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA = region;}; 
        //costumer's zip
        long retArrCosZip(){return  myArrMovement.CLIENTE_CP;};
        void setArrCosZip(long zip){myArrMovement.CLIENTE_CP = zip;};
        ////particular
        long retArrPCosZip(){return  myArrMovement.CLIENTE_PARTICULAR_CP;};
        void setArrPCosZip(long zip){myArrMovement.CLIENTE_PARTICULAR_CP = zip;};  
        //costumer type
        int retArrCosType(){return  myArrMovement.CLIENTE_TIPO;};
        void setArrCosType(long type){myArrMovement.CLIENTE_TIPO = type;};
        //costumer type by default
        int retArrCosTypeDef(){return  myArrMovement.CLIENTE_TIPO_DEF;};
        void setArrCosTypeDef(long type){myArrMovement.CLIENTE_TIPO_DEF = type;};
        //costumer's nima
        long retArrCosNima(){return  myArrMovement.CLIENTE_NIMA;};
        void setArrCosNima(long nima){myArrMovement.CLIENTE_NIMA = nima;};
        ////particular
        long retArrPCosNima(){return  myArrMovement.CLIENTE_PARTICULAR_NIMA;};
        void setArrPCosNima(long nima){myArrMovement.CLIENTE_PARTICULAR_NIMA = nima;};  
        //costumer's apply number
        long retArrCosNumIns(){return  myArrMovement.CLIENTE_NUM_INSCRIPCION;};
        void setArrCosNumIns(long num){myArrMovement.CLIENTE_NUM_INSCRIPCION = num;};
        ////particular
        long retArrPCosNumIns(){return  myArrMovement.CLIENTE_PARTICULAR_NUM_INSCRIPCION;};
        void setArrPCosNumIns(long num){myArrMovement.CLIENTE_PARTICULAR_NUM_INSCRIPCION = num;};  
        //costumer's telephone
        long retArrCosPhone(){return  myArrMovement.CLIENTE_TELEFONO;};
        void setArrCosPhone(long num){myArrMovement.CLIENTE_TELEFONO = num;};
        ////particular
        long retArrPCosPhone(){return  myArrMovement.CLIENTE_PARTICULAR_TELEFONO;};
        void setArrPCosPhone(long num){myArrMovement.CLIENTE_PARTICULAR_TELEFONO = num;};  
        //costumer's mail
        std::string retArrCosMail(){return myArrMovement.CLIENTE_MAIL;};
        void setArrCosMail(std::string mail){myArrMovement.CLIENTE_MAIL = mail;};
        ////particular
        std::string retArrPCosMail(){return myArrMovement.CLIENTE_PARTICULAR_MAIL;};
        void setArrPCosMail(std::string mail){myArrMovement.CLIENTE_PARTICULAR_MAIL = mail;};
        ////

        ////PRODUCT DATA
        void setArrProdDATA(std::vector <std::string> newDATA);
        void setDepProdDATA(std::vector <std::string> newDATA);
        int setAllProductData(qtDatabase & myDatabase);
        int setAllArrProductData(qtDatabase & myDatabase);
        std::string get_dep_whole_product(){return (myDepMovement.PRODUCTO_NOMBRE + " " + myDepMovement.PRODUCTO_NOMBRE2 + " " + myDepMovement.PRODUCTO_NOMBRE3 + " (" + std::to_string(myDepMovement.CODIGO_PRODUCTO) + ") " + std::to_string(myDepMovement.PRODUCTO_LER));};
        std::string get_arr_whole_product(){return (myArrMovement.PRODUCTO_NOMBRE + " " + myArrMovement.PRODUCTO_NOMBRE2 + " " + myArrMovement.PRODUCTO_NOMBRE3 + " (" + std::to_string(myArrMovement.CODIGO_PRODUCTO) + ") " + std::to_string(myArrMovement.PRODUCTO_LER));};
        //TODO
        virtual int setAllProducts(qtDatabase & myDatabase, std::string station_type){return 0;};
        //
        //product's code
        long retDepProdCode(){return  myDepMovement.CODIGO_PRODUCTO;};
        void setDepProdCode(long code){myDepMovement.CODIGO_PRODUCTO = code;};
        long retArrProdCode(){return  myArrMovement.CODIGO_PRODUCTO;};
        void setArrProdCode(long code){myArrMovement.CODIGO_PRODUCTO = code;};
        //product's LER
        long retDepProdLER(){return  myDepMovement.PRODUCTO_LER;};
        void setDepProdLER(long code){myDepMovement.PRODUCTO_LER = code;};
        long retArrProdLER(){return  myArrMovement.PRODUCTO_LER;};
        void setArrProdLER(long code){myArrMovement.PRODUCTO_LER = code;};
        //product's Name
        std::string retDepProdFullName(){return myDepMovement.PRODUCTO_NOMBRE + " " + myDepMovement.PRODUCTO_NOMBRE2 + " " + myDepMovement.PRODUCTO_NOMBRE3;};
        std::string retDepProdName1(){return myDepMovement.PRODUCTO_NOMBRE;};
        void setDepProdName1(std::string name){myDepMovement.PRODUCTO_NOMBRE = name;};
        std::string retDepProdName2(){return myDepMovement.PRODUCTO_NOMBRE2;};
        void setDepProdName2(std::string name){myDepMovement.PRODUCTO_NOMBRE2 = name;};
        std::string retDepProdName3(){return myDepMovement.PRODUCTO_NOMBRE3;};
        void setDepProdName3(std::string name){myDepMovement.PRODUCTO_NOMBRE3 = name;};
        std::string retArrProdFullName(){return myArrMovement.PRODUCTO_NOMBRE + " " + myArrMovement.PRODUCTO_NOMBRE2 + " " + myArrMovement.PRODUCTO_NOMBRE3;};
        std::string retArrProdName1(){return myArrMovement.PRODUCTO_NOMBRE;};
        void setArrProdName1(std::string name){myArrMovement.PRODUCTO_NOMBRE = name;};
        std::string retArrProdName2(){return myArrMovement.PRODUCTO_NOMBRE2;};
        void setArrProdName2(std::string name){myArrMovement.PRODUCTO_NOMBRE2 = name;};
        std::string retArrProdName3(){return myArrMovement.PRODUCTO_NOMBRE3;};
        void setArrProdName3(std::string name){myArrMovement.PRODUCTO_NOMBRE3 = name;};
        //product's danger
        std::string retDepProdPeligro(){return myDepMovement.PRODUCTO_PELIGROSIDAD;};
        void setDepProdPeligro(std::string peligrosidad){myDepMovement.PRODUCTO_PELIGROSIDAD = peligrosidad;};
        std::string retArrProdPeligro(){return myArrMovement.PRODUCTO_PELIGROSIDAD;};
        void setArrProdPeligro(std::string peligrosidad){myArrMovement.PRODUCTO_PELIGROSIDAD = peligrosidad;};
        
        //permits
        //int isArrCosProdPermit(){return 0;};
        virtual void setArrCosProdPermits(qtDatabase & myDatabase){return;};
        virtual void setArrCosProdPermits(qtDatabase & myDatabase, const char* type){return;};
        void setArrCosProdPermitsBase(qtDatabase & myDatabase, const char* type);
        //AUXILIAR
        int setArrPermitsFlags(std::vector<std::string> ourData);
        int setArrPermits(std::vector<std::string> ourData);  
        //
        ////
        void setArrPermitGralFlag(int value){myArrMovement.PERMISOS_PRODUCTO.FLAG_GENERAL = value;};
        void setDepPermitGralFlag(int value){myDepMovement.PERMISOS_PRODUCTO.FLAG_GENERAL = value;};
        //////
        void setArrPermitDateFlag(int value){myArrMovement.PERMISOS_PRODUCTO.FLAG_CONTRATO = value;};
        int retArrPermitDateFlag(){return myArrMovement.PERMISOS_PRODUCTO.FLAG_CONTRATO;};
        void setDepPermitDateFlag(int value){myDepMovement.PERMISOS_PRODUCTO.FLAG_CONTRATO = value;};
        int retDepPermitDateFlag(){return myDepMovement.PERMISOS_PRODUCTO.FLAG_CONTRATO;};  
        void setArrPermitDate(std::string value){myArrMovement.PERMISOS_PRODUCTO.CONTRATO = value;};
        std::string retArrPermitDate(){return myArrMovement.PERMISOS_PRODUCTO.CONTRATO;};
        void setDepPermitDate(std::string value){myDepMovement.PERMISOS_PRODUCTO.CONTRATO = value;};
        std::string retDepPermitDate(){return myDepMovement.PERMISOS_PRODUCTO.CONTRATO;};
        //////
        void setArrPermitNptFlag(int value){myArrMovement.PERMISOS_PRODUCTO.FLAG_NPT = value;};
        int retArrPermitNptFlag(){return myArrMovement.PERMISOS_PRODUCTO.FLAG_NPT;};
        void setDepPermitNptFlag(int value){myDepMovement.PERMISOS_PRODUCTO.FLAG_NPT = value;};
        int retDepPermitNptFlag(){return myDepMovement.PERMISOS_PRODUCTO.FLAG_NPT;};   
        std::string retArrPermitNpt(){return myArrMovement.PERMISOS_PRODUCTO.NPT;};
        void setArrPermitNpt(std::string newValue){myArrMovement.PERMISOS_PRODUCTO.NPT = newValue;};
        std::string retDepPermitNpt(){return myDepMovement.PERMISOS_PRODUCTO.NPT;};
        void setDepPermitNpt(std::string newValue){myDepMovement.PERMISOS_PRODUCTO.NPT = newValue;};
        //////
        void setArrPermitCbFlag(int value){myArrMovement.PERMISOS_PRODUCTO.FLAG_CB = value;};
        int retArrPermitCbFlag(){return myArrMovement.PERMISOS_PRODUCTO.FLAG_CB;};
        void setDepPermitCbFlag(int value){myDepMovement.PERMISOS_PRODUCTO.FLAG_CB = value;};
        int retDepPermitCbFlag(){return myDepMovement.PERMISOS_PRODUCTO.FLAG_CB;};   
        int retArrPermitCb(){return myArrMovement.PERMISOS_PRODUCTO.CB;};
        void setArrPermitCb(long newValue){myArrMovement.PERMISOS_PRODUCTO.CB = newValue;};
        int retDepProdpermitCb(){return myDepMovement.PERMISOS_PRODUCTO.CB;};
        void setDepProdpermitCb(long newValue){myDepMovement.PERMISOS_PRODUCTO.CB = newValue;};
        //////
        void setArrPermitCpFlag(int value){myArrMovement.PERMISOS_PRODUCTO.FLAG_CP = value;};
        int retArrPermitCpFlag(){return myArrMovement.PERMISOS_PRODUCTO.FLAG_CP;};
        void setDepPermitCpFlag(int value){myDepMovement.PERMISOS_PRODUCTO.FLAG_CP = value;};
        int retDepPermitCpFlag(){return myDepMovement.PERMISOS_PRODUCTO.FLAG_CP;};   
        int retArrPermitCp(){return myArrMovement.PERMISOS_PRODUCTO.CP;};
        void setArrPermitCp(long newValue){myArrMovement.PERMISOS_PRODUCTO.CP = newValue;};
        int retDepProdpermitCp(){return myDepMovement.PERMISOS_PRODUCTO.CP;};
        void setDepProdpermitCp(long newValue){myDepMovement.PERMISOS_PRODUCTO.CP = newValue;};
        //////
        void setArrPermitDcpFlag(int value){myArrMovement.PERMISOS_PRODUCTO.FLAG_DCP = value;};
        int retArrPermitDcpFlag(){return myArrMovement.PERMISOS_PRODUCTO.FLAG_DCP;};
        void setDepPermitDcpFlag(int value){myDepMovement.PERMISOS_PRODUCTO.FLAG_DCP = value;};
        int retDepPermitDcpFlag(){return myDepMovement.PERMISOS_PRODUCTO.FLAG_DCP;};   
        int retArrPermitDcp(){return myArrMovement.PERMISOS_PRODUCTO.DCP;};
        void setArrPermitDcp(long newValue){myArrMovement.PERMISOS_PRODUCTO.DCP = newValue;};
        int retDepProdpermitDcp(){return myDepMovement.PERMISOS_PRODUCTO.DCP;};
        void setDepProdpermitDcp(long newValue){myDepMovement.PERMISOS_PRODUCTO.DCP = newValue;};
        //////

        int isArrProdPermit(){int ret; (isArrProdGralPermit() && isArrProdDatePermit() && isArrProdNptPermit() && isArrProdCbPermit() && isArrProdCpPermit() && isArrProdDcpPermit()?ret = 1:ret = 0); return ret;};
        int isArrProdGralPermit(){ return myArrMovement.PERMISOS_PRODUCTO.FLAG_GENERAL;};
        int isArrProdDatePermit();
        int isArrProdNptPermit();
        int isArrProdCbPermit();
        int isArrProdCpPermit();
        int isArrProdDcpPermit();

        int isDepProdNptPermit();
        
        void clearPermits(){myArrMovement.PERMISOS_PRODUCTO = (const struct struPermits){ 0 };return;};

        ////DRIVER DATA
        int setDriverByCode(long code, qtDatabase & local_database);
        int setDriverByName(std::string name);
        int default_driver(qtDatabase &);
        
        driver* depDriver;
        void retDepDriver(driver *& new_dep_driver){ (depDriver?new_dep_driver = new driver(depDriver):new_dep_driver = new driver());};
            
        ////origin code
        station* arrOriginStation;
        station* depOriginStation; 
        void setArrOrigStation(station * origin){if(arrOriginStation) delete arrOriginStation; arrOriginStation = new station(); *arrOriginStation = *origin; return;}; 
        void setDepOrigStation(station * origin){if(depOriginStation) delete depOriginStation; depOriginStation = new station(); *depOriginStation = *origin; return;};
        void retArrOriginStation(station *& newOrigin){ (arrOriginStation?newOrigin = new station(arrOriginStation):newOrigin = new station());};
        void retDepOriginStation(station *& newOrigin){ (depOriginStation?newOrigin = new station(depOriginStation):newOrigin = new station());};
        std::string retArrDestStationDR(){return myArrMovement.OPERACION_DE_TRATAMIENTO;};
        void setArrDestStationDR(std::string value){myArrMovement.OPERACION_DE_TRATAMIENTO = value;};
        ////destination code
        station* arrDestinationStation;
        station* depDestinationStation; 
        void setArrDestStation(station * destination){if(arrDestinationStation) delete arrDestinationStation; arrDestinationStation = new station(); *arrDestinationStation = *destination; return;}; 
        void setDepDestStation(station * destination){if(depDestinationStation) delete depDestinationStation; depDestinationStation = new station(); *depDestinationStation = *destination; return;};
        void retArrDestinationStation(station *& newDest){ (arrDestinationStation?newDest = new station(arrDestinationStation):newDest = new station());};
        void retDepDestinationStation(station *& newDest){ (depDestinationStation?newDest = new station(depDestinationStation):newDest = new station());};
        std::string retDepDestStationDR(){return myDepMovement.OPERACION_DE_TRATAMIENTO;};
        void setDepDestStationDR(std::string value){myDepMovement.OPERACION_DE_TRATAMIENTO = value;};

        ////our identity
        costumer* ourId;
        void setOurId(costumer* newId){if(ourId) delete ourId; ourId = new costumer(newId);};
        void retOurId(costumer *& newId){ (ourId?newId = new costumer(ourId):newId = new costumer());};
        /* stations */
        ////our station
        station* ourStation;
        void setOurStation(station * newStation){if(ourStation) delete ourStation; ourStation = new station(newStation);};
        void retOurStation(station *& newStation){ (ourStation?newStation = new station(ourStation):newStation = new station());};

        std::vector<std::string> retStationsLst(qtDatabase & myDatabase, int internal);
        ////MISC
        //ecoembes
        int retDepEco(){return  myDepMovement.ECOEMBES;};
        void setDepEco(int eco){myDepMovement.ECOEMBES = eco;};
        int retArrEco(){return  myArrMovement.ECOEMBES;};
        void setArrEco(int eco){myArrMovement.ECOEMBES = eco;};
        //price
        void setDepPayProcedure(int pay){myDepMovement.FORMA_DE_PAGO = pay;};
        int retDepPayProcedure(){return myDepMovement.FORMA_DE_PAGO;};
        float retDepPrice(){return myDepMovement.PRECIO_TN;};
        void setDepPrice(float price){myDepMovement.PRECIO_TN = price; return;};
        float retArrPrice(){return myArrMovement.PRECIO_TN;};
        void setArrPrice(float price){myArrMovement.PRECIO_TN = price; return;};
        //plates
        std::string retDepPlate(){return myDepMovement.MATRICULA;};
        void setDepPlate(std::string plate){myDepMovement.MATRICULA = plate;};
        std::string retArrPlate(){return myArrMovement.MATRICULA;};
        void setArrPlate(std::string plate){myArrMovement.MATRICULA = plate;};
        std::string retDepPlateAtt(){return myDepMovement.REMOLQUE;};
        void setDepPlateAtt(std::string plate){myDepMovement.REMOLQUE = plate;};
        std::string retArrPlateAtt(){return myArrMovement.REMOLQUE;};
        void setArrPlateAtt(std::string plate){myArrMovement.REMOLQUE = plate;};
        //operacion tratamiento
        std::string retDepTreat(){return myDepMovement.OPERACION_DE_TRATAMIENTO;};
        void setDepTreat(std::string treatment){myDepMovement.OPERACION_DE_TRATAMIENTO = treatment; return;};
        //
        //scaling
        virtual int isArrPesoOk(){return 0;};
        virtual int isDepPesoOk(){return 0;};
        virtual int retDepScaleExpected(){return 0;};
        virtual void setAndCalcScaleOut(unsigned int scale){myDepMovement.PESO_SALIDA = scale;};
        virtual int saveScaleOut(qtDatabase & myDatabase, qtDatabase &myRemoteDatabase, const char * remoteHost, int remotePort ){ return 1;};
        void setErrorScale(float error){ERROR_ACCEPTED_WEIGHT = error;};
        float retErrorScale(){return ERROR_ACCEPTED_WEIGHT;};
        unsigned int retDepScaleOut(){return myDepMovement.PESO_SALIDA;};
        void setDepScaleOut(unsigned int scale){myDepMovement.PESO_SALIDA = scale;};
        unsigned int retDepScaleIn(){return myDepMovement.PESO_ENTRADA;};
        void setDepScaleIn(unsigned int scale){myDepMovement.PESO_ENTRADA = scale;};
        unsigned int retArrScaleIn(){return myArrMovement.PESO_ENTRADA;};
        void setArrScaleIn(unsigned int scale){myArrMovement.PESO_ENTRADA = scale;};
        // calculated weights
        unsigned int retGrossWeight(){return grossWeight;};
        void setGrossWeight(unsigned int weight){grossWeight = weight;};
        unsigned int retTareWeight(){return tareWeight;};
        void setTareWeight(unsigned int weight){tareWeight = weight;};
        long retNetWeight(){return netWeight;};
        void setNetWeight(long weight){netWeight = weight;};
        long retDepWeightToTakeAway(){return myDepMovement.PESO_A_RETIRAR;};
        void setDepWeightToTakeAway(long scale){myDepMovement.PESO_A_RETIRAR = scale;};
        long retArrWeightToTakeAway(){return myArrMovement.PESO_A_RETIRAR;};
        void setArrWeightToTakeAway(long scale){myArrMovement.PESO_A_RETIRAR = scale;}; 
        //DI
        std::string retDepDi(){return myDepMovement.DI;};
        void setDepDi(std::string newDI){myDepMovement.DI = newDI;};
        std::string retArrDi(){return myArrMovement.DI;};
        void setArrDi(std::string newDI){myArrMovement.DI = newDI;};
        //TYPE
        int retDepMovType(){return myDepMovement.TIPO_DE_MOVIMIENTO;};
        void setDepMovType(int newType){myDepMovement.TIPO_DE_MOVIMIENTO = newType;};
        int retArrMovType(){return myArrMovement.TIPO_DE_MOVIMIENTO;};
        void setArrMovType(int newType){myArrMovement.TIPO_DE_MOVIMIENTO = newType;};
        // SPECIALS FOR ORDERS
        costumer* depAuthCostumer;
        void retDepAuthCostumer(costumer *& newDepAuthCostumer){ (depAuthCostumer?newDepAuthCostumer = new costumer(depAuthCostumer):newDepAuthCostumer = new costumer());};
        ////

        //RESET FUNCTIONS
        void resetArrCostumer();
        void resetDepCostumer(); 
        void resetArrProduct();
        void resetArrProdPermits(){myArrMovement.PERMISOS_PRODUCTO = resetPermits();};
        void resetDepProduct();
        void resetDepProdPermits(){myDepMovement.PERMISOS_PRODUCTO = resetPermits();};
        void resetArrScale();
        void resetDepScale();
        void resetArrPlate();
        void resetDepPlate();
        void resetArrDi();
        void resetDepDi(); 
        void resetArrOrigin();
        void resetDepOrigin();
        void resetArrDestination();
        void resetDepDestination();
        void resetOurId();
        void resetDepDriver();
        void resetStaff();

        //date and time
        std::string retDepDateTime(){return myDepMovement.FECHA_HORA;};
        void setDepDateTime(std::string newDateTime){myDepMovement.FECHA_HORA = newDateTime; return;};
        std::string retArrDateTime(){return myArrMovement.FECHA_HORA;};
        void setArrDateTime(std::string newDateTime){myArrMovement.FECHA_HORA = newDateTime; return;};
        std::string retDepFinalDateTime(){return myDepMovement.FECHA_HORA_FINAL;};
        void setDepFinalDateTime(std::string newDateTime){myDepMovement.FECHA_HORA_FINAL = newDateTime; return;};
        //
        ///////////////////////////////////////////
        //////////////////////////////////////////
        //
    protected:
        //incidents
        std::vector < std::string> iIncidents;
        std::vector < std::string> oIncidents;
        //operato comment
        std::string iComment;
        std::string oComment;
        int depMovIndex;
        //plates in system
        int formSCADA;
        struMovement myArrMovement;
        struMovement myDepMovement;
        staff *staff_in_charge;
    
    private:
        //
        int formLlegada;
        int formState;
        int formInicState;
        int formFinalState;
        int formType;

        //entrada a ET
        std::string carCode;
        int maxPlateLength;
        int minPlateLength;
        std::string plateImage1;
        std::string plateImage; 
        std::vector <bool> productPermits;
        std::vector <std::string> clientProductPermits;

        std::string diDate;
        std::string diTime;

        //FOLDER TO SAVE DATA
        std::string arrFolder;
        std::string depFolder;
        //

        //all Drivers
        std::vector <driver*> allDrivers;
        
    public:
        //salvado del formulario
        std::vector <std::vector <std::string>> allTransitoInfo;
        //
    private:
        bool overallProductPermit;
        bool contractDatePermit;
        bool nptPermit;
        bool cbPermit;
        bool cpPermit;
        bool dcpPermit;
        
        // weights
        unsigned int grossWeight;
        unsigned int tareWeight;
        long netWeight;
        float ERROR_ACCEPTED_WEIGHT;

};

#endif
