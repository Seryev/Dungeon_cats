#ifndef ENEMIGOS_h
#define ENEMIGOS_h
//Librerias 
#include "Armas.h"
#include "Artefactos.h"
#include "Movimientos.h"
#include <string>

using namespace std;

class Enemigos {
    public:
        string NOM;             //Nombre            
        string CLAS;            //Clase  
        int NIV;                //Nivel
        int EXP;                //Experiencia
        int VID;                //Vida
        int MAN;                //Mana
        int FUE;                //Fuerza
        int DEF;                //Defensa
        int MAG;                //Magia
        int RES;                //Resitencia magica
        int VEL;                //Velocidad
        int COR;                //Cordura
        bool LIVE;              //Si esta vivo o no
        Armas* ARM;             //Arma equipada
        vector<Artefactos*> ART;//Artefactos
        Movimientos MOV[4];     //Movimientos

        Enemigos(string NOM,string CLAS,int NIV,int EXP,int VID,int MAN,int FUE,int DEF,int MAG,int RES,int VEL,int COR,bool LIVE)
            : NOM(NOM),CLAS(CLAS),NIV(NIV),EXP(EXP),VID(VID),MAN(MAN),FUE(FUE),DEF(DEF),MAG(MAG),RES(RES),VEL(VEL),COR(COR),LIVE(LIVE) {}
};

#endif