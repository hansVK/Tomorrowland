#ifndef TOMORROWLAND_DATUM_H
#define TOMORROWLAND_DATUM_H
#include <iostream>
#include <sstream>
#define SIZE 50


class Datum {
    private:
        int datum;
        int month;
        int jaar;
    public:
        Datum();
        Datum(int datum, int month, int jaar);
        int getDay();
        int countSchrikkeljaar();
        int countDatum();
        bool operator < (Datum &datum2);
        int operator - (Datum &datum2);
        std::wstring datumNaarString();
        friend class OnderliggendeBSysteem;
};
#endif

