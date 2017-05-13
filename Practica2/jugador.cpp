#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class nodo{
	public: 
		int x,y;
		vector<pair<int, int> > bestcamino;
		int heuristica;

};



bool ComportamientoJugador::kingNear(){

	int aux = posfil - lastkingx + poscol - lastkingy;	
	if(aux < 15){
		if(aux > -15){
			return true;
		}
	}
return false;
}






void ComportamientoJugador::limpiarGravedadResultado(){

	for(int i=0; i<MAPSIZE; i++){
		for(int j=0; j<MAPSIZE; j++){
			if(gravedadResultado[i][j]<0){
				gravedadResultado[i][j] = 15;
			}
		}
	}
}





bool compareme (const nodo& first, const nodo& second)
{
  return ( first.heuristica < second.heuristica );
}

bool ComportamientoJugador::Astar(const int posx, const int posy){
	nodo inicial;
	inicial.x = posfil;
	inicial.y = poscol;
	inicial.heuristica = abs(posx - posfil) + abs(posy - poscol);

	list<nodo> Aexplorar;
	list<pair<int,int> > Yaexplore;
	Aexplorar.push_back(inicial);
	bool encontrado = false;
	bool explorado;
	char aux;
	int tope = 0;
	list<pair<int,int> >::iterator it;
	nodo nuevo;
	vector<pair<int, int> > camino;	
	do{
		if(tope == 500){
			return false;
		}
		if(Aexplorar.empty()){
			return false;
		}
		tope++;
		Aexplorar.sort(compareme);
		nodo mejor = Aexplorar.front();
		Yaexplore.push_front(pair<int,int>(mejor.x,mejor.y));
		if(mejor.x == posx && mejor.y == posy){
			encontrado = true;
			camino = mejor.bestcamino;
		}else{
			explorado = false;
	 		for (it=Yaexplore.begin(); it != Yaexplore.end(); ++it){
				if((*it).first == mejor.x-1 && (*it).second == mejor.y){
					explorado = true;
				}
			}
			if(!explorado){
				aux = test(mejor.x-1,mejor.y);
				if( aux == 'S' || aux == 'T' || aux == 'K' || (aux == 'B' && tengoZap)){
					nuevo.x = mejor.x-1;
					nuevo.y = mejor.y;
					nuevo.bestcamino = mejor.bestcamino;
					nuevo.bestcamino.push_back(pair<int,int>(mejor.x-1,mejor.y));
					Aexplorar.push_back(nuevo);
				}
			}


			explorado = false;
	 		for (it=Yaexplore.begin(); it != Yaexplore.end(); ++it){
					if((*it).first == mejor.x+1 && (*it).second == mejor.y){
					explorado = true;
				}
			}
			if(!explorado){
				aux = test(mejor.x+1,mejor.y);
				if( aux == 'S' || aux == 'T' || aux == 'K' || (aux == 'B' && tengoZap)){
					nuevo.x = mejor.x+1;
					nuevo.y = mejor.y;
					nuevo.bestcamino = mejor.bestcamino;
					nuevo.bestcamino.push_back(pair<int,int>(mejor.x+1,mejor.y));
					Aexplorar.push_back(nuevo);
				}
			}


			explorado = false;
	 		for (it=Yaexplore.begin(); it != Yaexplore.end(); ++it){
					if((*it).first == mejor.x && (*it).second == mejor.y-1){
					explorado = true;
				}
			}
			if(!explorado){
				aux = test(mejor.x,mejor.y-1);
				if( aux == 'S' || aux == 'T' || aux == 'K' || (aux == 'B' && tengoZap)){
					nuevo.x = mejor.x;
					nuevo.y = mejor.y-1;
					nuevo.bestcamino = mejor.bestcamino;
					nuevo.bestcamino.push_back(pair<int,int>(mejor.x,mejor.y-1));
					Aexplorar.push_back(nuevo);
				}
			}



			explorado = false;
	 		for (it=Yaexplore.begin(); it != Yaexplore.end(); ++it){
					if((*it).first == mejor.x && (*it).second == mejor.y+1){
					explorado = true;
				}
			}
			if(!explorado){
				aux = test(mejor.x,mejor.y+1);
				if( aux == 'S' || aux == 'T' || aux == 'K' || (aux == 'B' && tengoZap)){
					nuevo.x = mejor.x;
					nuevo.y = mejor.y+1;
					nuevo.bestcamino = mejor.bestcamino;
					nuevo.bestcamino.push_back(pair<int,int>(mejor.x,mejor.y+1));
					Aexplorar.push_back(nuevo);
				}
			}


			Aexplorar.pop_front();
		}

	  	for (vector<pair<int,int> >::iterator it = camino.begin() ; it != camino.end(); ++it){
			pair<int,int> a = *it;
			gravedadResultado[a.first][a.second] -=61;
	  	}
	
		
	}while(!encontrado);

return true;
}


