#ifndef __MEDICATIONFILE_HPP__
#define __MEDICATIONFILE_HPP__

/*puntos extras=proyecto de archivo simple abierto*/
/*ej: cuando entras al menu de doctor abre el archivo y cuando sale lo cierra*/

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>  //stringstream
#include <string>

#include "indextuple.hpp"
#include "medication.hpp"

class MedicationFile {
        std::string dataFileName;
        std::string indexCode;
        std::string indexName;

        std::fstream dataFile;
        std::fstream indexByCode;
        std::fstream indexByName;

        std::list<IndexTuple<>> indexByCodeList;
        std::list<IndexTuple<>> indexByNameList;

        void reindex();

        template <class T>
        std::list<T>& fileToList(std::fstream&,
                                 std::list<T>&);

        template <class T>
        std::fstream& listToFile(const std::list<T>&, std::fstream&);

        template <class T>
        int getIndex(const std::list<T>&, const T&);

    public:
        MedicationFile();

        ~MedicationFile();

        void addData(const Medication&);
        void addData(std::list<Medication>&);

        void deleteData(const int&);  // index

        int findData(const Medication&);
        int findDataCode(std::string&);  // code
        int findDataName(std::string&);  // name

        Medication retrieve(const int&); //index

        std::list<Medication> toList();

        void clearFile();

        void compress();

        void importFromBackup(const std::string&);
        void exportToBackup(const std::string&);
    };

/// IMPLEMENTATION
using namespace std;

template <class T>
std::list<T>& MedicationFile::fileToList(std::fstream& file, std::list<T>& dataList) {
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
std::fstream& MedicationFile::listToFile(const std::list<T>& dataList, std::fstream& file) {
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
int MedicationFile::getIndex(const std::list<T>& dataList, const T& item) {
    int index = 0;
    for (const T& data : dataList) {
        if (data == item) {
            return index;
            }
        index++;
        }
    return -1;
    }

#endif  // __MEDICATIONFILE_HPP__
