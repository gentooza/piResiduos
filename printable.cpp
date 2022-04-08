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
#include "printable.h"


#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

void
print_grid  (HPDF_Doc     pdf,
             HPDF_Page    page)
{
    HPDF_REAL height = HPDF_Page_GetHeight (page);
    HPDF_REAL width = HPDF_Page_GetWidth (page);
    HPDF_Font font = HPDF_GetFont (pdf, "Helvetica", NULL);
    HPDF_UINT x, y;

    HPDF_Page_SetFontAndSize (page, font, 5);
    HPDF_Page_SetGrayFill (page, 0.5);
    HPDF_Page_SetGrayStroke (page, 0.8);

    /* Draw horizontal lines */
    y = 0;
    while (y < height) {
        if (y % 10 == 0)
            HPDF_Page_SetLineWidth (page, 0.5);
        else {
            if (HPDF_Page_GetLineWidth (page) != 0.25)
                HPDF_Page_SetLineWidth (page, 0.25);
        }

        HPDF_Page_MoveTo (page, 0, y);
        HPDF_Page_LineTo (page, width, y);
        HPDF_Page_Stroke (page);

        if (y % 10 == 0 && y > 0) {
            HPDF_Page_SetGrayStroke (page, 0.5);

            HPDF_Page_MoveTo (page, 0, y);
            HPDF_Page_LineTo (page, 5, y);
            HPDF_Page_Stroke (page);

            HPDF_Page_SetGrayStroke (page, 0.8);
        }

        y += 5;
    }


    /* Draw virtical lines */
    x = 0;
    while (x < width) {
        if (x % 10 == 0)
            HPDF_Page_SetLineWidth (page, 0.5);
        else {
            if (HPDF_Page_GetLineWidth (page) != 0.25)
                HPDF_Page_SetLineWidth (page, 0.25);
        }

        HPDF_Page_MoveTo (page, x, 0);
        HPDF_Page_LineTo (page, x, height);
        HPDF_Page_Stroke (page);

        if (x % 50 == 0 && x > 0) {
            HPDF_Page_SetGrayStroke (page, 0.5);

            HPDF_Page_MoveTo (page, x, 0);
            HPDF_Page_LineTo (page, x, 5);
            HPDF_Page_Stroke (page);

            HPDF_Page_MoveTo (page, x, height);
            HPDF_Page_LineTo (page, x, height - 5);
            HPDF_Page_Stroke (page);

            HPDF_Page_SetGrayStroke (page, 0.8);
        }

        x += 5;
    }

    /* Draw horizontal text */
    y = 0;
    while (y < height) {
        if (y % 10 == 0 && y > 0) {
            char buf[12];

            HPDF_Page_BeginText (page);
            HPDF_Page_MoveTextPos (page, 5, y - 2);
#ifdef __WIN32__
            _snprintf (buf, 12, "%u", y);
#else
            snprintf (buf, 12, "%u", y);
#endif
            HPDF_Page_ShowText (page, buf);
            HPDF_Page_EndText (page);
        }

        y += 5;
    }


    /* Draw virtical text */
    x = 0;
    while (x < width) {
        if (x % 50 == 0 && x > 0) {
            char buf[12];

            HPDF_Page_BeginText (page);
            HPDF_Page_MoveTextPos (page, x, 5);
#ifdef __WIN32__
            _snprintf (buf, 12, "%u", x);
#else
            snprintf (buf, 12, "%u", x);
#endif
            HPDF_Page_ShowText (page, buf);
            HPDF_Page_EndText (page);

            HPDF_Page_BeginText (page);
            HPDF_Page_MoveTextPos (page, x, height - 10);
            HPDF_Page_ShowText (page, buf);
            HPDF_Page_EndText (page);
        }

        x += 5;
    }

    HPDF_Page_SetGrayFill (page, 0);
    HPDF_Page_SetGrayStroke (page, 0);
}

void
show_stripe_pattern  (HPDF_Page   page,
                      HPDF_REAL   x,
                      HPDF_REAL   y)
{
    HPDF_UINT iy = 0;

    while (iy < 50) {
        HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.5);
        HPDF_Page_SetLineWidth (page, 1);
        HPDF_Page_MoveTo (page, x, y + iy);
        HPDF_Page_LineTo (page, x + HPDF_Page_TextWidth (page, "ABCabc123"),
                    y + iy);
        HPDF_Page_Stroke (page);
        iy += 3;
    }

    HPDF_Page_SetLineWidth (page, 2.5);
}


void
show_description  (HPDF_Page          page,
                   HPDF_REAL          x,
                   HPDF_REAL          y,
                   const char   *text)
{
    float fsize = HPDF_Page_GetCurrentFontSize (page);
    HPDF_Font font = HPDF_Page_GetCurrentFont (page);
    HPDF_RGBColor c = HPDF_Page_GetRGBFill (page);

    HPDF_Page_BeginText (page);
    HPDF_Page_SetRGBFill (page, 0, 0, 0);
    HPDF_Page_SetTextRenderingMode (page, HPDF_FILL);
    HPDF_Page_SetFontAndSize (page, font, 10);
    HPDF_Page_TextOut (page, x, y - 12, text);
    HPDF_Page_EndText (page);

    HPDF_Page_SetFontAndSize (page, font, fsize);
    HPDF_Page_SetRGBFill (page, c.r, c.g, c.b);
}
void
draw_image (HPDF_Doc     pdf,
            const char  *filename,
            float        x,
            float        y,
            const char  *text,int png_jpeg)
{

    HPDF_Page page = HPDF_GetCurrentPage (pdf);
    HPDF_Image image;

    if(!png_jpeg)
      image = HPDF_LoadPngImageFromFile (pdf, filename);
    else
      image = HPDF_LoadJpegImageFromFile (pdf, filename);     
    //dimensiones 200x200 max
    float width = HPDF_Image_GetWidth (image);
    float heigth = HPDF_Image_GetHeight (image);
    if(heigth > width)
      {
	width = width*200.0/heigth;
	heigth = 200.0;
	if(width < 10.0)
	  width = 10.0;
      }
    else if(heigth < width)
      {
	heigth = heigth*200.0/width;
	width = 200.0;
	if(heigth < 10.0)
	  heigth = 10.0;
      }
    else
      {
	heigth=width=200.0;
      }
    
    /* Draw image to the canvas. */
  
    HPDF_Page_DrawImage (page, image, x, y, (int) width,(int)heigth);

    /* Print the text. */
    HPDF_Page_BeginText (page);
    HPDF_Page_SetTextLeading (page, 16);
    HPDF_Page_MoveTextPos (page, x, y);
    //HPDF_Page_ShowTextNextLine (page, filename);
    HPDF_Page_ShowTextNextLine (page, text);
    HPDF_Page_EndText (page);
}

printable::printable(int doc_type) {
    docType = DOC_NOT_SET;
    return;
}

printable::~printable() {
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