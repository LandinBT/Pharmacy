#include "diagnosisinterface.hpp"
using namespace std;

void DiagnosisInterface::addDiagnosis(DiagnosisFile*) {

    }

void DiagnosisInterface::deleteDiagnosis(DiagnosisFile*) {

    }

void DiagnosisInterface::searchByCode(DiagnosisFile*) {

    }

void DiagnosisInterface::modifyDiagnosis(DiagnosisFile*) {

    }

void DiagnosisInterface::showList(DiagnosisFile*) {

    }

void DiagnosisInterface::deleteAll(DiagnosisFile*) {

    }

void DiagnosisInterface::importData(DiagnosisFile*) {

    }

void DiagnosisInterface::exportData(DiagnosisFile*) {

    }

DiagnosisInterface::DiagnosisInterface() {
    UserInterfaceUtils uiUtils;
    diagnosisFilePtr=new DiagnosisFile();
    bool repeat = true;
    int opc;

    string title ="*** D I A G N Ó S T I C O S ***";
    vector<string> options = {"Nuevo diagnóstico", "Eliminar diagnóstico",
                              "Buscar por código", "Modificar diagnóstico",
                              "Mostrar lista", "Eliminar todo",
                              "Importar del archivo de respaldo",
                              "Exportar a un archivo de respaldo", "Regresar"
                             };
    int numOpt=9;

    do {
        system("title FARMACIA GUANATOS: DIAGNÓSTICO");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_VIOLET);

        switch(opc) {
            case 1:
                addDiagnosis(diagnosisFilePtr);
                break;

            case 2:
                deleteDiagnosis(diagnosisFilePtr);
                break;

            case 3:
                searchByCode(diagnosisFilePtr);
                break;

            case 4:
                modifyDiagnosis(diagnosisFilePtr);
                break;

            case 5:
                showList(diagnosisFilePtr);
                break;

            case 6:
                deleteAll(diagnosisFilePtr);
                break;

            case 7:
                importData(diagnosisFilePtr);
                break;

            case 8:
                exportData(diagnosisFilePtr);
                break;

            case 9:
                repeat=false;
                break;
            }

        }
    while(repeat);
    }

DiagnosisInterface::~DiagnosisInterface() {
    delete diagnosisFilePtr;
    }
