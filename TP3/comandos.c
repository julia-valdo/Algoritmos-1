#include <stdio.h>
#include "comandos.h"
#include <string.h>

#define MAX_NOMBRE 20
const char CAMINO_ESTANDAR = -1;

void preguntar_torres(configuracion_t* configuracion){

	printf("RESISTENCIA TORRE 1:");
	scanf("%i", &(*configuracion).resistencia_torre_1);

	printf("RESISTENCIA TORRE 2:");
	scanf("%i", &(*configuracion).resistencia_torre_2);

	printf("VELOCIDAD DEL JUEGO:");
	scanf("%f", &(*configuracion).velocidad_juego);

	printf("INGRESA LA RUTA DEL CAMINO QUE DESEAS UTILIZAR.\n--> SI DESEAS CREAR UN CAMINO EJECUTA EL PROGRAMA CON EL COMANDO 'crear_camino'.\n--> SI DESEAS USAR UN CAMINO ALEATORIO INGRESA -1: ");
	scanf("%s", (*configuracion).caminos);		
}

void preguntar_enanos(aliados_t* enanos){

	printf("ENANOS AL INICIAR NIVEL ESTE:");
	scanf("%i", &(*enanos).nivel_este);

	printf("ENANOS AL INICIAR NIVEL OESTE:");
	scanf("%i", &(*enanos).nivel_oeste);

	printf("ENANOS AL INICIAR NIVEL NORTE:");
	scanf("%i", &(*enanos).nivel_norte);

	printf("ENANOS AL INICIAR NIVEL SUR:");
	scanf("%i", &(*enanos).nivel_sur);

	printf("CANTIDAD DE ENANOS EXTRA:");
	scanf("%i", &(*enanos).cantidad_extra);

	printf("COSTO DE ENANOS EXTRA A LA TORRE 1:");
	scanf("%i", &(*enanos).costo_extra_1);

	printf("COSTO DE ENANOS EXTRA A LA TORRE 2:");
	scanf("%i", &(*enanos).costo_extra_2);

	printf("FALLO ENANOS:");
	scanf("%i", &(*enanos).fallo);

	printf("CRITICO ENANOS:");
	scanf("%i", &(*enanos).critico);
}

void preguntar_elfos(aliados_t* elfos){

	printf("ELFOS AL INICIAR NIVEL ESTE:");
	scanf("%i", &(*elfos).nivel_este);

	printf("ELFOS AL INICIAR NIVEL OESTE:");
	scanf("%i", &(*elfos).nivel_oeste);

	printf("ELFOS AL INICIAR NIVEL NORTE:");
	scanf("%i", &(*elfos).nivel_norte);

	printf("ELFOS AL INICIAR NIVEL SUR:");
	scanf("%i", &(*elfos).nivel_sur);

	printf("CANTIDAD DE ELFOS EXTRA:");
	scanf("%i", &(*elfos).cantidad_extra);

	printf("COSTO DE ELFOS EXTRA A LA TORRE 1:");
	scanf("%i", &(*elfos).costo_extra_1);

	printf("COSTO DE ELFOS EXTRA A LA TORRE 2:");
	scanf("%i", &(*elfos).costo_extra_2);

	printf("FALLO ELFOS:");
	scanf("%i", &(*elfos).fallo);

	printf("CRITICO ELFOS:");
	scanf("%i", &(*elfos).critico);
}

void preguntar_configuracion(configuracion_t* configuracion, aliados_t* enanos, aliados_t* elfos){

	printf("Si desea dejar la configuracion estandar de alguna de las siguientes caracteristicas, ingrese -1.\n");
	
	preguntar_torres(&(*configuracion));

	preguntar_enanos(&(*enanos));

	preguntar_elfos(&(*elfos));

}

void configurar_juego(configuracion_t* configuracion, aliados_t* enanos, aliados_t* elfos){

	char CAMPO[MAX_NOMBRE];

	FILE* config = fopen((*configuracion).nombre_archivo, "w");
	if(!config){
		perror("Error");
		return;
	}

	preguntar_configuracion(&(*configuracion), &(*enanos), &(*elfos));

	strcpy(CAMPO, "RESISTENCIA_TORRES");
	fprintf(config, "%s=%i,%i\n", CAMPO, (*configuracion).resistencia_torre_1, (*configuracion).resistencia_torre_2);

	strcpy(CAMPO, "ENANOS_INICIO");
	fprintf(config, "%s=%i,%i,%i,%i\n", CAMPO, (*enanos).nivel_este, (*enanos).nivel_oeste, (*enanos).nivel_norte, (*enanos).nivel_sur);

	strcpy(CAMPO, "ELFOS_INICIO");
	fprintf(config, "%s=%i,%i,%i,%i\n", CAMPO, (*elfos).nivel_este, (*elfos).nivel_oeste, (*elfos).nivel_norte, (*elfos).nivel_sur);

	strcpy(CAMPO, "ENANOS_EXTRA");
	fprintf(config, "%s=%i,%i,%i\n", CAMPO, (*enanos).cantidad_extra, (*enanos).costo_extra_1, (*enanos).costo_extra_2);

	strcpy(CAMPO, "ELFOS_EXTRA");
	fprintf(config, "%s=%i,%i,%i\n", CAMPO, (*elfos).cantidad_extra, (*elfos).costo_extra_1, (*elfos).costo_extra_2);

	strcpy(CAMPO, "ENANOS_ANIMO");
	fprintf(config, "%s=%i,%i\n", CAMPO, (*enanos).critico, (*enanos).fallo);

	strcpy(CAMPO, "ELFOS_ANIMO");
	fprintf(config, "%s=%i,%i\n", CAMPO, (*elfos).critico, (*elfos).fallo);

	strcpy(CAMPO, "VELOCIDAD");
	fprintf(config, "%s=%f\n", CAMPO, (*configuracion).velocidad_juego);

	strcpy(CAMPO, "CAMINOS");
	fprintf(config, "%s=%s\n", CAMPO, (*configuracion).caminos);

	fclose(config);
}


