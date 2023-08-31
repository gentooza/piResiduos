/*
This file is part of PiResiduos.

Copyright 2023 Joaquín Cuéllar <joaquin (dot) cuellar (at) uco (dot) es>

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

#ifndef _MASK4_STATEWORK_
#define _MASK4_STATEWORK_

//acciones
static int stateWork(PARAM *p, DATA *d)
{
	int ret = -1;
  	char error[128];
  	if(d->enFutEstado != formEntrada->getState())
    {
    	switch(d->enFutEstado)
		{
			case -1: //entramos sin un formulario previo
	  		{
	    		pvSetChecked(p,CHKENTRADA,1);
	    		pvSetChecked(p,CHKSALIDA,0);
	    		d->productoActual.clear();
	    		d->entrarDescargar=1;
	    		//globalSyncronization(p,d, formEntrada);	    
	    		break;
	  		}
			case 0:
			{
	    		popteTransito(p,d,TABLATRANSITO,formEntrada);
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    		break;
			}
			case 6: //tomando matrícula
	  		{  
	    		std::string plate;
	    		ret = useCamera(p, d, 1, plate, IMCAM);
	    		if(!ret)
	      		{
					pvSetText(p,EDITCAM,pvtr(plate.c_str()));
					formEntrada->setArrPlate(plate);
					d->processTag=1;
	      		}
	    		else
	      		{
					d->processTag=-1;
					sprintf(error,"*ERROR* imposible recibir matrícula de la cámara 1");
					console.push_back(error);
	      		}
	    		break;
	  		}
			case 10: //matrícula registrada
	  		{
	    		//TODO, va fuera!!
	    		//seleccionamos clientes para la matrícula seleccionada
	    		char * sql =NULL;
	    		sel_all_cos_from_car(sql,formEntrada->retArrPlate().c_str());
	    		localDatabase.query(p,sql);
	    		d->allClientes.clear();
	    		d->allClientesCodes.clear();	    
	    		std::vector <std::vector <std::string>> dataReturn = localDatabase.retData2();	 
	    		for(int i=0;i<dataReturn.size();i++)
	      		{
					if(dataReturn[i][0].compare("0"))
		  				d->allClientesCodes.push_back(dataReturn[i][0]);
	      		}
	    		delete sql;
	    		for(std::vector <std::string>::iterator iter = d->allClientesCodes.begin(); iter != d->allClientesCodes.end(); ++iter)
	      		{
					if(!iter->empty())
		  			{
		    			selectClientNameByCode(sql,iter->c_str());
		    			localDatabase.query(p,sql);
		    			dataReturn.clear();
		    			dataReturn = localDatabase.retData2();
		    			if(dataReturn.size())
		      				d->allClientes.push_back(dataReturn[0][0]);
		    			delete sql;
		  			}
	      		}
	    		d->allClientes.push_back("OTROS");
	    		d->allClientesCodes.push_back("0");
	    		populateCombo(p,COMBOCLIENTES,d->allClientes);
	    		/////
	    		break;
	  		}
			case 120: //AUTHORIZED CLIENT SELECTED, WE SHOW IT'S PRODUCTS ASSOCIATED ALLOWED
			case 20: //cliente seleccionado mostramos todos los productos de ese cliente!
			{
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    		std::string clientCode = std::to_string(formEntrada->retArrCosCode());
	    		int istation_type = 0;
	    		myStation->getType(istation_type);
	    		if(formEntrada->retArrCosCode() == DEF_BIORECICLAJE_CODE) //SI ES UNA TRANSFERENCIA LO DEFINIMOS COMO TIPO DE MOVIMIENTO AQUI
	      			formEntrada->setArrMovType(DEF_MOV_TRANSFER);
	    		else if(istation_type == 3) //deposit
	      			formEntrada->setArrMovType(DEF_MOV_INTERNOD5);	      
	    		else
	      			formEntrada->setArrMovType(DEF_MOV_ENTRADA);
	    		std::string strstation_type;
	    		myStation->getType(strstation_type);
				//TODO
	    		//fuera de aquí el acceso a la base de datos!
	    		char * sql = NULL;
	    		selProdsAllowedToClient(sql,clientCode.c_str(),strstation_type.c_str(),true);
	    		localDatabase.query(p,sql);
				if (sql != NULL)
				{
					delete [] sql;
				}
	    		localDatabase.query(p,"select * from resultado");	
	    		populateProdsCombo(p,COMBOPRODUCTOS,localDatabase.retData2(),true);
	    		localDatabase.query(p,"drop table resultado");
	    		d->pesaje1 = 0;
	    		break;
			}
			case 121: //waiting taking weigth, product chosen from authorized client
			case 21: //waiting weigth, product chosen by normal path
	  		{
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);	    
	    		std::string myDI = formEntrada->createArrDi(localDatabase);
	    		//if(!formEntrada->isIncArrPlateEdited()) //chequeo de imagen
	      		formEntrada->savePlateImage(1,"entrada");
	    		pvSetText(p,EDITDIPROV,myDI.c_str());
				break;
	  		}
			case 322:
			case 122: //weigth ok, waiting for proceed
			case 40:
			case 22:
	  			refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	  			break;
			case 235:
			case 135:
			case 35:
			case 325:
			case 125: //ANIMATION STATE TAKING TRUCK WEIGHT
			case 25: //ANIMATION STATE
	  			break;
			case 326:
			case 236:
			case 136:
			case 126://communication and taking weight
			case 36:
      		case 26: //comm
	  		{
	    		char error[256];
	    		bascula * testBascula = NULL;
	    		//reseteamos peso
	    		std::string sPesoTest = "0";
	    		pvSetText(p,EDITPESOENT,sPesoTest.c_str());
	    		formEntrada->setArrScaleIn(0);
	    		formEntrada->incArrScaleEdited(0);
	    		//
	    		sprintf(error,"(INFO) usando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, paridad:%s , control de flujo:%s y %s bits de parada...",1, basculas.at(0).port.c_str(),basculas.at(0).bauds,basculas.at(0).timeout , basculas.at(0).ask.c_str(), (basculas.at(0).parity==0?"ninguna":(basculas.at(0).parity==1?"impar":"par")),(basculas.at(0).ctrl==0?"ninguno":(basculas.at(0).ctrl==1?"software":"hardware")),(basculas.at(0).stopBits==0?"1":(basculas.at(0).stopBits==1?"1,5":"2")));
	    		console.push_back(error);
	    		testBascula = new bascula(basculas.at(0).port,basculas.at(0).bauds);
	    		if(!basculas.at(0).ask.empty())
	      		{
					testBascula->set_parity(basculas.at(0).parity);
					testBascula->set_flowControl(basculas.at(0).ctrl);
					testBascula->set_stopBits(basculas.at(0).stopBits);
					//no capturamos excepciones
					testBascula->setCommand(basculas.at(0).ask);	     
					std::cout << "(INFO) leyendo peso!" << std::endl;
					char* texto;
					try
		  			{
		    			int ret = testBascula->readPeso(basculas.at(0).timeout,texto);
		    			std::string sPeso =  fromBufferAPeso(texto);
		    			try
		      			{
		        			formEntrada->setArrScaleIn(std::stoi(sPeso));
		      			}
		    			catch (...)
		      			{
							formEntrada->setArrScaleIn(0);
							sPeso = "0";
		      			}
		    			pvSetText(p,EDITPESOENT,sPeso.c_str());
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
				{
	      			delete testBascula;
				}
				break;
	  		}
			case 230:
			case 130: //all products chosen
			case 30:
	  		{
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);	    
	    		//
	    		std::string type;
	    		myStation->getType(type);
	    		//TODO database inside formulario
	    		//formEntrada->updtAllProducts(localDatabase,type.c_str());
	    		//	    
	    		char * sql =NULL;
	    		selAllProdsCodesPermsFromProductos(sql,type.c_str());
	    		localDatabase.query(p,sql);
	    		d->allProductos.clear();
	    		d->allProductos2.clear();
	    		d->allProductos3.clear();
	    		d->allProductosCodes.clear();
	    		d->allProductosLers.clear();
	    		d->allPermisosNecesariosProducto.clear();
	    		std::vector <std::vector <std::string>> dataReturn;
	    		dataReturn = localDatabase.retData2();
	    		std::vector<std::vector<std::string>>::iterator iRows;
	    		std::vector<std::string>::iterator iCols;
	    		int col = 0;
	    		for(iRows = dataReturn.begin(); iRows != dataReturn.end(); ++iRows)
	      		{
					col = 0;
					for(iCols = iRows->begin(); iCols != iRows->end(); ++iCols)
		  			{
		    			//std::cout << "col:" << col << " valor:" << *iCols << std::endl;
		    			if(col == 0) //codigo
		      				d->allProductosCodes.push_back(*iCols);
		    			else if(col==1) //codigo ler
		      				d->allProductosLers.push_back(*iCols);
		    			else if(col == 2) //nombre 1
		      				d->allProductos.push_back(*iCols);
		    			else if(col == 3) //nombre 2
		      				d->allProductos2.push_back(*iCols);
		    			else if(col == 4) //nombre 3
		      				d->allProductos3.push_back(*iCols);
		    			col++;
		  			}
	      		}	    
	    		std::vector <std::string> allProdsCodes4Combo;
	    		for (int i=0; i < d->allProductos.size(); i++)
	      			allProdsCodes4Combo.push_back(d->allProductosLers[i]  + " " + d->allProductos[i] + " " + d->allProductos2[i] + " " + d->allProductos3[i]+ " " + d->allProductosCodes[i]);
	    		populateCombo(p,COMBOLERS,allProdsCodes4Combo);
	    		d->comboProducto2.clear();
				break;
			}
			case 231:
			case 131:
			case 31: //Product selected and its permits shown
	  		{
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    		//
	    		std::string type;
	    		myStation->getType(type);
	    		formEntrada->setArrCosProdPermits(localDatabase, type.c_str());	   
				break;
	  		}
			case 232:
			case 132: //product authorized
			case 32:
	  		{
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    		//
	    		std::string myDI = formEntrada->createArrDi(localDatabase);
	    		//if(!formEntrada->isIncArrPlateEdited())//chequeo de imagen
	      		formEntrada->savePlateImage(1,"entrada");
	    		pvSetText(p,EDITDIPROV,myDI.c_str());
				break;
	  		}
			case 99: //Vehículo a tránsito y borramos formulario
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
	    		if(formEntrada->storeTransit(localDatabase,remoteDatabase,myStation,remote_connected))
	    		{
		    		console.push_back("AVISO: no se consiguió escribir el movimiento a tránsito en la base de datos remota, sincronice cuando pueda");
		    		console.push_back("AVISO: tenga en cuenta que si es un movimiento de transferencia, este seguirá en el sistema, pida a administración que lo borren");
	    		}
				break;
	  		}
			case 101: //matrícula no registrada
	  			refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	  			break;
			case 110: //matrícula no registrada AUTORIZADA elegir cliente
	  		{
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    		// TODO: database access out of GUI
				//seleccionamos todos los clientes
	    		char * sql = NULL;
	    		selAllDatFrmCostumers(sql);
	    		localDatabase.query(p,sql);
				if (sql != NULL)
				{
	    			delete[] sql;
				}
	    		d->allClientes.clear();
	    		d->allClientesCodes.clear();
	    		std::vector <std::vector <std::string>> dataReturn;
	    		dataReturn = localDatabase.retData2();
	    		int row,col=0;
	    		for(row=0;row<dataReturn.size();row++)
	      		{
					for(col=0;col<dataReturn[row].size();col++)
		  			{
		    			if(col==1)
		     	 			d->allClientes.push_back(dataReturn[row][col]);
		    			if(col==0)
		      				d->allClientesCodes.push_back(dataReturn[row][col]);
		  			}
	      		}
	    		populateCombo(p,COMBOCLIENTES,d->allClientes);
	    		break;
	  		}
			case 210: //Particular client
	  		{
				//TODO revisar estado, sql va fuera
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    		//cleaning possible garbage
	    		d->editClient.clear();
	    		//Client "OTROS" selection
	    		std::string sql = "select CODIGO_CLIENTE from CLIENTES where NOMBRE = \'OTROS\'";
	    		localDatabase.query(p,sql.c_str());
	    		std::vector <std::vector <std::string>> dataReturn;
	    		dataReturn = localDatabase.retData2();
	    		//TODO TO IMPROVE // ERROR CATCHING
	    		if(dataReturn.size())
	      		{
					try
		  			{
		    			formEntrada->setArrCosCode(std::stoi(dataReturn[0][0]));
		  			}
					catch (...)
		  			{
		    			formEntrada->setArrCosCode(0);
		  			}
	      		}
	    		//////
	    		pvClear(p,COMBOCLIENTES);
	    		pvSetText(p,COMBOCLIENTES,"OTROS"); //lo miramos en base de datos?
	    		break;
	  		}
			case 321: //transfer movement
	  		{
	    		//operator comment
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTENT);
	    		//COSTUMER
	    		formEntrada->setArrCosCode(DEF_BIORECICLAJE_CODE);	    
	    		formEntrada->setAllArrCostumerData(localDatabase);
	    		pvSetText(p,EDITCLIENTES,formEntrada->retArrCosName().c_str());	    
	    		//PRODUCT
	    		formEntrada->setAllArrProductData(localDatabase);	    
	    		std::string productText = "(";
	    		productText += formEntrada->retArrProdLER();
	    		productText +=  ") ";
	    		productText += formEntrada->retArrProdName1();
	    		productText += " ";
	    		productText += formEntrada->retArrProdName2();
	    		productText += " ";
	    		productText += formEntrada->retArrProdName3(); 
	    		pvSetText(p,EDITPRODUCTOS,productText.c_str());		
	    		//DI and folder
	    		std::string myDI = formEntrada->createArrDi(localDatabase);
	    		//if(!formEntrada->isIncArrPlateEdited())//chequeo de imagen
	      		formEntrada->savePlateImage(1,"entrada");
	  	  		pvSetText(p,EDITDIPROV,myDI.c_str());
				break;
	  		}
			case 1000: //salida de descargar
			{
	    		if(syncro_needed(&my_syncro_data))
	    		{
					globalSyncronization(p,d,formEntrada);
					stateGUI(p,d, formEntrada->getState());
					syncro_done(&my_syncro_data);
	    		}
	    		//commons
	    		popteTransito(p,d,TABLATRANSITO, formEntrada);
	    		d->transito_plate.clear();
	    		d->post_transito_plate.clear();
				break;
			}
			case 1011: //taking plate camera2
	  		{
	    		std::string plate;	    
	    		ret = useCamera(p, d, 2, plate, IMCAM_E2);
	    		if(!ret)
	      		{
					pvSetText(p,EDITCAM_E2,pvtr(plate.c_str()));
					formEntrada->setDepPlate(plate);
					d->processTag=1;
	      		}
	    		else
	      		{
					d->processTag=-1;
					sprintf(error,"**ERROR** imposible recibir matrícula de la cámara 2");
					console.push_back(error);
	      		}
	    		break;
	  		}
			case 1020: //hemos seleccionado un transporte de la tabla de tránsito
	  		{
	    		//operator comment
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	    		//load DI
	    		formEntrada->createDepDi(localDatabase);	    
	    		pvSetText(p,EDITDIDEF,formEntrada->retDepDi().c_str());
	    		//if(!formEntrada->isIncDepPlateEdited())//chequeo de imagen
	    		formEntrada->savePlateImage(2,"salida");
	    		std::string pesoSalida = std::to_string(formEntrada->retDepScaleOut());
	    		pvSetText(p,EDITPESOTARA,pesoSalida.c_str());
	    		//default driver
	    		if(formEntrada->default_driver(localDatabase))
	      		{
					driver *tmp_driver;
					formEntrada->ret_dep_driver(tmp_driver);
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
			case 1021: //almacenamos la tara en DB
	  		{
	    		//saving weight!
	    		d->test = 0;
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	    		int DatabaseData_chkd;
	    		try
	      		{
					DatabaseData_chkd= std::stoi(remoteDatabaseData.db_port);
	      		}
	    		catch(...)
	      		{
					DatabaseData_chkd = 0;
	      		}
	    		formEntrada->saveScaleOut(localDatabase,remoteDatabase,remoteDatabaseData.db_host.c_str(), DatabaseData_chkd);
				break;
	  		}
			case(1022):
	  			refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	  			break;
			case 1024://retrieving all DI data
	  		{
	    		costumer * ourId = new costumer(DEF_BIORECICLAJE_CODE,localDatabase);
	    		formEntrada->setOurId(ourId);
	    		delete ourId;
	    		formEntrada->setAllDiData(localDatabase, myStation, DEF_BIORECICLAJE_CODE, DEF_TRANS_CODE);
				break;
	  		}
      		case 1026: //pesaje2
	  		{
	    		char error[256];
	    		bascula * testBascula = NULL;
	    		//reseteamos peso
	    		std::string sPesoTest = "0";
	    		pvSetText(p,EDITPESOTARA,sPesoTest.c_str());
	    		formEntrada->setDepScaleOut(0);
	    		formEntrada->incDepScaleEdited(0);
	    		//
	    		sprintf(error,"(INFO) usando báscula %d con puerto:%s , baudios:%d , timeout de %d milisegundos , comando:%s, paridad:%s , control de flujo:%s y %s bits de parada...",2, basculas.at(1).port.c_str(),basculas.at(1).bauds,basculas.at(1).timeout , basculas.at(1).ask.c_str(), (basculas.at(1).parity==0?"ninguna":(basculas.at(1).parity==1?"impar":"par")),(basculas.at(1).ctrl==0?"ninguno":(basculas.at(1).ctrl==1?"software":"hardware")),(basculas.at(1).stopBits==0?"1":(basculas.at(1).stopBits==1?"1,5":"2")));
	    		console.push_back(error);
	    		testBascula = new bascula(basculas.at(1).port,basculas.at(1).bauds);
	    		if(!basculas.at(1).ask.empty())
	      		{
					testBascula->set_parity(basculas.at(1).parity);
					testBascula->set_flowControl(basculas.at(1).ctrl);
					testBascula->set_stopBits(basculas.at(1).stopBits);
					//no capturamos excepciones
					testBascula->setCommand(basculas.at(1).ask);	     
					std::cout << "(INFO) leyendo peso!" << std::endl;
					char* texto;
					try
		  			{
		    			int ret = testBascula->readPeso(basculas.at(1).timeout,texto);
		    			std::string sPeso =  fromBufferAPeso(texto);
		    			try
		      			{
		        			formEntrada->setDepScaleOut(std::stoi(sPeso));
		      			}
		    			catch (...)
		      			{
							formEntrada->setDepScaleOut(0);
							sPeso = "0";
		      			}
		    			pvSetText(p,EDITPESOTARA,sPeso.c_str());
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
				{
	      			delete testBascula;
				}
				break;
	  		}
			case 1030:
			case 1031:
			{
	  			pvSetText(p,EDITCODETRANSP,std::to_string(formEntrada->retDepDriCode()).c_str());
	  			pvSetText(p,EDITNAMETRANSP,formEntrada->retDepDriName().c_str());
	  			refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	  			break;
			}
			case 1036: //firma del movimiento
	  		{
	    		//operator comment
	    		refreshOperatorComment(p,d,formEntrada,EDITCOMMENTSAL);
	    		std::string cname;
	    		std::string productText;
	    		char * sql;
	    		//COSTUMER
	    		std::string clientCode = std::to_string(formEntrada->retDepCosCode());
	    		selectClientNameByCode(sql,clientCode.c_str());
	    		localDatabase.query(p,sql);
	    		std::vector<std::vector<std::string>> ourData = localDatabase.retData2();
	    		if(ourData.size() >= 1)
	      		{
	        		cname = ourData.at(0).at(0);		
	      		}	   
	    		delete sql;
	    		//
	    		//PRODUCT
	    		std::string productCode = std::to_string(formEntrada->retDepProdCode());
	    		selectProductBasisByCode(sql,productCode.c_str());
	    		localDatabase.query(p,sql);
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
	    		delete sql;
	    		//
	    		int error = 0;	    
	    		d->miTableta = new tableta(error);
	    		if(!error)
	      		{
					//d->miTableta->init();
					//std::cout << "estableciendo la imagen" << std::endl;
					char speso[100];
					int pesoTotal =  formEntrada->retDepScaleIn() - formEntrada->retDepScaleOut();
					sprintf(speso,"%d",pesoTotal);
					std::string sspeso = speso;
					float precio = pesoTotal *  formEntrada->retDepPrice()/1000.0;
					std::string sPrecio = std::to_string (precio);
					//std::cout << cname << "," << productText << std::endl;
					d->miTableta->setInfoShow(formEntrada->retDepPlate(),cname,productText,sPrecio, sspeso);
					//std::cout << "fin de establecer la imagen" << std::endl;
					int tries = 3;
					int i=0;
					int done = 0;
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
		    			console.push_back("*ERROR* error en la tableta, desenchufe y vuelva a enchufarla e intente firmar de nuevo");
		    			if(!error)
		      				d->miTableta->reset();
		    			delete d->miTableta;
		    			d->miTableta = NULL;
		  			}
	      		}
	    		else
	      		{
					console.push_back("ERROR* ¡Tableta de firmas no detectada!");
					delete d->miTableta;
					d->miTableta = NULL;
	      		}
				break;	
	  		}
			case 1097:
	  			formEntrada->unsetStaff();
	  			pvInputDialog(p,BUTPROCEDER_E1,"Inserte el código de basculista para proceder:","");
	  			break;
			case 1099: //almacenaje del movimiento, impresión del pdf
	  		{
	    		//copia archivo firma
	    		formEntrada->saveSignature();
	    		//to DATABASE
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
      			std::cout << "trying out connection of: " + remoteDatabaseData.db_host + ":" + remoteDatabaseData.db_port;    
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
        			std::cout << "trying out connection of: " + remoteDatabaseData.local_db_host + ":" + remoteDatabaseData.local_db_port;
			  		if(isConnected(remoteDatabaseData.local_db_host.c_str(), DatabaseData_chkd))
        			{
		  	  			remote_connected = 1;
        			}
	    		}
	    		int error = formEntrada->storeDepMov(localDatabase,remoteDatabase,remote_connected);
	    		if(!error)
					console.push_back("INFO Movimiento generado correctamente");
	    		else if(error ==-1)
	    		{
					console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
					console.push_back("*ERROR* ¡Necesita sincronizar para actualizar el movimiento en el servidor central!");
	    		}
	    		else if(error == -10)
	    		{
					console.push_back("*ERROR* ¡Hubo errores al guardar el movimiento en el servidor central!");
					console.push_back("*ERROR* ¡Necesita sincronizar! Vuelva a intentarlo");
					d->error = 1;
	    		}
	    		else
				{
	    			console.push_back("*ERROR* ¡Fallo al guardar el movimiento!");
					d->error = 1;
				}
				if (!d->error)
				{
					// printing
					std::string myTicketPrinter;
					std::string ticketCode;
					miIni->retTicketPrinterId(myTicketPrinter);
					miIni->retTicketCode(ticketCode);
					if(myTicketPrinter.empty())
					{
		  				console.push_back("AVISO: no se va a imprimir el ticket, al no tener configurada la impresora");
					}
					formEntrada->createTicket(myTicketPrinter, ticketCode);
					// backing up files
					try 
					{
						formEntrada->backupFiles(formEntrada->retDepMovCode().c_str());
					} 
					catch(...)
					{
						console.push_back("*ERROR* ¡Hubo errores al guardar los ficheros del movimiento en el servidor central!");
					}
					// sending incidents email
					mailClient->sendIncidentsMail(myStation,formEntrada);
				}
	    		break;
	  		}
			default:
	  			break;
		}
		formEntrada->setState(d->enFutEstado);
      	stateGUI(p,d,formEntrada->getState());
      	ret = 0;
    }
  	return ret;
}
#endif