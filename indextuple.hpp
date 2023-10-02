#ifndef __INDEXTUPLE_HPP__
#define __INDEXTUPLE_HPP__

#include <iostream>
#include <string>

template <class T = std::string>
class IndexTuple {
        int index;
        T data;

    public:
        IndexTuple();
        IndexTuple(const IndexTuple&);
        IndexTuple(const int&, const T&);
        IndexTuple(const T&);

        IndexTuple& operator=(const IndexTuple&);
        IndexTuple& operator=(const T&);

        int getIndex() const;
        T getData() const;

        void setIndex(const int&);
        void setData(const T&);

        bool operator == (const IndexTuple&) const;
        bool operator != (const IndexTuple&) const;
        bool operator < (const IndexTuple&) const;
        bool operator <= (const IndexTuple&) const;
        bool operator > (const IndexTuple&) const;
        bool operator >= (const IndexTuple&) const;

        template<class U>
        friend std::istream& operator>>(std::istream&, IndexTuple<U>&);

        template<class U>
        friend std::ostream& operator<<(std::ostream&, IndexTuple<U>&);
    };

/// IMPLEMENTATION
using namespace std;

template <class T>
IndexTuple<T>::IndexTuple() {}

template <class T>
IndexTuple<T>::IndexTuple(const IndexTuple<T>& t)
    : index(t.index), data(t.data) {}

template <class T>
IndexTuple<T>::IndexTuple(const int& i, const T& d) : index(i), data(d) {}

template <class T>
IndexTuple<T>::IndexTuple(const T& d) : data(d) {}

template <class T>
IndexTuple<T>& IndexTuple<T>::operator=(const IndexTuple<T>& t) {
    index = t.index;
    data = t.data;

    return *this;
    }

template <class T>
IndexTuple<T>& IndexTuple<T>::operator=(const T& d) {
    data = d;

    return *this;
    }

template <class T>
int IndexTuple<T>::getIndex() const {
    return index;
    }

template <class T>
T IndexTuple<T>::getData() const {
    return data;
    }

template <class T>
void IndexTuple<T>::setIndex(const int& i) {
    index = i;
    }

template <class T>
void IndexTuple<T>::setData(const T& d) {
    data = d;
    }

template <class T>
bool IndexTuple<T>::operator==(const IndexTuple<T>& idxT) const {
    return index==idxT.index;
    }

template <class T>
bool IndexTuple<T>::operator!=(const IndexTuple<T>& idxT) const {
    return !(*this==idxT);
    }

template <class T>
bool IndexTuple<T>::operator<(const IndexTuple<T>& idxT) const {
    return index<idxT.index;
    }

template <class T>
bool IndexTuple<T>::operator<=(const IndexTuple<T>& idxT) const {
    return *this<idxT or *this==idxT;
    }

template <class T>
bool IndexTuple<T>::operator>(const IndexTuple<T>& idxT) const {
    return !(*this<=idxT);
    }

template <class T>
bool IndexTuple<T>::operator>=(const IndexTuple<T>& idxT) const {
    return !(*this<idxT);
    }

template <class U>
istream& operator>>(istream& is, IndexTuple<U>& t) {
    string str;

    getline(is, str, '*');
    t.index = stoi(str);

    is>>t.data;

    return is;
    }

template <class U>
ostream& operator<<(ostream& os, IndexTuple<U>& t) {
    os << t.index << '*';
    os << t.data << '*';

    return os;
    }

template <class T>
ostream& operator << (ostream& os, const IndexTuple<T>& t) {
    os << t.getIndex() << "*" << t.getData() << "*";
    return os;
    }

#endif  // __INDEXTUPLE_HPP__
