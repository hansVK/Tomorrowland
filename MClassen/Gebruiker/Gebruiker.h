//
// Created by r0834721 on 31/7/2023
//

#ifndef TOMORROWLAND_GEBRUIKER_H
#define TOMORROWLAND_GEBRUIKER_H



//#include "../../OnderliggendeBSysteem/OnderliggendeBSysteem.h"


#include <iostream>

class OnderliggendeBSysteem;

class Gebruiker {
protected:
    std::wstring gebruikersnaam;
    std::wstring wachtwoord;

public:
    Gebruiker(std::wstring gebruikersnaam, std::wstring wachtwoord);

    friend class OnderliggendeBSysteem;

};


#endif //TOMORROWLAND_GEBRUIKER_H
