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

  std::fstream dataFile;
  std::fstream indexByCode;

  std::list<IndexTuple<>> indexByCodeList;

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
  int findData(std::string&);  // code

  std::list<Medication> toList();

  void clearFile();

  void compress();

  void importFromBackup();
  void exportToBackup();
};

/// IMPLEMENTATION
using namespace std;

template <class T>
list<T>& MedicationFile::fileToList(
    fstream& myFstream, list<T>& myList) {
        string str;
        T data;

        while(!myFstream.eof()) {
            getline(myFstream, str, '#');

            if(str.empty()) continue;

            stringstream strStream(str);

            getline(strStream, str, '*');

            if(str=="1"){
                strStream>>data;
                myList.push_back(data);
            }
        }

        return myList;
    }

template <class T>
fstream& MedicationFile::listToFile(const list<T>& myList, fstream& myFstream) {
    for(auto it=myList.begin(); it!=myList.end(); it++){
        myFstream<<"1*"<<*it<<"#";
    }

    return myFstream;
}

template <class T>
int MedicationFile::getIndex(const list<T>& myList, const T& elem) {
    int idx=0;

    for(typename list<T>::const_iterator it=myList.begin(); it!=myList.end(); ++it) {
        if(*it==elem){
            return idx;
        }

        idx++;
    }

    return -1;
}

#endif  // __MEDICATIONFILE_HPP__
