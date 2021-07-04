#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include "comandos.h"

#define ESTANDAR "-1"
#define MAX_CAMINO 200

const int DEFENSORES_ESTE = 5;
const int DEFENSORES_OESTE = 5;
const int DEFENSORES_NORTE = 6;
const int DEFENSORES_SUR = 8;
const int MAX_TERRENO_1_2 = 15;
const int MAX_TERRENO_3_4 = 20;
const int VIDA_DEF_EXTRA = 50;
const int NIVEL_ESTE = 1;
const int NIVEL_OESTE = 2;
const int NIVEL_NORTE = 3;
const int NIVEL_SUR = 4;
static const int JUGANDO = 0;
static const int GANADO = 1;
static const int VALIDO = 0;
static const int INVALIDO = -1;
static const int CONFIG_ESTANDAR = -1;
static const char ELFOS = 'L';
static const char ENANOS = 'G';
static const char TIERRA = '-';
static const char ENTRADA = 'E';
static const char TORRE = 'T';
static const char CAMINO = ' ';

void pedir_posicion(int* fil, int* col){

	printf("-----------POSICIONA A TU DEFENSOR-----------\n");
	
	printf("En que fila queres posicionar a tu defensor?:\n");
	scanf("%i", fil);
	
	printf("En que columna queres posicionar a tu defensor?:\n");
	scanf("%i", col);

}

/*
 * Pre: recibe un juego en proceso.
 * Post: se inicializan los defensores.
 */
void cargar_defensores(juego_t* juego, configuracion_t* configuracion){

	coordenada_t posicion;
	int defensor_agregado = VALIDO;
	int enanos_iniciales;
	int elfos_iniciales;

	if((*juego).nivel_actual == NIVEL_ESTE){

		enanos_iniciales = DEFENSORES_ESTE;
		if((*configuracion).enanos.nivel_este != CONFIG_ESTANDAR){
			enanos_iniciales = (*configuracion).enanos.nivel_este;
		}

		for(int i = 0; i < enanos_iniciales; i++){
			(*juego).nivel.defensores[i].tipo = ENANOS;
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			system("clear");
			mostrar_juego(*juego);
		}
	}else if((*juego).nivel_actual == NIVEL_OESTE){

		elfos_iniciales = DEFENSORES_OESTE;
		if((*configuracion).elfos.nivel_oeste != CONFIG_ESTANDAR){
			elfos_iniciales = (*configuracion).elfos.nivel_oeste;
		}

		for(int i = 0; i < elfos_iniciales; i++){
			(*juego).nivel.defensores[i].tipo = ELFOS;
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			system("clear");
			mostrar_juego(*juego);			
		}
	}else if((*juego).nivel_actual == NIVEL_NORTE){

		enanos_iniciales = NIVEL_NORTE;
		elfos_iniciales = NIVEL_NORTE;
		if((*configuracion).elfos.nivel_norte != CONFIG_ESTANDAR){
			elfos_iniciales = (*configuracion).elfos.nivel_norte;
		}
		if((*configuracion).enanos.nivel_norte != CONFIG_ESTANDAR){
			enanos_iniciales = (*configuracion).enanos.nivel_norte;
		}				
		for(int i = 0; i < enanos_iniciales; i++){
			(*juego).nivel.defensores[i].tipo = ENANOS;
			
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			system("clear");
			mostrar_juego(*juego);			
		}
		for(int i = enanos_iniciales; i < (enanos_iniciales+elfos_iniciales); i++){
			(*juego).nivel.defensores[i].tipo = ELFOS;
			
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			system("clear");
			mostrar_juego(*juego);			
		}	
	}else if((*juego).nivel_actual == NIVEL_SUR){
		
		enanos_iniciales = NIVEL_SUR;
		elfos_iniciales = NIVEL_SUR;
		if((*configuracion).elfos.nivel_sur != CONFIG_ESTANDAR){
			elfos_iniciales = (*configuracion).elfos.nivel_sur;
		}
		if((*configuracion).enanos.nivel_sur != CONFIG_ESTANDAR){
			enanos_iniciales = (*configuracion).enanos.nivel_sur;
		}				
		for(int i = 0; i < enanos_iniciales; i++){
			(*juego).nivel.defensores[i].tipo = ENANOS;
			
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			system("clear");
			mostrar_juego(*juego);			
		}
		for(int i = enanos_iniciales; i < (enanos_iniciales+elfos_iniciales); i++){
			(*juego).nivel.defensores[i].tipo = ELFOS;
			
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			system("clear");
			mostrar_juego(*juego);			
		}
	}
}

/*
 * Pre: el archivo de caminos debe de estar creado.
 * Post: abre y lee el archivo de caminos y los carga en el struct de coordenadas de cada camino.
 */
