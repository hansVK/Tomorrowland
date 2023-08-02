//
// Created by r0834721 on 31/7/2023
//

#ifndef TOMORROWLAND_OCCUPYPARK_H
#define TOMORROWLAND_OCCUPYPARK_H

class Datum;

class Abonnee;

class OccupyPark {
private:
    Datum *beginVanafDatum;
    Datum *toDatum;
    Abonnee *tenant;
public:
    OccupyPark(Datum *beginVanafDatum, Datum *toDatum, Abonnee *tenant);

    friend class OnderliggendeBSysteem;

    friend class Park;

    friend class Abonnee;

};
#endif //TOMORROWLAND_OCCUPYPARK_H
