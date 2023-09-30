#ifndef __NAME_HPP__
#define __NAME_HPP__

#include <iostream>
#include <string>

class Name {
  std::string last;
  std::string first;

 public:
  Name();
  Name(const Name&);

  Name& operator=(const Name&);

  std::string getLast() const;
  std::string getFirst() const;

  std::string toString() const;

  void setLast(const std::string&);
  void setFirst(const std::string&);

  bool operator==(const Name&) const;
  bool operator!=(const Name&) const;
  bool operator<(const Name&) const;
  bool operator<=(const Name&) const;
  bool operator>(const Name&) const;
  bool operator>=(const Name&) const;

  friend std::istream& operator>>(std::istream&, Name&);
  friend std::ostream& operator<<(std::ostream&, const Name&);
};

#endif  // __NAME_HPP__