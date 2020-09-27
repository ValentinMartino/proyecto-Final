#include<stdio.h>
#include<stdlib.h> /*libreria para utilizar el atof*/


int main()
{
	FILE *archivo;
	char c;
	char arr[5];
	
	int i = 0;
	int ban = 0;
	
	float aux;

	float temp,hum,pres;

	archivo = fopen("datos.txt","r"); 
	if(archivo == NULL )
	{
	    	printf("\nno se pudo abrir el archivo");
	}
	else
	{
	    while((c = fgetc(archivo)) != '\n')
	        {
			if(c == '\t')
	           	{
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
