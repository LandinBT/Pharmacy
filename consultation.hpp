#ifndef __CONSULTATION_HPP__
#define __CONSULTATION_HPP__

#include <iostream>
#include <string>

#include "date.hpp"
#include "diagnosis.hpp"
#include "doctor.hpp"
#include "medication.hpp"
#include "patient.hpp"
#include "time.hpp"

class Consultation {
  Date date;
  Time time;
  std::string diagnosisCode;
  std::string therapIndic;  // therapeutic indications
  std::string doctorEmpCode;
  std::string patientSSN;
  std::string med1Code;  // medication1
  std::string med2Code;  // medication2
  std::string med3Code;  // medication3

 public:
  Consultation();
  Consultation(const Consultation&);

  Consultation operator=(const Consultation&);

  Date getDate() const;
  Time getTime() const;
  std::string getDiagnosisCode() const;
  std::string getTherapIndic() const;
  std::string getDoctorEmpCode() const;
  std::string getPatientSSN() const;
  std::string getMed1Code() const;
  std::string getMed2Code() const;
  std::string getMed3Code() const;

  std::string toString() const;

  void setDate(const Date&);
  void setTime(const Time&);
  void setDiagnosisCode(const std::string&);
  void setTherapIndic(const std::string&);
  void setDoctorEmpCode(const std::string&);
  void setPatientSSN(const std::string&);
  void setMed1Code(const std::string&);
  void setMed2Code(const std::string&);
  void setMed3Code(const std::string&);

  bool operator==(const Consultation&) const;
  bool operator!=(const Consultation&) const;
  bool operator<(const Consultation&) const;
  bool operator<=(const Consultation&) const;
  bool operator>(const Consultation&) const;
  bool operator>=(const Consultation&) const;

  friend std::istream& operator>>(std::istream&, Consultation&);
  friend std::ostream& operator<<(std::ostream&, const Consultation&);
};

#endif  // __CONSULTATION_HPP__
