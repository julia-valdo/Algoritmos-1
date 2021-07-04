#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"

static const int MAX_TERRENO_1_2 = 15;
static const int MAX_TERRENO_3_4 = 20;
static const char ELFOS = 'L';
static const char ENANOS = 'G';
static const char ORCOS = 'O';
static const int NIVEL_ESTE = 1;
static const int NIVEL_OESTE = 2;
static const int NIVEL_NORTE = 3;
static const int NIVEL_SUR = 4;
static const int JUGANDO = 0;
static const int GANADO = 1;
static const int VALIDO = 0;
static const int INVALIDO = -1;
const int PERDIDO = -1;
const int RESISTENCIA_T = 600;
const int ENANOS_EXTRA = 10;
const int ELFOS_EXTRA = 10;
const int CRITICO_MALO = 0;
const int CRITICO_REGULAR = 10;
const int CRITICO_BUENO = 25;
const int ATAQUE_LEGOLAS = 30;
const int ATAQUE_GIMLI = 60;
const int ATAQUE_CRITICO_LEGOLAS = 70;
const int ATAQUE_CRITICO_GIMLI = 100;
const int DISTANCIA_MIN_ELFO = 3;
const int DISTANCIA_MIN_ENANO = 2;
const int VIDA_ORCOS = 200;
const int CANT_ORCOS_ESTE = 100;
const int CANT_ORCOS_OESTE = 200;
const int CANT_ORCOS_NORTE = 300;
const int CANT_ORCOS_SUR = 500;
const int CAMINO_UNO = 1;
const int CAMINO_DOS = 2;
const int SE_MURIO = 0;
const int CONFIG_ESTANDAR = -1;
const char TIERRA = '-';
const char ENTRADA = 'E';
const char TORRE = 'T';
const char CAMINO = ' ';
#define ANIMO_BUENO 'B'
#define ANIMO_REGULAR 'R'
#define ANIMO_MALO 'M'

/*
 * Pre: recibe un struct de torres.
 * Post: inicializa las torres.
 */
void cargar_torre(torres_t* torres){

	(*torres).resistencia_torre_1 = RESISTENCIA_T;
	(*torres).resistencia_torre_2 = RESISTENCIA_T;
	(*torres).enanos_extra = ENANOS_EXTRA;
	(*torres).elfos_extra = ELFOS_EXTRA;
}

/*
 * Pre:
 * Post: dependiendo del animo, asigna la probabilidad de golpe critico.
 */
int calcular_porcentaje_critico(char animo){

	int probabilidad_critico = 0;

	switch(animo){
		case ANIMO_MALO:
			probabilidad_critico = CRITICO_MALO;
			break;
		case ANIMO_REGULAR:
			probabilidad_critico = CRITICO_REGULAR;
			break;
		case ANIMO_BUENO:
			probabilidad_critico = CRITICO_BUENO;
			break;
	}
	return probabilidad_critico;
}

/*
 * Pre:
 * Post: dependiendo del ambiente, calcula el porcentaje de fallo.
 */
int calcular_porcentaje_fallo(int ambiente){

	int porcentaje_fallo = (ambiente/2);

	return porcentaje_fallo;
}

void inicializar_juego(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli/*, configuracion_t configuracion*/){

	(*juego).nivel.tope_enemigos = 0;

	(*juego).nivel.tope_defensores = 0;

	cargar_torre(&((*juego).torres));
	
	(*juego).critico_legolas = calcular_porcentaje_critico(animo_legolas);
		
	(*juego).critico_gimli = calcular_porcentaje_critico(animo_gimli);

	(*juego).fallo_legolas = calcular_porcentaje_fallo(viento);

	(*juego).fallo_gimli = calcular_porcentaje_fallo(humedad);

}

int estado_nivel(nivel_t nivel);

int estado_juego(juego_t juego){

	int estado_juego = JUGANDO;

	if(juego.nivel_actual == NIVEL_SUR && estado_nivel(juego.nivel) == GANADO){
		estado_juego = GANADO;
	}
	
	if(juego.torres.resistencia_torre_1 <= 0 || juego.torres.resistencia_torre_2 <= 0){
		estado_juego = PERDIDO;
	}

	return estado_juego;
}

