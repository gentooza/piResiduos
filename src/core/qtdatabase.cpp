/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.
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

/***************************************************************************
                          qtdatabase.cpp  -  description
                             -------------------
    begin                : Fri May 28 2010
    http://pvbrowser.org
	improved 			: January 2017
 ***************************************************************************/
#include "qtdatabase.h"

qtDatabase::qtDatabase()
{
  //db = new QSqlDatabase;
  //std::cout << db->drivers().isEmpty() <<std::endl;
  //delete db;

  db = NULL;
  result = new QSqlQuery();
  error  = new QSqlError();
}

qtDatabase::~qtDatabase()
{
  if(db != NULL)
  {
    close();
  }
  delete result;
  delete error;
}

int qtDatabase::open(const char *dbtype, const char *hostname, const char *dbname, const char *user, const char *pass, int port)
{ 
  if(db != NULL) return -1;
  db = new QSqlDatabase;

  *db = QSqlDatabase::addDatabase(dbtype,dbname);
  db->setHostName(hostname);
  db->setDatabaseName(dbname);
  db->setUserName(user);
  db->setPassword(pass);
  db->setPort(port);
  if(!strcmp(dbtype,"QMYSQL"))
     db->setConnectOptions("MYSQL_OPT_RECONNECT=1");
  if(db->open())
  {
    return 0;
  }
  else
  {
    delete db;
    db = NULL;
    return -1;
  }
}

int qtDatabase::isOpen()
{
  int ret = 1;
  if(db != NULL)
    {
      if(!db->isOpen())
	{
	  ret = 0;
	}
    }
  return ret;
}

int qtDatabase::reOpen()
{
  int ret = 1;
  if(db != NULL)
    {
      db->close();
      if(db->open())
	{
	  ret = 0;
	}
    }
  return ret;
}

int qtDatabase::close()
{
  if(db == NULL) 
  {
    return -1;
  }  
  db->close();
  delete db;
  db = NULL;
  return 0;
}

int qtDatabase::query(PARAM *p, const char *sqlcommand)
{
  if(db == NULL) return -1;
  std::cout << "DEBUG: executing sql query ---> " << sqlcommand << std::endl;
  QString qsqlcommand = QString::fromUtf8(sqlcommand);
  *result = db->exec(qsqlcommand);
  *error = db->lastError();
  if(error->isValid())
  {
    QString e = error->databaseText();
    printf("qtDatabase::query ERROR: %s\n", (const char *) e.toUtf8());
    //pvStatusMessage(p,255,0,0,"ERROR: qtDatabase::query(%s) %s", sqlcommand, (const char *) e.toUtf8());
    return -1;
  }
  return 0;
}

int qtDatabase::populateTable(PARAM *p, int id)
{
  int x,y,xmax,ymax;
  
  if(db == NULL)
  {
    pvStatusMessage(p,255,0,0,"ERROR: qtDatabase::populateTable() db==NULL");
    return -1;
  }  

  // set table dimension
  xmax = result->record().count();
  //
  // Using SQLITE a user from our forum found an issue
  // getting ymax.
  // With SQLITE numRowsAffected() does not return the correct value.
  // Other database systems do.
  //
  if(db->driverName() == "QSQLITE")
  {
    result->last();
    ymax = result->at()+1;
    result->first();
    //printf("SQLITE ymax = %d \n",ymax);
  }
  else
  {
    ymax = result->numRowsAffected();
    //printf("no SQLITE, ymax = %d \n",ymax);
  }
  pvSetNumRows(p,id,ymax);
  pvSetNumCols(p,id,xmax);

  // populate table
  QSqlRecord record = result->record();
  if(record.isEmpty())
  {
    pvStatusMessage(p,255,0,0,"ERROR: qtDatabase::populateTable() record is empty");
    return -1;
  }

  for(x=0; x<xmax; x++)
  { // write name of fields
    pvSetTableText(p, id, x, -1, (const char *) record.fieldName(x).toUtf8());
  }
  result->next();
  for(y=0; y<ymax; y++)
  { // write fields
    QSqlRecord record = result->record();
    for(x=0; x<xmax; x++)
    {
      QSqlField f = record.field(x);
      if(f.isValid())
      {
        QVariant v = f.value();
        pvSetTableText(p, id, x, y, (const char *) v.toString().toUtf8());
      }
      else
      {
        pvSetTableText(p, id, x, y, "ERROR:");
      }
    }
    result->next();
  }

  return 0;
}

