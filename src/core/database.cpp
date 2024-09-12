/*
This file is part of PiResiduos.

Copyright 2017-2018 Prointegra SL.
Copyright 2019-2020 Pixelada S. Coop. And. <info (at) pixelada (dot) org>
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
@file database.cpp
*/
#include "database.h"

/*! SELECT queries */
//table CENTERS
void selAllDatFrmCenter(std::string& sql, long code)
{ 
    sql = "select CODIGO_CENTRO, TIPO_CENTRO, NOMBRE, NIF, DIRECCION, PROVINCIA, ";
    sql += "POBLACION, CP, COMUNIDAD_AUTONOMA,NIMA, NUM_INSCRIPCION, TELEFONO, MAIL, BORRADO ";
    sql += "FROM CENTROS WHERE CODIGO_CENTRO = ";
    sql += std::to_string(code);
    sql += "  AND (BORRADO is null or BORRADO = 0);";

    return;
}

void selAllDatFrmLocalCenters(std::string& sql)
{
    sql = "select CODIGO_CENTRO, TIPO_CENTRO, NOMBRE, NIF, DIRECCION, PROVINCIA, ";
    sql += "POBLACION, CP, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL, BORRADO ";
    sql += "FROM CENTROS WHERE TIPO_CENTRO > 0 AND TIPO_CENTRO < 5;";

    return;
}

void selExtCentersNameCode(char *& sql)
{
  sql = new char[sizeof("select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO =5")+30];
   
  sprintf(sql,"select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO =5");

  return;

}
void selIntCentersNameCode(char *& sql)
{
  sql = new char[sizeof("select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO <5")+30];
   
  sprintf(sql,"select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO <5");

  return;

}

void rmtSelAllCenters(std::string& sql)
{
    sql = "select CODIGO_CENTRO,TIPO_CENTRO,NOMBRE,NIF,DOMICILIO,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO FROM centros WHERE BORRADO = 0";
    return;
}

