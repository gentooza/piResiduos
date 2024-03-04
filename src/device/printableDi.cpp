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
    // pointers
    di_4Cos = new costumer();
    di_5Station = new station();
    di_5Cos = new costumer();
    di_6Station = new station();
    di_6Cos = new costumer();
    di_8Driver = new driver();
    return;
}

printableDi::~printableDi() 
{
    // std::cout << "printableDi::~printableDi()" << std::endl;
    HPDF_Free (hpdfDoc);
    // pointers
    if (di_4Cos)
        delete di_4Cos;
    if (di_5Station)
        delete di_5Station;
    if (di_5Cos)
        delete di_5Cos;
    if (di_6Station)
        delete di_6Station;
    if (di_6Cos)
        delete di_6Cos;
    if (di_8Driver)
        delete di_8Driver;
    return;
}

int printableDi::composeFile()
{
    // std::cout << "printableDi::composeFile()" << std::endl;
    int ret = 0;
    //Header
    if (composeHeader())
        ret = -1;
    // Paragraph 4
    if (compose4DepCos())
        ret = -1;
    // Paragraphs 5
    if (compose5Origin())
        ret = -1;
    // etc
    if (compose6Destination())
        ret = -1;
    if (compose7Product())
        ret = -1;
    if (compose8Driver())
        ret = -1;
    if (compose9Plates())
        ret = -1;
    if (compose10Misc())
        ret = -1;
    if (composeSignature())
        ret = -1;
    if (composeOperatorComment())
        ret = -1;
    if (composeWeights())
        ret = -1;
    if (composeStaff())
        ret = -1;

    return ret;
}

int printableDi::composeHeader()
{
    //LER
    _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_productLer, 480, 1034);
    //DANGER
    HPDF_Page_BeginText (hpdfPage1);
    if(di_productDanger.empty() || !di_productDanger.compare(""))   
        HPDF_Page_MoveTextPos (hpdfPage1, 672, 1034);    
    else
        HPDF_Page_MoveTextPos (hpdfPage1, 562, 1034);
    HPDF_Page_ShowText (hpdfPage1, "X");
    HPDF_Page_EndText (hpdfPage1);
    //DI CODE
    _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_code, 558, 1015);
    //NPT
    _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_npt, 558, 995);
    //DATE TIME
    _HaruText(hpdfPage1, fontSize, 47, hpdfFont, removeTime(di_dateTime), 558, 975);

    return 0;
}
int printableDi::compose4DepCos()
{
    int ret = 0;
    if(di_4Cos)
    {
        std::string myText = "X";
        
        HPDF_Page_BeginText (hpdfPage1);
        if(di_4Cos->getType() == 1)
        {
            HPDF_Page_MoveTextPos (hpdfPage1, 183, 925);
        }
        else if(di_4Cos->getType() == 2)
        {
            HPDF_Page_MoveTextPos (hpdfPage1, 290, 913);
        }
        else if(di_4Cos->getType() == 3)
        {
            HPDF_Page_MoveTextPos (hpdfPage1, 509, 925);;
        }	  
        else if(di_4Cos->getType() == 4)
        {
            HPDF_Page_MoveTextPos (hpdfPage1, 183, 880);	
        }	  
        else if(di_4Cos->getType() == 5)
        {
            HPDF_Page_MoveTextPos (hpdfPage1, 290, 880);
        }
        else if(di_4Cos->getType() == 6)
        {
            HPDF_Page_MoveTextPos (hpdfPage1, 509, 880);
        }
        else { // if type 1 or no type present (by default)
            HPDF_Page_MoveTextPos (hpdfPage1, 183, 925);
        }	 
        HPDF_Page_ShowText (hpdfPage1, myText.c_str());
        HPDF_Page_EndText (hpdfPage1);
        // NAME
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getName(), 188, 841);
        //NIF
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getNif(), 648, 841);
        // ZIP
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, std::to_string(di_4Cos->getZip()), 648, 816);
        //COMUNIDAD AUTONOMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getRegion(), 648, 792);
        //DIRECCION
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getAddress(), 188, 816);
        //MUNICIPIO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getCity(), 188, 792);
        //NIMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getNima(), 188, 764);
        //TELEFONO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getPhone(), 188, 737);
        //PROVINCIA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getProvence(), 465, 792);
        //Nº INSC REGISTRO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getNumIns(), 465, 764);
        //EMAIL
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_4Cos->getMail(), 465, 737);
    }
    else
        ret = 1;
    return ret;
}

