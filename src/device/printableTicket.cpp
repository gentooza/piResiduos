/*
This file is part of PiResiduos.

Copyright 2022, Pixelada S. Coop. And. <info (at) pixelada (dot) org>
Copyright 2023, 2024 Joaquín Cuéllar <joa (dot) cuellar (at) riseup (dot) net>

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

printableTicket::printableTicket(std::string file, std::string ptrId) 
{
    std::cout << "printableTicket::printableTicket()" << std::endl;
    // temporary name
    // from base class
    fileName = file;
    printerId = ptrId;
    // fonts sizes
    fontSize = 10;
    fontSize_sm = 8;
    fontSize_xl = 12;
    // pdf entity creation
    // from base class
    hpdfDoc = HPDF_New (error_handler, NULL);
    if (!hpdfDoc) 
    {
        std::cout << "error: cannot create PdfDoc object" << std::endl;
        return;
    }
    if (setjmp(env)) 
    {
        HPDF_Free (hpdfDoc);
        return;
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
    currentLine = 900;
    HPDF_Page_SetHeight (hpdfPage, 900);
    // default font size
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);  
    // ticket cups printing options
    // printOpts from base class
    int num_options = 0;
    num_options = cupsAddOption("media", "custom.200x1100", num_options, &printOpts);

    return;
}

printableTicket::~printableTicket() 
{
    std::cout << "printableTicket::~printableTicket()" << std::endl;
    HPDF_Free (hpdfDoc);
}

int printableTicket::composeFile()
{
    std::cout << "printableTicket::composeFile()" << std::endl;
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
    {
        if (composePrice())
        ret = -1;
    }
    // comment
    if (composeComment())
        ret = -1;
    // staff
    if (composeStaff())
        ret = -1;
  
    return ret;
}
/*! function helper for writting the ticket header */
int printableTicket::composeHeader()
{
    std::cout << "printableTicket::composeHeader()" << std::endl;
    // TODO: error handling?
    HPDF_Image logoImg = NULL;
    HPDF_Image lineImg = NULL;
    // logo
    logoImg = HPDF_LoadPngImageFromFile (hpdfDoc, "image/logo_costumer_trans.png");
    if (logoImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, logoImg, 10, currentLine - 55, 180, 53);
    // code
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_sm);
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 57, 140, (currentLine - 57 - 9),
                ticket_code.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);

    // cif
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 110, currentLine - 57, 190, (currentLine - 57 - 9),
                ticket_ourCIF.c_str(), HPDF_TALIGN_RIGHT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);

    // horizontal line
    lineImg = HPDF_LoadPngImageFromFile (hpdfDoc, "image/black_square.png");
    if (lineImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, lineImg, 10, (currentLine - 57 - 9 -2), 180, 2);

    //updating line
    currentLine = currentLine - 57 - 9 - 2;

    return 0;
}
/*! function helper for writting the ticket station name, and it's NIMA, with the second horizontal separation line */
int printableTicket::composeStationTitle()
{
    std::cout << "printableTicket::composeStationTitle()" << std::endl;
    HPDF_Image lineImg = NULL;
    std::string stationNameField;

    stationNameField = "Instalación: " + stringToUppercase(ticket_stationName);
    std::string nima_text = "NIMA: " + ticket_stationNIMA;
    // station name
    int Y = 25;
    int finalY = 50;
    if (stationNameField.length() > 20)
        Y = 20;
    if (stationNameField.length() > 45)
    {
        Y = 10;
        finalY = 65;
    }
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_xl);
    HPDF_Page_SetTextLeading(hpdfPage, fontSize_xl);
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - Y, 190, (currentLine - finalY),
                stationNameField.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);
    currentLine = currentLine - finalY;

    // NIMA
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);
    HPDF_Page_SetTextLeading(hpdfPage, fontSize);
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 5, 190, (currentLine - 15),
        nima_text.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);
    currentLine = currentLine - 15;

    // horizontal line
    lineImg = HPDF_LoadPngImageFromFile (hpdfDoc, "image/black_square.png");
    if (lineImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, lineImg, 10, currentLine - 5, 180, 2);
    currentLine = currentLine - 5;

    return 0;
}
/*! function helper for writting the ticket first ifnormation, about movement number, date and time */
int printableTicket::composeRegistration()
{
    std::cout << "printableTicket::composeRegistration()" << std::endl;
    std::string myText;

    // label
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_xl);
    HPDF_Page_BeginText (hpdfPage);
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 5, 190, (currentLine - 21), 
                ticket_type.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space text" << std::endl;
    
    HPDF_Page_EndText (hpdfPage);
    currentLine = currentLine - 26;

    // DATA
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_sm);
    HPDF_Page_BeginText (hpdfPage);
    myText = "Nº MOV:" + ticket_movCode;
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 15, 190, (currentLine - 25), 
                myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);

    HPDF_Page_BeginText (hpdfPage);
    myText = "FECHA:" + ticket_movDate;
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 5, 190, (currentLine - 15),
                myText.c_str(), HPDF_TALIGN_RIGHT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);

    HPDF_Page_BeginText (hpdfPage);
    myText = "HORA SALIDA:" + ticket_movTime;
    if(HPDF_Page_TextRect( hpdfPage, 10, currentLine - 25, 190, (currentLine - 35),
                myText.c_str(), HPDF_TALIGN_RIGHT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);
    currentLine = currentLine - 45;

    return 0;
}