int estado_nivel(nivel_t nivel){

	int estado_nivel = GANADO;

	for(int i = 0; i < nivel.max_enemigos_nivel; i++){ 
		if(nivel.enemigos[i].vida > 0) 
			estado_nivel = JUGANDO;	
	}

	return estado_nivel;
}

/*
 * Pre: recibe un tipo de defensor (ENANO o ELFO).
 * Post: devuelve la fuerza con el que va a pegar el defensor.
 */
int calcular_fuerza_ataque(char tipo){

	int fuerza = 0;

	if(tipo == ENANOS){
		fuerza = ATAQUE_GIMLI;
	}
	else if(tipo == ELFOS){
		fuerza = ATAQUE_LEGOLAS;
	}		
	return fuerza;
}

/*
 * Pre: recibe un nivel en proceso y la fila y columna del defensor agregado.
 * Post: devuelve VALIDO si el defensor pudo agregarse correctamente o INVALIDO si no se pudo agregar.
 */
int verificar_posicion(nivel_t* nivel, int fil, int col){

	int i = 0;
	int j = 0;
	int k = 0;

	int defensor_agregado = VALIDO;

	while(i < (*nivel).tope_defensores){	
		if((fil == (*nivel).defensores[i].posicion.fil) && (col == (*nivel).defensores[i].posicion.col)){

			defensor_agregado = INVALIDO;
		}
		i++;
	}

	if(defensor_agregado == VALIDO){
		while(j < (*nivel).tope_camino_1){
			if((fil == (*nivel).camino_1[j].fil) && (col == (*nivel).camino_1[j].col)){
				defensor_agregado = INVALIDO;

			}
			j++;
		}
		
		while(k < (*nivel).tope_camino_2){
			if((fil == (*nivel).camino_2[k].fil) && (col == (*nivel).camino_2[k].col)){
				defensor_agregado = INVALIDO;
			}
			k++;			
		}
	}
	
	return defensor_agregado;
}

int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){

	int posicionado = VALIDO;

	(*nivel).defensores[(*nivel).tope_defensores].tipo = tipo;
	(*nivel).defensores[(*nivel).tope_defensores].fuerza_ataque = calcular_fuerza_ataque(tipo);	
	(*nivel).defensores[(*nivel).tope_defensores].posicion.fil = posicion.fil;
	(*nivel).defensores[(*nivel).tope_defensores].posicion.col = posicion.col;
	posicionado = verificar_posicion(nivel, posicion.fil, posicion.col);
	if(posicionado == VALIDO)
		(*nivel).tope_defensores++;
	
	return posicionado;
}

/*
 * Pre: recibe fila y columna del defensor (ELFO) y fila y columna del enemigo.
 * Post: devuelve la distancia manhattan que hay entre ellos.
 */
int calcular_dist_manhattan(int fil_defensor, int col_defensor, int fil_enemigo, int col_enemigo){

	int fila = abs((fil_defensor - fil_enemigo));
	int columna = abs((col_defensor - col_enemigo));

	return (fila + columna);
}

/*
 * Pre: recibe fila y columna del defensor (ENANO) y fila y columna del enemigo.
 * Post: devuelve la distancia que hay entre ellos.
 */
int calcular_distancia_enanos(int fil_defensor, int col_defensor, int fil_enemigo, int col_enemigo){

	int x = (fil_defensor - fil_enemigo);
	int y = (col_defensor - col_enemigo);
	int distancia = ((x*x) + (y*y));

	return distancia;
}

/*
 * Pre: recibe un juego en proceso, las coordenadas del enemigo y  las coordendas del defensor.
 * Post: devuelve true si hay un enemigo a distancia <= 2 o false en caso contrario.
 */
