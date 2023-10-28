#ifndef ARTEFACTOS_h
#define ARTEFACTOS_h

#include "Personajes.h"
#include <string>

using namespace std;

class Personajes;

class Artefactos{
    public:
        string NOM;             //Nombre
        char CLAS;              //Clasificacion
        int NIV;                //Nivel
        int VID;                //Vida
        int MAN;                //Mana
        int FUE;                //Fuerza
        int DEF;                //Defensa
        int MAG;                //Magia
        int RES;                //Resitencia magica
        int VEL;                //Velocidad
        int COR;                //Cordura
        int PRE;                //Precio
        Personajes* PER;        //Personaje donde esta equipada

        Artefactos(string NOM,char CLAS,int NIV,int VID,int MAN,int FUE,int DEF,int MAG,int RES,int VEL,int COR,int PRE)
            : NOM(NOM),CLAS(CLAS),NIV(NIV),VID(VID),MAN(MAN),FUE(FUE),DEF(DEF),MAG(MAG),RES(RES),VEL(VEL),COR(COR),PRE(PRE) {}
};


#endif