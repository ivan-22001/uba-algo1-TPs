//
// Este archivo contiene las definiciones de las funciones auxiliares
// que ustedes necesiten implementar. Tienen que coincidir con las 
// declaraciones de auxiliares.h
//

#include <iostream>

#include "definiciones.h"
#include "ejercicios.h"
#include "auxiliares.h"

using namespace std;

bool estaEnTablero (pos p, tablero &t){
    return (p.first >= 0 && p.first < t.size() && p.second >= 0 && p.second < t[0].size());
}

bool hayMina (pos p, tablero& t){
    return (t[p.first][p.second]);
}

void removerPosicion (banderitas &b, int index){
    banderitas nuevoB{};
    for (int i = 0; i < b.size(); ++i) {
        if (i != index)
            nuevoB.push_back(b[index]);
    }
    b = nuevoB;
}

int cantPosicionesSinMinas(tablero& t) {
    int cantSinMinas = 0;
    int largoTablero = t.size();
    for (int i = 0; i < largoTablero; ++i) {
        for (int j = 0; j < largoTablero; ++j) {
            pos p = make_pair(i, j);
            if (!hayMina(p, t))
                cantSinMinas++;
        }
    }
    return cantSinMinas;
}

bool esPosicionSinJugar(pos p, jugadas& j) {
    bool esJugada = false;
    for (int i = 0; i < j.size(); ++i) {
        if(p == j[i].first)
            esJugada = true;
    }
    return esJugada;
}

void agregarJugadasNuevas(pos p, int minas, jugadas& j) {
    if (esPosicionSinJugar(p,j)) {
        jugada elem = make_pair(p, minas);
        j.push_back(elem);
    }
}

bool tieneBanderita(pos p, banderitas &b) {
    bool existe = false;
    for (int i = 0; i < b.size(); ++i) {
        if(b[i] == p)
            existe = true;
    }
    return existe;
}

bool existen1y1Horizontales(jugadas& j, pos posicionCon2,tablero &t) {
    bool existen = false;
    int cuentoUnos = 0;
    for(int i = -1; i <= 1; i++){
        pos buscoUno = make_pair(posicionCon2.first,posicionCon2.second+i);
        if(!esPosicionSinJugar(buscoUno, j) && minasAdyacentes(t, buscoUno) == 1)
            cuentoUnos++;
    }
    if(cuentoUnos == 2)
        existen = true;
    return existen;
}
bool existen1y1Verticales(jugadas& j, pos posicionCon2, tablero &t){
    bool existen = false;
    int cuentoUnos = 0;
    for(int i = -1; i <= 1; i++){
        pos buscoUno = make_pair(posicionCon2.first+i,posicionCon2.second);
        if(!esPosicionSinJugar(buscoUno, j) && minasAdyacentes(t, buscoUno) == 1)
            cuentoUnos++;
    }
    if(cuentoUnos == 2)
        existen = true;
    return existen;
}

pos sugieroPHorizontal(pos pos2, tablero &t, jugadas &j, banderitas &b, bool &esSugerible){
    pos superior = make_pair(pos2.first - 1, pos2.second);
    pos inferior = make_pair(pos2.first + 1, pos2.second);
    pos posSugerida{};

    if (estaEnTablero(superior, t) && esPosicionSinJugar(superior, j) && !tieneBanderita(superior, b)) {
        posSugerida = superior;
        esSugerible = true;
    }
    else if (estaEnTablero(inferior, t) && esPosicionSinJugar(inferior, j) && !tieneBanderita(inferior, b)) {
        posSugerida = inferior;
        esSugerible = true;
    }

    return posSugerida;
}

pos sugieroPVertical(pos pos2, tablero &t, jugadas &j, banderitas &b, bool &esSugerible){
    pos derecha = make_pair(pos2.first, pos2.second + 1);
    pos izquierda = make_pair(pos2.first, pos2.second - 1);
    pos posSugerida{};

    if (estaEnTablero(derecha, t) && esPosicionSinJugar(derecha, j) && !tieneBanderita(derecha, b)) {
        posSugerida = derecha;
        esSugerible = true;
    }

    else if (estaEnTablero(izquierda, t) && esPosicionSinJugar(izquierda, j) && !tieneBanderita(izquierda, b)) {
        posSugerida = izquierda;
        esSugerible = true;
    }


    return posSugerida;
}