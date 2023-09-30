#ifndef __PATIENT_HPP__
#define __PATIENT_HPP__

#include <iostream>
#include <string>
#include <algorithm> //remove

#include "address.hpp"
#include "date.hpp"
#include "name.hpp"

class Patient {
  std::string socSecNum;  // social security number
  Name name;
  Date birth;
  Address address;
  long phoneNum;  // phone number

 public:
  Patient();
  Patient(const Patient&);

  Patient& operator=(const Patient&);

  std::string getSocSecNum() const;
  Name getName() const;
  Date getBirth() const;
  Address getAddress() const;
  long getPhoneNum() const;

  std::string toString() const;

  void setSocSecNum(const std::string&);
  void setName(const Name&);
  void setBirth(const Date&);
  void setAddress(const Address&);
  void setPhoneNum(const long&);

  bool operator==(const Patient&) const;
  bool operator!=(const Patient&) const;
  bool operator<(const Patient&) const;
  bool operator<=(const Patient&) const;
  bool operator>(const Patient&) const;
  bool operator>=(const Patient&) const;

  friend std::istream& operator>>(std::istream&, Patient&);
  friend std::ostream& operator<<(std::ostream&, const Patient&);
};

#endif  // __PATIENT_HPP__
