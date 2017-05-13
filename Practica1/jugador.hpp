#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
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
			deads = 0;	
			located = false;
			tengoZap = tengoKey = keyMano = zapMano = tengoBik = bikMano = false;
			hue = 0;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){

		}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
		void updateMap(Sensores sensores);
		Action choose(Sensores sensores);
		void changemap(int i, int j);
		char test(int i, int j);
		int testScore(int i, int j);
		bool algoenMano();
		void deadReset();
		void rellenoTramposo();
		void calibrateCompass(Action accion);
    int interact(Action accion, int valor);


    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    
		char mapa[MAPSIZE*2-1][MAPSIZE*2-1]; 
		int gravedad[MAPSIZE*2-1][MAPSIZE*2-1];
		int gravedadResultado[MAPSIZE][MAPSIZE]; 
		int posfil, poscol;
		char facing;				// North, West, South or East
		bool located, bordeando, targeted, mustforward;
		bool tengoZap, tengoKey, tengoBik, keyMano, zapMano, bikMano;
		int siz, hue, deads;
	
};


#endif
