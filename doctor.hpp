#ifndef __DOCTOR_HPP__
#define __DOCTOR_HPP__

#include <iostream>
#include <string>

#include "name.hpp"
#include "time.hpp"

class Doctor {
  std::string empCode;  // employee code
  Name name;
  std::string certificate;
  Time arrival;
  Time departure;

 public:
  Doctor();
  Doctor(const Doctor&);

  Doctor& operator=(const Doctor&);

  std::string getEmpCode() const;
  Name getName() const;
  std::string getCertificate() const;
  Time getArrival() const;
  Time getDeparture() const;

  std::string toString() const;

  void setEmpCode(const std::string&);
  void setName(const Name&);
  void setCertificate(const std::string&);
  void setArrival(const Time&);
  void setDeparture(const Time&);

  bool operator==(const Doctor&) const;
  bool operator!=(const Doctor&) const;
  bool operator<(const Doctor&) const;
  bool operator<=(const Doctor&) const;
  bool operator>(const Doctor&) const;
  bool operator>=(const Doctor&) const;

  friend std::istream& operator>>(std::istream&, Doctor&);
  friend std::ostream& operator<<(std::ostream&, const Doctor&);
};

#endif  // __DOCTOR_HPP__