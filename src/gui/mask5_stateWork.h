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

#ifndef _MASK5_STATEWORK_
#define _MASK5_STATEWORK_

static int stateWork(PARAM *p, DATA *d)
{
    int ret = -1;
    char error[128];
    if(d->enFutEstado != formSalida->getState())
    {
        switch(d->enFutEstado)
	    {
	        case(-1): //no previous form
            {
                pvSetChecked(p,CHKENTRADA,1);
                pvSetChecked(p,CHKSALIDA,0);
                d->productoActual.clear();
                d->llegada=1;	   
                break;
            }
	        case(99):
            {
                int DatabaseData_chkd;
                int remote_connected = 0;
                try
                {
                    DatabaseData_chkd = std::stoi(remoteDatabaseData.db_port);
                }
                catch(...)
                {
                    DatabaseData_chkd = 0;
                }	    
                if(isConnected(remoteDatabaseData.db_host.c_str(), DatabaseData_chkd))
                    remote_connected = 1;
                
                if(formSalida->storeTransit(localDatabase,remoteDatabase,myStation,remote_connected))
                    console.push_back("AVISO: no se consiguió escribir el movimiento a tránsito en la base de datos remota, sincronice cuando pueda");
                cameraSemaphore(3,1,globalConfiguration.traffic_lights_enabled);
                break;
            }
	        case(500): //waiting plate selection
	        {
	            //commons
	            popteTransito(p,d,TABLATRANSITO,formSalida);
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
                //populate orders table
                formSalida->setOrders(localDatabase, myStation->getCode());	   
                popteOrders(p,d,TABORDERS,formSalida);
                d->selectedOrder=-1;
                break;
            }
	        case(501): //order selected
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
                //COSTUMER NAME
                pvSetText(p,EDITCLIENT,formSalida->retArrCosName().c_str());		
                //PRODUCT NAME
                pvSetText(p,EDITPRODUCT,formSalida->retArrProdFullName().c_str());		
                //PERMITS
                formSalida->setArrCosProdPermits(localDatabase);	    	   
                break;
            }
	        case(510): //DI creation and folder saving
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT); 
                pvSetText(p,EDITDIPROV,formSalida->createArrDi(localDatabase).c_str());	    
                if(!formSalida->isIncArrPlateEdited())
                    formSalida->savePlateImage(3,"entrada");
                break;
            }
	        case(512): //taking plate!
            {	    
                std::string plate;
                ret = useCamera(p, d, 3, plate, IMCAM);
                if(!ret)
                {
                    pvSetText(p,EDITCAM,pvtr(plate.c_str()));
                    formSalida->setArrPlate(plate);
                    d->processTag=1;
                }
                else
                {
                    d->processTag=-1;
                    sprintf(error,"*ERROR* imposible recibir matrícula de la cámara 3");
                    console.push_back(error);
                }
                break;
            }
	        case(520): //good plate, waiting for taking weight and showing temporal DI
	        case(522): 
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);	    	   	
                break;
            }
	        case(525):
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
                
                char error[256];
                bascula * testBascula = NULL;
                //reseteamos peso
                std::string sPesoTest = "-1";
                pvSetText(p,EDITPESOENT,sPesoTest.c_str());
                formSalida->setArrScaleIn(0);
                formSalida->incArrScaleEdited(0);
                //
                sprintf(error,"(INFO) probando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, \nparidad:%s , control de flujo:%s y %s bits de parada...",3, basculas.at(2).port.c_str(),basculas.at(2).bauds,basculas.at(2).timeout , basculas.at(2).ask.c_str(), (basculas.at(2).parity==0?"ninguna":(basculas.at(2).parity==1?"impar":"par")),(basculas.at(2).ctrl==0?"ninguno":(basculas.at(2).ctrl==1?"software":"hardware")),(basculas.at(2).stopBits==0?"1":(basculas.at(2).stopBits==1?"1,5":"2")));
                console.push_back(error);
                testBascula = new bascula(basculas.at(2).port,basculas.at(2).bauds);
                if(!basculas.at(2).ask.empty())
                {
                    testBascula->set_parity(basculas.at(2).parity);
                    testBascula->set_flowControl(basculas.at(2).ctrl);
                    testBascula->set_stopBits(basculas.at(2).stopBits);
                    //no capturamos excepciones
                    testBascula->setCommand(basculas.at(2).ask);	     
                    std::cout << "(INFO) leyendo peso!" << std::endl;
                    char* texto;
                    try
                    {
                        int ret = testBascula->readPeso(basculas.at(2).timeout,texto);
                        std::string sPeso =  fromBufferAPeso(texto);
                        formSalida->setArrScaleIn(std::stoi(sPeso));		    
                        pvSetText(p,EDITPESOENT,sPeso.c_str());
                        if(ret)
                        {
                            console.push_back("(AVISO) posible TIMEOUT o lectura errónea del puerto");
                        }
                        pvSetText(p,EDITPESOENT,sPeso.c_str());
                    }
                    catch(...)
                    {
                        console.push_back("*ERROR* error de entrada/salida, puerto correcto y conectado?");
                    }
                }
                if(testBascula != NULL)
                delete testBascula;
                break;
            }
	        case(610):
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTENT);
                if(formSalida->getFzCurrentProduct())
                    pvSetChecked(p,CHKFORZARPROD,1);
                else
                    pvSetChecked(p,CHKFORZARPROD,0); 
                break;
            }
	        case(1100):
            {
                popteTransito(p,d,TABLATRANSITO, formSalida);
                //tipo de movimiento tránsito!
                formSalida->setDepMovType(DEF_MOV_SALIDA);
                d->transito_plate.clear();
                d->post_transito_plate.clear();
                break;
            }
	        case(1200):
            {
                //tipo de movimiento transferencia!
                formSalida->setTransferMov(DEF_BIORECICLAJE_CODE,myStation);	  
                break;
            }
	        case(1211):
	        case(1111): //taking plate camera 4
            {  
                std::string plate;	    
                ret = useCamera(p, d, 4, plate, IMCAM_E2);
                if(!ret)
                {
                    pvSetText(p,EDITCAM_E2,pvtr(plate.c_str()));
                    d->processTag=1;
                    formSalida->setDepPlate(plate);
                }
                else
                {
                    d->processTag=-1;
                    sprintf(error,"*ERROR* imposible recibir matrícula de la cámara 4");
                    console.push_back(error);
                }
                break;
            }
	        case(1120):
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
                pvSetText(p,EDITDIDEF,formSalida->createDepDi(localDatabase).c_str());    
                if(!formSalida->isIncDepPlateEdited())	    
                    formSalida->savePlateImage(4,"salida");
                std::string pesoSalida = std::to_string(formSalida->retDepScaleOut());
                pvSetText(p,EDITPESOSAL,pesoSalida.c_str());
                //default driver
                if(formSalida->default_driver(localDatabase))
                {
                    driver *tmp_driver;
                    formSalida->ret_dep_driver(tmp_driver);
                    pvSetText(p,EDITCODETRANSP,std::to_string(tmp_driver->get_code()).c_str());
                    pvSetText(p,EDITNAMETRANSP,tmp_driver->get_name().c_str());
                    delete tmp_driver;
                }
                else
                {
                    pvSetText(p,EDITCODETRANSP,"N/A");
                    pvSetText(p,EDITNAMETRANSP,"N/A");
                }
                break;
            } 
	        case(1121)://we store scale in database
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
                d->test= 0;
                int DatabaseData_chkd;
                try
                {
                    DatabaseData_chkd= std::stoi(remoteDatabaseData.db_port);
                }
                catch(...)
                {
                    DatabaseData_chkd = 0;
                }
                formSalida->saveScaleOut(localDatabase,remoteDatabase,remoteDatabaseData.db_host.c_str(), DatabaseData_chkd);
                break;
            }
	        case(1223):
            {
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL); 
                pvSetText(p,EDITCAM_E2,formSalida->retDepPlate().c_str());
                pvSetText(p,EDITDIDEF,formSalida->retDepDi().c_str());
                break;
            }
	        case(1123):
            {
	            refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
	            break;
            }
	        case(1224):
	        case(1124): //loading all DI information
            {
                costumer * ourId = new costumer(DEF_BIORECICLAJE_CODE,localDatabase);
                formSalida->setOurId(ourId);
                delete ourId;
                formSalida->setAllDiData(localDatabase, myStation, DEF_BIORECICLAJE_CODE, DEF_TRANS_CODE);
                break;
            }
	        case(1126):
            {	    
                char error[256];
                bascula * testBascula = NULL;
                //reseteamos peso
                std::string sPesoTest = "-1";
                pvSetText(p,EDITPESOSAL,sPesoTest.c_str());
                formSalida->setDepScaleOut(0);
                //
                sprintf(error,"(INFO) usando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, \nparidad:%s , control de flujo:%s y %s bits de parada...",4, basculas.at(3).port.c_str(),basculas.at(3).bauds,basculas.at(3).timeout , basculas.at(3).ask.c_str(), (basculas.at(3).parity==0?"ninguna":(basculas.at(3).parity==1?"impar":"par")),(basculas.at(3).ctrl==0?"ninguno":(basculas.at(3).ctrl==1?"software":"hardware")),(basculas.at(3).stopBits==0?"1":(basculas.at(3).stopBits==1?"1,5":"2")));
                console.push_back(error);
                testBascula = new bascula(basculas.at(3).port,basculas.at(3).bauds);
                if(!basculas.at(3).ask.empty())
                {
                    testBascula->set_parity(basculas.at(3).parity);
                    testBascula->set_flowControl(basculas.at(3).ctrl);
                    testBascula->set_stopBits(basculas.at(3).stopBits);
                    //no capturamos excepciones
                    testBascula->setCommand(basculas.at(3).ask);	     
                    std::cout << "(INFO) leyendo peso!" << std::endl;
                    char* texto;
                    try
                    {
                        int ret = testBascula->readPeso(basculas.at(3).timeout,texto);
                        std::string sPeso =  fromBufferAPeso(texto);
                        pvSetText(p,EDITPESOSAL,sPeso.c_str());
                        formSalida->setDepScaleOut(std::stoi(sPeso));		      
                        if(ret)
                        {
                            console.push_back("(AVISO) posible TIMEOUT o lectura errónea del puerto");
                        }
                    }
                    catch(...)
                    {
                        console.push_back("*ERROR* error de entrada/salida, puerto correcto y conectado?");
                    }
                }
                if(testBascula != NULL)
                    delete testBascula;
                break;
            }
            case(1230):
            case(1130):
            {
                pvSetText(p,EDITCODETRANSP,std::to_string(formSalida->retDepDriCode()).c_str());
                pvSetText(p,EDITNAMETRANSP,formSalida->retDepDriName().c_str());
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);	  
                break;
            }
	        case(1231):
	        case(1131):
            {
                pvSetText(p,EDITCODETRANSP,std::to_string(formSalida->retDepDriCode()).c_str());
                pvSetText(p,EDITNAMETRANSP,formSalida->retDepDriName().c_str());
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
                break;
            }
	        case(1136): //signing
	        {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);
                //TODO
                //REMOVE DATABASE QUERY FROM HERE
                std::string cname;
                std::string productText;
                std::string sql;
                //COSTUMER
                std::string clientCode = std::to_string(formSalida->retDepCosCode());
                selCostumerNameByCode(sql, clientCode);
                localDatabase.query(p,sql.c_str());
                std::vector<std::vector<std::string>> ourData = localDatabase.retData2();
                if(ourData.size() >= 1)
                {
                    cname = ourData.at(0).at(0);		
                }
                //
                //PRODUCT
                std::string productCode = std::to_string(formSalida->retDepProdCode());
                selProductBasisByCode(sql, productCode);
                localDatabase.query(p, sql.c_str());
                ourData.clear();
                ourData = localDatabase.retData2();
                if(ourData.size() >= 1)
                {
                    std::string ler = ourData.at(0).at(0);
                    std::string pname = ourData.at(0).at(1);
                    std::string pname2 = ourData.at(0).at(2);
                    std::string pname3 = ourData.at(0).at(3);
                    productText = "(" + ler + ") " + pname + " " + pname2 + " " + pname3; 		
                }
                //
                int error = 0;
                d->miTableta = new tableta(error);
                if(!error)
                {
                    //d->miTableta->init();
                    //std::cout << "estableciendo la imagen" << std::endl;
                    char speso[100];
                    //TODO
                    int pesoTotal =  formSalida->retDepScaleOut() - formSalida->retDepScaleIn();
                    //TOTAL WEIGHT IS NOW MANAGED BY FORMULARIO CLASS, AND ITS DERIVED
                    sprintf(speso,"%d",pesoTotal);
                    std::string sspeso = speso;
                    float precio = pesoTotal *  formSalida->retDepPrice()/1000.0;
                    std::string sPrecio = std::to_string (precio);
                    //std::cout << cname << "," << productText << std::endl;
                    d->miTableta->setInfoShow(formSalida->retDepPlate(),cname,productText,sPrecio, sspeso);
                    //std::cout << "fin de establecer la imagen" << std::endl;
                    int tries = 3;
                    int i=0;
                    int done=0;
                    while(i<tries && !done && !error)
                    {
                        d->miTableta->init();
                        if(!d->miTableta->loadInfo())
                            done = 1;
                        else
                        {
                            espera(1);
                            d->miTableta->reset();
                            delete d->miTableta;
                            d->miTableta = new tableta(error);
                        }
                        i++;
                    }
                    if(done)
                    {
                        d->miTableta->startCapture();
                        pvMessageBox(p,BUTFIRMAR,BoxInformation,"Pulsa OK, y toque con el lápiz la tableta cuando haya terminado de firmar",MessageBoxOk,0,0);
                    }
                    else
                    {
                        console.push_back("**ERROR** desenchufe y vuelva a enchufar la tableta de firmas y vuélvalo a intentar");
                        if(!error)
                        d->miTableta->reset();
                        delete d->miTableta;
                        d->miTableta = NULL;
                    }
                }
                else
                {
                    console.push_back("**ERROR** ¡Tableta de firmas no detectada!");
                    delete d->miTableta;
                    d->miTableta = NULL;
                }
               	break; 
            }
	        case(1221):
            {
                //operator comment
                refreshOperatorComment(p,d,formSalida,EDITCOMMENTSAL);	    
                pvSetText(p,EDITDIDEF,formSalida->createDepDi(localDatabase).c_str());
                //Create fake signature for transportist not present	    
                formSalida->saveSignature("image/void.png");
                //default driver
                if(formSalida->default_driver(localDatabase))
                {
                    driver *tmp_driver;
                    formSalida->ret_dep_driver(tmp_driver);
                    pvSetText(p,EDITCODETRANSP,std::to_string(tmp_driver->get_code()).c_str());
                    pvSetText(p,EDITNAMETRANSP,tmp_driver->get_name().c_str());
                    delete tmp_driver;
                }
                else
                {
                    pvSetText(p,EDITCODETRANSP,"N/A");
                    pvSetText(p,EDITNAMETRANSP,"N/A");
                }
                break;
            } 
	        case(1197):
            {
                formSalida->unsetStaff();
                pvInputDialog(p,BUTPROCEDER_E1,"Inserte el código de basculista para proceder:","");
                break;
            }
	        case(1199): //almacenaje del movimiento, impresión del pdf
	        {
                //to DATABASE
                int DatabaseData_chkd;
                int remote_connected = 0;
                int error_check = 0;
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
                    try
                    {
                        DatabaseData_chkd = std::stoi(remoteDatabaseData.local_db_port);
                    }
                    catch(...)
                    {
                        DatabaseData_chkd = 0;
                    }
                    if(isConnected(remoteDatabaseData.local_db_host.c_str(), DatabaseData_chkd))
                        remote_connected = 1;
                }
                d->ret = 0;

                std::string myPrinter;
                miIni->retPrinterId(myPrinter);
                if(myPrinter.empty())
                    console.push_back("**AVISO** no se va a imprimir el DI, al no tener configurada la impresora");
                // transfers movements
                if (formSalida->retDepMovType() == DEF_MOV_TRANSFER)
                {			
                    error_check = formSalida->storeDepTransfer(localDatabase, remoteDatabase,remote_connected);
                    if(error_check == -2) //cathastrophic
                    {
                        console.push_back("*ERROR* no se pudo guardar la transferencia, contacte con mantenimiento");
                        d->ret = 1;
                    }
                    else
                    {
                        formSalida->saveSignature(1);
                        if(error_check == -1) //only remote error
                        {
                            console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
                            console.push_back("*ERROR* ¡Necesita sincronizar! Si se trata de un movimiento de transferencia la estación de destino no lo verá");
                        }
                        formSalida->createPdf(myPrinter);
                        d->ret = 0;
                    }
                }
                // outcoming loading materials movements
                else
                {		
                    error_check = formSalida->storeDepMov(localDatabase,remoteDatabase,remote_connected);
                    if(!error_check)
                    {
                        console.push_back("INFO Movimiento generado correctamente");
                        d->ret = 0;
                    }
                    else if(error_check == -1) //remote fail
                    {
                        console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
                        console.push_back("*ERROR* ¡Necesita sincronizar! Si se trata de una orden de recogida necesitará que administración la borre manualmente");
                        d->ret = 0;
                    }
                    else //Cathastrophic
                    {
                        console.push_back("*ERROR* ¡Fallo al guardar el movimiento!");
                        d->ret =1;
                    }	
                    if(!d->ret)
                    {
                        // saving signature
                        formSalida->saveSignature();
                        // printing DI
                        formSalida->createPdf(myPrinter);
                        // sending incidents email
                        if(mailClient->sendIncidentsMail(myStation,formSalida))
                            console.push_back("*ERROR* ¡Error en el sistema de envío de emails");
                        // backing up files
                        formSalida->backupFiles(formSalida->retDepMovCode().c_str());
                    }
                }
                cameraSemaphore(4,1,globalConfiguration.traffic_lights_enabled);
                break;
            }
	        default:
	  	        break;
	    }
        formSalida->setState(d->enFutEstado);
        stateGUI(p,d,formSalida->getState());
        ret = 0;
    }
    return ret;
}

#endif