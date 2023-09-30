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
int DoctorFile::getIndex(const list<T>& iList, const T& elem) {
    typename list<T>::iterator it(find(iList.begin(), iList.end(), elem));

    if(it==iList.end()) {
        return -1; // retornamos una posicio invalida
        }

    return it->getIndex();
    }

#endif  // __DOCTORFILE_HPP__
