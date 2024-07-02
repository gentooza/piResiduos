/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2020, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
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
@file database.h
*/

#ifndef _DATABASE_RESIDUOS_
#define _DATABASE_RESIDUOS_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include "generic_tools.h"

enum {
  MIN_STATION_TYPE = 0,
  STATION_TYPE_PT,
  STATION_TYPE_ET,
  STATION_TYPE_D5,
  STATION_TYPE_PL,
  STATION_TYPE_EXTERNO,
  MAX_STATION_TYPE
};


//TABLE CENTERS
void selAllDatFrmCenter(std::string& sql,long code);
void selAllDatFrmLocalCenters(std::string& sql);
void selExtCentersNameCode(char *& sql);
void selIntCentersNameCode(char *& sql);

void rmtSelAllCenters(std::string& sql);

void loadCenters(std::string& sql, std::vector<std::vector<std::string>> dataReturn);

//TABLE ORDERS
void selAllFromOrders(std::string& sql, long station_code);
void delOrder(std::string& sltQuery, std::string& myQuery,long destiny,long costumer_code, long product);
void selOrderById(std::string& myQuery, long order_code);

void rmtSelAllOrders(std::string& sql, long fromStation);

void loadOrders(std::string& sql, std::vector<std::vector<std::string>> dataReturn);

//TABLE TRANSFERS
void selAllTransfers(char *& sql, long station_code);
void selAllUnsyncroTransfers(std::string& sql);
void delTransfer(char *& sltQuery, char *& myQuery,long origin,long destiny,long product, const char* plate);

void rmtSelAllTransfers(std::string& sql, long codigo_estacion);
void rmtUpdtTransfers(std::string& sql, std::vector< std::vector <std::string>> dataReturn);

void loadTransfers(std::string& sql, std::vector<std::vector<std::string>> dataReturn);

//TABLE PRODUCTS
void selProdPermits(char *& sql, const char* type, long product_code);
void selProdDataByCode(char *& sql, long code);
void selProductBasisByCode(std::string& sql, std::string code);
void selProdsAllowedToClient(char *& sql, const char* codigoCliente, const char* tipoEstacion, bool temporal);
void selAllProds(char*&sql);

void rmtSelAllProducts(std::string& sql);

void loadProducts(std::string& sql,std::vector<std::vector<std::string>> dataReturn);

//TABLE COSTUMERS
void selCosDataByCode(std::string& sql, long code);
void selAllDatFrmCostumers(char *& sql);
void selCostumerNameByCode(std::string& sql, std::string code);
void sel_default_driver(char *& sql, long code);

void rmtSelAllCostumers(std::string& sql);

void loadCostumers(std::string& sql, std::vector<std::vector<std::string>> dataReturn);

//TABLE COSTUMERS-PRODUCTS
void selProdCosPermits(char *& sql, const char* type, long product_code, long costumer_code);
void sel_price_cos_prod(char *&sql, long product_code, long costumer_code);
void sel_DIbasis_cos_prod(char *& sql,const char* tipoEstacion, long codigoCliente, long codigoProducto);

void rmtSelAllCosProds(std::string& sql);

void loadCosProds(std::string& sql, std::vector<std::vector<std::string>> dataReturn);

//TABLE MOVEMENTS
void selLastDiFromMovsByClientProduct(std::string& sql, long costumer_code, long product_code);
void selAllUnsyncroMovs(std::string& sql);
void updtAllUnsyncroMovs(std::string& sql);
void updtSyncroMovs(std::string& sql, std::vector<std::vector<std::string>> dataReturn);

void rmtUpdtMovs(std::string& sql, std::vector<std::vector<std::string>> dataReturn);
void rmtSelLastMov(std::string& sql, long codigo_estacion, int year);
void selLastMovCode(std::string& sql, std::string codigo_estacion);

//TABLE ARRIVING TRANSIT
void updtScaleOutTrans(char *& sql, const char* fecha_hora, long codigo_cliente, long codigo_producto, unsigned int peso_salida, const char* comentario, const char * incidencias);
void sel_all_unsyncro_transito(char *& sql, int codigo_estacion);
void selAllTransit(std::string& sql, long codigo_estacion);
void selAllTransit(std::string& sql);

