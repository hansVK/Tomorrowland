
// Created by r0834721 on 31/7/2023
//

#include "Park.h"


Park::Park(std::wstring parkID, std::wstring locatie, std::wstring parkDescription)
        : parkID(parkID),
          locatie(locatie),
          parkDescription(parkDescription),
          isToegevoegd(false),
          beginDatum(nullptr),
          eindDatum(nullptr),
          beheerder(nullptr),
          minRating(0),
          consumingPointsPerDay(0),
          parkScores(0)
{}
double Park::getRatingScore() {
    if(this->lijstParkRecensie.empty()){
        return 0;
    }
    double tmpScore = 0;
    for(auto & i : lijstParkRecensie){
        tmpScore += i->ratingScore;
    }
    double avgScore = (double ) tmpScore / (double ) lijstParkRecensie.size();
    return avgScore;
}
void Park::zieParkInfo() {
    std::wcout << L"\nBeheerder: " << beheerder->mail << L"\n";
    std::wcout << L"Locatie: " << locatie << L"\n";
    std::wcout << L"Description: " << parkDescription << L"\n";
    std::wcout << L"Rating score: " << this->getRatingScore() << L"\n";
    if(isToegevoegd){
        std::wcout << L"Available van: " << this->beginDatum->datumNaarString() << L" to " << this->eindDatum->datumNaarString() << L"\n";
        std::wcout << L"Krediet per day: " << consumingPointsPerDay << L"\n";
        std::wcout << L"Minimum rating score of tenant: " << minRating << L"\n";
    }
}
void Park::zieParkRecensie() {
    if(lijstParkRecensie.empty()){
        std::wcout << L"\nThere are no recensies for this park\n";
    }
    else {
        for(auto &i : lijstParkRecensie){
            int tmpScore = i->ratingScore;
            std::wstring tmpComment = i->comment;
            auto abnRecensie = i->abonneeRecensie;
            std::wcout << L"\n-----------------------"
                      << L"\n\nRecensie by abonnee: " << abnRecensie->mail
                      << L"\n-----------------------"
                      << L"Score: " << tmpScore << L"\n"
                      << L"Comment: " << tmpComment;
        }
    }
}
void Park::aanvraagToevoegenToParkAanvraagLijst(Aanvraag *aanvraag) {
    lijstParkAanvraag.push_back(aanvraag);
}

void Park::recensieToevoegenToParkRecensielijst(Recensie *recensie) {
    lijstParkRecensie.push_back(recensie);
}


Park::~Park() {
    delete beginDatum;
    delete eindDatum;

    for (auto& gehuurdePark : lijstOccupyPark) {
        delete gehuurdePark;
    }

    for (auto& aanvraag : lijstParkAanvraag) {
        delete aanvraag;
    }

    for (auto& recensie : lijstParkRecensie) {
        delete recensie;
    }
}


