//
// Created by r0834721 on 31/7/2023
//

#ifndef TOMORROWLAND_BEHEERDER_H
#define TOMORROWLAND_BEHEERDER_H

#endif //TOMORROWLAND_BEHEERDER_H
#include <iostream>
#include "../Gebruiker/Gebruiker.h"


class Beheerder : public Gebruiker {
public:
    Beheerder(std::wstring gebruikersnaam, std::wstring wachtwoord);

    friend class OnderliggendeBSysteem;

    friend class Park;
};