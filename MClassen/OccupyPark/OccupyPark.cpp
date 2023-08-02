//
// Created by r0834721 on 31/7/2023
//

#include "OccupyPark.h"
OccupyPark::OccupyPark(Datum *beginVanafDatum, Datum *toDatum, Abonnee *tenant)
        : beginVanafDatum(beginVanafDatum),
          toDatum(toDatum),
          tenant(tenant)
{
}
