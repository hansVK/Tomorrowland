
//
// Created by r0834721 on 31/7/2023
//

#ifndef TOMORROWLAND_TENANT_H
#define TOMORROWLAND_TENANT_H
class Datum;
class Park;

class Tenant {
    Datum *beginVanafDatum;
    Datum *ToDatum;
    Park *occupyPark;

public:
   Tenant(Datum *occupyVanDatum, Datum *occupyToDatum, Park *occupyPark);

    friend class Abonnee;

    friend class Park;

    friend class OnderliggendeBSysteem;


};
#endif //TOMORROWLAND_TENANT_H
