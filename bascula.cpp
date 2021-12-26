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
@file bascula.cpp
''''''
*/
#include "bascula.h"


void read_callback(bool& data_available, boost::asio::deadline_timer& timeout, const boost::system::error_code& error, std::size_t bytes_transferred)
{
  
  if (error || !bytes_transferred)
    {
      // No data was read!
      data_available = false;
      std::cout << error.message() << std::endl;
      return;
    }
  timeout.cancel();  // will cause wait_callback to fire with an error
  data_available = true;
}


void wait_callback(boost::asio::serial_port& ser_port, const boost::system::error_code& error)
{
  if (error)
  {   
    // Data was read and this timeout was canceled
    return;
  }
  std::cout << "cerrando el puerto" << std::endl;
  ser_port.cancel();  // will cause read_callback to fire with an error
}


/*! constructor, it sets up socket
port: example /dev/tty0
baudRate: example 9600
*/

bascula::bascula(std::string port, int baudRate = 9600)
{
  iBauds = baudRate;
  sPort = port;
  if(!baudRateOk(baudRate))
    iBauds = 9600;
  sCommand = "$";
  iParity = 0;
  iFlow = 0;
  iStop = 0;
  return;
}

void bascula::set_parity(int parity)
{
  if(parity < 0)
    parity = 0;
  if (parity > 2)
    parity = 2;
  iParity = parity;

  return;
}
/*!0-> none, 1-> software, 2-> hardware*/
void bascula::set_flowControl(int flow)
{
  if(flow < 0)
    flow = 0;
  if (flow > 2)
    flow = 2;
  iFlow = flow;

  return;
}
/*!0-> one, 1-> onepointfive, 2-> two*/
void bascula::set_stopBits(int stop)
{
  if(stop < 0)
    stop = 0;
  if (stop > 2)
    stop = 2;
  iStop = stop;

  return;
}

/*! lectura peso
*/
int bascula::readPeso(int mstimeout, char *& readbuffer)
{
  int ret = -1;
  if(mstimeout <200)
    mstimeout = 200;
  bool data_available = false;
  boost::asio::io_service ios;
  boost::asio::serial_port sp(ios, sPort);
  boost::asio::deadline_timer timeout(ios);
  static char tmpbuffer[256];

  
  sp.set_option(boost::asio::serial_port::baud_rate(iBauds));
  
  if(iParity == 1)
    sp.set_option(boost::asio::serial_port::parity(boost::asio::serial_port_base::parity::odd));
  else if(iParity == 2)
    sp.set_option(boost::asio::serial_port::parity(boost::asio::serial_port_base::parity::even));
  else
    sp.set_option(boost::asio::serial_port::parity(boost::asio::serial_port_base::parity::none));
  
  if(iStop == 1)
    sp.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port_base::stop_bits::onepointfive));
  else if(iStop == 2)
    sp.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port_base::stop_bits::two));
  else
    sp.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port_base::stop_bits::one));

  if(iFlow == 1)
    sp.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port_base::flow_control::software));
  else if(iFlow == 2)
    sp.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port_base::flow_control::hardware));
  else
    sp.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port_base::flow_control::none));

  sp.write_some(boost::asio::buffer(sCommand));
  //no bloquea
  /*sp.async_read_some(boost::asio::buffer(tmpbuffer,256),
      boost::bind(&read_callback, boost::ref(data_available), boost::ref(timeout),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
  */
  boost::asio::async_read(sp,boost::asio::buffer(tmpbuffer,256),boost::bind(&read_callback, boost::ref(data_available), boost::ref(timeout),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
  timeout.expires_from_now(boost::posix_time::milliseconds(mstimeout));
  timeout.async_wait(boost::bind(&wait_callback, boost::ref(sp),
                  boost::asio::placeholders::error));
  
//bloquea
  //auto length = sp.read_some(boost::asio::buffer(tmpbuffer),boost::asio::transfer_exactly(10));
  // process the info received
  //ret = atoi(tmpBuffer);
  ios.run();
  if (!data_available)
    {
      std::cout << "ERR: buffer de salida:" << tmpbuffer << std::endl;
      readbuffer = tmpbuffer;
      sp.close();
      return -1;
    }
  std::cout << "buffer de salida:" << tmpbuffer << std::endl;
  readbuffer = tmpbuffer;
  sp.close();
  
  return 0;
}

/*!
*/
int bascula::setBauds(int baudRate)
{
  int ret = -1;
  if(baudRateOk(baudRate))
    {
      iBauds = baudRate;
      ret = 0;
    }
  return ret;
}

/*!
*/
int bascula::setPort(std::string port)
{
  int ret = -1;
  if(!port.empty())
    {
      sPort = port;
      ret = 0;
    }
  return ret;
}


/*!
*/
int baudRateOk(int bauds)
{
  int ret = 0;
  if(bauds == 4800 || bauds == 9600 || bauds == 19200 || bauds == 38400 || bauds ==57600 || bauds == 115200)
    ret = 1;
  return ret;
}
