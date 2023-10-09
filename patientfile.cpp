#include "patientfile.hpp"
using namespace std;

void PatientFile::reindex() {
    string str;
    int idx; // Inicializar el índice
    Patient patient;
    IndexTuple<> idxCode;      // Indexar por código
    IndexTuple<Name> idxName;

    dataFile.open(dataFileName, ios_base::in);

    if (!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para lectura");
        }

    indexByCodeList.clear();
    indexByNameList.clear();

    while (!dataFile.eof()) {
        idx = int(dataFile.tellg());
        getline(dataFile, str, '#');

        if (str.empty() or str[0] == '0') {
            continue; // Saltar registros vacíos o marcados como eliminados
            }

        stringstream strStream(str);

        getline(strStream, str, '*');
        if (str == "1") {
            strStream >> patient;

            idxCode.setIndex(idx);
            idxCode.setData(patient.getSocSecNum());
            indexByCodeList.push_back(idxCode);

            idxName.setIndex(idx);
            idxName.setData(patient.getName());
            indexByNameList.push_back(idxName);
            }
        }

    indexByCode.open(indexCode, ios_base::out | ios_base::trunc);
    if (!indexByCode.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para escritura");
        }

    listToFile(indexByCodeList, indexByCode);
    indexByCode.close();

    indexByName.open(indexName, ios_base::out | ios_base::trunc);
    if (!indexByName.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para escritura");
        }

    listToFile(indexByNameList, indexByName);
    indexByName.close();

    dataFile.close();
    }

PatientFile::PatientFile() : dataFileName("patient.file"),
    indexCode("patient_code.index"), indexName("patient_name.index") {}

PatientFile::~PatientFile() {
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

void PatientFile::addData(const Patient& pat) {
    /*dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para escritura");
        }

    dataFile<<"1*"<<pat<<"#";

    dataFile.close();*/
    list<Patient> patList;
    patList.push_back(pat);
    addData(patList);

    reindex();
    }

void PatientFile::addData(list<Patient>& patList) {
    dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para escritura");
        }

    listToFile(patList, dataFile);

    dataFile.close();

    reindex();
    }

void PatientFile::deleteData(const int& idx) {
    dataFile.open(dataFileName, ios_base::in);

    if (!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para lectura");
        }

    dataFile.seekp(idx);

    dataFile<<"0";

    dataFile.close();

    reindex();
    compress();
    }

int PatientFile::findData(const Patient& pat) {
    int idx = 0;
    for (const IndexTuple<>& indexTuple : indexByCodeList) {
        int idxAux = indexTuple.getIndex();
        string ssn = indexTuple.getData();

        if (ssn == pat.getSocSecNum()) {
            dataFile.seekg(idxAux);
            Patient patTemp;
            dataFile>>patTemp;

            if(patTemp == pat) {
                return idx;
                }
            }
        idx++;
        }

    return -1;
    }

int PatientFile::findData(const string& ssn) {
    return getIndex(indexByCodeList, ssn);
    }

int PatientFile::findData(const Name& n) {
    return getIndex(indexByNameList, n);
    }

Patient PatientFile::retrieve(const int& idx) {
    Patient patient;
    string str;

    indexByName.open(dataFileName);

    if(!indexByName.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo, retrieve");
        }

    indexByName.seekg(idx);
    getline(indexByName, str, '#');

    if(str.empty()) {
        throw ios_base::failure("No se encontró ningún dato");
        }

    stringstream strStream(str);
    getline(strStream, str, '*');
    if(str=="0") {
        throw ios_base::failure("Dato borrado");
        }

    strStream>>patient;

    return patient;
    }


list<Patient> PatientFile::toList() {
    dataFile.open(dataFileName, ios_base::in);

    if (!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para lectura.");
        }

    list<Patient> patList;
    patList=fileToList(dataFile, patList);

    dataFile.close();
    return patList;
    }

void PatientFile::clearFile() {
    dataFile.close();
    indexByCode.close();
    indexByName.close();

    remove(dataFileName.c_str());
    remove(indexCode.c_str());
    remove(indexName.c_str());

    indexByCodeList.clear();
    indexByNameList.clear();
    }

void PatientFile::exportToBackup(const string&) {

    }

list<Patient> PatientFile::importFromBackup(const string& fileName) {
    Patient patient;
    Name name;
    Date birth;
    Address address;
    string phoneNum;
    string socSecNum;
    string str;

    list<Patient> patientList;

    fstream archive(fileName, ios_base::in);

    if (!archive.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo para lectura");
        }

    while (!archive.eof()) {
        getline(archive, str, '#');

        if (str.empty()) {
            continue;
            }

        stringstream strStream(str);

        try {
            // SocSecNum
            getline(strStream, socSecNum, '*');
            patient.setSocSecNum(socSecNum);

            // Name
            strStream >> name;
            patient.setName(name);

            // Birth
            strStream >> birth;
            patient.setBirth(birth);

            // Address
            strStream >> address;
            patient.setAddress(address);

            // PhoneNum
            getline(strStream, phoneNum, '*');
            patient.setPhoneNum(phoneNum);

            // Agregar el paciente a la lista
            patientList.push_back(patient);
            }
        catch (const exception& ex) {
            cout << "Algo salió mal: " << ex.what() << endl;
            }
        }

    archive.close();
    return patientList;
    }


void PatientFile::compress() {
    string tempName = dataFileName+".temp";
    fstream tempFile(tempName, ios_base::out | ios_base::trunc);

    if (!tempFile.is_open()) {
        throw ios_base::failure("No se pudo crear el archivo temporal.");
        }

    dataFile.seekg(0);

    while (!dataFile.eof()) {
        string str;
        getline(dataFile, str, '#');

        if (str.empty()) {
            continue;
            }

        if (str[0] == '1') {
            tempFile<<str<<"#";
            }
        }

    dataFile.close();
    remove(dataFileName.c_str());

    rename(tempName.c_str(), dataFileName.c_str());

    reindex();
    }
