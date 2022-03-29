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

#ifndef _MASK4_DATA_
#define _MASK4_DATA_


typedef struct // (todo: define your data structure here)
{
  int estadoActual;
  int estadoFuturo;

  long selectedStation;
  long selectedId;
  long selectedTrans;
  
  int camPos;
  std::string selectedCam;
  std::string loadedCam;  
  std::string editedCamIp;
  std::string editedCamPort;
  std::string editedCamTimeout;
  int chsenCamRelay;
  int chsenCamRelayB;

  float error_scale;
  int basPos;
  std::string selectedBas;
  std::string loadedBas;  
  std::string editedBasPort;
  int chsenBasBauds;
  int editedBasTimeout;
  std::string editedBasAsk;
  int chsenBasParity;
  int chsenBasStopBits;
  int chsenBasFlow;

  std::string smtpServer;
  int smtpPort;
  std::string mailUser;
  std::string mailPass;
  std::string recipients;
  std::string mailName;

  std::string selectedPrinter;
  std::string loadedPrinter;
  std::string actualPrinter;

  int syncro_minutes;

  //triggers
  int f1Unloads;
  int f2Loads;
  
  //consola
  std::vector <std::string> localConsole;
}
DATA;

#endif
