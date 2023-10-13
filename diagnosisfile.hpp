#ifndef __DIAGNOSISFILE_HPP__
#define __DIAGNOSISFILE_HPP__

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>  //stringstream
#include <string>

#include "diagnosis.hpp"
#include "indextuple.hpp"

class DiagnosisFile {
        std::string dataFileName;
        std::string indexCode;
        std::string indexDesc;

        std::fstream dataFile;
        std::fstream indexByCode;
        std::fstream indexByDesc;

        std::list<IndexTuple<>> indexByCodeList;
        std::list<IndexTuple<>> indexByDescList;

        void reindex();

        template <class T>
        std::list<T>& fileToList(std::fstream&,
                                 std::list<T>&);

        template <class T>
        std::fstream& listToFile(const std::list<T>&, std::fstream&);

        template <class T>
        int getIndex(const std::list<T>&, const T&);

    public:
        DiagnosisFile();

        ~DiagnosisFile();

        void addData(const Diagnosis&);
        void addData(std::list<Diagnosis>&);

        void deleteData(const int&);  // index

        int findData(const Diagnosis&);
        int findDataCode(std::string&);  // code
        int findDataDesc(std::string&);  // description

        Diagnosis retrieve(const int&); //index

        std::list<Diagnosis> toList();

        void clearFile();

        void compress();

        void importFromBackup(const std::string&);
        void exportToBackup(const std::string&);
    };

/// IMPLEMENTATION
using namespace std;

template <class T>
std::list<T>& DiagnosisFile::fileToList(std::fstream& file, std::list<T>& dataList) {
    dataList.clear();

    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para lectura." << std::endl;
        return dataList;
        }

    T item;
    while (file >> item) {
        dataList.push_back(item);
        }

    return dataList;
    }

template <class T>
std::fstream& DiagnosisFile::listToFile(const std::list<T>& dataList, std::fstream& file) {
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para escritura." << std::endl;
        return file;
        }

    for (const T& item : dataList) {
        file << item;
        }

    return file;
    }

template <class T>
int DiagnosisFile::getIndex(const std::list<T>& dataList, const T& item) {
    int index = 0;
    for (const T& data : dataList) {
        if (data == item) {
            return index;
            }
        index++;
        }
    return -1;
    }

#endif  // __DIAGNOSISFILE_HPP__
