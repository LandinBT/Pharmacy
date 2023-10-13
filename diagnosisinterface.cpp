#include "diagnosisinterface.hpp"
using namespace std;

void DiagnosisInterface::addDiagnosis() {
    UserInterfaceUtils uiUtils;
    Diagnosis diagnosis;
    string str, title("*** Nuevo Diagnóstico ***");
    char opc;

    do {
        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout<<title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Código: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        diagnosis.setCode(str);

        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Descripción: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        diagnosis.setDesc(str);

        diagnosisFilePtr->addData(diagnosis);

        uiUtils.gotoxy(3, 11);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Desea agregar otro diagnóstico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>opc;
        opc=toupper(opc);
        cin.ignore();
        }
    while(opc=='S');

    if(opc!='S' and opc!='N') {
        uiUtils.gotoxy(3, 13);
        uiUtils.setColorText(TXT_RED);
        cout<<"Opción inválida!";
        }

    uiUtils.gotoxy(3, 15);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DiagnosisInterface::deleteDiagnosis() {
    UserInterfaceUtils uiUtils;
    Diagnosis diagnosis;
    string str, title("*** Eliminar Diagnóstico ***");
    char opc;

        system("cls");
        uiUtils.setColorText(TXT_GREEN);
        uiUtils.centerText(title, 1);
        cout<<title;

        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Código: ";
        uiUtils.setColorText(TXT_WHITE);
        getline(cin, str);
        diagnosis.setCode(str);

        int idx(diagnosisFilePtr->findData(diagnosis));

        if(idx!=-1){
            uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Diagnóstico encontrado: ";

        list<Diagnosis> diagList=diagnosisFilePtr->toList();
        auto it=diagList.begin();
        advance(it, idx);
        Diagnosis foundDiag=*it;

        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_BLUE);
        cout<<foundDiag.toString();

        uiUtils.gotoxy(3, 9);
        uiUtils.setColorText(TXT_CYAN);
        cout<<"Está seguro de eliminar este diagnóstico? (s/n): ";
        uiUtils.setColorText(TXT_WHITE);
        cin>>opc;
        opc=toupper(opc);
        cin.ignore();

        if(opc=='S') {
            diagnosisFilePtr->deleteData(idx);
            uiUtils.gotoxy(3, 11);
            uiUtils.setColorText(TXT_GREEN);
            cout<<"Diagnóstico eliminado exitosamente.";
            }
        else if(opc=='N') {
            uiUtils.gotoxy(3, 11);
            uiUtils.setColorText(TXT_YELLOW);
            cout<<"Operación de eliminación cancelada.";
            }
        else {
            uiUtils.gotoxy(3, 11);
            uiUtils.setColorText(TXT_RED);
            cout<<"Opción inválida!";
            }
        }

    uiUtils.gotoxy(3, 13);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DiagnosisInterface::searchByCode() {
    UserInterfaceUtils uiUtils;
    string str, title="*** Buscar diagnóstico por código ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout << "Código: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, str);

    int idx(diagnosisFilePtr->findDataCode(str));
    list<Diagnosis> diagList=diagnosisFilePtr->toList();

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Diagnóstico encontrado:";

        auto it = diagList.begin();
        advance(it, idx);
        Diagnosis diagnosis=*it;

        uiUtils.gotoxy(3, 9);
        uiUtils.setColorText(TXT_CYAN);
        cout<<diagnosis.toString()<<endl;
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout<<"No se encontró ningún diagnóstico con el código "<<str;
        }

    uiUtils.gotoxy(3, 11);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DiagnosisInterface::searchByDesc() {
    UserInterfaceUtils uiUtils;
    string str, title="*** Buscar diagnóstico por descripción ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout<<"Descripción: ";
    uiUtils.setColorText(TXT_WHITE);
    getline(cin, str);

    int idx(diagnosisFilePtr->findDataDesc(str));
    list<Diagnosis> diagList=diagnosisFilePtr->toList();

    if (idx != -1) {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Diagnóstico encontrado:";

        auto it = diagList.begin();
        advance(it, idx);
        Diagnosis diagnosis=*it;

        uiUtils.gotoxy(3, 9);
        uiUtils.setColorText(TXT_CYAN);
        cout<<diagnosis.toString()<<endl;
        }
    else {
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_RED);
        cout<<"No se encontró ningún diagnóstico";
        }

    uiUtils.gotoxy(3, 11);
    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DiagnosisInterface::modifyDiagnosis() {

    }

