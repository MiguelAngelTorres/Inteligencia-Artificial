#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

const int MAPSIZE = 100;

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
			siz = MAPSIZE*2 - 1;
			for(int i=0; i < siz; i++){
				for(int j=0; j < siz; j++){
					mapa[i][j] = '?';
					gravedad[i][j] = 0; 
				}
			}
			for(int i=0; i < size; i++){
				for(int j=0; j < size; j++){
					if(i<2 || j<2){
						mapaResultado[i][j] = 'P';
					}
				}
			}
			posfil = MAPSIZE-1; 
			poscol = MAPSIZE-1;
			facing = 'N'; 
			lastkingx = lastkingy = -100;
			zapalgor = deads = norepetir = 0;	
			located = false;
			tengoZap = tengoKey = keyMano = zapMano = tengoReg = regMano = false;
			hue = 0;
			following_plan = buscoZap = buscoReg = false;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){

		}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
		void limpiarGravedadResultado();
		bool Astar(const int posx, const int posy);
		bool kingNear();
		bool pathFinding(const int posx, const int posy, char dir, int profundidad);
		void updateMap(Sensores sensores);
		Action choose(Sensores sensores);
		void changemap(int i, int j);
		char test(int i, int j);
		int testScore(int i, int j);
		bool algoenMano();
		void deadReset(Sensores sensores);
		void rellenoTramposo();
		void calibrateCompass(Action accion);
    int interact(Action accion, int valor);


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    
		char mapa[MAPSIZE*2-1][MAPSIZE*2-1]; 
		int gravedad[MAPSIZE*2-1][MAPSIZE*2-1];
		int gravedadResultado[MAPSIZE][MAPSIZE]; 
		int posfil, poscol;
		int lastkingx, lastkingy;
		char facing;				// North, West, South or East
		bool located, targeted;
		bool tengoZap, tengoKey, tengoReg, keyMano, zapMano, regMano;
		bool buscoReg, buscoZap, necesitoZapn, necesitoZape, necesitoZaps, necesitoZapw;
		int siz, hue, deads, zapalgor, norepetir;
		Action lastaccion;

		bool following_plan;
		list<pair<int,int> > plan;
	
};


#endif
