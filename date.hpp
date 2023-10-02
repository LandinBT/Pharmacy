#ifndef __DATE_HPP__
#define __DATE_HPP__

#include <iostream>
#include <string>
#include<sstream> //stringstream
#include <iomanip> //setw, setfill

class Date {
  int day;
  int month;
  int year;

  int toInt() const;

  bool isValid() const;

 public:
  Date();
  Date(const Date&);

  Date& operator=(const Date&);

  int getDay() const;
  int getMonth() const;
  int getYear() const;

  std::string toString() const;

  void setDay(const int&);
  void setMonth(const int&);
  void setYear(const int&);

  bool operator==(const Date&) const;
  bool operator!=(const Date&) const;
  bool operator<(const Date&) const;
  bool operator<=(const Date&) const;
  bool operator>(const Date&) const;
  bool operator>=(const Date&) const;

  friend std::istream& operator>>(std::istream&, Date&);
  friend std::ostream& operator<<(std::ostream&, const Date&);
};

#endif  // __DATE_HPP__
