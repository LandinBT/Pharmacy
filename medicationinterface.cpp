#include "medicationinterface.hpp"
using namespace std;

void MedicationInterface::addMedication() {
    UserInterfaceUtils uiUtils;
    Medication medication;
    string str, title = "*** Nuevo Medicamento ***";
    char opc;

    do {
        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout << title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Código: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        medication.setCode(str);

        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Nombre: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        medication.setName(str);

        // Validar que el código y el nombre no estén vacíos
        if (medication.getCode().empty() or medication.getName().empty()) {
            uiUtils.gotoxy(3, 11);
            uiUtils.setColorText(TXT_RED);
            cout << "Código y nombre son obligatorios. Inténtalo de nuevo." << endl;
            continue;  // Volver a solicitar los datos si no son válidos
            }

        // Agregar el medicamento solo si el código no existe ya
        int existingIndex = medicationFilePtr->findData(medication);
        if (existingIndex != -1) {
            uiUtils.gotoxy(3, 11);
            uiUtils.setColorText(TXT_RED);
            cout << "Ya existe un medicamento con este código. Inténtalo de nuevo." << endl;
            continue;  // Volver a solicitar los datos si no son válidos
            }

        medicationFilePtr->addData(medication);

        uiUtils.gotoxy(3, 13);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Desea agregar otro medicamento? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();
        }
    while (opc == 'S');

    if (opc != 'S' && opc != 'N') {
        uiUtils.setColorText(TXT_RED);
        uiUtils.gotoxy(3, 15);
        cout << "Opción inválida!" << endl;
        }

    uiUtils.gotoxy(3, 17);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::deleteMedication() {
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
    cout<<"Ingrese el código: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, code);
    medication.setCode(code);

    int idx=medicationFilePtr->findData(medication);

    if(idx!=-1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Medicamento encontrado:";

        list<Medication> medList=medicationFilePtr->toList();
        auto it=medList.begin();
        advance(it, idx);
        Medication foundMed=*it;

        uiUtils.gotoxy(3, 9);
        uiUtils.setColorText(TXT_BLUE);
        cout<<foundMed.toString();

        uiUtils.gotoxy(3, 13);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Está seguro de eliminar este medicamento? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>opc;
        opc=toupper(opc);
        cin.ignore();

        if(opc=='S') {
            medicationFilePtr->deleteData(idx);
            uiUtils.gotoxy(3, 15);
            uiUtils.setColorText(TXT_GREEN);
            cout<<"Medicamento eliminado exitosamente.";
            }
        else if(opc=='N') {
            uiUtils.gotoxy(3, 15);
            uiUtils.setColorText(TXT_YELLOW);
            cout<<"Operación de eliminación cancelada.";
            }
        else {
            uiUtils.gotoxy(3, 15);
            uiUtils.setColorText(TXT_RED);
            cout<<"Opción inválida!";
            }
        }

    uiUtils.gotoxy(3, 17);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::searchByCode() {
    UserInterfaceUtils uiUtils;
    Medication medication;
    string code, title="*** Buscar medicamento por código ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el código del medicamento: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, code);

    int idx = medicationFilePtr->findDataCode(code);

    list<Medication> medList = medicationFilePtr->toList();

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Medicamento encontrado:";

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
        cout<<"No se encontró ningún medicamento con el código "<<code;
        }

    uiUtils.gotoxy(3, 11);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::searchByName() {
    UserInterfaceUtils uiUtils;
    Medication medication;
    string name, title="*** Buscar medicamento por nombre ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el nombre del medicamento: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, name);

    int idx = medicationFilePtr->findDataName(name);

    list<Medication> medList = medicationFilePtr->toList();

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Medicamento encontrado:";

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
        cout<<"No se encontró ningún medicamento con el nombre "<<name;
        }

    uiUtils.gotoxy(3, 11);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::modifyMedication() {
    /*    UserInterfaceUtils uiUtils;
        Medication medication;
        string code, title="*** Modificar medicamento ***";

        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout<<title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Ingrese el código del medicamento: ";
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
            cout<<"No se encontró ningún medicamento con el código "<<code;
            }

        uiUtils.gotoxy(3, 11);
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        */
    }

void MedicationInterface::showList() {
    UserInterfaceUtils uiUtils;
    string title="*** Lista de medicamentos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    try {
        list<Medication> medList = medicationFilePtr->toList();

        if (!medList.empty()) {
            uiUtils.gotoxy(3, 5);
            uiUtils.setColorText(TXT_BLUE);
            cout<<"Código\tNombre"<<endl<<endl;

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
        cout<<"Algo salió mal: "<<ex.what()<<endl<<endl;
        }

    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::deleteAll() {
    UserInterfaceUtils uiUtils;
    string title="*** Eliminar todos los medicamentos ***";
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout<<"¿Está seguro de eliminar todos los medicamentos? (s/n): ";
    uiUtils.setColorText(TXT_WHITE);
    cin>>opc;
    opc = toupper(opc);
    cin.ignore();

    if(opc=='S') {
        medicationFilePtr->clearFile();
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Todos los medicamentos han sido eliminados.";
        }
    else if(opc=='N') {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_YELLOW);
        cout<<"Operación de eliminación cancelada.";
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout<<"Opción inválida.";
        }

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::importData() {
    UserInterfaceUtils uiUtils;
    list<Medication> medList;
    string str, title="*** Recuperar datos de medicamentos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    cout<<"Nombre del archivo: ";
    getline(cin, str);

    try {
        medicationFilePtr->importFromBackup(str);
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
    cout<<"Archivo leído correctamente";
    uiUtils.gotoxy(3, 7);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void MedicationInterface::exportData() {
    UserInterfaceUtils uiUtils;
    string str, title="*** Guardar datos de medicamentos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    cout<<"Nombre del archivo: ";
    getline(cin, str);

    try {
        medicationFilePtr->exportToBackup(str);
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
                              "Buscar por código", "Buscar por nombre",
                              "Modificar medicamento", "Mostrar lista",
                              "Eliminar todo", "Recuperar", "Guardar",
                              "Regresar"
                             };
    int numOpt=10;

    do {
        system("title FARMACIA GUANATOS: MEDICAMENTO");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_VIOLET);

        switch(opc) {
            case 1:
                addMedication();
                break;

            case 2:
                deleteMedication();
                break;

            case 3:
                searchByCode();
                break;

            case 4:
                searchByName();
                break;

            case 5:
                modifyMedication();
                break;

            case 6:
                showList();
                break;

            case 7:
                deleteAll();
                break;

            case 8:
                importData();
                break;

            case 9:
                exportData();
                break;

            case 10:
                repeat=false;
                break;
            }

        }
    while(repeat);
    }

MedicationInterface::~MedicationInterface() {
    delete medicationFilePtr;
    }
