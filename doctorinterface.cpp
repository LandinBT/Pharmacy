#include "doctorinterface.hpp"
using namespace std;

void DoctorInterface::addDoctor(DoctorFile* fileRef) {
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

        fileRef->addData(doctor);
        }
    while (opc == 'S');

    if (opc != 'S' and opc != 'N') {
        uiUtils.setColorText(TXT_RED);
        uiUtils.gotoxy(3, 18);
        cout << "Opción inválida!" << endl;
        }

    uiUtils.gotoxy(3, 20);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::deleteDoctor(DoctorFile* fileRef) {
    UserInterfaceUtils uiUtils;
    Doctor doctor;
    string code;
    int idx;
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Eliminar médico ***", 1);
    cout << "*** Eliminar médico ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Ingrese el código de empleado del médico a eliminar: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, code);

    idx=fileRef->findData(code);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Médico encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);

        // Obtener los detalles del médico encontrado
        list<Doctor> doctorList = fileRef->toList();
        auto it = doctorList.begin();
        advance(it, idx);
        Doctor foundDoctor = *it;

        // Mostrar los detalles del médico encontrado
        cout << "Código de empleado: " << foundDoctor.getEmpCode() << endl;
        cout << "Nombre: " << foundDoctor.getName().toString() << endl;
        cout << "Cédula: " << foundDoctor.getCertificate() << endl;
        cout << "Hora de entrada: " << foundDoctor.getArrival().toString() << endl;
        cout << "Hora de salida: " << foundDoctor.getDeparture().toString() << endl;
        cout << endl;

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout << "¿Está seguro de eliminar este médico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        opc = toupper(opc);
        cin.ignore();

        if (opc == 'S') {
            fileRef->deleteData(idx);
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

void DoctorInterface::modifyDoctor(DoctorFile* fileRef) {
    UserInterfaceUtils uiUtils;
    Doctor doctor;
    Time time;
    Name name;
    string str, hourStr, minuteStr;
    int idx;
    int opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Modificar médico ***", 1);
    cout<<"*** Modificar médico ***";

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout<<"Ingrese el código de empleado del médico a modificar: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, str);

    idx=fileRef->findData(str);

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout << "Médico encontrado:" << endl;
        uiUtils.setColorText(TXT_CYAN);
        //Doctor doctor = doctorFile.toList()[idx];
        //mostrar doctor encontrado

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"¿Qué campo desea modificar?"<<endl;
        uiUtils.setColorText(TXT_CYAN);
        cout<<"1. Nombre"<<endl;
        cout<<"2. Cédula"<<endl;
        cout<<"3. Hora de entrada"<<endl;
        cout<<"4. Hora de salida"<<endl;
        cout<<"0. Cancelar"<<endl;
        cout<<"Opción: ";
        uiUtils.setColorText(TXT_WHITE);
        cin >> opc;
        cin.ignore();

        switch (opc) {
            case 1: {
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nuevo nombre(s): ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, str);
                name.setFirst(str);
                uiUtils.gotoxy(3, 15);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nuevo apellido(s): ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, str);
                name.setLast(str);
                doctor.setName(name);
                break;
                }
            case 2: {
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout<<"Nueva cédula: ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, str);
                doctor.setCertificate(str);
                break;
                }
            case 3: {
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout << "Nueva hora de entrada (HH:MM): ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, str);
                hourStr=str.substr(0, 2);
                time.setHour(stoi(hourStr));
                minuteStr=str.substr(3, 2);
                time.setMinute(stoi(minuteStr));
                doctor.setArrival(time);
                break;
                }
            case 4: {
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_CYAN);
                cout<<"Nueva hora de salida (HH:MM): ";
                uiUtils.setColorText(TXT_WHITE);
                getline(cin, str);
                hourStr=str.substr(0, 2);
                time.setHour(stoi(hourStr));
                minuteStr=str.substr(3, 2);
                time.setMinute(stoi(minuteStr));
                doctor.setDeparture(time);
                break;
                }
            case 0:
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_YELLOW);
                cout<<"Operación de modificación cancelada."<<endl;
                break;
            default:
                uiUtils.gotoxy(3, 14);
                uiUtils.setColorText(TXT_RED);
                cout << "Opción inválida." << endl;
                break;
            }

        if (opc>=1 and opc<=4) {
            // Actualiza el médico modificado en el archivo de datos
            fileRef->deleteData(idx);
            fileRef->addData(doctor);

            uiUtils.gotoxy(3, 16);
            uiUtils.setColorText(TXT_GREEN);
            cout<<"Médico modificado exitosamente."<<endl;
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

void DoctorInterface::showList(DoctorFile* fileRef) {
    UserInterfaceUtils uiUtils;
    list<Doctor> docList = fileRef->toList();

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText("*** Lista de Médicos ***", 1);
    cout << "*** Lista de Médicos ***" << endl;

    int idx = 0;
    for (const Doctor& doctor : docList) {
        idx++;
        cout<<"\tMédico #" <<idx<<":"<<endl;
        cout<<doctor.toString()<<endl;
        cout<<endl;
        }

    if (docList.empty()) {
        uiUtils.setColorText(TXT_YELLOW);
        cout << "La lista de médicos está vacía." << endl;
        }

    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::deleteAll(DoctorFile* fileRef) {
    UserInterfaceUtils uiUtils;

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
        fileRef->clearFile();
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

void DoctorInterface::importData(DoctorFile* fileRef) {
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

void DoctorInterface::exportData(DoctorFile* fileRef) {
    UserInterfaceUtils uiUtils;

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

    list<Doctor> docList=fileRef->toList();
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout << "No se pudo abrir el archivo de destino." << endl;
        uiUtils.setColorText(TXT_CYAN);
        uiUtils.enterToContinue();
        return;
        }

    for (const Doctor& doctor : docList) {
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
    doctorFilePtr=new DoctorFile();
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
                addDoctor(doctorFilePtr);
                break;

            case 2:
                deleteDoctor(doctorFilePtr);
                break;

            case 3:
                modifyDoctor(doctorFilePtr);
                break;

            case 4:
                showList(doctorFilePtr);
                break;

            case 5:
                deleteAll(doctorFilePtr);
                break;

            case 6:
                importData(doctorFilePtr);
                break;

            case 7:
                exportData(doctorFilePtr);
                break;

            case 8:
                repeat=false;
                break;
            }

        }
    while(repeat);
    }

DoctorInterface::~DoctorInterface() {
    delete doctorFilePtr;
    }
