#include <stdio.h>
#include <string.h>
#include "comandos.h"

#define MAX_NOMBRE 50
#define PUNTOS_INVALIDOS -1000
#define NOMBRE_INVALIDO "zzzzzzzzzzzzzzz"

const char CAMINO_ESTANDAR = -1;

void preguntar_torres(configuracion_t* configuracion){

	printf("RESISTENCIA TORRE 1: ");
	scanf("%i", &(*configuracion).resistencia_torre_1);

	printf("RESISTENCIA TORRE 2: ");
	scanf("%i", &(*configuracion).resistencia_torre_2);

	printf("VELOCIDAD DEL JUEGO: ");
	scanf("%f", &(*configuracion).velocidad_juego);

	printf("INGRESA LA RUTA DEL CAMINO QUE DESEAS UTILIZAR. SI DESEAS USAR UN CAMINO ALEATORIO INGRESA -1: ");
	scanf("%s", (*configuracion).nombre_camino);		
}

void preguntar_enanos(enanos_t* enanos){

	printf("ENANOS AL INICIAR NIVEL ESTE: ");
	scanf("%i", &(*enanos).nivel_este);

	printf("ENANOS AL INICIAR NIVEL NORTE: ");
	scanf("%i", &(*enanos).nivel_norte);

	printf("ENANOS AL INICIAR NIVEL SUR: ");
	scanf("%i", &(*enanos).nivel_sur);

	printf("CANTIDAD DE ENANOS EXTRA: ");
	scanf("%i", &(*enanos).cantidad_extra);

	printf("COSTO DE ENANOS EXTRA A LA TORRE 1: ");
	scanf("%i", &(*enanos).costo_extra_1);

	printf("FALLO ENANOS: ");
	scanf("%i", &(*enanos).fallo);

	printf("CRITICO ENANOS: ");
	scanf("%i", &(*enanos).critico);
}

void preguntar_elfos(elfos_t* elfos){

	printf("ELFOS AL INICIAR NIVEL OESTE: ");
	scanf("%i", &(*elfos).nivel_oeste);

	printf("ELFOS AL INICIAR NIVEL NORTE: ");
	scanf("%i", &(*elfos).nivel_norte);

	printf("ELFOS AL INICIAR NIVEL SUR: ");
	scanf("%i", &(*elfos).nivel_sur);

	printf("CANTIDAD DE ELFOS EXTRA: ");
	scanf("%i", &(*elfos).cantidad_extra);

	printf("COSTO DE ELFOS EXTRA A LA TORRE 2: ");
	scanf("%i", &(*elfos).costo_extra_2);

	printf("FALLO ELFOS: ");
	scanf("%i", &(*elfos).fallo);

	printf("CRITICO ELFOS: ");
	scanf("%i", &(*elfos).critico);
}

/*
 * Pre: 
 * Post: struct de configuracion cargado.
 */
void preguntar_configuracion(configuracion_t* configuracion, enanos_t* enanos, elfos_t* elfos){

	printf("Si desea dejar la configuracion estandar de alguna de las siguientes caracteristicas, ingrese -1.\n");
	
	preguntar_torres(&(*configuracion));

	preguntar_enanos(&(*enanos));

	preguntar_elfos(&(*elfos));

}

void configurar_juego(configuracion_t* configuracion){

	char campo[MAX_NOMBRE];

	FILE* config = fopen((*configuracion).nombre_archivo, "w");
	if(!config){
		perror("Error");
		return;
	}

	preguntar_configuracion(&(*configuracion), &(*configuracion).enanos, &(*configuracion).elfos);

	strcpy(campo, "RESISTENCIA_TORRES");
	fprintf(config, "%s=%i,%i\n", campo, (*configuracion).resistencia_torre_1, (*configuracion).resistencia_torre_2);

	strcpy(campo, "ENANOS_INICIO");
	fprintf(config, "%s=%i,0,%i,%i\n", campo, (*configuracion).enanos.nivel_este, (*configuracion).enanos.nivel_norte, (*configuracion).enanos.nivel_sur);

	strcpy(campo, "ELFOS_INICIO");
	fprintf(config, "%s=0,%i,%i,%i\n", campo, (*configuracion).elfos.nivel_oeste, (*configuracion).elfos.nivel_norte, (*configuracion).elfos.nivel_sur);

	strcpy(campo, "ENANOS_EXTRA");
	fprintf(config, "%s=%i,%i,0\n", campo, (*configuracion).enanos.cantidad_extra, (*configuracion).enanos.costo_extra_1);

	strcpy(campo, "ELFOS_EXTRA");
	fprintf(config, "%s=%i,0,%i\n", campo, (*configuracion).elfos.cantidad_extra, (*configuracion).elfos.costo_extra_2);

	strcpy(campo, "ENANOS_ANIMO");
	fprintf(config, "%s=%i,%i\n", campo, (*configuracion).enanos.critico, (*configuracion).enanos.fallo);

	strcpy(campo, "ELFOS_ANIMO");
	fprintf(config, "%s=%i,%i\n", campo, (*configuracion).elfos.critico, (*configuracion).elfos.fallo);

	strcpy(campo, "VELOCIDAD");
	fprintf(config, "%s=%f\n", campo, (*configuracion).velocidad_juego);

	strcpy(campo, "CAMINOS");
	fprintf(config, "%s=%s\n", campo, (*configuracion).nombre_camino);

	fclose(config);
}

