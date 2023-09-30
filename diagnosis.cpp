#include "diagnosis.hpp"
using namespace std;

Diagnosis::Diagnosis() {}

Diagnosis::Diagnosis(const Diagnosis& d) : code(d.code), desc(d.desc) {}

Diagnosis& Diagnosis::operator=(const Diagnosis& d) {
    code=d.code;
    desc=d.desc;

    return *this;
    }

string Diagnosis::getCode() const {
    return code;
    }

string Diagnosis::getDesc() const {
    return desc;
    }

string Diagnosis::toString() const {
    return code+" | "+desc;
    }

void Diagnosis::setCode(const string& c) {
    code=c;
    }

void Diagnosis::setDesc(const string& d) {
    desc=d;
    }

bool Diagnosis::operator==(const Diagnosis& d) const {
    return code==d.code;
    }

bool Diagnosis::operator!=(const Diagnosis& d) const {
    return !(*this==d);
    }

bool Diagnosis::operator<(const Diagnosis& d) const {
    return code<d.code;
    }

bool Diagnosis::operator<=(const Diagnosis& d) const {
    return *this<d or *this==d;
    }

bool Diagnosis::operator>(const Diagnosis& d) const {
    return !(*this<=d);
    }

bool Diagnosis::operator>=(const Diagnosis& d) const {
    return !(*this<d);
    }

istream& operator>>(istream& is, Diagnosis& d) {
    getline(is, d.code, '*');
    getline(is, d.desc, '*');

    return is;
}

ostream& operator<<(ostream& os, const Diagnosis& d) {
    os<<d.code<<"*";
    os<<d.desc<<"*";

    return os;
}