int printableDi::compose5Origin()
{
    int ret = 0;
    if(di_5Station)
    {        
        // NAME
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getName(), 188, 638);
        // DIRECCION
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getAddress(), 188, 614);
        // MUNICIPIO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getCity(), 188, 589);
        // NIMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getNima(), 188, 562);
        // PROVINCIA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getProvence(), 465, 589);
        // Nº INSC REGISTRO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getNumIns(), 465, 562);
        // NIF
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getNif(), 648, 638);
        // CP
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, std::to_string(di_5Station->getZip()), 648, 614);
        // COMUNIDAD AUTONOMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Station->getRegion(), 648, 589);
        // CNAE
        // nothing!
    }
    else
        ret = 1;
    
    if(di_5Cos)
    {  
        // NAME
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getName(), 188, 512);
        // DIRECCION
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getAddress(), 188, 487);
        // MUNICIPIO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getCity(), 188, 462);
        // NIMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getNima(), 188, 437);
        // TELEFON0
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getPhone(), 188, 411);
        // PROVINCIA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getProvence(), 465, 462);
        // Nº INSC REGISTRO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getNumIns(), 465, 437);
        // EMAIL
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getMail(), 465, 411);
        // NIF
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getNif(), 648, 512);
        // ZIP
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, std::to_string(di_5Cos->getZip()), 648, 487);        
        // COMUNIDAD AUTONOMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_5Cos->getRegion(), 648, 462);
    }
    else
        ret = 1;

    return  ret;
}

int printableDi::compose6Destination()
{
    int ret = 0;
    if(di_6Station)
    {
        // NAME
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getName(), 188, 315);
        // DIRECCION
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getAddress(), 188, 290);
        // MUNICIPIO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getCity(), 188, 265);
        // NIMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getNima(), 188, 240);
        // PROVINCIA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getProvence(), 465, 265);       
        // Nº INSC REGISTRO
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getNumIns(), 465, 240); 
        // NIF
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getNif(), 648, 315); 
        // ZIP
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, std::to_string(di_6Station->getZip()), 648, 290); 
        //COMUNIDAD AUTONOMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Station->getRegion(), 648, 265);
        // DR
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6DR, 686, 240);
    }
    else
        ret = 1;
    if(di_6Cos)
    {
        // NAME
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getName(), 188, 187);
        // ADDRESS
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getAddress(), 188, 162);
        // CITY
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getCity(), 188, 137);
        // NIMA
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getNima(), 188, 112);
        // PHONE
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getPhone(), 188, 86);
        // PROVINCE
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getProvence(), 465, 137);
        // INSCRIPTION NUMBER
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getNumIns(), 465, 112);
        // EMAIL
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getMail(), 465, 86);
        // NIF
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getNif(), 648, 187);
        // ZIP
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, std::to_string(di_6Cos->getZip()), 648, 162);
        // REGION
        _HaruText(hpdfPage1, fontSize, 47, hpdfFont, di_6Cos->getRegion(), 648, 137);
    }
    else
        ret = 1;

    return ret;
}

int printableDi::compose7Product()
{
    int ret = 0;
    // LER
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_7LER, 140, 1075);
    // NAME
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_7Name, 303, 1075);
    // TOTAL WEIGHT
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_totalWeight, 659, 1075);
    // CHARACTERISTIC DANGER
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_7Danger, 260, 1050);
    return ret;
}

int printableDi::compose8Driver()
{
    int ret = 0;
    if(di_8Driver)
    {
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getName(), 188, 980);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getAddress(), 188, 955);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getCity(), 188, 930);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getNima(), 188, 904);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getPhone(), 188, 877);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getProvence(), 465, 930);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getNumIns(), 465, 904);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getMail(), 465, 877);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getNif(), 648, 980);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, std::to_string(di_8Driver->getZip()), 648, 955);
        _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_8Driver->getRegion(), 648, 930);
    }
    else
        ret = 1;
    return ret;
}

int printableDi::compose9Plates()
{
    int ret = 0;
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_9Plate, 190, 804);
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_9PlateAtt, 468, 804);
    return ret;
}