void loadCenters(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into centros (codigo_centro, tipo_centro, NOMBRE,NIF,DIRECCION,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}

//TABLE STATION_DI and remote CENTROS_DI
void rmtSelAllStationDIs(std::string& sql, long stationId)
{
    sql = "select MES, ANYO, DI FROM centros_di ";
    sql += "WHERE CODIGOCENTRO_DI = " + std::to_string(stationId);
    return;
}

void loadStationDIs(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into STATION_DI (MONTH, YEAR, DI) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end(); ++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}

//table orders
void selAllFromOrders(std::string& sql, long station_code)
{
    sql = "SELECT ORDENES.CODIGO_ORDEN, ORDENES.ECOEMBES, ORDENES.CODIGO_CLIENTE, ";
    sql += "ORDENES.CODIGO_PRODUCTO, ORDENES.FECHA_FIRMA, ORDENES.FECHA_PROGRAMADA, ";
    sql += "ORDENES.PRECIO_TN, ORDENES.PESO_A_RETIRAR, ORDENES.CODIGO_DESTINO, ";
    sql += "ORDENES.OPERACION_TRATAMIENTO, ORDENES.REPETIR, ORDENES.TIPO_OPERADOR, ";
    sql += "ORDENES.CODIGO_INFO_ORIGEN_CENTRO, ORDENES.CODIGO_INFO_ORIGEN_AUTORIZADO, ";
    sql += "ORDENES.CODIGO_INFO_DESTINO_CENTRO, ORDENES.CODIGO_INFO_DESTINO_AUTORIZADO, ";
    sql += "ORDENES.INFO_DESTINO_CENTRO_NOMBRE, ORDENES.INFO_DESTINO_CENTRO_NIF, ";
    sql += "ORDENES.INFO_DESTINO_CENTRO_DIRECCION, ORDENES.INFO_DESTINO_CENTRO_CP, ";
    sql += "ORDENES.INFO_DESTINO_CENTRO_MUNICIPIO, ORDENES.INFO_DESTINO_CENTRO_PROVINCIA, ";
    sql += "ORDENES.INFO_DESTINO_CENTRO_COMUNIDAD_AUTONOMA, ORDENES.INFO_DESTINO_CENTRO_NIMA, ";
    sql += "ORDENES.INFO_DESTINO_CENTRO_N_INSC_REGISTRO, ORDENES.INFO_DESTINO_CENTRO_TELEFONO, ";
    sql += "ORDENES.INFO_DESTINO_CENTRO_EMAIL, ORDENES.INFO_DESTINO_AUTORIZADO_NOMBRE, ";
    sql += "ORDENES.INFO_DESTINO_AUTORIZADO_NIF, ORDENES.INFO_DESTINO_AUTORIZADO_DIRECCION, ";
    sql += "ORDENES.INFO_DESTINO_AUTORIZADO_CP, ORDENES.INFO_DESTINO_AUTORIZADO_MUNICIPIO, ";
    sql += "ORDENES.INFO_DESTINO_AUTORIZADO_PROVINCIA, ORDENES.INFO_DESTINO_AUTORIZADO_COMUNIDAD_AUTONOMA, ";
    sql += "ORDENES.INFO_DESTINO_AUTORIZADO_NIMA, ORDENES.INFO_DESTINO_AUTORIZADO_N_INSC_REGISTRO, ";
    sql += "ORDENES.INFO_DESTINO_AUTORIZADO_TELEFONO, ORDENES.INFO_DESTINO_AUTORIZADO_EMAIL, ";
    sql += "CLIENTES.NOMBRE, PRODUCTOS.CODIGO_LER, ORDENES.NUMERODI from ORDENES ";
    sql += "INNER JOIN CLIENTES ON ORDENES.CODIGO_CLIENTE = CLIENTES.CODIGO_CLIENTE ";
    sql += "INNER JOIN PRODUCTOS ON PRODUCTOS.CODIGO_PRODUCTO = ORDENES.CODIGO_PRODUCTO ";
    sql += "WHERE ORDENES.CODIGO_DESTINO = " + std::to_string(station_code);
    return;
}

void delOrder(std::string& sltQuery, std::string& myQuery,long destiny,long costumer,long product)
{
  sltQuery = "DELETE FROM ordenes WHERE CODIGO_CLIENTE =" + std::to_string(costumer);
  sltQuery += " AND CODIGO_DESTINO = " + std::to_string(destiny);
  sltQuery += " AND CODIGO_PRODUCTO = " + std::to_string(product);
  sltQuery += " AND (REPETIR is null or REPETIR = 0) order by FECHA_PROGRAMADA asc LIMIT 1";
  myQuery = sltQuery;
}

/*! select all order data by it's order code*/
void selOrderById(std::string& sql, long order_code)
{
    sql = "select CODIGO_ORDEN, ECOEMBES, CODIGO_CLIENTE, CODIGO_PRODUCTO, FECHA_FIRMA, ";
    sql += "FECHA_PROGRAMADA, PRECIO_TN, PESO_A_RETIRAR , CODIGO_DESTINO , OPERACION_TRATAMIENTO , ";
    sql += "REPETIR, TIPO_OPERADOR, CODIGO_INFO_ORIGEN_CENTRO, CODIGO_INFO_ORIGEN_AUTORIZADO, ";
    sql += "CODIGO_INFO_DESTINO_CENTRO, CODIGO_INFO_DESTINO_AUTORIZADO, INFO_DESTINO_CENTRO_NOMBRE, ";
    sql += "INFO_DESTINO_CENTRO_NIF, INFO_DESTINO_CENTRO_DIRECCION, INFO_DESTINO_CENTRO_CP, ";
    sql += "INFO_DESTINO_CENTRO_MUNICIPIO, INFO_DESTINO_CENTRO_PROVINCIA, ";
    sql += "INFO_DESTINO_CENTRO_COMUNIDAD_AUTONOMA, INFO_DESTINO_CENTRO_NIMA, ";
    sql += "INFO_DESTINO_CENTRO_N_INSC_REGISTRO, INFO_DESTINO_CENTRO_TELEFONO, ";
    sql += "INFO_DESTINO_CENTRO_EMAIL, INFO_DESTINO_AUTORIZADO_NOMBRE, INFO_DESTINO_AUTORIZADO_NIF, ";
    sql += "INFO_DESTINO_AUTORIZADO_DIRECCION, INFO_DESTINO_AUTORIZADO_CP, ";
    sql += "INFO_DESTINO_AUTORIZADO_MUNICIPIO, INFO_DESTINO_AUTORIZADO_PROVINCIA, ";
    sql += "INFO_DESTINO_AUTORIZADO_COMUNIDAD_AUTONOMA, INFO_DESTINO_AUTORIZADO_NIMA, ";
    sql += "INFO_DESTINO_AUTORIZADO_N_INSC_REGISTRO, INFO_DESTINO_AUTORIZADO_TELEFONO, ";
    sql += "INFO_DESTINO_AUTORIZADO_EMAIL, NUMERODI from ordenes where ";
    sql += "CODIGO_ORDEN = " + std::to_string(order_code);

    return;
}

void rmtSelAllOrders(std::string& sql, long codigo_estacion)
{
    sql = "select CODIGO_ORDEN, ECOEMBES, CODIGO_CLIENTE, CODIGO_PRODUCTO, FECHA_FIRMA, ";
    sql += "FECHA_PROGRAMADA, PRECIO_TN, PESO_RETIRAR, CODIGO_DESTINO, OPERACION_TRATAMIENTO, ";
    sql += "REPETIR, TIPO_OPERADOR, CODIGO_INFO_ORIGEN_CENTRO, CODIGO_INFO_ORIGEN_AUTORIZADO, ";
    sql += "CODIGO_INFO_DESTINO_CENTRO, CODIGO_INFO_DESTINO_AUTORIZADO, INFO_DESTINO_CENTRO_NOMBRE, ";
    sql += "INFO_DESTINO_CENTRO_NIF, INFO_DESTINO_CENTRO_DIRECCION, INFO_DESTINO_CENTRO_CP, ";
    sql += "INFO_DESTINO_CENTRO_MUNICIPIO, INFO_DESTINO_CENTRO_PROVINCIA, ";
    sql += "INFO_DESTINO_CENTRO_COMUNIDAD_AUTONOMA, INFO_DESTINO_CENTRO_NIMA, ";
    sql += "INFO_DESTINO_CENTRO_N_INSC_REGISTRO, INFO_DESTINO_CENTRO_TELEFONO, ";
    sql += "INFO_DESTINO_CENTRO_EMAIL, INFO_DESTINO_AUTORIZADO_NOMBRE, INFO_DESTINO_AUTORIZADO_NIF, ";
    sql += "INFO_DESTINO_AUTORIZADO_DIRECCION, INFO_DESTINO_AUTORIZADO_CP, ";
    sql += "INFO_DESTINO_AUTORIZADO_MUNICIPIO, INFO_DESTINO_AUTORIZADO_PROVINCIA, ";
    sql += "INFO_DESTINO_AUTORIZADO_COMUNIDAD_AUTONOMA, INFO_DESTINO_AUTORIZADO_NIMA, ";
    sql += "INFO_DESTINO_AUTORIZADO_N_INSC_REGISTRO, INFO_DESTINO_AUTORIZADO_TELEFONO, ";
    sql += "INFO_DESTINO_AUTORIZADO_EMAIL, NUMERODI from ordenes ";
    sql += "where CODIGO_DESTINO = " + std::to_string(codigo_estacion);
    return;
}

void loadOrders(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into ordenes ( CODIGO_ORDEN, ECOEMBES, CODIGO_CLIENTE, CODIGO_PRODUCTO, ";
    sql += "FECHA_FIRMA, FECHA_PROGRAMADA, PRECIO_TN, PESO_A_RETIRAR, CODIGO_DESTINO, ";
    sql += "OPERACION_TRATAMIENTO, REPETIR, TIPO_OPERADOR, CODIGO_INFO_ORIGEN_CENTRO, ";
    sql += "CODIGO_INFO_ORIGEN_AUTORIZADO, CODIGO_INFO_DESTINO_CENTRO, ";
    sql += "CODIGO_INFO_DESTINO_AUTORIZADO, INFO_DESTINO_CENTRO_NOMBRE, INFO_DESTINO_CENTRO_NIF, ";
    sql += "INFO_DESTINO_CENTRO_DIRECCION, INFO_DESTINO_CENTRO_CP, INFO_DESTINO_CENTRO_MUNICIPIO, ";
    sql += "INFO_DESTINO_CENTRO_PROVINCIA, INFO_DESTINO_CENTRO_COMUNIDAD_AUTONOMA, ";
    sql += "INFO_DESTINO_CENTRO_NIMA, INFO_DESTINO_CENTRO_N_INSC_REGISTRO, ";
    sql += "INFO_DESTINO_CENTRO_TELEFONO, INFO_DESTINO_CENTRO_EMAIL, INFO_DESTINO_AUTORIZADO_NOMBRE, ";
    sql += "INFO_DESTINO_AUTORIZADO_NIF, INFO_DESTINO_AUTORIZADO_DIRECCION, ";
    sql += "INFO_DESTINO_AUTORIZADO_CP, INFO_DESTINO_AUTORIZADO_MUNICIPIO, ";
    sql += "INFO_DESTINO_AUTORIZADO_PROVINCIA, INFO_DESTINO_AUTORIZADO_COMUNIDAD_AUTONOMA, ";
    sql += "INFO_DESTINO_AUTORIZADO_NIMA, INFO_DESTINO_AUTORIZADO_N_INSC_REGISTRO, ";
    sql += "INFO_DESTINO_AUTORIZADO_TELEFONO, INFO_DESTINO_AUTORIZADO_EMAIL, NUMERODI) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        //TRANSFORM MYSQL DATES TO SQLITE DATES
        myRow->at(4) = mysql2sqliteDate(myRow->at(4));
        myRow->at(5) = mysql2sqliteDate(myRow->at(5));
        //////////////////////////////////////
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
	        sql += ",";
        row++;
    }
    return;
}


////****table TRANSFERS****////

void selAllTransfers(char *& sql, long station_code)
{
 sql = new char[sizeof("select di, fecha_hora, codigo_origen, codigo_producto, codigo_transportista , matricula, remolque, incidencias, comentario_operador, operacion_Tratamiento FROM transferencias WHERE (codigo_destino = XX)")+32];
 
 sprintf(sql,"select di, fecha_hora, codigo_origen, codigo_producto, codigo_transportista , matricula, remolque, incidencias, comentario_operador, operacion_tratamiento FROM transferencias WHERE (codigo_destino = %lu)",station_code);

  return;
}

void selAllUnsyncroTransfers(std::string& sql)
{
    sql = "select di, fecha_hora, codigo_origen, codigo_destino, codigo_producto, codigo_transportista , matricula, remolque, incidencias, comentario_operador, operacion_tratamiento FROM transferencias WHERE (SINCRONIZADO = 0)";
    return;
}

void delTransfer(char *& sltQuery, char *& myQuery,long origin,long destiny,long product, const char* plate)
{
  sltQuery = new char[sizeof("DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = XXXXX AND CODIGO_DESTINO = XXXXX AND CODIGO_PRODUCTO = XXXXXX AND MATRICULA = \"XXXXXXXX\" order by FECHA_HORA asc LIMIT 1") + 32];

  myQuery = new char[sizeof("DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = XXXXX AND CODIGO_DESTINO = XXXXX AND CODIGO_PRODUCTO = XXXXXX AND MATRICULA = \"XXXXXXXX\" AND (BORRADO is NULL OR BORRADO = 0) order by FECHA_HORA asc LIMIT 1") + 32];
  
  sprintf(sltQuery,"DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = %lu AND CODIGO_DESTINO = %lu AND CODIGO_PRODUCTO = %lu AND MATRICULA = \"%s\" order by FECHA_HORA asc LIMIT 1",origin,destiny,product,plate);

  sprintf(myQuery,"DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = %lu AND CODIGO_DESTINO = %lu AND CODIGO_PRODUCTO = %lu AND MATRICULA = \"%s\" AND (BORRADO is NULL OR BORRADO = 0) order by FECHA_HORA asc LIMIT 1",origin,destiny,product,plate);
}

void delTransfer(char*&sql,const char* fecha_hora, long codigo_origen, long codigo_destino)
{
  sql = new char[sizeof("delete from transferencias where fecha_hora = \"XXXX-XX-XX XX:XX:XX\" and codigo_origen=XXXXXX and codigo_destino=XXXXXX")+64];
 
  sprintf(sql,"delete from transferencias where fecha_hora = \"%s\" and codigo_origen=%lu and codigo_destino=%lu",fecha_hora,codigo_origen,codigo_destino);

  return;
}

void rmtSelAllTransfers(std::string&sql, long codigo_estacion)
{
    sql = "select DI, FECHA_HORA, CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, MATRICULA, REMOLQUE, INCIDENCIAS, COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO from transferencias where CODIGO_DESTINO = ";
    sql += std::to_string(codigo_estacion) + " and BORRADO = 0";
    return;
}

void rmtUpdtTransfers(std::string& sql, std::vector< std::vector <std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into transferencias (DI, FECHA_HORA, CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, MATRICULA, REMOLQUE, INCIDENCIAS, COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    sql += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA = VALUES(FECHA_HORA) , CODIGO_ORIGEN = VALUES(CODIGO_ORIGEN), CODIGO_DESTINO = VALUES(CODIGO_DESTINO),CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), CODIGO_TRANSPORTISTA = VALUES(CODIGO_TRANSPORTISTA), MATRICULA = VALUES(MATRICULA), REMOLQUE = VALUES(REMOLQUE), INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), OPERACION_TRATAMIENTO = VALUES(OPERACION_TRATAMIENTO)";
    return;
}

