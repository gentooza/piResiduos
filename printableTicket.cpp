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
@file printableTicket.cpp
*/
#include "printableTicket.h"

printableTicket::printableTicket() 
{
    // temporary name
    // from base class
    fileName = "ticket.pdf";
    // fonts sizes
    fontSize = 10;
    fontSize_sm = 8;
    fontSize_xl = 12;
    // pdf entity creation
    // from base class
    hpdfDoc = HPDF_New (error_handler, NULL);
    if (!hpdfDoc) 
    {
        printf ("error: cannot create PdfDoc object\n");
        return -1;
    }
    if (setjmp(env)) 
    {
        HPDF_Free (hpdfDoc);
        return -1;
    }
    /* set compression mode */
    HPDF_SetCompressionMode (hpdfDoc, HPDF_COMP_ALL);
    HPDF_UseUTFEncodings(hpdfDoc); 

    /* create default-font */
    hpdfFont = HPDF_GetFont (hpdfDoc, HPDF_LoadTTFontFromFile (hpdfDoc, "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf", HPDF_TRUE),"UTF-8");
    /* add pages objects */
    hpdfPage = HPDF_AddPage (hpdfDoc);
    HPDF_Page_SetWidth (hpdfPage, 200);
    // initial line and ticket height
    currentLine = 0;
    HPDF_Page_SetHeight (hpdfPage, 900);
    // default font size
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fsize);  
    // ticket cups printing options
    // printOpts from base class
    int num_options = 0;
    num_options = cupsAddOption("media", "custom.200x1100", num_options, &printOpts);

    return;
}

printableTicket::~printableTicket() 
{
    HPDF_Free (hpdfDoc);
}