void rmtDelTransit(std::string& sql, long fromStation);
void rmtUpdtTransit(std::string& sql, std::vector<std::vector<std::string>> dataReturn, long codigo_estacion);

//TABLE DEPARTURE TRANSIT
void updtScaleOutTransSal(std::string& sql, std::string fecha_hora, long codigo_cliente, long codigo_producto, long peso_salida, std::string comentario, std::string incidencias);
void sel_all_unsyncro_transito_dep(char *& sql,long codigo_estacion);
void selAllTransitDep(std::string& sql);

void rmt_selAllFromTransitoSalidas(char *& sql,long fromStation);
void rmtDelTransitDep(std::string& sql, long fromStation);
void rmtUpdtTransitDep(std::string& sql, std::vector<std::vector<std::string>> dataReturn, long codigo_estacion);

void sqlLoadTransitoSalidas(char*& sql,std::vector<std::vector<std::string>> dataReturn);

//TABLE CARS
void sel_all_cars(char *& sql);
void selCostumersFromCar(std::string& sql, std::string matricula);

void rmtSelAllCars(std::string& sql);

void loadCars(std::string& sql,std::vector<std::vector<std::string>> dataReturn);

//TABLE STAFF
void sel_staff_data_by_code(char *&sql, long code);
void selAllStaffData(char*& sql,long code);

void rmtSelAllStaff(std::string& sql);

void loadStaff(std::string& sql, std::vector<std::vector<std::string>> load_data);

//TABLE BILLING
void sel_fp_by_cos_code(char *&, long);

void rmtSelAllBilling(std::string& sql);

void loadBilling(std::string& sql,std::vector< std::vector< std::string>> load_data);

//TABLE DRIVERS
void selDriverDataByCode(std::string& sql, long code);
void selAllDrivers(std::string& sql);
void rmtSelAllDrivers(std::string& sql);
void loadDrivers(std::string& sql, std::vector<std::vector<std::string>> dataReturn);

// PARAMS
void getParamValue(std::string& sql, std::string pname);
void setParamValue(std::string& sql, std::string pname, std::string pvalue, std::string year);

//unsorted and deprecated
void selectAllFromClient(char *&sql, const char *cliente);
void selNifFromCostumersByCode(char *&sql, const char *costumerCode);
void selectAllFromLer(char *&sql, const char *ler);
void selectVehicsFromClient(char *&sql, int cod_cliente);
void selAllProdsCodesPermsFromProductos(char *&sql,const char* tipoEstacion);
void selPermitsTypeClientProd(char *& sql,const char* tipoEstacion, const char* codigoCliente, const char* codigoProducto);
void selPermitsFromClientAndProd(char *& sql,const char* tipoEstacion, const char* codigoCliente, const char* codigoProducto);
void selProdsCodesPermsFromClienteProductos(char *& sql, const char* cliente , const char* estacion);
void selProdsPermsFromProductosByCode(char *& sql, std::vector <std::string> prodCodes, const char* estacion);
void selectProductDataByCode(char *& sql, const char* code);
void selLastDiFromMovementsByClient(char *& sql, const char* codigoCliente);

void delTransfer(char*&sql,const char* fecha_hora, long codigo_origen, long codigo_destino);

//remote mysql
std::string remote_selectAllCostumers();
void rmt_selAllFromTransito(char *& sql,int fromStation);

////syncronize
//local
void sqlLoadTransito(char*& sql,std::vector<std::vector<std::string>> dataReturn);

//remote
void remote_updatePesoSalidaTransito(std::string & sql, long costumer_code, const char* date_time, int station_code, unsigned int scale,const char * comentario, const char* incidents);
void remote_updatePesoSalidaTransitoSalida(std::string & sql, long costumer_code, const char* date_time, long station_code,  unsigned int scale, const char* comentario, const char* incidents);
#endif