int qtDatabase::retData(PARAM *p, char **** table, int **columns, int **rows)
{
  //std::cout << "DEBUG: (inside qtDatabase::retData)" << std::endl;
  int x,y,xmax,ymax, failed = -1;
  char ***retTable;
  int * pointX;
  int * pointY;

  pointX = new int();
  pointY = new int();
  
  if(db != NULL)
  {
    // set table dimension
    xmax = result->record().count();
    //
    // Using SQLITE a user from our forum found an issue
    // getting ymax.
    // With SQLITE numRowsAffected() does not return the correct value.
    // Other database systems do.
    //
    if(db->driverName() == "QSQLITE")
      {
	result->last();
	ymax = result->at()+1;
	result->first();
	//printf("SQLITE ymax = %d \n",ymax);
      }
    else
      {
	ymax = result->numRowsAffected();
	//printf("no SQLITE, ymax = %d \n",ymax);
      }
    //std::cout << "DEBUG: (inside qtDatabase::retData) return of columns:" << xmax <<"  and rows:" << ymax << std::endl;
    retTable = new char**[ymax];
    for(int i =0; i < ymax; i++)
      retTable[i] = new char*[xmax];
    *pointX = xmax;
    *pointY = ymax;
    // populate table
    QSqlRecord record = result->record();
    if(!record.isEmpty())
      {
	result->next();
	for(y=0; y<ymax; y++)
	  { // write fields
	    QSqlRecord record = result->record();
	    for(x=0; x<xmax; x++)
	      {
		QSqlField f = record.field(x);
		if(f.isValid())
		  {
		    QVariant v = f.value();
		    //retTable[y][x] = new char[strlen(v.toString().toUtf8())];
		    //sprintf(retTable[y][x],"%s",v.toString().toUtf8());
		    retTable[y][x] = new char[strlen(v.toByteArray().data())];
		    sprintf(retTable[y][x],"%s",v.toByteArray().data());
		  }
		else
		  {
		    retTable[y][x] = new char[strlen("ERROR")];
		    sprintf(retTable[y][x],"ERROR");
		  }
	      }
	    result->next();
	  }
	failed = 0;
      }
  }
  //std::cout << "DEBUG: (inside qtDatabase::retData) returning" << std::endl; 
  *table = retTable;
  *columns = pointX;
  *rows = pointY;
  return failed;
}

const char *qtDatabase::recordFieldValue(PARAM *p, int x)
{
  QSqlRecord record = result->record();
  if(record.isEmpty())
  {
    pvStatusMessage(p,255,0,0,"ERROR: qtDatabase::recordFieldValue(%d) record is empty", x);
    return "ERROR:";
  }
  QSqlField f = record.field(x);
  if(f.isValid())
  {
    QVariant v = f.value();
    //return v.toString().toUtf8();
    //printf("%s\n", v.toString());
	//modified by Joa
    return v.toByteArray().data();
  }
  else
  {
    pvStatusMessage(p,255,0,0,"ERROR: qtDatabase::recordFieldValue(%d) field is invalid", x);
    return "ERROR:";
  }
}

int qtDatabase::nextRecord()
{
  result->next();
  QSqlRecord record = result->record();
  if(record.isEmpty()) return -1;
  return 0;
}


std::vector<std::vector<std::string>> qtDatabase::retData2()
{
    std::cout << "DEBUG: (inside qtDatabase::retData2)" << std::endl;
  
    int xmax,ymax,failed = -1;
    std::vector <std::vector <std::string>> matrix;
    xmax = result->record().count();
    if(db->driverName() == "QSQLITE")
    {
        ymax = 0;
        if(result->last() && result->isValid())
        {
            ymax = result->at()+1;
            result->first();
        }
        // std::cout << "SQLITE ymax = " << ymax << std::endl;
    }
    else
    {
        ymax = result->numRowsAffected();
        // std::cout << "NO SQLITE ymax = " << ymax << std::endl;
    }

    if(db != NULL)
    {
        QSqlRecord record = result->record();
        if(!record.isEmpty())
        {
	        for(int i=0; i < ymax;i++)
	        {
	            if(db->driverName() != "QSQLITE")
	                result->next();
	            std::vector < std::string> row;	    
	            QSqlRecord record = result->record();
	            for (int j=0;j< xmax; j++)
	            {		
		            QSqlField f = record.field(j);
		            if(db->driverName() != "QSQLITE" ? f.isValid() : !f.isNull())
		            {
		                QVariant v = f.value();
		                // std::cout << i << "," << j <<" = " << v.toByteArray().constData() << std::endl;
		                if(v.canConvert(QVariant::String))
		                    row.push_back(v.toString().toUtf8().constData());
		                else
		                    row.push_back(v.toByteArray().constData());
		                //row.push_back(v.toByteArray().data());
		                //sprintf(retTable[y][x],"%s",v.toByteArray().data());
		                failed = 0;
		            }
		            else
		                row.push_back("");
	            }
	            if(!row.empty())
	                matrix.push_back(row);
	            if(db->driverName() == "QSQLITE")
	                result->next();
	        }
        }
    }
    return matrix;
}
