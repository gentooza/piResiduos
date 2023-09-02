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
@file camera.cpp
*/
#include "camera.h"
#include <sstream>

//imagina camera
//start = ascii (2)
//delimiter = ascii(31)
//end = ascii(3)
//Data = ascii(4)
//start delimiter length delimiter command delimiter filed1 delimiter ... field delimiter end datalength data

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


/*! constructor, it sets up socket
ip: string to camera IP (i.e: 217.160.132.75)
port: port to connect
*/
camera::camera(std::string ip, int port)
{
  std::cout << "DEBUG:camera::camera"<< std::endl;
  s= NULL;
  referenceT = NULL;
  s = new rlSocket(ip.c_str(),port, 1);
  capturing = 0;

  camIp = ip;
  camPort = port;
}

/*! destructor, it deletes socket
*/
camera::~camera()
{
  std::cout << "DEBUG:camera::~camera"<< std::endl;
  delete s;
  if(referenceT != NULL)
    delete referenceT;
}

/*! it connects socket
*/
int camera::connect()
{
  int ret =-1;
  std::cout << "DEBUG:camera::connect"<< std::endl;
  if(s == NULL)
     s = new rlSocket(camIp.c_str(),camPort, 1);
  if(!s->isConnected() && s != NULL)
    {
      ret = s->connect();
    }
  return ret;
}

/*! it disconnects socket
*/
int camera::disconnect()
{
  int ret = 0;
  std::cout << "DEBUG:camera::disconnect" << std::endl;
  if( s != NULL)
    {
      ret = s->disconnect();
      delete s;
    }
  s = NULL;
  return ret;
}

/*! sets reference time*/
int camera::setRefTime(int ms)
{
  std::cout << "DEBUG:camera::setRefTime" << std::endl;
  int seconds = 0, milliseconds;
  
  if (ms < 0)
    ms = 200;
  if (ms > 59999)
    ms = 59999;

  if (ms >= 1000)
  {
    seconds = ms/1000;
  }
  camMs = ms;
  milliseconds = ms - seconds*1000;
  if(referenceT != NULL)
    delete referenceT;
  
  referenceT = new rlTime(0,0,0,0,0,seconds,milliseconds);

  return 0;
}

/*! check camera status*/
int camera::checkStatus()
{
  //std::cout << "DEBUG:camera::checkStatus" << std::endl;
  std::string command;
  std::string message;
  std::string data;
  int ret = -1;

  //start timing
  startT.getLocalTime();
  ret = prepareCommand(STATUS,command);
  if(ret)
    std::cout << "ERROR: command STATUS not found!" << std::endl;
  else
    {
      std::cout << "DEBUG:camera::checkStatus sending command: "<< translate(command) << std::endl;
      ret = sendCommand(command);
      if(!ret)
	{
	  ret = getReponse(message,data);
	  //std::cout <<"DEBUG: reponse: "<< message << std::endl;
	  //std::cout <<"DEBUG: data: "<< data << std::endl;	  
	}
      else
	std::cout << "ERROR:camera::checkStatus error sending command: "<< translate(command) << std::endl;
    }
  return ret;
}

/*! check camera status*/
int camera::reset()
{
  std::string command = std::string() + char(2) + char(31) + "000015" + char(31) + "PR" + char(31)
    + '1' + char(31) + char(3) + '0' + char(4);
  std::string message;
  std::string data;
  int ret = -1;

  rlTime actual;
  rlTime refT;
  
  refT.millisecond = camMs;
  actual.getLocalTime();

  refT += *referenceT;
  while(actual < refT)
    {
      actual.getLocalTime();
    }
  
  if(s->isConnected())
    {
      std::cout <<"DEBUG: sending command:  " << command << std::endl;
      if(s->write(command.c_str(),command.size()) >= 0)
        readReponse(message,data,1000);
      ret = 0;
      std::cout <<"DEBUG: receiving message: " << message << std::endl;
    }
  referenceT->getLocalTime();
  
  return ret;
}

