#include "medicationfile.hpp"
using namespace std;

void MedicationFile::reindex() {
    Medication medication;
    IndexTuple<> idxCode;
    string str;
    int idx;

    dataFile.open(dataFileName, ios_base::in);

    if (!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para lectura");
        }

    indexByCodeList.clear();

    while (!dataFile.eof()) {
        idx = int(dataFile.tellg());
        getline(dataFile, str, '#');

        if (str.empty() or str[0] == '0') {
            continue;
            }

        stringstream strStream(str);

        getline(strStream, str, '*');
        if (str=="1") {
            strStream>>medication;

            idxCode.setIndex(idx);
            idxCode.setData(medication.getCode());
            indexByCodeList.push_back(idxCode);
            }
        }

    indexByCode.open(indexCode, ios_base::out | ios_base::trunc);
    if (!indexByCode.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para escritura");
        }

    listToFile(indexByCodeList, indexByCode);
    indexByCode.close();

    dataFile.close();
    }

MedicationFile::MedicationFile() : dataFileName("medication.file"), indexCode("medication_code.index") {}

MedicationFile::~MedicationFile() {
    if(dataFile.is_open()) dataFile.close();

    if(indexByCode.is_open()) indexByCode.close();
    }

void MedicationFile::addData(const Medication& med) {
    dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) throw ios_base::failure("No se pudo abrir el archivo para escritura");

    dataFile<<"1*"<<med<<"#";

    dataFile.close();
    }

void MedicationFile::addData(list<Medication>& medList) {
    dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) throw ios_base::failure("No se pudo abrir el archivo para escritura");

    listToFile(medList, dataFile);

    dataFile.close();

    reindex();
    }

void MedicationFile::deleteData(const int& idx) {
    if(idx>=0 and idx<indexByCodeList.size()) {
        auto it=indexByCodeList.begin();
        advance(it, idx);

        dataFile.seekp(it->getIndex());
        dataFile<<"0";

        indexByCodeList.erase(it);

        reindex();
        }
    }

int MedicationFile::findData(const Medication& med) {
    int idx;
    for(const IndexTuple<>& idxTup : indexByCodeList) {
        int idxAux=idxTup.getIndex();
        string code=idxTup.getData();

        if(code==med.getCode()) {
            dataFile.seekg(idxAux);
            Medication medTemp;
            dataFile>>medTemp;

            if(medTemp==med) return idx;
            }

        idx++;
        }

    return -1;
    }

int MedicationFile::findData(string& code) {
    int idx=getIndex(indexByCodeList, IndexTuple<>(-1, code));

    if(idx!=-1) return idx;

    return -1;
    }

list<Medication> MedicationFile::toList() {
    dataFile.open(dataFileName, ios_base::in);

    if(!dataFile.is_open())
        throw ios_base::failure("No se pudo abrir el archivo de datos para lectura");

    list<Medication> medList;
    medList=fileToList(dataFile, medList);

    dataFile.close();

    return medList;
    }

void MedicationFile::clearFile() {
    dataFile.close();
    indexByCode.close();

    remove(dataFileName.c_str());
    remove(indexCode.c_str());

    dataFile.clear();
    indexByCodeList.clear();
    }

void MedicationFile::compress() {
    string tempFileName=dataFileName+".temp";
    fstream tempFile(tempFileName, ios_base::out | ios_base::trunc);

    if(!tempFile.is_open()) throw ios_base::failure("No se pudo crear el archivo temporal.");

    dataFile.seekg(0);

    while(!dataFile.eof()) {
        string str;
        getline(dataFile, str, '#');

        if(str.empty()) continue;

        if(str[0]=='1') tempFile<<str<<"#";
        }

    dataFile.close();

    remove(dataFileName.c_str());

    rename(tempFileName.c_str(), dataFileName.c_str());

    reindex();
    }

void MedicationFile::importFromBackup() {
    reindex();
    }

void MedicationFile::exportToBackup() {
    compress();
    }