void cargar_camino(char nombre_camino[MAX_NOMBRE], coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int nivel_actual, int* tope_camino_1, int* tope_camino_2, char nivel_solicitado[MAX_NOMBRE], char camino_solicitado[MAX_NOMBRE]){

	int i = 0;
	int leidos = 2;
	
	char campo[MAX_NOMBRE];
	
	FILE* caminos = fopen(nombre_camino, "r");
	if(!caminos){
		perror("Error");
		return;
	}

	fscanf(caminos, "%s\n", campo);
	while(strcmp(campo, nivel_solicitado) != 0){
		fscanf(caminos, "%s\n", campo);
	}

	fscanf(caminos, "%s\n", campo);
	while(strcmp(campo, camino_solicitado) != 0){
		fscanf(caminos, "%s\n", campo);
	}

	while(leidos == 2){
		if(strcmp(camino_solicitado, "CAMINO=1") == 0){
			(*tope_camino_1)++;
			leidos = fscanf(caminos, "%i;%i\n", &camino_1[i].fil, &camino_1[i].col);
			i++;
		}else{
			(*tope_camino_2)++;
			leidos = fscanf(caminos, "%i;%i\n", &camino_2[i].fil, &camino_2[i].col);
			i++;
		}
	}
	(*tope_camino_1)--;	
	(*tope_camino_2)--;

	fclose(caminos);
}

/*
 * Pre: recibe un juego en proceso y coordenadas para la entrada y torre.
 * Post: obtiene un camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_este(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_1, configuracion_t* configuracion, int nivel_actual){
		
	if(strcmp((*configuracion).nombre_camino, ESTANDAR) == 0){
		entrada_1.fil = rand() % MAX_TERRENO_1_2-1;
		entrada_1.col = MAX_TERRENO_1_2-1;
		torre_1.fil = rand() % MAX_TERRENO_1_2-1;
		torre_1.col = 0;
		obtener_camino((*juego).nivel.camino_1, &(*juego).nivel.tope_camino_1, entrada_1, torre_1);		
	}else{
		char nivel_solicitado[MAX_NOMBRE] = "NIVEL=1";
		char camino_solicitado[MAX_NOMBRE] = "CAMINO=1";
		cargar_camino(configuracion->nombre_camino, juego->nivel.camino_1, juego->nivel.camino_2, nivel_actual, &juego->nivel.tope_camino_1, &juego->nivel.tope_camino_2, nivel_solicitado, camino_solicitado);
	}	
	mostrar_juego(*juego);
	cargar_defensores(juego, configuracion);
}

/*
 * Pre: recibe un juego en proceso y coordenadas para la entrada y torre.
 * Post: obtiene un camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_oeste(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_2, configuracion_t* configuracion,int nivel_actual){
		
	if(strcmp((*configuracion).nombre_camino, ESTANDAR) == 0){
		entrada_1.fil = rand() % MAX_TERRENO_1_2-1;
		entrada_1.col = 0;
		torre_2.fil = rand() % MAX_TERRENO_1_2-1;
		torre_2.col = MAX_TERRENO_1_2-1;
		obtener_camino((*juego).nivel.camino_1, &(*juego).nivel.tope_camino_1, entrada_1, torre_2);		
	}else{
		char nivel_solicitado[MAX_NOMBRE] = "NIVEL=2";
		char camino_solicitado[MAX_NOMBRE] = "CAMINO=1";
		cargar_camino(configuracion->nombre_camino, juego->nivel.camino_1, juego->nivel.camino_2, nivel_actual, &juego->nivel.tope_camino_1, &juego->nivel.tope_camino_2, nivel_solicitado, camino_solicitado);
	}
		mostrar_juego(*juego);
		cargar_defensores(juego, configuracion);
}

/*
 * Pre: recibe un juego en proceso y coordenadas para las dos entradas y las dos torres.
 * Post: obtiene dos camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_norte(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_1, coordenada_t entrada_2, coordenada_t torre_2, configuracion_t* configuracion){
		
	if(strcmp((*configuracion).nombre_camino, ESTANDAR) == 0){
		entrada_1.fil = 0;
		entrada_1.col = 3;
		entrada_2.fil = 0;
		entrada_2.col = 16;
		torre_1.fil = 19;
		torre_1.col = 8;
		torre_2.fil = 19;
		torre_2.col = 11;
		obtener_camino((*juego).nivel.camino_1, &(*juego).nivel.tope_camino_1, entrada_1, torre_1);
		obtener_camino((*juego).nivel.camino_2, &(*juego).nivel.tope_camino_2, entrada_2, torre_2);
	}else{
		char nivel_solicitado[MAX_NOMBRE] = "NIVEL=3";
		char camino_solicitado[MAX_NOMBRE] = "CAMINO=1";
		cargar_camino(configuracion->nombre_camino, juego->nivel.camino_1, juego->nivel.camino_2, juego->nivel_actual, &juego->nivel.tope_camino_1, &juego->nivel.tope_camino_2, nivel_solicitado, camino_solicitado);
		strcpy(camino_solicitado, "CAMINO=2");
		cargar_camino(configuracion->nombre_camino, juego->nivel.camino_1, juego->nivel.camino_2, juego->nivel_actual, &juego->nivel.tope_camino_1, &juego->nivel.tope_camino_2, nivel_solicitado, camino_solicitado);
	}
		mostrar_juego(*juego);
		cargar_defensores(juego, configuracion);
}

/*
 * Pre: recibe un juego en proceso y coordenadas para las dos entradas y las dos torres.
 * Post: obtiene dos camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_sur(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_1, coordenada_t entrada_2, coordenada_t torre_2, configuracion_t* configuracion, int nivel_actual){
		
		if(strcmp((*configuracion).nombre_camino, ESTANDAR) == 0){
			entrada_1.fil = 19;
			entrada_1.col = 5;
			entrada_2.fil = 19;
			entrada_2.col = 14;
			torre_1.fil = 0;
			torre_1.col = 5;
			torre_2.fil = 0;
			torre_2.col = 11;
			obtener_camino((*juego).nivel.camino_1, &(*juego).nivel.tope_camino_1, entrada_1, torre_1);
			obtener_camino((*juego).nivel.camino_2, &(*juego).nivel.tope_camino_2, entrada_2, torre_2);				
		}else{
			char nivel_solicitado[MAX_NOMBRE] = "NIVEL=4";
			char camino_solicitado[MAX_NOMBRE] = "CAMINO=1";
			cargar_camino(configuracion->nombre_camino, juego->nivel.camino_1, juego->nivel.camino_2, nivel_actual, &juego->nivel.tope_camino_1, &juego->nivel.tope_camino_2, nivel_solicitado, camino_solicitado);			
			strcpy(camino_solicitado, "CAMINO=2");
			cargar_camino(configuracion->nombre_camino, juego->nivel.camino_1, juego->nivel.camino_2, nivel_actual, &juego->nivel.tope_camino_1, &juego->nivel.tope_camino_2, nivel_solicitado, camino_solicitado);			
		}
		mostrar_juego(*juego);
		cargar_defensores(juego, configuracion);
}

/*
 * Pre:
 * Post:
 */
