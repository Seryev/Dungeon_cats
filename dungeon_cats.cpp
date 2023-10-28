/*
Author: Seryev
Date: 10/25/2023
Version 0.5
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

//Informacion de recursos del jugador (Personajes, Objetos, Dinero, etc).

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

void Menu_CrearPersonaje(){
    int per = 1;
    string nombre;
    string clase;
    while(per<3){
        Mostrar_Clases();
        cout << "\nConfigurando personaje " << per << ":\n\nNombre: ";
        cin >> nombre;
        cout << "\nClase: ";
        cin >> clase; 
        per++;
        system("clear");
    }

}
              



int main(){

    Menu_CrearPersonaje();


    return 0;
}