bool ComportamientoJugador::pathFinding(const int posx, const int posy, char dir, int profundidad){
	if(posx == lastkingx && posy == lastkingy){
		return true;
	}
	if(profundidad == 0){
		return false;
	}


//	cout << "Smiguel huele un camino" << endl;
//////////////////  LOS BLOQUES SON IGUALES, SOLO CAMBIA LA DIRECCIÓN A LA QUE SE MIRA  //////////
	char aux;
	
	if(dir=='N'){
		aux = test(posx-1,posy); 
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx-1,posy,dir,profundidad-1)){
				gravedadResultado[posx-1][posy]-=61;
				return true;
			}
		}
		aux = test(posx,posy-1);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx,posy-1,'W',profundidad-1)){
				gravedadResultado[posx][posy-1]-=61;

				return true;
			}
		}
		aux = test(posx,posy+1);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx,posy+1,'E',profundidad-1)){
				gravedadResultado[posx][posy+1]-=61;

				return true;
			}
		}

		return false;
	}else if(dir=='W'){


		aux = test(posx,posy-1);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx,posy-1,dir,profundidad-1)){
				gravedadResultado[posx][posy-1]-=61;
				return true;
			}
		}
		aux = test(posx+1,posy);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx+1,posy,'S',profundidad-1)){
				gravedadResultado[posx+1][posy]-=61;

				return true;
			}
		}
		aux = test(posx-1,posy);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx-1,posy,'N',profundidad-1)){
				gravedadResultado[posx-1][posy]-=61;

				return true;
			}
		}
		return false;
		
	}else if(dir=='S'){
		aux = test(posx+1,posy);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx+1,posy,dir,profundidad-1)){
				gravedadResultado[posx+1][posy]-=61;
				return true;
			}
		}
		aux = test(posx,posy+1);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx,posy+1,'E',profundidad-1)){
				gravedadResultado[posx][posy+1]-=61;
				return true;
			}
		}
		aux = test(posx,posy-1);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx,posy-1,'W',profundidad-1)){
				gravedadResultado[posx][posy-1]-=61;

				return true;
			}
		}

	return false;
	}else{


		aux = test(posx,posy+1);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx,posy+1,dir,profundidad-1)){
				gravedadResultado[posx][posy+1]-=61;
				return true;
			}
		}
		aux = test(posx-1,posy);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx-1,posy,'N',profundidad-1)){
				gravedadResultado[posx-1][posy]-=61;

				return true;
			}
		}
		aux = test(posx+1,posy);
		if( aux == 'S' || aux == 'T' || aux == 'K' ){
			if(pathFinding(posx+1,posy,'S',profundidad-1)){
				gravedadResultado[posx+1][posy]-=61;

				return true;
			}
		}
		return false;
	}
	
	
}


