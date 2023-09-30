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
  Diagnosis diagnosis;
  std::string therapIndic;  // therapeutic indications
  Doctor doctor;
  Patient patient;
  Medication med1;  // medication1
  Medication med2;  // medication2
  Medication med3;  // medication3

 public:
  Consultation();
  Consultation(const Consultation&);

  Consultation operator=(const Consultation&);

  Date getDate() const;
  Time getTime() const;
  Diagnosis getDiagnosis() const;
  std::string getTherapIndic() const;
  Doctor getDoctor() const;
  Patient getPatient() const;
  Medication getMed1() const;
  Medication getMed2() const;
  Medication getMed3() const;

  std::string toString() const;

  void setDate(const Date&);
  void setTime(const Time&);
  void setDiagnosis(const Diagnosis&);
  void setTherapIndic(const std::string&);
  void setDoctor(const Doctor&);
  void setPatient(const Patient&);
  void setMed1(const Medication&);
  void setMed2(const Medication&);
  void setMed3(const Medication&);

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