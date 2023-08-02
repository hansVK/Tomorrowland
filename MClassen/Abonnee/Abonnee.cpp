//
// Created by r0834721 on 31/7/2023
//

#include "Abonnee.h"

//#include "../Datum/Datum.h"
//#include "../../OnderliggendeBSysteem/OnderliggendeBSysteem.h"
#include "../../vast.h"
#include "../Park/Park.h"
#include "../Recensie/Recensie.h"
#include "../Aanvraag/Aanvraag.h"
#include "../OccupyPark/OccupyPark.h"
#include "../Tenant/Tenant.h"

#include <algorithm>


#include <utility>

Abonnee::Abonnee(std::wstring gebruikersnaam, std::wstring wachtwoord, std::wstring abonneeID, std::wstring mail,
                 double krediet, double score, std::wstring locatie)
        : Gebruiker(gebruikersnaam,wachtwoord),
          abonneeId(abonneeID),
          mail(mail),
          krediet(krediet),
          score(score),
          locatie(locatie),
          parkBeheerder(nullptr)
{
    tenantRecensielijst.clear();
    aanvraagLijst.clear();
}


double Abonnee::getRatingScore() {
    if (this->tenantRecensielijst.empty()) {
        return 10;
    }
    double tmpScore = 0;
    for (Recensie *rv: tenantRecensielijst) {
        tmpScore += rv->ratingScore;
    }
    double ratingScore = (double) tmpScore / (double) tenantRecensielijst.size();
    return ratingScore;
}


void Abonnee::toonAccountInfo() {
    std::wcout  << L"\nYour information: \n" ;
    std::wcout  << L"Your gebruikersnaam: " << this->gebruikersnaam << L"\n" ;
    std::wcout  << L"Your name: " << this->mail << L"\n" ;
    std::wcout  << L"Your krediet: " << this->krediet << L"\n" ;
    std::wcout  << L"Your locatie: " << this->locatie << L"\n" ;
    std::wcout  << L"Your score: " << this->getRatingScore() << L"\n" ;
    if (parkBeheerder == nullptr) {
        std::wcout << L"\n";
    } else {
        std::wcout  << L"ParkID: " << parkBeheerder->parkID << L"  Locatie: " << parkBeheerder->locatie << L"\n" ;
    }
}

//add krediet to abonnee's krediet
bool Abonnee::kredietToevoegen(double kredietPoint) {
    this->krediet += kredietPoint;
    return true;
}

//minus krediet of abonnee
bool Abonnee::minusKrediet(double kredietPoint) {
    if (this->krediet < kredietPoint) {
        return false;
    }
    this->krediet -= kredietPoint;
    return true;
}

bool Abonnee::recensieTonen() {

    if (this->tenantRecensielijst.empty()) {
        std::wcout  << L"\nThere are no recensies for this abonnee\n";
        return false;
    } else {
        std::wcout  << L"\nAll recensie for this abonnee: \n" ;
        for (int i = 0; i < this->tenantRecensielijst.size(); i++) {
            Recensie *recensie = tenantRecensielijst[i];
            std::wstring tmpComment = recensie->comment;
            int tmpScore = recensie->ratingScore;
            Abonnee *abonnee = recensie->abonneeRecensie;
            std::wcout  << L"\n-----------------------"
                      << L"\n\nRecensie by abonnee: " << abonnee->mail
                      << L"\n-----------------------"
                      << L"Score: " << tmpScore << L"\n"
                      << L"Comment: " << tmpComment ;

        }

    }
    return true;
}

bool Abonnee::createPark(Park *park) {
    if (this->parkBeheerder != nullptr) {
        return false;
    } else {
        this->parkBeheerder = park;
        park->beheerder = this;
        return true;
    }
}


bool Abonnee::parkToevoegen(Datum *beginDatum, Datum *eindDatum, int consumingPointsPerDay, double scores, std::wstring status) {


    if (parkBeheerder->isToegevoegd) {
        return false;
    }

    parkBeheerder->isToegevoegd = true;
    parkBeheerder->beginDatum = beginDatum;
    parkBeheerder->eindDatum = eindDatum;
    parkBeheerder->consumingPointsPerDay = consumingPointsPerDay;
    parkBeheerder->parkStatus = status;
    parkBeheerder->minRating = scores;

    return true;
}

bool Abonnee::deletePark() {

    if (!parkBeheerder->isToegevoegd || !parkBeheerder->lijstParkAanvraag.empty()) {
        return false;
    }

    parkBeheerder->isToegevoegd = false;
    parkBeheerder->parkStatus = STATUS[1];
    parkBeheerder->beginDatum = nullptr;
    parkBeheerder->eindDatum = nullptr;
    parkBeheerder->consumingPointsPerDay = 0;
    parkBeheerder->parkDescription = L"";
    return true;
}


