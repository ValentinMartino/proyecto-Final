#include<stdio.h>
#include<string.h>
#include<stdlib.h> /*para el malloc*/
#include<stdlib.h> /*libreria para utilizar el atof*/
#include<fcntl.h> /* File control definitions             PARA LA FUNCION DE LEER EL PUERTO*/
#include<unistd.h> /* UNIX standard function definitions  PARA LA FUNCION DE LEER EL PUERTO*/
#include "termset.h"/*                                   PARA LA FUNCION DE LEER EL PUERTO*/
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

int leer_puerto()
{
	int fd ; /* Descriptor de archivo del puerto */
	unsigned char leido_1 [6]; /*caracter para tomar los datos obtenidos del puerto serie*/
	char basura;

	FILE *archivo;
  
	struct termios oldtty , newtty ; //termset.h
  

	fd = open ("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY );
	if( fd == -1)
	{
		printf (" ERROR : no se pudo abrir el dispositivo .\n");
		return -1;
	}

	if( termset (fd , 9600 , & oldtty , & newtty ) == -1)
	{
		printf (" ERROR : no se pudo configurar el TTY \n");
		return -1;
	}

	//abrimos el archivo y verificamos que no haya errores

	archivo = fopen("datos.txt", "w");
		
	if(archivo == NULL)
	{
		printf("\nNo se pudo crear el archivo.\n");
		return -1;
	}

	tcflush ( fd , TCIOFLUSH );
        
	int ban = 0;
	
	write (fd , "s", 1);
	sleep (1);
	
	while(ban < 2 )
	{
		read(fd, &basura, 1);
		
		if(basura == 's')
			ban++;
		else
		{
			printf("\nban = %i",ban);
			ban = 0;
		}		
	}
		
	// read ( la cantidad de datos tomados)
	

		
	for (int i = 0; i<6; i++)
	{
       	
 		if(i%4 == 0 && i != 0)
		{
			printf("\n");
         		fprintf(archivo, "\n");
         	}         		
         	
	 	read(fd, leido_1 , 5);

	 	fprintf(archivo,"%s\t",leido_1);
	 	printf("%s\t",leido_1);  
	 	
	 	/*simulacion de la hora*/
         	if(i%4 == 0 && i != 0)
         	{
         		fprintf(archivo,"15:24");  
         		printf("15:24"); 
         	}	
	}

	fclose(archivo); //cerramos el archivo de texto
	close (fd);
	
	
	//FALTA EL RETURN DE LA CANTIDAD DE DATOS OBTENIDOS POR LOS SENSORES
	
	return 1;
}

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
	    fseek(archivo,(n*24), SEEK_SET); //n*24 pq cada linea tiene 24 caracteres
	    
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

int mayor_dato(ptrNodo ptrS, int a)
{

	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	int nodo_mayor = 0;
	int i = 0; //iterador 
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	
	float mayor = -200.0;
	

	//if(ptrActual != NULL) <------- no es necesario poner eso ya que si no hay ningun nodo nunca se va a llamar esta
				      // funcion. La funcion mayor_dato() se llama en las funciones 5 y 6.
	
	if(a == 1) //busca la temperatura mayor
	{
		while(ptrActual != NULL)
		{
			if(ptrActual->temp > mayor)
			{
				mayor = ptrActual->temp;
				nodo_mayor = i;
			}
				
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i ++;		
		}		
	}
	
	if(a == 2) //busca la humedad mayor
	{
		while(ptrActual != NULL)
		{
			if(ptrActual->hum > mayor)
			{
				mayor = ptrActual->hum;
				nodo_mayor = i;
			}
				
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i ++;		
		}		
	}
	
	if(a == 3) //busca la presion mayor
	{
		while(ptrActual != NULL)
		{
			if(ptrActual->pres > mayor)
			{
				mayor = ptrActual->pres;
				nodo_mayor = i;
			}
				
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i ++;		
		}		
	}

	return nodo_mayor;
}

/*FUNCION 5*/

int menor_dato(ptrNodo ptrS, int a)
{

	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	int nodo_menor = 0;
	int i = 0; //iterador 
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	
	float menor = 300.0;
	

	//if(ptrActual != NULL) <------- no es necesario poner eso ya que si no hay ningun nodo nunca se va a llamar esta
				      // funcion. La funcion mayor_dato() se llama en las funciones 5 y 6.
	
	if(a == 1) //busca la temperatura menor
	{
		while(ptrActual != NULL)
		{
			if(ptrActual->temp < menor)
			{
				menor = ptrActual->temp;
				nodo_menor = i;
			}
				
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i ++;		
		}		
	}
	
	if(a == 2) //busca la humedad menor
	{
		while(ptrActual != NULL)
		{
			if(ptrActual->hum < menor)
			{
				menor = ptrActual->hum;
				nodo_menor = i;
			}
				
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i ++;		
		}		
	}
	
	if(a == 3) //busca la presion menor
	{
		while(ptrActual != NULL)
		{
			if(ptrActual->pres < menor)
			{
				menor = ptrActual->pres;
				nodo_menor = i;
			}
				
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i ++;		
		}		
	}

	return nodo_menor;
}




/*---------------------------------------------------------------------------------------------------------------------------*/




/*FUNCION 6*/

void archivo_usuario(ptrNodo ptrS)
{
	FILE *archivo;
	
	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	
	int i = 0; //iterador
	
	int t, h, p;       //en estas variables se guarda la posicion del nodo en donde se registro el ultimo MAYOR
	float t_ma, h_ma, p_ma;       //en estas variables se guarda el ultimo MAYOR dato registrado 
	char h_t_ma[6], h_h_ma[6], h_p_ma[6];      //en estas cadenas se guarda la hora en donde se registro el ultimo MAYOR
	
	int t2, h2, p2;        //en estas variables se guarda la posicion del nodo en donde se registro el ultimo MENOR
	float t_me, h_me, p_me;       //en estas variables se guarda el ultimo MENOR dato registrado 
	char h_t_me[6], h_h_me[6], h_p_me[6];      //en estas cadenas se guarda la hora en donde se registro el ultimo MENOR
	
	
	archivo = fopen("archivoPiola.txt", "w");
		
	if(archivo == NULL)
	{
		printf("\nNo se pudo crear el archivo.\n");
	}
	else
	{
		
		
		if(ptrActual != NULL)
		{
			
			fprintf(archivo,"\t\tDATOS RECOPILADOS POR LOS SENSORES");
			fprintf(archivo,"\n\nA continuacion se muestra una tabla con todos los resultados:\n\n");
			fprintf(archivo,"TEMP\tHUM\tPRES\tHORA\n");
			
			/*en las siguientes 3 lineas se se guarda la posicion del nodo en donde se registro el ultimo MAYOR*/
			t = mayor_dato(ptrActual, 1);
			h = mayor_dato(ptrActual, 2);
			p = mayor_dato(ptrActual, 3);
		
			/*en las siguientes 3 lineas se se guarda la posicion del nodo en donde se registro el ultimo MENOR*/
			t2 = menor_dato(ptrActual, 1);
			h2 = menor_dato(ptrActual, 2);
			p2 = menor_dato(ptrActual, 3);
			
		
			while(ptrActual != NULL)
			{
				fprintf(archivo,"\n%.2f",ptrActual->temp);
				fprintf(archivo,"\t%.2f",ptrActual->hum);
				fprintf(archivo,"\t%.2f",ptrActual->pres);
				fprintf(archivo,"\t%s",ptrActual->hora);
				
				if(t == i) //algoritmo para guardar la MAYOR temperatura y hora en su respectiva variable
				{
					t_ma = ptrActual->temp;
					strcpy( h_t_ma, ptrActual->hora );
				}
			
				if(h == i) //algoritmo para guardar la MAYOR humedad y hora en su respectiva variable
				{
					h_ma = ptrActual->hum;
					strcpy( h_h_ma, ptrActual->hora );
				}
			
				if(p == i) //algoritmo para guardar la MAYOR presion y hora en su respectiva variable
				{
					p_ma = ptrActual->pres;
					strcpy( h_p_ma, ptrActual->hora );
				}
			
			
				if(t2 == i) //algoritmo para guardar la MENOR temperatura y hora en su respectiva variable
				{
					t_me = ptrActual->temp;
					strcpy( h_t_me, ptrActual->hora );
				}
			
				if(h2 == i) //algoritmo para guardar la MENOR humedad y hora en su respectiva variable
				{
					h_me = ptrActual->hum;
					strcpy( h_h_me, ptrActual->hora );
				}
			
				if(p2 == i) //algoritmo para guardar la MENOR presion y hora en su respectiva variable
				{
					p_me = ptrActual->pres;
					strcpy( h_p_me, ptrActual->hora );
				}
			
				ptrAnterior = ptrActual;
				ptrActual = ptrAnterior->ptrSig;
				
				i++;		
			}
			
			
			fprintf(archivo,"\n\nLa mayor temperatura registrada es %.2f y la ultima hora en la que se registro "
		     	 		 "fue a las %s hs",t_ma, h_t_ma);
		       
			fprintf(archivo,"\nLa mayor humedad registrada es %.2f y la ultima hora en la que se registro "
		      		 	"fue a las %s hs",h_ma, h_h_ma);
		
			fprintf(archivo,"\nLa mayor presion registrada es %.2f y la ultima hora en la que se registro "
			  		"fue a las %s hs",p_ma, h_p_ma);
		       
		       
			fprintf(archivo,"\n\nLa menor temperatura registrada es %.2f y la ultima hora en la que se registro "
		       			"fue a las %s hs",t_me, h_t_me);
		       
			fprintf(archivo,"\nLa menor humedad registrada es %.2f y la ultima hora en la que se registro "
		   			"fue a las %s hs",h_me, h_h_me);
		
			fprintf(archivo,"\nLa menor presion registrada es %.2f y la ultima hora en la que se registro "
		       			"fue a las %s hs",p_me, h_p_me);
		

		
		}
		else
		{
			fprintf(archivo,"\nNo hay ningun dato que poner en el archivo.\n");
		}
					
		fclose(archivo);
		
	}

}



/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 7*/

void mostrar(ptrNodo ptrS)
{

	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	int i = 0; //iterador
	
	int t, h, p;       //en estas variables se guarda la posicion del nodo en donde se registro el ultimo MAYOR
	float t_ma, h_ma, p_ma;       //en estas variables se guarda el ultimo MAYOR dato registrado 
	char h_t_ma[6], h_h_ma[6], h_p_ma[6];      //en estas cadenas se guarda la hora en donde se registro el ultimo MAYOR
	
	int t2, h2, p2;        //en estas variables se guarda la posicion del nodo en donde se registro el ultimo MENOR
	float t_me, h_me, p_me;       //en estas variables se guarda el ultimo MENOR dato registrado 
	char h_t_me[6], h_h_me[6], h_p_me[6];      //en estas cadenas se guarda la hora en donde se registro el ultimo MENOR
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	

	if(ptrActual != NULL)
	{
		printf("\t\tDATOS RECOPILADOS POR LOS SENSORES");
		printf("\n\nA continuacion se muestra una tabla con todos los resultados:\n\n");
		printf("TEMP\tHUM\tPRES\tHORA\n");
		
		/*en las siguientes 3 lineas se se guarda la posicion del nodo en donde se registro el ultimo MAYOR*/
		t = mayor_dato(ptrActual, 1);
		h = mayor_dato(ptrActual, 2);
		p = mayor_dato(ptrActual, 3);
		
		/*en las siguientes 3 lineas se se guarda la posicion del nodo en donde se registro el ultimo MENOR*/
		t2 = menor_dato(ptrActual, 1);
		h2 = menor_dato(ptrActual, 2);
		p2 = menor_dato(ptrActual, 3);
		
		while(ptrActual != NULL)
		{
			printf("\n%.2f",ptrActual->temp);
			printf("\t%.2f",ptrActual->hum);
			printf("\t%.2f",ptrActual->pres);
			printf("\t%s",ptrActual->hora);
			
			if(t == i) //algoritmo para guardar la MAYOR temperatura y hora en su respectiva variable
			{
				t_ma = ptrActual->temp;
				strcpy( h_t_ma, ptrActual->hora );
			}
			
			if(h == i) //algoritmo para guardar la MAYOR humedad y hora en su respectiva variable
			{
				h_ma = ptrActual->hum;
				strcpy( h_h_ma, ptrActual->hora );
			}
			
			if(p == i) //algoritmo para guardar la MAYOR presion y hora en su respectiva variable
			{
				p_ma = ptrActual->pres;
				strcpy( h_p_ma, ptrActual->hora );
			}
			
			
			if(t2 == i) //algoritmo para guardar la MENOR temperatura y hora en su respectiva variable
			{
				t_me = ptrActual->temp;
				strcpy( h_t_me, ptrActual->hora );
			}
			
			if(h2 == i) //algoritmo para guardar la MENOR humedad y hora en su respectiva variable
			{
				h_me = ptrActual->hum;
				strcpy( h_h_me, ptrActual->hora );
			}
			
			if(p2 == i) //algoritmo para guardar la MENOR presion y hora en su respectiva variable
			{
				p_me = ptrActual->pres;
				strcpy( h_p_me, ptrActual->hora );
			}
			
			
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i++;		
		}
					
		printf("\n\nLa mayor temperatura registrada es %.2f y la ultima hora en la que se registro "
		       "fue a las %s hs",t_ma, h_t_ma);
		       
		printf("\nLa mayor humedad registrada es %.2f y la ultima hora en la que se registro "
		       "fue a las %s hs",h_ma, h_h_ma);
		
		printf("\nLa mayor presion registrada es %.2f y la ultima hora en la que se registro "
		       "fue a las %s hs",p_ma, h_p_ma);
		       
		       
		printf("\n\nLa menor temperatura registrada es %.2f y la ultima hora en la que se registro "
		       "fue a las %s hs",t_me, h_t_me);
		       
		printf("\nLa menor humedad registrada es %.2f y la ultima hora en la que se registro "
		       "fue a las %s hs",h_me, h_h_me);
		
		printf("\nLa menor presion registrada es %.2f y la ultima hora en la que se registro "
		       "fue a las %s hs",p_me, h_p_me);
		
	}
	else
	{
		printf("\nNo hay ningun dato que mostrar.\n");
	}
		
}


/*---------------------------------------------------------------------------------------------------------------------------*/



























