void loadTransfers(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into transferencias (DI, FECHA_HORA, CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, MATRICULA, REMOLQUE, INCIDENCIAS, COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO,SINCRONIZADO) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {  
        //TRANSFORM MYSQL DATES TO SQLITE DATES
        myRow->at(1) = mysql2sqliteDate(myRow->at(1));
        //////////////////////////////////////
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\",1)";
        if(row < dataReturn.size()-1)
          	sql += ",";
        row++;
    }
    return;
}

////////////////
////****table products****////
void selProdPermits(std::string & sql, const char* type, long product_code)
{
    sql = "select PERMISO_";
    sql += type;
    sql += ", CONTRATO_";
    sql += type;
    sql += ", NPT_";
    sql += type;
    sql += ", CB_";
    sql += type;
    sql += ", CP_";
    sql += type;
    sql += ", DCP_";
    sql += type;
    sql += " from productos WHERE CODIGO_PRODUCTO = " + std::to_string(product_code);
    return;
}
void selProdDataByCode(char *& sql, long code)
{ 
  sql = new char[sizeof("SELECT NOMBRE, NOMBRE2, NOMBRE3,CODIGO_LER,DESCRIPCION_PELIGRO,PRECIO_DEFECTO  from PRODUCTOS WHERE (CODIGO_PRODUCTO=XXXXX AND (BORRADO is null or BORRADO = 0))")+12];
  
  sprintf(sql,"SELECT NOMBRE, NOMBRE2, NOMBRE3,CODIGO_LER,DESCRIPCION_PELIGRO,PRECIO_DEFECTO  from PRODUCTOS WHERE (CODIGO_PRODUCTO=%lu AND (BORRADO is null or BORRADO = 0))",code);
  
  return; 
}

//búsqueda conjunta de tablas productos y clientes-productos para sacar los que están eprmitidos al cliente en cuestión
void selProdsAllowedToClient(char *& sql, const char* codigoCliente, const char* tipoEstacion, bool temporal)
{
  
  sql = new char[sizeof("CREATE TEMPORARY TABLE resultado as select CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PRODUCTOS.CODIGO_PRODUCTO from PRODUCTOS INNER JOIN CLIENTES_PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_CLIENTE= AND CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = PRODUCTOS.CODIGO_PRODUCTO AND PRODUCTOS.PERMISO_XX!=0 AND ((PRODUCTOS.CONTRATO_XX!=0 AND CLIENTES_PRODUCTOS.CONTRATO_XX >=CURRENT_DATE) OR PRODUCTOS.CONTRATO_XX=0) AND ((PRODUCTOS.NPT_XX!=0 AND CLIENTES_PRODUCTOS.NPT_XX!=0) OR PRODUCTOS.NPT_XX=0) AND ((PRODUCTOS.CB_XX!=0 AND CLIENTES_PRODUCTOS.CB_XX!=0) OR PRODUCTOS.CB_XX=0) AND ((PRODUCTOS.CP_XX!=0 AND CLIENTES_PRODUCTOS.CP_XX!=0) OR PRODUCTOS.CP_XX=0) AND ((PRODUCTOS.DCP_XX!=0 AND CLIENTES_PRODUCTOS.DCP_XX!=0) OR PRODUCTOS.DCP_XX=0) AND (BORRADO is null or BORRADO = 0) ORDER BY nombre,nombre2,nombre3")+ strlen(codigoCliente) + 64];

  if(temporal)
    sprintf(sql,"CREATE TEMPORARY TABLE resultado as select CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PRODUCTOS.CODIGO_PRODUCTO from PRODUCTOS INNER JOIN CLIENTES_PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_CLIENTE=%s AND CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = PRODUCTOS.CODIGO_PRODUCTO AND PRODUCTOS.PERMISO_%s!=0 AND ((PRODUCTOS.CONTRATO_%s!=0 AND CLIENTES_PRODUCTOS.CONTRATO_%s >=CURRENT_DATE) OR PRODUCTOS.CONTRATO_%s=0) AND ((PRODUCTOS.NPT_%s!=0 AND CLIENTES_PRODUCTOS.NPT_%s!=0) OR PRODUCTOS.NPT_%s=0) AND ((PRODUCTOS.CB_%s!=0 AND CLIENTES_PRODUCTOS.CB_%s!=0) OR PRODUCTOS.CB_%s=0) AND ((PRODUCTOS.CP_%s!=0 AND CLIENTES_PRODUCTOS.CP_%s!=0) OR PRODUCTOS.CP_%s=0) AND ((PRODUCTOS.DCP_%s!=0 AND CLIENTES_PRODUCTOS.DCP_%s!=0) OR PRODUCTOS.DCP_%s=0) AND (BORRADO is null or BORRADO = 0) ORDER BY nombre,nombre2,nombre3",codigoCliente,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion);
  else
     sprintf(sql,"select CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PRODUCTOS.CODIGO_PRODUCTO from PRODUCTOS INNER JOIN CLIENTES_PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_CLIENTE=%s AND CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = PRODUCTOS.CODIGO_PRODUCTO AND PRODUCTOS.PERMISO_%s!=0 AND ((PRODUCTOS.CONTRATO_%s!=0 AND CLIENTES_PRODUCTOS.CONTRATO_%s >=CURRENT_DATE) OR PRODUCTOS.CONTRATO_%s=0) AND ((PRODUCTOS.NPT_%s!=0 AND CLIENTES_PRODUCTOS.NPT_%s!=0) OR PRODUCTOS.NPT_%s=0) AND ((PRODUCTOS.CB_%s!=0 AND CLIENTES_PRODUCTOS.CB_%s!=0) OR PRODUCTOS.CB_%s=0) AND ((PRODUCTOS.CP_%s!=0 AND CLIENTES_PRODUCTOS.CP_%s!=0) OR PRODUCTOS.CP_%s=0) AND ((PRODUCTOS.DCP_%s!=0 AND CLIENTES_PRODUCTOS.DCP_%s!=0) OR PRODUCTOS.DCP_%s=0) AND (BORRADO is null or BORRADO = 0) ORDER BY nombre,nombre2,nombre3",codigoCliente,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion);

  return;
}

void selAllProds(char*&sql)
{
  sql = new char[sizeof("select codigo_producto, codigo_ler, nombre, nombre2, nombre3, permiso_pt, contrato_pt, npt_pt, cb_pt,cp_pt,dcp_pt, permiso_et, contrato_et, npt_et, cb_et,cp_et,dcp_et, permiso_d5, contrato_d5, npt_d5, cb_d5,cp_d5,dcp_d5, permiso_sal, contrato_sal, npt_sal, cb_sal,cp_sal,dcp_sal, descripcion_peligro FROM productos WHERE (BORRADO is null or BORRADO = 0) order by nombre,nombre2,nombre3")+32];
 
  sprintf(sql,"select codigo_producto, codigo_ler, nombre, nombre2, nombre3, permiso_pt, contrato_pt, npt_pt, cb_pt,cp_pt,dcp_pt, permiso_et, contrato_et, npt_et, cb_et,cp_et,dcp_et, permiso_d5, contrato_d5, npt_d5, cb_d5,cp_d5,dcp_d5, permiso_sal, contrato_sal, npt_sal, cb_sal,cp_sal,dcp_sal, descripcion_peligro FROM productos WHERE (BORRADO is null or BORRADO = 0) order by nombre,nombre2,nombre3");

  return;
}

void rmtSelAllProducts(std::string& sql)
{
    sql = "select CODIGO_PROD, CODIGO_LER , NOMBRE , NOMBRE2 , NOMBRE3 , PERMISO_PT ,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT ,PERMISO_ET ,CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,PERMISO_D5 ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,PERMISO_SAL ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL ,DESCRIPCION_PELIGRO,PRECIO_DEFECTO from productos WHERE BORRADO = 0;";
    return;
}

void loadProducts(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into productos (codigo_producto, codigo_ler, nombre, nombre2,nombre3,PERMISO_PT ,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT ,PERMISO_ET ,CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,PERMISO_D5 ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,PERMISO_SAL ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL ,DESCRIPCION_PELIGRO,PRECIO_DEFECTO) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}