void ComportamientoJugador::updateMap(Sensores sensores){  												//  ACTUALIZA EL MAPA 
	if(!located){    // Mapa provisional
		mapa[posfil][poscol] = sensores.terreno[0];
		if(facing == 'N'){
			if(sensores.superficie[2] == 'r'){
				gravedad[posfil-1][poscol] += 41;
			}
			mapa[posfil-1][poscol-1] = sensores.terreno[1];
			mapa[posfil-1][poscol] = sensores.terreno[2];
			mapa[posfil-1][poscol+1] = sensores.terreno[3];
			mapa[posfil-2][poscol-2] = sensores.terreno[4];
			mapa[posfil-2][poscol-1] = sensores.terreno[5];
			mapa[posfil-2][poscol] = sensores.terreno[6];
			mapa[posfil-2][poscol+1] = sensores.terreno[7];
			mapa[posfil-2][poscol+2] = sensores.terreno[8];
			mapa[posfil-3][poscol-3] = sensores.terreno[9];
			mapa[posfil-3][poscol-2] = sensores.terreno[10];
			mapa[posfil-3][poscol-1] = sensores.terreno[11];
			mapa[posfil-3][poscol] = sensores.terreno[12];
			mapa[posfil-3][poscol+1] = sensores.terreno[13];
			mapa[posfil-3][poscol+2] = sensores.terreno[14];
			mapa[posfil-3][poscol+3] = sensores.terreno[15];
		}else if(facing == 'W'){
			if(sensores.superficie[2] == 'r'){
				gravedad[posfil][poscol-1] += 41;
			}
			mapa[posfil+1][poscol-1] = sensores.terreno[1];
			mapa[posfil][poscol-1] = sensores.terreno[2];
			mapa[posfil-1][poscol-1] = sensores.terreno[3];
			mapa[posfil+2][poscol-2] = sensores.terreno[4];
			mapa[posfil+1][poscol-2] = sensores.terreno[5];
			mapa[posfil][poscol-2] = sensores.terreno[6];
			mapa[posfil-1][poscol-2] = sensores.terreno[7];
			mapa[posfil-2][poscol-2] = sensores.terreno[8];
			mapa[posfil+3][poscol-3] = sensores.terreno[9];
			mapa[posfil+2][poscol-3] = sensores.terreno[10];
			mapa[posfil+1][poscol-3] = sensores.terreno[11];
			mapa[posfil][poscol-3] = sensores.terreno[12];
			mapa[posfil-1][poscol-3] = sensores.terreno[13];
			mapa[posfil-2][poscol-3] = sensores.terreno[14];
			mapa[posfil-3][poscol-3] = sensores.terreno[15];
		}else if(facing == 'S'){
			if(sensores.superficie[2] == 'r'){
				gravedad[posfil+1][poscol] += 41;
			}
			mapa[posfil+1][poscol+1] = sensores.terreno[1];
			mapa[posfil+1][poscol] = sensores.terreno[2];
			mapa[posfil+1][poscol-1] = sensores.terreno[3];
			mapa[posfil+2][poscol+2] = sensores.terreno[4];
			mapa[posfil+2][poscol+1] = sensores.terreno[5];
			mapa[posfil+2][poscol] = sensores.terreno[6];
			mapa[posfil+2][poscol-1] = sensores.terreno[7];
			mapa[posfil+2][poscol-2] = sensores.terreno[8];
			mapa[posfil+3][poscol+3] = sensores.terreno[9];
			mapa[posfil+3][poscol+2] = sensores.terreno[10];
			mapa[posfil+3][poscol+1] = sensores.terreno[11];
			mapa[posfil+3][poscol] = sensores.terreno[12];
			mapa[posfil+3][poscol-1] = sensores.terreno[13];
			mapa[posfil+3][poscol-2] = sensores.terreno[14];
			mapa[posfil+3][poscol-3] = sensores.terreno[15];
		}else{
			if(sensores.superficie[2] == 'r'){
				gravedad[posfil][poscol+1] += 41;
			}
			mapa[posfil-1][poscol+1] = sensores.terreno[1];
			mapa[posfil][poscol+1] = sensores.terreno[2];
			mapa[posfil+1][poscol+1] = sensores.terreno[3];
			mapa[posfil-2][poscol+2] = sensores.terreno[4];
			mapa[posfil-1][poscol+2] = sensores.terreno[5];
			mapa[posfil][poscol+2] = sensores.terreno[6];
			mapa[posfil+1][poscol+2] = sensores.terreno[7];
			mapa[posfil+2][poscol+2] = sensores.terreno[8];
			mapa[posfil-3][poscol+3] = sensores.terreno[9];
			mapa[posfil-2][poscol+3] = sensores.terreno[10];
			mapa[posfil-1][poscol+3] = sensores.terreno[11];
			mapa[posfil][poscol+3] = sensores.terreno[12];
			mapa[posfil+1][poscol+3] = sensores.terreno[13];
			mapa[posfil+2][poscol+3] = sensores.terreno[14];
			mapa[posfil+3][poscol+3] = sensores.terreno[15];
		}
		char ntest = test(posfil-1,poscol);
		char wtest = test(posfil,poscol-1);
		char etest = test(posfil,poscol+1);
		char stest = test(posfil+1,poscol);
		gravedad[posfil][poscol]+=2;

		if( ntest == 'S' || ntest == 'T' || ntest == 'K' || ntest == 'B'){
			gravedad[posfil-1][poscol]+=1;
		}else{
			gravedad[posfil-1][poscol]+=20;
		}

		if( wtest == 'S' || wtest == 'T' || wtest == 'K' || wtest == 'B' ){
			gravedad[posfil][poscol-1]+=1;
		}else{
			gravedad[posfil][poscol-1]+=20;
		}

		if( etest == 'S' || etest == 'T' || etest == 'K' || etest == 'B' ){
			gravedad[posfil][poscol+1]+=1;
		}else{
			gravedad[posfil][poscol+1]+=20;
		}

		if( stest == 'S' || stest == 'T' || stest == 'K' || stest == 'B' ){
			gravedad[posfil+1][poscol]+=1;
		}else{
			gravedad[posfil+1][poscol]+=20;
		}
			if(gravedad[posfil-1][poscol] > 60)
				gravedad[posfil-1][poscol]=60;
			if(gravedad[posfil+1][poscol] > 60)
				gravedad[posfil+1][poscol]=60;
			if(gravedad[posfil][poscol-1] > 60)
				gravedad[posfil][poscol-1]=60;
			if(gravedad[posfil][poscol+1] > 60)
				gravedad[posfil][poscol+1]=60;


		if(sensores.terreno[0] == 'K'){
			located == true;
			changemap(sensores.mensajeF,sensores.mensajeC);
		}

	}else{					 // Mapa definitivo

		mapaResultado[posfil][poscol] = sensores.terreno[0];

		if(facing == 'N'){
			if(sensores.superficie[2] == 'r'){
				gravedadResultado[posfil-1][poscol] += 41;
			}else if(sensores.superficie[9] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol-3;
			}else if(sensores.superficie[10] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol-2;
			}else if(sensores.superficie[11] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol-1;
			}else if(sensores.superficie[12] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol;
			}else if(sensores.superficie[13] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol+1;
			}else if(sensores.superficie[14] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol+2;
			}else if(sensores.superficie[15] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol+3;
			}
			mapaResultado[posfil-1][poscol-1] = sensores.terreno[1];
			mapaResultado[posfil-1][poscol] = sensores.terreno[2];
			mapaResultado[posfil-1][poscol+1] = sensores.terreno[3];
			mapaResultado[posfil-2][poscol-2] = sensores.terreno[4];
			mapaResultado[posfil-2][poscol-1] = sensores.terreno[5];
			mapaResultado[posfil-2][poscol] = sensores.terreno[6];
			mapaResultado[posfil-2][poscol+1] = sensores.terreno[7];
			mapaResultado[posfil-2][poscol+2] = sensores.terreno[8];
			mapaResultado[posfil-3][poscol-3] = sensores.terreno[9];
			mapaResultado[posfil-3][poscol-2] = sensores.terreno[10];
			mapaResultado[posfil-3][poscol-1] = sensores.terreno[11];
			mapaResultado[posfil-3][poscol] = sensores.terreno[12];
			mapaResultado[posfil-3][poscol+1] = sensores.terreno[13];
			mapaResultado[posfil-3][poscol+2] = sensores.terreno[14];
			mapaResultado[posfil-3][poscol+3] = sensores.terreno[15];
		}else if(facing == 'W'){
			if(sensores.superficie[2] == 'r'){
				gravedadResultado[posfil][poscol-1] += 41;
			}else if(sensores.superficie[9] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol-3;
			}else if(sensores.superficie[10] == 'r'){
				lastkingx= posfil+2; lastkingy = poscol-3;
			}else if(sensores.superficie[11] == 'r'){
				lastkingx= posfil+1; lastkingy = poscol-3;
			}else if(sensores.superficie[12] == 'r'){
				lastkingx= posfil; lastkingy = poscol-3;
			}else if(sensores.superficie[13] == 'r'){
				lastkingx= posfil-1; lastkingy = poscol-3;
			}else if(sensores.superficie[14] == 'r'){
				lastkingx= posfil-2; lastkingy = poscol-3;
			}else if(sensores.superficie[15] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol-3;
			}
			mapaResultado[posfil+1][poscol-1] = sensores.terreno[1];
			mapaResultado[posfil][poscol-1] = sensores.terreno[2];
			mapaResultado[posfil-1][poscol-1] = sensores.terreno[3];
			mapaResultado[posfil+2][poscol-2] = sensores.terreno[4];
			mapaResultado[posfil+1][poscol-2] = sensores.terreno[5];
			mapaResultado[posfil][poscol-2] = sensores.terreno[6];
			mapaResultado[posfil-1][poscol-2] = sensores.terreno[7];
			mapaResultado[posfil-2][poscol-2] = sensores.terreno[8];
			mapaResultado[posfil+3][poscol-3] = sensores.terreno[9];
			mapaResultado[posfil+2][poscol-3] = sensores.terreno[10];
			mapaResultado[posfil+1][poscol-3] = sensores.terreno[11];
			mapaResultado[posfil][poscol-3] = sensores.terreno[12];
			mapaResultado[posfil-1][poscol-3] = sensores.terreno[13];
			mapaResultado[posfil-2][poscol-3] = sensores.terreno[14];
			mapaResultado[posfil-3][poscol-3] = sensores.terreno[15];
		}else if(facing == 'S'){
			if(sensores.superficie[2] == 'r'){
				gravedadResultado[posfil+1][poscol] += 41;
			}else if(sensores.superficie[9] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol+3;
			}else if(sensores.superficie[10] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol+2;
			}else if(sensores.superficie[11] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol+1;
			}else if(sensores.superficie[12] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol;
			}else if(sensores.superficie[13] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol-1;
			}else if(sensores.superficie[14] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol-2;
			}else if(sensores.superficie[15] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol-3;
			}
			mapaResultado[posfil+1][poscol+1] = sensores.terreno[1];
			mapaResultado[posfil+1][poscol] = sensores.terreno[2];
			mapaResultado[posfil+1][poscol-1] = sensores.terreno[3];
			mapaResultado[posfil+2][poscol+2] = sensores.terreno[4];
			mapaResultado[posfil+2][poscol+1] = sensores.terreno[5];
			mapaResultado[posfil+2][poscol] = sensores.terreno[6];
			mapaResultado[posfil+2][poscol-1] = sensores.terreno[7];
			mapaResultado[posfil+2][poscol-2] = sensores.terreno[8];
			mapaResultado[posfil+3][poscol+3] = sensores.terreno[9];
			mapaResultado[posfil+3][poscol+2] = sensores.terreno[10];
			mapaResultado[posfil+3][poscol+1] = sensores.terreno[11];
			mapaResultado[posfil+3][poscol] = sensores.terreno[12];
			mapaResultado[posfil+3][poscol-1] = sensores.terreno[13];
			mapaResultado[posfil+3][poscol-2] = sensores.terreno[14];
			mapaResultado[posfil+3][poscol-3] = sensores.terreno[15];
		}else{
			if(sensores.superficie[2] == 'r'){
				gravedadResultado[posfil][poscol+1] += 41;
			}else if(sensores.superficie[9] == 'r'){
				lastkingx= posfil-3; lastkingy = poscol+3;
			}else if(sensores.superficie[10] == 'r'){
				lastkingx= posfil-2; lastkingy = poscol+3;
			}else if(sensores.superficie[11] == 'r'){
				lastkingx= posfil-1; lastkingy = poscol+3;
			}else if(sensores.superficie[12] == 'r'){
				lastkingx= posfil; lastkingy = poscol+3;
			}else if(sensores.superficie[13] == 'r'){
				lastkingx= posfil+1; lastkingy = poscol+3;
			}else if(sensores.superficie[14] == 'r'){
				lastkingx= posfil+2; lastkingy = poscol+3;
			}else if(sensores.superficie[15] == 'r'){
				lastkingx= posfil+3; lastkingy = poscol+3;
			}
			mapaResultado[posfil-1][poscol+1] = sensores.terreno[1];
			mapaResultado[posfil][poscol+1] = sensores.terreno[2];
			mapaResultado[posfil+1][poscol+1] = sensores.terreno[3];
			mapaResultado[posfil-2][poscol+2] = sensores.terreno[4];
			mapaResultado[posfil-1][poscol+2] = sensores.terreno[5];
			mapaResultado[posfil][poscol+2] = sensores.terreno[6];
			mapaResultado[posfil+1][poscol+2] = sensores.terreno[7];
			mapaResultado[posfil+2][poscol+2] = sensores.terreno[8];
			mapaResultado[posfil-3][poscol+3] = sensores.terreno[9];
			mapaResultado[posfil-2][poscol+3] = sensores.terreno[10];
			mapaResultado[posfil-1][poscol+3] = sensores.terreno[11];
			mapaResultado[posfil][poscol+3] = sensores.terreno[12];
			mapaResultado[posfil+1][poscol+3] = sensores.terreno[13];
			mapaResultado[posfil+2][poscol+3] = sensores.terreno[14];
			mapaResultado[posfil+3][poscol+3] = sensores.terreno[15];
		}

		gravedadResultado[posfil][poscol]+=2;

		char ntest = test(posfil-1,poscol);
		char wtest = test(posfil,poscol-1);
		char etest = test(posfil,poscol+1);
		char stest = test(posfil+1,poscol);
		if(following_plan){
			gravedad[posfil][poscol]+=65;
		}else{
			gravedad[posfil][poscol]+=2;
		}
		if( ntest == 'S' || ntest == 'T' || ntest == 'K' || ntest == 'B'){
			gravedadResultado[posfil-1][poscol]+=1;
		}else{
			gravedadResultado[posfil-1][poscol]+=20;
		}

		if( wtest == 'S' || wtest == 'T' || wtest == 'K' || wtest == 'B'){
			gravedadResultado[posfil][poscol-1]+=1;
		}else{
			gravedadResultado[posfil][poscol-1]+=20;
		}

		if( etest == 'S' || etest == 'T' || etest == 'K' || etest == 'B'){
			gravedadResultado[posfil][poscol+1]+=1;
		}else{
			gravedadResultado[posfil][poscol+1]+=20;
		}

		if( stest == 'S' || stest == 'T' || stest == 'K' || stest == 'B'){
			gravedadResultado[posfil+1][poscol]+=1;
		}else{
			gravedadResultado[posfil+1][poscol]+=20;
		}
			if(gravedadResultado[posfil-1][poscol] > 60)
				gravedadResultado[posfil-1][poscol]=60;
			if(gravedadResultado[posfil+1][poscol] > 60)
				gravedadResultado[posfil+1][poscol]=60;
			if(gravedadResultado[posfil][poscol-1] > 60)
				gravedadResultado[posfil][poscol-1]=60;
			if(gravedadResultado[posfil][poscol+1] > 60)
				gravedadResultado[posfil][poscol+1]=60;
	}

}


