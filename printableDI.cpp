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
@file printableDI.cpp
*/
#include "printableDI.h"

printableDI::printableDI() {
    return;
}

printableDI::~printableDI() {
    return;
}

/*! function for start a ticket creation */
void printable::startNewTicket() 
{
  HPDF_Doc  pdf;
  HPDF_Font font;
  HPDF_Page page1;
  HPDF_Image templatePage1;
  char fname[512];
  char signature[512];
  float fsize = 10;
  float fsize_small = 8;
  float fsize_big = 12;
  HPDF_STATUS ret;
  std::string myText;
  int line = 0;

  strcpy (fname, "ticket.pdf");

  pdf = HPDF_New (error_handler, NULL);
  if (!pdf) {
    printf ("error: cannot create PdfDoc object\n");
    return -1;
  }

  if (setjmp(env)) {
    HPDF_Free (pdf);
    return -1;
  }
  /* set compression mode */
  HPDF_SetCompressionMode (pdf, HPDF_COMP_ALL);
  HPDF_UseUTFEncodings(pdf); 

  /* create default-font */
  font = HPDF_GetFont (pdf, HPDF_LoadTTFontFromFile (pdf, "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf", HPDF_TRUE),"UTF-8");
  /* add pages objects */
  page1 = HPDF_AddPage (pdf);
  HPDF_Page_SetWidth (page1, 200);
  // calculation of total height
  calculateTicketHeight(line);
  //std::cout << "DEBUG: lines height = " << line << std::endl;
  HPDF_Page_SetHeight (page1, line);
  // default font size
  HPDF_Page_SetFontAndSize (page1, font, fsize);  

}
/*! function for start a DI creation */
void printable::startNewDI() 
{

}