bool enemigo_cerca_enano(juego_t* juego, coordenada_t pos_enemigo_encontrado, coordenada_t posicion){
	
	bool enemigo_cerca = false;

	int distancia = calcular_distancia_enanos(posicion.fil, posicion.col, pos_enemigo_encontrado.fil, pos_enemigo_encontrado.col); 
	if(distancia <= DISTANCIA_MIN_ENANO)
		enemigo_cerca = true;	
	else
		enemigo_cerca = false;		
	
	return enemigo_cerca;
}

/*
 * Pre: recibe el fallo del defensor.
 * Post: devuelve true si probabilidad_fallo < fallo, y false en caso contrario. 
 */
bool fallo_ataque(int fallo){

	bool falla = false;

	int probabilidad_fallo = rand() % 99;

	if(probabilidad_fallo < fallo)
		falla = true;
	else
		falla = false;
	

	return falla;
}

/*
 * Pre: recibe un juego en proceso y el tipo del defensor.
 * Post: devuelve la fuerza con la que pega el defensor.
 */
int fuerza_ataque(juego_t* juego, char tipo){

	int fuerza = 0;
	int critico = rand() % 99;

	if(tipo == ENANOS){
		if(critico < (*juego).critico_gimli)
			fuerza = ATAQUE_CRITICO_GIMLI;
		else
			fuerza = ATAQUE_GIMLI;
	}else if(tipo == ELFOS){
		if(critico < (*juego).critico_legolas)
			fuerza = ATAQUE_CRITICO_LEGOLAS;
		else
			fuerza = ATAQUE_LEGOLAS;
		
	}
	return fuerza;
}

/*
 * Pre: recibe un juego en proceso y un struct de defensores cargado.
 * Post: verifica que tenga un enemigo cerca y si falla el ataque. Si tiene un enemigo cerca y no falla el ataque, ataca.
 */
void juegan_enanos(juego_t* juego, defensor_t defensor){

	int i = 0;
	bool falla_ataque = false;
	bool enemigo_cerca = false;
	coordenada_t pos_enemigo_encontrado;
	
	while(enemigo_cerca == false && i < (*juego).nivel.tope_enemigos){
		if((*juego).nivel.enemigos[i].camino == CAMINO_UNO)
			pos_enemigo_encontrado = (*juego).nivel.camino_1[(*juego).nivel.enemigos[i].pos_en_camino];
		else 
			pos_enemigo_encontrado = (*juego).nivel.camino_2[(*juego).nivel.enemigos[i].pos_en_camino];

		if((*juego).nivel.enemigos[i].vida > 0){
			enemigo_cerca = enemigo_cerca_enano(juego, pos_enemigo_encontrado, defensor.posicion);
			if(enemigo_cerca == true){
				falla_ataque = fallo_ataque((*juego).fallo_gimli);
				if(falla_ataque == false){ 
					(*juego).nivel.enemigos[i].vida -= fuerza_ataque(juego, defensor.tipo); 
				}
			}
		}
		i++;
	}
	
}

/*
 * Pre: recibe un juego en proceso, las coordenadas del enemigo y  las coordendas del defensor.
 * Post: devuelve true si hay un enemigo a distancia <= DISTANCIA_MIN_ELFO o false en caso contrario.
 */
bool enemigo_cerca_elfo(juego_t* juego, coordenada_t posicion, coordenada_t pos_enemigo_encontrado){

	bool enemigo_cerca = false;
	
	int distancia = calcular_dist_manhattan(posicion.fil, posicion.col, pos_enemigo_encontrado.fil, pos_enemigo_encontrado.col); 
	if(distancia <= DISTANCIA_MIN_ELFO){
		enemigo_cerca = true;
	}else
		enemigo_cerca = false;		
		
	return enemigo_cerca;
}

/*
 * Pre: recibe un juego en proceso y un struct de defensores cargado.
 * Post: verifica que tenga un enemigo cerca y si falla el ataque. Si tiene un enemigo cerca y no falla el ataque, ataca.
 */
