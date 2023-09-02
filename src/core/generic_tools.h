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

/**
@file generic_tools.h
*/

#ifndef _GEN_TOOLS_
#define _GEN_TOOLS_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//string, vectors tools
std::vector <std::string> stringToVector(std::string text,std::string separator);
std::string vectorToString(std::vector<std::string> ourVector,std::string separator);
int areVectorsDifferents(std::vector<std::string> v1, std::vector<std::string> v2);
int are2dMatrixDifferents(std::vector<std::vector<std::string>> myVector1, std::vector<std::vector<std::string>> myVector2);
void showMatrixContent(std::vector<std::vector <std::string>> myData);
int isStrInVector(std::vector < std::string> list, std::string myString);
int findCodeInList(std::vector<std::string>,long);
long retCodeFromString(std::string fromString,std::string separator); //we have a string with format: "XXXXXX...XXX {code}" this function will return the code.
std::string extractIncidentCode(std::string);
std::vector<std::string> ret_paragraph_with_lines_return(std::string original,int line_width);
std::string stringToUppercase(std::string);

//
int isNewYear(std::string temporalDIDate,int year);
std::string getCurrentDate();
int compareDates(std::string first, std::string second);
std::string mysql2sqliteDate(std::string oldDate);
std::string removeTime(std::string dateTime);

void espera(int seconds);
std::string zeroPadNumber(int num, int stringLength);
int isConnected(const char* address, int port);
std::string fromBufferAPeso(char * buffer);

//SPECIAL
int upload_movement_files_from_sql(std::vector< std::vector< std::string>> data_from_sql_movement, int field);
int copy_files_to_remote_server(std::string folder_in_backups);
int tools_copy(const char * origin, const char * destination);
int log_message(std::string message, int level);

#endif
