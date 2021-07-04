#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "animos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include "comandos.h"

const int NIVEL_ESTE = 1;
const int NIVEL_OESTE = 2;
const int NIVEL_NORTE = 3;
const int NIVEL_SUR = 4;
const int DEFENSORES_ESTE = 5;
const int DEFENSORES_OESTE = 5;
const int DEFENSORES_NORTE = 6;
const int DEFENSORES_SUR = 8;
const int MAX_TERRENO_1_2 = 15;
const int MAX_TERRENO_3_4 = 20;
const int VIDA_DEF_EXTRA = 50;
static const int JUGANDO = 0;
static const int GANADO = 1;
static const char ELFOS = 'L';
static const char ENANOS = 'G';
static const int VALIDO = 0;
static const int INVALIDO = -1;


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
void cargar_defensores(juego_t* juego){

	coordenada_t posicion;
	int defensor_agregado = VALIDO;

	if((*juego).nivel_actual == NIVEL_ESTE){

		for(int i = 0; i < DEFENSORES_ESTE; i++){
			(*juego).nivel.defensores[i].tipo = ENANOS;
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
		}
	}else if((*juego).nivel_actual == NIVEL_OESTE){

		for(int i = 0; i < DEFENSORES_OESTE; i++){
			(*juego).nivel.defensores[i].tipo = ELFOS;
			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			
		}
	}else if((*juego).nivel_actual == NIVEL_NORTE){
				
		for(int i = 0; i < DEFENSORES_NORTE; i++){

			if(i < 3){
				(*juego).nivel.defensores[i].tipo = ENANOS;
			}else
				(*juego).nivel.defensores[i].tipo = ELFOS;

			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			
		}	
	}else if((*juego).nivel_actual == NIVEL_SUR){
		
		for(int i = 0; i < DEFENSORES_SUR; i++){

			if(i < 4){
				(*juego).nivel.defensores[i].tipo = ENANOS;
			}else
				(*juego).nivel.defensores[i].tipo = ELFOS;

			pedir_posicion(&posicion.fil, &posicion.col);
			defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);
			while(defensor_agregado == INVALIDO){
				printf("Algo salio mal al posicionar tu defensor, elige otras coordenadas.\n");
				pedir_posicion(&posicion.fil, &posicion.col);
				defensor_agregado = agregar_defensor(&(*juego).nivel, posicion, (*juego).nivel.defensores[i].tipo);	    		
			}
			
		}
	}
}

/*
 * Pre: recibe un juego en proceso y coordenadas para la entrada y torre.
 * Post: obtiene un camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_este(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_1){
		entrada_1.fil = rand() % MAX_TERRENO_1_2-1;
		entrada_1.col = MAX_TERRENO_1_2-1;
		torre_1.fil = rand() % MAX_TERRENO_1_2-1;
		torre_1.col = 0;
		obtener_camino((*juego).nivel.camino_1, &(*juego).nivel.tope_camino_1, entrada_1, torre_1);
		mostrar_juego(*juego);
		cargar_defensores(juego);
}

/*
 * Pre: recibe un juego en proceso y coordenadas para la entrada y torre.
 * Post: obtiene un camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_oeste(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_2){
		entrada_1.fil = rand() % MAX_TERRENO_1_2-1;
		entrada_1.col = 0;
		torre_2.fil = rand() % MAX_TERRENO_1_2-1;
		torre_2.col = MAX_TERRENO_1_2-1;
		obtener_camino((*juego).nivel.camino_1, &(*juego).nivel.tope_camino_1, entrada_1, torre_2);
		mostrar_juego(*juego);
		cargar_defensores(juego);
}

/*
 * Pre: recibe un juego en proceso y coordenadas para las dos entradas y las dos torres.
 * Post: obtiene dos camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_norte(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_1, coordenada_t entrada_2, coordenada_t torre_2){
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
		mostrar_juego(*juego);
		cargar_defensores(juego);
}

/*
 * Pre: recibe un juego en proceso y coordenadas para las dos entradas y las dos torres.
 * Post: obtiene dos camino y carga los defensores de ese nivel.
 */