int printableDi::compose10Misc()
{
    int ret = 0;
    // everything empty but date
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_dateTime, 395, 690);
    return ret;
}

int printableDi::composeSignature()
{
    int ret = 0;
    try
    {
        draw_image (hpdfDoc, di_signaturePath.c_str(), 100, HPDF_Page_GetHeight(hpdfPage2) - 900, "Firma transportista", 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << "no signature png file path provided!" << '\n';
        ret = 1;
    }
    return ret;
}

int printableDi::composeOperatorComment()
{
    int ret = 0;
    HPDF_Page_SetRGBFill(hpdfPage2, 0.85, 0.85, 0.85);
    HPDF_Page_Rectangle(hpdfPage2, 350, 475, 404,20);
    HPDF_Page_FillStroke(hpdfPage2);
    HPDF_Page_SetRGBFill(hpdfPage2, 1, 1, 1);
    HPDF_Page_Rectangle(hpdfPage2, 350, 395, 404,80);
    HPDF_Page_FillStroke(hpdfPage2);
    HPDF_Page_SetRGBFill(hpdfPage2, 0, 0, 0);
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, std::string("COMENTARIO OPERADOR:"), 355, 480);
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_operatorComment, 355, 455);
    return ret;
}

int printableDi::composeWeights()
{
    int ret = 0;    
    HPDF_Page_SetRGBFill(hpdfPage2, 0.85, 0.85, 0.85);
    HPDF_Page_Rectangle(hpdfPage2, 348, 345, 60, 40);
    HPDF_Page_Rectangle(hpdfPage2, 488, 345, 60, 40);
    HPDF_Page_Rectangle(hpdfPage2, 628, 345, 60, 40);
    HPDF_Page_FillStroke(hpdfPage2);
 
    HPDF_Page_SetRGBFill(hpdfPage2, 0, 0, 0);
    HPDF_Page_BeginText (hpdfPage2);
    HPDF_Page_MoveTextPos (hpdfPage2, 360, 360);
    HPDF_Page_ShowText (hpdfPage2, "TARA");
    HPDF_Page_MoveTextPos (hpdfPage2, 136, 0);
    HPDF_Page_ShowText (hpdfPage2, "BRUTO");
    HPDF_Page_MoveTextPos (hpdfPage2, 140, 0);
    HPDF_Page_ShowText (hpdfPage2, "NETO"); 
    HPDF_Page_EndText (hpdfPage2);

    HPDF_Page_SetRGBFill(hpdfPage2, 1, 1, 1);
    HPDF_Page_Rectangle(hpdfPage2, 408, 345, 70, 40);
    HPDF_Page_Rectangle(hpdfPage2, 548, 345, 70, 40);
    HPDF_Page_Rectangle(hpdfPage2, 688, 345, 70, 40);
    HPDF_Page_FillStroke(hpdfPage2);
    HPDF_Page_SetRGBFill(hpdfPage2, 0, 0, 0);

    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_scaleIn, 412, 360);
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_scaleOut, 551, 360);
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, di_totalWeight, 692, 360);
    return ret;
}

int printableDi::composeStaff()
{
    int ret = 0;    
    HPDF_Page_SetRGBFill(hpdfPage2, 0.85, 0.85, 0.85);
    HPDF_Page_Rectangle(hpdfPage2, 350, 315, 235,20);
    HPDF_Page_FillStroke(hpdfPage2);
    HPDF_Page_SetRGBFill(hpdfPage2, 1, 1, 1);
    HPDF_Page_Rectangle(hpdfPage2, 350, 235, 235,80);
    HPDF_Page_FillStroke(hpdfPage2);
    HPDF_Page_SetRGBFill(hpdfPage2, 0, 0, 0);
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, "BASCULISTA:", 355, 320);
    _HaruText(hpdfPage2, fontSize, 47, hpdfFont, "CÓDIGO: " + di_staffCode, 365, 275);
    try 
    {
        draw_image (hpdfDoc, "image/sellotrans.png", 420, 205,"",0);
    } 
    catch(const std::exception& e)
    {
        std::cerr << "no staff stamp png file path provided!" << '\n';
        ret = 1;
    }
    return ret;
}