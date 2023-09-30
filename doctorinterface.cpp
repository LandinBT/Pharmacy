#include "doctorinterface.hpp"
using namespace std;

void DoctorInterface::addDoctor() {
    UserInterfaceUtils uiUtils;
    Doctor doctor;
    Name name;
    Time arrival;
    Time departure;
    string title = "*** Nuevo m�dico ***";
    string str, hourStr, minuteStr;
    char opc;

    do {
        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout << title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout << "C�digo de empleado: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        doctor.setEmpCode(str);

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
        doctor.setName(name);

        uiUtils.gotoxy(3, 10);
        uiUtils.setColorText(TXT_CYAN);
        cout << "C�dula: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        doctor.setCertificate(str);

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Hora de entrada(HH:MM): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        hourStr = str.substr(0, 2);
        minuteStr = str.substr(3, 2);
        arrival.setHour(stoi(hourStr));
        arrival.setMinute(stoi(minuteStr));
        doctor.setArrival(arrival);

        uiUtils.gotoxy(3, 14);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Hora de salida(HH:MM): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        hourStr = str.substr(0, 2);
        minuteStr = str.substr(3, 2);
        departure.setHour(stoi(hourStr));
        departure.setMinute(stoi(minuteStr));
        doctor.setDeparture(departure);

        uiUtils.gotoxy(3, 16);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Desea agregar otro m�dico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();
        }
    while (opc == 'S');

    if (opc != 'S' && opc != 'N') {
        uiUtils.setColorText(TXT_RED);
        uiUtils.gotoxy(3, 18);
        cout << "Opci�n inv�lida!" << endl;
        }

    uiUtils.gotoxy(3, 20);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();

    // Agrega el m�dico a la lista de m�dicos
    DoctorFile doctorFile;
    doctorFile.addData(doctor);
    }