void juegan_elfos(juego_t* juego, defensor_t defensor){ 

	bool hay_enemigo = false;
	bool falla_ataque = false;
	coordenada_t pos_enemigo_encontrado;

	for(int i = 0; i < (*juego).nivel.tope_enemigos; i++){
		if((*juego).nivel.enemigos[i].camino == CAMINO_UNO)
			pos_enemigo_encontrado = (*juego).nivel.camino_1[(*juego).nivel.enemigos[i].pos_en_camino];
		else 
			pos_enemigo_encontrado = (*juego).nivel.camino_2[(*juego).nivel.enemigos[i].pos_en_camino];

		if((*juego).nivel.enemigos[i].vida > 0){
			hay_enemigo = enemigo_cerca_elfo(juego, defensor.posicion, pos_enemigo_encontrado); 
			if(hay_enemigo == true){
				falla_ataque = fallo_ataque((*juego).fallo_legolas);
				if(falla_ataque == false){ 
					defensor.fuerza_ataque = fuerza_ataque(juego, defensor.tipo); 
					(*juego).nivel.enemigos[i].vida -= defensor.fuerza_ataque; 
				}
			}
		}
		
	}	  
}

/*
 * Pre: recibe un juego en proceso.
 * Post: inicializa a los enemigos.
 */
void agregar_enemigo(juego_t* juego){

	if((*juego).nivel.tope_enemigos < (*juego).nivel.max_enemigos_nivel){

		if((*juego).nivel_actual == NIVEL_ESTE || (*juego).nivel_actual == NIVEL_OESTE){
			(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].camino = CAMINO_UNO;
			(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].pos_en_camino = 0;
			(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].vida = VIDA_ORCOS + rand() % 99;
			(*juego).nivel.tope_enemigos++;	
		}else if((*juego).nivel_actual == NIVEL_NORTE || (*juego).nivel_actual == NIVEL_SUR){
			if((*juego).nivel.tope_enemigos%2 == 0){
				(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].camino = CAMINO_UNO;
				(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].pos_en_camino = 0;
				(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].vida = VIDA_ORCOS + rand() % 99;			
			}else{
				(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].camino = CAMINO_DOS;
				(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].pos_en_camino = 0;
				(*juego).nivel.enemigos[(*juego).nivel.tope_enemigos].vida = VIDA_ORCOS + rand() % 99;
			}
			(*juego).nivel.tope_enemigos++;		
		}

	}

}

/*
 * Pre: recibe un juego en proceso.
 * Post: hace que los orcos avancen por el camino y le peguen a la torre en caso de haber llegado a una.
 */
void juegan_orcos_1_2(juego_t* juego){

	for(int i = 0; i < (*juego).nivel.tope_enemigos; i++){
		if((*juego).nivel.enemigos[i].vida > 0){
			(*juego).nivel.enemigos[i].pos_en_camino++; 
			if((*juego).nivel.enemigos[i].pos_en_camino == (*juego).nivel.tope_camino_1 -1){ 
				if((*juego).nivel_actual == NIVEL_ESTE){
					(*juego).torres.resistencia_torre_1 -= (*juego).nivel.enemigos[i].vida; 
					(*juego).nivel.enemigos[i].vida = 0;					
				}else{
					(*juego).torres.resistencia_torre_2 -= (*juego).nivel.enemigos[i].vida; 
					(*juego).nivel.enemigos[i].vida = 0;
				}
			}
		}

	}
	agregar_enemigo(juego); 
}

/*
 * Pre: recibe un juego en proceso.
 * Post: hace que los orcos avancen por el camino y le peguen a la torre en caso de haber llegado a una.
 */
