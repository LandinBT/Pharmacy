#include "medicationfile.hpp"
using namespace std;

void MedicationFile::reindex() {
    indexByCodeList.clear();
    indexByNameList.clear();

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
        Medication medication;
        ss >> medication;

        IndexTuple<> indexCode;
        indexCode.setIndex(index);
        indexCode.setData(medication.getCode());
        indexByCodeList.push_back(indexCode);

        IndexTuple<> indexName;
        indexName.setIndex(index);
        indexName.setData(medication.getName());
        indexByNameList.push_back(indexName);

        index++;
        }

    dataFile.close();
    }

MedicationFile::MedicationFile()
    : dataFileName("medication.file"),
      indexCode("medication_code.index"),
      indexName("medication_name.index") {
    reindex();
    }

MedicationFile::~MedicationFile() {}

void MedicationFile::addData(const Medication& medication) {
    std::fstream dataFile(dataFileName, std::ios_base::out | std::ios_base::app);

    if (!dataFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de datos para escritura." << std::endl;
        return;
        }

    dataFile << medication << '#';
    dataFile.close();

    reindex();
    }

void MedicationFile::addData(std::list<Medication>& medicationList) {
    std::fstream dataFile(dataFileName, std::ios_base::out | std::ios_base::app);

    if (!dataFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de datos para escritura." << std::endl;
        return;
        }

    listToFile(medicationList, dataFile);
    dataFile.close();

    reindex();
    }

void MedicationFile::deleteData(const int& index) {
    std::fstream dataFile(dataFileName, std::ios_base::in | std::ios_base::out);

    if (!dataFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de datos para lectura/escritura." << std::endl;
        return;
        }

    dataFile.seekp(index, std::ios::beg);
    dataFile.put('0');
    dataFile.close();

    reindex();
    compress();
    }

int MedicationFile::findData(const Medication& med) {
    int index = 0;
    for (const IndexTuple<std::string>& indexTuple : indexByCodeList) {
        int idxAux = indexTuple.getIndex();
        std::string code = indexTuple.getData();

        if (code == med.getCode()) {
            // Ahora que encontramos un c�digo coincidente, verificamos si el objeto Medication tambi�n coincide
            Medication medTemp = retrieve(idxAux);
            if (medTemp == med) {
                return index;
            }
        }
        index++;
    }
    return -1;
    }

int MedicationFile::findDataCode(string& code) {
    int index = 0;
    for (const IndexTuple<std::string>& indexTuple : indexByCodeList) {
        const std::string& storedCode = indexTuple.getData();
        if (storedCode == code) {
            return index;
        }
        index++;
    }
    return -1;
    }

int MedicationFile::findDataName(string& name) {
    int index = 0;
    for (const IndexTuple<std::string>& indexTuple : indexByNameList) {
        const std::string& storedName = indexTuple.getData();
        if (storedName == name) {
            return index;
        }
        index++;
    }
    return -1;
    }

Medication MedicationFile::retrieve(const int& index) {
    std::fstream dataFile(dataFileName, std::ios_base::in);

    if (!dataFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de datos para lectura." << std::endl;
        throw std::runtime_error("Error al abrir el archivo de datos.");
        }

    dataFile.seekg(index, std::ios::beg);
    std::string line;
    std::getline(dataFile, line, '#');

    if (line.empty() or line[0] == '0') {
        throw std::runtime_error("Dato borrado o no encontrado.");
        }

    std::stringstream ss(line);
    Medication medication;
    ss >> medication;

    dataFile.close();
    return medication;
    }

std::list<Medication> MedicationFile::toList() {
    std::fstream dataFile(dataFileName, std::ios_base::in);

    if (!dataFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de datos para lectura." << std::endl;
        throw std::runtime_error("Error al abrir el archivo de datos.");
        }

    std::list<Medication> medicationList;
    fileToList(dataFile, medicationList);

    dataFile.close();
    return medicationList;
    }

void MedicationFile::clearFile() {
    std::remove(dataFileName.c_str());
    std::remove(indexCode.c_str());
    std::remove(indexName.c_str());

    indexByCodeList.clear();
    indexByNameList.clear();
    }

void MedicationFile::compress() {
    std::string tempFileName = dataFileName + ".temp";
    std::fstream tempFile(tempFileName, std::ios_base::out | std::ios_base::trunc);

    if (!tempFile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo temporal." << std::endl;
        return;
        }

    std::fstream dataFile(dataFileName, std::ios_base::in);

    if (!dataFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de datos para lectura." << std::endl;
        return;
        }

    int index = 0;
    std::string line;
    while (std::getline(dataFile, line, '#')) {
        if (line.empty()) {
            index++;
            continue; // Saltar registros vac�os
            }

        if (line[0] == '1') {
            tempFile << line << '#';
            }

        index++;
        }

    dataFile.close();
    tempFile.close();

    std::remove(dataFileName.c_str());
    std::rename(tempFileName.c_str(), dataFileName.c_str());

    reindex();
    }

void MedicationFile::importFromBackup(const std::string& fileName) {
    std::ifstream archive(fileName);

    if (!archive.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de respaldo para lectura." << std::endl;
        return;
        }

    std::list<Medication> medicationList;
    Medication medication;

    while (archive>>medication) {
        medicationList.push_back(medication);
        }

    archive.close();

    addData(medicationList);
    }

void MedicationFile::exportToBackup(const std::string& fileName) {
    std::ofstream archive(fileName);

    if (!archive.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de respaldo para escritura." << std::endl;
        return;
        }

    std::list<Medication> medicationList = toList();

    for (const Medication& medication : medicationList) {
        archive<<medication<<"#";
        }

    archive.close();
    }