void inicializar_nivel(juego_t* juego, configuracion_t* configuracion){

	coordenada_t entrada_1;
	coordenada_t entrada_2;
	coordenada_t torre_1;
	coordenada_t torre_2;

	if((*juego).nivel_actual == NIVEL_ESTE){
		inicializar_nivel_este(juego, entrada_1, torre_1, configuracion, juego->nivel_actual);		
	}else if((*juego).nivel_actual == NIVEL_OESTE){
		inicializar_nivel_oeste(juego, entrada_1, torre_2, configuracion, juego->nivel_actual);
	}else if((*juego).nivel_actual == NIVEL_NORTE){
		inicializar_nivel_norte(juego, entrada_1, torre_1, entrada_2, torre_2, configuracion);
	}else if((*juego).nivel_actual == NIVEL_SUR){
		inicializar_nivel_sur(juego, entrada_1, torre_1, entrada_2, torre_2, configuracion, juego->nivel_actual);
	}
}

void posicionar_defensor(juego_t* juego, configuracion_t* configuracion){

	char tipo;
	char posicionar;
	int defensor_agregado;
	coordenada_t posicion;

	printf("Queres posicionar un defensor extra? S o N?:\n");
	scanf("%c", &posicionar);
	while(posicionar != 'S' && posicionar != 'N'){
		printf("Debes contestar si (S) o no (N):\n");
		scanf("%c", &posicionar);
	}

	if((*juego).nivel_actual == NIVEL_ESTE){
		if(posicionar == 'S'){
			tipo = ENANOS;
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, tipo);
		    while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, tipo);	    		
			}
			
		    (*juego).torres.enanos_extra--;
			if((*configuracion).enanos.costo_extra_1 != CONFIG_ESTANDAR){
				(*juego).torres.resistencia_torre_1 -= (*configuracion).enanos.costo_extra_1;
			}else{
				(*juego).torres.resistencia_torre_1 -= VIDA_DEF_EXTRA;
			}
		}
	}else if((*juego).nivel_actual == NIVEL_OESTE){
		if(posicionar == 'S'){
			tipo = ELFOS;
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, tipo);
		   	while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, tipo);	    		
			}
		    (*juego).torres.elfos_extra--;
		    if((*configuracion).elfos.costo_extra_2 != CONFIG_ESTANDAR){
				(*juego).torres.resistencia_torre_2 -= (*configuracion).elfos.costo_extra_2;
			}else{
				(*juego).torres.resistencia_torre_2 -= VIDA_DEF_EXTRA;
			}
		}
	}else{
		if(posicionar == 'S'){
			printf("Queres posicionar un elfo (L) o un enano (G)?:\n");
			scanf("%c", &tipo);
			while(tipo != ELFOS && tipo != ENANOS){
				printf("Los unicos buenos en esta gurrea son los elfos (L) o los enanos (G), elige un defensor valido:\n");
				scanf("%c", &tipo);
			}
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, tipo);
		    while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, tipo);	    		
			}
			if(tipo == ELFOS){
		    	(*juego).torres.elfos_extra--;
		    	if((*configuracion).elfos.costo_extra_2 != CONFIG_ESTANDAR){
					(*juego).torres.resistencia_torre_2 -= (*configuracion).elfos.costo_extra_2;
				}else{
					(*juego).torres.resistencia_torre_2 -= VIDA_DEF_EXTRA;
				}
			}
		    else{
		    	(*juego).torres.enanos_extra--;
		    	if((*configuracion).enanos.costo_extra_1 != CONFIG_ESTANDAR){
					(*juego).torres.resistencia_torre_1 -= (*configuracion).enanos.costo_extra_1;
				}else{
					(*juego).torres.resistencia_torre_1 -= VIDA_DEF_EXTRA;
				}
		    }
		}
	}
	if(posicionar == 'N'){
		return;
	}
}

