//
// Created by r0834721 on 31/7/2023
//

#include "Recensie.h"
Recensie::Recensie(double ratingScore, std::wstring comment, Abonnee *abonneeRecensie)
        : ratingScore(ratingScore),
          comment(comment),
          abonneeRecensie(abonneeRecensie)
{
}
