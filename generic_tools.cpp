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
@file generic_tools.cpp
*/
#include "generic_tools.h"


std::vector <std::string> stringToVector(std::string cadena, std::string separator)
{
  std::vector < std::string> ourVector;
  size_t location = 0;

  while(location = cadena.find(separator,0))
    {
      if(location!=std::string::npos)
	{
	  ourVector.push_back(cadena.substr(0,location));
	  cadena.erase(0,location+1);
	}
      else
	{
	  if (!cadena.substr(0,location).empty())
	    ourVector.push_back(cadena.substr(0,cadena.length()));
	  break;
	}
    }
  return ourVector;
}

std::string vectorToString(std::vector<std::string> ourVector,std::string separator)
{
  std::string ret = "";
  std::vector<std::string>::iterator iter;
  if(!ourVector.empty())
    {
      for(iter=ourVector.begin();iter!=ourVector.end();++iter)
	{
	  ret += *iter;
	  ret += separator;
	}
      ret.erase(ret.length()-separator.length(),separator.length());
    }
  return ret; 
}

int areVectorsDifferents(std::vector<std::string> v1, std::vector<std::string> v2)
{
  int ret = 1;
  if(v1.size() ==  v2.size())
    {
      std::set<std::string> s1(v1.begin(), v1.end());
      std::set<std::string> s2(v2.begin(), v2.end());
      std::vector<std::string> v3;
      std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(v3));

      if(v3.size() == v1.size())
	ret = 0;
    }  
  return ret;
}

int are2dMatrixDifferents(std::vector<std::vector<std::string>> v1, std::vector<std::vector<std::string>> v2)
{
  int ret = 1; 
  if(v1.size() ==  v2.size())
    {
      std::vector<std::vector<std::string>>::iterator v1Iter;
      std::vector<std::vector<std::string>>::iterator v2Iter;
      int equals = 1;
      for(v1Iter = v1.begin(), v2Iter = v2.begin(); v1Iter != v1.end() && v2Iter != v2.end() && equals; ++v1Iter , ++v2Iter)
	{
	  equals = !areVectorsDifferents(*v1Iter, *v2Iter);
	}
    }
  return ret;
}

void showMatrixContent(std::vector<std::vector <std::string>> myData)
{
 
  std::vector<std::vector<std::string>>::iterator myRow;

  std::cout << "showing content--->" << std::endl;
  for(myRow = myData.begin(); myRow != myData.end();++myRow)
    {
      std::cout << "(\"";
      std::cout << vectorToString(*myRow,"\",\"");
      std::cout << "\")" << std::endl;

    }
  std::cout << "<---Finish showing content" << std::endl;
  return;
}
/*! int isStrInVector(std::vector < std::string> list, std::string myString)
function to get if a string is inside a vector and it's  position
*/
int isStrInVector(std::vector < std::string> list, std::string myString)
{
  int itIs=-1;
  unsigned int i = 0;
  std::vector<std::string>::iterator iter;
  for(iter = list.begin(); iter != list.end(); ++iter)
    {
      if(!iter->compare(myString))
	itIs=i;
      i++;
    }
  
  return itIs;
}

int findCodeInList(std::vector<std::string> myVector ,long myCode)
{
  int i = 0;
  std::vector<std::string>::iterator iter;
  int found = 0;
  int posFound = 0;
  std::size_t posCode;
  long codeToCompare;
  
  iter = myVector.begin();
  while(iter != myVector.end() && !found)
    {
      posCode = iter->find_last_of(" ");
      try
	{
	  codeToCompare = std::stol(iter->substr(posCode+1));
	}
      catch(...)
	{
	std::cout << "in findCodeInList, cant convert!" << iter->substr(posCode+1) << std::endl;
	codeToCompare = 0;
	}
      if(myCode == codeToCompare)
	{
	  std::cout << "Found!, code:"<< myCode << " register:" << *iter << " position:"<<i<<std::endl;
	  found =1;
	  posFound = i;
	}
      i++;
      ++iter;
    }
  
  if(!found)
    posFound = -1;
  
  return posFound;
}