/*
 * Pre: el archivo de ranking no debe de estar creado.
 * Post: 
 */
void incializar_ranking(ranking_t ranking){
	
	FILE* podio = fopen(ranking.nombre_archivo, "w");
	if(!podio){
		perror("Error");
		return;
	}
	fprintf(podio, "%s;%i\n", ranking.nombre_jugador, ranking.puntos_jugador);
	fclose(podio);
}

void escribir_ranking(configuracion_t configuracion, ranking_t ranking){

	ranking_t ranking_viejo;

	char* token;

	token = strtok(configuracion.nombre_archivo, ".");

	strcpy(configuracion.nombre_archivo, token);

	strcpy(ranking.nombre_archivo, "ranking_");
	if(strcmp(configuracion.nombre_archivo, "/0") != 0){
		strcat(ranking.nombre_archivo, configuracion.nombre_archivo);
	}
	strcat(ranking.nombre_archivo, ".csv");

	FILE* podio = fopen(ranking.nombre_archivo, "r");
	if(!podio){
		incializar_ranking(ranking);
		return;
	}

	FILE* podio_nuevo = fopen("podio_nuevo", "w");
	if(!podio_nuevo){
		fclose(podio);
		perror("Error");
		return;
	}

	int leidos = fscanf(podio, "%[^;];%i\n", ranking_viejo.nombre_jugador, &ranking_viejo.puntos_jugador);
	while(leidos == 2){
		if(ranking.puntos_jugador < ranking_viejo.puntos_jugador){
			fprintf(podio_nuevo, "%s;%i\n", ranking_viejo.nombre_jugador, ranking_viejo.puntos_jugador);			
			leidos = fscanf(podio, "%[^;];%i\n", ranking_viejo.nombre_jugador, &ranking_viejo.puntos_jugador);
		}else if(ranking.puntos_jugador > ranking_viejo.puntos_jugador){
			fprintf(podio_nuevo, "%s;%i\n", ranking.nombre_jugador, ranking.puntos_jugador);
			strcpy(ranking.nombre_jugador, NOMBRE_INVALIDO);
			ranking.puntos_jugador = PUNTOS_INVALIDOS;				
		}else{
			int cmp = strcmp(ranking.nombre_jugador, ranking_viejo.nombre_jugador);
			if(cmp < 0){
				fprintf(podio_nuevo, "%s;%i\n", ranking_viejo.nombre_jugador, ranking_viejo.puntos_jugador);
				leidos = fscanf(podio, "%[^;];%i\n", ranking_viejo.nombre_jugador, &ranking_viejo.puntos_jugador);
			}else if(cmp > 0){
				fprintf(podio_nuevo, "%s;%i\n", ranking.nombre_jugador, ranking.puntos_jugador);
				strcpy(ranking.nombre_jugador, NOMBRE_INVALIDO);
				ranking.puntos_jugador = PUNTOS_INVALIDOS;
			}else{
				fprintf(podio_nuevo, "%s;%i\n", ranking.nombre_jugador, ranking.puntos_jugador);
				strcpy(ranking.nombre_jugador, NOMBRE_INVALIDO);
				ranking.puntos_jugador = PUNTOS_INVALIDOS;
			}
		}
	}

	fclose(podio);	
	fclose(podio_nuevo);
	rename("podio_nuevo", ranking.nombre_archivo);
}

void mostrar_ranking(ranking_t ranking){	

	FILE* podio = fopen(ranking.nombre_archivo, "r");
	if(!podio){
		perror("Error");
		return;
	}
				
	int leidos = fscanf(podio, "%[^;];%i", ranking.nombre_jugador, &(ranking).puntos_jugador);
	while(!feof(podio) && leidos != EOF){
		printf("%s;%i", ranking.nombre_jugador, (ranking).puntos_jugador);
		leidos = fscanf(podio, "%[^;];%i", ranking.nombre_jugador, &(ranking).puntos_jugador);
	}

	fclose(podio);
}