int printableTicket::compose()
{
    int ret = 0;
    //ticket header
    if (composeHeader())
        ret = -1;
    // station title and NIMA
    if (composeStationTitle())
        ret = -1;
    // registration data
    if (composeRegistration())
        ret = -1;
    // origin
    if (composeOrigin())
        ret = -1;
    // transport
    if (composeTransport())
        ret = -1;
    // product
    if (composeProduct())
        ret = -1;
    // weight
    if (composeWeight())
        ret = -1;
    // paid?
    if(ticket_payProcedure == 1)
        if (composePrice())
            ret = -1;
    // comment
    if (composeComment())
        ret = -1;
    // staff
    if (composeStaff())
        ret = -1;
    return ret;
}
/*! function helper for writting the ticket header */
void printableTicket::composeHeader()
{
    // TODO: error handling?
    HPDF_Image logoImg = NULL;
    HPDF_Image lineImg = NULL;
    // logo
    logoImg = HPDF_LoadPngImageFromFile (hpdfDoc, "image/logo_bioreciclaje_trans.png");
    if (logoImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, logoImg, 10, line - 55, 180, 53);
    // code
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_sm);
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 57, 140, (currentLine - 57 - 9), ticket_code.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
    {
        std::cout << "TODO: not enough space" << std::endl;
    }
    HPDF_Page_EndText (hpdfPage);

    // cif
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 110, currentLine - 57, 190, (currentLine - 57 - 9), ticket_costumerCIF.c_str(), HPDF_TALIGN_RIGHT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
    {
        std::cout << "TODO: not enough space" << std::endl;
    }
    HPDF_Page_EndText (hpdfPage);

    // horizontal line
    lineImg = HPDF_LoadPngImageFromFile (hpdfDoc, "image/black_square.png");
    if (lineImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, lineImg, 10, (currentLine - 57 - 9 -2), 180, 2);

    //updating line
    currentLine = currentLine - 57 - 9 - 2;

    return;
}
/*! function helper for writting the ticket station name, and it's NIMA, with the second horizontal separation line */
void printableTicket::composeStationTitle()
{
    HPDF_Image lineImg = NULL;

    ticket_stationName = stringToUppercase(ticket_stationName);
    std::string nima_text = "NIMA: " + ticket_stationNIMA;

    // station name
    int Y = 25;
    int finalY = 50;
    if (ticket_stationName.length() > 20)
        Y = 20;
    if (ticket_stationName.length() > 45)
    {
        Y = 10;
        finalY = 65;
    }
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_xl);
    HPDF_Page_SetTextLeading(hpdfPage, fontSize_xl);
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - Y, 190, (currentLine - finalY), ticket_stationName.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
    {
        std::cout << "TODO: not enough space" << std::endl;
    }
    HPDF_Page_EndText (hpdfPage);
    currentLine = currentLine - finalY;

    // NIMA
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);
    HPDF_Page_SetTextLeading(hpdfPage, fontSize);
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 5, 190, (currentLine - 15), nima_text.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
    {
        std::cout << "TODO: not enough space" << std::endl;
    }
    HPDF_Page_EndText (hpdfPage);
    currentLine = currentLine - 15;

    // horizontal line
    lineImg = HPDF_LoadPngImageFromFile (hpdfDoc, "image/black_square.png");
    if (lineImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, lineImg, 10, currentLine - 5, 180, 2);
    currentLine = currentLine - 5;

    return;
}
/*! function helper for writting the ticket first ifnormation, about movement number, date and time */
void inputForm::ticketRegistrationData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  std::string myText;

   // label
  HPDF_Page_SetFontAndSize (myPage, font, fsize_big);
  HPDF_Page_BeginText (myPage);
  if(HPDF_Page_TextRect( myPage, 10, line - 5, 190, (line - 21), "REGISTRO DE ENTRADA", HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);
  line = line - 26;

  // DATA
  HPDF_Page_SetFontAndSize (myPage, font, fsize_small);
  HPDF_Page_BeginText (myPage);
  myText = "Nº MOV:" + retDepMovCode();
  if(HPDF_Page_TextRect( myPage, 10, line - 15, 190, (line - 25), myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);

  HPDF_Page_SetFontAndSize (myPage, font, fsize_small);
  HPDF_Page_BeginText (myPage);
  myText = "FECHA:" + retDepDateTime().substr(0, retDepDateTime().find(' '));
  if(HPDF_Page_TextRect( myPage, 10, line - 5, 190, (line - 15), myText.c_str(), HPDF_TALIGN_RIGHT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);

  HPDF_Page_SetFontAndSize (myPage, font, fsize_small);
  HPDF_Page_BeginText (myPage);
  myText = "HORA SALIDA:" + retDepDateTime().substr(retDepDateTime().find(' '), retDepDateTime().length());
  if(HPDF_Page_TextRect( myPage, 10, line - 25, 190, (line - 35), myText.c_str(), HPDF_TALIGN_RIGHT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);
  line = line -35;

  return;
}

/*! function helper for writting the ticket second information, about origin costumer */
void inputForm::ticketOriginData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  std::string myText;
  std::string costumerName = retDepCosName();
  int finalLine = fsize_big;

  // ORIGEN label
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 0, line - fsize_big - 5);
  HPDF_Page_ShowText (myPage, "ORIGEN: ");
  HPDF_Page_EndText (myPage);

  // costumer name
  HPDF_Page_SetFontAndSize (myPage, font, fsize_big);
  HPDF_Page_SetTextLeading(myPage, fsize_big);
  HPDF_Page_BeginText (myPage);
  myText = "      " + costumerName;
  if(myText.length() > 28) {
    finalLine = 3*fsize_big;
  }
  if(myText.length() > 56) {
    finalLine = 5*fsize_big;
  }
  if(HPDF_Page_TextRect( myPage, 0, line - 7, 190, (line - finalLine), myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);

  line = line - finalLine;
}

/*! function helper for writting the ticket third information, about transportation */
void inputForm::ticketTransportData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  std::string myText;
  std::string transportName = retDepDriName();
  std::string transportPlate = retDepPlate();
  int finalLine = fsize_medium;

  // transportation label
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 0, line - fsize_big - 5);
  HPDF_Page_ShowText (myPage, "TRANSPORTISTA: ");
  HPDF_Page_EndText (myPage);

  // transportation name
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_SetTextLeading(myPage, fsize_medium);
  HPDF_Page_BeginText (myPage);
  myText = "              " + transportName;
  if(myText.length() > 30) {
    finalLine = 3*fsize_medium;
  }
  if(myText.length() > 68) {
    finalLine = 5*fsize_medium;
  }
  if(HPDF_Page_TextRect( myPage, 0, line - 8, 190, (line - finalLine), myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);

  line = line - finalLine;
  finalLine = fsize_medium;

  // PLATE label
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 0, line - fsize_big - 5);
  HPDF_Page_ShowText (myPage, "MATRÍCULA: ");
  HPDF_Page_EndText (myPage);

  // transportation plate
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 60, line - fsize_big - 5);
  HPDF_Page_ShowText (myPage, transportPlate.c_str());
  HPDF_Page_EndText (myPage);

  line = line - finalLine;
}

/*! function helper for writting the ticket forth information, about product */
void inputForm::ticketProductData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  std::string myText;
  std::string ler = std::to_string(retDepProdLER()) + "-";
  std::string product = retDepProdFullName();
  int finalLine = fsize_medium;

  // product label
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 0, line - fsize_big - 7);
  HPDF_Page_ShowText (myPage, "LER-PRODUCTO: ");
  HPDF_Page_EndText (myPage);

  // product ler
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 77, line - fsize_big - 7);
  HPDF_Page_ShowText (myPage, ler.c_str());
  HPDF_Page_EndText (myPage);

  // transportation name
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_SetTextLeading(myPage, fsize_medium);
  HPDF_Page_BeginText (myPage);
  myText = "                    " + product;
  if(myText.length() > 30) {
    finalLine = 3*fsize_medium;
  }
  if(myText.length() > 68) {
    finalLine = 5*fsize_medium;
  }
  if(HPDF_Page_TextRect( myPage, 0, line - 10, 190, (line - 10 - finalLine), myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);

  line = line - finalLine - 5;
}

