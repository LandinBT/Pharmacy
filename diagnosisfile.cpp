#include "diagnosisfile.hpp"
using namespace std;

void DiagnosisFile::reindex() {
    indexByCodeList.clear();
    indexByDescList.clear();

    fstream dataFile(dataFileName, ios_base::in);

    if (!dataFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de datos para lectura." << std::endl;
        return;
        }

    int index = 0;
    string line;
    while (getline(dataFile, line, '#')) {
        if (line.empty() or line[0] == '0') {
            index++;
            continue; // Saltar registros vac�os o marcados como eliminados
            }

        stringstream ss(line);
        Diagnosis diagnosis;
        ss >> diagnosis;

        IndexTuple<> idxCode;
        idxCode.setIndex(index);
        idxCode.setData(diagnosis.getCode());
        indexByCodeList.push_back(idxCode);

        IndexTuple<> idxDesc;
        idxDesc.setIndex(index);
        idxDesc.setData(diagnosis.getDesc());
        indexByDescList.push_back(idxDesc);

        index++;
        }

    dataFile.close();
    }

DiagnosisFile::DiagnosisFile() : dataFileName("diagnosis.file"),
    indexCode("diagnosis_code.index"), indexDesc("diagnosis_desc.index") {
    reindex();
    }

DiagnosisFile::~DiagnosisFile() {}

void DiagnosisFile::addData(const Diagnosis& dx) {
    dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo de datos para escritura.");
        }

    dataFile<<dx<<'#';
    dataFile.close();

    reindex();
    }

void DiagnosisFile::addData(list<Diagnosis>& diagList) {
    dataFile.open(dataFileName, ios_base::out | ios_base::app);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo de datos para escritura.");
        }

    listToFile(diagList, dataFile);
    dataFile.close();
    reindex();
    }

void DiagnosisFile::deleteData(const int& idx) {
    dataFile.open(dataFileName, ios_base::in | ios_base::out);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo de datos para lectura/escritura.");
        }

    dataFile.seekp(idx, ios_base::beg);
    dataFile.put('0');
    dataFile.close();

    reindex();
    compress();
    }

int DiagnosisFile::findData(const Diagnosis& dx) {
    int idx(0);
    for(const IndexTuple<>& idxTup : indexByCodeList) {
        int idxAux=idxTup.getIndex();
        string code=idxTup.getData();

        if(code==dx.getCode()) {
            Diagnosis diagTemp=retrieve(idxAux);

            if(diagTemp==dx) {
                return idx;
                }
            }

        idx++;
        }

    return -1;
    }

int DiagnosisFile::findDataCode(string& findCode) {
    int idx(0);

    for(const IndexTuple<>& idxTup : indexByCodeList) {
        const string& codeAux=idxTup.getData();

        if(codeAux==findCode) {
            return idx;
            }

        idx++;
        }

    return -1;
    }

int DiagnosisFile::findDataDesc(string& findDesc) {
    int idx(0);

    for(const IndexTuple<>& idxTup : indexByDescList) {
        const string& descAux=idxTup.getData();

        if(descAux==findDesc) {
            return idx;
            }

        idx++;
        }

    return -1;
    }

Diagnosis DiagnosisFile::retrieve(const int& idx) {
    dataFile.open(dataFileName, ios_base::in);

    if(!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo de datos para lectura.");
        }

    dataFile.seekg(idx, ios_base::beg);

    string str;
    getline(dataFile, str, '#');

    if(str.empty() or str[0]=='0') {
        throw ios_base::failure("Dato borrado o no encontrado.");
        }

    istringstream strStream(str);
    Diagnosis diagnosis;

    strStream>>diagnosis;

    dataFile.close();

    return diagnosis;
    }

list<Diagnosis> DiagnosisFile::toList() {
    dataFile.open(dataFileName, ios_base::in);

    if(!dataFile.is_open()){
        throw ios_base::failure("No se pudo abrir el archivo de datos para lectura.");
    }

    list<Diagnosis> diagList;
    fileToList(dataFile, diagList);

    dataFile.close();

    return diagList;
    }

void DiagnosisFile::clearFile() {
    remove(dataFileName.c_str());
    remove(indexCode.c_str());
    remove(indexDesc.c_str());

    indexByCodeList.clear();
    indexByDescList.clear();
    }

void DiagnosisFile::compress() {
    string tempFileName(dataFileName+".temp");
    fstream tempFile(tempFileName, ios_base::out | ios_base::trunc);

    if(!tempFile.is_open()){
        throw ios_base::failure("No se pudo crear el archivo temporal.");
    }

    dataFile.open(dataFileName, ios_base::in);

    if(!dataFile.is_open()){
        throw ios_base::failure("No se pudo abrir el archivo de datos para lectura.");
    }

    int idx(0);
    string str;

    while(getline(dataFile, str, '#')){
        if(str.empty()){
            idx++;
            continue;
        }

        if(str[0]=='1'){
            tempFile<<str<<'#';
        }

        idx++;
    }

    dataFile.close();
    tempFile.close();

    remove(dataFileName.c_str());
    rename(tempFileName.c_str(), dataFileName.c_str());

    reindex();
    }

void DiagnosisFile::importFromBackup(const string& fileName) {
    ifstream archive(fileName);

    if(!archive.is_open()){
        throw ios_base::failure("No se pudo abrir el archivo de respaldo para lectura.");
    }

    list<Diagnosis> diagList;
    Diagnosis diagnosis;

    while(archive>>diagnosis){
        diagList.push_back(diagnosis);
    }

    archive.close();

    addData(diagList);
    }

void DiagnosisFile::exportToBackup(const string& fileName) {
    ofstream archive(fileName);

    if(!archive.is_open()){
        throw ios_base::failure("No se pudo abrir el archivo de respaldo para escritura.");
    }

    list<Diagnosis> diagList=toList();

    for(const Diagnosis& diagnosis : diagList){
        archive<<diagnosis<<"#";
    }

    archive.close();
    }
