#include "patientinterface.hpp"
using namespace std;

void PatientInterface::addPatient(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    Patient patient;
    Name name;
    Date birth;
    Address address;
    string str;
    int day, month, year, myInt;
    char opc, delimiter;

    do {
        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText("*** Nuevo paciente ***", 1);
        cout<<"*** Nuevo paciente ***";

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Número de Seguro Social: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        patient.setSocSecNum(str);

        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Nombre(s): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        name.setFirst(str);
        uiUtils.gotoxy(3, 8);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Apellido(s): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        name.setLast(str);
        patient.setName(name);

        uiUtils.gotoxy(3, 10);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Fecha de nacimiento (DD/MM/AAAA): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);

        if(sscanf(str.c_str(), "%d%c%d%c%d", &day, &delimiter, &month, &delimiter, &year) == 5 and delimiter=='/') {
            birth.setDay(day);
            birth.setMonth(month);
            birth.setYear(year);
            patient.setBirth(birth);
            }
        else {
            cout<<"Formato de fecha no válido. Use el formato DD/MM/AAAA."<<endl;
            }

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"\tDomicilio";
        uiUtils.gotoxy(3, 13);
        cout<<"Calle: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        address.setStreet(str);

        uiUtils.gotoxy(3, 14);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Número de casa: ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>myInt;
        cin.ignore();
        address.setHouseNum(myInt);

        uiUtils.gotoxy(3, 15);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Colonia: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        address.setColony(str);

        uiUtils.gotoxy(3, 16);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Código postal: ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>myInt;
        cin.ignore();
        address.setZipCode(myInt);

        uiUtils.gotoxy(3, 17);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Municipio: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        address.setLocality(str);
        patient.setAddress(address);

        uiUtils.gotoxy(3, 19);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Número telefónico: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        patient.setPhoneNum(str);

        filePtr->addData(patient);

        uiUtils.gotoxy(3, 21);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Desea agregar otro paciente? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();
        }
    while (opc == 'S');

    if (opc != 'S' and opc != 'N') {
        uiUtils.setColorText(TXT_RED);
        uiUtils.gotoxy(3, 23);
        cout << "Opción inválida!" << endl;
        }

    uiUtils.gotoxy(3, 25);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void PatientInterface::deletePatient(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    string ssn;
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Eliminar paciente ***", 1);
    cout << "*** Eliminar paciente ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el número de Seguro Social del paciente a eliminar: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, ssn);
    trim(ssn);
    cout<<ssn<<endl;

    int idx = filePtr->findData(ssn);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Paciente encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);

        // Obtener los detalles del paciente encontrado
        list<Patient> patientList = filePtr->toList();
        auto it = patientList.begin();
        advance(it, idx);
        Patient foundPatient = *it;

        // Mostrar los detalles del paciente encontrado
        cout << foundPatient.toString() << endl << endl;

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "¿Está seguro de eliminar este paciente? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();

        if (opc == 'S') {
            filePtr->deleteData(idx);
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_GREEN);
            cout << "Paciente eliminado exitosamente." << endl;
            }
        else if (opc == 'N') {
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_YELLOW);
            cout << "Operación de eliminación cancelada." << endl;
            }
        else {
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_RED);
            cout << "Opción inválida." << endl;
            }
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se encontró ningún paciente con el SSN proporcionado." << endl;
        }

    uiUtils.gotoxy(3, 16);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void PatientInterface::searchBySsn(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    string ssn;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Buscar paciente por SSN ***", 1);
    cout << "*** Buscar paciente por SSN ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el número de Seguro Social del paciente: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, ssn);

    int idx = filePtr->findData(ssn);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Paciente encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);

        // Obtener los detalles del paciente encontrado
        list<Patient> patientList = patientFilePtr->toList();
        auto it = patientList.begin();
        advance(it, idx);
        Patient foundPatient = *it;

        // Mostrar los detalles del paciente encontrado
        cout<<foundPatient.toString()<<endl;
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se encontró ningún paciente con el SSN proporcionado." << endl;
        }

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void PatientInterface::searchByName(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    Name name;
    string str;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Buscar paciente por nombre ***", 1);
    cout << "*** Buscar paciente por nombre ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Nombre(s): ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, str);
    name.setFirst(str);

    uiUtils.gotoxy(3, 6);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Apellido(s): ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, str);
    name.setLast(str);

    int idx=filePtr->findData(name);

    if (idx != -1) {
        uiUtils.gotoxy(3, 8);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Pacientes encontrados:" << endl;
        uiUtils.setColorText(TXT_CYAN);

        // Obtener los detalles del paciente encontrado
        list<Patient> patientList = patientFilePtr->toList();
        auto it = patientList.begin();
        advance(it, idx);
        Patient foundPatient = *it;

        // Mostrar los detalles del paciente encontrado
        cout<<foundPatient.toString()<<endl;
        }
    else {
        uiUtils.gotoxy(3, 8);
        uiUtils.setColorText(TXT_RED);
        cout << "No se encontraron pacientes con el nombre proporcionado." << endl;
        }


    uiUtils.gotoxy(3, 10);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void PatientInterface::modifyPatient(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    string ssn;
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Modificar paciente ***", 1);
    cout << "*** Modificar paciente ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el número de Seguro Social (SSN) del paciente a modificar: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, ssn);

    int idx = filePtr->findData(ssn);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Paciente encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);

        list<Patient> patientList = filePtr->toList();
        auto it = patientList.begin();
        advance(it, idx);
        Patient foundPatient = *it;

        cout<<foundPatient.toString()<<endl;

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "¿Desea modificar este paciente? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();

        if (opc == 'S') {
            // Aquí puedes implementar la lógica para modificar los datos del paciente
            // Puedes pedir al usuario que ingrese los nuevos datos y actualizarlos en el objeto `foundPatient`
            // Luego, guarda los cambios en el archivo usando `patientFilePtr->updateData(idx, foundPatient);`

            // Ejemplo:
            // string newName;
            // uiUtils.gotoxy(3, 14);
            // uiUtils.setColorText(TXT_CYAN);
            // cout << "Ingrese el nuevo nombre: ";
            // uiUtils.setColorText(TXT_WHITE);
            // getline(cin, newName);
            // foundPatient.setName(newName);
            // patientFilePtr->updateData(idx, foundPatient);

            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_GREEN);
            cout << "Paciente modificado exitosamente." << endl;
            }
        else if (opc == 'N') {
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_YELLOW);
            cout << "Operación de modificación cancelada." << endl;
            }
        else {
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_RED);
            cout << "Opción inválida." << endl;
            }
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se encontró ningún paciente con el SSN proporcionado." << endl;
        }

    uiUtils.gotoxy(3, 16);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void PatientInterface::showList(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Lista de pacientes ***", 1);
    cout << "*** Lista de pacientes ***";

    list<Patient> patientList = filePtr->toList();

    if (!patientList.empty()) {
        uiUtils.setColorText(TXT_CYAN);
        cout << "Número de Seguro Social (SSN)\tNombre\tFecha de nacimiento\tDirección" << endl;

        for (const Patient& patient : patientList) {
            cout<<patient.toString()<<endl;
            }
        }
    else {
        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_RED);
        cout << "No hay pacientes registrados." << endl;
        }

    uiUtils.gotoxy(3, 7);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void PatientInterface::deleteAll(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Eliminar todos los pacientes ***", 1);
    cout << "*** Eliminar todos los pacientes ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "¿Está seguro de eliminar todos los pacientes? (s/n): ";
    uiUtils.setColorText(TXT_WHITE);
    cin >> opc;
    opc = toupper(opc);
    cin.ignore();

    if (opc == 'S') {
        filePtr->clearFile();
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Todos los médicos han sido eliminados." << endl;
        }
    else if (opc == 'N') {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_YELLOW);
        cout << "Operación de eliminación cancelada." << endl;
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "Opción inválida." << endl;
        }

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void PatientInterface::importData(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    list<Patient> patientList;
    string str;

    system("cls");

    cout << "--- Importar datos de pacientes ---" << endl << endl;
    cout << "Nombre del archivo a importar: ";
    getline(cin, str);

    try {
        patientList = filePtr->importFromBackup(str);
        }
    catch (const ios_base::failure& ex) {
        cout << "Error al tratar de leer el archivo " << str << endl
             << ex.what() << endl;

        uiUtils.enterToContinue();
        }

    cout << "Archivo leído correctamente" << endl;
    cout << "Pacientes importados:" << endl << endl;

    for (const Patient& patient : patientList) {
        cout << patient.toString() << endl << endl;
        }

    cout << endl << endl;
    uiUtils.enterToContinue();
    }

