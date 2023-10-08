#include "medicationinterface.hpp"
using namespace std;

void MedicationInterface::addMedication(MedicationFile* filePtr) {
    UserInterfaceUtils uiUtils;
    Medication medication;
    string str, title="*** Nuevo Medicamento ***";
    char opc;

    do {
        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout<<title;

        uiUtils.gotoxy(3,5);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"C�digo: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        medication.setCode(str);

        uiUtils.gotoxy(3,7);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Nombre: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        medication.setName(str);

        filePtr->addData(medication);

        uiUtils.gotoxy(3,9);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Desea agregar otro medicamento? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>opc;
        opc=toupper(opc);
        cin.ignore();
        }
    while(opc=='S');

    if(opc!='S' and opc!='N') {
        uiUtils.setColorText(TXT_RED);
        uiUtils.gotoxy(3, 11);
        cout<<"Opci�n inv�lida!"<<endl;
        }

    uiUtils.gotoxy(3, 13);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::deleteMedication(MedicationFile* filePtr) {
    UserInterfaceUtils uiUtils;
    Medication medication;
    string code, title="*** Eliminar medicamento ***";
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout<<"Ingrese el c�digo: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, code);
    medication.setCode(code);

    int idx=filePtr->findData(medication);

    if(idx!=-1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Medicamento encontrado:";

        list<Medication> medList=filePtr->toList();
        auto it=medList.begin();
        advance(it, idx);
        Medication foundMed=*it;

        uiUtils.gotoxy(3, 9);
        uiUtils.setColorText(TXT_BLUE);
        cout<<foundMed.toString();

        uiUtils.gotoxy(3, 13);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Est� seguro de eliminar este medicamento? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>opc;
        opc=toupper(opc);
        cin.ignore();

        if(opc=='S') {
            filePtr->deleteData(idx);
            uiUtils.gotoxy(3, 15);
            uiUtils.setColorText(TXT_GREEN);
            cout<<"Medicamento eliminado exitosamente.";
            }
        else if(opc=='N') {
            uiUtils.gotoxy(3, 15);
            uiUtils.setColorText(TXT_YELLOW);
            cout<<"Operaci�n de eliminaci�n cancelada.";
            }
        else {
            uiUtils.gotoxy(3, 15);
            uiUtils.setColorText(TXT_RED);
            cout<<"Opci�n inv�lida!";
            }

        uiUtils.gotoxy(3, 17);
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        }
    }

void MedicationInterface::searchByCode(MedicationFile* filePtr) {
    UserInterfaceUtils uiUtils;
    Medication medication;
    string code, title="*** Buscar medicamento ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el c�digo del medicamento: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, code);
    medication.setCode(code);

    int idx = filePtr->findData(medication);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Medicamento encontrado:";

        list<Medication> medList = filePtr->toList();
        auto it = medList.begin();
        advance(it, idx);
        Medication foundMed=*it;

        uiUtils.gotoxy(3, 9);
        uiUtils.setColorText(TXT_CYAN);
        cout<<foundMed.toString()<<endl;
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout<<"No se encontr� ning�n medicamento con el c�digo "<<code;
        }

    uiUtils.gotoxy(3, 11);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::modifyMedication(MedicationFile* filePtr) {
    /*    UserInterfaceUtils uiUtils;
        Medication medication;
        string code, title="*** Modificar medicamento ***";

        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout<<title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Ingrese el c�digo del medicamento: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, code);
        medication.setCode(code);

        int idx = filePtr->findData(medication);

        if (idx != -1) {
            uiUtils.gotoxy(3, 7);
            uiUtils.setColorText(TXT_GREEN);
            cout<<"Medicamento encontrado:";

            list<Medication> medList = filePtr->toList();
            auto it = medList.begin();
            advance(it, idx);
            Medication foundMed=*it;

            uiUtils.gotoxy(3, 9);
            uiUtils.setColorText(TXT_CYAN);
            cout<<foundMed.toString()<<endl;
            }
        else {
            uiUtils.gotoxy(3, 7);
            uiUtils.setColorText(TXT_RED);
            cout<<"No se encontr� ning�n medicamento con el c�digo "<<code;
            }

        uiUtils.gotoxy(3, 11);
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        */
    }

void MedicationInterface::showList(MedicationFile* filePtr) {
    UserInterfaceUtils uiUtils;
    string title="*** Lista de medicamentos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    try {
        list<Medication> medList = filePtr->toList();

        if (!medList.empty()) {
            uiUtils.gotoxy(3, 5);
            uiUtils.setColorText(TXT_BLUE);
            cout<<"C�digo\tNombre"<<endl<<endl;

            uiUtils.setColorText(TXT_CYAN);
            for(const Medication& medication : medList) {
                cout<<medication.toString()<<endl;
                }
            }
        else {
            uiUtils.gotoxy(3, 5);
            uiUtils.setColorText(TXT_RED);
            cout<<"No hay medicamentos registrados."<<endl;
            }
        }
    catch(const ios_base::failure& ex) {
        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_RED);
        cout<<"Algo sali� mal: "<<ex.what()<<endl<<endl;
        }

    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::deleteAll(MedicationFile* filePtr) {
    UserInterfaceUtils uiUtils;
    string title="*** Eliminar todos los pacientes ***";
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout<<"�Est� seguro de eliminar todos los medicamentos? (s/n): ";
    uiUtils.setColorText(TXT_WHITE);
    cin>>opc;
    opc = toupper(opc);
    cin.ignore();

    if(opc=='S') {
        filePtr->clearFile();
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Todos los medicamentos han sido eliminados.";
        }
    else if(opc=='N') {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_YELLOW);
        cout<<"Operaci�n de eliminaci�n cancelada.";
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout<<"Opci�n inv�lida.";
        }

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::importData(MedicationFile* filePtr) {
    UserInterfaceUtils uiUtils;
    list<Medication> medList;
    string title="*** Importar datos de medicamentos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    try {
        filePtr->importFromBackup();
        }
    catch (const ios_base::failure& ex) {
        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_RED);
        cout << "Error al tratar de leer el archivo "<<ex.what();
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        }

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_GREEN);
    cout<<"Archivo le�do correctamente";
    uiUtils.gotoxy(3, 7);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::exportData(MedicationFile* filePtr) {
    UserInterfaceUtils uiUtils;
    string title="*** Exportar datos de medicamentos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    try {
        filePtr->exportToBackup();
        }
    catch (const ios_base::failure& ex) {
        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_RED);
        cout << "Error al tratar de escribir en el archivo "<<ex.what();
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        }

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_GREEN);
    cout<<"Datos exportados exitosamente.";

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

