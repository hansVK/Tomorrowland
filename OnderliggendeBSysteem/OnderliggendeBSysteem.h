//
// Created by r0834721 on 31/7/2023
//

#ifndef TOMORROWLAND_ONDERLIGGENDEBSYSTEEM_H
#define TOMORROWLAND_ONDERLIGGENDEBSYSTEEM_H

#include <regex>
#include <vector>
#include "../MClassen/Park/Park.h"
#include "../MClassen/Beheerder/Beheerder.h"
#include "../MClassen/Datum/Datum.h"
#include "../MClassen/Tenant/Tenant.h"
#include "../MClassen/Recensie/Recensie.h"
#include "../MClassen/Abonnee/Abonnee.h"
#include "../MClassen/Aanvraag/Aanvraag.h"
#include "../MClassen/OccupyPark/OccupyPark.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "../vast.h"
#include <sstream>

class Datum;
class Gebruiker;
class Beheerder;
class Abonnee;
class Park;

#define RATING_TENANT_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\ratingTenant.dat)"
#define OCCUPIERS_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\occupiers.dat)"
#define RATING_park_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\ratingPark.dat)"
#define ABONNEES_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\abonnees.dat)"
#define UNRATED_OCC_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\unratedOcc.dat)"
#define park_LIJST_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\parkLijst.dat)"
#define AANVRAAG_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\aanvraag.dat)"
#define park_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\park.dat)"
#define BEHEERDER_BESTAND LR"(C:\Users\hansA\Documents\Hans_Actual\2022-2023\1e-Semester\-Object-Oriented-Programming\max\Data\beheerder.dat)"

class OnderliggendeBSysteem {
public:
    std::vector<Abonnee *> abonnees;
    Beheerder *beheerder;
    std::vector<Park *> parkVector;
    Abonnee *huidigGebruiker = nullptr;
    Park *huidigGebruikerPark;
    std::vector<Park *> abonneeSuitableParkLijst;
    OnderliggendeBSysteem();
    inline std::wstring trimString(std::wstring &str);
    inline std::vector<std::wstring> mijnStrTok(const std::wstring& str, wchar_t sep);
    inline bool isNumGeldig(std::wstring &inputStr);
    inline bool isDouble(std::wstring &inputStr);
    inline bool isWachtGeldig(std::wstring &wachtwoord);
    inline bool isGebrGeldig(std::wstring &gebruikersnaam);
    inline bool geldigeMail(std::wstring &umail);
    inline bool isValidKrediet(Abonnee *abn, Park *park);
    inline bool isValidScore(Abonnee *abn, Park *park);
    inline bool isDatumGeldig(std::wstring datum);
    inline bool isJuisteDatumOrder(Datum* begin, Datum *eind);
    inline int menuKeuze(int begin, int eind);
    inline void hoofdScherm();
    inline void beheerderMenu();
    inline void beheerderLoginMenu();
    inline void toonAanvraagSent();
    inline void beheerderZieAbonneeMenu();
    inline void beheerderZieParkMenu();
    inline void loginAbnMenu();
    inline void abonneeMenu();
    inline void parkHuurvrijMenu();
    inline void rateTenantMenu(int leaveID);
    inline bool getInfoLijstParkMenu();
    inline bool enterParkInfo();
    inline void validParkMenu(Datum *begin, Datum *eind, std::wstring locatie);
    inline void searchValidParkMenu();
    inline bool abnAanvraagPark(Datum *beginDatum, Datum *eindDatum, int parkId);
    inline void zieAanvraagMenu();
    inline void actionAanvraagMenu(int aanvraagID);
    inline void gehuurdeParkTonen();
    inline void cancelAanvraagMenu(int ID);
    inline void recensieTonen();
    inline void zieUnratedTenantLijst();
    inline bool isValidBeginParks(Datum *begin, Abonnee *abn, Park *park, std::wstring locatie);
    inline bool isValidEndParks(Datum *eind, Abonnee *abn, Park *park, std::wstring locatie);
    inline bool getGeldigeBeginParks(Datum *begin, std::wstring locatie);
    inline bool getGeldigeEndParks(Datum *eind, std::wstring locatie);
    inline bool deleteInRentPark();
    inline void inputParkToSys();
    inline void inputBeheerderToSys();
    inline void inputAbnParkToSys();
    inline void inputParkLijstToSys();
    inline void inputAbonneeToSys();
    inline void inputRatingTenantToSys();
    inline void inputRatingParkToSys();
    inline void inputAanvraagToSys();
    inline void inputOccupierToSys();
    inline void inputUnratedToSys();
    inline void outputOccupierNaarBestand();
    inline void outputBeheerderNaarBestand();
    inline void outputUnratedNaarBestand();
    inline void outputAanvraagNaarBestand();
    inline void outputRatingTenantNaarBestand();
    inline void outputRatingParkNaarBestand();
    inline void outputParkNaarBestand();
    inline void outputParkLijstNaarBestand();
    inline void outputAbonneeNaarBestand();
    //    FUN OVERLOADING!
    inline void outputAbonneeNaarBestand(std::vector<Abonnee *> newabonnee);
    inline void abonneeRegistreren();
    inline bool abonneeInloggen(std::wstring gebruikersnaam, std::wstring wachtwoord);
    inline Datum *stringToDatum(std::wstring &datum);
};
#endif //TOMORROWLAND_ONDERLIGGENDEBSYSTEEM_H
