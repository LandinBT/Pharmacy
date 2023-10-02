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

void DoctorFile::deleteData(const int& idx) {
    // Verifica si el índice está dentro del rango de la lista
    if (idx>=0 and idx<indexByCodeList.size()) {
        // Busca el elemento en la lista por su índice
        auto it = indexByCodeList.begin();
        advance(it, idx);

        // Marca el registro como borrado en el archivo de datos
        dataFile.seekp(it->getIndex());
        dataFile << "0"; // Marca como borrado

        // Elimina el elemento de las listas de índices
        indexByCodeList.erase(it);
        indexByNameList.erase(next(indexByNameList.begin(), idx));

        // Reindexa para reflejar los cambios
        reindex();
        }
    }

int DoctorFile::findData(const Doctor& doc) {
    // Recorre la lista de índices por código de empleado
    int idx = 0;
    for (const IndexTuple<>& indexTuple : indexByCodeList) {
        // Obtiene el índice del registro y el código de empleado correspondiente
        int idxAux = indexTuple.getIndex();
        string empCode = indexTuple.getData();

        // Compara el código de empleado
        if (empCode == doc.getEmpCode()) {
            // Compara los datos reales para confirmar la coincidencia
            dataFile.seekg(idxAux);
            Doctor docTemp;
            dataFile>>docTemp;

            // Realiza una comparación explícita de los campos relevantes
            if (docTemp==doc) {
                return idx; // Retorna el índice encontrado
                }
            }
        idx++;
        }

    return -1; // No se encontró la coincidencia
    }

int DoctorFile::findData(string& code) {
    // Busca el registro en la lista de índices por código de empleado
    int idx = getIndex(indexByCodeList, IndexTuple<>(-1, code));
    if (idx != -1) {
        return idx; // Retorna el índice encontrado
        }
    return -1; // No se encontró la coincidencia
    }

int DoctorFile::findData(const Name& n) {
    // Busca el registro en la lista de índices por nombre
    int idx = getIndex(indexByNameList, IndexTuple<Name>(-1, n));
    if (idx != -1) {
        return idx; // Retorna el índice encontrado
        }
    return -1; // No se encontró la coincidencia
    }

list<Doctor> DoctorFile::toList() {
    list<Doctor> docList;

    dataFile.open(dataFileName, ios_base::in);

    if (!dataFile.is_open()) {
        throw ios_base::failure("No se pudo abrir el archivo de datos para lectura.");
        }

    while (!dataFile.eof()) {
        string str;
        getline(dataFile, str, '#');

        if (str.empty()) {
            continue; // Salta registros vacíos
            }

        if (str[0] == '1') {
            Doctor doctor;
            stringstream strStream(str);
            strStream>>doctor;
            docList.push_back(doctor);
            }
        }

    dataFile.close();
    return docList;
    }

void DoctorFile::clearFile() {
    dataFile.close();
    indexByCode.close();
    indexByName.close();

    remove(dataFileName.c_str());
    remove(indexCode.c_str());
    remove(indexName.c_str());

    indexByCodeList.clear();
    indexByNameList.clear();
    }

void DoctorFile::compress() {
    // Crea una copia temporal del archivo de datos
    string tempName = dataFileName+".temp";
    fstream tempFile(tempName, ios_base::out | ios_base::trunc);

    if (!tempFile.is_open()) {
        throw ios_base::failure("No se pudo crear el archivo temporal.");
        }

    dataFile.seekg(0); // Vuelve al principio del archivo de datos

    while (!dataFile.eof()) {
        string str;
        getline(dataFile, str, '#');

        if (str.empty()) {
            continue; // Salta registros vacíos
            }

        if (str[0] == '1') {
            tempFile<<str<<"#"; // Escribe registros activos en el archivo temporal
            }
        }

    // Cierra y elimina el archivo original de datos
    dataFile.close();
    remove(dataFileName.c_str());

    // Renombra el archivo temporal como el archivo de datos original
    rename(tempName.c_str(), dataFileName.c_str());

    // Reindexa para reflejar los cambios
    reindex();
    }
