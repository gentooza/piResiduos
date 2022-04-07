/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>

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
@file inputForm.h
*/
#ifndef _INPUT_FORM_
#define _INPUT_FORM_

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
#include <boost/algorithm/string.hpp>
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
#include "formulario.h"


class inputForm: public baseForm
{
 public:
 inputForm(int type) : baseForm(type,1){formSCADA=1;};
 inputForm() : baseForm(){};
  ~inputForm(){};

  int getFormType(){return DISCHARGE_FORM;};
  //movement data
  int storeDepMov(qtDatabase & localDatabase,qtDatabase & remoteDatabase, int remote_host_connected);
  //database dependant
  int storeTransit(qtDatabase & myDatabase,qtDatabase & remoteDatabase, station * myStation, int remote_host_connected);

  int isTrf(qtDatabase & myDatabase, station*& myStation);
  int setTrfMov(qtDatabase & myDatabase, station *& myStation);
  void setDepMov(int index, qtDatabase& myDatabase);
  void setTransit(std::vector<std::vector<std::string>> transit){vctAllTransit.clear(); vctAllTransit = transit; return;};
  std::vector<std::vector<std::string>> retTransit(){return vctAllTransit;};
  int isPlateInTransit(std::string);
  int setTransitMov(int index, std::string plate, qtDatabase & myDatabase);
  int delTransit(int index,std::string plate, qtDatabase & myDatabase, qtDatabase & myRemoteDatabase, std::string host, int port, long station_code);

  //all costumers
  std::vector<std::string> retAllCos4Combo(qtDatabase & myDatabase);
  ///

  //product permits
  //datatabase dependant
  void setArrCosProdPermits(qtDatabase & myDatabase, const char* type){setArrCosProdPermitsBase(myDatabase,type);};
  void forceCurrentProduct();
  void unforceCurrentProduct();
  int getFzCurrentProduct();

  //scaling
  int isArrPesoOk();
  int isDepPesoOk();
  int retDepScaleExpected(){return 0;};
  void setAndCalcScaleOut(unsigned int scale);
  int saveScaleOut(qtDatabase & myDatabase, qtDatabase &myRemoteDatabase, const char * remoteHost, int remotePort );
  //
  int setMovCode(std::string sLastCode, int stationCode, int movementTypeCode);

  //DI INFORMATION
  void setAllDiData(qtDatabase & localDatabase, station *myStation, long ourCode, long defDriverCode);
  int isDiComplete();
  int isDiCostumerDefined();
  
  std::vector <std::string> allClientes;
  std::vector <std::string> allClientesCodes;

  void createPdf(std::string printerId);

  int createTicket(std::string printerId, std::string ticketCode);
  void calculateTicketHeight(int& lines);
  void ticketHeader(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, std::string ticketCode, float fsize_small);
  void ticketStationTitle(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium);
  void ticketRegistrationData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketOriginData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketTransportData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketProductData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  void ticketWeightData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float size_big, float size_medium, float size_small);
  
  //
 private:
  std::vector<std::vector<std::string>> vctAllTransfers;
  std::vector<std::vector<std::string>> vctAllTransit;
};

#endif

