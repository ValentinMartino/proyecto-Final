#include<stdio.h>
#include<stdlib.h>
#include "funciones.h"


//FUNCION 1
//ingresa un nodo y lo ordena entre los nodos dependiendo del valor del entero que esta en ese nodo

//Agrego este comentario

void insertar_nodo(ptrNodo *ptrS)
{	

	ptrNodo ptrActual;
	ptrNodo ptrAnterior;
	ptrNodo ptrNuevo;
 

	ptrNuevo = (ptrNodo)malloc(sizeof (NODO)); /* crea un nodo */

	if(ptrNuevo != NULL)     /* hay espacio disponible */
	{
		/*
		aca se ingresa la humedad, temperatura y presion al ptrNuevo
		
		ptrNuevo->ptrSig = NULL; /* el nodo no se enlaza con otro nodo */
		
		*/
		
		ptrNuevo->ptrSig = NULL; /* el nodo no se enlaza con el nodo siguiente */
	
		
		ptrAnterior = NULL;
		ptrActual = *ptrS; /*  */
		
		
		/*ESTE WHILE ES PARA ORDENAR LOS NODOS, QUE POR EJEMPLO LOS PODEMOS IR ORDENANDO POR LA HORA*/
		while(ptrActual != NULL && ptrNuevo->num > ptrActual->num)  
		{
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
		}
		
		
		/* si no habia ningun nodo y es el primero que se va a incertar */
		
		if(ptrAnterior == NULL)
		{
			ptrNuevo->ptrSig = ptrActual;
			*ptrS = ptrNuevo;
			
		}
		else
		{
			ptrAnterior->ptrSig = ptrNuevo;
			ptrNuevo->ptrSig = ptrActual;			
		}
		
	}
	else
	{	
		printf("\nNo se inserto el nodo TAL porque no hay espacio disponible. \n",dato );
	}

} /*termina la funcion */

/*--------------------------------------------------------------------------------------------------------------------------*/

//FUNCION 2

void mostrar(ptrNodo ptrS)
{
	ptrNodo ptrActual;
	ptrNodo ptrAnterior;
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	
	
	putchar('\n');
	putchar('\t');
	
	if(ptrActual != NULL) //si hay por lo menos un nodo que mostrar
	{
		while(ptrActual != NULL) //mientras que el ptrActual no llegue al final se itera el while
		{
			printf("%i - ", ptrActual->num);
			
			ptrAnterior = ptrActual;		//estas dos lineas recorren todos los nodos hasta el final
			ptrActual = ptrAnterior->ptrSig;
		}
		
		printf("---->FIN DE LA LISTA\n");
				
	}
	else
	{
		printf("\nNo hay nada que mostrar en la lista.\n");
	}
	
	
}

/*---------------------------------------------------------------------------------------------------------------------------*/
//FUNCION 3

void eliminar_nodo(ptrNodo *ptrS)
{
	ptrNodo ptrActual;
	ptrNodo ptrAnterior;

	int dato;
	int ban = 0;	

	ptrActual = *ptrS;
	ptrAnterior = NULL;
	

	if(ptrActual != NULL)
	{
		printf("\nIngrese el dato que quiera eliminar: ");
		scanf("%i",&dato);
	
		while(ptrActual != NULL && ban == 0)
		{
			if(ptrActual->num == dato && ptrAnterior != NULL) //caso en que quiera eliminar el nodo que no sea el primero
			{
				ptrAnterior->ptrSig = ptrActual->ptrSig;
				free(ptrActual);
				ban = 1;
			}
			
			if(ptrActual->num == dato && ptrAnterior == NULL) //caso en el que quiera eliminar el primer nodo
			{
				*ptrS = ptrActual->ptrSig;
				free(ptrActual);
				ban = 1;
			}

			ptrAnterior = ptrActual;          //estas dos lineas hace que se "corra" de nodo
			ptrActual = ptrAnterior->ptrSig;
		}

		if(ban == 0) //quiere decir que salio del while porque llego al final y no encontro el dato que el uduario queria elimiar
		{
			printf("\nNo existe el archivo que quiera eliminar.\n");
		}
	}
	else
	{
		printf("\nNo hay dato que eliminar. ");
	}

}

/*---------------------------------------------------------------------------------------------------------------------------*/

//FUNCION 4