int Abonnee::toonAanvragen() {
    int index = 0;
    if (parkBeheerder->lijstParkAanvraag.empty()) {
        std::wcout  << L"\nNo aanvraag for you\n" ;
        return 0;
    }
    std::wcout
             << std::left
            << std::setw(5)
            << L"ID"
            << std::left
            << std::setw(10)
            << L"Abonnee ID"
            << std::left
            << std::setw(15)
            << L"Aanvraag Datum"
            << std::left
            << std::setw(15)
            << L"Status"
            << L"\n" ;
    for (Aanvraag *i: parkBeheerder->lijstParkAanvraag) {
        index++;
        std::wcout
                 << std::left
                << std::setw(5)
                << index
                << std::left
                << std::setw(10)
                << i->aangevraagdByAbonnee->abonneeId
                << std::left
                << std::setw(15)
                << i->beginDatum->datumNaarString()
                << std::left
                << std::setw(15)
                << i->aanvraagStatus
                << L"\n" ;
    }
    return index;
}

bool Abonnee:: toonAanvraagSent() {
    int index = 0;
    if(aanvraagLijst.empty()) {
        std:: cout << L"\nThere are no aanvraag that you sent\n" ;
        return false;
    }
    std::wcout
             << std::left
            << std::setw(5)
            << L"ID"
            << std::left
            << std::setw(10)
            << L"Park ID"
            << std::left
            << std::setw(15)
            << L"Aanvraag Datum"
            << std::left
            << std::setw(15)
            << L"Status"
            << L"\n" ;
    for(Aanvraag *i: aanvraagLijst) {
         index++;
         std::wcout
                 <<std::left
                << std::setw(5)
                << index
                << std::left
                << std::setw(10)
                << i->parkID
                << std::left
                << std::setw(15)
                << i->beginDatum->datumNaarString()
                << std::left
                << std::setw(15)
                << i->aanvraagStatus
                << L"\n" ;
    }
    return true;
}

bool Abonnee::cancelAanvraag(int ID) {
    int index = 0;
    if(ID - 1 > static_cast<int>(aanvraagLijst.size())){
        return false;
    }
    auto aanvraag = aanvraagLijst[ID-1];
    if(aanvraag->aanvraagStatus == AV_STATUS[1]){
        return false;
    }
    else {
        aanvraagLijst.erase(aanvraagLijst.begin()+(ID-1));
        return true;
    }
}

void Abonnee::recensiePark(Park *occupyPark, int score, std::wstring comment) {
    //create object
    Recensie *recensie = new Recensie(score, comment, this);
    //add to recensie lijst of park
    occupyPark->recensieToevoegenToParkRecensielijst(recensie);
}


bool Abonnee::declineAanvraag(int ID) {
    int indice = 0;
    for (auto i: parkBeheerder->lijstParkAanvraag) {
        if (parkBeheerder->lijstParkAanvraag[ID] == i) {
            continue;
        }
        if ((i->eindDatum->countDatum() - parkBeheerder->lijstParkAanvraag[ID]->beginDatum->countDatum()) < 0 ||
            (parkBeheerder->lijstParkAanvraag[ID]->eindDatum->countDatum() - i->beginDatum->countDatum()) < 0) {
            continue;
        }
        indice++;
        i->aanvraagStatus = AV_STATUS[2];
    }
    parkBeheerder->lijstParkAanvraag[ID]->aanvraagStatus = AV_STATUS[2];


    return true;
}

bool Abonnee::acceptAanvraag(int ID) {
    if (ID > parkBeheerder->lijstParkAanvraag.size()) {
        return false;
    }


    if(parkBeheerder->lijstParkAanvraag[ID]->aanvraagStatus == AV_STATUS[1] || parkBeheerder->lijstParkAanvraag[ID]->aanvraagStatus == AV_STATUS[2]) {
        std::wcout  <<"\nYou can not accept the aanvraag has been accepted or declined\n" ;
        return false;
    }
    // cout << L"\nThe aanvraag does not match\n";
    // return false;
    parkBeheerder->parkStatus = L"UNAVAILABLE";
    auto huurDatum = parkBeheerder->lijstParkAanvraag[ID ]->beginDatum;
    auto huurEinddatum = parkBeheerder->lijstParkAanvraag[ID]->eindDatum;
    auto tenant = parkBeheerder->lijstParkAanvraag[ID]->aangevraagdByAbonnee;

    // int requiredKrediet = (huurDatum - huurEinddatum) *parkBeheerder->consumingPointsPerDay;
    declineAanvraag(ID );
    parkBeheerder->lijstParkAanvraag[ID]->aanvraagStatus = AV_STATUS[1];
    OccupyPark *occupyPark = new OccupyPark(huurDatum, huurEinddatum, tenant);
    Tenant *occupyAbonnee = new Tenant(huurDatum, huurEinddatum, parkBeheerder);
    // add object to occupy lijst
    tenant->tenantLijst.push_back(occupyAbonnee);
    parkBeheerder->lijstOccupyPark.push_back(occupyPark);
    // add krediet of beheerder and minus krediet of tenant
    this->kredietToevoegen(parkBeheerder->consumingPointsPerDay * (huurEinddatum->countDatum() - huurDatum->countDatum()));
    tenant->minusKrediet(parkBeheerder->consumingPointsPerDay * (huurEinddatum->countDatum() - huurDatum->countDatum()));
    return true;
}