void juegan_orcos_3_4(juego_t* juego){

	for(int i = 0; i < (*juego).nivel.tope_enemigos; i++){
		if((*juego).nivel.enemigos[i].vida > 0){
			(*juego).nivel.enemigos[i].pos_en_camino++; 
			if((*juego).nivel.enemigos[i].camino == CAMINO_UNO){
				if((*juego).nivel.enemigos[i].pos_en_camino == (*juego).nivel.tope_camino_1 -1){ 
					(*juego).torres.resistencia_torre_1 -= (*juego).nivel.enemigos[i].vida; 
					(*juego).nivel.enemigos[i].vida = 0;
				}
			}else{
				if((*juego).nivel.enemigos[i].pos_en_camino == (*juego).nivel.tope_camino_2 -1){ 
				(*juego).torres.resistencia_torre_2 -= (*juego).nivel.enemigos[i].vida; 
				(*juego).nivel.enemigos[i].vida = 0;
				}
			}
		}
	}
	agregar_enemigo(juego); 
	agregar_enemigo(juego); 
}


/*
 * Pre: recibe un juego en proceso.
 * Post: inicializa max_enemigos_nivel y hace que los orcos jueguen.
 */
void juegan_orcos(juego_t* juego){

	if((*juego).nivel_actual == NIVEL_ESTE){
		(*juego).nivel.max_enemigos_nivel = CANT_ORCOS_ESTE;
	}else if((*juego).nivel_actual == NIVEL_OESTE){
		(*juego).nivel.max_enemigos_nivel = CANT_ORCOS_OESTE;
	}else if((*juego).nivel_actual == NIVEL_NORTE){
		(*juego).nivel.max_enemigos_nivel = CANT_ORCOS_NORTE;
	}else if((*juego).nivel_actual == NIVEL_SUR){
		(*juego).nivel.max_enemigos_nivel = CANT_ORCOS_SUR;
	}

	if((*juego).nivel_actual == NIVEL_ESTE || (*juego).nivel_actual == NIVEL_OESTE){
		juegan_orcos_1_2(juego);		
	}else if((*juego).nivel_actual == NIVEL_NORTE || (*juego).nivel_actual == NIVEL_SUR){
		juegan_orcos_3_4(juego);
	}
}

void jugar_turno(juego_t* juego){

	for(int i = 0; i < (*juego).nivel.tope_defensores; i++){ // recorro los defensores
		if((*juego).nivel.defensores[i].tipo == ENANOS){ // si son enanos
			juegan_enanos(juego, (*juego).nivel.defensores[i]); //los hago jugar
		}
	}

	for(int i = 0; i < (*juego).nivel.tope_defensores; i++){
		if((*juego).nivel.defensores[i].tipo == ELFOS){
			juegan_elfos(juego, (*juego).nivel.defensores[i]);
		}
	}
		
	juegan_orcos(juego);
}

void mostrar_terreno_chico(juego_t juego, defensor_t defensores[MAX_DEFENSORES], char terreno[MAX_TERRENO_1_2][MAX_TERRENO_1_2], coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
	
	for(int i = 0; i < MAX_TERRENO_1_2; i++){
    	for(int j = 0; j < MAX_TERRENO_1_2; j++){
    		terreno[i][j] = TIERRA;
   		}
  	}
  
	for(int i = 0; i < tope_camino; i++){
    	terreno[camino[i].fil][camino[i].col] = CAMINO;
  	}

  	for(int i = 0; i < juego.nivel.tope_enemigos; i++){
  		if(juego.nivel.enemigos[i].vida > 0)
  			terreno[camino[juego.nivel.enemigos[i].pos_en_camino].fil][camino[juego.nivel.enemigos[i].pos_en_camino].col] = ORCOS;
	}

  	for(int i = 0; i < juego.nivel.tope_defensores; i++){  		  			
  		if(defensores[i].tipo == ELFOS){
    		terreno[defensores[i].posicion.fil][defensores[i].posicion.col] = ELFOS;
  		}else if(defensores[i].tipo == ENANOS){
			terreno[defensores[i].posicion.fil][defensores[i].posicion.col] = ENANOS;
		}
  	}

 	for(int i = 0; i < MAX_TERRENO_1_2; i++){
    	for (int j = 0; j < MAX_TERRENO_1_2; j++){
     		if(i == camino[tope_camino-1].fil && j == camino[tope_camino-1].col){
        		terreno[i][j] = TORRE;
      		}
     		if(i == camino[0].fil && j == camino[0].col){
        		terreno[i][j] = ENTRADA;
      		}
     	printf("%c", terreno[i][j]);
   		}   
    printf("\n");
  	}  	
}

