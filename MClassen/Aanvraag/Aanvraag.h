
#ifndef AANVRAAG_H
#define AANVRAAG_H
#include <iostream>
#include "../Datum/Datum.h"
//#include "../Abonnee/Abonnee.h"

class Datum;
class Abonnee;

class Aanvraag {
    std::wstring parkID;
    std::wstring aanvraagStatus;
    Datum* beginDatum;
    Datum* eindDatum;
    Abonnee* aangevraagdByAbonnee;

public:

    Aanvraag(Datum *beginDatum, Datum *eindDatum, Abonnee *aangevraagdByAbonnee, std::wstring parkId, std::wstring status);


    friend class OnderliggendeBSysteem;

    friend class Abonnee;


};

#endif