void insertar_inicio(ptrNodo *ptrS)
{

	ptrNodo ptrActual;
	ptrNodo ptrNuevo;
	
	int dato;  //dato que va a ingresar el usuario
	
	
	ptrNuevo = (ptrNodo)malloc(sizeof(NODO));
	
	ptrActual = *ptrS;
	
	if(ptrNuevo != NULL)
	{
		printf("\nIngrese el numero: ");
		scanf("%i", &dato);
		
		ptrNuevo->num = dato;     /* coloca el valor en el nodo */
		ptrNuevo->ptrSig = NULL; /* el nodo no se enlaza con otro nodo */
	
		if(ptrActual != NULL) // caso en que el nodo actual exista
		{
			*ptrS = ptrNuevo;
			ptrNuevo->ptrSig = ptrActual;
		}
		else
		{
			*ptrS = ptrNuevo;	
		}
	}
	else
	{
		printf("\nNo hay espacio para crear un nuevo nodo.\n");
	}
	
}

/*---------------------------------------------------------------------------------------------------------------------------*/

//FUNCION 5

void insertar_cola(ptrNodo *ptrS)
{
	ptrNodo ptrActual;
	ptrNodo ptrAnterior;
	ptrNodo ptrNuevo;
		
	int dato;  //dato que va a ingresar el usuario
		
	ptrNuevo = (ptrNodo)malloc(sizeof(NODO));
	
	ptrActual = *ptrS;
	ptrAnterior = NULL;
	
	if(ptrNuevo != NULL)
	{
		printf("\nIngrese el numero: ");
		scanf("%i", &dato);
		
		ptrNuevo->num = dato;     /* coloca el valor en el nodo */
		ptrNuevo->ptrSig = NULL; /* el nodo no se enlaza con otro nodo */
	
		
		if(ptrActual == NULL)
		{
			*ptrS = ptrNuevo;
		}
		else
		{		
			while(ptrActual != NULL) //mientras que el ptrActual no llegue al final se itera el while
			{			
				ptrAnterior = ptrActual;		//estas dos lineas recorren todos los nodos hasta el final
				ptrActual = ptrAnterior->ptrSig;
			}
			
			ptrAnterior->ptrSig = ptrNuevo; //en este punto el prtAnterior va a ser el ultimo de la lista
		}	
	}
	else
	{
		printf("\nNo hay espacio para crear un nuevo nodo.\n");
	}

}

/*---------------------------------------------------------------------------------------------------------------------------*/
//FUNCION 6

void eliminar_inicio(ptrNodo *ptrS)
{
	ptrNodo ptrActual;

	ptrActual = *ptrS;
	
	if(ptrActual != NULL)
	{
		*ptrS = ptrActual->ptrSig;
		free(ptrActual);		
	}
	else
	{
		printf("\nNo hay dato que eliminar. ");
	}
}

/*---------------------------------------------------------------------------------------------------------------------------*/


//FUNCION 7

void eliminar_cola(ptrNodo *ptrS)
{
	
	ptrNodo ptrActual;
	ptrNodo ptrAnterior;
	
	ptrActual = *ptrS;
	ptrAnterior = NULL;
			
		
	if(ptrActual != NULL)
	{
		while(ptrActual->ptrSig != NULL) //mientras que el siguiente del ptrActual no llegue al final se itera el while
		{			
			ptrAnterior = ptrActual;		//estas dos lineas recorren todos los nodos hasta el final
			ptrActual = ptrAnterior->ptrSig;
		}
			
			
		ptrAnterior->ptrSig = ptrActual->ptrSig;
		free(ptrActual);		
	}
	else
	{
		printf("\nNo hay dato que eliminar. ");
	}	
		
}

/*---------------------------------------------------------------------------------------------------------------------------*/

//FUNCION 8

void borrar_lista(ptrNodo *ptrS)
{
	ptrNodo ptrActual;
	ptrNodo ptrAnterior;
	
	ptrActual = *ptrS;
	
	if(ptrActual != NULL)
	{
		while(ptrActual != NULL)
		{
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			free(ptrAnterior);
		}
		
		*ptrS = NULL;
	}
	else
	{
		printf("\nNo hay nada que borrar.\n");
	}


}

/*---------------------------------------------------------------------------------------------------------------------------*/
