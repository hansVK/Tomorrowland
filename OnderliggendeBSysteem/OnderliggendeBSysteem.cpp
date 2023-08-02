//
// Created by r0834721 on 31/7/2023
//

#include "OnderliggendeBSysteem.h"

OnderliggendeBSysteem::OnderliggendeBSysteem() {
    inputBeheerderToSys();
    inputAbonneeToSys();
    inputParkToSys();
    inputAbnParkToSys();
    inputParkLijstToSys();
    inputOccupierToSys();  //check this
    inputRatingParkToSys();
    inputRatingTenantToSys();
    inputAanvraagToSys();
    inputUnratedToSys();
    hoofdScherm();
}

inline std::wstring OnderliggendeBSysteem::trimString(std::wstring &str) {

    std::wstring finalStr;
    for (wchar_t c: str) {
        if (c == L' ') {
            continue;
        } else {
            finalStr += c;
        }
    }
    return finalStr;

}

inline std::vector<std::wstring> OnderliggendeBSysteem::mijnStrTok(const std::wstring& str, wchar_t sep) {
    std::vector<std::wstring> gegLijst;
    std::wstringstream ss;
    ss << str;
    std::wstring cell;
    while (std::getline(ss, cell, sep)) {
        gegLijst.push_back(cell);
    }
    return gegLijst;
}


inline bool OnderliggendeBSysteem::isNumGeldig(std::wstring &inputStr) {
    for (int i = 0; i < inputStr.length(); i++) {
        if (i == 0) {
            if (inputStr[i] == L'-') {
                continue;
            }
        }
        if (!std::isdigit(inputStr[i])) {
            return false;
        }
    }
    return true;
}

inline bool OnderliggendeBSysteem::isDouble(std::wstring &inputStr) {
    int dotCount = 0;
    for (int i = 0; i < inputStr.length(); i++) {
        if (i == 0) {
            if (inputStr[i] == L'.') {
                dotCount++;
                continue;
            }
        }
        if (inputStr[i] == L'.') {
            dotCount++;
            continue;
        }

        if (!std::isdigit(inputStr[i])) {
            std::wcout  << L"Not a number!!! Try again: " ;
            return false;
        }
        if (dotCount > 1) {
            std::wcout  << L"Not a number!!! Try again: " ;
            return false;
        }
    }
    return true;
}

inline bool OnderliggendeBSysteem::isWachtGeldig(std::wstring &wachtwoord) {
    //false: Minimum 8 and maximum 10 characters, at least one uppercase letter, one lowercase letter, one number and one special character:
    //true: continue
    std::wregex reg(L"^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@$!%*?&])[A-Za-z0-9@$!%*?&]{8,10}$");
    wachtwoord = trimString(wachtwoord);
    if (std::regex_match(wachtwoord, reg)) {
        return true;
    } else {
        std::wcout

                << L"Minimum 8 and maximum 10 characters, at least one uppercase letter, one lowercase letter, one number and one special character. Try again \n"
                ;
        return false;
    }
}

inline bool OnderliggendeBSysteem::isGebrGeldig(std::wstring &gebruikersnaam) {
    std::wregex reg(L"\\s");
    if (std::regex_match(gebruikersnaam, reg)) {
        std::wcout  << L"The gebruikersnaam cannot have spaces! Try again \n" ;
        return false;
    } else {
        if (8 > gebruikersnaam.length() || gebruikersnaam.length() > 16) {
            std::wcout  << L"The gebruikersnaam can only have 8 to 16 characters! Try again \n" ;
            return false;
        } else {
            for (auto abonnee: abonnees) {
                if (gebruikersnaam == abonnee->gebruikersnaam) {
                    std::wcout  << L"Taken gebruikersnaam! Try again: \n" ;
                    return false;
                }
            }
            return true;
        }
    }
}

inline bool OnderliggendeBSysteem::geldigeMail(std::wstring &umail) {
    std::wregex reg(L"^[a-zA-Z0-9._%+-]{1,10}@[a-zA-Z0-9.-]{1,10}\\.[a-zA-Z]{2,}$");
    umail = trimString(umail);
    if (std::regex_match(umail, reg)) {
        return true;
    } else {
        std::wcout  << L"Tot 10 chars voor en na @\n" ;
        return false;
    }
}

inline bool OnderliggendeBSysteem::isValidKrediet(Abonnee *abn, Park *park) {
    if (abn->krediet <
        (park->consumingPointsPerDay * (park->eindDatum->countDatum() - park->beginDatum->countDatum()))) {
        return false;
    }
    return true;
}

inline bool OnderliggendeBSysteem::isValidScore(Abonnee *abn, Park *park) {
    if (abn->score < park->minRating) {
        return false;
    }
    return true;
}

inline bool OnderliggendeBSysteem::isDatumGeldig(std::wstring datum) {
    std::wstring day = datum.substr(0, 2);
    std::wstring month = datum.substr(3, 2);
    std::wstring jaar = datum.substr(6, 4);

    for (int i = 0; i < datum.length(); i++) {
        if (i == 2 || i == 5) {
            if (datum[i] != L'/') {
                std::wcout  << L"Datum must follow the format xx/xx/xxxx. Try again \n" ;
                return false;
            }
        } else if (!std::isdigit(datum[i])) {
            std::wcout  << L"Your datum is not valid. Try again \n" ;
            return false;
        } else if (std::stoi(month) > 13 || std::stoi(month) < 1) {
            std::wcout  << L"Your datum is not valid. Try again \n" ;
            return false;
        } else if (std::stoi(day) > DAG_VSCH_MAAND[std::stoi(month) - 1]) {
            std::wcout  << L"Your datum is not valid. Try again \n" ;
            return false;
        }
    }
    return true;
}

inline bool OnderliggendeBSysteem::isJuisteDatumOrder(Datum *begin, Datum *eind) {
    if (eind->countDatum() - begin->countDatum() > 0) {
        return true;
    } else {
        return false;
    }
}


inline int OnderliggendeBSysteem::menuKeuze(int begin, int eind) {
    int finalKeuze;
    std::wstring tmpKeuze;
    bool flag;

    do {
        std::wcout  << LR"(Uw keuze invoeren:   )" ;
        std::wcin >> tmpKeuze;
        if (!isNumGeldig(tmpKeuze)) {
            std::wcout  << L"\nKeuze is only number! Try again: " ;
            flag = false;
            continue;
        }
        finalKeuze = std::stoi(tmpKeuze);
        if (finalKeuze < begin || finalKeuze > eind) {
            std::wcout  << L"Between " << begin << L" and " << eind << L" only! Try again: " ;
            flag = false;
            continue;
        } else {
            flag = true;
        }
    } while (!flag);

    return finalKeuze;
}
inline void OnderliggendeBSysteem::hoofdScherm() {
    int keuze;
    std::wcout << LR"---(
                            Discover Vacation Parks: Your Gateway to an unforgettable Escapes and Luxury Stays
      ::::.
        _____A_             Explore Our Parks, Choose Your Ideal Accommodation
       /      /\            Book with Ease, Modify and Create Memories
    __/__/\__/  \___        Empowering Owners, Assisting Employees, :) Customers
