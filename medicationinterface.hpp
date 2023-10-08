#ifndef MEDICATIONINTERFACE_HPP_INCLUDED
#define MEDICATIONINTERFACE_HPP_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include<list>
#include<vector>
#include <exception>

#include "userinterfaceutils.hpp"
#include "medicationfile.hpp"
#include "medication.hpp"

class MedicationInterface {
    MedicationFile* medicationFilePtr;

    void addMedication(MedicationFile*);
    void deleteMedication(MedicationFile*);
    void searchByCode(MedicationFile*);
    void modifyMedication(MedicationFile*);
    void showList(MedicationFile*);
    void deleteAll(MedicationFile*);

    void importData(MedicationFile*);
    void exportData(MedicationFile*);

public:
    MedicationInterface();
    ~MedicationInterface();
};

#endif // MEDICATIONINTERFACE_HPP_INCLUDED