void ComportamientoJugador::changemap(int reali, int realj){
	int ofsetfil = posfil - reali;
	int ofsetcol = poscol - realj;
	char auxchar;
	int auxint;
	for(int i=0; i<MAPSIZE; i++){
		for(int j=0; j<MAPSIZE; j++){
			auxchar = mapa[ofsetfil+i][ofsetcol+j]; 
			auxint = gravedad[ofsetfil+i][ofsetcol+j];
			if( '?' == mapaResultado[i][j]){
				mapaResultado[i][j] = auxchar;
			}
			gravedadResultado[i][j] += auxint;
		}
	}
	posfil = reali;
	poscol = realj;
	located = true;
}


char ComportamientoJugador::test(int i, int j){
	if(located){
		return mapaResultado[i][j];
	}else{
		return mapa[i][j];
	}
}


int ComportamientoJugador::testScore(int i, int j){
	if(located){
		return gravedadResultado[i][j];
	}else{
		return gravedad[i][j];
	}
}


bool ComportamientoJugador::algoenMano(){
	return keyMano || zapMano || regMano;
}


Action ComportamientoJugador::choose(Sensores sensores){      											//  TESTEA EL MAPA Y TOMA UNA DECISIÓN
	Action act = actIDLE;	
		int nScore = testScore(posfil-1,poscol);
		int eScore = testScore(posfil,poscol+1);
		int sScore = testScore(posfil+1,poscol);
		int wScore = testScore(posfil,poscol-1);
		char ntest = test(posfil-1,poscol);
		char wtest = test(posfil,poscol-1);
		char etest = test(posfil,poscol+1);
		char stest = test(posfil+1,poscol);
		switch(hue){
			case 0:
				switch (sensores.superficie[2]){
				case '0' : 
						if(algoenMano()){
							regMano = keyMano = zapMano = false;					
							return actPUSH;
						} else {
								hue = 5;
								return actPICKUP;
						}
				case '1' :
						if(algoenMano()){
							regMano = keyMano = zapMano = false;					
							return actPUSH;
						} else {
								hue = 5;
								return actPICKUP;
						}
				case '2' : 
							if(algoenMano()){
								regMano = keyMano = zapMano = false;					
								return actPUSH;
							} else {
									if(tengoZap){
										hue = 5;
										return actPICKUP;
									}else{
										zapMano = tengoZap = true;
										return actPICKUP;
									}
							}
				case '3' :
						if(algoenMano()){
							regMano = keyMano = zapMano = false;					
							return actPUSH;
						} else {
								if(tengoKey){
										hue = 5;
										return actPICKUP;
									}else{
										keyMano = tengoKey = true;
										return actPICKUP;
									}
						}
				case '4' :
						if(algoenMano()){
							regMano = keyMano = zapMano = false;					
							return actPUSH;
						}else {
								if(tengoReg){
									if(located){
										if(facing == 'N'){
											gravedadResultado[posfil-1][poscol] = gravedadResultado[posfil][poscol-1] + 1;
										}else if(facing == 'W'){
											gravedadResultado[posfil][poscol-1] = gravedadResultado[posfil+1][poscol] + 1;
										}else if(facing == 'S'){
											gravedadResultado[posfil+1][poscol] = gravedadResultado[posfil][poscol+1] + 1;
										}else{
											gravedadResultado[posfil][poscol+1] = gravedadResultado[posfil-1][poscol] + 1 ;
										}
									}else{
										if(facing == 'N'){
											gravedad[posfil-1][poscol] = gravedad[posfil][poscol-1] + 1;
										}else if(facing == 'W'){
											gravedad[posfil][poscol-1] = gravedad[posfil+1][poscol] + 1;
										}else if(facing == 'S'){
											gravedad[posfil+1][poscol] = gravedad[posfil][poscol+1] + 1;
										}else{
											gravedad[posfil][poscol+1] = gravedad[posfil-1][poscol] + 1 ;
										}
									}
									return actTURN_L;
								}else{
									following_plan = false;
									regMano = tengoReg = true;
									return actPICKUP;
								}
					}
				default: break;
				}
				if(!located){    /// SI HAY UN PK CERCA VOY HACIA ÉL SI NO HE PISADO YA UNO

					if(facing == 'N'){
						if(test(posfil-1,poscol) == 'K'){
							return actFORWARD;
						}else if(test(posfil,poscol-1) == 'K'){
							return actTURN_L;
						}else if(test(posfil-1,poscol) == 'K'){
							return actTURN_R;
						}else if(test(posfil-1, poscol-1) == 'K'){
							char aux = test(posfil-1,poscol);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_L;
							}
						}else if(test(posfil-1, poscol+1) == 'K'){
							char aux = test(posfil-1,poscol);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_R;
							}
						}
					}else if(facing == 'E'){
						if(test(posfil,poscol+1) == 'K'){
							return actFORWARD;
						}else if(test(posfil-1,poscol) == 'K'){
							return actTURN_L;
						}else if(test(posfil+1,poscol) == 'K'){
							return actTURN_R;
						}else if(test(posfil-1, poscol+1) == 'K'){
							char aux = test(posfil,poscol+1);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_L;
							}
						}else if(test(posfil+1, poscol+1) == 'K'){
							char aux = test(posfil,poscol+1);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_R;
							}
						}
					}else if(facing == 'W'){
						if(test(posfil,poscol-1) == 'K'){
							return actFORWARD;
						}else if(test(posfil+1,poscol) == 'K'){
							return actTURN_L;
						}else if(test(posfil-1,poscol) == 'K'){
							return actTURN_R;
						}else if(test(posfil+1, poscol-1) == 'K'){
							char aux = test(posfil,poscol-1);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_L;
							}
						}else if(test(posfil-1, poscol-1) == 'K'){
							char aux = test(posfil,poscol-1);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_R;
							}
						}
					}else{
						if(test(posfil-1,poscol) == 'K'){
							return actFORWARD;
						}else if(test(posfil,poscol+1) == 'K'){
							return actTURN_L;
						}else if(test(posfil,poscol-1) == 'K'){
							return actTURN_R;
						}else if(test(posfil+1, poscol-1) == 'K'){
							char aux = test(posfil+1,poscol);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_R;
							}
						}else if(test(posfil+1, poscol+1) == 'K'){
							char aux = test(posfil+1,poscol);			
							if(aux == 'S' || aux == 'T'){
								return actFORWARD;
							}else{
								return actTURN_L;
							}
						}
					}
				}

				necesitoZapn = necesitoZape = necesitoZaps = necesitoZapw = false; 
				if(ntest == 'B'){
					if(tengoZap){
						necesitoZapn = true;
					}else{
						nScore += eScore;
					}
				}

				if(etest == 'B'){
					if(tengoZap){
						necesitoZape = true;
					}else{
						eScore += sScore;
					}
				}

				if(wtest == 'B'){
					if(tengoZap){
						necesitoZapw = true;
					}else{
						wScore += nScore;
					}
				}

				if(stest == 'B'){
					if(tengoZap){
						necesitoZaps = true;
					}else{
						sScore += wScore;
					}
				}
				if(facing == 'N'){

						int best_score = nScore;
						act = actFORWARD;
						if(best_score > eScore){
							best_score = eScore;
							act = actTURN_R;
						}
						if(best_score > sScore){
							best_score = sScore;
							act = actTURN_R;
						}
						if(best_score > wScore){
							best_score = wScore;
							act = actTURN_L;
						}
						if(act == actFORWARD){
							if(necesitoZapn){
								buscoZap = true;
							}
						}
						

				}else if(facing == 'E'){

					int best_score = eScore;
					act = actFORWARD;
					if(best_score > nScore){
						best_score = nScore;
						act = actTURN_L;
					}
					if(best_score > sScore){
						best_score = sScore;
						act = actTURN_R;
					}
					if(best_score > wScore){
						best_score = wScore;
						act = actTURN_L;
					}
						if(act == actFORWARD){
							if(necesitoZape){
								buscoZap = true;
							}
						}

				}else if(facing == 'W'){

					int best_score = wScore;
					act = actFORWARD;
					if(best_score > nScore){
						best_score = nScore;
						act = actTURN_R;
					}
					if(best_score > sScore){
						best_score = sScore;
						act = actTURN_L;
					}
					if(best_score > eScore){
						best_score = eScore;
						act = actTURN_L;
					}
						if(act == actFORWARD){
							if(necesitoZapw){
								buscoZap = true;
							}
						}

				}else{

					int best_score = sScore;
					act = actFORWARD;
					if(best_score > eScore){
						best_score = eScore;
						act = actTURN_L;
					}
					if(best_score > wScore){
						best_score = sScore;
						act = actTURN_R;
					}
					if(best_score > nScore){
						best_score = nScore;
						act = actTURN_L;
					}
						if(act == actFORWARD){
							if(necesitoZaps){
								buscoZap = true;
							}
						}
				}

				if(buscoZap){
					switch(zapalgor){
						case 0:
							if(sensores.objetoActivo == '2'){
								zapMano = true;
								regMano = keyMano = false;
								buscoZap = false;
								
							}else{
								zapalgor++;
								return actPUSH;
							}
							break;
						case 1:
							zapalgor--;
							return actPOP;
							break;
					}
				}

				return act;
			

			case 1:
				hue--;
				return actTURN_L;
			case 2:
				hue--;
				return actTURN_L;
			case 3:
				hue--;
				return actTHROW;
			case 4:
				hue--;
				return actTURN_L;
			case 5:
				hue--;
				return actTURN_L;
			}		
}