---/__|" '' "| /___/\----   Your Dream: Getaway | Our Mission: Manage
   |''|"'||'"| |' '||
   `""`""))""`"`""""        created by r0834721 for a summer retake. All rights reserved)---";
    std::wcout  << std::endl << std::endl << std::endl << std::endl ;
    std::wcout  << L" Use the app as:    1. Abonnee   2. Beheerder  3. Staff 4.I've had enough (quit) \n" ;
    std::wcout  << L"----------------------------------------------------------\n\n" ;

    keuze = menuKeuze(1, 4);
    switch (keuze) {
        case 1:
            loginAbnMenu();
            break;
        case 2:
            beheerderLoginMenu();
            break;
        case 3:
//            TODO
        case 4:
            outputAbonneeNaarBestand();
            outputParkNaarBestand();
            outputParkLijstNaarBestand();
            outputBeheerderNaarBestand();
            outputAanvraagNaarBestand();
            outputRatingParkNaarBestand();
            outputUnratedNaarBestand();
            outputRatingTenantNaarBestand();
            outputOccupierNaarBestand();
            break;
    }
}
//beheerder menu - basic feature
inline void OnderliggendeBSysteem::beheerderMenu() {
    int keuze;
    std::wcout  << L"---------------------------------------\n" ;
    std::wcout  << L"              BEHEERDER MENU             \n" ;
    std::wcout  << L"     1.Zie Abonnee Lijst              \n"
              << L"     2.Zie Park Lijst               \n"
              << L"     3.Back to main menu             \n" ;
    std::wcout  << L"---------------------------------------\n" ;
    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            beheerderZieAbonneeMenu();
            break;
        case 2:
            beheerderZieParkMenu();
            break;
        case 3:
            hoofdScherm();
            break;
    }


}

inline void OnderliggendeBSysteem::beheerderZieAbonneeMenu() {
    int index = 1;
    std::wcout  << L"All the abonnee of the systeem: " << L"\n" ;
    std::wcout
             << std::left
            << std::setw(5)
            << L"Index"
            << std::left
            << std::setw(10)
            << L"AbonneeID"
            << std::left
            << std::setw(15)
            << L"Full Name"
            << L"\n" ;
    for (auto abn: abonnees) {
        std::wcout
                 << std::left
                << std::setw(5)
                << index
                << std::left
                << std::setw(10)
                << abn->abonneeId
                << std::left
                << std::setw(15)
                << abn->mail
                << L"\n" ;
        index++;
    }
    std::wcout << L"\n";
    std::wcout  << L"\t---1.Zie Abonnee Detail---\n" << L"\t---2.Back to beheerder menu---\n" ;
    int keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            std::wcout
                     << std::left
                    << std::setw(10)
                    << L"Index"
                    << std::left
                    << std::setw(15)
                    << L"AbonneeID"
                    << std::left
                    << std::setw(15)
                    << L"Full Name"
                    << std::left
                    << std::setw(15)
                    << L"Gebruikersnaam"
                    << std::left
                    << std::setw(8)
                    << L"Krediet"
                    << std::left
                    << std::setw(15)
                    << L"Locatie"
                    << std::left
                    << std::setw(10)
                    << L"Rating Score"
                    << L"\n" ;
            for (int i = 0; i < abonnees.size(); i++) {
                std::wcout
                         << std::left
                        << std::setw(10)
                        << i + 1
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->abonneeId
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->mail
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->gebruikersnaam
                        << std::left
                        << std::setw(8)
                        << abonnees[i]->krediet
                        << std::left
                        << std::setw(15)
                        << abonnees[i]->locatie
                        << std::left
                        << std::setw(10)
                        << abonnees[i]->getRatingScore()
                        << L"\n" ;
            }
            std::wcout << L"\n";
            std::wcout  << abonnees.size() + 1 << L".Back to beheerder menu\n" ;
            menuKeuze(abonnees.size() + 1, abonnees.size() + 1);
            beheerderMenu();

        case 2:
            beheerderMenu();
            break;
    }
}

inline void OnderliggendeBSysteem::beheerderZieParkMenu() {
    int index = 1;
    std::wcout  << L"All park of the systeem: " << L"\n" ;
    std::wcout
             << std::left
            << std::setw(10)
            << L"Index"
            << std::left
            << std::setw(8)
            << L"ParkID"
            << std::left
            << std::setw(15)
            << L"BeheerderID"
            << std::left
            << std::setw(15)
            << L"Locatie"
            << std::left
            << std::setw(35)
            << L"Description"
            << L"\n" ;
    for (auto i: parkVector) {
        std::wcout
                 << std::left
                << std::setw(10)
                << index
                << std::left
                << std::setw(8)
                << i->parkID
                << std::left
                << std::setw(15)
                << i->beheerder->abonneeId
                << std::left
                << std::setw(15)
                << i->locatie
                << std::left
                << std::setw(35)
                << i->parkDescription
                << L"\n" ;
        index++;
    }
    std::wcout << L"\n";
    std::wcout  << L"\t---1.Zie Park Detail---\n" << L"\t---2.Back to beheerder menu---\n" ;
    int keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            std::wcout
                     << std::left
                    << std::setw(10)
                    << L"Index"
                    << std::left
                    << std::setw(10)
                    << L"ParkID"
                    << std::left
                    << std::setw(10)
                    << L"BeheerderID"
                    << std::left
                    << std::setw(20)
                    << L"Begin Datum"
                    << std::left
                    << std::setw(20)
                    << L"End Datum"
                    << std::left
                    << std::setw(25)
                    << L"KredietPerDay"
                    << std::left
                    << std::setw(15)
                    << L"minScore"
                    << std::left
                    << std::setw(20)
                    << L"Locatie"
                    << std::left
                    << std::setw(35)
                    << L"Description"
                    << L"\n" ;
            for (int j = 0; j < parkVector.size(); j++) {
                std::wcout
                         << std::left
                        << std::setw(10)
                        << j + 1
                        << std::left
                        << std::setw(10)
                        << parkVector[j]->parkID
                        << std::left
                        << std::setw(10)
                        << parkVector[j]->beheerder->abonneeId
                        << std::left
                        << std::setw(20)
                        << parkVector[j]->beginDatum->datumNaarString()
                        << std::left
                        << std::setw(20)
                        << parkVector[j]->eindDatum->datumNaarString()
                        << std::left
                        << std::setw(25)
                        << parkVector[j]->consumingPointsPerDay
                        << std::left
                        << std::setw(15)
                        << parkVector[j]->minRating
                        << std::left
                        << std::setw(20)
                        << parkVector[j]->locatie
                        << std::left
                        << std::setw(35)
                        << parkVector[j]->parkDescription
                        << L"\n" ;
            }
            std::wcout << L"\n";
            std::wcout  << parkVector.size() + 1 << L".Back to beheerder menu\n" ;
            menuKeuze(parkVector.size() + 1, parkVector.size() + 1);
            beheerderMenu();
            break;
        case 2:
            beheerderMenu();
            break;
    }


}

inline void OnderliggendeBSysteem::loginAbnMenu() {
    std::wstring gebruikersnaam, wachtwoord;
    std::wcout  << L"--------------------------------------\n" ;
    std::wcout  << L"            ABONNEE PORTAL            \n" ;
    std::wcout  << L"        1. Register as a new abonnee          \n";
    std::wcout  << L"        2. Login as abonnee          \n"
              << L"        3. Back to main menu        \n" ;
    std::wcout  << L"--------------------------------------\n" ;

    switch (menuKeuze(1, 2)) {
        case 1:
            abonneeRegistreren();
            break;
        case 2:
            std::wcin.ignore();
            std::wcout  << LR"(Uw gebruikersnaam invoeren:   )" ;
            std::getline(std::wcin, gebruikersnaam);
            std::wcout  << LR"(Uw wachtwoord invoeren:   )" ;
            std::getline(std::wcin, wachtwoord);
            if (abonneeInloggen(gebruikersnaam, wachtwoord)) {
                abonneeMenu();
                break;
            }
        case 3:
            hoofdScherm();
            break;
    }


}

inline void OnderliggendeBSysteem::beheerderLoginMenu() {
    std::wstring gebruikersnaam, wachtwoord;

    std::wcout  << L"---------------------------------------\n" ;
    std::wcout  << L"              BEHEERDER MENU             \n" ;
    std::wcout  << L"     1.Login As Beheerder                \n"
              << L"     2.Back to main menu             \n" ;
    std::wcout  << L"---------------------------------------\n" ;
    switch (menuKeuze(1, 2)) {
        case 1:
            std::wcin.ignore();
            std::wcout  << LR"(Uw gebruikersnaam invoeren:   )" ;
            std::getline(std::wcin, gebruikersnaam);
            std::wcout  << LR"(Uw wachtwoord invoeren:   )" ;
            std::getline(std::wcin, wachtwoord);
            if (beheerder->gebruikersnaam == gebruikersnaam && beheerder->wachtwoord == wachtwoord) {
                std::wcout  << L"Succesvol ingelogd... aan het laden... \n\n\n\n" ;
                beheerderMenu();
                break;
            } else {
                std::wcout  << L"\n\nWrong gebruikersnaam or wachtwoord!!! \n" ;
            }
        case 2:
            hoofdScherm();
            break;


    }
}


inline void OnderliggendeBSysteem::abonneeMenu() {
//    TODO Customers can edit their gegevens
    int keuze;
    std::wcout  << L"----------------------------------------\n" ;
    std::wcout  << L"          ---ABONNEE MENU---           \n" ;
    std::wcout  << L"  1.Zie Account's Information        \n"
              << L"  2.Zie Available Parks             \n"
              << L"  3.Handle Aanvraags                   \n"
              << L"  4.Lijst Park For Rental             \n"
              << L"  5.Toon gehuurde menu                  \n"
              << L"  6.Zie Unrated Tenant Lijst          \n"
              << L"  7.Toon Aanvraag Sent                 \n"
              << L"  8.Logout                            \n" ;
    std::wcout  << L"----------------------------------------\n" ;
    keuze = menuKeuze(1, 8);
    switch (keuze) {
        case 1:
            huidigGebruiker->toonAccountInfo();
            std::wcout  << L"1. Back to menu...\n" ;
            menuKeuze(1, 1);
            abonneeMenu();
            break;
        case 2:
            searchValidParkMenu();
            break;
        case 3:
            zieAanvraagMenu();
            break;
        case 4:
            parkHuurvrijMenu();
            break;
        case 5:
            gehuurdeParkTonen();
            break;
        case 6:
            zieUnratedTenantLijst();
            break;
        case 7:
            toonAanvraagSent();
            break;
        case 8:
            huidigGebruiker = nullptr;
            hoofdScherm();
            break;
    }


}

inline void OnderliggendeBSysteem::parkHuurvrijMenu() {
    std::wcout  << L"\t---UP park FOR RENT MENU ---\n" ;
    if (huidigGebruiker->parkBeheerder != nullptr) {
        if (huidigGebruiker->parkBeheerder->isToegevoegd) {
            std::wcout  << L"You are having a park for rent: \n" ;
            huidigGebruiker->parkBeheerder->zieParkInfo();
            if (huidigGebruiker->parkBeheerder->lijstParkAanvraag.empty()) {
                std::wcout  << L"\n\n---\t1. Omit the park of renting site ---\n"
                          << L"\t---2. Back to abonnee menu ---\n" ;
                switch (menuKeuze(1, 2)) {
                    case 1:
                        deleteInRentPark();
                        std::wcout  << L"\tCome back to UP park FOR RENT MENU \n" ;
                        parkHuurvrijMenu();
                        break;
                    case 2:
                        abonneeMenu();
                        break;
                }
            } else {
                std::wcout  << L"\tCome back to abonnee menu \n" ;
                abonneeMenu();
            }
        } else {
            std::wcout  << L"You are having a park but not allowing rental yet: \n"
                      << L"1. Add the park for rent\n"
                      << L"2. Back to abonnee menu\n" ;
            switch (menuKeuze(1, 2)) {
                case 1:
                    getInfoLijstParkMenu();
                    std::wcout  << L"\nPark toegevoegd\n\n" ;
                    parkHuurvrijMenu();
                    break;
                case 2:
                    abonneeMenu();
                    break;
            }
        }
    } else {
        std::wcout  << L"You do not have a park. Add one: \n" ;
        enterParkInfo();
        parkHuurvrijMenu();
    }
}

inline bool OnderliggendeBSysteem::getInfoLijstParkMenu() {
    std::wstring beginDatum, eindDatum, minScores, minKrediets;
    std::wcin.ignore();

    std::wcout  << L"\tPlease enter of your rental info\n" ;
    do {
        do {
            std::wcout  << L"Enter the first renting datum " ;
            std::getline(std::wcin, beginDatum);
        } while (!isDatumGeldig(beginDatum));
        do {
            std::wcout  << L"Enter the eind renting datum " ;
            std::getline(std::wcin, eindDatum);
        } while (!isDatumGeldig(eindDatum));
    } while (!isJuisteDatumOrder(stringToDatum(beginDatum), stringToDatum(eindDatum)));

    do {
        std::wcout  << L"Enter the required krediets per day " ;
        std::getline(std::wcin, minKrediets);
    } while (!isDouble(minKrediets));

    do {
        std::wcout  << L"Enter the required minimum scores of renant " ;
        std::getline(std::wcin, minScores);
    } while (!isDouble(minScores));

    Datum *begin = stringToDatum(beginDatum);
    Datum *eind = stringToDatum(eindDatum);
    huidigGebruiker->parkToevoegen(begin, eind, std::stod(minKrediets), std::stod(minScores), STATUS[0]);
    return true;
}

inline bool OnderliggendeBSysteem::enterParkInfo() {
    std::wstring parkId, locatie, description;
    int keuze;
    std::wcout  << L"\tPlease enter your park's information\n" ;
    std::wcout  << L"\tKies the supported app locatie: " ;
    std::wcout  << L"\t1. BOOM \t2.WILLEBROEK \t3.RUMST\n" ;
    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            locatie = PLEKKEN[0];
            break;
        case 2:
            locatie = PLEKKEN[1];
            break;
        case 3:
            locatie = PLEKKEN[2];
            break;
    }
    std::wcin.ignore();
    std::wcout  << L"\tEnter the description for your park: \n" ;
    std::getline(std::wcin, description);
    auto *createdPark = new Park(L"PRK" + std::to_wstring(parkVector.size() + 1), locatie, description);
    parkVector.push_back(createdPark);
    huidigGebruiker->createPark(createdPark);
    return true;
}

inline void OnderliggendeBSysteem::gehuurdeParkTonen() {
    //Check if huidig abonnee ocupying any park
    if (huidigGebruiker->tenantLijst.empty()) {
        std::wcout  << L"\n\t\tThere are no park you are renting\n\n\t\tBack To Abonnee Menu\n" ;
        abonneeMenu();
    }
    std::wcout  << L"\nThe lijst of park you occupied:\n" ;
    huidigGebruiker->zieTenant();
    std::wcout << L"\n---" << huidigGebruiker->tenantLijst.size() + 1 << L".Back to menu\n";
    int keuze = menuKeuze(1, huidigGebruiker->tenantLijst.size() + 1);
    if (keuze == huidigGebruiker->tenantLijst.size() + 1) {
        abonneeMenu();
    }
    auto tenantPark = huidigGebruiker->tenantLijst[keuze - 1]->occupyPark;
    tenantPark->zieParkInfo();
    std::wcout  << L"\n"
              << L"\t\t1.Checkout\n"
              << L"\t\t2.Back to menu\n" ;
    int newKeuze = menuKeuze(1, 2);
    switch (newKeuze) {
        case 1:
            huidigGebruiker->checkout(keuze - 1);
            std::wcout  << L"\n\t\tLeft Park\n" ;
            rateTenantMenu(keuze - 1);
            break;
        case 2:
            abonneeMenu();
            break;
    }

}

inline void OnderliggendeBSysteem::rateTenantMenu(int leaveID) {
    std::wcout  << L"\n\t\t1.Press 1 to rate the park: " ;

    int keuze = menuKeuze(1, 1);
    if (keuze == 1) {
        auto leaveAbonnee = huidigGebruiker->tenantLijst[leaveID];
        std::wstring comment;
        std::wstring score;
        std::wcout  << L"\n\t\tPlease leave a comment: " ;
        std::wcin.ignore();
        std::getline(std::wcin, comment);

        while (true) {
            std::wcout  << L"\n\t\tPlease leave a score: " ;
            std::wcin >> score;
            if (!isNumGeldig(score)) {
                continue;
            }
            if (std::stoi(score) < -10 || std::stoi(score) > 10) {
                std::wcout  << L"The rating scores can only be van -10 to 10: " ;
                continue;
            }else{
                break;
            }
        }

        huidigGebruiker->recensiePark(leaveAbonnee->occupyPark, std::stoi(score), comment);
        std::wcout  << L"\nPress 2 to back to the abonnee Menu: " ;
        if (menuKeuze(2, 2) == 2) {
            abonneeMenu();
        }

    }
}

inline void OnderliggendeBSysteem::toonAanvraagSent() {
    std::wcout  << L"\nEnter the index of aanvraag that you want to cancel:\n" ;
    std::wcout  << L"Lijst of the aanvraag you have sent: \n" ;
    huidigGebruiker->toonAanvraagSent();
    std::wcout  << huidigGebruiker->aanvraagLijst.size() + 1 << L".Back to Abonnee Menu\n" ;
    int keuze = menuKeuze(1, huidigGebruiker->aanvraagLijst.size() + 1);
    if (keuze == huidigGebruiker->aanvraagLijst.size() + 1) {
        abonneeMenu();
    } else {
        cancelAanvraagMenu(keuze);
    }

}

inline void OnderliggendeBSysteem::cancelAanvraagMenu(int ID) {
    std::wcout  << L"\nPress 1 to cancel the aanvraag\n" ;
    std::wcout  << L"\nPress 2 to back to toon aanvraag sent menu\n" ;
    int keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            for (auto i: parkVector) {
                for (int j = 0; j < i->lijstParkAanvraag.size(); j++) {
                    if (i->lijstParkAanvraag[j]->parkID == huidigGebruiker->aanvraagLijst[ID - 1]->parkID) {
                        i->lijstParkAanvraag.erase(i->lijstParkAanvraag.begin() + j);
                    }
                }
            }
            huidigGebruiker->cancelAanvraag(ID);
            std::wcout  << L"\nAanvraag canceled\nBack to menu:\n" ;
            toonAanvraagSent();
            break;

        case 2:
            toonAanvraagSent();
            break;
    }
}

inline void OnderliggendeBSysteem::searchValidParkMenu() {
    std::wstring beginDatum;
    std::wstring eindDatum;
    std::wstring locatie;
    Datum *eind, *begin;
    int keuze;
    std::wcout  << L"\tSearch for suitable parks: \n" ;
    std::wcout  << L"\t---1. Search by your begin day ---\n" << L"\t---2. Search by your eind day ---\n" ;
    switch (menuKeuze(1, 2)) {
        case 1:
            std::wcin.ignore();
            do {
                std::wcout  << L"Enter when you want to rent (dd/mm/yyyy): " ;
                std::getline(std::wcin, beginDatum);
            } while (!isDatumGeldig(beginDatum));
            std::wcout << beginDatum << L"\n";
            break;

        case 2:
            std::wcin.ignore();
            do {
                std::wcout  << L"Enter when you want to eind renting (dd/mm/yyyy): " ;
                std::getline(std::wcin, eindDatum);
            } while (!isDatumGeldig(eindDatum));
            break;
    }

    std::wcout  << L"\tKies the city you want to stay: \n\n" ;
    std::wcout  << L"\t1. BOOM \t2.WILLEBROEK \t3.RUMST\n" ;
    keuze = menuKeuze(1, 3);
    switch (keuze) {
        case 1:
            locatie = PLEKKEN[0];
            break;
        case 2:
            locatie = PLEKKEN[1];
            break;
        case 3:
            locatie = PLEKKEN[2];
            break;
    }

    if (eindDatum.length() == 0) {
        eind = nullptr;
    } else {
        eind = stringToDatum(eindDatum);
    }

    if (beginDatum.length() == 0) {
        begin = nullptr;
    } else {
        begin = stringToDatum(beginDatum);
    }

    validParkMenu(begin, eind, locatie);

}

inline void OnderliggendeBSysteem::validParkMenu(Datum *begin, Datum *eind, std::wstring locatie) {
    abonneeSuitableParkLijst.clear();
    Aanvraag *aanvraag;
    int keuze;
    if (eind == nullptr) {
        getGeldigeBeginParks(begin, locatie);
    } else {
        getGeldigeEndParks(eind, locatie);
    }
    std::wcout  << abonneeSuitableParkLijst.size() + 1 << L". Back to abonnee menu\n" ;
    keuze = menuKeuze(1, abonneeSuitableParkLijst.size() + 1);
    if (keuze == abonneeSuitableParkLijst.size() + 1) {

        abonneeMenu();
    } else {
        abonneeSuitableParkLijst[keuze - 1]->zieParkInfo();
        std::wcout  << L"\n\n--> 1.\tAanvraag to rent this park\n\n"
                  << L"--> 2.\tZie park's recensies\n\n"
                  << L"--> 3.\tBack to park lijst\n" ;
        switch (menuKeuze(1, 3)) {
            case 1: {
                if (eind == nullptr) {
                    aanvraag = new Aanvraag(begin, abonneeSuitableParkLijst[keuze - 1]->eindDatum, huidigGebruiker,
                                            abonneeSuitableParkLijst[keuze - 1]->parkID,
                                            AV_STATUS[0]);
                } else {
                    aanvraag = new Aanvraag(abonneeSuitableParkLijst[keuze - 1]->beginDatum, eind, huidigGebruiker,
                                            abonneeSuitableParkLijst[keuze - 1]->parkID,
                                            AV_STATUS[0]);
                }
                abonneeSuitableParkLijst[keuze - 1]->aanvraagToevoegenToParkAanvraagLijst(aanvraag);
                abonneeMenu();
                break; //function send aanvraags
            }
            case 2:
                std::wcout  << L"\nRecensies of the park you want: \n" ;
                abonneeSuitableParkLijst[keuze - 1]->zieParkRecensie();
                std::wcout  << L"\n4. Back to the aanvraag action menu: \n" ;
                if (menuKeuze(4, 4) == 4) {
                    validParkMenu(begin, eind, locatie);
                    break; //function zie recensies
                }


            case 3:
                validParkMenu(begin, eind, locatie);
                break;
        }
    }
}

inline void OnderliggendeBSysteem::actionAanvraagMenu(int aanvraagID) {
    std::wcout  << L"\n\n1.Toon Aanvraager Recensie\n2.Accept Aanvraag\n3.Decline Aanvraag\n" ;
    switch (menuKeuze(1, 3)) {
        case 1: {
            std::wcout  << L"\nThe recensie of your aanvraager is being toonn below: \n" ;
            auto aanvraager = huidigGebruiker->parkBeheerder->lijstParkAanvraag[aanvraagID]->aangevraagdByAbonnee;
            if (aanvraager->tenantRecensielijst.empty()) {
                std::wcout  << L"\nThere are no recensies for this abonnee\n" ;
                std::wcout  << L"4.Back to the Aanvraag Menu: \n" ;

                if (menuKeuze(4, 4) == 4) {
                    actionAanvraagMenu(aanvraagID);
                }
                break;
            } else {
                aanvraager->recensieTonen();
            }

            std::wcout  << L"4.Back to the Aanvraag Menu: \n" ;
            if (menuKeuze(4, 4) == 4) {
                actionAanvraagMenu(aanvraagID);
                break;
            }
        }
        case 2:
            if (!huidigGebruiker->acceptAanvraag(aanvraagID)) {
                std::wcout  << L"\n" << huidigGebruiker->parkBeheerder->lijstParkAanvraag.size() + 1
                          << L".Back to aanvraag menu\n" ;
                menuKeuze(huidigGebruiker->parkBeheerder->lijstParkAanvraag.size() + 1,
                           huidigGebruiker->parkBeheerder->lijstParkAanvraag.size() + 1);
                zieAanvraagMenu();
            } else {
                std::wcout  << L"\nAanvraag accepted\n" ;
                abonneeMenu();
                break;
            }
        case 3:
            //Return beheerder to aanvraag menu once there is no valid accept yet
            if (!huidigGebruiker->declineAanvraag(aanvraagID)) {
                std::wcout  << L"You can not decline a aanvraag that has been accpeted and declinded" ;
                std::wcout  << L"\n" << huidigGebruiker->parkBeheerder->lijstParkAanvraag.size() + 1
                          << L".Back to aanvraag menu\n" ;
                menuKeuze(huidigGebruiker->parkBeheerder->lijstParkAanvraag.size() + 1,
                           huidigGebruiker->parkBeheerder->lijstParkAanvraag.size() + 1);
                zieAanvraagMenu();
            } else {
                std::wcout  << L"\nAanvraag Declined\n" ;
                abonneeMenu();
                break;
            }

    }
}

inline void OnderliggendeBSysteem::zieUnratedTenantLijst() {
    std::wcout  << L"\n\t\tLijst of Unrated Occupiers: \n" ;
    if (huidigGebruiker->parkBeheerder->unratedTenant.empty()) {
        std::wcout  << L"\nThere are no tenants in your lijst\n" ;
        abonneeMenu();
    }
    huidigGebruiker->zieUnratedLijst();
    std::wcout  << L"\n" << huidigGebruiker->parkBeheerder->unratedTenant.size() + 1 << L".Back to abonnee menu" ;
    std::wcout  << L"\nKies the Tenant you would like to recensie: " ;
    int keuze = menuKeuze(1, huidigGebruiker->parkBeheerder->unratedTenant.size() + 1);

    if (keuze == huidigGebruiker->parkBeheerder->unratedTenant.size() + 1) {
        abonneeMenu();
    } else {
        std::wstring comment;
        std::wstring score;
        std::wcout  << L"\nPlease leave a comment to this tenant: " ;
        std::wcin.ignore();
        std::getline(std::wcin, comment);
        std::wcout  << L"\nPlease score the Tenant: " ;
        while (true) {
            std::wcout  << L"\n\t\tPlease leave a score: " ;
            std::wcin >> score;
            if (!isNumGeldig(score)) {
                continue;
            }
            if (std::stoi(score) < -10 || std::stoi(score) > 10) {
                std::wcout  << L"The rating scores can only be van -10 to 10: " ;
                continue;
            }else{
                break;
            }
        }
        huidigGebruiker->recensieTenant(keuze - 1, std::stoi(score), comment);
        abonneeMenu();
    }

}

inline void OnderliggendeBSysteem::zieAanvraagMenu() {
    int keuze;
    std::wcout  << L"\n\n\tYour aanvraag today:\n\n" ;
    if (huidigGebruiker->parkBeheerder == nullptr) {
        std::wcout  << L"You do not have a park. So you do not have any aanvraag! \n" ;
        abonneeMenu();
    } else {
        int numberAanvraag = huidigGebruiker->toonAanvragen();
        std::wcout  << L"\n\tKies your option:\n\n" ;
        std::wcout  << L"\n\n--> 1.\tPoint the Aanvraag:\n\n"
                  << L"--> 2.\tBack to Menu\n" ;
        keuze = menuKeuze(1, 3);
        switch (keuze) {
            case 1: {
                std::wcout  << L"Enter the aanvraag you want to proceed: \n" ;
                int newKeuze = menuKeuze(1, numberAanvraag);
                actionAanvraagMenu(newKeuze - 1);
                break;
            }
            case 2:
                abonneeMenu();
                break;
        }
    }

}

inline bool OnderliggendeBSysteem::abnAanvraagPark(Datum *beginDatum, Datum *eindDatum, int parkId) {
    if (parkId > abonneeSuitableParkLijst.size()) {
        return false;
    }

}

inline bool OnderliggendeBSysteem::isValidBeginParks(Datum *begin, Abonnee *abn, Park *park, std::wstring locatie) {

    int count = 0;
    if (!park->isToegevoegd) {
        return false;
    }

    if (park->parkStatus == STATUS[1]) {
        return false;
    }

    if (park == abn->parkBeheerder) {
        return false;
    }

    if (!isValidScore(abn, park)) {
        return false;
    }
    if (!isValidKrediet(abn, park)) {
        return false;
    }

    if (locatie != park->locatie) {
        return false;
    }

    if (park->beginDatum->datumNaarString() == begin->datumNaarString()) {
        return true;
    }
    return false;

}

inline bool OnderliggendeBSysteem::isValidEndParks(Datum *eind, Abonnee *abn, Park *park, std::wstring locatie) {
    if (!park->isToegevoegd) {
        return false;
    }

    if (park->parkStatus == STATUS[1]) {
        return false;
    }

    if (park == abn->parkBeheerder) {
        return false;
    }

    if (!isValidScore(abn, park)) {
        return false;
    }
    if (!isValidKrediet(abn, park)) {
        return false;
    }

    if (locatie != park->locatie) {
        return false;
    }


    if (park->eindDatum == eind) {
        return true;
    }

    return false;
}

inline bool OnderliggendeBSysteem::getGeldigeBeginParks(Datum *begin, std::wstring locatie) {
    abonneeSuitableParkLijst.clear();
    for (auto &park: parkVector) {
        if (isValidBeginParks(begin, huidigGebruiker, park, locatie)) {
            abonneeSuitableParkLijst.push_back(park);
        }
    }

    if (abonneeSuitableParkLijst.empty()) {
        std::wcout  << L"\nThere is no parks matched your search\n" ;
        return false;
    }

    std::wcout  << L"\nThe suitable park lijst:\n\n" ;
    for (int i = 0; i < abonneeSuitableParkLijst.size(); i++) {
        std::wcout  << L"--> " << i + 1 << L". " ;
        std::wcout  << L"Park Id: " << abonneeSuitableParkLijst[i]->parkID << L"\tLocatie: "
                  << abonneeSuitableParkLijst[i]->locatie << L"\tRating: "
                  << abonneeSuitableParkLijst[i]->getRatingScore() << L"\n" ;
    }
    std::wcout << L"\n\n";

    return true;
}

inline bool OnderliggendeBSysteem::getGeldigeEndParks(Datum *eind, std::wstring locatie) {
    abonneeSuitableParkLijst.clear();
    for (auto &park: parkVector) {
        if (isValidEndParks(eind, huidigGebruiker, park, locatie)) {

            abonneeSuitableParkLijst.push_back(park);
        }
    }

    if (abonneeSuitableParkLijst.empty()) {
        std::wcout  << L"\nThere is no parks matched your search\n" ;
        return false;
    }

    std::wcout  << L"\nThe suitable park lijst:\n\n" ;
    for (int i = 0; i < abonneeSuitableParkLijst.size(); i++) {
        std::wcout << L"--> " << i + 1 << L". ";
        std::wcout  << L"Park Id: " << abonneeSuitableParkLijst[i]->parkID << L"\tLocatie: "
                  << abonneeSuitableParkLijst[i]->locatie << L"\tRating: "
                  << abonneeSuitableParkLijst[i]->getRatingScore() << L"\n" ;
    }
    std::wcout << L"\n\n";

    return true;
}

inline bool OnderliggendeBSysteem::deleteInRentPark() {
    if (huidigGebruiker->deletePark()) {
        std::wcout  << L"\nSuccessfully omit the park\n" ;
        return true;
    } else {
        std::wcout  << L"The park have aanvraags hanging. Resolved all before omitting! \n" ;
        return false;
    }
}

inline void OnderliggendeBSysteem::inputParkToSys() {
    parkVector.clear();
    std::wstring gegLijn;
    std::wifstream bestandLezen{park_BESTAND};
    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << park_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";

    }
    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        auto *park = new Park(gegLijst[0], gegLijst[2], gegLijst[3]);
        parkVector.push_back(park);
    }
    bestandLezen.close();
}

inline void OnderliggendeBSysteem::inputBeheerderToSys() {

    std::wifstream bestandLezen{BEHEERDER_BESTAND};
    std::vector<std::wstring> gegLijst{};
    std::wstring gegLijn,gebruikersnaam,wachtw;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << BEHEERDER_BESTAND << L" niet openen. Probeer het eens opnnieuw.\n";
        return;  //  Als 't bestand iets problematisch heeft
    } else std::cout << L"\nAan het laden...\n";

    if (std::getline(bestandLezen, gegLijn)) {
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
    } else {
        std::wcerr << L"Kon uw beheerdergegevens niet lezen.\n";
        return; // Als je een foutieve lijn krijgt
    }

    if (static_cast<int>(gegLijst.size()) < 2) {
        std::wcerr << L"Data is in an incorrect format\n";
        return; // Return immediately if the necessary data is not present
    }
    gebruikersnaam = gegLijst[0];
    wachtw = gegLijst[1];

//    CANNOT DO Beheerder* bc declared at top Classe
    beheerder = new Beheerder(gebruikersnaam, wachtw);
}


inline void OnderliggendeBSysteem::inputParkLijstToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{park_LIJST_BESTAND};
    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << park_LIJST_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }
    Abonnee *beheerder;
    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        Datum *beginDatum = stringToDatum(gegLijst[2]);
        Datum *eindDatum = stringToDatum(gegLijst[3]);
        double krediets = std::stod(gegLijst[4]);
        double scores = std::stod(gegLijst[5]);
        std::wstring status = gegLijst[6];
        std::wstring beheerderId = gegLijst[1];
        for (Abonnee *abn: abonnees) {
            if (beheerderId == abn->abonneeId) {
                beheerder = abn;
            }
        }
        beheerder->parkToevoegen(beginDatum, eindDatum, krediets, scores, status);
    }
    bestandLezen.close();
}

inline void OnderliggendeBSysteem::inputAbnParkToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{park_BESTAND};
    Abonnee *targetAbn;
    Park *abnPark;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << park_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (Park *park: parkVector) {
            if (gegLijst[0] == park->parkID) {
                abnPark = park;
            }
        }
        for (Abonnee *abn: abonnees) {
            if (gegLijst[1] == abn->abonneeId) {
                targetAbn = abn;
            }
        }
        targetAbn->createPark(abnPark);
    }
    bestandLezen.close();

}

inline void OnderliggendeBSysteem::inputAbonneeToSys() {
    abonnees.clear();
    std::wstring gegLijn;
    std::wifstream bestandLezen{ABONNEES_BESTAND};

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << ABONNEES_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        auto *abonnee = new Abonnee(gegLijst[2], gegLijst[3], gegLijst[0], gegLijst[1],
                                  std::stod(gegLijst[5]), std::stod(gegLijst[6]), gegLijst[4]);
        abonnees.push_back(abonnee);
    }
    bestandLezen.close();
}


inline void OnderliggendeBSysteem::inputRatingTenantToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{RATING_TENANT_BESTAND};
    Abonnee *beCommentedAbn;
    Abonnee *commentAbn;


    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << RATING_park_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (auto abn: abonnees) {
            if (abn->abonneeId == gegLijst[1]) {
                beCommentedAbn = abn;
            }
        }
        for (auto abn2: abonnees) {
            if (abn2->abonneeId == gegLijst[0]) {
                commentAbn = abn2;
            }
        }


        auto abnRating = new Recensie(std::stod(gegLijst[2]), gegLijst[3], commentAbn);
        beCommentedAbn->tenantRecensielijst.push_back(abnRating);
    }

    bestandLezen.close();

}

inline void OnderliggendeBSysteem::outputRatingTenantNaarBestand() {
    std::wofstream bestandSchrijven{RATING_TENANT_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << RATING_TENANT_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    for (auto &abn: abonnees) {
        for (auto &abnRating: abn->tenantRecensielijst) {
            bestandSchrijven << abnRating->abonneeRecensie->abonneeId << SCHEIDER
                      << abn->abonneeId << SCHEIDER
                      << abnRating->ratingScore << SCHEIDER
                      << abnRating->comment << L"\n";
        }
    }
    bestandSchrijven.close();
}

inline void OnderliggendeBSysteem::outputRatingParkNaarBestand() {
    std::wofstream bestandSchrijven{RATING_park_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << RATING_park_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    for (auto &park: parkVector) {
        for (auto &abnRating: park->lijstParkRecensie) {
            bestandSchrijven << abnRating->abonneeRecensie->abonneeId << SCHEIDER
                      << park->parkID << SCHEIDER
                      << abnRating->ratingScore << SCHEIDER
                      << abnRating->comment << L"\n";
        }
    }
    bestandSchrijven.close();
}

inline void OnderliggendeBSysteem::inputRatingParkToSys() {
    std::wstring gegLijn;
    Abonnee *targetAbn;
    Park *abnPark;
    std::wifstream bestandLezen{RATING_park_BESTAND};
    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << RATING_park_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (auto abn: abonnees) {
            if (abn->abonneeId == gegLijst[0]) {
                targetAbn = abn;
            }
        }

        for (auto park: parkVector) {
            if (park->parkID == gegLijst[1]) {
                abnPark = park;
            }
        }

        double parkScore = std::stod(gegLijst[2]);
        std::wstring parkComment = gegLijst[3];

        auto parkRecensie = new Recensie(parkScore, parkComment, targetAbn);
        abnPark->recensieToevoegenToParkRecensielijst(parkRecensie);
    }
    bestandLezen.close();
}


inline void OnderliggendeBSysteem::inputAanvraagToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{AANVRAAG_BESTAND};
    Abonnee *targetAbn;
    Park *targetPark;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << AANVRAAG_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst;
        gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (Park *park: parkVector) {
            if (gegLijst[1] == park->parkID) {
                targetPark = park;
            }
        }
        for (Abonnee *abn: abonnees) {
            if (gegLijst[0] == abn->abonneeId) {
                targetAbn = abn;
            }
        }
        Datum *beginDatum = stringToDatum(gegLijst[2]);
        Datum *eindDatum = stringToDatum(gegLijst[3]);
        std::wstring status = gegLijst[4];
        Aanvraag *av = new Aanvraag(beginDatum, eindDatum, targetAbn, targetPark->parkID, status);
        targetPark->aanvraagToevoegenToParkAanvraagLijst(av);
        targetAbn->aanvraagLijst.push_back(av);
    }
    bestandLezen.close();
}

inline void OnderliggendeBSysteem::inputOccupierToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{OCCUPIERS_BESTAND};
    Abonnee *targetAbn;
    Park *targetPark;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << OCCUPIERS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (auto &abn: abonnees) {
            if (abn->abonneeId == gegLijst[0]) {
                targetAbn = abn;
            }
        }
        for (auto &park: parkVector) {
            if (park->parkID == gegLijst[1]) {
                targetPark = park;
            }
        }
        Datum *begin = stringToDatum(gegLijst[2]);
        Datum *eind = stringToDatum(gegLijst[3]);

        auto *occupyPark = new OccupyPark(begin, eind, targetAbn);
        auto *occupyAbn = new Tenant(begin, eind, targetPark);

        targetAbn->tenantLijst.push_back(occupyAbn);
        targetPark->lijstOccupyPark.push_back(occupyPark);
    }
}

inline void OnderliggendeBSysteem::inputUnratedToSys() {
    std::wstring gegLijn;
    std::wifstream bestandLezen{UNRATED_OCC_BESTAND};
    Abonnee *targetAbn;
    Park *targetPark;

    if (!bestandLezen.is_open()) {
        std::wcerr << L"Kan bestand " << UNRATED_OCC_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    while (std::getline(bestandLezen, gegLijn)) {
        std::vector<std::wstring> gegLijst = mijnStrTok(gegLijn, SCHEIDER);
        for (auto &abn: abonnees) {
            if (abn->abonneeId == gegLijst[1]) {
                targetAbn = abn;
            }
        }
        for (auto &park: parkVector) {
            if (park->parkID == gegLijst[0]) {
                targetPark = park;
            }
        }
        Datum *begin = stringToDatum(gegLijst[2]);
        Datum *eind = stringToDatum(gegLijst[3]);

        auto *unratedOcc = new OccupyPark(begin, eind, targetAbn);
        targetPark->unratedTenant.push_back(unratedOcc);
    }
}

inline void OnderliggendeBSysteem::outputOccupierNaarBestand() {
    std::wofstream bestandSchrijven{OCCUPIERS_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << OCCUPIERS_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    for (auto &abn: abonnees) {
        for (auto &abnOccupy: abn->tenantLijst) {
            bestandSchrijven << abn->abonneeId << SCHEIDER
                      << abnOccupy->occupyPark->parkID << SCHEIDER
                      << abnOccupy->beginVanafDatum->datumNaarString() << SCHEIDER
                      << abnOccupy->ToDatum->datumNaarString() << L"\n";
        }
    }
    bestandSchrijven.close();
}

inline void OnderliggendeBSysteem::outputBeheerderNaarBestand() {
    std::wofstream bestandSchrijven{BEHEERDER_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << BEHEERDER_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    bestandSchrijven << beheerder->gebruikersnaam << SCHEIDER
              << beheerder->wachtwoord << L"\n";
}

inline void OnderliggendeBSysteem::outputUnratedNaarBestand() {
    std::wofstream bestandSchrijven{UNRATED_OCC_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << UNRATED_OCC_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    for (auto &park: parkVector) {
        for (auto &unratedOcc: park->unratedTenant) {
            bestandSchrijven << park->parkID << SCHEIDER
                      << unratedOcc->tenant->abonneeId << SCHEIDER
                      << unratedOcc->beginVanafDatum->datumNaarString() << SCHEIDER
                      << unratedOcc->toDatum->datumNaarString() << L"\n";
        }
    }
    bestandSchrijven.close();
}

inline void OnderliggendeBSysteem::outputAanvraagNaarBestand() {
    std::wofstream bestandSchrijven{AANVRAAG_BESTAND};

    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << AANVRAAG_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
    }

    for (auto &park: parkVector) {
        for (auto &abnAanvraag: park->lijstParkAanvraag) {
            bestandSchrijven << abnAanvraag->aangevraagdByAbonnee->abonneeId << SCHEIDER
                      << park->parkID << SCHEIDER
                      << abnAanvraag->beginDatum->datumNaarString() << SCHEIDER
                      << abnAanvraag->eindDatum->datumNaarString() << SCHEIDER
                      << abnAanvraag->aanvraagStatus << L"\n";
        }
    }
    bestandSchrijven.close();
}

inline void OnderliggendeBSysteem::outputParkLijstNaarBestand() {
    std::wofstream bestandSchrijven{park_LIJST_BESTAND};
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << park_LIJST_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }

    for (auto abn: abonnees) {
        if (abn->parkBeheerder == nullptr) {
            continue;
        }
        if (!abn->parkBeheerder->isToegevoegd) {
            continue;
        }

        bestandSchrijven << abn->parkBeheerder->parkID << SCHEIDER
                  << abn->abonneeId << SCHEIDER
                  << abn->parkBeheerder->beginDatum->datumNaarString() << SCHEIDER
                  << abn->parkBeheerder->eindDatum->datumNaarString() << SCHEIDER
                  << abn->parkBeheerder->consumingPointsPerDay << SCHEIDER
                  << abn->parkBeheerder->minRating << SCHEIDER
                  << abn->parkBeheerder->parkStatus << L"\n";
    }
    bestandSchrijven.close();
}

inline void OnderliggendeBSysteem::outputAbonneeNaarBestand() {
    std::wofstream bestandSchrijven{ABONNEES_BESTAND, std::ios::app}; // Append mode
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << ABONNEES_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }

    for (auto &abn: abonnees) {
        bestandSchrijven << abn->abonneeId << SCHEIDER
                  << abn->mail << SCHEIDER
                  << abn->gebruikersnaam << SCHEIDER
                  << abn->wachtwoord << SCHEIDER
                  << abn->locatie << SCHEIDER
                  << abn->krediet << SCHEIDER
                  << abn->getRatingScore() << L"\n";
    }

    bestandSchrijven.close();
}
//FUN OVER
inline void OnderliggendeBSysteem::outputAbonneeNaarBestand(std::vector<Abonnee *> newabonnee) {
    std::wofstream bestandSchrijven{ABONNEES_BESTAND, std::ios::app}; // Append mode
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << ABONNEES_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }

        bestandSchrijven << newabonnee[0]->abonneeId << SCHEIDER
                  << newabonnee[0]->mail << SCHEIDER
                  << newabonnee[0]->gebruikersnaam << SCHEIDER
                  << newabonnee[0]->wachtwoord << SCHEIDER
                  << newabonnee[0]->locatie << SCHEIDER
                  << newabonnee[0]->krediet << SCHEIDER
                  << newabonnee[0]->getRatingScore() << L"\n";

    bestandSchrijven.close();
}

inline void OnderliggendeBSysteem::outputParkNaarBestand() {
    std::wofstream bestandSchrijven{park_BESTAND};
    if (!bestandSchrijven.is_open()) {
        std::wcerr << L"Kan bestand " << park_BESTAND << L"niet openen. Doe eens opnieuw\n" L"\n";
        return;
    }
    for (Park *park: parkVector) {
        bestandSchrijven << park->parkID << SCHEIDER
                  << park->beheerder->abonneeId << SCHEIDER
                  << park->locatie << SCHEIDER
                  << park->parkDescription << SCHEIDER
                  << park->getRatingScore() << L"\n";
    }
    bestandSchrijven.close();


}


inline bool OnderliggendeBSysteem::abonneeInloggen(std::wstring gebruikersnaam, std::wstring wachtwoord) {
    int count = 0;
    for (Abonnee *abn: abonnees) {
//        std::cout << (abn->gebruikersnaam == gebruikersnaam) << (abn->wachtwoord == wachtwoord);
        if (abn->gebruikersnaam == gebruikersnaam && abn->wachtwoord == wachtwoord) {
            huidigGebruiker = abn;
            for (std::wstring loc: PLEKKEN) {
                if (loc == huidigGebruiker->locatie) {
                    count++;
                    break;
                }
            }
            if (count == 0) {
                std::wcout  << L"The app do not support you in your region! \n" ;
                hoofdScherm();
                return false;
            }
            std::wcout  << L"U bent in het systeem...laden...\n\n" ;
            return true;
        }
    }
    std::wcout  << L"\n\nWrong gebruikersnaam or wachtwoord!!! \n" ;
    return false;
}

inline void OnderliggendeBSysteem::abonneeRegistreren() {
    int keuze;
    int subKeuze;
    std::wstring gebruikersnaam, wachtwoord, umail, locatie;
    std::vector<Abonnee*> newlyRegisteredAbnVector{};
    std::wcout  << L"\t---ABONNEE REGISTRATIE---\n" ;
    std::wcin.ignore();
    do {
        std::wcout  << LR"(Uw gebruikersnaam invoeren:   )" ;
        getline(std::wcin, gebruikersnaam);
    } while (!isGebrGeldig(gebruikersnaam));

    do {
        std::wcout  << LR"(Uw wachtwoord invoeren:   )" ;
        getline(std::wcin, wachtwoord);
    } while (!isWachtGeldig(wachtwoord));
// TODO implement email ipv umail
    do {
        std::wcout  << LR"(Uw e-mail invoeren:   )" ;
        getline(std::wcin, umail);
    } while (!geldigeMail(umail));


    std::wcout  << L"1. Kies the locaties the app support \n" ;
    std::wcout  << L"2. Enter the locatie yourself \n" ;
    keuze = menuKeuze(1, 2);
    switch (keuze) {
        case 1:
            std::wcout  << L"Kies een van de volgende locaties: \n" ;
            std::wcout  << L"1.BOOM\t2.WILLEBROEK\t3.RUMST\n" ;
            subKeuze = menuKeuze(1, 3);
            switch (subKeuze) {
                case 1:
                    locatie = PLEKKEN[0];
                    break;
                case 2:
                    locatie = PLEKKEN[1];
                    break;
                case 3:
                    locatie = PLEKKEN[2];
                    break;
            }
            break;
        case 2:
            std::wcin.ignore();
            std::wcout  << LR"(Uw locatie invoeren:   )" ;
            getline(std::wcin, locatie);
            break;
    }
    Abonnee *newAbn = new Abonnee(gebruikersnaam, wachtwoord, L"ABN" + std::to_wstring(abonnees.size() + 1), umail,
                                OORSPRONKELIJKE_KREDIETEN, OORSPRONKELIJKE_SCORES, locatie);
    newlyRegisteredAbnVector.push_back(newAbn);
//    flush ASAP w fun overloading
    outputAbonneeNaarBestand(newlyRegisteredAbnVector);
    std::wcout  << L"Registratie ging oke.\n" ;
    hoofdScherm();
}

inline Datum *OnderliggendeBSysteem::stringToDatum(std::wstring &datum) {
    std::vector<std::wstring> gegLijst = mijnStrTok(datum, '/');
    Datum *geconverteerdeDatum = new Datum(std::stoi(gegLijst[0]), std::stoi(gegLijst[1]), std::stoi(gegLijst[2]));
    return geconverteerdeDatum;

}
