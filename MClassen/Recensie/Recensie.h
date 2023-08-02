//
// Created by r0834721 on 31/7/2023
//

#ifndef TOMORROWLAND_RECENSIE_H
#define TOMORROWLAND_RECENSIE_H
#include <iostream>
//#include "../Abonnee/Abonnee.h"
//#include "../Park/Park.h"

class Park;
class Abonnee;
class Recensie {
private:
    double ratingScore;
    std::wstring comment;
    Abonnee *abonneeRecensie;
public:
    Recensie(double ratingScore, std::wstring comment, Abonnee *abonneeRecensie);
    friend class Abonnee;
    friend class Park;
    friend class OnderliggendeBSysteem;
};


#endif //TOMORROWLAND_RECENSIE_H