/*
 * Pre: recibe un struct de configuracion.
 * Post: struct de configuracion cargado con la configuracion predeterminada.
 */
void config_estandar(configuracion_t* configuracion){
	(*configuracion).resistencia_torre_1 = CONFIG_ESTANDAR;
	(*configuracion).resistencia_torre_2 = CONFIG_ESTANDAR;
	(*configuracion).velocidad_juego = 0.5;
	(*configuracion).enanos.nivel_este = CONFIG_ESTANDAR;
	(*configuracion).enanos.nivel_norte = CONFIG_ESTANDAR;
	(*configuracion).enanos.nivel_sur = CONFIG_ESTANDAR;
	(*configuracion).enanos.cantidad_extra = CONFIG_ESTANDAR;
	(*configuracion).enanos.costo_extra_1 = CONFIG_ESTANDAR;
	(*configuracion).enanos.fallo = CONFIG_ESTANDAR;
	(*configuracion).enanos.critico = CONFIG_ESTANDAR;
	(*configuracion).elfos.nivel_oeste = CONFIG_ESTANDAR;
	(*configuracion).elfos.nivel_norte = CONFIG_ESTANDAR;
	(*configuracion).elfos.nivel_sur = CONFIG_ESTANDAR;
	(*configuracion).elfos.cantidad_extra = CONFIG_ESTANDAR;
	(*configuracion).elfos.costo_extra_2 = CONFIG_ESTANDAR;
	(*configuracion).elfos.fallo = CONFIG_ESTANDAR;
	(*configuracion).elfos.critico = CONFIG_ESTANDAR;
	strcpy((*configuracion).nombre_camino, ESTANDAR);
	strcpy((*configuracion).nombre_archivo, "/0");
}

/*
 * Pre: recibe un struct de configuracion. El archivo de configuracion debe de estar creado.
 * Post: struct de configuracion cargado con la configuracion personalizada.
 */
void config_personalizada(configuracion_t* configuracion){

	char CAMPO[MAX_NOMBRE];

	FILE* config = fopen((*configuracion).nombre_archivo, "r");
	if(!config){
		perror("Error");
		config_estandar(configuracion);
	}

	fscanf(config, "%[^'=']=%i,%i", CAMPO, &(*configuracion).resistencia_torre_1, &(*configuracion).resistencia_torre_2);
	fscanf(config, "%[^'=']=%i,0,%i,%i", CAMPO, &(*configuracion).enanos.nivel_este, &(*configuracion).enanos.nivel_norte, &(*configuracion).enanos.nivel_sur);
	fscanf(config, "%[^'=']=0,%i,%i,%i", CAMPO, &(*configuracion).elfos.nivel_oeste, &(*configuracion).elfos.nivel_norte, &(*configuracion).elfos.nivel_sur);
	fscanf(config, "%[^'=']=%i,%i", CAMPO, &(*configuracion).enanos.cantidad_extra, &(*configuracion).enanos.costo_extra_1);
	fscanf(config, "%[^'=']=%i,%i", CAMPO, &(*configuracion).elfos.cantidad_extra, &(*configuracion).elfos.costo_extra_2);
	fscanf(config, "%[^'=']=%i,%i", CAMPO, &(*configuracion).enanos.fallo, &(*configuracion).enanos.critico);
	fscanf(config, "%[^'=']=%i,%i", CAMPO, &(*configuracion).elfos.fallo, &(*configuracion).elfos.critico);
	fscanf(config, "%[^'=']=%f", CAMPO, &(*configuracion).velocidad_juego);
	fscanf(config, "%[^'=']=%s", CAMPO, (*configuracion).nombre_camino);

	fclose(config);
}