//we have a string with format: "XXXXXX...XXX {code}" this function will return the code.
long retCodeFromString(std::string fromString, std::string separator)
{
  long code;
  std::size_t found = fromString.find_last_of(separator);
  try
    {
      code = std::stol(fromString.substr(found+1));
    }
  catch(...)
    {
      code = 0;
    }

  return code;
}

std::string extractIncidentCode(std::string incident)
{
  std::string code;
  std::size_t found = incident.find_first_of(":");
  try
    {
      code = incident.substr(0,found);
    }
  catch(...)
    {
      code = "0";
    }
  
  return code;
}

std::vector<std::string> ret_paragraph_with_lines_return(std::string original,int line_width)
{
  std::vector<std::string> my_paragraph;
  std::string tmp;
  std::size_t new_pos;

  tmp = original;
  while(tmp.length() > line_width)
    {
      std::cout << "analizyng string: " << tmp << " , longitud:" << tmp.length() << std::endl;
      new_pos = tmp.substr(0,line_width).find_last_of(' ');
      if(new_pos != std::string::npos)
	{
	  my_paragraph.push_back(tmp.substr(0,new_pos));
	  tmp = tmp.substr(new_pos+1);
	}
      else
	{
	  my_paragraph.push_back(tmp.substr(0,line_width));
	  tmp = tmp.substr(line_width+1);
	}
    }
  my_paragraph.push_back(tmp);
  return my_paragraph;
}
// easy function to convert to uppercase a string */
std::string stringToUppercase(std::string toConvert)
{
  for(int i = 0; i < toConvert.length(); i++)
  {
    toConvert[i] = std::toupper(toConvert[i]);
  }
  return toConvert;
}

////
int isNewYear(std::string temporalDIDate,int year)
{
  int ret = 1;
  if(!temporalDIDate.empty())
    {
      std::string sYear = std::to_string(year);
      std::string tempYear = temporalDIDate.substr(0,4);
      if(!tempYear.compare(sYear))
	ret = 0;
    }
    
  return ret;
}

