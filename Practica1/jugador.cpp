#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;


void ComportamientoJugador::updateMap(Sensores sensores){  												//  ACTUALIZA EL MAPA 
	if(!located){    // Mapa provisional
		mapa[posfil][poscol] = sensores.terreno[0];
		if(facing == 'N'){
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

		if( ntest == 'S' || ntest == 'T' || ntest == 'K' ){
			gravedad[posfil-1][poscol]+=1;
		}else{
			gravedad[posfil-1][poscol]+=20;
		}

		if( wtest == 'S' || wtest == 'T' || wtest == 'K' ){
			gravedad[posfil][poscol-1]+=1;
		}else{
			gravedad[posfil][poscol-1]+=20;
		}

		if( etest == 'S' || etest == 'T' || etest == 'K' ){
			gravedad[posfil][poscol+1]+=1;
		}else{
			gravedad[posfil][poscol+1]+=20;
		}

		if( stest == 'S' || stest == 'T' || stest == 'K' ){
			gravedad[posfil+1][poscol]+=1;
		}else{
			gravedad[posfil+1][poscol]+=20;
		}

		if(sensores.terreno[0] == 'K'){
			located == true;
			changemap(sensores.mensajeF,sensores.mensajeC);
		}

	}else{					 // Mapa definitivo

		mapaResultado[posfil][poscol] = sensores.terreno[0];

		if(facing == 'N'){
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
		gravedad[posfil][poscol]+=2;

		if( ntest == 'S' || ntest == 'T' || ntest == 'K' ){
			gravedadResultado[posfil-1][poscol]+=1;
		}else{
			gravedadResultado[posfil-1][poscol]+=20;
		}

		if( wtest == 'S' || wtest == 'T' || wtest == 'K' ){
			gravedadResultado[posfil][poscol-1]+=1;
		}else{
			gravedadResultado[posfil][poscol-1]+=20;
		}

		if( etest == 'S' || etest == 'T' || etest == 'K' ){
			gravedadResultado[posfil][poscol+1]+=1;
		}else{
			gravedadResultado[posfil][poscol+1]+=20;
		}

		if( stest == 'S' || stest == 'T' || stest == 'K' ){
			gravedadResultado[posfil+1][poscol]+=1;
		}else{
			gravedadResultado[posfil+1][poscol]+=20;
		}

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
	return keyMano || bikMano || zapMano;
}

Action ComportamientoJugador::choose(Sensores sensores){      											//  TESTEA EL MAPA Y TOMA UNA DECISIÓN
	Action act = actIDLE;	
		int nScore = testScore(posfil-1,poscol);
		int eScore = testScore(posfil,poscol+1);
		int sScore = testScore(posfil+1,poscol);
		int wScore = testScore(posfil,poscol-1);
		switch(hue){
			case 0:
				switch (sensores.superficie[2]){
				case '0' : 
						if(algoenMano()){
							keyMano = zapMano = bikMano = false;					
							return actPUSH;
						} else {
								hue = 5;
								return actPICKUP;
						}
				case '1' :
						if(algoenMano()){
							keyMano = zapMano = bikMano = false;					
							return actPUSH;
						} else {
								hue = 5;
								return actPICKUP;
						}
				case '2' : 
							if(algoenMano()){
								keyMano = zapMano = bikMano = false;					
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
							keyMano = zapMano = bikMano = false;					
							return actPUSH;
						} else {
								keyMano = tengoKey = true;
								return actPICKUP;
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

void ComportamientoJugador::deadReset(){
			cout << "HE MUERTO" << endl;
			posfil = MAPSIZE-1; 
			poscol = MAPSIZE-1;
			facing = 'N'; 
			located = false;
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
		deadReset();
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

		accion = choose(sensores);
		
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


	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
