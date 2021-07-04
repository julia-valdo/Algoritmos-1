#include<stdio.h>

const int VALOR_CERO = 0;
const int DIA_UNO = 1;
const int DIA_ONCE = 11;
const int DIA_VEINTE = 20;
const int DIA_VEINTIUNO = 21;
const int DIA_TREINTA = 30;
const int CERO_HORAS = 0;
const int CUATRO_HORAS = 4;
const int CINCO_HORAS = 5;
const int OCHO_HORAS = 8;
const int DOCE_HORAS = 12;
const int VIENTO_BAJO = 25;
const int VIENTO_MEDIO = 50;
const int VIENTO_ALTO = 75;
const int HUMEDAD_BAJA = 25;
const int HUMEDAD_MEDIA = 50;
const int HUMEDAD_ALTA = 75;
const int CINCO_PUNTOS = 5;
const int DIEZ_PUNTOS = 10;
const int QUINCE_PUNTOS = 15;
const int VEINTE_PUNTOS = 20;
const int VEINTEUNO_PUNTOS = 21;
const int TREINTAYCINCO_PUNTOS = 35;
const int TREINTAYSEIS_PUNTOS = 36;
const int CINCUENTA_PUNTOS = 50;
const char LETRA_NULA = 'N';
const char HORA_MANIANA = 'M';
const char HORA_TARDE = 'T';
const char HORA_NOCHE = 'N';
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char CENA_ENSALADA = 'E';
const char CENA_HAMBURGUESA = 'H';
const char CENA_PIZZA = 'P';
const char CENA_GUISO = 'G';
const char ANIMO_BUENO = 'B';
const char ANIMO_REGULAR = 'R';
const char ANIMO_MALO = 'M';
const char ANIMO_NULO = 'N';


/* Pre-Condicion:
 * Post-Condicion: carga un numero entre 1 y 30.
 */
void ingresar_dia(int* dia_mes){

	printf("Que dia es? (Ingrese un numero entre 1 y 30):\n");
    scanf("%i", dia_mes);
	while(*dia_mes < DIA_UNO || *dia_mes > DIA_TREINTA){
		printf("Error. Ingrese un numero entre 1 y 30:\n");
		scanf("%i", dia_mes);
	}
}

/* Pre-Condicion:
 * Post-Condicion: carga una letra valida.
 */
void ingresar_hora(char* hora_dia){

	printf("Que hora del dia es? (Ingrese M para indicar maniana, T para tarde y N para noche):\n");
    scanf(" %c", hora_dia);
    while(*hora_dia != HORA_MANIANA && *hora_dia != HORA_TARDE && *hora_dia != HORA_NOCHE){
    	printf("Error. Ingrese M (maniana), T (tarde), N (noche):\n");
		scanf(" %c", hora_dia);
    }
}

/* Pre-Condicion:
 * Post-Condicion: carga las variables pie_apoyado_legolas, cena_legolas y 
 *                 horas_dormidas_legolas, con valores validos.
 */
void ingresar_animo_legolas(char* pie_apoyado_legolas, char* cena_legolas, int* horas_dormidas_legolas){

	printf("Con que pie se levanto Legolas? Con el D (derecho) o I (izquierdo):\n");
	scanf(" %c", pie_apoyado_legolas);
	while(*pie_apoyado_legolas != PIE_IZQUIERDO && *pie_apoyado_legolas != PIE_DERECHO){
    	printf("Error. Ingrese D (derecho) o I (izquierdo):\n");
		scanf(" %c", pie_apoyado_legolas);
	}

	printf("Que ceno Legolas? E (ensalada), H (hamburguesa), P (pizza) o G (guiso):\n");
	scanf(" %c", cena_legolas);
	while(*cena_legolas != CENA_ENSALADA && *cena_legolas != CENA_HAMBURGUESA && *cena_legolas != CENA_PIZZA && *cena_legolas != CENA_GUISO){
    	printf("Error. Ingrese  E (ensalada), H (hamburguesa), P (pizza) o G (guiso):\n");
		scanf(" %c", cena_legolas);
	}

	printf("Cuantas horas durmio Legolas? Ingrese un numero entre 0 y 12:\n");
	scanf("%i", horas_dormidas_legolas);
	while(*horas_dormidas_legolas < CERO_HORAS || *horas_dormidas_legolas > DOCE_HORAS){
		printf("Error. Ingrese un numero entre 0 y 12:\n");
		scanf("%i", horas_dormidas_legolas);
	}
}