/////////////////////////////////////////////////////
////****table costumers****////
void selCosDataByCode(std::string& sql, long code)
{
    sql = "SELECT CODIGO_CLIENTE, NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, CODIGO_ENTIDAD_FACTURACION, CBC, TIPO, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from CLIENTES WHERE (CODIGO_CLIENTE = ";
    sql += std::to_string(code) + " AND (BORRADO is null or BORRADO = 0))";
    return;
}
void selAllDatFrmCostumers(char *& sql)
{
  sql = new char[sizeof("SELECT CODIGO_CLIENTE,NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, CODIGO_ENTIDAD_FACTURACION, CBC, TIPO, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from CLIENTES WHERE (BORRADO is null or BORRADO = 0) order by NOMBRE")+12];

  sprintf(sql,"SELECT CODIGO_CLIENTE,NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, CODIGO_ENTIDAD_FACTURACION, CBC, TIPO, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from CLIENTES WHERE (BORRADO is null or BORRADO = 0) order by NOMBRE");

  return;
}

void sel_default_driver(char *& sql, long code)
{
  sql = new char[sizeof("select TRANSPORTISTA_DEFECTO from CLIENTES where (CODIGO_CLIENTE=XXXXX AND (BORRADO is null or BORRADO = 0))")+12];

  sprintf(sql,"select TRANSPORTISTA_DEFECTO from CLIENTES where (CODIGO_CLIENTE=%lu AND (BORRADO is null or BORRADO = 0))",code);

  return;
}

void rmtSelAllCostumers(std::string& sql)
{
    sql = "select CODIGO, NOMBRE , NIF , DIRECCION , PROVINCIA ,POBLACION ,CP , ENTIDAD_FACTURACION ,CBC ,TIPO , COMUNIDAD_AUTONOMA , NIMA , NUM_INSCRIPCION , TELEFONO , MAIL, TRANSPORTISTA_DEFECTO from clientes WHERE  (BORRADO is null or BORRADO = 0)";
    return;
}

void loadCostumers(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into clientes (codigo_cliente, nombre,nif, direccion, provincia,poblacion,cp,codigo_entidad_facturacion,cbc,tipo,comunidad_autonoma,nima,num_inscripcion,telefono,mail,transportista_defecto) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}
////////
////****table costumers-products****////
void selProdCosPermits(std::string& sql, const char* type, long product_code, long costumer_code)
{
    sql = "select CONTRATO_";
    sql += type;
    sql +=", NPT_";
    sql += type;
    sql += ", CB_";
    sql += type;
    sql += ", CP_";
    sql += type;
    sql += ", DCP_";
    sql += type;
    sql +=" from clientes_productos WHERE CODIGO_PRODUCTO = " + std::to_string(product_code);
    sql +=" AND CODIGO_CLIENTE = " + std::to_string(costumer_code);
    return;
}

void sel_price_cos_prod(char *&sql, long product_code, long costumer_code)
{
  sql = new char[sizeof("select PRECIO_TRATAMIENTO from clientes_products WHERE CODIGO_PRODUCTO = XXXXX AND CODIGO_CLIENTE = XXXXX")+32];
  
  sprintf(sql,"select PRECIO_TRATAMIENTO from clientes_products WHERE CODIGO_PRODUCTO = %lu AND CODIGO_CLIENTE = %lu",product_code, costumer_code);
  
  return;
}
void sel_DIbasis_cos_prod(char *& sql,const char* tipoEstacion, long codigoCliente, long codigoProducto)
{
  sql = new char[sizeof("select NPT_XXX,PRECIO_TRATAMIENTO from clientes_productos WHERE (CODIGO_PRODUCTO = xxxxx AND CODIGO_CLIENTE = xxxxx)") + 32];
  
  sprintf(sql,"select NPT_%s,PRECIO_TRATAMIENTO from clientes_productos WHERE (CODIGO_PRODUCTO = %lu AND CODIGO_CLIENTE = %lu)",tipoEstacion,codigoProducto,codigoCliente);

  return;
}

void rmtSelAllCosProds(std::string& sql)
{
    sql = "select CODIGO_PROD,CODIGO_CLIENTE,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT , CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL, PRECIO_TRATAMIENTO from clientes_productos";
    return;
}

void loadCosProds(std::string& sql,std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert or ignore into clientes_productos (CODIGO_PRODUCTO,CODIGO_CLIENTE,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT , CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL, PRECIO_TRATAMIENTO) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
          	sql += ",";
        row++;
    }
    return;
}

//////// 
////****table movements****////
void selLastDiFromMovsByClientProduct(std::string& sql, long costumer_code, long product_code)
{
  sql = "select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE = " + std::to_string(costumer_code);
  sql += " AND CODIGO_PRODUCTO = " + std::to_string(product_code);
  sql += " ORDER BY DATETIME(FECHA_HORA_FINAL) DESC";

  return;
}

void selAllUnsyncroMovs(std::string& sql)
{
    sql = "select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, CODIGO_CLIENTE, ";
    sql += "CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, CODIGO_BASCULISTA, PESO_NETO, PESO_TARA, ";
    sql += "PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, CENTRO_DESTINO, ";
    sql += "INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, ";
    sql += "CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, ";
    sql += "CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, ";
    sql += "CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, ";
    sql += "CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, ";
    sql += "DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, ";
    sql += "DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, ";
    sql += "DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO, ";
    sql += "TIPO_CLIENTE, TRANSPORTISTA_NOMBRE, TRANSPORTISTA_NIF, TRANSPORTISTA_DIRECCION, ";
    sql += "TRANSPORTISTA_PROVINCIA, TRANSPORTISTA_POBLACION, TRANSPORTISTA_CP, ";
    sql += "TRANSPORTISTA_COMUNIDAD_AUTONOMA, TRANSPORTISTA_NIMA, TRANSPORTISTA_NUM_INSCRIPCION, ";
    sql += "TRANSPORTISTA_TELEFONO, TRANSPORTISTA_MAIL from MOVIMIENTOS where SINCRONIZADO = 0";
    return;
}

void updtAllUnsyncroMovs(std::string& sql)
{
    sql = "UPDATE MOVIMIENTOS SET SINCRONIZADO = 1  WHERE SINCRONIZADO = 0";
    return;
}