/*! function helper for writting the ticket fifth information, about weight */
void inputForm::ticketWeightData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  std::string myText;
  int finalLine = fsize_medium + 7;

  // bruto
  HPDF_Page_BeginText (myPage);
  myText = "BRUTO:" + std::to_string(retDepScaleOut());
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 0, line - 7); 
  HPDF_Page_ShowText (myPage, myText.c_str());
  HPDF_Page_EndText (myPage);

  // tara
  HPDF_Page_BeginText (myPage);
  myText = "TARA:" + std::to_string(retDepScaleIn());
  HPDF_Page_MoveTextPos (myPage, 55, line - 7);
  HPDF_Page_ShowText (myPage, myText.c_str());
  HPDF_Page_EndText (myPage);

  ///neto
  HPDF_Page_BeginText (myPage);
  myText = "NETO:" + std::to_string(retDepTotalWeight());
  myText += " Kg"; 
  HPDF_Page_MoveTextPos (myPage, 110, line - 7);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_big);
  HPDF_Page_ShowText (myPage, myText.c_str());
  HPDF_Page_EndText (myPage);

  line = line - finalLine;
}

/*! function helper for writting the ticket sixth information, about payment */
void inputForm::ticketPaidData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  std::string myText;
  int finalLine = fsize_medium + 5;

  // payment label
  HPDF_Page_BeginText (myPage);
  
  double total_price = retDepTotalWeight()*retDepPrice() / 1000.0;
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << total_price;
  myText = "PRECIO:" + stream.str(); + " Euros";
     
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  HPDF_Page_MoveTextPos (myPage, 0, line - 5); 
  HPDF_Page_ShowText (myPage, myText.c_str());
  HPDF_Page_EndText (myPage);

  line = line - finalLine;
}

/*! function helper for writting the ticket seventh information, about operator comment */
void inputForm::ticketCommentData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  std::string myText;
  int finalLine = fsize_medium + 5;
 
  // comment label
  HPDF_Page_BeginText (myPage);
  myText = "OBSERVACIONES: " +  getOutputComment();
  if(myText.length() > 30)
  {
    finalLine = 3*fsize_medium;
  }
  if(myText.length() > 68)
  {
    finalLine = 5*fsize_medium;
  }
  if(HPDF_Page_TextRect( myPage, 0, line, 190, (line - finalLine), myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);
     
  line = line - finalLine;
}

/*! function helper for writting the ticket last information, about staff, and driver signature */
void inputForm::ticketStaffData(HPDF_Doc &myPdf, HPDF_Page &myPage, int &line, HPDF_Font &font, float fsize_big = 12,
  float fsize_medium = 10, float fsize_small = 9)
{
  int refLine = 0;
  int finalLine = 7;
  HPDF_Image lineImg;
  std::string signature;
  std::string myText;

  // horizontal line
  lineImg = HPDF_LoadPngImageFromFile (myPdf, "image/black_square.png");
  HPDF_Page_DrawImage (myPage, lineImg, 10, line -5, 180, 2);
  line = line - finalLine;
  refLine = line;

  // staff code label
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  myText = "COD. BASCULISTA";
  finalLine = 3*fsize_medium;
  if(HPDF_Page_TextRect( myPage, 0, line - 5, 80, (line - finalLine), myText.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);
  line = line - finalLine - 5;
  
  // staff code
  HPDF_Page_BeginText (myPage);
  myText = std::to_string(ret_staff_code());
  finalLine = 3*fsize_medium;
  if(HPDF_Page_TextRect( myPage, 0, line - 10, 80, (line - finalLine), myText.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);     

  line = refLine;
  // separator
  finalLine = 60;
  lineImg = HPDF_LoadPngImageFromFile (myPdf, "image/black_square.png");
  HPDF_Page_DrawImage (myPage, lineImg, 89, line - finalLine - 20, 2, finalLine + 10);

  // signature code label
  HPDF_Page_BeginText (myPage);
  HPDF_Page_SetFontAndSize (myPage, font, fsize_medium);
  myText = "FIRMA TRANSPORTISTA";
  finalLine = 3*fsize_medium;
  if(HPDF_Page_TextRect( myPage, 100, line - 5, 190, (line - finalLine), myText.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
  {
    std::cout << "TODO: not enough space" << std::endl;
  }
  HPDF_Page_EndText (myPage);
  line = line - finalLine - 5;
  
  // Signature
  signature = retDepDiFolder() + "/firma.png";
  HPDF_Page_DrawImage (myPage, HPDF_LoadPngImageFromFile (myPdf, signature.c_str()), 100, line - 60, 90, 60);
}

/*! function helper for calculating ticket height */
void inputForm::calculateTicketHeight(int &line)
{
  std::string textToCompare;
  // minimal height
  line = 900;
  // station name length
  station * localDestination;
  retDepDestinationStation(localDestination);
  if(localDestination->getName().length() > 20) {
    line += 15;
  }
  // origin costumer name length
  textToCompare = "ORIGEN: " + retDepCosName();
  if(textToCompare.length() >  26) {
    line += 15;
  }
  if(textToCompare.length() > 52) {
    line += 15;
  }
  // transportation name length
  textToCompare = "TRANSPORTISTA: " + retDepDriName();
  if(textToCompare.length() >  30) {
    line += 15;
  }
  if(textToCompare.length() > 60) {
    line += 15;
  }

  delete localDestination;
}