void mostrar_resultados(int estado_juego, ranking_t* ranking){

	if(estado_juego == GANADO){
		printf("FELICIDADES! Defendiste exitosamente las torres durante la Guerra del Anillo.\n");
		printf("Por favor ingresa tu nombre: ");
		scanf("%s", (*ranking).nombre_jugador);
	}else
		printf("Lo siento. Los orcos han derribado tus torres :(.\n");
}

/*
 * Pre: recibe un juego y una configuracion ya cargados.
 * Post: devuelve un entero que representara los puntos que hizo el jugador.
 */
int calcular_puntos(int puntos, juego_t juego, int orcos_muertos, configuracion_t configuracion){
	
	int enanos_inicio = (configuracion.enanos.nivel_este + configuracion.enanos.nivel_norte + configuracion.enanos.nivel_sur);
	int elfos_inicio = (configuracion.elfos.nivel_oeste + configuracion.elfos.nivel_norte + configuracion.elfos.nivel_sur);

	puntos = ((orcos_muertos*1000) / (juego.torres.resistencia_torre_1 + juego.torres.resistencia_torre_2 + enanos_inicio + elfos_inicio + configuracion.enanos.cantidad_extra + configuracion.elfos.cantidad_extra));

	return puntos;
}

void preguntar_posicion(int* fil, int* col){

	printf("FILA: \n");
	scanf("%i", fil);
	printf("COLUMNA: \n");
	scanf("%i", col);
}

