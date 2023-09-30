#include "doctor.hpp"
using namespace std;

Doctor::Doctor() {}

Doctor::Doctor(const Doctor& d) : empCode(d.empCode), name(d.name),
    certificate(d.certificate), arrival(d.arrival), departure(d.departure) {}

Doctor& Doctor::operator=(const Doctor& d) {
    empCode=d.empCode;
    name=d.name;
    certificate=d.certificate;
    arrival=d.arrival;
    departure=d.departure;

    return *this;
    }

string Doctor::getEmpCode() const {
    return empCode;
    }

Name Doctor::getName() const {
    return name;
    }

string Doctor::getCertificate() const {
    return certificate;
    }

Time Doctor::getArrival() const {
    return arrival;
    }

Time Doctor::getDeparture() const {
    return departure;
    }

string Doctor::toString() const {
    return empCode+" | "+
           name.toString()+" | "+
           certificate+" | "+
           arrival.toString()+" | "+
           departure.toString();
    }

void Doctor::setEmpCode(const string& ec) {
    empCode=ec;
    }

void Doctor::setName(const Name& n) {
    name=n;
    }

void Doctor::setCertificate(const string& c) {
    certificate=c;
    }

void Doctor::setArrival(const Time& a) {
    arrival=a;
    }

void Doctor::setDeparture(const Time& d) {
    departure=d;
    }

bool Doctor::operator==(const Doctor& d) const {
    return empCode==d.empCode;
    }

bool Doctor::operator!=(const Doctor& d) const {
    return !(*this==d);
    }

bool Doctor::operator<(const Doctor& d) const {
    return empCode<d.empCode;
    }

bool Doctor::operator<=(const Doctor& d) const {
    return *this<d or *this==d;
    }

bool Doctor::operator>(const Doctor& d) const {
    return !(*this<=d);
    }

bool Doctor::operator>=(const Doctor& d) const {
    return !(*this<d);
    }

istream& operator>>(istream& is, Doctor& d) {
    getline(is, d.empCode, '*');
    is>>d.name;
    getline(is, d.certificate, '*');
    is>>d.arrival;
    is>>d.departure;

    return is;
    }

ostream& operator<<(ostream& os, const Doctor& d) {
    os<<d.empCode<<"*";
    os<<d.name;
    os<<d.certificate<<"*";
    os<<d.arrival;
    os<<d.departure;

    return os;
    }
