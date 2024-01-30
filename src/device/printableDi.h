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
@file printableDI.h
*/

#ifndef _PRINTABLE_DI_
#define _PRINTABLE_DI_

#include "printable.h"

class printableDi: public printable
{
    public:
    printableDi(std::string file, std::string ptrId);
    ~printableDi();

    int composeFile();

    int composeHeader();
    int composer4DepCos();

    void setProductLer(std::string productLer){di_productLer = productLer;};
    void setProductDanger(std::string productDanger){di_productDanger = productDanger;};
    void setDiCode(std::string diCode){di_code = diCode;};
    void setDiNpt(std::string diNpt){di_npt = diNpt;};
    void setDiDateTime(std::string diDateTime){di_dateTime = diDateTime;};

    void setDepCosType(int depCosType){di_4CosType = depCosType;};
    void setDepCosName(std::string depCosName){di_4CosName = depCosName;};
    void setDepCosNif(std::string data){ di_4CosNif = data; };
    void setDepCosZip(std::string data){ di_4CosZip = data; };
    void setDepCosRegion(std::string data){ di_4CosRegion = data; };
    void setDepCosAddr(std::string data){ di_4CosAddr = data; };
    void setDepCosCity(std::string data){ di_4CosCity = data; };
    void setDepCosNima(std::string data){ di_4CosNima = data; };
    void setDepCosPhone(std::string data){ di_4CosPhone = data; };
    void setDepCosProvence(std::string data){ di_4CosProvence = data; };
    void setDepCosNumIns(std::string data){ di_4CosNumIns = data; };
    void setDepCosEmail(std::string data){ di_4CosEmail = data; };

    private:
    HPDF_Font hpdfFont;
    HPDF_Page hpdfPage1;
    HPDF_Page hpdfPage2;
    float fontSize;
    float fontSize_sm;
    float fontSize_xl;
    int currentLine;

    std::string di_productLer;
    std::string di_productDanger;
    std::string di_code;
    std::string di_npt;
    std::string di_dateTime;

    int di_4CosType;
    std::string di_4CosName;
    std::string di_4CosNif;
    std::string di_4CosZip;
    std::string di_4CosRegion;
    std::string di_4CosAddr;
    std::string di_4CosCity;
    std::string di_4CosNima;
    std::string di_4CosPhone;
    std::string di_4CosProvence;
    std::string di_4CosNumIns;
    std::string di_4CosEmail;
};



#endif
