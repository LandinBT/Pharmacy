#ifndef DOCTORINTERFACE_HPP_INCLUDED
#define DOCTORINTERFACE_HPP_INCLUDED

#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<vector>

#include "userinterfaceutils.hpp"
#include "doctorfile.hpp"
#include "doctor.hpp"
#include "name.hpp"
#include "time.hpp"

class DoctorInterface {
        DoctorFile* doctorFilePtr;

        void addDoctor(DoctorFile*);
        void deleteDoctor(DoctorFile*);
        void modifyDoctor(DoctorFile*);
        void showList(DoctorFile*);
        void deleteAll(DoctorFile*);

        void importData(DoctorFile*);
        void exportData(DoctorFile*);

    public:
        DoctorInterface();
        ~DoctorInterface();
    };

#endif // DOCTORINTERFACE_HPP_INCLUDED
