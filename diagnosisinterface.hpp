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

        void addDiagnosis(DiagnosisFile*);
        void deleteDiagnosis(DiagnosisFile*);
        void searchByCode(DiagnosisFile*);
        void modifyDiagnosis(DiagnosisFile*);
        void showList(DiagnosisFile*);
        void deleteAll(DiagnosisFile*);

        void importData(DiagnosisFile*);
        void exportData(DiagnosisFile*);

    public:
        DiagnosisInterface();
        ~DiagnosisInterface();
    };

#endif // DIAGNOSISINTERFACE_HPP_INCLUDED
