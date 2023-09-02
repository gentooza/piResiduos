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

#ifndef _MASK7_DATA_
#define _MASK7_DATA_


typedef struct // (todo: define your data structure here)
{
  std::string comboCliente;
  std::string editClient;
  std::string tmpClient;
  std::string comboProducto;
  std::string comboProducto2;

  std::string camImage;
  std::string txtPlate;
  std::string enPlate;
    
  std::vector <std::string> allVehiculos;
  
  std::vector <std::string> allClientes;
  std::vector <std::string> allClientesCodes;

  std::string productoActual;
  std::string productoCodeActual;  
  std::vector <std::string> allProductos;
  std::vector <std::string> allProductos2;
  std::vector <std::string> allProductos3;
  std::vector <std::string> allProductosCodes;
  std::vector <std::string> allProductosLers;
  std::vector <std::vector <std::string>> allPermisosNecesariosProducto;
  std::vector <std::string> allPermisosProductoCliente;

  //
  //finales
  int camionElegido;
  
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