void Abonnee::zieTenant() {
    std::wcout
             << std::left
            << std::setw(15)
            << L"Begin Datum"
            << std::left
            << std::setw(20)
            << L"End Datum"
            << std::left
            << std::setw(15)
            << L"Park ID"
            << std::left
            << std::setw(15)
            << L"Beheerder ID"
            << L"\n" ;
    for (int i = 0; i < tenantLijst.size(); i++) {
        auto tenantbeginDatum = tenantLijst[i]->beginVanafDatum->datumNaarString();
        auto tenanteindDatum = tenantLijst[i]->ToDatum->datumNaarString();
        auto Park = tenantLijst[i]->occupyPark;
        std::wcout  << i+1 << L"."
                  << std::left
                  << std::setw(15)
                  << tenantbeginDatum
                  << std::left
                  << std::setw(20)
                  << tenanteindDatum
                  << std::left
                  << std::setw(15)
                  << Park->parkID
                  << std::left
                  << std::setw(15)
                  << Park->beheerder->abonneeId
                  << L"\n" ;
    }
}


bool Abonnee::zieAbonneeOccupyLijst() {
    if (tenantLijst.empty()) {
        std::wcout  << L"\nThere are no parks you are occupying\n" ;
        return false;
    }
    for (int i = 0; i < tenantLijst.size(); i++) {
        std::wcout  << i + 1 << '.' << tenantLijst[i]->beginVanafDatum->datumNaarString() << L"-->"
                  << tenantLijst[i]->ToDatum->datumNaarString() << L":" << tenantLijst[i]->occupyPark->parkID << L"\n" ;
    }
    return true;
}

bool Abonnee::checkout(int leaveId) {
    //if input greater than the size of lijst, return false
    if (leaveId > tenantLijst.size()) {
        return false;
    }
    //get object
    auto leaveTenant = tenantLijst[leaveId];
    auto leavebeginDatum = leaveTenant->beginVanafDatum;
    auto leaveDatum = leaveTenant->ToDatum;
    auto leavePark = leaveTenant->occupyPark;
    //create object
    auto *unrated = new OccupyPark(leavebeginDatum, leaveDatum, this);
    //add object to unrated lijst
    leavePark->unratedTenant.push_back(unrated);
    leavePark->parkStatus = STATUS[0];
    //delete van tenant lijst
    tenantLijst.erase(tenantLijst.begin() + (leaveId));
    //when leave park call abonnee recensie park and abonnee recensie occupier afterwards in menu
    return true;

}

bool Abonnee::zieUnratedLijst() {
    //if lijst is empty
    if (parkBeheerder->unratedTenant.empty()) {
        return false;
    }
    //display data
    std::wcout  << L"\nAll unrated tenant will be displayed: \n" ;
    std::wcout
             <<std::left
            << std::setw(10)
            << L"Index"
            << std::left
            << std::setw(20)
            << L"Begin Datum"
            << std::left
            << std::setw(20)
            << L"End Datum"
            << std::left
            << std::setw(10)
            << L"AbonneeID"
            << L"\n" ;
    for (int i = 0; i < parkBeheerder->unratedTenant.size(); i++) {
        std::wcout
                 << std::left
                << std::setw(10)
                << i+1
                << std::left
                << std::setw(20)
                << parkBeheerder->unratedTenant[i]->beginVanafDatum->datumNaarString()
                << std::left
                << std::setw(20)
                << parkBeheerder->unratedTenant[i]->toDatum->datumNaarString()
                << std::left
                << std::setw(10)
                << parkBeheerder->unratedTenant[i]->tenant->abonneeId
                << L"\n" ;
    }
    return true;
}

bool Abonnee::recensieTenant(int rateId, int score, std::wstring comment) {
    if (rateId > parkBeheerder->unratedTenant.size()) {
        return false;
    }
    auto tenant = parkBeheerder->unratedTenant[rateId]->tenant;
    //create recensie object
    auto recensie = new Recensie(score, comment, tenant);
    //add recensie to recensie lijst
    tenant->tenantRecensielijst.push_back(recensie);
    //remove van unrated lijst
    parkBeheerder->unratedTenant.erase(parkBeheerder->unratedTenant.begin() + (rateId - 1));
    return true;


}

Abonnee::~Abonnee() {
    for (auto& tenant : tenantLijst) {
        delete tenant;
    }

    for (auto& recensie : tenantRecensielijst) {
        delete recensie;
    }

    for (auto& aanvraag : aanvraagLijst) {
        delete aanvraag;
    }
}

