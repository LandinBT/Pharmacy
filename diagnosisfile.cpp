#include "diagnosisfile.hpp"
using namespace std;

void DiagnosisFile::reindex() {
  string str;
  int idx;  // index
  Diagnosis diagnosis;
  IndexTuple<> idxCode;  // index code

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

    strStream >> diagnosis;

    idxCode.setIndex(idx);
    idxCode.setData(diagnosis.getCode());
    indexByCodeList.push_back(idxCode);
  }

  indexByCode.open(indexCode, ios_base::out | ios_base::trunc);
  if (!indexByCode.is_open()) {
    throw ios_base::failure(
        "No se pudo abrir el archivo para lectura, indexByCode");
  }

  listToFile(indexByCodeList, indexByCode);

  indexByCode.close();
}

DiagnosisFile::DiagnosisFile()
    : dataFileName("diagnosis.file"), indexCode("diagnosis_code.index") {}

DiagnosisFile::~DiagnosisFile() {
  if (dataFile.is_open()) {
    dataFile.close();
  }

  if (indexByCode.is_open()) {
    indexByCode.close();
  }
}

void DiagnosisFile::addData(const Diagnosis& dx) {
  dataFile.open(dataFileName, ios_base::out | ios_base::app);

  if (!dataFile.is_open()) {
    throw ios_base::failure("No se pudo abrir el archivo para escritura");
  }

  dataFile << "1*" << dx << "#";

  dataFile.close();
}

void DiagnosisFile::addData(list<Diagnosis>& diagList) {
  dataFile.open(dataFileName, ios_base::out | ios_base::app);

  if (!dataFile.is_open()) {
    throw ios_base::failure("No se pudo abrir el archivo para escritura");
  }

  listToFile(diagList, dataFile);

  dataFile.close();

  reindex();
}

void DiagnosisFile::deleteData(const int& idx) {
  if (idx >= 0 and idx < indexByCodeList.size()) {
    auto it = indexByCodeList.begin();
    advance(it, idx);

    dataFile.seekp(it->getIndex());
    dataFile << "0";

    indexByCodeList.erase(it);

    reindex();
  }
}

int DiagnosisFile::findData(const Diagnosis& dx) {
  int idx = 0;
  for (const IndexTuple<>& indexTuple : indexByCodeList) {
    int idxAux = indexTuple.getIndex();
    string code = indexTuple.getData();

    if (code == dx.getCode()) {
      dataFile.seekg(idxAux);
      Diagnosis dxTemp;
      dataFile >> dxTemp;

      if (dxTemp == dx) {
        return idx;
      }
    }
    idx++;
  }

  return -1;
}

int DiagnosisFile::findData(string& code) {
  int idx = getIndex(indexByCodeList, IndexTuple<>(-1, code));
  if (idx != -1) {
    return idx;
  }
  return -1;
}

list<Diagnosis> DiagnosisFile::toList() {
  list<Diagnosis> diagList;

  dataFile.open(dataFileName, ios_base::in);

  if (!dataFile.is_open()) {
    throw ios_base::failure(
        "No se pudo abrir el archivo de datos para lectura.");
  }

  while (!dataFile.eof()) {
    string str;
    getline(dataFile, str, '#');

    if (str.empty()) {
      continue;
    }

    if (str[0] == '1') {
      Diagnosis diagnosis;
      stringstream strStream(str);
      strStream >> diagnosis;
      diagList.push_back(diagnosis);
    }
  }

  dataFile.close();
  return diagList;
}

void DiagnosisFile::clearFile() {
  dataFile.close();
  indexByCode.close();

  remove(dataFileName.c_str());
  remove(indexCode.c_str());

  indexByCodeList.clear();
}

void DiagnosisFile::compress() {
  string tempName = dataFileName + ".temp";
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
      tempFile << str << "#";
    }
  }

  dataFile.close();
  remove(dataFileName.c_str());

  rename(tempName.c_str(), dataFileName.c_str());

  reindex();
}