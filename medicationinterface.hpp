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

    void addMedication();
    void deleteMedication();
    void searchByCode();
    void searchByName();
    void modifyMedication();
    void showList();
    void deleteAll();

    void importData();
    void exportData();

public:
    MedicationInterface();
    ~MedicationInterface();
};

#endif // MEDICATIONINTERFACE_HPP_INCLUDED
