#include "medication.hpp"
using namespace std;

Medication::Medication() {}

Medication::Medication(const Medication& m) : code(m.code), name(m.name) {}

Medication& Medication::operator=(const Medication& m) {
    code=m.code;
    name=m.name;

    return *this;
    }

string Medication::getCode() const {
    return code;
    }

string Medication::getName() const {
    return name;
    }

string Medication::toString() const {
    return code+" | "+name;
    }

void Medication::setCode(const string& c) {
    code=c;
    }

void Medication::setName(const string& n) {
    name=n;
    }

bool Medication::operator==(const Medication& m) const {
    return code==m.code;
    }

bool Medication::operator!=(const Medication& m) const {
    return !(*this==m);
    }

bool Medication::operator<(const Medication& m) const {
    return code<m.code;
    }

bool Medication::operator<=(const Medication& m) const {
    return *this<m or *this==m;
    }

bool Medication::operator>(const Medication& m) const {
    return !(*this<=m);
    }

bool Medication::operator>=(const Medication& m) const {
    return !(*this<m);
    }

istream& operator>>(istream& is, Medication& m) {
    getline(is, m.code, '*');
    getline(is, m.name, '*');

    return is;
    }

ostream& operator<<(ostream& os, const Medication& m) {
    os<<m.code<<"*";
    os<<m.name<<"*";

    return os;
    }
