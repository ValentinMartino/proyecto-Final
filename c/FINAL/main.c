#include<stdio.h>
#include"funciones.h"

int main()
{
	//printf(FONDO_BLANCO); // pone todo en blanco
	//printf(LETRA_NEGRA); // pone todas las letras en negro
	
	int cant_nodos = lineas();

	if(cant_nodos != 0)
	{
		
		char c;
		
		printf("\n¿Desea recuperar el archivo de la ultima vez que ejecuto el programa?(s/cualquier caracter");
		scanf("%c",&c);
		
		if(c == 's' || c == 'S')
		{		
			menu(cant_nodos);
			
			return 0; //termina la ejecucion del programa
		
		}
		else
		{
			//cant_nodos = leer_puerto();
	
			cant_nodos = 10;
	
			menu(cant_nodos);		
		}	
	}
	
	

		
	
	putchar('\n');
	return 0;
}