void mostrar_mapa_chico(char terreno[MAX_TERRENO_1_2][MAX_TERRENO_1_2], coordenada_t camino[MAX_CAMINO], int tope_camino){


	for(int i = 0; i < MAX_TERRENO_1_2; i++){
    	for(int j = 0; j < MAX_TERRENO_1_2; j++){
    		terreno[i][j] = TIERRA;
   		}
  	}

  	for(int i = 0; i < tope_camino; i++){
    	terreno[camino[i].fil][camino[i].col] = CAMINO;
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

void mostrar_mapa_grande(char terreno[MAX_TERRENO_3_4][MAX_TERRENO_3_4], coordenada_t camino_1[MAX_CAMINO], int tope_camino_1, coordenada_t camino_2[MAX_CAMINO], int tope_camino_2){

	for(int i = 0; i < MAX_TERRENO_3_4; i++){
    	for(int j = 0; j < MAX_TERRENO_3_4; j++){
    		terreno[i][j] = TIERRA;
   		}
  	}

	for(int i = 0; i < tope_camino_1; i++){
	    terreno[camino_1[i].fil][camino_1[i].col] = CAMINO;		
	}
	if(tope_camino_2 > 0){
		for(int j = 0; j < tope_camino_2; j++){
	    	terreno[camino_2[j].fil][camino_2[j].col] = CAMINO;		
		
  		}
	}

 	for(int i = 0; i < MAX_TERRENO_3_4; i++){
    	for(int j = 0; j < MAX_TERRENO_3_4; j++){
     		if(i == camino_1[tope_camino_1-1].fil && j == camino_1[tope_camino_1-1].col){
        		terreno[i][j] = TORRE;
      		}
     		if(i == camino_1[0].fil && j == camino_1[0].col){
        		terreno[i][j] = ENTRADA;
      		}
      		if(tope_camino_2 > 0){
      			if(i == camino_2[tope_camino_2-1].fil && j == camino_2[tope_camino_2-1].col){
        			terreno[i][j] = TORRE;
      			}
     			if(i == camino_2[0].fil && j == camino_2[0].col){
        			terreno[i][j] = ENTRADA;
      			}
      		}
     	printf("%c", terreno[i][j]);
   		}   
    printf("\n");
  	}
}

/*
 * Pre: recibe coordenadas del camino ya cargadas.
 * Post: devuelve la distancia que hay entre esas coordenadas.
 */
int validar_posicion(coordenada_t camino_1[MAX_CAMINO], coordenada_t camino_2[MAX_CAMINO]){

	int x = ((*camino_1).fil - (*camino_2).fil);
	int y = ((*camino_1).col - (*camino_2).col);
	int distancia = ((x*x) + (y*y));

	return distancia;
}

/*
 * Pre: recibe structs de coordenada de cada camino y su respectivo tope.
 * Post: structs de camino cargados con las coordendas que eligio el usuario. 
 */
void crear_camino(int nivel_actual, coordenada_t camino_1[MAX_CAMINO], int* tope_camino_1, coordenada_t camino_2[MAX_CAMINO], int* tope_camino_2){
	
	int posicion = 0;
	char letra = 'O';
	char terreno_chico[MAX_TERRENO_1_2][MAX_TERRENO_1_2];
	char terreno_grande[MAX_TERRENO_3_4][MAX_TERRENO_3_4];

	printf("NIVEL: %i\n", nivel_actual);
	printf("Ingresa las coordenadas de la ENTRADA 1.\n");
	preguntar_posicion(&camino_1[0].fil, &camino_1[0].col);
	(*tope_camino_1)++;	
	system("clear");

	while((*tope_camino_1) < MAX_CAMINO && letra != 'F'){
		posicion++;
		if(nivel_actual == NIVEL_ESTE || nivel_actual == NIVEL_OESTE){
			mostrar_mapa_chico(terreno_chico, camino_1, (*tope_camino_1));
		}else{
			mostrar_mapa_grande(terreno_grande, camino_1, (*tope_camino_1), camino_2, (*tope_camino_2));
		}
		printf("Ingresa las coordenadas del camino 1.\n");
		preguntar_posicion(&camino_1[posicion].fil, &camino_1[posicion].col);
		int distancia = validar_posicion(&camino_1[posicion], &camino_1[posicion-1]);
		while(distancia > 2){
			printf("Error! Elige unas coordenadas validas.\n");
			preguntar_posicion(&camino_1[(*tope_camino_1)].fil, &camino_1[(*tope_camino_1)].col);
			distancia = validar_posicion(&camino_1[(*tope_camino_1)], &camino_1[(*tope_camino_1)-1]);
		}
		(*tope_camino_1)++;
		if((*tope_camino_1) > 5){
			printf("Si desea terminar el camino, ingrese 'F': ");
			scanf(" %c", &letra);
			if(nivel_actual == NIVEL_ESTE || nivel_actual == NIVEL_OESTE){
				mostrar_mapa_chico(terreno_chico, camino_1, (*tope_camino_1));
			}else{
				mostrar_mapa_grande(terreno_grande, camino_1, (*tope_camino_1), camino_2, (*tope_camino_2));
			}		
			system("clear");
		}	
		system("clear");	
	}
	printf("Camino 1 creado.\n");
	system("clear");

	if(nivel_actual == NIVEL_NORTE || nivel_actual == NIVEL_SUR){
		printf("Ingresa las coordenadas de la ENTRADA 2.\n");
		preguntar_posicion(&camino_2[0].fil, &camino_2[0].col);
		(*tope_camino_2)++;	
		letra = 'O';
		posicion = 0;
		while((*tope_camino_2) < MAX_CAMINO && letra != 'F'){
			posicion++;
			mostrar_mapa_grande(terreno_grande, camino_1, (*tope_camino_1), camino_2, (*tope_camino_2));
			printf("Ingresa las coordenadas del camino 2.\n");
			preguntar_posicion(&camino_2[posicion].fil, &camino_2[posicion].col);
			int distancia = validar_posicion(&camino_2[posicion], &camino_2[posicion-1]);
			while(distancia > 2){
				printf("Error! Elige unas coordenadas validas.\n");
				preguntar_posicion(&camino_2[(*tope_camino_1)].fil, &camino_2[(*tope_camino_1)].col);
				distancia = validar_posicion(&camino_2[(*tope_camino_1)], &camino_2[(*tope_camino_1)-1]);
			}
			(*tope_camino_2)++;
			if((*tope_camino_2) > 5){
				printf("Si desea terminar el camino, ingrese 'F': ");
				scanf(" %c", &letra);
				mostrar_mapa_grande(terreno_grande, camino_1, (*tope_camino_1), camino_2, (*tope_camino_2));
				system("clear");				
			}
			system("clear");		
		}
	printf("Camino 2 creado.\n");
	system("clear");	
	}
}

/*
 * Pre: structs de camino cargados correctamente. El nivel actual debe de ser el primero.
 * Post: crea un archivo de texto en donde se van a escribir las coordenadas de cada camino dependiendo el nivel.
 */
void crear_archivo_camino(char nombre_camino[MAX_CAMINO], int nivel_actual, coordenada_t camino_1[MAX_CAMINO], int tope_camino_1){

	FILE* camino = fopen(nombre_camino, "a");
	if(!camino){
		perror("Error");
		return;
	}
	int i = 0;

	fprintf(camino, "%s=%i\n%s=%i\n", "NIVEL", nivel_actual, "CAMINO", 1);
	while(i < tope_camino_1){
		fprintf(camino, "%i;%i\n", camino_1[i].fil, camino_1[i].col);
		i++;
	}
	fclose(camino);
}

/*
 * Pre: structs de camino cargados correctamente.
 * Post: escribe un archivo de texto las coordenadas de cada camino dependiendo el nivel.
 */
void guardar_archivo_camino(char nombre_camino[MAX_CAMINO], int nivel_actual, coordenada_t camino_1[MAX_CAMINO], int tope_camino_1, coordenada_t camino_2[MAX_CAMINO], int tope_camino_2){

	FILE* caminos = fopen(nombre_camino, "w");
	if(!caminos){
		perror("Error");
		return;
	}

	int i =0;
	int camino = 1;

	if(nivel_actual <= 2){
		fprintf(caminos, "%s=%i\n%s=%i\n", "NIVEL", nivel_actual, "CAMINO", camino);
		while(i < tope_camino_1){
			fprintf(caminos, "%i;%i\n", camino_1[i].fil, camino_1[i].col);
			i++;
		}
	}else{
		fprintf(caminos, "%s=%i\n", "NIVEL", nivel_actual);
		fprintf(caminos, "%s=%i\n", "CAMINO", camino);
		while(i < tope_camino_1){
			fprintf(caminos, "%i;%i\n", camino_1[i].fil, camino_1[i].col);
			i++;
		}
		i = 0;
		camino++;
		fprintf(caminos, "%s=%i\n", "CAMINO", camino);
		while(i < tope_camino_2){
			fprintf(caminos, "%i;%i\n", camino_2[i].fil, camino_2[i].col);
			i++;
		}
	}
	fclose(caminos);
}

/*
 * Pre: struct de coordenadas de cada camino cargados.
 * Post: archivo de texto con las coordenadas de cada camino creado.
 */
void formar_camino(char nombre_camino[MAX_CAMINO], int nivel_actual, coordenada_t camino_1[MAX_CAMINO], int* tope_camino_1, coordenada_t camino_2[MAX_CAMINO], int* tope_camino_2){
	
	nivel_actual = NIVEL_ESTE;

	while(nivel_actual < 5){
		(*tope_camino_1) = 0;
		(*tope_camino_2) = 0;
		crear_camino(nivel_actual, camino_1, &(*tope_camino_1), camino_2, &(*tope_camino_2));
		if(nivel_actual == NIVEL_ESTE){
			crear_archivo_camino(nombre_camino, nivel_actual, camino_1, (*tope_camino_1));
		}else{
			guardar_archivo_camino(nombre_camino, nivel_actual, camino_1, (*tope_camino_1), camino_2, (*tope_camino_2));
		}
		nivel_actual++;
	}
}

/*
 * Pre: el archivo binario con la partida guardada debe de estar creado.
 * Post: 
 */
void ver_partida(float velocidad, char nombre_partida[MAX_NOMBRE]){

	juego_t juego_repe;

	FILE* repe = fopen(nombre_partida, "r");
	if(!repe){
		perror("Error");
		return;
	}
	
	while(!feof(repe)){		

		fread(&juego_repe.nivel,sizeof(nivel_t),1,repe);
		fread(&juego_repe.torres,sizeof(torres_t),1,repe);
		fread(&juego_repe.nivel_actual,sizeof(int),1,repe);
		fread(&juego_repe.critico_legolas,sizeof(int),1,repe);
		fread(&juego_repe.critico_gimli,sizeof(int),1,repe);
		fread(&juego_repe.fallo_legolas,sizeof(int),1,repe);
		fread(&juego_repe.fallo_gimli,sizeof(int),1,repe);

		mostrar_juego(juego_repe);
		detener_el_tiempo(velocidad);
		system("clear");
	}

	fclose(repe);	
}

int main(int argc, char* argv[]){

	srand((unsigned)time(NULL));

	juego_t juego;
	configuracion_t configuracion;
	ranking_t ranking;

	coordenada_t camino_1[MAX_CAMINO];
	int tope_camino_1;
	coordenada_t camino_2[MAX_CAMINO];
	int tope_camino_2;

	char animo_legolas;
	char animo_gimli;

	int orcos_muertos = 0;
	int puntos = 0;
	int viento = 0;
	int humedad = 0;
	int estado_del_juego = JUGANDO;
	int estado_del_nivel = JUGANDO;

	float segundos;	

	char* token;
	char* token_2;
	char* token_3;

	char nombre_partida[MAX_NOMBRE];
	char nombre_grabacion[MAX_NOMBRE];

	bool esta_grabando = false;

	FILE* repe;

	if(argc > 1){
		if(strcmp(argv[1], "crear_camino") == 0){
			if(argc < 3){
				printf("Comando no valido.\n");
				return -1;
			}else{
				strcpy(configuracion.nombre_camino, argv[2]);
				formar_camino(configuracion.nombre_camino, juego.nivel_actual, camino_1, &tope_camino_1, camino_2, &tope_camino_2);
				return 0;
			}
		}
		if(strcmp(argv[1], "crear_configuracion") == 0){
			if(argc < 3){
				printf("Comando no valido.\n");
				return -1;
			}else{
				strcpy(configuracion.nombre_archivo, argv[2]);
				configurar_juego(&configuracion);
				return 0;
			}			
		}		
		if(strcmp(argv[1], "poneme_la_repe") == 0){
			if(argc < 3){
				printf("Comando no valido.\n");
				return -1;
			}else if(argc < 4){
				float velocidad = 1;
				token_2 = strtok(argv[2], "=");
				if(strcmp(token_2, "grabacion") == 0){
					strcpy(nombre_partida, strtok(NULL, "="));
					ver_partida(velocidad, nombre_partida);					
				}
				return 0;
			}
		}
		if(strcmp(argv[1], "ranking") == 0){
			if(argc < 3){				
				strcpy(ranking.nombre_archivo, "ranking_.csv");
				mostrar_ranking(ranking);
			}else if(argc < 4){
				token = strtok(argv[2], "=");
				if(strcmp(token, "config") == 0){
					strcpy(ranking.nombre_archivo, "ranking_");
					strcat(ranking.nombre_archivo, strtok(NULL, "="));					
				}
				mostrar_ranking(ranking);
			}else if(argc < 5){
				printf("Error. Ingresaste demasiados comandos.\n");
			}
			return 0;
		}
		
	}
	if(argc > 1){
		if(strcmp(argv[1], "jugar") == 0){
			if(argc < 3){
				config_estandar(&configuracion);				
			}else if(argc < 4){
				token = strtok(argv[2], "=");
				if(strcmp(token, "config") == 0){
					strcpy(configuracion.nombre_archivo, strtok(NULL, "="));
					config_personalizada(&configuracion);
				}
			}else if(argc < 5){
				token = strtok(argv[2], "=");
				if(strcmp(token, "config") == 0){
					strcpy(configuracion.nombre_archivo, strtok(NULL, "="));
					config_personalizada(&configuracion);
				}
				token_3 = strtok(argv[3], "=");
				if(strcmp(token_3, "grabacion") == 0){
					esta_grabando = true;
					strcpy(nombre_grabacion, strtok(NULL, "="));
				}
			}
		}		
	}

	if(configuracion.enanos.critico == CONFIG_ESTANDAR || configuracion.enanos.fallo == CONFIG_ESTANDAR ||configuracion.elfos.critico == CONFIG_ESTANDAR || configuracion.elfos.fallo == CONFIG_ESTANDAR){
		animos(&viento, &humedad, &animo_legolas, &animo_gimli);
	}


	inicializar_juego(&juego ,viento, humedad, animo_legolas, animo_gimli, &configuracion); 

	juego.nivel_actual = NIVEL_ESTE; 

	inicializar_nivel(&juego, &configuracion);

	if(esta_grabando == true){
		repe = fopen(nombre_grabacion, "w");
		if(!repe){
			perror("Error");
			esta_grabando = false;		
		}		
	}

	while(estado_del_juego == JUGANDO){

		if(estado_del_nivel == GANADO && estado_del_juego == JUGANDO){ 
			juego.nivel_actual++;
			juego.nivel.tope_defensores = 0;
			juego.nivel.tope_enemigos = 0;
			juego.nivel.tope_camino_1 = 0;
			juego.nivel.tope_camino_2 = 0;
			inicializar_nivel(&juego, &configuracion); 
		}

		jugar_turno(&juego);

		if(juego.nivel_actual == NIVEL_ESTE){
			if(juego.nivel.tope_enemigos%25 == 0 && juego.torres.enanos_extra > 0 && juego.torres.elfos_extra > 0 && juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)
				posicionar_defensor(&juego, &configuracion);			
		}else if(juego.nivel_actual == NIVEL_OESTE || juego.nivel_actual == NIVEL_NORTE || juego.nivel_actual == NIVEL_SUR){
			if(juego.nivel.tope_enemigos%50 == 0 && juego.torres.enanos_extra > 0 && juego.torres.elfos_extra > 0 && juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)
				posicionar_defensor(&juego, &configuracion);
		}
		
		mostrar_juego(juego);

		segundos = configuracion.velocidad_juego;

		detener_el_tiempo(segundos);

		if(esta_grabando == true){

			fwrite(&juego.nivel, sizeof(nivel_t),1,repe);
			fwrite(&juego.torres, sizeof(torres_t),1,repe);
			fwrite(&juego.nivel_actual, sizeof(int),1,repe);
			fwrite(&juego.critico_legolas, sizeof(int),1,repe);
			fwrite(&juego.critico_gimli, sizeof(int),1,repe);
			fwrite(&juego.fallo_legolas, sizeof(int),1,repe);
			fwrite(&juego.critico_gimli, sizeof(int),1,repe);
		}

		estado_del_juego = estado_juego(juego);

		estado_del_nivel = estado_nivel(juego.nivel);


		for(int i = 0; i < juego.nivel.tope_enemigos; i++){
			if(juego.nivel.enemigos[i].vida <= 0){
				orcos_muertos++;
			}
		}
	}

	if(esta_grabando == true){
		fclose(repe);
	}
	
	if(estado_del_juego == GANADO){
		ranking.puntos_jugador = calcular_puntos(puntos, juego, orcos_muertos, configuracion);
	}

	system("clear");

	mostrar_resultados(estado_del_juego, &ranking);

	escribir_ranking(configuracion, ranking); 

	return 0;
}