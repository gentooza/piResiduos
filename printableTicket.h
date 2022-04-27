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
    public:
    printableTicket(std::string file, std::string ptrId);
    ~printableTicket();

    int composeFile();

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
    void setTicketType(std::string type) { ticket_type = type; };
    void setOurCIF(std::string CIF) { ticket_ourCIF = CIF; };
    void setStationName(std::string stationName) { ticket_stationName = stationName; };
    void setStationNIMA(std::string stationNIMA) { ticket_stationNIMA = stationNIMA; };
    void setMovCode(std::string movCode) { ticket_movCode = movCode; };
    void setMovDate(std::string movDate) { ticket_movDate = movDate; };
    void setMovTime(std::string movTime) { ticket_movTime = movTime; };
    void setCostumerName(std::string cosName) { ticket_costumerName = cosName; };
    void setTransportName(std::string trpName) { ticket_transportName = trpName; };
    void setTransportPlate(std::string trpPlate) { ticket_transportPlate = trpPlate; };
    void setProductName(std::string prodName) { ticket_productName = prodName; };
    void setProductLER(std::string prodLER) { ticket_productLER = prodLER; };
    void setGrossWeight(std::string grossWeight) { ticket_grossWeight = grossWeight; };
    void setNetWeight(std::string tareWeight) { ticket_tareWeight = tareWeight; };
    void setTotalWeight(std::string totalWeight) { ticket_totalWeight = totalWeight; };
    void setFinalPrice(std::string finalPrice) { ticket_finalPrice = finalPrice; };
    void setComment(std::string comment) { ticket_comment = comment; };
    void setStaffCode(std::string staffCode) { ticket_staffCode = staffCode; };
    void setSignaturePath(std::string signaturePath) { ticket_signaturePath = signaturePath; };
  
    private:
    HPDF_Font hpdfFont;
    HPDF_Page hpdfPage;
    float fontSize;
    float fontSize_sm;
    float fontSize_xl;
    int currentLine;

    int ticket_payProcedure;
    std::string ticket_code;
    std::string ticket_ourCIF;
    std::string ticket_stationName;
    std::string ticket_stationNIMA;
    std::string ticket_movCode;
    std::string ticket_type;
    std::string ticket_movDate;
    std::string ticket_movTime;
    std::string ticket_costumerName;
    std::string ticket_transportName;
    std::string ticket_transportPlate;
    std::string ticket_productName;
    std::string ticket_productLER;
    std::string ticket_grossWeight;
    std::string ticket_tareWeight;
    std::string ticket_totalWeight;
    std::string ticket_finalPrice;
    std::string ticket_comment;
    std::string ticket_staffCode;
    std::string ticket_signaturePath;
};



#endif