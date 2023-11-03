/*
Author: Seryev
Date: 10/25/2023
Version 0.6
*/

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
Librerias
/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
#include <iostream>                     //Entrada y salida de datos
#include <string>                       //Trabajar con datos tipo string
#include <fstream>                      //Lectura de archivos
#include <sstream>                      //Buffer de strings
#include <vector>                       //Estructura de datos
#include <cmath>                        //Utilidades matematicas
#include <ctime>                        //Tiempo
#include <cstdlib>                      //Utilidades
#include "headers/Armas.h"              //Objetos armas
#include "headers/Artefactos.h"         //Objetos artefactos
#include "headers/Class_Personajes.h"   //Clases de los personajes
#include "headers/Enemigos.h"           //Unidades enemigas
#include "headers/Movimientos.h"        //Movimientos
#include "headers/Personajes.h"         //Unidades aliadas

using namespace std;

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
Variables Globales
/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
//Utilidades
ifstream file;  //Lectura de archivos
int money;      //Dinero 
//Informacion de recursos del jugador (Personajes, Objetos, Dinero, etc).
vector<Personajes> personajes;
//Informacion de recursos para calculo de partida (Informacion del nivel donde se encuentra, etc)
vector<Class_Personajes> clases;
//Llaves de control de datos
bool Leer_Clases = false;
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
Funciones
/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/*/
/*=====================================================
Funcion para imprimir espacios en blanco en diferencia de size de nombres
=====================================================*/
void Ajuste_Nombre(int a, int b){
    int c = a - b;
    while(c > 0){
        cout << " ";
        c--;
    }
}
/*=====================================================
Funcion para imprimir espacios en blanco en la diferencia de numero de digitos de las estadisticas
=====================================================*/
void Ajuste_D(int a){
    int b = 3 - a;
    while(b>0){
        cout << " ";
        b--;
    }
}
/*=====================================================
Funcion para traducir la entrada de numeros como identificadores de las estadisticas preferidas de clase
=====================================================*/
string Resolver_PrefStat(int aux[]){
    int i=0;
    string prefs;
    while(i<3){
        switch (aux[i])
        {
        case 1:
            (i<2) ? prefs+="VID," :prefs+="VID";
            break;
        case 2:
            (i<2) ? prefs+="MAN," :prefs+="MAN";
            break;
        case 3:
            (i<2) ? prefs+="FUE," :prefs+="FUE";
            break;
        case 4:
            (i<2) ? prefs+="DEF," :prefs+="DEF";
            break;
        case 5:
            (i<2) ? prefs+="MAG," :prefs+="MAG";
            break;
        case 6:
            (i<2) ? prefs+="RES," :prefs+="RES";
            break;
        case 7:
            (i<2) ? prefs+="VEL," :prefs+="VEL";
            break;
        case 8:
            (i<2) ? prefs+="COR," :prefs+="COR";
            break;
        default:
           throw runtime_error("\nError: Fallo en la resolucion de estadistica preferidas de clase.");
            break;
        }
        i++;
    }
    return prefs;
}
/*=====================================================
Funcion para calcular el numero de digitos de una estadistica
=====================================================*/
int Numero_Dig(int num){
    return floor(log10(abs(num)))+1;
}
/*=====================================================
Funcion para buscar el nombre mas largo entre las clases
=====================================================*/
int Find_ms(vector<Class_Personajes> clase){
    int max_size = 0;

    for(int i=0; i < clase.size(); i++){
        if(max_size < clase[i].NOM.size()) max_size = clase[i].NOM.size();
    }
    return max_size;
}
/*=====================================================
Funcion para imprimir el nombre de las columnas de las clases
=====================================================*/
void Columnas_Clase(int max_size){
    cout << "+";
    for(int i=(max_size+64);i > 0 ; i--){
        cout << "=";
    }
    cout << "+"<< endl;
    cout << "| NOM";
    Ajuste_Nombre(max_size,3);
    cout << " | VID | MAN | FUE | DEF | MAG | RES | VEL | COR | PRST        |" <<  endl;
    cout << "+";
    for(int i=(max_size+64);i > 0 ; i--){
        cout << "=";
    }
    cout << "+"<< endl;
} 

