#include "consultationfile.hpp"
using namespace std;

ConsultationFile::ConsultationFile() {

    }

ConsultationFile::~ConsultationFile() {

    }

void ConsultationFile::addData(const Consultation&) {

    }

void ConsultationFile::addData(const list<Consultation>&) {

    }

list<Consultation> ConsultationFile::toList() const {

    }

void ConsultationFile::exportToBackup(const string&) {

    }

list<Consultation> ConsultationFile::importFromBackup(const string& fileName) {
    Consultation consultation;
    Diagnosis diagnosis;
    Doctor doctor;
    Patient patient;
    Medication medication;
    Name name;
    Date date;
    Time time;
    string therapIndic;
    string str;

    list<Consultation> consultList;

    fstream archive(fileName, ios_base::in);

    if(!archive.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para lectura");
        }

    while(!archive.eof()) {
        getline(archive, str, '#');

        if(str.empty()) {
            continue;
            }

        stringstream strStream(str);

        try {
            //consultation date
            strStream>>date;
            consultation.setDate(date);
            //consultation time
            strStream>>time;
            consultation.setTime(time);
            //diagnosis
            strStream>>diagnosis;
            consultation.setDiagnosis(diagnosis);
            //therapeutic indications
            getline(strStream, therapIndic, '*');
            consultation.setTherapIndic(therapIndic);
            //doctor
            strStream>>doctor;
            consultation.setDoctor(doctor);
            //patient
            strStream>>patient;
            consultation.setPatient(patient);
            //medications
            strStream>>medication;
            consultation.setMed1(medication);
            strStream>>medication;
            consultation.setMed2(medication);
            strStream>>medication;
            consultation.setMed3(medication);
            }
        catch(const exception& ex) {
            cout<<"Algo salió mal: "<<ex.what()<<endl;
            }

        consultList.push_back(consultation);
        }

    archive.close();
    return consultList;
    }

void ConsultationFile::clearFile() {

    }