void ComportamientoJugador::calibrateCompass(Action accion){    	//  CALIBRA LA BRÚJULA SI HE GIRADO, LA POSICIÓN SI HE AVANZADO
		if(accion == actTURN_L){
			if(facing == 'N'){
				facing = 'W';	
			}else if(facing == 'W'){
				facing = 'S';
			}else if(facing == 'S'){
				facing = 'E';
			}else{
				facing = 'N';
			}
		}else if(accion == actTURN_R){
			if(facing == 'N'){
				facing = 'E';	
			}else if(facing == 'W'){
				facing = 'N';
			}else if(facing == 'S'){
				facing = 'W';
			}else{
				facing = 'S';
			}
		}else if(accion == actFORWARD){
			if(facing == 'N'){
				posfil-=1; 
			}else if(facing == 'W'){
				poscol-=1;
			}else if(facing == 'S'){
				posfil+=1;
			}else{
				poscol+=1;
			}
		}
}

void ComportamientoJugador::deadReset(Sensores sensores){
			cout << "He muerto" << endl;
			posfil = MAPSIZE-1; 
			poscol = MAPSIZE-1;
			facing = 'N';  
			located = false;
			plan.clear();
			norepetir = hue = zapalgor = 0;
			lastkingx = lastkingy = -100;
			following_plan = buscoReg = buscoZap = tengoZap = tengoKey = keyMano = zapMano = tengoReg = regMano = false;
			siz = MAPSIZE*2 - 1;
			for(int i=0; i < siz; i++){
				for(int j=0; j < siz; j++){
					mapa[i][j] = '?';
					gravedad[i][j] = 0;
				}
			}
	deads++;
	if(deads==19){rellenoTramposo();}
}	