/*!function for returning a plate from camera, it refreshes the last jpg taken from camera*/
int camera::askForPlate(std::string &plate)
{
  int ret = -1;
  std::string command;
  std::string message;
  std::string data; 

  //start timing
  startT.getLocalTime();
  ret = prepareCommand(TAKEPLATE,command);
  if(ret)
    std::cout << "ERROR: command TAKEPLATE not found!" << std::endl;
  else
    {
      std::cout << "DEBUG:camera::askForPLate sending command: "<< translate(command) << std::endl;
      ret = sendCommand(command);
      //std::cout << "DEBUG:camera::askForPLate command sent" << std::endl;     
      if(!ret)
	{
	  //std::cout << "DEBUG:camera::askForPLate awaiting reponse"<< std::endl;
	  ret = getReponse(message,data);
	  if(!ret)
	    {
	      std::cout <<"DEBUG: receiving message: " << translate(message) << std::endl;
	      lastJpg = data;
	      if(message.size() > 23)
		{
		  plate.clear();
		  plate = message.substr(21);
		  size_t delimiter_pos =  plate.find_first_of(ASCII_DELIMITER);
		  if(delimiter_pos>0)		   
		      plate = plate.substr(0,delimiter_pos);
		}
	    }
	}
      else
	std::cout << "ERROR:camera::checkStatus error sending command: "<< translate(command) << std::endl;
    }
  return ret;

}


/*!function for returning a plate from camera, it refreshes the last jpg taken from camera*/
int camera::askPlate()
{
  int ret = -1;
  std::string command = std::string() + char(2) + char(31) + "000020" + char(31) + "PM" + char(31)
    + '1' + char(31) + "1000" + char(31) +  char(3) + '0' + char(4);
  //blocking timing check
  rlTime actual;
  rlTime refT;
  
  refT.millisecond = camMs;
  actual.getLocalTime();

  refT += *referenceT;
  while(actual < refT)
    {
      actual.getLocalTime();
    }
  //////
  if(s->isConnected())
    {
      std::cout <<"DEBUG: sending command:  " << command << std::endl;
      if(s->write(command.c_str(),command.size()) >= 0)
	ret = 0;
    }
  if(!ret)
    capturing = 1;
  return ret;
}
/*!function for returning a plate from camera, it refreshes the last jpg taken from camera*/
int camera::takePlate(std::string& plate, int timeout)
{
  std::string message;
  std::string data;
  char buffer[20];
  int ret = -1;
  //blocking timing check
  rlTime actual;
  rlTime refT;
  rlTime* funTimeout;
  int errorTimeout = 0;

  //toTime(funTimeout,timeout);
  
  refT.millisecond = camMs;
  actual.getLocalTime();

  refT += *referenceT;
  while(actual < refT)
    {
      actual.getLocalTime();
    }
  //////
  if(s->isConnected())
    {
      
      while(readReponse(message,data,500) >= 0 || !errorTimeout)
	{
	  if(readReponse(message,data,500) >= 0)
	    {
	      ret = 0;
	      std::cout <<"DEBUG: receiving message: " << translate(message) << std::endl;
	      lastJpg = data;
	      std::cout << "DEBUG: message size = " << message.size() << std::endl;
	      if(message.size() > 23)
		{
		  message.copy(buffer,7,21);
		  plate.clear();
		  plate += buffer;
		}
	    }
	  /*
	   actual.getLocalTime();
	   if((actual - refT) >= *funTimeout)
	     errorTimeout = 1;
	  */
	}
      
      if(errorTimeout)
	std::cout << "DEBUG: readReponse timeout!" << std::endl;
    }
  else
    std::cout << "DEBUG: socket no connected" << std::endl;
  referenceT->getLocalTime();
  
  return ret;
  
}
/*!it simply returns lastJpg stored*/
int camera::takeImage(std::string& image, const char * imageFile)
{
  int ret = -1;
  std::ofstream outfile (imageFile,std::ofstream::binary);
  if(!lastJpg.empty())
    {
      image = lastJpg;
      outfile.write (image.c_str(),image.size());
      ret = 0;
    }
  outfile.close();
  return ret;
}

/*function for reading camera reponse */
int camera::sendCommand(std::string message)
{
  int ret = -1;
  if(s->isConnected())
    {
      //std::cout <<"DEBUG: sending command:  " << message << std::endl;
      if(s->write(message.c_str(),message.size()) >= 0)
	ret = 0;
      else
	std::cout <<"ERROR:socket write returns:  " << ret << std::endl;
    }

  return ret;
}

/*function for reading camera reponse */
int camera::getReponse(std::string& message,std::string& data)
{
  int ret = -1;
  char character[1];
  std::string buffer;
  std::string sdataLength;
  int length;
  char* c_data;
  int errors = 0;
  int message_closed = 0;

  message.clear();
  data.clear();

  ret = getMessageHeader(message);
  if(ret)
    std::cout << "ERROR: not getting a message header from camera, increase timeout?" << std::endl;
  else
    {
      ret =  getMessageBody(message);
      if(ret)
	std::cout << "ERROR: not getting a message body from camera, increase timeout?" << std::endl;
      else
	{
	  ret =  getMessageData(data);
	}
    }

  std::cout << translate(message) << translate(data) << std::endl;
  
  return ret;
}
/*!function for getting a camera telegram header*/
int camera::getMessageHeader(std::string& message)
{
  int ret = -1;
  char character[1];
    
  while(character[0] != ASCII_INICIO && !timeout())  
    {
      if (s->readStr(character,1,100))
	{
	  if(character[0] == ASCII_INICIO)
	    {
	      if(s->readStr(character,1,100))
		{
		  if (character[0] == ASCII_DELIMITER)
		    {
		      message += "INICIO,";
		      ret = 0;
		      break;
		    }
		}
	    }
	}
    } 
  return ret;
}

