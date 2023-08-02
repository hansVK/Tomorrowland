
#include "Datum.h"
//#include "../../OnderliggendeBSysteem/OnderliggendeBSysteem.h"
#include "../../vast.h"
Datum::Datum(int datum, int month, int jaar)
        : datum(datum),
          month(month),
          jaar(jaar)
{
}




int Datum:: countSchrikkeljaar() {
    int huidigJaar = this->jaar;
    if(this->month <= 2) {
        huidigJaar--;
    }

    int Schrikkeljaar = huidigJaar / 4 - huidigJaar / 100 + huidigJaar / 400;
    return Schrikkeljaar;
}

int Datum::countDatum() {
    int aantalDagen = this->jaar * 365 + this->datum;

    for(int i = 0; i < this->month - 1; i++) {
        aantalDagen = aantalDagen + DAG_VSCH_MAAND[i];
    }

    aantalDagen = aantalDagen + this->countSchrikkeljaar();
    return aantalDagen;
}

bool Datum::operator < (Datum &datum2) {

    return  countDatum() - datum2.countDatum() >= 0;
}

int Datum::operator - (Datum &datum2) {
    // Get the difference between two datums
    std::wcout << this->countDatum() << L"\n";
    std::wcout << datum2.countDatum() << L"\n";

    return this->countDatum() - datum2.countDatum();
}

std::wstring Datum ::datumNaarString() {
    std::wstringstream ss;
    ss << datum << L"/" << month << L"/" << jaar;
    return ss.str();
}