void ComportamientoJugador::rellenoTramposo(){
	for(int i=0; i < MAPSIZE; i++){
		for(int j=0; j < MAPSIZE; j++){
			if(mapaResultado[i][j] == '?'){
				mapaResultado[i][j] = mapaResultado[i-1][j];
			}
		}
	}
}

Action ComportamientoJugador::think(Sensores sensores){
	Action accion;
	
	if(sensores.reset){   // HE MUERTO, REINICIA EL MAPA AUXILIAR
		deadReset(sensores);
		if(deads%5==0)
		limpiarGravedadResultado();
	}
	if(sensores.colision){   // ME HE CHOCADO, NO CUENTES PASOS
		if(facing == 'N'){
			posfil+=1; 
		}else if(facing == 'W'){
			poscol+=1;
		}else if(facing == 'S'){
			posfil-=1;
		}else{
			poscol-=1;
		}
	}

		updateMap(sensores);
			if(norepetir<=0 && tengoReg && kingNear() && located){
				norepetir = 3;
				if(test(lastkingx-1,lastkingy) == 'S' || test(lastkingx-1,lastkingy) == 'T'){
					if(Astar(lastkingx-1, lastkingy)){
						gravedadResultado[lastkingx][lastkingy] -=61;
						norepetir=20;
					}
				}else if(test(lastkingx+1,lastkingy) == 'S' || test(lastkingx+1,lastkingy) == 'T'){
					if(Astar(lastkingx+1, lastkingy)){
						gravedadResultado[lastkingx][lastkingy] -=61;
						norepetir=20;
					}
				}else if(test(lastkingx,lastkingy-1) == 'S' || test(lastkingx,lastkingy-1) == 'T'){
					if(Astar(lastkingx, lastkingy-1)){
						gravedadResultado[lastkingx][lastkingy] -=61;
						norepetir=20;
					}
				}else if(test(lastkingx,lastkingy+1) == 'S' || test(lastkingx-1,lastkingy) == 'T'){
					if(Astar(lastkingx, lastkingy+1)){
						gravedadResultado[lastkingx][lastkingy] -=61;
						norepetir=20;
					}
				}

				accion = choose(sensores);
			}else{
				if(located && !tengoReg && norepetir<=1){
					vector<pair<int,int> > aux = sensores.regalos;
					int best = -1;
					int distbest = 300;
					int max = aux.size();
					for(int i=0; i<max; i++){
						if(distbest > abs(aux[i].first-posfil) + abs(aux[i].second-poscol)){
							best = i;
							distbest = abs(aux[i].first-posfil) + abs(aux[i].second-poscol);
						}
					}
					if(distbest<20 && Astar(aux[best].first,aux[best].second)){
						norepetir=21;
					}else{
						norepetir = 5;
					}
				}					
				norepetir--;
				accion = choose(sensores);
			}

				if(sensores.superficie[2] == 'r' && tengoReg){
					switch(zapalgor){
						case 0:
							if(sensores.objetoActivo == '4'){
								regMano = false;
								zapMano = keyMano = false;
								tengoReg = false;
								accion = actGIVE;
								following_plan = false;
							}else{
								zapalgor=1;
								accion = actPUSH;
							}
							break;
						case 1:
							zapalgor=0;
							accion = actPOP;
							break;
					}
				
		}
		
		calibrateCompass(accion);
/*			UNCOMMENT TO CONSOLE MODE 
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Mochila: " << sensores.mochila << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << "Fila: " << sensores.mensajeF << endl;
	cout << "Columna: " << sensores.mensajeC << endl;
	cout << "objetoActivo: " << sensores.objetoActivo << endl;
*/

	lastaccion = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