std::string getCurrentDate()
{
  std::string myDate;
  std::string myTime;
  time_t t = time(NULL);
  tm* timePtr = localtime(&t);

  myDate = std::to_string(timePtr->tm_year+1900);
  myDate += '-';

  if(timePtr->tm_mon+1 <10)
      myDate += '0';
  myDate += std::to_string(timePtr->tm_mon+1);
  
  myDate += '-';

  if(timePtr->tm_mday <10)
      myDate += '0';
  myDate += std::to_string(timePtr->tm_mday);

  if(timePtr->tm_hour < 10)
      myTime += '0';
  myTime += std::to_string(timePtr->tm_hour);
  
  myTime += ':';
  
  if(timePtr->tm_min < 10)
      myTime += '0';
  myTime += std::to_string(timePtr->tm_min);

  myTime += ':';
  
  if(timePtr->tm_sec < 10)
      myTime += '0';

  if(timePtr->tm_sec > 59)
      myTime += '59';
  else
      myTime += std::to_string(timePtr->tm_sec);

  std::string myWhole = myDate + " " + myTime;
  
  return myWhole;
}
/*! 0 equal, 1 greater, -1 lower */
int compareDates(std::string first, std::string second)
{
  std::string fSub,sSub;
  int fNum,sNum;

  first.append(19 - first.length(),'0');
  second.append(19 - second.length(),'0');  
  //year
  fSub = first.substr(0,4);
  sSub = second.substr(0,4);
  try
    {
      fNum = std::stoi(fSub);
      sNum = std::stoi(sSub);
    }
  catch(...)
    {
      return -1;
    }
  if(fNum > sNum)
    return 1;
  else if (fNum < sNum)
    return -1;
  else
    {
      //month
      fSub = first.substr(5,2);
      sSub = second.substr(5,2);
      try
	{
	  fNum = std::stoi(fSub);
	  sNum = std::stoi(sSub);
	}
      catch(...)
	{
	  return -1;
	}
      if(fNum > sNum)
	return 1;
      else if (fNum < sNum)
	return -1;
      else
	{
	  //day
	  fSub = first.substr(8,2);
	  sSub = second.substr(8,2);
	  try
	    {
	      fNum = std::stoi(fSub);
	      sNum = std::stoi(sSub);
	    }
	  catch(...)
	    {
	      return -1;
	    }
	  if(fNum > sNum)
	    return 1;
	  else if (fNum < sNum)
	    return -1;	      
	  else
	    {
	      //hour
	      fSub = first.substr(11,2);
	      sSub = second.substr(11,2);
	      try
		{
		  fNum = std::stoi(fSub);
		  sNum = std::stoi(sSub);
		}
	      catch(...)
		{
		  return -1;
		}
	      if(fNum > sNum)
		return 1;
	      else if (fNum < sNum)
		return -1;	      
	      else
		{
		  //minutes
		  fSub = first.substr(14,2);
		  sSub = second.substr(14,2);
		  try
		    {
		      fNum = std::stoi(fSub);
		      sNum = std::stoi(sSub);
		    }
		  catch(...)
		    {
		      return -1;
		    }
		  if(fNum > sNum)
		    return 1;
		  else if (fNum < sNum)
		    return -1;	      
		  else
		    {
		      //seconds
		      fSub = first.substr(17,2);
		      sSub = second.substr(17,2);
		      try
			{
			  fNum = std::stoi(fSub);
			  sNum = std::stoi(sSub);
			}
		      catch(...)
			{
			  return -1;
			}
		      if(fNum > sNum)
			return 1;
		      else if (fNum < sNum)
			return -1;	      
		      else
			return 0;
		    }
		}
	    }
	}
    }			      	
  
  return -1;
  
}
/*! function to remove the T character appearing in mysql dates*/
std::string mysql2sqliteDate(std::string oldDate)
{
  std::string stringToReplace;
  std::string stringReplacement;
  std::string newDate;

  //fucking T character!, why?!?!?!
  stringToReplace = "T";
  stringReplacement = " ";

  if(!oldDate.empty())
    {
      std::size_t found = oldDate.find(stringToReplace);
      if (found!=std::string::npos)
	{//REPLACE!
	  oldDate.replace(found,stringToReplace.length(),stringReplacement);	  
	}
    }
  newDate = oldDate;
  
  return newDate;
}

/*!function for removing time for our date time string*/
std::string removeTime(std::string dateTime)
{
  std::string myDate;
  std::size_t found = dateTime.find_first_of(" ");
  try
    {
      myDate = dateTime.substr(0,found);
    }
  catch(...)
    {
      myDate.clear();
    }
  
  return myDate;
}

void espera(int seconds)
{
  if(seconds >=0)
    {
      fflush(stdout);
      sleep((unsigned int)seconds);
    }
  return;
}
///
std::string zeroPadNumber(int num, int stringLength)
{
  std::stringstream ss;
	
  // the number is converted to string with the help of stringstream
  ss << num; 
  std::string ret;
  ss >> ret;
	
  // Append zero chars
  int str_length = ret.length();
  for (int i = 0; i < stringLength - str_length; i++)
    ret = "0" + ret;
  return ret;
}

