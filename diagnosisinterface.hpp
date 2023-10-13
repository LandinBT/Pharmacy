#ifndef DIAGNOSISINTERFACE_HPP_INCLUDED
#define DIAGNOSISINTERFACE_HPP_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include<list>
#include<vector>

#include "userinterfaceutils.hpp"
#include "diagnosisfile.hpp"
#include "diagnosis.hpp"

class DiagnosisInterface {
        DiagnosisFile* diagnosisFilePtr;

        void addDiagnosis();
        void deleteDiagnosis();
        void searchByCode();
        void searchByDesc();
        void modifyDiagnosis();
        void showList();
        void deleteAll();

        void importData();
        void exportData();

    public:
        DiagnosisInterface();
        ~DiagnosisInterface();
    };

#endif // DIAGNOSISINTERFACE_HPP_INCLUDED
