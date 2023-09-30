#include "doctorinterface.hpp"
using namespace std;

void DoctorInterface::addDoctor() {
    UserInterfaceUtils uiUtils;
    Doctor doctor;
    Name name;
    Time arrival;
    Time departure;
    string title = "*** Nuevo médico ***";
    string str, hourStr, minuteStr;
    char opc;

    do {
        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout << title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout << "Código de empleado: ";
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
        cout << "Cédula: ";
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
        cout << "Desea agregar otro médico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();
        }
    while (opc == 'S');

    if (opc != 'S' && opc != 'N') {
        uiUtils.setColorText(TXT_RED);
        uiUtils.gotoxy(3, 18);
        cout << "Opción inválida!" << endl;
        }

    uiUtils.gotoxy(3, 20);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();

    // Agrega el médico a la lista de médicos
    DoctorFile doctorFile;
    doctorFile.addData(doctor);
    }

void DoctorInterface::deleteDoctor() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;
    int idx;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Eliminar médico ***", 1);
    cout << "*** Eliminar médico ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el código de empleado del médico a eliminar: ";
    uiUtils.setColorText(TXT_WHITE);
    string code;
    getline(cin, code);

    idx = doctorFile.findData(code);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Médico encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);
        Doctor doctor = doctorFile.toList()[idx];
        cout << "Código de empleado: " << doctor.getEmpCode() << endl;
        cout << "Nombre: " << doctor.getName() << endl;
        cout << "Cédula: " << doctor.getCertificate() << endl;
        cout << "Hora de entrada: " << doctor.getArrival().toString() << endl;
        cout << "Hora de salida: " << doctor.getDeparture().toString() << endl;

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "¿Está seguro de eliminar este médico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        char opc;
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();

        if (opc == 'S') {
            doctorFile.deleteData(idx);
            uiUtils.gotoxy(3, 14);
            uiUtils.setColorText(TXT_GREEN);
            cout << "Médico eliminado exitosamente." << endl;
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
        cout << "No se encontró ningún médico con el código de empleado proporcionado." << endl;
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
    uiUtils.centerText("*** Modificar médico ***", 1);
    cout << "*** Modificar médico ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el código de empleado del médico a modificar: ";
    uiUtils.setColorText(TXT_WHITE);
    string code;
    getline(cin, code);

    idx = doctorFile.findData(code);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Médico encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);
        Doctor doctor = doctorFile.toList()[idx];
        cout << "Código de empleado: " << doctor.getEmpCode() << endl;
        cout << "Nombre: " << doctor.getName() << endl;
        cout << "Cédula: " << doctor.getCertificate() << endl;
        cout << "Hora de entrada: " << doctor.getArrival().toString() << endl;
        cout << "Hora de salida: " << doctor.getDeparture().toString() << endl;

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "¿Qué campo desea modificar?" << endl;
        uiUtils.setColorText(TXT_CYAN);
        cout << "1. Nombre" << endl;
        cout << "2. Cédula" << endl;
        cout << "3. Hora de entrada" << endl;
        cout << "4. Hora de salida" << endl;
        cout << "0. Cancelar" << endl;
        cout << "Opción: ";
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
                cout << "Nueva cédula: ";
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
                cout << "Operación de modificación cancelada." << endl;
                break;
            default:
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_RED);
                cout << "Opción inválida." << endl;
                break;
            }

        if (opc >= 1 && opc <= 4) {
            // Actualiza el médico modificado en el archivo de datos
            doctorFile.deleteData(idx);
            doctorFile.addData(doctor);

            uiUtils.gotoxy(3, 16);
            uiUtils.setColorText(TXT_GREEN);
            cout << "Médico modificado exitosamente." << endl;
            }
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se encontró ningún médico con el código de empleado proporcionado." << endl;
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
    uiUtils.centerText("*** Lista de Médicos ***", 1);
    cout << "*** Lista de Médicos ***" << endl;

    int idx = 0;
    for (const Doctor& doctor : doctorList) {
        idx++;
        cout << "Médico #" << idx << ":" << endl;
        cout << "Código de empleado: " << doctor.getEmpCode() << endl;
        cout << "Nombre: " << doctor.getName().getFullName() << endl;
        cout << "Cédula: " << doctor.getCertificate() << endl;
        cout << "Hora de entrada: " << doctor.getArrival().toString() << endl;
        cout << "Hora de salida: " << doctor.getDeparture().toString() << endl;
        cout << endl;
        }

    if (doctorList.empty()) {
        uiUtils.setColorText(TXT_YELLOW);
        cout << "La lista de médicos está vacía." << endl;
        }

    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::deleteAll() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Eliminar todos los Médicos ***", 1);
    cout << "*** Eliminar todos los Médicos ***" << endl;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "¿Está seguro de eliminar todos los médicos? (s/n): ";
    uiUtils.setColorText(TXT_WHITE);
    char opc;
    cin >> opc;
    opc = toupper(opc);
    cin.ignore();

    if (opc == 'S') {
        doctorFile.clearFile();
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

void DoctorInterface::importData() {
    UserInterfaceUtils uiUtils;
    DoctorFile doctorFile;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Importar Datos de Médicos ***", 1);
    cout << "*** Importar Datos de Médicos ***" << endl;

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
        cout << "El archivo de importación está vacío." << endl;
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
    uiUtils.centerText("*** Exportar Datos de Médicos ***", 1);
    cout << "*** Exportar Datos de Médicos ***" << endl;

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

    string title ="*** M É D I C O S ***";
    vector<string> options = {"Nuevo médico", "Eliminar médico",
                              "Modificar médico","Mostrar médicos",
                              "Eliminar todo",
                              "Importar del archivo de respaldo",
                              "Exportar a un archivo de respaldo", "Regresar"
                             };
    int numOpt=8;

    do {
        system("title FARMACIA GUANATOS: MÉDICO");
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
