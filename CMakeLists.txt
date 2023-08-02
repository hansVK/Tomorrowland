cmake_minimum_required(VERSION 3.20)
project(TOMORROWLAND)

set(CMAKE_CXX_STANDARD 14)

include_directories(OnderliggendeBSysteem)

add_executable(TOMORROWLAND
        main.cpp
        MClassen/Beheerder/Beheerder.cpp
        MClassen/Recensie/Recensie.cpp
        MClassen/Recensie/Recensie.h
        MClassen/Aanvraag/Aanvraag.h
        MClassen/Aanvraag/Aanvraag.cpp
        MClassen/Datum/Datum.cpp
        MClassen/Datum/Datum.h
        OnderliggendeBSysteem/OnderliggendeBSysteem.cpp
        OnderliggendeBSysteem/OnderliggendeBSysteem.h
        MClassen/Abonnee/Abonnee.cpp
        MClassen/Abonnee/Abonnee.h
        MClassen/Gebruiker/Gebruiker.h
        MClassen/Gebruiker/Gebruiker.cpp
        MClassen/Park/Park.h
        MClassen/Park/Park.cpp
        MClassen/Beheerder/Beheerder.h
        MClassen/OccupyPark/OccupyPark.h
        MClassen/OccupyPark/OccupyPark.cpp
        MClassen/Tenant/Tenant.h
        MClassen/Tenant/Tenant.cpp
        vast.h MClassen/Beheerder/Beheerder.cpp MClassen/Beheerder/Beheerder.h
)