void Mostrar_Arma(Armas* ARM, int max_size){
    cout << "| Arma   | ";
    Ajuste_Nombre(max_size,0);cout << "|" << endl;
    cout << "| Nombre | " << ARM->NOM;
    Ajuste_Nombre(max_size,ARM->NOM.size());cout << "|" << endl; 
    cout << "| Rango  | " << ARM->CLAS;
    Ajuste_Nombre(max_size,1);cout << "|" << endl;
    cout << "| Nivel  | " << ARM->NIV;
    Ajuste_Nombre(max_size,Numero_Dig(ARM->NIV));cout << "|" << endl;
}
/*=====================================================
Funcion para imprimir la informacion de una clase
=====================================================*/
void Mostrar_Personaje(Personajes& pers){
    int max_size = (pers.NOM.size() > 11)? max_size=pers.NOM.size():max_size=11;
    if(max_size < pers.CLAS.size()) max_size = pers.CLAS.size();
    string iguales;

    for(int i=max_size+10;i>0;i--){
        iguales+= "=";
    }
    cout << "\n+" << iguales <<"+" << endl; // Separador ~~~~Nombre, clase y nivel
    cout << "| Nombre | " << pers.NOM;
    Ajuste_Nombre(max_size,pers.NOM.size());
    cout << "|\n| Clase  | " << pers.CLAS;
    Ajuste_Nombre(max_size,pers.CLAS.size());
    cout << "|\n| Nivel  | " << pers.NIV;
    Ajuste_Nombre(max_size,Numero_Dig(pers.NIV));
    cout << "|" << endl;
    cout << "+" << iguales << "+" << endl;//Separador ~~~~~~STATS
    cout << "| VID    | " << pers.VID;
    Ajuste_Nombre(max_size,Numero_Dig(pers.VID));cout << "|" << endl;
    cout << "| MAN    | " << pers.MAN;
    Ajuste_Nombre(max_size,Numero_Dig(pers.MAN));cout << "|" << endl;
    cout << "| FUE    | " << pers.FUE;
    Ajuste_Nombre(max_size,Numero_Dig(pers.FUE));cout << "|" << endl;
    cout << "| DEF    | " << pers.DEF;
    Ajuste_Nombre(max_size,Numero_Dig(pers.DEF));cout << "|" << endl;
    cout << "| MAG    | " << pers.MAG;
    Ajuste_Nombre(max_size,Numero_Dig(pers.MAG));cout << "|" << endl;
    cout << "| RES    | " << pers.RES;
    Ajuste_Nombre(max_size,Numero_Dig(pers.RES));cout << "|" << endl;
    cout << "| VEL    | " << pers.VEL;
    Ajuste_Nombre(max_size,Numero_Dig(pers.VEL));cout << "|" << endl;
    cout << "| COR    | " << pers.COR;
    Ajuste_Nombre(max_size,Numero_Dig(pers.COR));cout << "|" << endl;
    cout << "+" << iguales << "+" << endl;//Separador ~~~~~~~~~~~~ARMA
    if(pers.isARMempy()){
        cout << "| Arma   | NONE";
        Ajuste_Nombre(max_size,4);cout << "|" << endl;
    }else{
        Mostrar_Arma(pers.ARM, max_size);
    }
    cout << "+" << iguales << "+" << endl;//Separador ~~~~~~~~~~~~Artefactos
}
/*=====================================================
Funcion para calcular un valor aleatorio.
=====================================================*/
int valorAleatorio(int min, int max) {
    
    return min + rand() % (max - min + 1);
}
/*=====================================================
Funcion aumentar estadisticas al subir de nivel o crear personaje.
=====================================================*/
void Aum_Stats(Personajes& pers,int veces,int a,int b, int c){
    //Variables auxiliares
    int stats[11] = {1,2,3,4,5,6,7,8,a,b,c};
    int pt;
    int VID=0,MAN=0,FUE=0,DEF=0,MAG=0,RES=0,VEL=0,COR=0;
    
   veces = valorAleatorio(veces-5,veces+5);

    //Repartir puntos
    for(int i=0; i<veces;i++){
        pt = rand() % 11;
        switch(stats[pt]){
            case 1:
                pers.VID++;VID++;break;
            case 2:
                pers.MAN++;MAN++;break;
            case 3:
                pers.FUE++;FUE++;break;
            case 4:
                pers.DEF++;DEF++;break;
            case 5:
                pers.MAG++;MAG++;break;
            case 6:
                pers.RES++;RES++;break;
            case 7:
                pers.VEL++;VEL++;break;
            case 8:
                pers.COR++;COR++;break;
        }
    }
    //Mostrar estadisticas que aumentaron:
    cout << "\nPuntos adicionales:";
    cout << "\nVID: +" << VID << "\nMAN: +" << MAN
         << "\nFUE: +" << FUE << "\nDEF: +" << DEF
         << "\nMAG: +" << MAG << "\nRES: +" << RES
         << "\nVEL: +" << VEL << "\nCOR: +" << COR;
    cout << "\nTotal: " << (VID+MAN+FUE+DEF+MAG+RES+VEL+COR) << endl; 
}
/*=====================================================
Funcion para imprimir consecutivamente las clases ajustando los espacios en blanco para darle formato de tabla
=====================================================*/
void Mostrar_Clases(){
    int per = 1;
    string line;
    
    if(!Leer_Clases){
        file.open("game_resources/clases.csv");
        if (!file.is_open()) {
            cerr << "Error: No se encontró el archivo clases.csv" << endl;
        } else {
            while (getline(file, line)) {
                istringstream ss(line);
                string field;
                vector<string> fs;

                while (getline(ss, field, ',')) {
                    fs.push_back(field);
                }

                int a_aux[3];
                for(int i=0; i < 3; i++){
                    a_aux[i] = stoi(fs.back());
                    fs.pop_back();
                }

                Class_Personajes aux(fs[0],stoi(fs[1]),stoi(fs[2]),stoi(fs[3]),stoi(fs[4]),stoi(fs[5]),stoi(fs[6]),stoi(fs[7]),stoi(fs[8]),a_aux);
                clases.push_back(aux);
            }
            file.close();
        }
    }

    int max_size = Find_ms(clases);
    Columnas_Clase(max_size);

    int i = 0;
    while(i < clases.size()){
        vector<int> dif_dig;
        dif_dig.push_back(Numero_Dig(clases[i].COR));
        dif_dig.push_back(Numero_Dig(clases[i].VEL));
        dif_dig.push_back(Numero_Dig(clases[i].RES));
        dif_dig.push_back(Numero_Dig(clases[i].MAG));
        dif_dig.push_back(Numero_Dig(clases[i].DEF));
        dif_dig.push_back(Numero_Dig(clases[i].FUE));
        dif_dig.push_back(Numero_Dig(clases[i].MAN));
        dif_dig.push_back(Numero_Dig(clases[i].VID));


        cout << "| " << clases[i].NOM;
        Ajuste_Nombre(max_size,clases[i].NOM.size());
        cout << " | " << clases[i].VID;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << clases[i].MAN;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << clases[i].FUE;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << clases[i].DEF;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << clases[i].MAG;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << clases[i].RES;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << clases[i].VEL;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << clases[i].COR;
        Ajuste_D(dif_dig.back());dif_dig.pop_back();
        cout << " | " << Resolver_PrefStat(clases[i].PRST) << " |" << endl;
        i++;
    }
    cout << "+";
    for(int i=(max_size+64);i > 0 ; i--){
        cout << "=";
    }
    cout << "+"<< endl;
    Leer_Clases = true;
}
/*=====================================================
Funcion para crear personajes al iniciar una partida
=====================================================*/
void CrearPersonaje(int NIV){
    int per = 1;
    string nombre;
    string clase;
    string buff;
    int cla;
    bool class_exist = false;
    while(per<3){
        Mostrar_Clases();
        cout << "\nConfigurando personaje " << per << ":\n\nNombre: ";
        cin >> nombre;
        getline(cin,buff);
        while(!class_exist){
            cout << "\nClase: ";
            cin >> clase;
            getline(cin,buff);
            for(int i=0; i<clases.size(); i++){
                if(clase == clases [i].NOM){
                    class_exist = true;
                    cla = i;
                    break;
                }
            }
            if(!class_exist) cout << "\nNo existe esa clase, prueba otra vez."; 
        }
        class_exist = false;
        
        Personajes pers(nombre,clase,NIV,0,clases[cla].VID,clases[cla].MAN,clases[cla].FUE,clases[cla].DEF,clases[cla].MAG,clases[cla].RES,clases[cla].VEL,clases[cla].COR,true,clases[cla].PRST);
        Aum_Stats(pers,20,pers.PRST[0],pers.PRST[1],pers.PRST[2]);
        Mostrar_Personaje(pers);

        personajes.push_back(pers);
        per++;
        cout << "\n\n\nPulsa enter para continuar....";
        cin.get();
        system("clear");
    }

}
/*=====================================================
Funcion para leer documento de texto y mostrarlo como salida (como cat)
=====================================================*/
void Mostrar_Doc(string ruta){
    file.open(ruta);
    string line;
    if(!file.is_open()){
        cerr << "Error al abrir documento: " << ruta;
    }else{
        while(getline(file,line)){
            cout << line << endl;
        }
    }
}             

string Menu_Principal(){
    cout <<   "+______________________________________________________+"
         << "\n| personajes | inventario | tienda | comenzar | manual | $ " << money
         << "\n+======================================================+";

    cout << "\n\n\nMaster ~ $ ";
    string com;
    cin >> com;
    return com;
} 


int main(){
    srand(time(nullptr)); //Inicializar semilla de numeros aleatorios
    CrearPersonaje(1);

    return 0;
}


