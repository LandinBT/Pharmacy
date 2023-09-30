#ifndef USERINTERFACE_HPP_INCLUDED
#define USERINTERFACE_HPP_INCLUDED

#include<iostream>
#include<string>

#include "userinterfaceutils.hpp"
#include"consultationinterface.hpp"
#include"doctorinterface.hpp"

class UserInterface {
        void consultationMenu();
        void diagnosisMenu();
        void doctorMenu();
        void patientMenu();
        void medicationMenu();

    public:
        UserInterface();
    };

#endif // USERINTERFACE_HPP_INCLUDED
