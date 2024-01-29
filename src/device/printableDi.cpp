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
#include "printableDi.h"

printableDi::printableDi(std::string file, std::string ptrId) 
{
    // std::cout << "printableDi::printableDi()" << std::endl;
    HPDF_Image templatePage1,templatePage2;
    // for duplicating the pdf creation
    fileName = file + "_";
    printerId = ptrId;
    // fonts sizes
    fontSize = 14;
    fontSize_sm = 12;
    fontSize_xl = 16;
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
    hpdfPage1 = HPDF_AddPage (hpdfDoc);
    HPDF_Page_SetWidth (hpdfPage1, 827);
    HPDF_Page_SetHeight (hpdfPage1, 1169);
    hpdfPage2 = HPDF_AddPage (hpdfDoc);
    HPDF_Page_SetWidth (hpdfPage2, 827);
    HPDF_Page_SetHeight (hpdfPage2, 1169);
 
    templatePage1 = HPDF_LoadPngImageFromFile (hpdfDoc, "image/hoja1.png");
    templatePage2 = HPDF_LoadPngImageFromFile (hpdfDoc, "image/hoja2.png");  
    HPDF_Page_DrawImage (hpdfPage1, templatePage1, 0, 0, 827, 1169);
    HPDF_Page_DrawImage (hpdfPage2, templatePage2, 0, 0, 827, 1169);

    // default font size
    HPDF_Page_SetFontAndSize (hpdfPage1, hpdfFont, fontSize);
    HPDF_Page_SetFontAndSize (hpdfPage2, hpdfFont, fontSize);
    // ticket cups printing options
    // printOpts from base class
    int num_options = 0;
    num_options = cupsAddOption("fit-to-page", "true", num_options, &printOpts);
    return;
}

printableDi::~printableDi() 
{
    // std::cout << "printableDi::~printableDi()" << std::endl;
    HPDF_Free (hpdfDoc);
}

int printableDi::composeFile()
{
    // std::cout << "printableDi::composeFile()" << std::endl;
    int ret = 0;
    //Header
    if (composeHeader())
        ret = -1;

    return ret;
}

int printableDi::composeHeader()
{
    //LER
    HPDF_Page_BeginText (hpdfPage1);
    HPDF_Page_MoveTextPos (hpdfPage1, 480, 1034);
    HPDF_Page_ShowText (hpdfPage1, di_productLer.c_str());
    HPDF_Page_EndText (hpdfPage1);
  
    //DANGER
    HPDF_Page_BeginText (hpdfPage1);
    if(di_productDanger.empty() || !di_productDanger.compare(""))   
        HPDF_Page_MoveTextPos (hpdfPage1, 672, 1034);    
    else
        HPDF_Page_MoveTextPos (hpdfPage1, 562, 1034);
    HPDF_Page_ShowText (hpdfPage1, "X");
    HPDF_Page_EndText (hpdfPage1);

    //DI CODE
    HPDF_Page_BeginText (hpdfPage1);
    HPDF_Page_MoveTextPos (hpdfPage1, 558, 1015);
    HPDF_Page_ShowText (hpdfPage1, di_code.c_str());
    HPDF_Page_EndText (hpdfPage1);

    //NPT
    HPDF_Page_BeginText (hpdfPage1);
    HPDF_Page_MoveTextPos (hpdfPage1, 558, 995);
    HPDF_Page_ShowText (hpdfPage1, di_npt.c_str());
    HPDF_Page_EndText (hpdfPage1);

    //DATE TIME
    _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_dateTime, 558, 975);
    //HPDF_Page_BeginText (hpdfPage1);
    //HPDF_Page_MoveTextPos (hpdfPage1, 558, 975);
    //HPDF_Page_ShowText (hpdfPage1, di_dateTime.c_str());
    //HPDF_Page_EndText (hpdfPage1);

    return 0;
}
int printableDi::composer4DepCos()
{
    std::string myText = "X";
    
    HPDF_Page_BeginText (hpdfPage1);
    if(di_4CosType == 2)
    {
        HPDF_Page_MoveTextPos (hpdfPage1, 290, 913);
    }
    else if(di_4CosType == 3)
    {
        HPDF_Page_MoveTextPos (hpdfPage1, 509, 925);;
    }	  
    else if(di_4CosType == 4)
    {
        HPDF_Page_MoveTextPos (hpdfPage1, 183, 880);	
    }	  
    else if(di_4CosType == 5)
    {
        HPDF_Page_MoveTextPos (hpdfPage1, 290, 880);
    }
    else if(di_4CosType == 6)
    {
        HPDF_Page_MoveTextPos (hpdfPage1, 509, 880);
    }
    else { // if type 1 or no type present (by default)
        HPDF_Page_MoveTextPos (hpdfPage1, 183, 925);
    }	 
    HPDF_Page_ShowText (hpdfPage1, myText.c_str());
    HPDF_Page_EndText (hpdfPage1);
/*
    //NAME
    _HaruText(page1, fsize, 47, font, depCostumer->getName(), 188, 841);
    //NIF
    HPDF_Page_BeginText (page1);     
    HPDF_Page_MoveTextPos (page1, 648, 841);
    HPDF_Page_ShowText (page1, depCostumer->getNif().c_str());
    HPDF_Page_EndText (page1);
    //CP
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 816);
    HPDF_Page_ShowText (page1, std::to_string(depCostumer->getZip()).c_str());
    HPDF_Page_EndText (page1);
    //COMUNIDAD AUTONOMA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 648, 792);
    HPDF_Page_ShowText (page1, depCostumer->getRegion().c_str());
    HPDF_Page_EndText (page1);
    //DIRECCION
    _HaruText(page1, fsize, 47, font, depCostumer->getAddress(), 188, 816);
    //MUNICIPIO
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 792);
    HPDF_Page_ShowText (page1, depCostumer->getCity().c_str());
    HPDF_Page_EndText (page1);
    //NIMA
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 764);
    HPDF_Page_ShowText (page1, depCostumer->getNima().c_str());
    HPDF_Page_EndText (page1);
    //TELEFONO
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 188, 737);
    HPDF_Page_ShowText (page1, depCostumer->getPhone().c_str());
    HPDF_Page_EndText (page1);
    //PROVINCIA
    //TODO: to adjust with new set_di_text function
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 792);
    HPDF_Page_ShowText (page1, depCostumer->getProvence().c_str());
    HPDF_Page_EndText (page1);
    //Nº INSC REGISTRO
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 764);
    HPDF_Page_ShowText (page1, depCostumer->getNumIns().c_str());
    HPDF_Page_EndText (page1);
    //EMAIL
    HPDF_Page_BeginText (page1);
    HPDF_Page_MoveTextPos (page1, 465, 737);
    HPDF_Page_ShowText (page1, depCostumer->getMail().c_str());
    HPDF_Page_EndText (page1);*/
    return 0;
}