/* Pre-Condicion:
 * Post-Condicion: carga las variables pie_apoyado_gimli, cena_gimli y 
 *                 horas_dormidas_gimli, las cuales poseen un valor valido.
 */
void ingresar_animo_gimli(char* pie_apoyado_gimli, char* cena_gimli, int* horas_dormidas_gimli){

	printf("Con que pie se levanto Gimli? Con el D (derecho) o I (izquierdo):\n");
	scanf(" %c", pie_apoyado_gimli);
	while(*pie_apoyado_gimli != PIE_IZQUIERDO && *pie_apoyado_gimli != PIE_DERECHO){
    	printf("Error. Ingrese D (derecho) o I (izquierdo):\n");
		scanf(" %c", pie_apoyado_gimli);
	}

	printf("Que ceno Gimli? E (ensalada), H (hamburguesa), P (pizza) o G (guiso):\n");
	scanf(" %c", cena_gimli);
	while(*cena_gimli != CENA_ENSALADA && *cena_gimli != CENA_HAMBURGUESA && *cena_gimli != CENA_PIZZA && *cena_gimli != CENA_GUISO){
    	printf("Error. Ingrese  E (ensalada), H (hamburguesa), P (pizza) o G (guiso):\n");
		scanf(" %c", cena_gimli);
	}

	printf("Cuantas horas durmio Gimli? Ingrese un numero entre 0 y 12:\n");
	scanf("%i", horas_dormidas_gimli);
	while(*horas_dormidas_gimli < CERO_HORAS || *horas_dormidas_gimli > DOCE_HORAS){
		printf("Error. Ingrese un numero entre 0 y 12:\n");
		scanf("%i", horas_dormidas_gimli);
	}
}

 /* Pre-Condicion: recibe un entero (dia_mes) entre 0 y 30.
  * Post-Condicion: en base a los valores recibidos, devuelve un entero que representa el estado del viento.
  */
int calcular_viento(int dia_mes){

	int velocidad_viento = VALOR_CERO;

	if(dia_mes < DIA_ONCE){
		velocidad_viento = VIENTO_ALTO;
	}else if((DIA_ONCE <= dia_mes) && (dia_mes <= DIA_VEINTE)){
		velocidad_viento = VIENTO_MEDIO;
	}else
		velocidad_viento = VIENTO_BAJO;
	
	return velocidad_viento;
}

/* Pre-Condicion: recibe una letra valida.
 * Post-Condicion: devuelve un entero que representa a la letra recibida.
 */
int determinar_humedad(char hora_dia){

	int humedad = VALOR_CERO;

	if(hora_dia == HORA_MANIANA){
		humedad = HUMEDAD_ALTA;
	}else if(hora_dia == HORA_TARDE){
		humedad = HUMEDAD_BAJA;
	}else
		humedad = HUMEDAD_MEDIA;
	
	return humedad;
}

/* Pre-Condicion: recibe valores validos de pie_apoyado, cena y horas_dormidas de cada personaje.
 * Post-Condicion: devuelve un entero entre 5 y 50.
 */
int calcular_puntos_animo(char pie_apoyado, char cena, int horas_dormidas){

	int puntos_animo = VALOR_CERO;

	if(pie_apoyado == PIE_DERECHO){
		puntos_animo = puntos_animo +DIEZ_PUNTOS;
	}

	if(cena == CENA_ENSALADA){
		puntos_animo = puntos_animo +VEINTE_PUNTOS;
	}else if(cena == CENA_HAMBURGUESA){
		puntos_animo = puntos_animo +QUINCE_PUNTOS;
	}else if(cena == CENA_PIZZA){
		puntos_animo = puntos_animo +DIEZ_PUNTOS;
	}else
		puntos_animo = puntos_animo +CINCO_PUNTOS;
	
	if(CINCO_HORAS <= horas_dormidas && horas_dormidas <= OCHO_HORAS){
		puntos_animo = puntos_animo +DIEZ_PUNTOS;
	}else if(horas_dormidas > OCHO_HORAS){
		puntos_animo = puntos_animo +VEINTE_PUNTOS;
	}

	return puntos_animo;
}


/* Pre-Condicion: recibe un entero (puntos_animo) entre 5 y 50. 
 * Post-Condicion: devuelve una letra dependiendo el valor de puntos_animo de cada personaje.
 */