void updtSyncroMovs(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert or ignore into MOVIMIENTOS (CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, ";
    sql += "TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, CODIGO_BASCULISTA, ";
    sql += "PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, ";
    sql += "CENTRO_DESTINO, INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, ";
    sql += "CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, ";
    sql += "CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, ";
    sql += "CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, ";
    sql += "CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, ";
    sql += "CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, ";
    sql += "DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, ";
    sql += "DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, ";
    sql += "DESTINO_CORREO_ELECTRONICO, TIPO_CLIENTE, TRANSPORTISTA_NOMBRE, TRANSPORTISTA_NIF, ";
    sql += "TRANSPORTISTA_DIRECCION, TRANSPORTISTA_PROVINCIA, TRANSPORTISTA_POBLACION, TRANSPORTISTA_CP, ";
    sql += "TRANSPORTISTA_COMUNIDAD_AUTONOMA, TRANSPORTISTA_NIMA, TRANSPORTISTA_NUM_INSCRIPCION, ";
    sql += "TRANSPORTISTA_TELEFONO, TRANSPORTISTA_MAIL, SINCRONIZADO) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        myRow->at(2) = mysql2sqliteDate(myRow->at(2));
        myRow->at(3) = mysql2sqliteDate(myRow->at(3));      
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\",1)"; //<- sincronizado to 1 here, last value
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}

void rmtUpdtMovs(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into movimientos (CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, ";
    sql += "TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, CODIGO_BASCULISTA, ";
    sql += "PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, ";
    sql += "CENTRO_DESTINO, INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, ";
    sql += "CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, ";
    sql += "CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, ";
    sql += "CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, ";
    sql += "CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, ";
    sql += "CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, ";
    sql += "DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, ";
    sql += "DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, ";
    sql += "DESTINO_CORREO_ELECTRONICO, TIPO_CLIENTE, TRANSPORTISTA_NOMBRE, TRANSPORTISTA_NIF, ";
    sql += "TRANSPORTISTA_DIRECCION, TRANSPORTISTA_PROVINCIA, TRANSPORTISTA_POBLACION, TRANSPORTISTA_CP, ";
    sql += "TRANSPORTISTA_COMUNIDAD_AUTONOMA, TRANSPORTISTA_NIMA, TRANSPORTISTA_NUM_INSCRIPCION, ";
    sql += "TRANSPORTISTA_TELEFONO, TRANSPORTISTA_MAIL) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end(); ++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    sql += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA_INICIO = VALUES(FECHA_HORA_INICIO) ";
    sql += ",FECHA_HORA_FINAL = VALUES(FECHA_HORA_FINAL), TIPO_MOVIMIENTO = VALUES(TIPO_MOVIMIENTO), ";
    sql += "CODIGO_CLIENTE = VALUES(CODIGO_CLIENTE), CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), ";
    sql += "CODIGO_TRANSPORTISTA = VALUES(CODIGO_TRANSPORTISTA), ";
    sql += "CODIGO_BASCULISTA = VALUES(CODIGO_BASCULISTA), PESO_NETO = VALUES(PESO_NETO), ";
    sql += "PESO_TARA = VALUES(PESO_TARA), PESO_BRUTO = VALUES(PESO_BRUTO), PRECIO = VALUES(PRECIO), ";
    sql += "VEHICULO = VALUES(VEHICULO), REMOLQUE = VALUES(REMOLQUE), ";
    sql += "CENTRO_ORIGEN = VALUES(CENTRO_ORIGEN), CENTRO_DESTINO = VALUES(CENTRO_DESTINO), ";
    sql += "INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), ";
    sql += "CLIENTE_PARTICULAR_NOMBRE = VALUES(CLIENTE_PARTICULAR_NOMBRE), ";
    sql += "CLIENTE_PARTICULAR_NIF = VALUES(CLIENTE_PARTICULAR_NIF), ";
    sql += "CLIENTE_PARTICULAR_DOMICILIO = VALUES(CLIENTE_PARTICULAR_DOMICILIO), ";
    sql += "CLIENTE_PARTICULAR_PROVINCIA = VALUES(CLIENTE_PARTICULAR_PROVINCIA), ";
    sql += "CLIENTE_PARTICULAR_POBLACION = VALUES(CLIENTE_PARTICULAR_POBLACION), ";
    sql += "CLIENTE_PARTICULAR_CODIGO_POSTAL = VALUES(CLIENTE_PARTICULAR_CODIGO_POSTAL), ";
    sql += "CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA = VALUES(CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA), ";
    sql += "CLIENTE_PARTICULAR_NIMA = VALUES(CLIENTE_PARTICULAR_NIMA), ";
    sql += "CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO = VALUES(CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO), ";
    sql += "CLIENTE_PARTICULAR_TELEFONO = VALUES(CLIENTE_PARTICULAR_TELEFONO), ";
    sql += "CLIENTE_PARTICULAR_CORREO_ELECTRONICO = VALUES(CLIENTE_PARTICULAR_CORREO_ELECTRONICO), ";
    sql += "DESTINO_NOMBRE = VALUES(DESTINO_NOMBRE), DESTINO_NIF = VALUES(DESTINO_NIF), ";
    sql += "DESTINO_DOMICILIO = VALUES(DESTINO_DOMICILIO), DESTINO_PROVINCIA = VALUES(DESTINO_PROVINCIA), ";
    sql += "DESTINO_POBLACION = VALUES(DESTINO_POBLACION), DESTINO_CODIGO_POSTAL = VALUES(DESTINO_CODIGO_POSTAL), ";
    sql += "DESTINO_COMUNIDAD_AUTONOMA = VALUES(DESTINO_COMUNIDAD_AUTONOMA), ";
    sql += "DESTINO_NIMA = VALUES(DESTINO_NIMA), DESTINO_NUM_INSCRIPCION_REGISTRO = VALUES(DESTINO_NUM_INSCRIPCION_REGISTRO), ";
    sql += "DESTINO_TELEFONO = VALUES(DESTINO_TELEFONO), DESTINO_CORREO_ELECTRONICO = VALUES(DESTINO_CORREO_ELECTRONICO), ";
    sql += "TIPO_CLIENTE = VALUES(TIPO_CLIENTE), TRANSPORTISTA_NOMBRE = VALUES(TRANSPORTISTA_NOMBRE), ";
    sql += "TRANSPORTISTA_NIF = VALUES(TRANSPORTISTA_NIF), TRANSPORTISTA_DIRECCION = VALUES(TRANSPORTISTA_DIRECCION), ";
    sql += "TRANSPORTISTA_PROVINCIA = VALUES(TRANSPORTISTA_PROVINCIA), ";
    sql += "TRANSPORTISTA_POBLACION = VALUES(TRANSPORTISTA_POBLACION), TRANSPORTISTA_CP = VALUES(TRANSPORTISTA_CP), ";
    sql += "TRANSPORTISTA_COMUNIDAD_AUTONOMA = VALUES(TRANSPORTISTA_COMUNIDAD_AUTONOMA), ";
    sql += "TRANSPORTISTA_NIMA = VALUES(TRANSPORTISTA_NIMA), ";
    sql += "TRANSPORTISTA_NUM_INSCRIPCION = VALUES(TRANSPORTISTA_NUM_INSCRIPCION), ";
    sql += "TRANSPORTISTA_TELEFONO = VALUES(TRANSPORTISTA_TELEFONO), TRANSPORTISTA_MAIL = VALUES(TRANSPORTISTA_MAIL)";
    return;
}

void rmtSelLastMov(std::string& sql, long station_code, int year)
{
    std::string from_mov_code, to_mov_code;
    from_mov_code = std::to_string(year) + std::to_string(station_code) + "0000000";
    to_mov_code = std::to_string(year) + std::to_string(station_code) + "9999999";
    // TODO: REVCODES
    //  from_mov_code = std::to_string(year)+ (station_code < 10 && station_code >= 1?"0":"") + std::to_string(station_code) + "0000000";
    //  to_mov_code = std::to_string(year)+ (station_code < 10 && station_code >= 1?"0":"") + std::to_string(station_code) + "9999999";
    sql = "select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, ";
    sql += "CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, CODIGO_BASCULISTA, PESO_NETO, ";
    sql += "PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, CENTRO_DESTINO, ";
    sql += "INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, ";
    sql += "CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, ";
    sql += "CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, ";
    sql += "CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, ";
    sql += "CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, ";
    sql += "DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, ";
    sql += "DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, ";
    sql += "DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO, ";
    sql += "TIPO_CLIENTE, TRANSPORTISTA_NOMBRE, TRANSPORTISTA_NIF, TRANSPORTISTA_DIRECCION, ";
    sql += "TRANSPORTISTA_PROVINCIA, TRANSPORTISTA_POBLACION, TRANSPORTISTA_CP, ";
    sql += "TRANSPORTISTA_COMUNIDAD_AUTONOMA, TRANSPORTISTA_NIMA, TRANSPORTISTA_NUM_INSCRIPCION, ";
    sql += "TRANSPORTISTA_TELEFONO, TRANSPORTISTA_MAIL ";
    sql += "from movimientos where (CODIGO_MOV >= ";
    sql += from_mov_code;
    sql += " and CODIGO_MOV < " + to_mov_code;
    sql += ") ORDER BY CODIGO_MOV DESC LIMIT 1;";
    return;
}

////////
////****TABLE TRANSITO****////
void  updtScaleOutTrans(char *& sql, const char* fecha_hora, long codigo_cliente, long codigo_producto, unsigned int peso_salida, const char* comentario, const char * incidencias)
{
  
  sql = new char[sizeof("UPDATE TRANSITO SET PESO_SALIDA = XXXXXXXXX , comentario_operador = XXXXXXXX, incidencias = XXXXXXXXX WHERE (FECHA_HORA = (XXXX-XX-XX XX:XX:XX) AND CODIGO_CLIENTE=XXXXXX AND CODIGO_PRODUCTO=XXXXXX)")+32 + strlen(comentario) + strlen(incidencias)];

  sprintf(sql,"update transito set PESO_SALIDA = %u, comentario_operador = \"%s\", incidencias = \"%s\" WHERE (FECHA_HORA = \"%s\" AND CODIGO_CLIENTE = \"%lu\" AND CODIGO_PRODUCTO = \"%lu\")",peso_salida,comentario, incidencias,fecha_hora,codigo_cliente,codigo_producto);

  return;
}

void sel_all_unsyncro_transito(char *& sql, int fromStation)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA) FROM TRANSITO WHERE CODIGO_ESTACION=XXXXX AND SINCRONIZADO=0")+12];
  sprintf(sql,"SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA FROM TRANSITO WHERE CODIGO_ESTACION=%d AND SINCRONIZADO=0",fromStation);
  return;
}

void selAllTransit(std::string& sql, long fromStation)
{
    sql = "SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA FROM TRANSITO WHERE CODIGO_ESTACION = ";
    sql += std::to_string(fromStation);
    return;
}

void selAllTransit(std::string& sql)
{
    sql = "SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA FROM TRANSITO";
    return;
}

void rmtDelTransit(std::string& sql, long fromStation)
{
    sql = "DELETE FROM transito WHERE CODIGO_ESTACION = ";
    sql += std::to_string(fromStation);
    return;
}

