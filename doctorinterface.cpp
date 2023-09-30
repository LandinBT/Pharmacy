#include "doctorinterface.hpp"
using namespace std;

void DoctorInterface::addDoctor() {
    UserInterfaceUtils uiUtils;
    Doctor doctor;
    Name name;
    Time arrival;
    Time departure;
    string title ="*** Nuevo m�dico ***";
    string str, hourStr, minuteStr;
    char opc; //option

    do {
        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout<<title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"C�digo de empleado: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        doctor.setEmpCode(str);

        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Nombre(s): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        name.setFirst(str);
        uiUtils.gotoxy(3, 8);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Apellido(s): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        name.setLast(str);
        doctor.setName(name);

        uiUtils.gotoxy(3, 10);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"C�dula: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        doctor.setCertificate(str);

        uiUtils.gotoxy(3, 12);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Hora de entrada(HH:MM): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        hourStr=str.substr(0,2);
        minuteStr=str.substr(3,2);
        arrival.setHour(stoi(hourStr));
        arrival.setMinute(stoi(minuteStr));
        doctor.setArrival(arrival);

        uiUtils.gotoxy(3, 14);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Hora de salida(HH:MM): ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        hourStr=str.substr(0,2);
        minuteStr=str.substr(3,2);
        departure.setHour(stoi(hourStr));
        departure.setMinute(stoi(minuteStr));
        doctor.setDeparture(departure);

        //add

        uiUtils.gotoxy(3, 16);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Desea agregar otro m�dico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>opc;
        opc=toupper(opc);
        cin.ignore();
        }
    while(opc=='S');

    if(opc!='S' and opc!='N') {
        uiUtils.setColorText(TXT_RED);
        uiUtils.gotoxy(3, 18);
        cout<<"Opci�n inv�lida!"<<endl;
        }

    uiUtils.gotoxy(3, 20);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DoctorInterface::deleteDoctor() {

    }

void DoctorInterface::modifyDoctor() {

    }

void DoctorInterface::showList() {

    }

void DoctorInterface::deleteAll() {

    }

void DoctorInterface::importData() {

    }

void DoctorInterface::exportData() {

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
