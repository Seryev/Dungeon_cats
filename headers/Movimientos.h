#ifndef MOVIMIENTOS_h
#define MOVIMIENTOS_h

#include <vector>
#include <string>

using namespace std;

class Movimientos{
    public:
        vector<int> Potencia;   //Potencias de cada escalado
        vector<string> Escalado;//Estadisticas con las que escala el ataque
        bool DMG;               //Determina si hace damage o cura
};

#endif