void DoctorInterface::deleteDoctor() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;
    int idx;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Eliminar m�dico ***", 1);
    cout << "*** Eliminar m�dico ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el c�digo de empleado del m�dico a eliminar: ";
    uiUtils.setColorText(TXT_WHITE);
    string code;
    getline(cin, code);

    idx = doctorFile.findData(code);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "M�dico encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);
        Doctor doctor = doctorFile.toList()[idx];
        cout << "C�digo de empleado: " << doctor.getEmpCode() << endl;
        cout << "Nombre: " << doctor.getName() << endl;
        cout << "C�dula: " << doctor.getCertificate() << endl;
        cout << "Hora de entrada: " << doctor.getArrival().toString() << endl;
        cout << "Hora de salida: " << doctor.getDeparture().toString() << endl;

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "�Est� seguro de eliminar este m�dico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        char opc;
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();

        if (opc == 'S') {
            doctorFile.deleteData(idx);
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_GREEN);
            cout << "M�dico eliminado exitosamente." << endl;
            }
        else if (opc == 'N') {
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_YELLOW);
            cout << "Operaci�n de eliminaci�n cancelada." << endl;
            }
        else {
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_RED);
            cout << "Opci�n inv�lida." << endl;
            }
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se encontr� ning�n m�dico con el c�digo de empleado proporcionado." << endl;
        }

    uiUtils.gotoxy(3, 16);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::modifyDoctor() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;
    int idx;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Modificar m�dico ***", 1);
    cout << "*** Modificar m�dico ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el c�digo de empleado del m�dico a modificar: ";
    uiUtils.setColorText(TXT_WHITE);
    string code;
    getline(cin, code);

    idx = doctorFile.findData(code);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "M�dico encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);
        Doctor doctor = doctorFile.toList()[idx];
        cout << "C�digo de empleado: " << doctor.getEmpCode() << endl;
        cout << "Nombre: " << doctor.getName() << endl;
        cout << "C�dula: " << doctor.getCertificate() << endl;
        cout << "Hora de entrada: " << doctor.getArrival().toString() << endl;
        cout << "Hora de salida: " << doctor.getDeparture().toString() << endl;

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "�Qu� campo desea modificar?" << endl;
        uiUtils.setColorText(TXT_CYAN);
        cout << "1. Nombre" << endl;
        cout << "2. C�dula" << endl;
        cout << "3. Hora de entrada" << endl;
        cout << "4. Hora de salida" << endl;
        cout << "0. Cancelar" << endl;
        cout << "Opci�n: ";
        uiUtils.setColorText(TXT_WHITE);
        int opc;
        cin >> opc;
        cin.ignore();

        switch (opc) {
            case 1: {
                string firstName, lastName;
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nuevo nombre(s): ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, firstName);
                uiUtils.gotoxy(3, 15);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nuevo apellido(s): ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, lastName);
                doctor.setName(Name(firstName, lastName));
                break;
                }
            case 2: {
                string certificate;
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nueva c�dula: ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, certificate);
                doctor.setCertificate(certificate);
                break;
                }
            case 3: {
                string hourStr, minuteStr;
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nueva hora de entrada (HH:MM): ";
                uiUtils.setColorText(TXT_WHITE);
                string timeStr;
                getline(cin, timeStr);
                hourStr = timeStr.substr(0, 2);
                minuteStr = timeStr.substr(3, 2);
                Time arrival(stoi(hourStr), stoi(minuteStr));
                doctor.setArrival(arrival);
                break;
                }
            case 4: {
                string hourStr, minuteStr;
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nueva hora de salida (HH:MM): ";
                uiUtils.setColorText(TXT_WHITE);
                string timeStr;
                getline(cin, timeStr);
                hourStr = timeStr.substr(0, 2);
                minuteStr = timeStr.substr(3, 2);
                Time departure(stoi(hourStr), stoi(minuteStr));
                doctor.setDeparture(departure);
                break;
                }
            case 0:
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_YELLOW);
                cout << "Operaci�n de modificaci�n cancelada." << endl;
                break;
            default:
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_RED);
                cout << "Opci�n inv�lida." << endl;
                break;
            }

        if (opc >= 1 && opc <= 4) {
            // Actualiza el m�dico modificado en el archivo de datos
            doctorFile.deleteData(idx);
            doctorFile.addData(doctor);

            uiUtils.gotoxy(3, 16);
            uiUtils.setColorText(TXT_GREEN);
            cout << "M�dico modificado exitosamente." << endl;
            }
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se encontr� ning�n m�dico con el c�digo de empleado proporcionado." << endl;
        }

    uiUtils.gotoxy(3, 18);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::showList() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;
    list<Doctor> doctorList = doctorFile.toList();

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Lista de M�dicos ***", 1);
    cout << "*** Lista de M�dicos ***" << endl;

    int idx = 0;
    for (const Doctor& doctor : doctorList) {
        idx++;
        cout << "M�dico #" << idx << ":" << endl;
        cout << "C�digo de empleado: " << doctor.getEmpCode() << endl;
        cout << "Nombre: " << doctor.getName().getFullName() << endl;
        cout << "C�dula: " << doctor.getCertificate() << endl;
        cout << "Hora de entrada: " << doctor.getArrival().toString() << endl;
        cout << "Hora de salida: " << doctor.getDeparture().toString() << endl;
        cout << endl;
        }

    if (doctorList.empty()) {
        uiUtils.setColorText(TXT_YELLOW);
        cout << "La lista de m�dicos est� vac�a." << endl;
        }

    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::deleteAll() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Eliminar todos los M�dicos ***", 1);
    cout << "*** Eliminar todos los M�dicos ***" << endl;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "�Est� seguro de eliminar todos los m�dicos? (s/n): ";
    uiUtils.setColorText(TXT_WHITE);
    char opc;
    cin >> opc;
    opc = toupper(opc);
    cin.ignore();

    if (opc == 'S') {
        doctorFile.clearFile();
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Todos los m�dicos han sido eliminados." << endl;
        }
    else if (opc == 'N') {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_YELLOW);
        cout << "Operaci�n de eliminaci�n cancelada." << endl;
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "Opci�n inv�lida." << endl;
        }

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::importData() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Importar Datos de M�dicos ***", 1);
    cout << "*** Importar Datos de M�dicos ***" << endl;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el nombre del archivo a importar: ";
    uiUtils.setColorText(TXT_WHITE);
    string fileName;
    getline(cin, fileName);

    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se pudo abrir el archivo especificado." << endl;
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        return;
        }

    list<Doctor> importList;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        Doctor doctor;
        ss >> doctor;
        importList.push_back(doctor);
        }

    inputFile.close();

    if (!importList.empty()) {
        doctorFile.addData(importList);
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Datos importados exitosamente." << endl;
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_YELLOW);
        cout << "El archivo de importaci�n est� vac�o." << endl;
        }

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::exportData() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Exportar Datos de M�dicos ***", 1);
    cout << "*** Exportar Datos de M�dicos ***" << endl;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el nombre del archivo de destino: ";
    uiUtils.setColorText(TXT_WHITE);
    string fileName;
    getline(cin, fileName);

    list<Doctor> doctorList = doctorFile.toList();
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se pudo abrir el archivo de destino." << endl;
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        return;
        }

    for (const Doctor& doctor : doctorList) {
        outputFile << doctor << endl;
        }

    outputFile.close();

    uiUtils.gotoxy(3, 9);
    uiUtils.setColorText(TXT_GREEN);
    cout << "Datos exportados exitosamente." << endl;

    uiUtils.gotoxy(3, 11);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

DoctorInterface::DoctorInterface() {
    UserInterfaceUtils uiUtils;
    bool repeat = true;
    int opc;

    string title ="*** M � D I C O S ***";
    vector<string> options = {"Nuevo m�dico", "Eliminar m�dico",
                              "Modificar m�dico","Mostrar m�dicos",
                              "Eliminar todo",
                              "Importar del archivo de respaldo",
                              "Exportar a un archivo de respaldo", "Regresar"
                             };
    int numOpt=8;

    do {
        system("title FARMACIA GUANATOS: M�DICO");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_VIOLET);

        switch(opc) {
            case 1:
                addDoctor();
                break;

            case 2:
                deleteDoctor();
                break;

            case 3:
                modifyDoctor();
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
