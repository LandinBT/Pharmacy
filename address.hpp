#ifndef __ADDRESS_HPP__
#define __ADDRESS_HPP__

#include <iostream>
#include <string>

class Address {
  std::string street;
  int houseNum;  // house number
  std::string colony;
  int zipCode;
  std::string locality;

 public:
  Address();
  Address(const Address&);

  Address& operator=(const Address&);

  std::string getStreet() const;
  int getHouseNum() const;
  std::string getColony() const;
  int getZipCode() const;
  std::string getLocality() const;

  std::string toString() const;

  void setStreet(const std::string&);
  void setHouseNum(const int&);
  void setColony(const std::string&);
  void setZipCode(const int&);
  void setLocality(const std::string&);

  bool operator==(const Address&) const;
  bool operator!=(const Address&) const;
  bool operator<(const Address&) const;
  bool operator<=(const Address&) const;
  bool operator>(const Address&) const;
  bool operator>=(const Address&) const;

  friend std::istream& operator>>(std::istream&, Address&);
  friend std::ostream& operator<<(std::ostream&, const Address&);
};

#endif  // __ADDRESS_HPP__