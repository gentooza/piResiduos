/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
Copyright 2019-2020, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
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
void selAllDatFrmCenter(char *& sql,long code);
void selAllDatFrmLocalCenters(char *& sql);
void selExtCentersNameCode(char *& sql);
void selIntCentersNameCode(char *& sql);

//TABLE ORDERS
void selectAllFromOrders(char *& sql, long station_code);
void delOrder(char *& sltQuery, char *& myQuery,long destiny,long costumer_code, long product);
void delOrder(char *& myQuery, long order_code);
void selOrderById(char *& myQuery, long order_code);

//TABLE TRANSFERS
void selAllTransfers(char *& sql, long station_code);
void sel_all_unsyncro_transfers(char *& sql);
void delTransfer(char *& sltQuery, char *& myQuery,long origin,long destiny,long product, const char* plate);
void rmt_sel_all_transfers(char*&sql, long codigo_estacion);
void rmt_updt_transfers(char *& sql, std::vector< std::vector <std::string>> dataReturn);

//TABLE PRODUCTS
void selProdPermits(char *& sql, const char* type, long product_code);
void selProdDataByCode(char *& sql, long code);
void selProdsAllowedToClient(char *& sql, const char* codigoCliente, const char* tipoEstacion, bool temporal);
void selAllProds(char*&sql);
void sqlLoadProducts(char*& sql,std::vector<std::vector<std::string>> dataReturn);

//TABLE COSTUMERS
void selCosDataByCode(char *& sql, long code);
void selAllDatFrmCostumers(char *& sql);
void sel_all_costumers_from_car(char *& sql, char * plate);
void sel_default_driver(char *& sql, long code);

void rmt_sel_all_costumers(char *& sql);

//TABLE COSTUMERS-PRODUCTS
void selProdCosPermits(char *& sql, const char* type, long product_code, long costumer_code);
void sel_price_cos_prod(char *&sql, long product_code, long costumer_code);
void sel_DIbasis_cos_prod(char *& sql,const char* tipoEstacion, long codigoCliente, long codigoProducto);
void load_cos_prod(char*& sql,std::vector<std::vector<std::string>> dataReturn);
///remote
void rmt_sel_all_cos_prod(char*&sql);

//TABLE MOVEMENTS
void selLastDiFromMovementsByClientProduct(char *& sql, long costumer_code, long product_code);
void sel_all_unsyncro_movements(char *& sql);
void upd_all_unsyncro_movements(char *& sql);
void upd_syncro_movements(char*& sql,std::vector<std::vector<std::string>> dataReturn);
///remote
void rmt_sel_last_movement(char *& sql,long codigo_estacion,int year);

//TABLE ARRIVING TRANSIT
void updtScaleOutTransSal(char *& sql, const char* fecha_hora, long codigo_cliente, long codigo_producto, unsigned int peso_salida, const char* comentario, const char * incidencias);
void sel_all_unsyncro_transito(char *& sql, int codigo_estacion);
void sel_all_transito(char *& sql, int codigo_estacion);
void sel_all_transito(char *& sql);
void rmt_del_transito(char *& sql, int fromStation);

//TABLE DEPARTURE TRANSIT
void updtScaleOutTrans(char *& sql, const char* fecha_hora, long codigo_cliente, long codigo_producto, unsigned int peso_salida, const char* comentario, const char * incidencias);
void  updtScaleOutTransSal(char *& sql, const char* fecha_hora, long codigo_orden, unsigned int peso_salida, const char* comentario, const char * incidencias);
void sel_all_unsyncro_transito_dep(char *& sql,long codigo_estacion);
void sel_all_transito_dep(char *& sql);
void rmt_selAllFromTransitoSalidas(char *& sql,long fromStation);
void rmt_del_transito_dep(char *& sql, long fromStation);
void sqlLoadTransitoSalidas(char*& sql,std::vector<std::vector<std::string>> dataReturn);

//TABLE CARS
void sel_all_cars(char *& sql);
void sel_all_cos_from_car(char *&sql, const char *matricula);
void loadCars(std::string& sql,std::vector<std::vector<std::string>> dataReturn);
void rmtSelAllCars(std::string& sql);

//TABLE STAFF
void sel_staff_data_by_code(char *&sql, long code);
void selAllStaffData(char*& sql,long code);
void load_staff(char*& sql, std::vector<std::vector<std::string>> load_data);

void rmt_sel_all_staff(char *& sql);

//TABLE BILLING
void sel_fp_by_cos_code(char *&, long);
void load_billing(char *& sql,std::vector< std::vector< std::string>> load_data);
///remote
void rmt_sel_all_billing(char *& sql);

//TABLE DRIVERS
void sel_driver_data_by_code(char *& sql, long code);
void selAllDatFrmDrivers(char *& sql);

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
void selectClientNameByCode(char *& sql, const char* code);
void selectProductDataByCode(char *& sql, const char* code);
void selectProductBasisByCode(char *& sql, const char* code);
void selectProductBasisByCode(char *& sql, long code);
void selLastDiFromMovementsByClientProduct(char *& sql, const char* codigoCliente, const char* codigoProducto);
void selLastDiFromMovementsByClient(char *& sql, const char* codigoCliente);

void selLastMovCode(char *& sql,const char* codigo_estacion);
void selAllDrivers(char *&sql);
void selAllMovements(char*&sql);


void delTransfer(char*&sql,const char* fecha_hora, long codigo_origen, long codigo_destino);

//remote mysql
std::string remote_selectAllCostumers();
void remote_selectAllProducts(char*&sql);
void remote_selectAllOrders(char *& sql, const char* fromStation);
void remote_selectAllDrivers(char*&sql);
void rmt_selAllFromTransito(char *& sql,int fromStation);
void rmt_selAllStations(char *& sql);
void rmt_selAllMovements(char *& sql);

////syncronize
//local
std::string sqlLoadCostumers(std::vector<std::vector<std::string>> dataReturn);
void sqlLoadTransfers(char*& sql,std::vector<std::vector<std::string>> dataReturn);
void sqlLoadOrders(char*& sql,std::vector<std::vector<std::string>> dataReturn);
void sqlLoadDrivers(char*& sql,std::vector<std::vector<std::string>> dataReturn);
void sqlLoadTransito(char*& sql,std::vector<std::vector<std::string>> dataReturn);
void sqlLoadStations(char *& sql,std::vector<std::vector<std::string>> dataReturn);

//remote
void rmt_updtMovements(char*& sql, std::vector<std::vector<std::string>> dataReturn);
void rmt_updtTransito(char *& sql, std::vector<std::vector<std::string>> dataReturn, int codigo_estacion);
void rmt_updtTransitoSalidas(char *& sql, std::vector<std::vector<std::string>> dataReturn, int codigo_estacion);
void remote_updatePesoSalidaTransito(std::string & sql, long costumer_code, const char* date_time, int station_code, unsigned int scale,const char * comentario, const char* incidents);
void remote_updatePesoSalidaTransitoSalida(std::string & sql, long costumer_code, const char* date_time, long station_code,  unsigned int scale, const char* comentario, const char* incidents);
#endif
