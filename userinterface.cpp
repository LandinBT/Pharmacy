#include "userinterface.hpp"
using namespace std;

void UserInterface::consultationMenu() {
    new ConsultationInterface();
    }

void UserInterface::diagnosisMenu() {
    new DiagnosisInterface();
    }

void UserInterface::doctorMenu() {
    new DoctorInterface();
    }

void UserInterface::patientMenu() {
    new PatientInterface();
    }

void UserInterface::medicationMenu() {
    new MedicationInterface();
    }

UserInterface::UserInterface() {
    UserInterfaceUtils uiUtils;
    bool repeat = true;
    int opc;

    string title ="F A R M A C I A    G U A N A T O S";
    vector<string> options = {"Consultas", "Diagnósticos", "Médicos",
                              "Pacientes", "Medicamentos", "Salir"
                             };
    int numOpt=6;

    do {
        system("title FARMACIA GUANATOS");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_CYAN);

        switch(opc) {
            case 1:
                consultationMenu();
                break;

            case 2:
                diagnosisMenu();
                break;

            case 3:
                doctorMenu();
                break;

            case 4:
                patientMenu();
                break;

            case 5:
                medicationMenu();
                break;

            case 6:
                repeat=false;
                break;
            }

        }
    while(repeat);
    }