void PatientInterface::exportData(PatientFile* filePtr) {
    UserInterfaceUtils uiUtils;
    string fileName;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Exportar datos de pacientes ***", 1);
    cout << "*** Exportar datos de pacientes ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el nombre del archivo de exportación: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, fileName);

    list<Patient> patList=filePtr->toList();
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se pudo abrir el archivo de destino." << endl;
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        return;
        }

    for (const Patient& patient : patList) {
        outputFile<<patient<<endl;
        }

    outputFile.close();

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_GREEN);
    cout << "Datos exportados exitosamente." << endl;

    uiUtils.gotoxy(3, 11);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

PatientInterface::PatientInterface() {
    UserInterfaceUtils uiUtils;
    patientFilePtr=new PatientFile();
    bool repeat = true;
    int opc;

    string title ="*** P A C I E N T E S ***";
    vector<string> options = {"Nuevo paciente", "Eliminar paciente",
                              "Buscar por número de seguridad social",
                              "Buscar por nombre",
                              "Modificar paciente",
                              "Mostrar lista",
                              "Eliminar todo",
                              "Importar del archivo de respaldo",
                              "Exportar a un archivo de respaldo", "Regresar"
                             };
    int numOpt=10;

    do {
        system("title FARMACIA GUANATOS: PACIENTE");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_VIOLET);

        switch(opc) {
            case 1:
                addPatient(patientFilePtr);
                break;

            case 2:
                deletePatient(patientFilePtr);
                break;

            case 3:
                searchBySsn(patientFilePtr);
                break;

            case 4:
                searchByName(patientFilePtr);
                break;

            case 5:
                modifyPatient(patientFilePtr);
                break;

            case 6:
                showList(patientFilePtr);
                break;

            case 7:
                deleteAll(patientFilePtr);
                break;

            case 8:
                importData(patientFilePtr);
                break;

            case 9:
                exportData(patientFilePtr);
                break;

            case 10:
                repeat=false;
                break;
            }

        }
    while(repeat);
    }

PatientInterface::~PatientInterface() {
    delete patientFilePtr;
    }


void PatientInterface::trim(string &str) {
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    }
