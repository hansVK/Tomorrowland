//
// Created by r0834721 on 31/7/2023
//

#ifndef TOMORROWLAND_ABONNEE_H
#define TOMORROWLAND_ABONNEE_H

#include "../Gebruiker/Gebruiker.h"


#include "../Park/Park.h"
#include "../Aanvraag/Aanvraag.h"



#include "../OccupyPark/OccupyPark.h"
#include "OnderliggendeBSysteem.h"

#include "../Recensie/Recensie.h"

// #include "../../OnderliggendeBSysteem/OnderliggendeBSysteem.h"


#include "../Tenant/Tenant.h"

#include <iostream>
#include <vector>
#include <sstream>

#include<iomanip>

class OccupyPark;

class Tenant;

class OnderliggendeBSysteem;

class Park;

class Recensie;

class Aanvraag;

class Datum;


class Abonnee : public Gebruiker {
private:

    std::wstring abonneeId;
    std::wstring mail;
    Park *parkBeheerder;
    double krediet;
    double score;
    std::wstring locatie;
    std::vector<Recensie *> tenantRecensielijst; //recensie cua beheerder
    std::vector<Aanvraag *> aanvraagLijst; // Aanvraag da sent
    std::vector<Tenant *> tenantLijst; // lijst park ma minh da tWILLEBROEK



public:

    Abonnee(std::wstring gebruikersnaam, std::wstring wachtwoord, std::wstring abonneeID, std::wstring mail,
           double krediet, double score, std::wstring locatie);


    bool parkToevoegen(Datum *beginDatum, Datum *eindDatum, int consumingPointsPerDay, double scores, std::wstring status);


    bool deletePark();

    int toonAanvragen();

    bool cancelAanvraag(int ID);


    void toonAccountInfo();

    double getRatingScore();

    bool minusKrediet(double kredietPoint);

    bool kredietToevoegen(double kredietPoint);

    bool createPark(Park *park);

    void toonAllAvailablePark();

    bool acceptAanvraag(int ID);

    bool declineAanvraag(int ID);


    void recensiePark(Park *occupyPark, int score, std::wstring comment);

    bool toonAanvraagSent();

    void zieTenant();

    bool recensieTenant(int rateId, int score, std::wstring comment);


    bool recensieTonen();

    bool checkout(int leaveId);

    bool zieAbonneeOccupyLijst();

    bool zieUnratedLijst();


    void tenantLeavePark();

    void getParkIndex(int parkID);

    ~Abonnee();

    friend class Park;

    friend class OnderliggendeBSysteem;

};


#endif //TOMORROWLAND_ABONNEE_H