void DiagnosisInterface::showList() {
    UserInterfaceUtils uiUtils;
    string title="*** Lista de diagnósticos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    try {
        list<Diagnosis> diagList = diagnosisFilePtr->toList();

        if (!diagList.empty()) {
            uiUtils.gotoxy(3, 5);
            uiUtils.setColorText(TXT_BLUE);
            cout<<"Código | Descripción"<<endl<<endl;

            uiUtils.setColorText(TXT_CYAN);
            for(const Diagnosis& diagnosis : diagList) {
                cout<<diagnosis.toString()<<endl;
                }
            }
        else {
            uiUtils.gotoxy(3, 5);
            uiUtils.setColorText(TXT_RED);
            cout<<"No hay diagnósticos registrados.";
            }
        }
    catch(const ios_base::failure& ex) {
        uiUtils.gotoxy(3, 5);
        uiUtils.setColorText(TXT_RED);
        cout<<"Algo salió mal: "<<ex.what()<<endl;
        }

    uiUtils.setColorText(TXT_CYAN);
    uiUtils.enterToContinue();
    }

void DiagnosisInterface::deleteAll() {
    UserInterfaceUtils uiUtils;
    string title="*** Eliminar todos los diagnósticos ***";
    char opc;

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    uiUtils.gotoxy(3, 5);
    uiUtils.setColorText(TXT_CYAN);
    cout<<"¿Está seguro de eliminar todos los diagnósticos? (s/n): ";
    uiUtils.setColorText(TXT_WHITE);
    cin>>opc;
    opc = toupper(opc);
    cin.ignore();

    if(opc=='S') {
        diagnosisFilePtr->clearFile();
        uiUtils.gotoxy(3, 7);
        uiUtils.setColorText(TXT_GREEN);
        cout<<"Todos los diagnósticos han sido eliminados.";
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

void DiagnosisInterface::importData() {
    UserInterfaceUtils uiUtils;
    string str, title="*** Recuperar datos de diagnósticos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    cout<<"Nombre del archivo: ";
    getline(cin, str);

    try {
        diagnosisFilePtr->importFromBackup(str);
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

void DiagnosisInterface::exportData() {
    UserInterfaceUtils uiUtils;
    string str, title="*** Guardar datos de diagnósticos ***";

    system("cls");
    uiUtils.setColorText(TXT_GREEN);
    uiUtils.centerText(title, 1);
    cout<<title;

    cout<<"Nombre del archivo: ";
    getline(cin, str);

    try {
        diagnosisFilePtr->exportToBackup(str);
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

DiagnosisInterface::DiagnosisInterface() {
    UserInterfaceUtils uiUtils;
    diagnosisFilePtr=new DiagnosisFile();
    bool repeat = true;
    int opc;

    string title ="*** D I A G N Ó S T I C O S ***";
    vector<string> options = {"Nuevo diagnóstico", "Eliminar diagnóstico",
                              "Buscar por código", "Buscar por descripción",
                              "Modificar diagnóstico", "Mostrar lista",
                              "Eliminar todo", "Recuperar", "Guardar",
                              "Regresar"
                             };
    int numOpt=10;

    do {
        system("title FARMACIA GUANATOS: DIAGNÓSTICO");
        opc = uiUtils.mainMenu(title, options, numOpt, TXT_VIOLET);

        switch(opc) {
            case 1:
                addDiagnosis();
                break;

            case 2:
                deleteDiagnosis();
                break;

            case 3:
                searchByCode();
                break;

            case 4:
                searchByDesc();
                break;

            case 5:
                modifyDiagnosis();
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

DiagnosisInterface::~DiagnosisInterface() {
    delete diagnosisFilePtr;
    }
