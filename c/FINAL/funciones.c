#include<stdio.h>
#include<stdlib.h> /*para el malloc*/
#include<stdlib.h> /*libreria para utilizar el atof*/
#include "funciones.h"

/*FUNCION 1*/

void ingresar_cola(ptrNodo *ptrS, ptrNodo *ptrF , int n)
{
	ptrNodo ptrActual;
	ptrNodo ptrNuevo;
	ptrNodo ptrFinal;


	ptrNuevo = (ptrNodo)malloc(sizeof(NODO));//se crea espacio para el nodo
	ptrActual = *ptrS;
	ptrFinal = *ptrF;

	if(ptrNuevo != NULL)//si se pudo crear el espacio entra
	{
    		
    		/*ACA VA LA FUNCION QUE LEE EL ARCHIVO Y GUARDA LOS DATOS EN EL NODO*/
    		leer_archivo(&ptrNuevo,n);	
    		
		ptrNuevo->ptrSig = NULL;
		
		

		if(ptrActual != NULL)
    		{
        		ptrFinal->ptrSig = ptrNuevo;
        		*ptrF = ptrNuevo;
    		}
    		else
    		{
        		*ptrS = ptrNuevo;
        		*ptrF = ptrNuevo;
    		}
	}
	else//por si no hay espacio en el sistema
	{
	    	printf("\n error, no hay espacio \n");
	}
}

/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 2*/

/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 3*/

void leer_archivo(ptrNodo *ptrS, int n)
{
	FILE *archivo; 
	char c;
	char arr[5];/*cadena de caracteres donde se va a guardar temporalmente la humedad, la temp y la presion*/
	
	int i = 0;//para indicar en que posicion de arr[] se guarde cada caracter
	
	float aux; //variable auxiliar en donde se va a guardar temporalmente la humedad, la temp y la presion
	
	int ban = 0;//bandera que sirve para determinar que valor contiene la variable auxiliar
		    // osea, si tiene el valor de la temperatura, de la humedad, etc

	ptrNodo ptrNuevo = *ptrS;
	
	/*se abre el archio donde estan guardados los datos obtenidos por los sensores*/
	archivo = fopen("datos.txt","r"); 
	if(archivo == NULL )
	{
	    	printf("\nno se pudo abrir el archivo");
	}
	else
	{
	    fseek(archivo,(n*24), SEEK_SET);
	    
	    while((c = fgetc(archivo)) != '\n')
	        {
			if(c == '\t')     //cuando ya termino de leer un dato (ya sea la temperatura, la humedad, etc)
	           	{	         //porque los datos van a estar separados por un TAB '\t'
	                	i = 0; 
	            	} 
	            	else
	            	{
	                	arr[i] = c;
	                	i++;
	            	}
	            
	       		if(i == 5)
	       		{
				/*funcion que convierte arr en float*/
				aux = atof(arr);
				
				if(ban==0)
					ptrNuevo->temp = aux;
						
					
				if(ban==1)
					ptrNuevo->hum = aux;
						
				
				if(ban==2)
					ptrNuevo->pres = aux;
				
				
				
				if(ban==3)
				{
					ptrNuevo->hora[0] = arr[0];
					ptrNuevo->hora[1] = arr[1];
					ptrNuevo->hora[2] = arr[2];
					ptrNuevo->hora[3] = arr[3];
					ptrNuevo->hora[4] = arr[4];
					ptrNuevo->hora[5] = arr[5];
				}	
								
				ban++;
        		}
        		
       	 	}
        	/*cierra el while*/

	
	}

}


/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 4*/

void archivo_usuario(ptrNodo ptrS)
{
	FILE *archivo;
	
	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	
	
	archivo = fopen("archivoPiola.txt", "w");
		
	if(archivo == NULL)
	{
		printf("\nNo se pudo crear el archivo.\n");
	}
	else
	{
		fprintf(archivo,"\tDATOS OBTENIDOS");
		
		if(ptrActual != NULL)
		{
			while(ptrActual != NULL)
			{
				fprintf(archivo,"\n%.2f",ptrActual->temp);
				fprintf(archivo,"\t%.2f",ptrActual->hum);
				fprintf(archivo,"\t%.2f",ptrActual->pres);
				fprintf(archivo,"\t%s",ptrActual->hora);
			
				ptrAnterior = ptrActual;
				ptrActual = ptrAnterior->ptrSig;		
			}
		

		
		}
		else
		{
			fprintf(archivo,"\nNo hay ningun dato que poner en el archivo.\n");
		}
					
		fclose(archivo);
		
	}

}


/*---------------------------------------------------------------------------------------------------------------------------*/

void mostrar(ptrNodo ptrS)
{

	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	

	if(ptrActual != NULL)
	{
		while(ptrActual != NULL)
		{
			printf("\n%.2f",ptrActual->temp);
			printf("\t%.2f",ptrActual->hum);
			printf("\t%.2f",ptrActual->pres);
			printf("\t%s",ptrActual->hora);
			
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;		
		}
		

		
	}
	else
	{
		printf("\nNo hay ningun dato que mostrar.\n");
	}
		
}





























































