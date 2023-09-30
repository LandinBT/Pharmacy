#include "consultationinterface.hpp"
using namespace std;

void ConsultationInterface::addConsultation() {

    }

void ConsultationInterface::deleteConsultation() {

    }

void ConsultationInterface::modifyConsultation() {

    }

void ConsultationInterface::showList() {

    }

void ConsultationInterface::deleteAll() {}

void ConsultationInterface::importData() {
    UserInterfaceUtils uiUtils;
    ConsultationFile consultFile;
    list<Consultation> consultList;
    string str;

    system("cls");

    cout << "--- Importar datos ---" << endl << endl;
    cout << "Nombre del archivo a importar: ";
    getline(cin, str);

    try {
        consultList = consultFile.importFromBackup(str);
        }
    catch(const ios_base::failure& ex) {
        cout << "Error al tratar de leer el archivo " << str << endl
             << ex.what() << endl;

        uiUtils.enterToContinue();
        }

    cout << "Archivo leido correctamente" << endl
         << "En realidad no puedo importar todavia pero mostrare lo que he leido" << endl << endl; // borrar esta linea luego
    for(list<Consultation>::iterator it(consultList.begin()); it != consultList.end(); it++) {
        cout << it->toString() << endl << endl;
        }

    cout << endl << endl;
    uiUtils.enterToContinue();
    }

void ConsultationInterface::exportData() {

    }

ConsultationInterface::ConsultationInterface() {
    UserInterfaceUtils uiUtils;
    bool repeat = true;
    int opc;

    string title ="*** C O N S U L T A S ***";
    vector<string> options = {"Nueva consulta", "Eliminar consulta",
                              "Modificar consulta","Mostrar consultas",
                              "Eliminar todo",
                              "Importar del archivo de respaldo",
                              "Exportar a un archivo de respaldo", "Regresar"
                             };
    int numOpt=8;

    do {
        system("title FARMACIA GUANATOS: CONSULTA");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_VIOLET);

        switch(opc) {
            case 1:
                addConsultation();
                break;

            case 2:
                deleteConsultation();
                break;

            case 3:
                modifyConsultation();
                break;

            case 4:
                showList();
                break;

            case 5:
                deleteAll();
                break;

            case 6:
                importData();
                break;

            case 7:
                exportData();
                break;

            case 8:
                repeat=false;
                break;
            }

        }
    while(repeat);
    }
