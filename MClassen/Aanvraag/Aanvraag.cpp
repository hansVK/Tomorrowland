
#include "Aanvraag.h"


Aanvraag::Aanvraag(Datum *beginDatum, Datum *eindDatum, Abonnee *aangevraagdByAbonnee, std::wstring parkId, std::wstring status)
        : beginDatum(beginDatum),
          eindDatum(eindDatum),
          aangevraagdByAbonnee(aangevraagdByAbonnee),
          aanvraagStatus(status),
          parkID(parkId)
{
    // Note: need a function van systeem to get id of aanvraag
}