void mostrar_terreno_grande(juego_t juego, defensor_t defensores[MAX_DEFENSORES], char terreno[MAX_TERRENO_3_4][MAX_TERRENO_3_4], coordenada_t camino_1[MAX_LONGITUD_CAMINO], 
	                        int tope_camino_1, coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_2){

	for(int i = 0; i < MAX_TERRENO_3_4; i++){
    	for (int j = 0; j < MAX_TERRENO_3_4; j++){
    		terreno[i][j] = TIERRA;
   		}
  	}
  
	for(int i = 0; i < tope_camino_1; i++){
	    terreno[camino_1[i].fil][camino_1[i].col] = CAMINO;		
	}
	for(int j = 0; j < tope_camino_2; j++){
	    	terreno[camino_2[j].fil][camino_2[j].col] = CAMINO;		
		
  	}

  	for(int i = 0; i < juego.nivel.tope_enemigos; i++){ 
  		if(juego.nivel.enemigos[i].vida > 0){
  			if(juego.nivel.enemigos[i].camino == CAMINO_UNO)
  				terreno[camino_1[juego.nivel.enemigos[i].pos_en_camino].fil][camino_1[juego.nivel.enemigos[i].pos_en_camino].col] = ORCOS;
  			else
	  			terreno[camino_2[juego.nivel.enemigos[i].pos_en_camino].fil][camino_2[juego.nivel.enemigos[i].pos_en_camino].col] = ORCOS;
		}
	}

  	for(int i = 0; i < juego.nivel.tope_defensores; i++){
  		  			
  		if(defensores[i].tipo == ELFOS){
    		terreno[defensores[i].posicion.fil][defensores[i].posicion.col] = ELFOS;
  		}else if(defensores[i].tipo == ENANOS){
			terreno[defensores[i].posicion.fil][defensores[i].posicion.col] = ENANOS;
		}
  	}

 	for(int i = 0; i < MAX_TERRENO_3_4; i++){
    	for(int j = 0; j < MAX_TERRENO_3_4; j++){
     		if((i == camino_1[tope_camino_1-1].fil || i == camino_2[tope_camino_2-1].fil) && (j == camino_1[tope_camino_1-1].col || j == camino_2[tope_camino_2-1].col)){
        		terreno[i][j] = TORRE;
      		}
     		if((i == camino_1[0].fil || i == camino_2[0].fil) && (j == camino_1[0].col || j == camino_2[0].col)){
        		terreno[i][j] = ENTRADA;
      		}
     	printf("%c", terreno[i][j]);
   		}   
    printf("\n");
  	}

}

void mostrar_juego(juego_t juego){

	system("clear");

	char terreno_chico[MAX_TERRENO_1_2][MAX_TERRENO_1_2];	
	char terreno_grande[MAX_TERRENO_3_4][MAX_TERRENO_3_4];	
	
	printf("NIVEL: %i\n", juego.nivel_actual);

	if(juego.nivel_actual == NIVEL_ESTE || juego.nivel_actual == NIVEL_OESTE){
		mostrar_terreno_chico(juego, juego.nivel.defensores, terreno_chico, juego.nivel.camino_1, juego.nivel.tope_camino_1);
	}else if(juego.nivel_actual == NIVEL_NORTE || juego.nivel_actual == NIVEL_SUR){
		mostrar_terreno_grande(juego, juego.nivel.defensores, terreno_grande, juego.nivel.camino_1, juego.nivel.tope_camino_1, juego.nivel.camino_2, juego.nivel.tope_camino_2);
	}

	printf("Resistencia TORRE 1: %i            Resistencia TORRE 2: %i\n", juego.torres.resistencia_torre_1, juego.torres.resistencia_torre_2);
  	printf("Enanos extra: %i                     Elfos extra: %i\n", juego.torres.enanos_extra, juego.torres.elfos_extra);
}