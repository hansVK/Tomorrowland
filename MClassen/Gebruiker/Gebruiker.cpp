//
// Created by r0834721 on 31/7/2023
//

#include "Gebruiker.h"

#include <utility>

Gebruiker::Gebruiker(std::wstring gebruikersnaam, std::wstring wachtwoord)
        : gebruikersnaam(std::move(gebruikersnaam)),
          wachtwoord(std::move(wachtwoord))
{
}


