#ifndef CLASS_PERSONAJES_h
#define CLASS_PERSONAJES_h

#include <string>

using namespace std;

class Class_Personajes{  
    public:
        string NOM;             //Nombre    
        int VID;                //Vida
        int MAN;                //Mana
        int FUE;                //Fuerza
        int DEF;                //Defensa
        int MAG;                //Magia
        int RES;                //Resitencia magica
        int VEL;                //Velocidad
        int COR;                //Cordura
        int PRST[3];            //Stats preferidos

        Class_Personajes(string NOM,int VID,int MAN,int FUE,int DEF,int MAG,int RES,int VEL,int COR,int PRST[3])
            : NOM(NOM),VID(VID),MAN(MAN),FUE(FUE),DEF(DEF),MAG(MAG),RES(RES),VEL(VEL),COR(COR) {
                for(int i=0; i < 3; i++){
                    this->PRST[i] = PRST[i];
                }
            }
};

#endif