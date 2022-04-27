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
@file printable.h
*/

#ifndef _PRINTABLE_
#define _PRINTABLE_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cups/cups.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <math.h>
#include <setjmp.h>
#include "hpdf.h"
#include "generic_tools.h"


void
print_grid  (HPDF_Doc     pdf,
             HPDF_Page    page);

static jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data);

void
print_grid  (HPDF_Doc     pdf,
             HPDF_Page    page);

void
show_stripe_pattern  (HPDF_Page   page,
                      HPDF_REAL   x,
                      HPDF_REAL   y);

void
show_description  (HPDF_Page          page,
                   HPDF_REAL          x,
                   HPDF_REAL          y,
                   const char   *text);

void
draw_image (HPDF_Doc     pdf,
            const char  *filename,
            float        x,
            float        y,
            const char  *text,int png_jpeg);

class printable 
{
    public:
    printable();
    ~printable();

    int saveFile();
    int printFile();

    virtual int composeFile(){return 0;};

    virtual int composeHeader(){return 0;};
    virtual int composeStationTitle(){return 0;};
    virtual int composeRegistration(){return 0;};
    virtual int composeOrigin(){return 0;};
    virtual int composeTransport(){return 0;};
    virtual int composeProduct(){return 0;};
    virtual int composeWeight(){return 0;};
    virtual int composePrice(){return 0;};
    virtual int composeComment(){return 0;};
    virtual int composeStaff(){return 0;};

    virtual void setPayProcedure(int payProcedure) { return; };
    virtual void setTicketCode(std::string code) { return; };
    virtual void setTicketType(std::string type) { return; };
    virtual void setOurCIF(std::string CIF) { return; };
    virtual void setStationName(std::string stationName) { return; };
    virtual void setStationNIMA(std::string stationNIMA) { return; };
    virtual void setMovCode(std::string movCode) { return; };
    virtual void setMovDate(std::string movDate) { return; };
    virtual void setMovTime(std::string movTime) { return; };
    virtual void setCostumerName(std::string cosName) { return; };
    virtual void setTransportName(std::string trpName) { return; };
    virtual void setTransportPlate(std::string trpPlate) { return; };
    virtual void setProductName(std::string prodName) { return; };
    virtual void setProductLER(std::string prodLER) { return; };
    virtual void setGrossWeight(std::string grossWeight) { return; };
    virtual void setNetWeight(std::string tareWeight) { return; };
    virtual void setTotalWeight(std::string totalWeight) { return; };
    virtual void setFinalPrice(std::string finalPrice) { return; };
    virtual void setComment(std::string comment) { return; };
    virtual void setStaffCode(std::string staffCode) { return; };
    virtual void setSignaturePath(std::string signaturePath) { return; };

    HPDF_Doc  hpdfDoc;
    HPDF_STATUS hpdfStatus;
    std::string fileName;
    std::string printerId;
    cups_option_t *printOpts;
};



#endif

