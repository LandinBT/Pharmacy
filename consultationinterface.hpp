#ifndef CONSULTATIONINTERFACE_HPP_INCLUDED
#define CONSULTATIONINTERFACE_HPP_INCLUDED

#include<iostream>
#include<string>

#include "userinterfaceutils.hpp"
#include "consultationfile.hpp"
#include "consultation.hpp"

class ConsultationInterface {
        void addConsultation();
        void deleteConsultation();
        void modifyConsultation();
        void showList();
        void deleteAll();

        void importData();
        void exportData();

    public:
        ConsultationInterface();
    };

#endif // CONSULTATIONINTERFACE_HPP_INCLUDED
