#ifndef DOCTORINTERFACE_HPP_INCLUDED
#define DOCTORINTERFACE_HPP_INCLUDED

#include<iostream>
#include<string>
#include<list>

#include "userinterfaceutils.hpp"
#include "doctorfile.hpp"
#include "doctor.hpp"
#include "name.hpp"
#include "time.hpp"

class DoctorInterface {
        void addDoctor(list<Doctor>*);
        void deleteDoctor(list<Doctor>*);
        void modifyDoctor(list<Doctor>*);
        void showList(list<Doctor>*);
        void deleteAll(list<Doctor>*);

        void importData(list<Doctor>*);
        void exportData(list<Doctor>*);

    public:
        DoctorInterface();
    };

#endif // DOCTORINTERFACE_HPP_INCLUDED
