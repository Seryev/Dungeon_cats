#ifndef PERSONAJES_h
#define PERSONAJES_h

#include "Armas.h"
#include "Artefactos.h"
#include "Movimientos.h"
#include <string>
#include <vector>

using namespace std;

class Armas;
class Artefactos;

class Personajes {
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
        int PRST[3];               //Pref Stats
        bool LIVE;              //Si esta vivo o no
        Armas* ARM;             //Arma equipada
        vector<Artefactos*> ART;//Artefactos
        Movimientos MOV[4];     //Movimientos

        Personajes(string NOM,string CLAS,int NIV,int EXP,int VID,int MAN,int FUE,int DEF,int MAG,int RES,int VEL,int COR,bool LIVE,int PRST[3])
            : NOM(NOM),CLAS(CLAS),NIV(NIV),EXP(EXP),VID(VID),MAN(MAN),FUE(FUE),DEF(DEF),MAG(MAG),RES(RES),VEL(VEL),COR(COR),LIVE(LIVE) {
                for(int i=0; i < 3; i++){
                    this->PRST[i] = PRST[i];
                }
            }
};

#endif