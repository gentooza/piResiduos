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
@file printable.cpp
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
#include <cups/cups.h>

#include <setjmp.h>
#include "hpdf.h"


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

enum
{
    DOC_NOT_SET = 0,
    DOC_TICKET,
    DOC_DI,
};

class printable 
{
    printable(int type);
    ~printable();

    void startNewTicket();
    void startNewDI();

    private:
    int docType;
    HPDF_Doc  hpdfDoc;
    HPDF_Font hpdfFont;
    HPDF_Page hpdfPage1;
    HPDF_Page hpdfPage2;
    std::string fileName;
    float fontSize;
    float fontSize_sm;
    float fontSize_xl;
    HPDF_STATUS hpdfStatus;
    int currentLine;
};



#endif
