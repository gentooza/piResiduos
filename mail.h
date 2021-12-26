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
@file mail.h
''' class for sending incidents via mail, we are based in QT and SmtpClient-for-Qt: https://github.com/bluetiger9/SmtpClient-for-Qt'''
*/

#ifndef _MAIL_
#define _MAIL_

//QT
#include <QString>
#include <QApplication>

#include <iostream>
#include <string>
#include "SmtpClient-for-Qt/src/SmtpMime"
#include "formulario.h"
#include "station.h"


class myMail
{
 public:
  myMail();
  ~myMail(){};

  void setSmtpServer(std::string data){smtpServer = data;};
  void setSmtpPort(int data){smtpPort = data;};
  void setSmtpEncryption(int data){smtpEncryption = data;};
  void setMailUser(std::string data){mailUser = data;};
  void setMailPass(std::string data){mailPass = data;};
  void setMailSenderName(std::string data){mailSenderName = data;};
  void setMailRecipients(std::vector <std::string> data){mailRecipients = data;};

  int sendIncidentsMail(station *& myStation, baseForm *& myForm);
  int buildMessage( MimeText &text, station *& myStation, baseForm *& myForm);

  //test
  int sendTestMail(std::string name,std::string type);

 private:
  std::string smtpServer;
  std::string mailUser;
  std::string mailPass;
  int smtpPort;
  int smtpEncryption;

  std::vector <std::string> mailRecipients;
  std::string mailSenderName;
  std::string mailSubject;
  std::string mailHeader;
  std::string mailBody;
};

#endif
