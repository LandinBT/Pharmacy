#include "name.hpp"
using namespace std;

Name::Name() {}

Name::Name(const Name& n) : last(n.last), first(n.first) {}

Name& Name::operator=(const Name& n) {
    last=n.last;
    first=n.first;

    return *this;
    }

string Name::getLast() const {
    return last;
    }

string Name::getFirst() const {
    return first;
    }

string Name::toString() const {
    return last+", "+first;
    }

void Name::setLast(const string& l) {
    last=l;
    }

void Name::setFirst(const string& f) {
    first=f;
    }

bool Name::operator==(const Name& n) const {
    return toString()==n.toString();
    }

bool Name::operator!=(const Name& n) const {
    return !(*this==n);
    }

bool Name::operator<(const Name& n) const {
    return toString()<n.toString();
    }

bool Name::operator<=(const Name& n) const {
    return *this<n or *this==n;
    }

bool Name::operator>(const Name& n) const {
    return !(*this<=n);
    }

bool Name::operator>=(const Name& n) const {
    return !(*this<n);
    }

istream& operator>>(istream& is, Name& n) {
    getline(is, n.last, '*');
    getline(is, n.first, '*');

    return is;
    }

ostream& operator<<(ostream& os, const Name& n) {
    os<<n.last<<"*";
    os<<n.first<<"*";

    return os;
    }
