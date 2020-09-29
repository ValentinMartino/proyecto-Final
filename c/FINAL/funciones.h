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
* Esta funcion es por si el usuario quiere tener un archivo 
* para leercon los datos obtenidos. Recibe como parametro
* el inicio a la cola*/
void archivo_usuario(ptrNodo);




void mostrar(ptrNodo);


#endif














