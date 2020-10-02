#include<stdio.h>
#include<stdlib.h> /*libreria para utilizar el atof*/


int main()
{
	FILE *archivo;
	char c;
	char arr[5];
	
	int i = 0;//para indicar en que posicion de arr[] se guarde cada caracter
	
	float aux; //variable auxiliar en donde se va a guardar temporalmente la humedad, la temp y la presion
	
	int ban = 0;//bandera que sirve para determinar que valor contiene la variable auxiliar
		    // osea, si tiene el valor de la temperatura, de la humedad, etc


	float temp,hum,pres; //solo sirven de prueba mientras no tengamos la estructura de datos

	/*se abre el archio donde estan guardados los datos obtenidos por los sensores*/
	archivo = fopen("datos.txt","r"); 
	if(archivo == NULL )
	{
	    	printf("\nno se pudo abrir el archivo");
	}
	else
	{
	    while((c = fgetc(archivo)) != '\n')
	        {
			if(c == '\t') // cuando ya termino de leer un dato (ya sea la temperatura, la humedad, etc)
	           	{	      //porque los datos van a estar separados por un TAB '\t'
	                	i = 0; 
	            	} 
	            	else
	            	{
	                	arr[i] = c;
	                	i++;
	            	}
	            
	       		if(i == 4)
	       		{
				/*funcion que convierte arr en float*/
				aux = atof(arr);
				
				if(ban==0)
					/*estructura->temperatura = aux*/
					temp = aux;
					
				if(ban==1)
					/*estructura->humedad= aux*/
					hum = aux;
				
				if(ban==2)
					/*estructura->presion = aux*/
					pres = aux;
				
				//if(ban==3)
					/*estructura->hora = aux*/
								
				ban++;
        		}
        		
       	 	}
        	/*cierra el while*/
        
	printf("\n%.2f",temp);
	printf("\n%.2f",hum);
	printf("\n%.2f",pres);
	
}

	putchar('\n');
	return 0;
}
