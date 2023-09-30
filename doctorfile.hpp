#ifndef __DOCTORFILE_HPP__
#define __DOCTORFILE_HPP__

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <sstream>  //stringstream

#include "doctor.hpp"
#include "indextuple.hpp"
#include "name.hpp"

class DoctorFile {
        std::string dataFileName;
        std::string indexCode;
        std::string indexName;

        std::fstream dataFile;
        std::fstream indexByCode;
        std::fstream indexByName;

        std::list<IndexTuple<>> indexByCodeList;
        std::list<IndexTuple<Name>> indexByNameList;

        void reindex();

        template <class T>
        std::list<IndexTuple<T>>& fileToList(std::fstream&, std::list<IndexTuple<T>>&);

        template <class T>
        std::fstream& listToFile(const std::list<T>&, std::fstream&);

        template <class T>
        int getIndex(const std::list<T>&, const T&);

    public:
        DoctorFile();

        ~DoctorFile();

        void addData(const Doctor&);
        void addData(std::list<Doctor>&);

        void deleteData(const int&);  // index

        int findData(const Doctor&);
        int findData(std::string&);  // code
        int findData(const Name&);

        std::list<Doctor> toList() const;

        void clearFile();

        void compress();
    };

/// IMPLEMENTATION
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

template <class T>
list<IndexTuple<T>>& DoctorFile::fileToList(fstream& myFstream, list<IndexTuple<T>>& myList) {
    string str;
    T data;

    while (!myFstream.eof()) {
        getline(myFstream, str, '#');

        if (str.empty()) continue;

        stringstream strStream(str);

        getline(strStream, str, '*');

        if (str == "1") {
            strStream >> data;
            myList.push_back(data);
            }
        }

    return myList;
    }

template <class T>
fstream& DoctorFile::listToFile(const list<T>& myList, fstream& myFstream) {
    for (auto it = myList.begin(); it != myList.end(); it++) {
        myFstream << "1*" << *it << "#";
        }

    return myFstream;
    }

template <class T>
int DoctorFile::getIndex(const list<T>&, const T&) {}

DoctorFile::DoctorFile() {}

DoctorFile::~DoctorFile() {}

void DoctorFile::addData(const Doctor&) {}

void DoctorFile::addData(list<Doctor>&) {}

void DoctorFile::deleteData(const int&) {}

int DoctorFile::findData(const Doctor&) {}

int DoctorFile::findData(string&) {}

int DoctorFile::findData(const Name&) {}

list<Doctor> DoctorFile::toList() const {}

void DoctorFile::clearFile() {}

void DoctorFile::compress() {}

#endif  // __DOCTORFILE_HPP__
