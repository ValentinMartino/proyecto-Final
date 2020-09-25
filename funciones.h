#ifndef FUNCIONES_H
#define FUNCIONES_H


struct nodo{

float temp;
float humedad;
float presion;

struct nodo *ptrSig;

};

typedef struct nodo NODO;
typedef NODO *ptrNodo;


//prototipos de las funciones

//FUNCION 1

void insertar_nodo(ptrNodo *);

//FUNCION 2

void mostrar(ptrNodo);

//FUNCION 3

void eliminar_nodo(ptrNodo *);

//FUNCION 4

void insertar_inicio(ptrNodo *);

//FUNCION 5

void insertar_cola(ptrNodo *);

//FUNCION 6

void eliminar_inicio(ptrNodo *);

//FUNCION 7

void eliminar_cola(ptrNodo *);

//FUNCION 8

void borrar_lista(ptrNodo *);

//FUNCION 9

void ordenar_lista(ptrNodo *);








#endif
