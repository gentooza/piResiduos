/*
This file is part of PiResiduos.

Copyright 2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>

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
@file printableTicket.h
*/

#ifndef _PRINTABLE_TICKET_
#define _PRINTABLE_TICKET_

#include "printable.h"

class printableTicket: public printable
{
    printableTicket();
    ~printableTicket();

    int compose();

    int composeHeader();
    int composeStationTitle();
    int composeRegistration();
    int composeOrigin();
    int composeTransport();
    int composeProduct();
    int composeWeight();
    int composePrice();
    int composeComment();
    int composeStaff();

    void setPayProcedure(int payProcedure) { ticket_payProcedure = payProcedure; };
    void setTicketCode(std::string code) { ticket_code = code; };
    void setCostumerCIF(std::string CIF) { ticket_costumerCIF = CIF; };
    void setStationName(std::string stationName) { ticket_stationName = stationName; };
    void setStationNIMA(std::string stationNIMA) { ticket_stationNIMA = stationNIMA; };



    private:
    HPDF_Font hpdfFont;
    HPDF_Page hpdfPage;
    float fontSize;
    float fontSize_sm;
    float fontSize_xl;
    int currentLine;

    int ticket_payProcedure;
    std::string ticket_code;
    std::string ticket_costumerCIF;
    std::string ticket_stationName;
    std::string ticket_stationNIMA;
};



#endif
