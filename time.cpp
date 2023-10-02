#include "time.hpp"
using namespace std;

int Time::toInt() const {
    return hour*100+minute;
    }

bool Time::isValid() const {
    return minute<=0 and minute>60 and hour<=0 and hour>24;
    }

Time::Time() {}

Time::Time(const Time& t) : hour(t.hour), minute(t.minute) {}

Time& Time::operator=(const Time& t) {
    minute=t.minute;
    hour=t.hour;

    return *this;
    }

int Time::getHour() const {
    return hour;
    }

int Time::getMinute() const {
    return minute;
    }

string Time::toString() const {
    string hourStr = (hour < 10) ? "0" + to_string(hour) : to_string(hour);
    string minuteStr = (minute < 10) ? "0" + to_string(minute) : to_string(minute);

    return hourStr + ":" + minuteStr;
    }

void Time::setHour(const int& h) {
    hour=h;
    }

void Time::setMinute(const int& m) {
    minute=m;
    }

bool Time::operator==(const Time& t) const {
    return toInt()==t.toInt();
    }

bool Time::operator!=(const Time& t) const {
    return !(*this==t);
    }

bool Time::operator<(const Time& t) const {
    return toInt()<t.toInt();
    }

bool Time::operator<=(const Time& t) const {
    return *this<t or *this==t;
    }

bool Time::operator>(const Time& t) const {
    return !(*this<=t);
    }

bool Time::operator>=(const Time& t) const {
    return !(*this<t);
    }

istream& operator>>(istream& is, Time& t) {
    string str;

    getline(is, str, '*');

    istringstream strStream(str);

    getline(strStream, str, ':');
    t.hour=stoi(str);

    getline(strStream, str);
    t.minute=stoi(str);

    return is;
    }

ostream& operator<<(ostream& os, const Time& t) {
    os<<setw(2)<<setfill('0')<<t.hour<<":";
    os<<setw(2)<<setfill('0')<<t.minute<<"*";

    return os;
    }