void rmtUpdtTransit(std::string& sql, std::vector<std::vector<std::string>> dataReturn, long codigo_estacion)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into transito (DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA, CODIGO_ESTACION) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\",";
        sql += std::to_string(codigo_estacion);
        sql +=")";      
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    sql += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA = VALUES(FECHA_HORA), TIPO_MOVIMIENTO = VALUES(TIPO_MOVIMIENTO), CODIGO_CLIENTE = VALUES(CODIGO_CLIENTE), CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), PESO_ENTRADA = VALUES(PESO_ENTRADA), PRECIO = VALUES(PRECIO), MATRICULA = VALUES(MATRICULA), REMOLQUE = VALUES(REMOLQUE), CODIGO_ORIGEN = VALUES(CODIGO_ORIGEN), INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), PESO_SALIDA = VALUES(PESO_SALIDA), CODIGO_ESTACION = VALUES(CODIGO_ESTACION)";
    return;
}


/////
///////////////////////////////////
/**** TABLE TRANSITO_SALIDAS *****/
void  updtScaleOutTransSal(std::string& sql, std::string fecha_hora, long codigo_cliente, long codigo_producto, long peso_salida, std::string comentario, std::string incidencias)
{
  sql = "update transito_salidas set PESO_RETIRADO = " + std::to_string(peso_salida);
  sql += ", comentario_operador = \" " + comentario;
  sql += "\", incidencias = \"" + incidencias;
  sql += "\" WHERE (FECHA_HORA = \"" + fecha_hora;
  sql += "\" AND CODIGO_CLIENTE = \"" + std::to_string(codigo_cliente);
  sql += "\" AND CODIGO_PRODUCTO = \"" + std::to_string(codigo_producto) +"\")";

  return;
}

void sel_all_unsyncro_transito_dep(char *& sql,long fromStation)
{
  sql = new char[sizeof("DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR) FROM TRANSITO_SALIDAS WHERE CODIGO_DESTINO = XXXXX AND SICNRONIZADO = 0")+12];

  sprintf(sql,"SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR FROM TRANSITO_SALIDAS WHERE CODIGO_ESTACION=%lu AND SINCRONIZADO = 0",fromStation);

}

void selAllTransitDep(std::string& sql)
{
    sql = "SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR, FOLDER FROM TRANSITO_SALIDAS";
    return;
}

void rmt_selAllFromTransitoSalidas(char *& sql,long fromStation)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR FROM transito_salidas where CODIGO_ESTACION = XXXXX")+32];

  sprintf(sql,"select DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR FROM transito_salidas where CODIGO_ESTACION = %lu",fromStation);

  return;
}

void rmtDelTransitDep(std::string& sql, long fromStation)
{
    sql = "DELETE FROM transito_salidas WHERE CODIGO_ESTACION = ";
    sql += std::to_string(fromStation);
    return;
}

void rmtUpdtTransitDep(std::string& sql, std::vector<std::vector<std::string>> dataReturn, long codigo_estacion)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR, CODIGO_ESTACION) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql += "\",";
        sql += std::to_string(codigo_estacion);
        sql +=")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    sql += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA = VALUES(FECHA_HORA), CODIGO_CLIENTE = VALUES(CODIGO_CLIENTE), CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), PESO_ENTRADA = VALUES(PESO_ENTRADA), PRECIO = VALUES(PRECIO), MATRICULA = VALUES(MATRICULA), REMOLQUE = VALUES(REMOLQUE), PESO_A_RETIRAR = VALUES(PESO_A_RETIRAR), PESO_RETIRADO = VALUES(PESO_RETIRADO), CODIGO_DESTINO = VALUES(CODIGO_DESTINO), INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), CODIGO_ESTACION = VALUES(CODIGO_ESTACION)";
    return;
}

void sqlLoadTransitoSalidas(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_ESTACION, CODIGO_ORDEN, INCIDENCIAS, COMENTARIO_OPERADOR) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      //TRANSFORM MYSQL DATES TO SQLITE DATES
      myRow->at(1) = mysql2sqliteDate(myRow->at(1));
      //////////////////////////////////////
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\",1)"; //<- 1 for syncronized
      if(row < dataReturn.size()-1)
	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}
/////////////////////////////////

//////////////
//TABLE TRUCKS
void sel_all_cars(char *& sql)
{
  sql = new char[sizeof("select matricula from vehiculos where borrado is null or borrado = 0")+32];
  sprintf(sql,"select matricula from vehiculos where borrado is null or borrado = 0");
}

void selCostumersFromCar(std::string&sql, std::string matricula)
{
    sql = "select CODIGO_CLIENTE1, CODIGO_CLIENTE2, CODIGO_CLIENTE3, CODIGO_CLIENTE4, CODIGO_CLIENTE5, CODIGO_CLIENTE6, CODIGO_CLIENTE7, CODIGO_CLIENTE8, CODIGO_CLIENTE9, CODIGO_CLIENTE10";
    sql += ", CODIGO_CLIENTE11, CODIGO_CLIENTE12, CODIGO_CLIENTE13, CODIGO_CLIENTE14, CODIGO_CLIENTE15, CODIGO_CLIENTE16, CODIGO_CLIENTE17, CODIGO_CLIENTE18, CODIGO_CLIENTE19, CODIGO_CLIENTE20";
    sql += ", CODIGO_CLIENTE21, CODIGO_CLIENTE22, CODIGO_CLIENTE23, CODIGO_CLIENTE24, CODIGO_CLIENTE25, CODIGO_CLIENTE26, CODIGO_CLIENTE27, CODIGO_CLIENTE28, CODIGO_CLIENTE29, CODIGO_CLIENTE30 ";
    sql += "from VEHICULOS WHERE MATRICULA = \"" + matricula + "\"";
    return;
}

void rmtSelAllCars(std::string& sql)
{
    sql = "select CODIGO_VEHICULO,MATRICULA,VEHICULO_REMOLQUE ,TARA , PMA ,CODIGO_CLIENTE1 , CODIGO_CLIENTE2 ,CODIGO_CLIENTE3 ,CODIGO_CLIENTE4 ,CODIGO_CLIENTE5,CODIGO_CLIENTE6 , CODIGO_CLIENTE7 ,CODIGO_CLIENTE8 ,CODIGO_CLIENTE9 ,CODIGO_CLIENTE10"
            ",CODIGO_CLIENTE11 , CODIGO_CLIENTE12 ,CODIGO_CLIENTE13 ,CODIGO_CLIENTE14 ,CODIGO_CLIENTE15,CODIGO_CLIENTE16 , CODIGO_CLIENTE17 ,CODIGO_CLIENTE18 ,CODIGO_CLIENTE19 ,CODIGO_CLIENTE20"
            ",CODIGO_CLIENTE21 , CODIGO_CLIENTE22 ,CODIGO_CLIENTE23 ,CODIGO_CLIENTE24 ,CODIGO_CLIENTE25,CODIGO_CLIENTE26 , CODIGO_CLIENTE27 ,CODIGO_CLIENTE28 ,CODIGO_CLIENTE29 ,CODIGO_CLIENTE30 from vehiculos WHERE (BORRADO is null or BORRADO = 0);";

  return;
}

