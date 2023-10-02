#ifndef PATIENTINTERFACE_HPP_INCLUDED
#define PATIENTINTERFACE_HPP_INCLUDED

#include <iostream>
#include<fstream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include <cstdio> //sscanf
#include <algorithm> //trim
#include <cctype> //trim
#include <functional> //trim

#include "userinterfaceutils.hpp"
#include "patientfile.hpp"
#include "patient.hpp"
#include "address.hpp"
#include "date.hpp"
#include "name.hpp"

class PatientInterface {
        PatientFile* patientFilePtr;

        void addPatient(PatientFile*);
        void deletePatient(PatientFile*);
        void searchBySsn(PatientFile*);
        void searchByName(PatientFile*);
        void modifyPatient(PatientFile*);
        void showList(PatientFile*);
        void deleteAll(PatientFile*);

        void importData(PatientFile*);
        void exportData(PatientFile*);

    public:
        PatientInterface();
        ~PatientInterface();

        void trim(string&);
    };

#endif // PATIENTINTERFACE_HPP_INCLUDED