/*! function helper for writting the ticket second information, about origin costumer */
int printableTicket::composeOrigin()
{
    std::cout << "prinrtableTicket::composeOrigin()" << std::endl;
    std::string myText;
    int finalLine = 2*fontSize_xl;

    // costumer name
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_xl);
    HPDF_Page_SetTextLeading(hpdfPage, fontSize_xl);
    HPDF_Page_BeginText (hpdfPage);
    myText = "ORIGEN: " + ticket_costumerName;
    if(myText.length() > 26)
        finalLine += fontSize_xl;
    if(myText.length() > 52)
        finalLine +=  fontSize_xl;
    if(HPDF_Page_TextRect( hpdfPage, 0, currentLine, 190, (currentLine - finalLine),
                myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space for text, costumer name length = " << myText.length() << std::endl;
    currentLine = currentLine - finalLine + fontSize_xl;

    finalLine = 2*fontSize_xl;
    myText = "CIF: " + ticket_costumerNif;
    if(myText.length() > 26)
        finalLine += fontSize_xl;
    if(myText.length() > 52)
        finalLine += fontSize_xl;
    if(HPDF_Page_TextRect( hpdfPage, 0, currentLine, 190, (currentLine - finalLine),
        myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space, costuemr CIF length = " << myText.length() << std::endl;
    HPDF_Page_EndText (hpdfPage);

    currentLine = currentLine - finalLine - fontSize_xl/2;
    return 0;
}

/*! function helper for writting the ticket third information, about transportation */
int printableTicket::composeTransport()
{
    std::cout << "prinrtableTicket::composeTransport()" << std::endl;
    std::string myText;
    int finalLine = 2*fontSize;

    // transportation name
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);
    HPDF_Page_SetTextLeading(hpdfPage, fontSize);
    HPDF_Page_BeginText (hpdfPage);
    myText = "TRANSPORTISTA: " + ticket_transportName;
    if(myText.length() > 28)
        finalLine += fontSize;
    if(myText.length() > 56)
        finalLine += fontSize;
    if(myText.length() > 84)
        finalLine += fontSize;
    if(HPDF_Page_TextRect( hpdfPage, 0, currentLine, 190, (currentLine - finalLine),
                myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    // std::cout << "DEBUG: transport length: " << myText.length() << ", finalLine = " << finalLine << ", fontSize = " << fontSize << std::endl;
    HPDF_Page_EndText (hpdfPage);

    currentLine = currentLine - finalLine;
    finalLine = fontSize;

    // transportation plate
    HPDF_Page_BeginText (hpdfPage);
    myText = "MATRÍCULA: " + ticket_transportPlate;
    HPDF_Page_MoveTextPos (hpdfPage, 0, currentLine);
    HPDF_Page_ShowText (hpdfPage, myText.c_str());
    HPDF_Page_EndText (hpdfPage);

    currentLine = currentLine - finalLine;
    return 0;
}

/*! function helper for writting the ticket forth information, about product */
int printableTicket::composeProduct()
{
    std::cout << "printableTicket::composeProduct()" << std::endl;
    std::string myText;
    int finalLine = 2*fontSize;

    // product LER and NAME
    HPDF_Page_SetTextLeading(hpdfPage, fontSize);
    HPDF_Page_BeginText (hpdfPage);
    myText = "LER-PRODUCTO: " + ticket_productLER + " - " + ticket_productName;
    if(myText.length() > 28)
        finalLine += fontSize;
    if(myText.length() > 56)
        finalLine += fontSize;
    if(myText.length() > 84)
        finalLine += fontSize;
    if(HPDF_Page_TextRect( hpdfPage, 0, currentLine - fontSize, 190, (currentLine - finalLine),
                myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space, text length: " << myText.length() << std::endl;
    HPDF_Page_EndText (hpdfPage);

    currentLine = currentLine - finalLine;

    return 0;
}

/*! function helper for writting the ticket fifth information, about weight */
int printableTicket::composeWeight()
{
    std::cout << "printableTicket::composeWeight()" << std::endl;
    std::string myText;
    int finalLine = fontSize + fontSize_xl + 12;

    // bruto
    HPDF_Page_BeginText (hpdfPage);
    myText = "BRUTO:" + ticket_grossWeight;
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);
    HPDF_Page_MoveTextPos (hpdfPage, 0, currentLine - 7); 
    HPDF_Page_ShowText (hpdfPage, myText.c_str());
    HPDF_Page_EndText (hpdfPage);

    // tara
    HPDF_Page_BeginText (hpdfPage);
    myText = "TARA:" + ticket_tareWeight;
    HPDF_Page_MoveTextPos (hpdfPage, 100, currentLine - 7);
    HPDF_Page_ShowText (hpdfPage, myText.c_str());
    HPDF_Page_EndText (hpdfPage);

    ///neto
    HPDF_Page_BeginText (hpdfPage);
    myText = "NETO:" + ticket_netWeight;
    myText += " Kg"; 
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize_xl);
    HPDF_Page_MoveTextPos (hpdfPage, 0, currentLine - fontSize - 12);
    HPDF_Page_ShowText (hpdfPage, myText.c_str());
    HPDF_Page_EndText (hpdfPage);

    currentLine = currentLine - finalLine;

    return 0;
}

/*! function helper for writting the ticket sixth information, about payment */
int printableTicket::composePrice()
{
    std::cout << "printableTicket::composePrice()" << std::endl;
    std::string myText;
    int finalLine = fontSize + 5;

    // payment label
    HPDF_Page_BeginText (hpdfPage);
    myText = "PRECIO:" + ticket_finalPrice + " Euros";
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);
    HPDF_Page_MoveTextPos (hpdfPage, 0, currentLine - 5); 
    HPDF_Page_ShowText (hpdfPage, myText.c_str());
    HPDF_Page_EndText (hpdfPage);

    currentLine = currentLine - finalLine;

    return 0;
}

/*! function helper for writting the ticket seventh information, about operator comment */
int printableTicket::composeComment()
{
    std::cout << "printableTicket::composeComment()" << std::endl;
    std::string myText;
    int finalLine = fontSize + 5;
 
    // comment label
    HPDF_Page_BeginText (hpdfPage);
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);
    myText = "OBSERVACIONES: " +  ticket_comment;
    if(myText.length() > 30)
        finalLine = 3*fontSize;
    if(myText.length() > 68)
        finalLine = 5*fontSize;
    if(HPDF_Page_TextRect( hpdfPage, 0, currentLine, 190, (currentLine - finalLine),
                myText.c_str(), HPDF_TALIGN_LEFT, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space, text length: " << myText.length() << std::endl;
    HPDF_Page_EndText (hpdfPage);
     
    currentLine = currentLine - finalLine;

    return 0;
}

/*! function helper for writting the ticket last information, about staff, and driver signature */
int printableTicket::composeStaff()
{
    int refLine = 0;
    int finalLine = 7;
    HPDF_Image lineImg = NULL;
    HPDF_Image signatureImg = NULL;
    std::string signature;
    std::string myText;

    // horizontal line
    lineImg = HPDF_LoadPngImageFromFile (hpdfDoc, "image/black_square.png");
    if (lineImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, lineImg, 10, currentLine -5, 180, 2);
    currentLine = currentLine - finalLine;
    refLine = currentLine;

    // staff code label
    HPDF_Page_BeginText (hpdfPage);
    HPDF_Page_SetFontAndSize (hpdfPage, hpdfFont, fontSize);
    myText = "COD. BASCULISTA";
    finalLine = 3*fontSize;
    if(HPDF_Page_TextRect( hpdfPage, 0, currentLine - 5, 80, (currentLine - finalLine),
                myText.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);

    currentLine = currentLine - finalLine - 5;
    // staff code
    HPDF_Page_BeginText (hpdfPage);
    finalLine = 3*fontSize;
    if(HPDF_Page_TextRect( hpdfPage, 0, currentLine - 10, 80, (currentLine - finalLine),
                ticket_staffCode.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
        std::cout << "TODO: not enough space" << std::endl;
    HPDF_Page_EndText (hpdfPage);

    currentLine = refLine;
    // separator
    finalLine = 60;
    //lineImg = HPDF_LoadPngImageFromFile (myPdf, "image/black_square.png");
    if (lineImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, lineImg, 89, currentLine - finalLine - 20, 2, finalLine + 10);

    // signature code label
    HPDF_Page_BeginText (hpdfPage);
    myText = "FIRMA TRANSPORTISTA";
    finalLine = 3*fontSize;
    if(HPDF_Page_TextRect( hpdfPage, 100, currentLine - 5, 190, (currentLine - finalLine), myText.c_str(), HPDF_TALIGN_CENTER, NULL) == HPDF_PAGE_INSUFFICIENT_SPACE) 
    {
        std::cout << "TODO: not enough space" << std::endl;
    }
    HPDF_Page_EndText (hpdfPage);
    currentLine = currentLine - finalLine - 5;
  
    // Signature
    signatureImg = HPDF_LoadPngImageFromFile (hpdfDoc, ticket_signaturePath.c_str());
    if (signatureImg != NULL)
        HPDF_Page_DrawImage (hpdfPage, signatureImg, 100, currentLine - 60, 90, 60);

    return 0;
}