MedicationInterface::MedicationInterface() {
    UserInterfaceUtils uiUtils;
    medicationFilePtr=new MedicationFile();
    bool repeat = true;
    int opc;

    string title ="*** M E D I C A M E N T O S ***";
    vector<string> options = {"Nuevo medicamento", "Eliminar medicamento",
                              "Buscar por c�digo", "Modificar medicamento",
                              "Mostrar lista", "Eliminar todo",
                              "Importar del archivo de respaldo",
                              "Exportar a un archivo de respaldo", "Regresar"
                             };
    int numOpt=9;

    do {
        system("title FARMACIA GUANATOS: MEDICAMENTO");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_VIOLET);

        switch(opc) {
            case 1:
                addMedication(medicationFilePtr);
                break;

            case 2:
                deleteMedication(medicationFilePtr);
                break;

            case 3:
                searchByCode(medicationFilePtr);
                break;

            case 4:
                modifyMedication(medicationFilePtr);
                break;

            case 5:
                showList(medicationFilePtr);
                break;

            case 6:
                deleteAll(medicationFilePtr);
                break;

            case 7:
                importData(medicationFilePtr);
                break;

            case 8:
                exportData(medicationFilePtr);
                break;

            case 9:
                repeat=false;
                break;
            }

        }
    while(repeat);
    }

MedicationInterface::~MedicationInterface() {
    delete medicationFilePtr;
    }
