/*
This file is part of PiResiduos.

Copyright 2017-2019, Pro Integra SL
Copyright 2019,2020 Pixelada S. Coop. And <info (at) pixelada (dot) org>

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
@file mail.cpp
''''''
*/
#include "mail.h"

myMail::myMail()
{
  smtpServer.clear();
  mailUser.clear();
  mailPass.clear();
  smtpPort= 0;
  smtpEncryption = 0;

  mailRecipients.clear();
  mailSenderName.clear();
  mailSubject.clear();
  mailHeader.clear();
  mailBody.clear();
}

int myMail::sendIncidentsMail(station *& myStation, baseForm *& myForm)
{
  std::cout << "DEBUG: inside myMail::sendIncidentsMail" << std::endl;
  //if no incidents, return
  if(myForm->getOutputIncidents().empty())
    return 0;				     
  QApplication a();
    
  QString qstr = QString::fromStdString(smtpServer);
  SmtpClient smtp(qstr, smtpPort, SmtpClient::SslConnection);

  //timeouts
  smtp.setResponseTimeout(60000);
  smtp.setSendMessageTimeout(240000);
  //

  // We need to set the username (your email address) and the password
  // for smtp authentification.

  qstr = QString::fromStdString(mailUser);
  smtp.setUser(qstr);
  qstr = QString::fromStdString(mailPass);
  smtp.setPassword(qstr);

  // Now we create a MimeMessage object. This will be the email.

  MimeMessage message;
    
  qstr = QString::fromStdString(mailUser);
  QString qstr2 = QString::fromStdString(mailSenderName);
  std::cout << "message user mail:" << mailUser << " name:"<< mailSenderName << std::endl;
  message.setSender(new EmailAddress(qstr, qstr2));

  std::vector <std::string> ::iterator iter;
  std::cout << "send to: ";
  for(iter = mailRecipients.begin();iter != mailRecipients.end();++iter)
    {
      qstr = QString::fromStdString(*iter);
      std::cout << *iter << " ";
      message.addRecipient(new EmailAddress(qstr, "test recipient"));
    }
  std::cout << std::endl;
    
  //subject and body
  std::string subject = "Incidentes registrados en ";
  subject += myStation->getName();
  message.setSubject(QString::fromStdString(subject));
  MimeText text;
  buildMessage( text, myStation, myForm);

  // Now add it to the mail
  message.addPart(&text);
  
  // Now we can send the mail
  if(smtp.connectToHost())
    std::cout << "connect to host true" << std::endl;
  else
    std::cout << "can't connect to host!!" << std::endl;    
  if(smtp.login())
    std::cout << "login true" << std::endl;
  else
    std::cout << "login failed!! " << mailUser << " : " << mailPass << std::endl;
  if(smtp.sendMail(message))
    std::cout << "message sent true" << std::endl;
  else
    std::cout << "message wasn't sent!!" << std::endl;    
  smtp.quit();

  std::cout << "DEBUG: exiting! myMail::sendIncidentsMail" << std::endl;
  return 0;

}

int myMail::buildMessage( MimeText &text, station *& myStation, baseForm *& myForm)
{

  // Now add some text to the email.
  // First we create a MimeText object.

  std::string mailContent = "Hola!\n\nSe han encontrado las siguientes incidencias al procesar el transporte:\n\n";
 
  std::string station ="ESTACION:\n";
  station +="  ";
  station += myStation->getName();
  std::string sType;
  myStation->getType(sType);
  station +=" , DE TIPO ";
  station += sType;
  station += "\n";
  station += "  ";
  station += getCurrentDate();
  station += "\n\n";
  
  std::string costumer ="CLIENTE:\n";
  costumer += "  código: ";
  costumer += std::to_string(myForm->retDepCosCode());
  costumer += "   nombre: ";
  costumer += myForm->retDepCosName();
  costumer += "\n\n";
  
  std::string product ="PRODUCTO:\n";
  product += "  código: ";
  product += std::to_string(myForm->retDepProdCode());
  product += "   ler: ";
  product += std::to_string(myForm->retDepProdLER());
  product += "\n";
  product += "  nombre: ";
  product += myForm->retDepProdName1();
  product += " ";
  product += myForm->retDepProdName2();
  product += " ";
  product += myForm->retDepProdName3();
  product += "\n\n";

  std::string movement = "TIPO DE MOVIMIENTO ";
  int type = myForm->retDepMovType();
  if(type == 1)    
    movement += "DE ENTRADA DE MATERIAL";
  else if(type == 2)
    movement += "DE TRANSFERENCIA DE MATERIAL";
  else if(type == 3)
    movement += "DE SALIDA DE MATERIAL";
  else
    {
      movement += "DESCONOCIDO (";
      movement += std::to_string(type);
      movement += ")";
    }
  movement += "\n\n";

  std::string incidents = "INCIDENCIAS REGISTRADAS:\n";
  std::vector<std::string> myIncidents;
  std::vector<std::string>::iterator iter;
  myIncidents = myForm->getOutputIncidents();
  for(iter = myIncidents.begin(); iter != myIncidents.end(); ++iter)
    {
      incidents += " - ";
      incidents += *iter;
      incidents +="\n";
      //std::cout << "incidents: " << incidents << std::endl;
    }
  incidents +="\n";

  std::string comments = "COMENTARIO DEL OPERADOR:\n";
  comments += myForm->getOutputComment();
  
  mailContent += station + costumer + product + movement + incidents + comments;
  text.setText(QString::fromUtf8(mailContent.c_str()));

  return  0;
}

int myMail::sendTestMail(std::string name,std::string type)
{
  QApplication a();
    // This is a first demo application of the SmtpClient for Qt project

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

    QString qstr = QString::fromStdString(smtpServer);
    SmtpClient smtp(qstr, 465, SmtpClient::SslConnection);

    //timeouts
    smtp.setResponseTimeout(600000);
    smtp.setSendMessageTimeout(2400000);
    //
    // We need to set the username (your email address) and the password
    // for smtp authentification.

    qstr = QString::fromStdString(mailUser);
    smtp.setUser(qstr);
    qstr = QString::fromStdString(mailPass);
    smtp.setPassword(qstr);

    // Now we create a MimeMessage object. This will be the email.

    MimeMessage message;
    
    qstr = QString::fromStdString(mailUser);
    QString qstr2 = QString::fromStdString(mailSenderName);
    std::cout << "message user mail:" << mailUser << " name:"<< mailSenderName << std::endl;
    message.setSender(new EmailAddress(qstr, qstr2));

    std::vector <std::string> ::iterator iter;
        std::cout << "send to: ";
    for(iter = mailRecipients.begin();iter != mailRecipients.end();++iter)
      {
	qstr = QString::fromStdString(*iter);
	std::cout << *iter << " ";
	message.addRecipient(new EmailAddress(qstr, "test recipient"));
      }
    std::cout << std::endl;
    
    std::string strmessage = "Message sent from station ";
    strmessage += name;
    strmessage += " of type ";
    strmessage += type;

    qstr = QString::fromStdString(strmessage);
    message.setSubject(qstr);

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText("Hi,\nThis is a simple email message.\n");

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    if(smtp.connectToHost())
      std::cout << "connect to host true" << std::endl;
    else
      std::cout << "can't connect to host!" << std::endl;
    if(smtp.login())
      std::cout << "login true" << std::endl;
    else
      std::cout << "can't login!" << std::endl;
    if(smtp.sendMail(message))
       std::cout << "message sent true" << std::endl;
    else
      std::cout << "can't send message!" << std::endl;    
    smtp.quit();
    return 0;
}
