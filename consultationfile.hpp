#ifndef __CONSULTATIONFILE_HPP__
#define __CONSULTATIONFILE_HPP__

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <sstream> //stringstream

#include "consultation.hpp"
#include "diagnosis.hpp"
#include "doctor.hpp"
#include "patient.hpp"
#include "medication.hpp"
#include "name.hpp"
#include "date.hpp"
#include "time.hpp"

class ConsultationFile {
  std::fstream dataFile;

 public:
  ConsultationFile();

  ~ConsultationFile();

  void addData(const Consultation&);
  void addData(const std::list<Consultation>&);

  std::list<Consultation> toList() const;

  void exportToBackup(const std::string&);
  std::list<Consultation> importFromBackup(const std::string&);

  void clearFile();
};

#endif  // __CONSULTATIONFILE_HPP__