/*!function for getting a camera telegram header*/
int camera::getMessageBody(std::string& message)
{
  int ret = -1;
  int message_closed = 0;
  char character[1];
  
  while(!message_closed && !timeout())
    {
      if (s->readStr(character,1,100))
	{
	  if(character[0] == ASCII_FIN)
	    {
	      if(message.at(message.size()-1) == ASCII_DELIMITER)//closing message
		{
		  message += character[0];
		  message_closed = 1;
		  ret = 0;
		}
	    }
	  else
	    message += character[0];
	}
    }
  return ret;
}

/*!function for getting a camera telegram header*/
int camera::getMessageData(std::string& data)
{
  int ret = -1, length = 0;
  char character[1];
  std::string sdataLength;

  character[0] = '0';
  
  while(int(character[0]) != ASCII_DATO && !timeout())
    {
      if(s->readStr(character,1,100))
	{
	  if(character[0]!= ASCII_DATO)
	    {
	      sdataLength += character[0];
	    }
	  //message += character[0]; //we are not ending the message
	}
    }
  if(!timeout())
    {
      ret = 0;
      try
	{
	  length = std::stoi(sdataLength);
	}
      catch (const std::invalid_argument& e)
	{
	  length = 0;
	}
      if(length>0)
	{
	  ret = -2;
	  for(int i = 0; i < length; i++)
	    {
	      if(s->readStr(character,1,100))
		{
		  std::cout << "READ -> " << character[0] << std::endl;
		  data += character[0];
		  ret = 0;
		}
	      else
		{
		  ret =- 1;
		  i = length;
		}
	    }
	}
    }
  

  return ret;
}

/*function for reading camera reponse */
int camera::readReponse(std::string& message,std::string& data, int timeout)
{
  int ret = -1;
  char character[1];
  std::string buffer;
  std::string sdataLength;
  int length;
  char* c_data;
  int errors = 0;
  int message_closed = 0;

  message.clear();
  data.clear();

  while(character[0] != ASCII_INICIO)  
    {
      std::cout << "primer while, errores: " << errors << std::endl;
      if (errors >= ERROR_CHECK)
	break;
      if (s->readStr(character,1,0))
	{
	  if(character[0] == ASCII_INICIO)
	    {
	      if(s->readStr(character,1,0))
		{
		  if (character[0] == ASCII_DELIMITER)
		    {
		      message += "INICIO,";
		      break;
		    }
		  else
		    errors = ERROR_CHECK;
		}
	    }
	}
      else
	errors++;
    } 
  while(!message_closed)
    {
      std::cout << "segundo while, errores: " << errors << std::endl;
      if (errors >= ERROR_CHECK)
	break;
      if (s->readStr(character,1,0))
	{
	  if(character[0] == ASCII_FIN)
	    {
	      if(message.at(message.size()-1) == ASCII_DELIMITER)//closing message
		{
		  message += character[0];
		  message_closed = 1;
		}
	      else
		errors = ERROR_CHECK;
	    }
	  else
	    message += character[0];
	}
      else
	errors++;
    }
  while(int(character[0]) != ASCII_DATO)
    {
      if (errors >= ERROR_CHECK)
	break;
      if(s->readStr(character,1,0))
	{
	  if(character[0]!= ASCII_DATO)
	    {
	      sdataLength += character[0];
	    }
	  message += character[0];
	}
      else
	errors++;
    }
  if(errors < ERROR_CHECK)
    {
      ret = 0;
      try
	{
	  length = std::stoi(sdataLength);
	}
      catch (const std::invalid_argument& e)
	{
	  length = 0;
	}
      if(length>0)
	{
	  ret = -2;
	  for(int i = 0; i < length; i++)
	    {
	      if(s->readStr(character,1,0))
		{
		  std::cout << "READ -> " << character[0] << std::endl;
		  data += character[0];
		  ret = 0;
		}
	      else
		{
		  ret =- 1;
		  i = length;
		}
	    }
	}
    }
  std::cout << translate(message) << translate(data) << std::endl;
  
  return ret;
}