void loadCars(std::string& sql,std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;

    sql = "insert into vehiculos (CODIGO_VEHICULO, MATRICULA, VEHICULO_REMOLQUE, TARA, PMA, CODIGO_CLIENTE1, CODIGO_CLIENTE2, CODIGO_CLIENTE3, CODIGO_CLIENTE4, CODIGO_CLIENTE5, CODIGO_CLIENTE6, CODIGO_CLIENTE7, CODIGO_CLIENTE8, CODIGO_CLIENTE9, CODIGO_CLIENTE10"
            ", CODIGO_CLIENTE11, CODIGO_CLIENTE12, CODIGO_CLIENTE13, CODIGO_CLIENTE14, CODIGO_CLIENTE15, CODIGO_CLIENTE16, CODIGO_CLIENTE17, CODIGO_CLIENTE18, CODIGO_CLIENTE19, CODIGO_CLIENTE20"
            ", CODIGO_CLIENTE21, CODIGO_CLIENTE22, CODIGO_CLIENTE23, CODIGO_CLIENTE24, CODIGO_CLIENTE25, CODIGO_CLIENTE26, CODIGO_CLIENTE27, CODIGO_CLIENTE28, CODIGO_CLIENTE29, CODIGO_CLIENTE30) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}
//

///////////////
//TABLE STAFF
void sel_staff_data_by_code(char*& sql,long code)
{
  sql = new char[sizeof("select nombre,nif from basculistas where codigo = XXXXXXX and (borrado is null or borrado = 0) ")+32];
  sprintf(sql,"select nombre,nif from basculistas where codigo = \"%lu\" and (borrado is null or borrado = 0)",code);
  return;
}

void selAllStaffData(char*& sql,long code)
{
  sql = new char[sizeof("select codigo,nombre,nif from basculistas where codigo = XXXXXXX and (borrado is null or borrado = 0) ")+32];
  sprintf(sql,"select codigo,nombre,nif from basculistas where codigo = \"%lu\" and (borrado is null or borrado = 0)",code);
  return;
}

void rmtSelAllStaff(std::string& sql)
{
    sql = "select CODIGO, NOMBRE, NIF FROM basculistas WHERE BORRADO = 0;";
    return;
}

void loadStaff(std::string& sql, std::vector<std::vector<std::string>> load_data)
{
    std::vector<std::vector<std::string>>::iterator my_row;
    long unsigned int row = 0;
    sql = "insert into BASCULISTAS (CODIGO, NOMBRE, NIF) values ";
    for(my_row = load_data.begin(); my_row != load_data.end(); ++my_row)
    {
        sql +="(\"";
        sql += vectorToString(*my_row,"\",\"");
        sql +="\")";
        if(row < load_data.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}

//

////////////////
//TABLE BILLING
void sel_fp_by_cos_code(char *& sql, long code)
{
  sql = new char[sizeof("select FP from entidades_facturacion where codigo = (select CODIGO_ENTIDAD_FACTURACION from clientes where codigo_cliente = XXXXX)")+32];
  
  sprintf(sql,"select FP from entidades_facturacion where codigo = (select CODIGO_ENTIDAD_FACTURACION from clientes where codigo_cliente = %lu)",code);
  
}

void rmtSelAllBilling(std::string& sql)
{
    sql = "select CODIGO,NOMBRE,NIF,DIRECCION,CP,POBLACION,PROVINCIA,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,FP,IBAN,ENVIO_FACT,TELEFONO,MAIL from entidades_facturacion where (BORRADO is null or BORRADO = 0)";
    return;
}

void loadBilling(std::string& sql, std::vector< std::vector< std::string>> load_data)
{
    std::vector<std::vector<std::string>>::iterator my_row;
    long unsigned int row = 0;
    sql = "insert into entidades_facturacion (CODIGO, NOMBRE, NIF, DIRECCION, CP, POBLACION, PROVINCIA, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, FP, IBAN, ENVIO_FACT, TELEFONO, MAIL) values ";
    for(my_row = load_data.begin(); my_row != load_data.end(); ++my_row)
    {
        sql +="(\"";
        sql += vectorToString(*my_row,"\",\"");
        sql +="\")";
        if(row < load_data.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}

//
/////////////////////////////////////////////////////
////****table drivers****////
void selDriverDataByCode(std::string& sql, long code)
{
    sql = "SELECT CODIGO_TRANSPORTISTA, NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from TRANSPORTISTAS WHERE (CODIGO_TRANSPORTISTA = ";
    sql += std::to_string(code) + " AND (BORRADO is null or BORRADO = 0))";
    return;
}

void selAllDrivers(std::string& sql)
{
    sql = "select codigo_transportista, nombre, nif, direccion, provincia, poblacion, cp, comunidad_autonoma, nima, num_inscripcion, telefono, mail FROM transportistas WHERE (BORRADO is null or BORRADO = 0) order by NOMBRE";
    return;
}

void rmtSelAllDrivers(std::string& sql)
{
    sql = "select codigo_transportista, nombre, nif, domicilio, provincia, poblacion, cp, comunidad_autonoma, nima, num_inscripcion, telefono, mail FROM transportistas WHERE BORRADO = 0;";
    return;
}

void loadDrivers(std::string& sql, std::vector<std::vector<std::string>> dataReturn)
{
    std::vector<std::vector<std::string>>::iterator myRow;
    long unsigned int row = 0;
    sql = "insert into transportistas (codigo_transportista, nombre,nif, direccion, provincia,poblacion,cp,comunidad_autonoma,nima,num_inscripcion,telefono,mail) values ";
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
        sql +="(\"";
        sql += vectorToString(*myRow,"\",\"");
        sql +="\")";
        if(row < dataReturn.size()-1)
      	    sql += ",";
        row++;
    }
    return;
}

// table params

void getParamValue(std::string& sql, std::string pname)
{
    sql = "select pvalue, year from params where pname = \"" + pname + "\"";
    return;
}
void setParamValue(std::string& sql, std::string pname, std::string pvalue, std::string year)
{
    sql = "INSERT OR REPLACE INTO params (pname, pvalue, year) VALUES ( \'";
    sql += pname + "\', \'" + pvalue + " \', \'" + year + " \')";
    return;
}

/////////////////////////////////////////
void selectAllFromClient(char * &sql, const char *cliente)
{
  sql = new char[sizeof("select * from `CLIENTES` where (`NOMBRE`= ")+30];
   
  sprintf(sql,"select * from `CLIENTES` where (`NOMBRE`= \"%s\")",cliente);

  return;
}
void selNifFromCostumersByCode(char *&sql, const char *costumerCode)
{
  sql = new char[sizeof("select NIF from `CLIENTES` where (CODIGO= ")+30];
   
  sprintf(sql,"select NIF from `CLIENTES` where (`CODIGO_CLIENTE`= \"%s\")",costumerCode);

  return;
}

void selectAllFromLer(char * &sql, const char *ler)
{
  sql = new char[sizeof("select * from PRODUCTOS where (`CODIGO_LER`= ) LIMIT 1")+30];
   
  sprintf(sql,"select * from PRODUCTOS where (`CODIGO_LER`= \"%s\") LIMIT 1",ler);

  return;
}


void selAllProdsCodesPermsFromProductos(char *&sql,const char* tipoEstacion)
{
  sql = new char[sizeof("select CODIGO_PRODUCTO,CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_XX,CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from PRODUCTOS ORDER BY nombre,nombre2,nombre3")+20];
  sprintf(sql,"select CODIGO_PRODUCTO,CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_%s,CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from PRODUCTOS order by nombre,nombre2,nombre3",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion);
  
  return;
}
void selPermitsTypeClientProd(char *& sql,const char* tipoEstacion, const char* codigoCliente, const char* codigoProducto)
{
  sql = new char[sizeof("select CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from CLIENTES_PRODUCTOS WHERE (CODIGO_PRODUCTO = AND CODIGO_CLIENTE = )")+strlen(tipoEstacion)*5 + strlen(codigoCliente) + strlen(codigoProducto)+32];
  
  sprintf(sql,"select CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from CLIENTES_PRODUCTOS WHERE (CODIGO_PRODUCTO =%s AND CODIGO_CLIENTE =%s)",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,codigoProducto,codigoCliente);

  return;
}

void selProdsCodesPermsFromClienteProductos(char *& sql, const char* codigoCliente , const char* tipoEstacion)
{
  sql = new char[sizeof("select CODIGO_PROD,CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from CLIENTES_PRODUCTOS WHERE CODIGO_CLIENTE =  ORDER BY CODIGO_PROD ASC")+strlen(tipoEstacion)*5 + strlen(codigoCliente) +32];

  sprintf(sql,"select CODIGO_PROD,CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from CLIENTES_PRODUCTOS WHERE CODIGO_CLIENTE =%s ORDER BY CODIGO_PROD ASC",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,codigoCliente);

  return;
}
void selProdsPermsFromProductosByCode(char *& sql, std::vector <std::string> prodCodes, const char* estacion)
{
  std::string temp;
  std::vector <std::string>::iterator iter;
  sql = new char[sizeof("select CODIGO_PROD,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_XX,CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX,CODIGO_ER from productos where (codigo_prod=40001) ORDER BY CODIGO_PROD ASC")+ 9*sizeof(char)*prodCodes.size() +32];

  temp = "select CODIGO_PROD,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_";
  temp += estacion;
  temp +=",CONTRATO_";
  temp += estacion;
  temp += ",NPT_";
  temp += estacion;
  temp += ",CB_";
  temp += estacion;
  temp += ",CP_";
  temp += estacion;
  temp += ",DCP_";
  temp += estacion;
  temp += " from productos where (codigo_prod=";
  for(iter = prodCodes.begin();iter != prodCodes.end(); ++iter)
    {
      if(iter == prodCodes.begin())
	  temp += *iter;
      
      else
	{
	  temp += " OR codigo_prod=";
	  temp += *iter;
	}
    }
  temp+=") ORDER BY codigo_prod ASC";
  sprintf(sql,temp.c_str());
  
  return;
}

void selCostumerNameByCode(std::string& sql, std::string code)
{
    sql = "SELECT NOMBRE from CLIENTES WHERE (CODIGO_CLIENTE = " + code + ")";
    return;
}

void selectProductDataByCode(char *& sql, const char* code)
{ 
  sql = new char[sizeof("SELECT NOMBRE, NOMBRE2, CODIGO_LER, NOMBRE 3, PERMISO_PT,CONTRATO_PT,NPT_PT,CB_PT,CP_PT,DCP_PT, PERMISO_ET,CONTRATO_ET,NPT_ET,CB_ET,CP_ET,DCP_ET, PERMISO_D5,CONTRATO_D5,NPT_D5,CB_D5,CP_D5,DCP_D5, PERMISO_SAL,CONTRATO_SAL,NPT_SAL,CB_SAL,CP_SAL,DCP_SAL from PRODUCTOS WHERE (CODIGO_PRODUCTO=XXXXX)")+12];
  sprintf(sql,"SELECT NOMBRE, NOMBRE2, CODIGO_LER, NOMBRE 3, PERMISO_PT,CONTRATO_PT,NPT_PT,CB_PT,CP_PT,DCP_PT, PERMISO_ET,CONTRATO_ET,NPT_ET,CB_ET,CP_ET,DCP_ET, PERMISO_D5,CONTRATO_D5,NPT_D5,CB_D5,CP_D5,DCP_D5, PERMISO_SAL,CONTRATO_SAL,NPT_SAL,CB_SAL,CP_SAL,DCP_SAL from PRODUCTOS WHERE (CODIGO_PRODUCTO=%s)",code);
  
  return; 
}
void selProductBasisByCode(std::string& sql, std::string code)
{  
    sql = "SELECT CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,DESCRIPCION_PELIGRO from PRODUCTOS";
    sql += " WHERE (CODIGO_PRODUCTO =" + code + ")";
    return; 
}

void selPermitsFromClientAndProd(char *& sql,const char* tipoEstacion, const char* codigoCliente, const char* codigoProducto)
{
  sql = new char[sizeof("select case when PRODUCTOS.PERMISO_XXX > 0 then 1 else 0 end,case when PRODUCTOS.CONTRATO_XXX>0 AND CLIENTES_PRODUCTOS.CONTRATO_XXX >= CURRENT_DATE THEN 1 WHEN PRODUCTOS.CONTRATO_XXX=0 THEN 1 ELSE 0 END,case when PRODUCTOS.NPT_XXX>0 AND CLIENTES_PRODUCTOS.NPT_XXX >0 THEN 1 WHEN PRODUCTOS.NPT_XXX=0 THEN 1 ELSE 0 END,case when PRODUCTOS.CB_XXX>0 AND CLIENTES_PRODUCTOS.CB_XXX >0 THEN 1 WHEN PRODUCTOS.CB_SAL=0 THEN 1 ELSE 0 END,case when PRODUCTOS.CP_SAL>0 AND CLIENTES_PRODUCTOS.CP_SAL >0 THEN 1 WHEN PRODUCTOS.CP_SAL=0 THEN 1 ELSE 0 END,case when PRODUCTOS.DCP_SAL>0 AND CLIENTES_PRODUCTOS.DCP_SAL >0 THEN 1 WHEN PRODUCTOS.DCP_SAL=0 THEN 1 ELSE 0 END FROM CLIENTES_PRODUCTOS INNER JOIN PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = xxxxx AND PRODUCTOS.CODIGO_PRODUCTO = xxxxx AND CLIENTES_PRODUCTOS.CODIGO_CLIENTE = xxxxx") + 32];
  
  sprintf(sql,"select case when PRODUCTOS.PERMISO_%s > 0 then 1 else 0 end,case when PRODUCTOS.CONTRATO_%s>0 and CLIENTES_PRODUCTOS.CONTRATO_%s >= CURRENT_DATE then 1 when PRODUCTOS.CONTRATO_%s=0 then 1 else 0 end,case when PRODUCTOS.NPT_%s>0 and CLIENTES_PRODUCTOS.NPT_%s >0 then 1 when PRODUCTOS.NPT_%s=0 then 1 else 0 end, case when PRODUCTOS.CB_%s>0 and CLIENTES_PRODUCTOS.CB_%s >0 then 1 when PRODUCTOS.CB_%s=0 then 1 else 0 end, case when PRODUCTOS.CP_%s>0 and CLIENTES_PRODUCTOS.CP_%s >0 THEN 1 when PRODUCTOS.CP_%s=0 then 1 else 0 end,case when PRODUCTOS.DCP_%s>0 and CLIENTES_PRODUCTOS.DCP_%s >0 then 1 when PRODUCTOS.DCP_%s=0 then 1 else 0 end from CLIENTES_PRODUCTOS inner join PRODUCTOS on CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = %s and PRODUCTOS.CODIGO_PRODUCTO = %s and CLIENTES_PRODUCTOS.CODIGO_CLIENTE = %s",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,codigoProducto,codigoProducto,codigoCliente);

  return;
}

void selLastDiFromMovementsByClient(char *& sql, const char* codigoCliente)
{
 sql = new char[sizeof("select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=XXXXX ORDER BY DATETIME(FECHA_HORA) DESC;") + 32];

 sprintf(sql,"select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=%s ORDER BY DATETIME(FECHA_HORA_FINAL) DESC", codigoCliente);

 return;
}

void selLastMovCode(std::string& sql, std::string codigo_estacion)
{
    time_t myTime = time(NULL);
    struct tm *aTime = localtime(&myTime);
    int year = aTime->tm_year + 1900;

    std::string codigo = std::to_string(year);
    // TODO REVCODES
    //if(strlen(codigo_estacion)<2)
    //  codigo += "0";
    codigo += codigo_estacion;

    std::string codigo_min = codigo + "0000011";
    std::string codigo_max = codigo + "9999999";
  
    sql = "select CODIGO_MOV FROM movimientos WHERE (CODIGO_MOV >= ";
    sql += codigo_min;
    sql += " AND CODIGO_MOV <= ";
    sql += codigo_max;
    sql += ") ORDER BY CODIGO_MOV DESC LIMIT 1";

    return;
}

void rmt_selAllFromTransito(char *& sql,int fromStation)
{
  sql = new char[sizeof("select DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR,PESO_SALIDA,CODIGO_ESTACION FROM transito where CODIGO_ESTACION = XXXXX")+32];
  sprintf(sql,"select DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR,PESO_SALIDA,CODIGO_ESTACION FROM transito where CODIGO_ESTACION = %d",fromStation);
  
  return;
}

//////


void sqlLoadTransito(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transito (DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA, CODIGO_ESTACION, SINCRONIZADO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      //TRANSFORM MYSQL DATES TO SQLITE DATES
      myRow->at(1) = mysql2sqliteDate(myRow->at(1));
      //////////////////////////////////////
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\",1)";  //<- 1 for syncronized
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}

//remote

void remote_updatePesoSalidaTransito(std::string& sql, long costumer_code, const char* date_time, int station_code, unsigned int scale, const char* comentario, const char* incidents)
{    
  sql = "INSERT INTO transito (FECHA_HORA, CODIGO_CLIENTE, CODIGO_ESTACION,PESO_SALIDA,COMENTARIO_OPERADOR,INCIDENCIAS) VALUES (\"";
  sql += date_time;
  sql += "\",";
  sql += std::to_string(costumer_code);
  sql += ",";
  sql += std::to_string(station_code);
  sql += ",";
  sql += std::to_string(scale);
  sql += ",\"";
  sql += comentario; 
  sql += "\",\"";
  sql += incidents;
  sql += "\") ON DUPLICATE KEY UPDATE PESO_SALIDA = VALUES(PESO_SALIDA),COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), INCIDENCIAS = VALUES(INCIDENCIAS);";
 
  return;
}
void remote_updatePesoSalidaTransitoSalida(std::string& sql, long costumer_code, const char* date_time, long station_code,  unsigned int scale, const char* comentario, const char* incidents)
{    
    sql = "INSERT INTO transito_salidas (FECHA_HORA, CODIGO_CLIENTE, CODIGO_ESTACION,PESO_RETIRADO,COMENTARIO_OPERADOR, INCIDENCIAS) VALUES (\"";
    sql += date_time;
    sql += "\",";
    sql += std::to_string(costumer_code);
    sql += ",";
    sql += std::to_string(station_code);
    sql += ",";
    sql += std::to_string(scale);
    sql += ",\"";
    sql += comentario; 
    sql += "\",\"";
    sql += incidents;
    sql += "\") ON DUPLICATE KEY UPDATE PESO_RETIRADO = VALUES(PESO_RETIRADO),COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), INCIDENCIAS = VALUES(INCIDENCIAS);";
    return;
}
