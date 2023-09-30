#ifndef __MEDICATION_HPP__
#define __MEDICATION_HPP__

#include <iostream>
#include <string>

class Medication {
  std::string code;
  std::string name;

 public:
  Medication();
  Medication(const Medication&);

  Medication& operator=(const Medication&);

  std::string getCode() const;
  std::string getName() const;

  std::string toString() const;

  void setCode(const std::string&);
  void setName(const std::string&);

  bool operator==(const Medication&) const;
  bool operator!=(const Medication&) const;
  bool operator<(const Medication&) const;
  bool operator<=(const Medication&) const;
  bool operator>(const Medication&) const;
  bool operator>=(const Medication&) const;

  friend std::istream& operator>>(std::istream&, Medication&);
  friend std::ostream& operator<<(std::ostream&, const Medication&);
};

#endif  // __MEDICATION_HPP__