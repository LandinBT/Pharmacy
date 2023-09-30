#include "doctorfile.hpp"
using namespace std;

void DoctorFile::reindex() {
    string str;
    int idx;  // index
    Doctor doctor;
    IndexTuple<> idxCode;      // index code
    IndexTuple<Name> idxName;  // index name

    dataFile.open(dataFileName, ios_base::in);  // open archive
    if (!dataFile.is_open())
        throw ios_base::failure("No se pudo abrir el archivo para lectura");

    while (!dataFile.eof()) {
        idx = dataFile.tellg();  // recuperar posicion (en realidad es el index)

        getline(dataFile, str, '#');

        if (str.empty()) {
            continue;
            }

        stringstream strStream(str);

        getline(strStream, str, '*');

        if (str == "0") {  // registro borrado
            continue;
            }

        strStream >> doctor;

        idxCode.setIndex(idx);
        idxCode.setData(doctor.getEmpCode());
        indexByCodeList.push_back(idxCode);

        idxName.setIndex(idx);
        idxName.setData(doctor.getName());
        indexByNameList.push_back(idxName);
        }

    indexByCode.open(indexCode, ios_base::out | ios_base::trunc);
    if (!indexByCode.is_open()) {
        throw ios_base::failure(
            "No se pudo abrir el archivo para lectura, indexByCode");
        }

    listToFile(indexByCodeList, indexByCode);

    indexByCode.close();

    indexByName.open(indexName, ios_base::out | ios_base::trunc);
    if (!indexByName.is_open()) {
        throw ios_base::failure(
            "No se pudo abrir el archivo para lectura, indexByCode");
        }

    listToFile(indexByNameList, indexByName);

    indexByName.close();
    }

DoctorFile::DoctorFile() : dataFileName("doctor.file"),
indexCode("doctor_code.index"), indexName("doctor_name.index") {}

DoctorFile::~DoctorFile() {
    if(dataFile.is_open()) {
        dataFile.close();
    }

    if(indexByCode.is_open()) {
        indexByCode.close();
    }

    if(indexByName.is_open()) {
        indexByName.close();
    }
}

void DoctorFile::addData(const Doctor& doc) {
    dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para escritura");
    }

    dataFile<<"1*"<<doc<<"#";

    dataFile.close();
}

void DoctorFile::addData(list<Doctor>& docList) {
    dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para escritura");
    }

    listToFile(docList, dataFile);

    dataFile.close();

    reindex();
}

void DoctorFile::deleteData(const int& pos) {}

int DoctorFile::findData(const Doctor& d) {}

int DoctorFile::findData(string& code) {}

int DoctorFile::findData(const Name& n) {}

list<Doctor> DoctorFile::toList() const {}

void DoctorFile::clearFile() {}

void DoctorFile::compress() {}
