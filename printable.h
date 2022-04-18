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

class printable 
{
    printable();
    ~printable();

    int saveFile();
    int printFile();

    virtual int compose(){return 0;};

    private:
    HPDF_Doc  hpdfDoc;
    HPDF_STATUS hpdfStatus;
    std::string fileName;
    cups_option_t *printOpts;
};



#endif
