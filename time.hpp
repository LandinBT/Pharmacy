#ifndef __TIME_HPP__
#define __TIME_HPP__

#include <iostream>
#include <string>
#include <sstream> //stringstream
#include <iomanip> //setw, setfill

class Time {
  int hour;
  int minute;

  int toInt() const;

  bool isValid() const;

 public:
  Time();
  Time(const Time&);

  Time& operator=(const Time&);

  int getHour() const;
  int getMinute() const;

  std::string toString() const;

  void setHour(const int&);
  void setMinute(const int&);

  bool operator==(const Time&) const;
  bool operator!=(const Time&) const;
  bool operator<(const Time&) const;
  bool operator<=(const Time&) const;
  bool operator>(const Time&) const;
  bool operator>=(const Time&) const;

  friend std::istream& operator>>(std::istream&, Time&);
  friend std::ostream& operator<<(std::ostream&, const Time&);
};

#endif  // __TIME_HPP__