/*! isConnected(int elementId)
check if server connection is possible, elementId from enum in pvapp.h
returns 0 if unavailable*/
int isConnected(const char* address, int port)
{//https://stackoverflow.com/questions/26365575/gethostbyname-h-addr-list-incorrect-first-bit
  int ret = 0;
  int sockfd, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  struct in_addr ipv4addr;

  int method = 0;
  int i;
  const int len = strlen(address);
  for (i = 0; i < len; i++)
  {
    if (!isdigit(address[i]) && address[i] != '.')
	    method=1;
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd >= 0) //we have network
  {
    if(method) // by address
	  {
	    server = gethostbyname(address);
	    if(server!=NULL)
	    {
	      //bzero((char *) &serv_addr, sizeof(serv_addr));
	      memset((char *) &serv_addr,0, sizeof(serv_addr));
	      serv_addr.sin_family = AF_INET;
	      memmove((char *)server->h_addr, 
		      (char *)&serv_addr.sin_addr.s_addr,
		      server->h_length);
	      serv_addr.sin_port = htons(port);
	      if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) >= 0)
		    {
		      //SUCCESS!
		      ret = 1;
		      close(sockfd);
		    }
	      else
		      std::cout << "CONNECT FAIL! : "<< strerror(errno) << " to host:" <<  (char *)server->h_addr <<std::endl;
	    }
	    else
	      std::cout << "CONNECT method 1 FAIL!!\n" << std::endl;
	  }
    else
	  {
	    struct sockaddr_in sin;
	    sin.sin_family = AF_INET;
	    sin.sin_port   = htons(port);  // Could be anything
	    inet_pton(AF_INET, address, &sin.sin_addr);
	    if (connect(sockfd,(struct sockaddr *) &sin,sizeof(sin)) >= 0)
	    {
	      //SUCCESS!
	      ret = 1;
	      close(sockfd);
	    }
	    else
	      std::cout << "CONNECT method 2 FAIL!\n" <<std::endl;
	  }
  }
  return ret;
  // temporal bypass
  // return 1;
}

std::string fromBufferAPeso(char * buffer)
{
  std::string tmpBuffer = buffer;
  std::string peso = "-1";
  int ipeso;
  //console


  if(tmpBuffer.size() >= 10)
    {
      peso = tmpBuffer.substr(2,8);
	  try
	    {
	      ipeso = std::stoi(peso);
	    }
	  catch(...)
	    {
	      ipeso = 0;
	    }
      peso = std::to_string(ipeso);
    }
  
  return peso;
}

int upload_movement_files_from_sql(std::vector< std::vector< std::string>> data_from_sql_movement, int field)
{
  std::vector< std::vector <std::string> >::iterator iter;

  for(iter = data_from_sql_movement.begin(); iter != data_from_sql_movement.end(); ++iter)
    {
      if(iter->size()> (field+1))
	{
	  copy_files_to_remote_server(iter->at(field));
	}
    }
}


int copy_files_to_remote_server(std::string folder_in_backup)
{
  std::string command = "rsync -r --exclude '*.pdf' \"backup/";
  command += folder_in_backup;
  command += "\"";
  command += " biogesin@bioreciclaje.es:/home/biogesin/public_html/movimientos &";
  return(system(command.c_str()));
}

int tools_copy(const char * origin, const char * destination)
{
 int read_fd;
 int write_fd;
 struct stat stat_buf;
 off_t offset = 0;

 /* Open the input file. */
 read_fd = open (origin, O_RDONLY);
 /* Stat the input file to obtain its size. */
 fstat (read_fd, &stat_buf);
 /* Open the output file for writing, with the same permissions as the
   source file. */
 write_fd = open (destination, O_WRONLY | O_CREAT, stat_buf.st_mode);
 /* Blast the bytes from one file to the other. */
 sendfile (write_fd, read_fd, &offset, stat_buf.st_size);
 /* Close up. */
 close (read_fd);
 close (write_fd);

 return 0;

}

int log_message(std::string message, int level)
{
  //TODO, hardcoded
  std::string path = "logs/";
  std::string security_check = "mkdir " + path;
  int ret = 0;
  std::string file_name = path +  getCurrentDate().substr(0,10) + ".log";  
  std::ofstream my_file;

  system(security_check.c_str());
  my_file.open (file_name,std::ios::app);

  if(my_file.is_open())
    {
      my_file << getCurrentDate().substr(11) << " - " <<std::to_string(level) << ": "<< message << "\n";
      ret = 0;
    }
  else
    ret = 1;

  my_file.close();

  return ret;
}
