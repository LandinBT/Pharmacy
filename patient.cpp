#include "patient.hpp"
using namespace std;

Patient::Patient() {}

Patient::Patient(const Patient& p) : socSecNum(p.socSecNum), name(p.name),
    birth(p.birth), address(p.address), phoneNum(p.phoneNum) {}

Patient& Patient::operator=(const Patient& p) {
    socSecNum=p.socSecNum;
    name=p.name;
    birth=p.birth;
    address=p.address;
    phoneNum=p.phoneNum;

    return *this;
    }

string Patient::getSocSecNum() const {
    return socSecNum;
    }

Name Patient::getName() const {
    return name;
    }

Date Patient::getBirth() const {
    return birth;
    }

Address Patient::getAddress() const {
    return address;
    }

long Patient::getPhoneNum() const {
    return phoneNum;
    }

string Patient::toString() const {
    return socSecNum+" | "+
           name.toString()+" | "+
           birth.toString()+" | "+
           address.toString()+" | "+
           to_string(phoneNum);
    }

void Patient::setSocSecNum(const string& ssn) {
    socSecNum=ssn;
    }

void Patient::setName(const Name& n) {
    name=n;
    }

void Patient::setBirth(const Date& d) {
    birth=d;
    }

void Patient::setAddress(const Address& a) {
    address=a;
    }

void Patient::setPhoneNum(const long& pn) {
    phoneNum=pn;
    }

bool Patient::operator==(const Patient& p) const {
    return socSecNum==p.socSecNum;
    }

bool Patient::operator!=(const Patient& p) const {
    return !(*this==p);
    }

bool Patient::operator<(const Patient& p) const {
    return socSecNum<p.socSecNum;
    }

bool Patient::operator<=(const Patient& p) const {
    return *this<p or *this==p;
    }

bool Patient::operator>(const Patient& p) const {
    return !(*this<=p);
    }

bool Patient::operator>=(const Patient& p) const {
    return !(*this<p);
    }

istream& operator>>(istream& is, Patient& p) {
    string str;

    getline(is, p.socSecNum, '*');
    is >> p.name;
    is >> p.birth;
    is >> p.address;
    getline(is, str, '*');
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    p.phoneNum = stol(str);

    return is;
    }

ostream& operator<<(ostream& os, const Patient& p) {
    os<<p.socSecNum<<"*";
    os<<p.name;
    os<<p.birth;
    os<<p.address;
    string str=to_string(p.phoneNum);
    str.insert(2, " ");
    str.insert(7, " ");
    os<<str<<"*";

    return os;
    }
