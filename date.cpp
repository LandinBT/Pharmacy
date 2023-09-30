#include "date.hpp"
using namespace std;

int Date::toInt() const {
    return year*10000+month*100+day;
    }

bool Date::isValid() const {
    return day>0 and day<=31 and month>0 and month<=12 and year>1980 and year<=2080;
    }

Date::Date() {}

Date::Date(const Date& d) : day(d.day), month(d.month), year(d.year) {}

Date& Date::operator=(const Date& d) {
    day=d.day;
    month=d.month;
    year=d.year;

    return *this;
    }

int Date::getDay() const {
    return day;
    }

int Date::getMonth() const {
    return month;
    }

int Date::getYear() const {
    return year;
    }

string Date::toString() const {
    return to_string(day)+"/"+to_string(month)+"/"+to_string(year);
    }

void Date::setDay(const int& d) {
    day=d;
    }

void Date::setMonth(const int& m) {
    month=m;
    }

void Date::setYear(const int& y) {
    year=y;
    }

bool Date::operator==(const Date& d) const {
    return toInt()==d.toInt();
    }

bool Date::operator!=(const Date& d) const {
    return !(*this==d);
    }

bool Date::operator<(const Date& d) const {
    return toInt()<d.toInt();
    }

bool Date::operator<=(const Date& d) const {
    return *this<d or *this==d;
    }

bool Date::operator>(const Date& d) const {
    return !(*this<=d);
    }

bool Date::operator>=(const Date& d) const {
    return !(*this<d);
    }

istream& operator>>(istream& is, Date& d) {
    string str;

    getline(is, str, '*');

    stringstream strStream(str);

    getline(strStream, str, '/');
    d.day=stoi(str);

    getline(strStream, str, '/');
    d.month=stoi(str);

    getline(strStream, str);
    d.year=stoi(str);

    return is;
    }

ostream& operator<<(ostream& os, const Date& d) {
    os<<d.day<<"/";
    os<<d.month<<"/";
    os<<d.year<<"*";

    return os;
    }
