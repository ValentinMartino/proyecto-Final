#ifndef FUNCIONES_H
#define FUNCIONES_H

struct nodo{

float temp;
float hum;
float pres;
char hora[6]; 

struct nodo *ptrSig;

};

typedef struct nodo NODO;
typedef NODO *ptrNodo;

/*FUNCIONES*/

/*FUNCION1:
*
* esta funcion ingresa un nodo nuevo, en esta funcion
* esta la funcion que lee los datos del archivo.
* El int es la cantidad de datos que fueron recibidos
* del arduino */
void ingresar_cola(ptrNodo *,ptrNodo *, int);


/*FUNCION2: 
*
* Esta funcion se comunica con el puerto serial de Arduino,
* lee todos los datos enviados por este y los guarda en un
* archivo (de texto o nose). Devuelve la cantidad de datos
* que fueron recibidos del arduino. Por ejemplo: si devuel-
* ve 50, luego en el main se va a llamar 50 veces a la fun-
* cion de ingresar cola.*/
int leer_puerto();

/*FUNCION 3:
*
* Esta funcion se encarga de leer el archivo donde estan 
* los datos y guardarlos en el nodo correspondiente de la
* estructura de datos. Esta funcion solo se llama dentro 
* de la funcion ingresar cola. Esta funcion recibe el 
* ptrNuevo para guardarle los valores de presion, temp, etc*/
void leer_archivo(ptrNodo *, int);


/*FUNCION 4:
*
* Esta funcion encuentra al mayor dato, ya sea temp, hum o pres
* El entero que recibe es para especificar que va a encontrar
* si la temp mayor o la pres mayor o la hum mayor*/
int mayor_dato(ptrNodo, int);

/*FUNCION 5:
*
* Esta funcion encuentra al menor dato, ya sea temp, hum o pres
* El entero que recibe es para especificar que va a encontrar
* si la temp menor o la pres menor o la hum menor*/
int menor_dato(ptrNodo, int);

/*FUNCION 6:
*
* Esta funcion es por si el usuario quiere tener un archivo 
* para leercon los datos obtenidos. Recibe como parametro
* el inicio a la cola. retorna 1 si los datos se guardaron
* en el archivo, y cero si hubo algun error*/
int archivo_usuario(ptrNodo);


/*FUNCION 7:
*
* Esta funcion muestra por pantalla los mismos datos que la
* funcion archivo_usuario*/
void mostrar(ptrNodo);


/*FUNCION 8:
*
* funcion que muestra el grafico de temperatura. */

void grafico_temp(ptrNodo, int);

/*FUNCION 9:
*
* funcion que muestra el grafico de humedad. */

void grafico_hum(ptrNodo, int);

/*FUNCION 10:
*
* funcion que muestra el grafico de presion. */

void grafico_pres(ptrNodo, int);





/* FUNCION QUE NO ME GUSTA:
*
* esta funcion cuenta las lineas del archivo datos.txt para 
* saber cuantas veces llamar a la funcion de crear cola*/

int contar();



#endif














