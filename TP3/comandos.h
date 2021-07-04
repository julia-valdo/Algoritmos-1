#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#include <stdio.h>
#include <stdlib.h>

#define MAX_NOMBRE 20

typedef struct aliados{
	int nivel_este;
	int nivel_oeste;
	int nivel_norte;
	int nivel_sur;
	int cantidad_extra;
	int costo_extra_1;
	int costo_extra_2;
	int fallo;
	int critico;
}aliados_t;

typedef struct configuracion{
	aliados_t aliados;
	int resistencia_torre_1;
	int resistencia_torre_2;	
	float velocidad_juego;	
	char caminos[MAX_NOMBRE];
	char nombre_archivo[MAX_NOMBRE];
}configuracion_t;

/*
 *
 */
//void mostrar_ranking();

/*
 *
 */
//void crear_caminos();

/*
 *
 */
void configurar_juego(configuracion_t* configuracion, aliados_t* enanos, aliados_t* elfos);

/*
 *
 */
//void ver_partida();

#endif /* __COMANDOS_H__ */