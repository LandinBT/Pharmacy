#include "consultation.hpp"
using namespace std;

Consultation::Consultation() {}

Consultation::Consultation(const Consultation& c) : date(c.date), time(c.time),
    diagnosis(c.diagnosis), therapIndic(c.therapIndic),
    doctor(c.doctor), patient(c.patient),
    med1(c.med1), med2(c.med2), med3(c.med3) {}

Consultation Consultation::operator=(const Consultation& c) {
    date=c.date;
    time=c.time;
    diagnosis=c.diagnosis;
    therapIndic=c.therapIndic;
    doctor=c.doctor;
    patient=c.patient;
    med1=c.med1;
    med2=c.med2;
    med3=c.med3;

    return *this;
    }

Date Consultation::getDate() const {
    return date;
    }

Time Consultation::getTime() const {
    return time;
    }

Diagnosis Consultation::getDiagnosis() const {
    return diagnosis;
    }

string Consultation::getTherapIndic() const {
    return therapIndic;
    }

Doctor Consultation::getDoctor() const {
    return doctor;
    }

Patient Consultation::getPatient() const {
    return patient;
    }

Medication Consultation::getMed1() const {
    return med1;
    }

Medication Consultation::getMed2() const {
    return med2;
    }

Medication Consultation::getMed3() const {
    return med3;
    }

string Consultation::toString() const {
    return date.toString()+"\n"+
           time.toString()+"\n"+
           diagnosis.toString()+"\n"+
           therapIndic+"\n"+
           doctor.toString()+"\n"+
           patient.toString()+"\n"+
           med1.toString()+"\n"+
           med2.toString()+"\n"+
           med3.toString();
    }

void Consultation::setDate(const Date& d) {
    date=d;
    }

void Consultation::setTime(const Time& t) {
    time=t;
    }

void Consultation::setDiagnosis(const Diagnosis& d) {
    diagnosis=d;
    }

void Consultation::setTherapIndic(const string& ti) {
    therapIndic=ti;
    }

void Consultation::setDoctor(const Doctor& d) {
    doctor=d;
    }

void Consultation::setPatient(const Patient& p) {
    patient=p;
    }

void Consultation::setMed1(const Medication& m) {
    med1=m;
    }

void Consultation::setMed2(const Medication& m) {
    med2=m;
    }

void Consultation::setMed3(const Medication& m) {
    med3=m;
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
    char delimiter='#';

    is>>c.date;
    is>>c.time;
    is>>c.diagnosis;
    getline(is, c.therapIndic, '*');
    is>>c.doctor;
    is>>c.patient;
    is>>c.med1;
    is>>c.med2;
    is>>c.med3;
    is>>delimiter;

    return is;
    }

ostream& operator<<(ostream& os, const Consultation& c) {
    os<<c.date;
    os<<c.time;
    os<<c.diagnosis;
    os<<c.therapIndic<<"*";
    os<<c.doctor;
    os<<c.patient;
    os<<c.med1;
    os<<c.med2;
    os<<c.med3;
    os<<"#";

    return os;
    }
