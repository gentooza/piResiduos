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

#ifndef _MASK8_DATA_
#define _MASK8_DATA_


typedef struct // (todo: define your data structure here)
{
  
  std::vector<std::string> comboList;
  std::string comboSet;
  long comboCode;
  int comboPos;
  
  //formulario
  std::string formEnCliente;
  int enFutEstado;
  int entrarDescargar;

  //triggers
  int retroceder;
  int cancelar;
  int proceder;
  int plateTaking;
  int processTag;
  int pesaje1;
  int pesaje2;
  int firmar;
  int firmado;
  int fzProducto;
  int fzAutorized;
  int noClient;
  int test;
  
  int lastMask;

  //consola
  std::vector <std::string> localConsole;

}
DATA;

#endif
