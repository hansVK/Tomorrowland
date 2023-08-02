// Created by r0834721 on 31/7/2023


#ifndef TOMORROWLAND_PARK_H
#define TOMORROWLAND_PARK_H

#include "../Recensie/Recensie.h"

#include "../Abonnee/Abonnee.h"
#include "../Aanvraag/Aanvraag.h"
#include "../OccupyPark/OccupyPark.h"

#include "../Datum/Datum.h"

#include <iostream>

#include <vector>

class Abonnee;

class Recensie;

class Datum;

class Aanvraag;

class OccupyPark;

class Park {
private:

    std::wstring parkID;
    std::wstring locatie;
    std::wstring parkDescription;
    std::wstring parkStatus;

    Abonnee *beheerder;


    bool isToegevoegd;
    Datum *beginDatum;
    Datum *eindDatum;
    double consumingPointsPerDay;
    double minRating;
    double parkScores;

    std::vector<Recensie *> lijstParkRecensie;

    std::vector<Aanvraag *> lijstParkAanvraag;

    std::vector<OccupyPark*> lijstOccupyPark;

    std::vector<OccupyPark *> unratedTenant;


public:

    Park(std::wstring parkID, std::wstring locatie, std::wstring parkDescription);


    double getRatingScore();

    void aanvraagToevoegenToParkAanvraagLijst(Aanvraag *aanvraag);

    bool removeAanvraagVanParkAanvraagLijst(Aanvraag *aanvraag);


    void recensieToevoegenToParkRecensielijst(Recensie *recensie);


    void zieParkInfo();


    void zieParkRecensie();

    ~Park();

    friend class Abonnee;

    friend class OnderliggendeBSysteem;

};


#endif //TOMORROWLAND_PARK_H