int camera::resetRelaysStatus()
{
  int fails = 0;
  int ret = 0;
  std::string command;

  for(int i = 1; i <= 4; i++)
    {
      ret = prepareRelayCommand(i,0,-1,command);
      if(!ret)
	{
	  ret = sendCommand(command);
	}
      else
	std::cout << "ERROR: CAMERA RELAY " << i << " OFF FAILED" << std::endl; 
      fails += ret;
    }
  return fails;
  
}

int camera::setRelayOn(int relay, int milli)
{
  int ret = -1;
  std::string command;

  if(relay >=1 && relay <= 4)
   {
    ret = prepareRelayCommand(relay,1,milli,command);
    if(!ret)
	  {
	    std::cout << "INFO: set relay command = " << command << std::endl;
	    ret = sendCommand(command);
	  }
    else
	    std::cout << "ERROR: CAMERA RELAY " << relay << " ON FAILED" << std::endl;
  }
  else
      std::cout << "ERROR: relay out of boundaries, relay:" << relay << std::endl;
  return ret;

}
int camera::setRelayOn(int milli)
{
  int ret = -1;
  std::string command;

  if(iRelay >=1 && iRelay <= 4)
    {
      ret = prepareRelayCommand(iRelay,1,milli,command);
      if(!ret)
	{
	  ret = sendCommand(command);
	}
      else
	std::cout << "ERROR: CAMERA RELAY " << iRelay << " ON FAILED" << std::endl;
    }
  else
    std::cout << "ERROR: relay out of boundaries, relay:" << iRelay << std::endl;
  return ret;
}

/*!tool for translating camera messages to human readable format*/
std::string camera::translate(std::string message)
{
  std::string ret;
  
  for(int i = 0; i < message.size(); i++)
    {
      if(message[i] == 2)
	ret += "INICIO";
      else if(message[i] == 31)
	ret += ',';
      else if(message[i] == 3)
	ret += "FIN";
      else if(message[i] == 4)
	ret += "DATO";
      else
	ret += message[i];
    }
  
  return ret;
}

/*! all TCP ip commands defined by Imagina are set here*/
int camera::prepareCommand(int commandId, std::string & command)
{
  int failed = -1;
  
  command.clear();
  switch(commandId)
    {
    case STATUS:
      command += std::string() + char(2) + char(31) + "000015" + char(31) + "PE" + char(31)
    + '1' + char(31) + char(3) + '0' + char(4);
      failed = 0;
      break;

    case RESET:
      command = std::string() + char(2) + char(31) + "000015" + char(31) + "PR" + char(31)
    + '1' + char(31) + char(3) + '0' + char(4);
      failed = 0;
      break;

    case TAKEPLATE:
      command = std::string() + char(2) + char(31) + "000020" + char(31) + "PM" + char(31)
    + '1' + char(31) + "2000" + char(31) +  char(3) + '0' + char(4);
      failed = 0;
      break;
    default:
      failed = 1;
      break;
    };
  
  return failed;
}

/*! all TCP ip commands defined by Imagina for acting on camera relays are set here*/
int camera::prepareRelayCommand(int relayNum, int state, int milli,  std::string & command)
{
  int failed = -1;
  int myState;
  char myRelay[12];
  char myMilli[12];
  std::string length;
  int length_int = 0;

  if(relayNum >=1 || relayNum <=4)
    {
      sprintf(myRelay,"%d",relayNum);
      length = "0000";
      if(milli > 99999)
	milli = 99999;
      if(state == 1 || state == 0)
	{
	  if(state == 0)
	    sprintf(myMilli,"%d",0);
	  else
	    {
	      if(milli < -1)
		sprintf(myMilli,"%d",-1);
	      else if(milli == 0)
		sprintf(myMilli,"%d",0);
	      else
		sprintf(myMilli,"%d",milli);		
	    }
	  length_int = 18; //minimum
	  length_int += strlen(myMilli);
	  length += std::to_string(length_int);
	  command.clear();
	  command += std::string() + char(2) + char(31) + length.c_str() + char(31) + "PO" + char(31)
	    + '1' + char(31) + myRelay + char(31) + myMilli + char(31) + char(3) + '0' + char(4);
	  failed = 0; 
	}
      else
	std::cout << "ERROR: in camera::prepareRelayCommand, undefined state: " << state << std::endl;
    }
  else
    std::cout << "ERROR: in camera::prepareRelayCommand, bad relay number: " << relayNum << std::endl;
  return failed;
}

/*! function for returning true if timeout!*/
int camera::timeout()
{
  rlTime now;
  int ret = 0;

  //std::cout << "in timeout!" << std::endl;
  now.getLocalTime();
  if ((now-startT) >= *referenceT)
    ret = 1;
  //std::cout << "finished timeout! :" << ret << std::endl;
  return ret;
}
