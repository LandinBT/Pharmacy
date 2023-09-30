#ifndef __DIAGNOSIS_HPP__
#define __DIAGNOSIS_HPP__

#include <iostream>
#include <string>

class Diagnosis {
  std::string code;
  std::string desc;  // description

 public:
  Diagnosis();
  Diagnosis(const Diagnosis&);

  Diagnosis& operator=(const Diagnosis&);

  std::string getCode() const;
  std::string getDesc() const;

  std::string toString() const;

  void setCode(const std::string&);
  void setDesc(const std::string&);

  bool operator==(const Diagnosis&) const;
  bool operator!=(const Diagnosis&) const;
  bool operator<(const Diagnosis&) const;
  bool operator<=(const Diagnosis&) const;
  bool operator>(const Diagnosis&) const;
  bool operator>=(const Diagnosis&) const;

  friend std::istream& operator>>(std::istream&, Diagnosis&);
  friend std::ostream& operator<<(std::ostream&, const Diagnosis&);
};

#endif  // __DIAGNOSIS_HPP__