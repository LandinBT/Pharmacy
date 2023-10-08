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

  std::fstream dataFile;
  std::fstream indexByCode;

  std::list<IndexTuple<>> indexByCodeList;

  void reindex();

  template <class T>
  std::list<IndexTuple<T>>& fileToList(std::fstream&,
                                       std::list<IndexTuple<T>>&);

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
  int findData(std::string&);

  std::list<Diagnosis> toList();

  void clearFile();

  void compress();
};

/// IMPLEMENTATION
using namespace std;

template <class T>
list<IndexTuple<T>>& DiagnosisFile::fileToList(fstream& myFstream,
                                            list<IndexTuple<T>>& myList) {
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
fstream& DiagnosisFile::listToFile(const list<T>& myList, fstream& myFstream) {
  for (auto it = myList.begin(); it != myList.end(); it++) {
    myFstream << "1*" << *it << "#";
  }

  return myFstream;
}

template <class T>
int DiagnosisFile::getIndex(const list<T>& iList, const T& elem) {
  int index = 0;

  for (typename std::list<T>::const_iterator it = iList.begin();
       it != iList.end(); ++it) {
    if (*it == elem) {
      return index;  // Retorna el índice encontrado
    }
    index++;
  }

  return -1;  // No se encontró la coincidencia
}

#endif  // __DIAGNOSISFILE_HPP__