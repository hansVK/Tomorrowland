//
// Created by r0834721 on 31/7/2023
//

#include "Tenant.h"
Tenant::Tenant(Datum *occupyVanDatum, Datum *occupyToDatum, Park *occupyPark)
        : beginVanafDatum(occupyVanDatum),
          ToDatum(occupyToDatum),
          occupyPark(occupyPark)
{
}

