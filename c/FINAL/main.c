#include<stdio.h>
#include"funciones.h"

int main()
{
	ptrNodo ptrInicial = NULL;
	ptrNodo ptrFinal = NULL;
	
	for(int i = 0; i<11; i++)
		ingresar_cola(&ptrInicial, &ptrFinal,i);
	
	mostrar(ptrInicial);
	archivo_usuario(ptrInicial);
	
	
	putchar('\n');
	return 0;
}