char letra_animo(int puntos_animo){
	
	char letra_animo = ANIMO_NULO;

	if((puntos_animo >= CINCO_PUNTOS) && (puntos_animo <= VEINTE_PUNTOS)){
		letra_animo = ANIMO_MALO;
	}else if((puntos_animo >= VEINTEUNO_PUNTOS) && (puntos_animo <= TREINTAYCINCO_PUNTOS)){
		letra_animo = ANIMO_REGULAR;
	}else if((puntos_animo >= TREINTAYSEIS_PUNTOS) && (puntos_animo <= CINCUENTA_PUNTOS)){
		letra_animo = ANIMO_BUENO;
	}

	return letra_animo;
}

/* Pre-Condicion:
 * Post-Condicion: dependiendo el valor de velocidad_viento imprime un mensaje por pantalla.
 */
void mostrar_viento(int velocidad_viento){

	if(velocidad_viento == VIENTO_ALTO){
		printf("Mucho viento,");
	}else if(velocidad_viento == VIENTO_MEDIO){
		printf("Viento moderado,");
	}else
		printf("Poco viento,");
}

/* Pre-Condicion:
 * Post-Condicion: dependiendo el valor de humedad imprime un mensaje por pantalla.
 */
void mostrar_humedad(int humedad){

	if(humedad == HUMEDAD_ALTA){
		printf(" alta humedad,");
	}else if(humedad == HUMEDAD_MEDIA){
		printf(" humedad normal,");
	}else
		printf(" poca humedad,");
}

/* Pre-Condicion:
 * Post-Condicion: dependiendo el valor de letra_animo imprime un mensaje por pantalla para cada personaje.
 */
void mostrar_animo(char letra_animo){

	if(letra_animo == ANIMO_BUENO){
		printf(" muy buen dia para ");
	}else if(letra_animo == ANIMO_REGULAR){
		printf(" no muy buen dia para ");
	}else
		printf(" muy mal dia para ");
}

/* Pre-Condicion:
 * Post-Condicion:
 */
void mostrar_resumen(int velocidad_viento, int humedad, char letra_animo_legolas, char letra_animo_gimli){

	printf("Resumen: %i %i %c %c.\n", velocidad_viento, humedad, letra_animo_legolas, letra_animo_gimli);
}

int main(){

	int dia_mes = VALOR_CERO;
	int horas_dormidas_legolas = VALOR_CERO;  
	int horas_dormidas_gimli = VALOR_CERO;
	char hora_dia = LETRA_NULA;
	char pie_apoyado_legolas = LETRA_NULA;
	char cena_legolas = LETRA_NULA;
	char pie_apoyado_gimli = LETRA_NULA;
	char cena_gimli = LETRA_NULA;
	int velocidad_viento = VALOR_CERO;
	int humedad = VALOR_CERO;
	int puntos_animo_legolas = VALOR_CERO;
	int puntos_animo_gimli = VALOR_CERO;
	char letra_animo_legolas = LETRA_NULA;
	char letra_animo_gimli = LETRA_NULA;

	ingresar_dia(&dia_mes);
	
	ingresar_hora(&hora_dia);
	
	ingresar_animo_legolas(&pie_apoyado_legolas, &cena_legolas, &horas_dormidas_legolas);
	
	ingresar_animo_gimli(&pie_apoyado_gimli, &cena_gimli, &horas_dormidas_gimli);
		
	velocidad_viento = calcular_viento(dia_mes);
	
	humedad = determinar_humedad(hora_dia);
	
	puntos_animo_legolas = calcular_puntos_animo(pie_apoyado_legolas, cena_legolas, horas_dormidas_legolas);

	puntos_animo_gimli = calcular_puntos_animo(pie_apoyado_gimli, cena_gimli, horas_dormidas_gimli);
	
	letra_animo_legolas = letra_animo(puntos_animo_legolas);

	letra_animo_gimli = letra_animo(puntos_animo_gimli);

	mostrar_viento(velocidad_viento);

	mostrar_humedad(humedad);

	mostrar_animo(letra_animo_legolas);
	printf("Legolas y definitivamente");

	mostrar_animo(letra_animo_gimli);
	printf("Gimli.\n");

	mostrar_resumen(velocidad_viento, humedad, letra_animo_legolas, letra_animo_gimli);

	return 0;
}