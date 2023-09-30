#include "address.hpp"
using namespace std;

Address::Address() {}

Address::Address(const Address& a) : street(a.street), houseNum(a.houseNum),
    colony(a.colony), zipCode(a.zipCode), locality(a.locality) {}

Address& Address::operator=(const Address& a) {
    street=a.street;
    houseNum=a.houseNum;
    colony=a.colony;
    zipCode=a.zipCode;
    locality=a.locality;

    return *this;
    }

string Address::getStreet() const {
    return street;
    }

int Address::getHouseNum() const {
    return houseNum;
    }

string Address::getColony() const {
    return colony;
    }

int Address::getZipCode() const {
    return zipCode;
    }

string Address::getLocality() const {
    return locality;
    }

string Address::toString() const {
    return street+" | "+
           to_string(houseNum)+" | "+
           colony+" | "+
           to_string(zipCode)+" | "+
           locality;
    }

void Address::setStreet(const string& s) {
    street=s;
    }

void Address::setHouseNum(const int& hn) {
    houseNum=hn;
    }

void Address::setColony(const string& c) {
    colony=c;
    }

void Address::setZipCode(const int& zc) {
    zipCode=zc;
    }

void Address::setLocality(const string& l) {
    locality=l;
    }

bool Address::operator==(const Address& a) const {
    return toString()==a.toString();
    }

bool Address::operator!=(const Address& a) const {
    return !(*this==a);
    }

bool Address::operator<(const Address& a) const {
    return toString()<a.toString();
    }

bool Address::operator<=(const Address& a) const {
    return *this<a or *this==a;
    }

bool Address::operator>(const Address& a) const {
    return !(*this<=a);
    }

bool Address::operator>=(const Address& a) const {
    return !(*this<a);
    }

istream& operator>>(istream& is, Address& a) {
    string str;

    getline(is, a.street, '*');

    getline(is, str, '*');
    a.houseNum=stoi(str);

    getline(is, a.colony, '*');

    getline(is, str, '*');
    a.zipCode=stoi(str);

    getline(is, a.locality, '*');

    return is;
    }

ostream& operator<<(ostream& os, const Address& a) {
    os<<a.street<<"*";
    os<<a.houseNum<<"*";
    os<<a.colony<<"*";
    os<<a.zipCode<<"*";
    os<<a.locality<<"*";

    return os;
    }
