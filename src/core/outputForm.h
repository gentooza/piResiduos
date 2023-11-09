/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
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
/**
@file outputForm.h
*/
#ifndef _OUTPUT_FORM_
#define _OUTPUT_FORM_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> 
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cups/cups.h>
#include <sys/stat.h>
#include <unistd.h>

#include <math.h>
#include <setjmp.h>
#include "hpdf.h"
#include "generic_tools.h"
#include "qtdatabase.h"
#include "database.h"
#include "station.h"
#include "baseForm.h"


class outputForm: public baseForm
{
 public:
 outputForm(int type) : baseForm(type,0){formSCADA=2;};
 outputForm() : baseForm(){};
  ~outputForm(){};

  int getFormType(){return LOAD_FORM;};
  
  int storeDepMov(qtDatabase & localDatabase,qtDatabase & remoteDatabase,int remote_host_connected);
  int storeDepTransfer(qtDatabase & my_local_database, qtDatabase & my_remote_database, int remote_host_connected);
   /*ORDERS*/
  void setOrders(qtDatabase & myDatabase, long station_code);
  std::vector<std::string> retOrdersTable();
  std::vector<struMovement> retOrders(){return allOrders;};
  struMovement selOrder(unsigned int index);

  /*TRANSIT*/
  int storeTransit(qtDatabase & myDatabase,qtDatabase & remoteDatabase, station * myStation, int remote_host_connected);
  void setTransit(std::vector<std::vector<std::string>> transit){vctAllTransit.clear(); vctAllTransit = transit; return;};
  std::vector<std::vector<std::string>> retTransit(){return vctAllTransit;};
  int isPlateInTransit(std::string);
  int setTransitMov(int,std::string,qtDatabase &myDatabase);
  int delTransit(int index,std::string plate, qtDatabase & myDatabase, qtDatabase & myRemoteDatabase, std::string host, int port, long station_code);

  /*TRANSFERS*/
  void setTransferMov(costumer *& myCostumer, station *& myStation);
  
  int isArrMov();
 
  //product permits
  //datatabase dependant
  void setArrCosProdPermits(qtDatabase & myDatabase){setArrCosProdPermitsBase(myDatabase,"SAL");};
  void forceCurrentProduct();
  void unforceCurrentProduct();
  int getFzCurrentProduct();
  //
  //int setArrPlateImage(std::string newPlateImage){myArrMovement.IMAGEN_MATRICULA = newPlateImage; return 0;};
  //std::string retArrPlateImage(){return myArrMovement.IMAGEN_MATRICULA;};
  //
  //scaling 
  int isArrPesoOk();
  int isDepPesoOk();
  int retDepScaleExpected();
  void setAndCalcScaleOut(unsigned int scale);
  int saveScaleOut(qtDatabase & myDatabase, qtDatabase &myRemoteDatabase, const char * remoteHost, int remotePort );
  //
  //codigo movimiento
  int setMovCode(std::string lastCode, int stationCode, int movementTypeCode);
  //
  //DI INFORMATION
  void setAllDiData(qtDatabase & localDatabase, station *myStation, long ourCode, long defDriverCode);
  int getAllOrderInfo(qtDatabase & localDatabase, long order_code);
  int isDiComplete();

  void createPdf(std::string printerId);

  int createTicket(std::string printerId, std::string ticketCode);
  void calculateTicketHeight(int& lines);
  void ticketHeader(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, std::string ticketCode, float fsize_small);
  void ticketStationTitle(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium);
  void ticketRegistrationData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketDestinationData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketTransportData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketProductData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketWeightData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketPaidData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketCommentData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketStaffData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  
    
 private:
  std::vector<std::vector<std::string>> vctAllOrders;
  std::vector<std::vector<std::string>> vctAllTransit;
  std::vector <struMovement> allOrders;
};

#endif
