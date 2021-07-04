#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#include <stdio.h>
#include <stdlib.h>

#define MAX_NOMBRE 50

typedef struct enanos{
	int nivel_este;
	int nivel_norte;
	int nivel_sur;
	int cantidad_extra;
	int costo_extra_1;
	int costo_extra_2;
	int fallo;
	int critico;
}enanos_t;

typedef struct elfos{
	int nivel_oeste;
	int nivel_norte;
	int nivel_sur;
	int cantidad_extra;
	int costo_extra_1;
	int costo_extra_2;
	int fallo;
	int critico;
}elfos_t;

typedef struct configuracion{
	enanos_t enanos;
	elfos_t elfos;
	int resistencia_torre_1;
	int resistencia_torre_2;	
	float velocidad_juego;	
	char nombre_camino[MAX_NOMBRE];
	char nombre_archivo[MAX_NOMBRE];
}configuracion_t;

typedef struct ranking{
	char nombre_archivo[MAX_NOMBRE];
	char nombre_jugador[MAX_NOMBRE];
	int puntos_jugador;
}ranking_t;

/*
 * Pre: recibe una configuracion y un ranking cargados.
 * Post: se crea un archivo de texto ordenado.
 */

void escribir_ranking(configuracion_t configuracion, ranking_t ranking);

/*
 * Pre: debe de existir un archivo de ranking.
 * Post: 
 */
void mostrar_ranking(ranking_t ranking);

/*
 * Pre: luego de preguntarle al usuario la configuracion, el struct de configuracion debe de estar cargado.
 * Post: se crea una archivo de texto con la configuracion personalizada del jugador.
 */
void configurar_juego(configuracion_t* configuracion);

#endif /* __COMANDOS_H__ */