void inicializar_nivel_sur(juego_t* juego, coordenada_t entrada_1, coordenada_t torre_1, coordenada_t entrada_2, coordenada_t torre_2){
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
		mostrar_juego(*juego);
		cargar_defensores(juego);
}

/*
 * Pre:
 * Post:
 */
void inicializar_nivel(juego_t* juego){

	coordenada_t entrada_1;
	coordenada_t entrada_2;
	coordenada_t torre_1;
	coordenada_t torre_2;	
		
	if((*juego).nivel_actual == NIVEL_ESTE){
		inicializar_nivel_este(juego, entrada_1, torre_1);
	}else if((*juego).nivel_actual == NIVEL_OESTE){
		inicializar_nivel_oeste(juego, entrada_1, torre_2);
	}else if((*juego).nivel_actual == NIVEL_NORTE){
		inicializar_nivel_norte(juego, entrada_1, torre_1, entrada_2, torre_2);
	}else if((*juego).nivel_actual == NIVEL_SUR){
		inicializar_nivel_sur(juego, entrada_1, torre_1, entrada_2, torre_2);
	}
}

/*
 * Pre:
 * Post:
 */
void posicionar_defensor(juego_t* juego){

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
			(*juego).torres.resistencia_torre_1 -= VIDA_DEF_EXTRA;
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
		    (*juego).torres.resistencia_torre_2 -= VIDA_DEF_EXTRA;
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
		    	(*juego).torres.resistencia_torre_2 -= VIDA_DEF_EXTRA;
			}
		    else{
		    	(*juego).torres.enanos_extra--;
		    	(*juego).torres.resistencia_torre_1 -= VIDA_DEF_EXTRA;
		    }

		}
	}
	if(posicionar == 'N'){
		return;
	}
}

void mostrar_resultados(int estado_juego, int estado_nivel){

	if(estado_juego == GANADO){
		printf("FELICIDADES! Defendiste exitosamente las torres durante la Guerra del Anillo\n");
	}else
		printf("Lo siento. Los orcos han derribado tus torres :(.\n");
}

int main(int argc, char* argv[]){

	srand((unsigned)time(NULL));

	juego_t juego;
	configuracion_t configuracion;
	aliados_t enanos;
	aliados_t elfos;

	char animo_legolas;
	char animo_gimli;
	int viento = 0;
	int humedad = 0;
	int estado_del_juego = JUGANDO;
	int estado_del_nivel = JUGANDO;
	float segundos = 0.5;	

	animos(&viento, &humedad, &animo_legolas, &animo_gimli);

	if(strcmp(argv[1], "crear_configuracion") == 0){
		if(argc < 2){
			printf("Comando no valido.\n");
			return -1;
		}else{
			strcpy(configuracion.nombre_archivo, argv[2]);
			configurar_juego(&configuracion, &enanos, &elfos);
		}			
	}

	inicializar_juego(&juego ,viento, humedad, animo_legolas, animo_gimli); 

	juego.nivel_actual = NIVEL_ESTE; 

	inicializar_nivel(&juego); 

	while(estado_del_juego == JUGANDO){

		if(estado_del_nivel == GANADO && estado_del_juego == JUGANDO){ 
			juego.nivel_actual++;
			juego.nivel.tope_defensores = 0;
			juego.nivel.tope_enemigos = 0;
			inicializar_nivel(&juego); 
		}

		jugar_turno(&juego);

		if(juego.nivel_actual == NIVEL_ESTE){
			if(juego.nivel.tope_enemigos%25 == 0 && juego.torres.enanos_extra > 0 && juego.torres.elfos_extra > 0 && juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)
				posicionar_defensor(&juego);			
		}else if(juego.nivel_actual == NIVEL_OESTE || juego.nivel_actual == NIVEL_NORTE || juego.nivel_actual == NIVEL_SUR){
			if(juego.nivel.tope_enemigos%50 == 0 && juego.torres.enanos_extra > 0 && juego.torres.elfos_extra > 0 && juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)
				posicionar_defensor(&juego);
		}
		
		mostrar_juego(juego);

		detener_el_tiempo(segundos);

		estado_del_juego = estado_juego(juego);

		estado_del_nivel = estado_nivel(juego.nivel);
	}

	system("clear");

	mostrar_resultados(estado_del_juego, estado_del_nivel); 

	return 0;
}