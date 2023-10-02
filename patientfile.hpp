#ifndef PATIENTFILE_HPP_INCLUDED
#define PATIENTFILE_HPP_INCLUDED

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <sstream>  //stringstream

#include "indextuple.hpp"
#include "patient.hpp"
#include "name.hpp"

class PatientFile {
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
        std::list<T>& fileToList(std::fstream&, std::list<T>&);

        template <class T>
        std::fstream& listToFile(const std::list<T>&, std::fstream&);

        template <class T>
        int getIndex(const std::list<IndexTuple<T>>&, const T&);

    public:
        PatientFile();
        ~PatientFile();

        void addData(const Patient&);
        void addData(std::list<Patient>&);

        void deleteData(const int&);  // index

        int findData(const Patient&);
        int findData(const std::string&);  // code
        int findData(const Name&);

        Patient retrieve(const int&); //index

        std::list<Patient> toList();

        void exportToBackup(const std::string&);
        std::list<Patient> importFromBackup(const std::string&);

        void clearFile();

        void compress();
    };

///IMPLEMENTATION
using namespace std;

template <class T>
list<T>& PatientFile::fileToList(fstream& myFstream, list<T>& myList) {
    string str;
    T data;

    while (!myFstream.eof()) {
        getline(myFstream, str, '#');

        if (str.empty()) {
            continue;
            }

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
fstream& PatientFile::listToFile(const list<T>& myList, fstream& myFstream) {
    for (auto it = myList.begin(); it != myList.end(); it++) {
        myFstream << "1*" << *it << "#";
        }

    return myFstream;
    }

template <class T>
int PatientFile::getIndex(const list<IndexTuple<T>>& myList, const T& elem) {
    int index = 0;

    for (const IndexTuple<T>& it : myList) {
        if (it.getData() == elem) {
            return index;
            }
        index++;
        }

    return -1; // Elemento no encontrado
    }

#endif // PATIENTFILE_HPP_INCLUDED
