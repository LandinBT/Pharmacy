#include "consultation.hpp"
using namespace std;

Consultation::Consultation() {}

Consultation::Consultation(const Consultation& c) : date(c.date), time(c.time),
    diagnosisCode(c.diagnosisCode), therapIndic(c.therapIndic),
    doctorEmpCode(c.doctorEmpCode), patientSSN(c.patientSSN),
    med1Code(c.med1Code), med2Code(c.med2Code), med3Code(c.med3Code) {}

Consultation Consultation::operator=(const Consultation& c) {
    date=c.date;
    time=c.time;
    diagnosisCode=c.diagnosisCode;
    therapIndic=c.therapIndic;
    doctorEmpCode=c.doctorEmpCode;
    patientSSN=c.patientSSN;
    med1Code=c.med1Code;
    med2Code=c.med2Code;
    med3Code=c.med3Code;

    return *this;
    }

Date Consultation::getDate() const {
    return date;
    }

Time Consultation::getTime() const {
    return time;
    }

string Consultation::getDiagnosisCode() const {
    return diagnosisCode;
    }

string Consultation::getTherapIndic() const {
    return therapIndic;
    }

string Consultation::getDoctorEmpCode() const {
    return doctorEmpCode;
    }

string Consultation::getPatientSSN() const {
    return patientSSN;
    }

string Consultation::getMed1Code() const {
    return med1Code;
    }

string Consultation::getMed2Code() const {
    return med2Code;
    }

string Consultation::getMed3Code() const {
    return med3Code;
    }

string Consultation::toString() const {
    return date.toString()+"\n"+
           time.toString()+"\n"+
           diagnosisCode+"\n"+
           therapIndic+"\n"+
           doctorEmpCode+"\n"+
           patientSSN+"\n"+
           med1Code+"\n"+
           med2Code+"\n"+
           med3Code;
    }

void Consultation::setDate(const Date& d) {
    date=d;
    }

void Consultation::setTime(const Time& t) {
    time=t;
    }

void Consultation::setDiagnosisCode(const string& d) {
    diagnosisCode=d;
    }

void Consultation::setTherapIndic(const string& ti) {
    therapIndic=ti;
    }

void Consultation::setDoctorEmpCode(const string& d) {
    doctorEmpCode=d;
    }

void Consultation::setPatientSSN(const string& p) {
    patientSSN=p;
    }

void Consultation::setMed1Code(const string& m) {
    med1Code=m;
    }

void Consultation::setMed2Code(const string& m) {
    med2Code=m;
    }

void Consultation::setMed3Code(const string& m) {
    med3Code=m;
    }

bool Consultation::operator==(const Consultation& c) const {
    return therapIndic==c.therapIndic;
    }

bool Consultation::operator!=(const Consultation& c) const {
    return !(*this==c);
    }

bool Consultation::operator<(const Consultation& c) const {
    return therapIndic<c.therapIndic;
    }

bool Consultation::operator<=(const Consultation& c) const {
    return *this<c or *this==c;
    }

bool Consultation::operator>(const Consultation& c) const {
    return !(*this<=c);
    }

bool Consultation::operator>=(const Consultation& c) const {
    return !(*this<c);
    }

istream& operator>>(istream& is, Consultation& c) {
    //read...
    is>>c.date;
    is>>c.time;
    getline(is, c.diagnosisCode, '*');
    getline(is, c.therapIndic, '*');
    getline(is, c.doctorEmpCode, '*');
    getline(is, c.patientSSN, '*');
    getline(is, c.med1Code, '*');
    getline(is, c.med2Code, '*');
    getline(is, c.med3Code, '#');

    return is;
    }

ostream& operator<<(ostream& os, const Consultation& c) {
    os<<c.date;
    os<<c.time;
    os<<c.diagnosisCode<<"*";
    os<<c.therapIndic<<"*";
    os<<c.doctorEmpCode<<"*";
    os<<c.patientSSN<<"*";
    os<<c.med1Code<<"*";
    os<<c.med2Code<<"*";
    os<<c.med3Code<<"#";

    return os;
    }
