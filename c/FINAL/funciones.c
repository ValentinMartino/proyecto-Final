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
        
	tcflush (fd , TCIOFLUSH);
        
	int ban = 0;
	int ban2 = 0;
	
	write (fd , "s", 1);
	sleep (10);

	while(ban < 2 )
	{
		read(fd, &basura, 1);
		
		if(basura == 's')
			ban++;
		else
		{
			printf("\nBan = %i",ban);
			ban = 0;
			ban2 ++;			
		}
		if(ban2 == 1)
		{
			printf("\nBan2 = %i\n",ban2);
			write (fd , "s", 1);
			sleep (2);
			ban2 = 0;		
		}		
	}
		
	// read ( la cantidad de datos tomados)
	
	char numero[4];
	float num;
	
	read(fd, numero, 3);
	num = atof(numero);
	
	printf("\nNum = %f \n",num);
	
			
	for (int i = 0; i<(num*5); i++)
	{
       	
 		if(i%4 == 0 && i != 0)
		{			
			printf("\n");
         		fprintf(archivo, "\n");
         	}
         	
	 	read(fd, leido_1 , 5);


	 	fprintf(archivo,"%s\t",leido_1);
	 	printf("%s\t",leido_1); 	
	}
	
	fprintf(archivo,"\n");
	

	fclose(archivo); //cerramos el archivo de texto
	
	write (fd , "r", 1); // le indica al programa en arduino que reinicie sus valores
	close (fd);
     
     
	putchar('\n');
	
 	return (int)num;
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
	    fseek(archivo,(n*30), SEEK_SET); //n*24 pq cada linea tiene 24 caracteres
	    
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
	       			if(ban != 3 || ban != 4)
					aux = atof(arr);/*funcion que convierte arr en float*/
					
									
				if(ban==0)
					ptrNuevo->temp = aux;
						
					
				if(ban==1)
					ptrNuevo->hum = aux;
						
				
				if(ban==2)
					ptrNuevo->pres = aux;
				
				
				
				if(ban==3)
					strcpy(ptrNuevo->hora, arr);
					
					
				if(ban==4)
					strcpy(ptrNuevo->fecha, arr);	
						
						
								
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

int archivo_usuario(ptrNodo ptrS)
{
	FILE *archivo;
	char nombre[30]; //cadena que va a almacenar el nombre del archivo
	
	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	
	
	int i = 0; //iterador
	
	int t, h, p;       //en estas variables se guarda la posicion del nodo en donde se registro el ultimo MAYOR
	float t_ma, h_ma, p_ma;       //en estas variables se guarda el ultimo MAYOR dato registrado 
	char h_t_ma[6], h_h_ma[6], h_p_ma[6];      //en estas cadenas se guarda la hora en donde se registro el ultimo MAYOR
	char f_t_ma[6], f_h_ma[6], f_p_ma[6];      //en estas cadenas se guarda la fecha en donde se registro el ultimo MAYOR
	
	int t2, h2, p2;        //en estas variables se guarda la posicion del nodo en donde se registro el ultimo MENOR
	float t_me, h_me, p_me;       //en estas variables se guarda el ultimo MENOR dato registrado 
	char h_t_me[6], h_h_me[6], h_p_me[6];      //en estas cadenas se guarda la hora en donde se registro el ultimo MENOR
	char f_t_me[6], f_h_me[6], f_p_me[6];      //en estas cadenas se guarda la fecha en donde se registro el ultimo MENOR
	
	
	
	printf("\nIngrese el nombre que desee ponerle al archivo: ");
    	scanf("%[^\n]",nombre);
    			
	archivo = fopen(nombre, "w");
		
	if(archivo == NULL)
	{
		printf("\nNo se pudo crear el archivo.\n");
		return 0;
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
				fprintf(archivo,"\t%s",ptrActual->fecha);
				
				if(t == i)//algoritmo para guardar la MAYOR temperatura, hora y fecha en su respectiva variable
				{
					t_ma = ptrActual->temp;
					strcpy( h_t_ma, ptrActual->hora );
					strcpy( f_t_ma, ptrActual->fecha );
				}
			
				if(h == i) //algoritmo para guardar la MAYOR humedad, hora y fecha en su respectiva variable
				{
					h_ma = ptrActual->hum;
					strcpy( h_h_ma, ptrActual->hora );
					strcpy( f_h_ma, ptrActual->fecha );
				}
			
				if(p == i) //algoritmo para guardar la MAYOR presion, hora y fecha en su respectiva variable
				{
					p_ma = ptrActual->pres;
					strcpy( h_p_ma, ptrActual->hora );
					strcpy( f_p_ma, ptrActual->fecha );
				}
			
			
				if(t2 == i)//algoritmo para guardar la MENOR temperatura,hora y fecha en su respectiva variable
				{
					t_me = ptrActual->temp;
					strcpy( h_t_me, ptrActual->hora );
					strcpy( f_t_me, ptrActual->fecha );
				}
			
				if(h2 == i) //algoritmo para guardar la MENOR humedad,hora y fecha en su respectiva variable
				{
					h_me = ptrActual->hum;
					strcpy( h_h_me, ptrActual->hora );
					strcpy( f_h_me, ptrActual->fecha );
				}
			
				if(p2 == i) //algoritmo para guardar la MENOR presion,hora y fecha en su respectiva variable
				{
					p_me = ptrActual->pres;
					strcpy( h_p_me, ptrActual->hora );
					strcpy( f_p_me, ptrActual->fecha );
				}
			
				ptrAnterior = ptrActual;
				ptrActual = ptrAnterior->ptrSig;
				
				i++;		
			}
			
			
			fprintf(archivo,"\n\nLa mayor temperatura registrada es %.2f y la ultima hora en la que se registro "
		     	 		 "fue a las %s hs el dia %s ",t_ma, h_t_ma, f_t_ma);
		       
			fprintf(archivo,"\nLa mayor humedad registrada es %.2f y la ultima hora en la que se registro "
		      		 	"fue a las %s hs el dia %s",h_ma, h_h_ma, f_h_ma);
		
			fprintf(archivo,"\nLa mayor presion registrada es %.2f y la ultima hora en la que se registro "
			  		"fue a las %s hs el dia %s",p_ma, h_p_ma, f_p_ma);
		       
		       
			fprintf(archivo,"\n\nLa menor temperatura registrada es %.2f y la ultima hora en la que se registro "
		       			"fue a las %s hs el dia %s",t_me, h_t_me, f_t_me);
		       
			fprintf(archivo,"\nLa menor humedad registrada es %.2f y la ultima hora en la que se registro "
		   			"fue a las %s hs el dia %s",h_me, h_h_me, f_h_me);
		
			fprintf(archivo,"\nLa menor presion registrada es %.2f y la ultima hora en la que se registro "
		       			"fue a las %s hs el dia %s",p_me, h_p_me, f_p_me);
		

		
		}
		else
		{
			fprintf(archivo,"\nNo hay ningun dato que poner en el archivo.\n");
		}
					
		fclose(archivo);
		
	}


	return 1; //si todo funciono bien
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
	char f_t_ma[6], f_h_ma[6], f_p_ma[6];      //en estas cadenas se guarda la fecha en donde se registro el ultimo MAYOR
	
	int t2, h2, p2;        //en estas variables se guarda la posicion del nodo en donde se registro el ultimo MENOR
	float t_me, h_me, p_me;       //en estas variables se guarda el ultimo MENOR dato registrado 
	char h_t_me[6], h_h_me[6], h_p_me[6];      //en estas cadenas se guarda la hora en donde se registro el ultimo MENOR
	char f_t_me[6], f_h_me[6], f_p_me[6];      //en estas cadenas se guarda la fecha en donde se registro el ultimo MENOR
	
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
			printf("\t%s",ptrActual->fecha);
			
			if(t == i)//algoritmo para guardar la MAYOR temperatura, hora y fecha en su respectiva variable
			{
				t_ma = ptrActual->temp;
				strcpy( h_t_ma, ptrActual->hora );
				strcpy( f_t_ma, ptrActual->fecha );
			}
			
			if(h == i) //algoritmo para guardar la MAYOR humedad, hora y fecha en su respectiva variable
			{
				h_ma = ptrActual->hum;
				strcpy( h_h_ma, ptrActual->hora );
				strcpy( f_h_ma, ptrActual->fecha );
			}
		
			if(p == i) //algoritmo para guardar la MAYOR presion, hora y fecha en su respectiva variable
			{
				p_ma = ptrActual->pres;
				strcpy( h_p_ma, ptrActual->hora );
				strcpy( f_p_ma, ptrActual->fecha );
			}
			
			
			if(t2 == i)//algoritmo para guardar la MENOR temperatura,hora y fecha en su respectiva variable
			{
				t_me = ptrActual->temp;
				strcpy( h_t_me, ptrActual->hora );
				strcpy( f_t_me, ptrActual->fecha );
			}
			
			if(h2 == i) //algoritmo para guardar la MENOR humedad,hora y fecha en su respectiva variable
			{
				h_me = ptrActual->hum;
				strcpy( h_h_me, ptrActual->hora );
				strcpy( f_h_me, ptrActual->fecha );
			}
			
			if(p2 == i) //algoritmo para guardar la MENOR presion,hora y fecha en su respectiva variable
			{
				p_me = ptrActual->pres;
				strcpy( h_p_me, ptrActual->hora );
				strcpy( f_p_me, ptrActual->fecha );
			}
			
						
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i++;		
		}
					
		printf("\n\nLa mayor temperatura registrada es %.2f y la ultima hora en la que se registro "
		     	 		 "fue a las %s hs el dia %s ",t_ma, h_t_ma, f_t_ma);
		       
		printf("\nLa mayor humedad registrada es %.2f y la ultima hora en la que se registro "
		      		 	"fue a las %s hs el dia %s",h_ma, h_h_ma, f_h_ma);
		
		printf("\nLa mayor presion registrada es %.2f y la ultima hora en la que se registro "
			  		"fue a las %s hs el dia %s",p_ma, h_p_ma, f_p_ma);
		       
		       
		printf("\n\nLa menor temperatura registrada es %.2f y la ultima hora en la que se registro "
		       			"fue a las %s hs el dia %s",t_me, h_t_me, f_t_me);
		       
		printf("\nLa menor humedad registrada es %.2f y la ultima hora en la que se registro "
		   			"fue a las %s hs el dia %s",h_me, h_h_me, f_h_me);
		
		printf("\nLa menor presion registrada es %.2f y la ultima hora en la que se registro "
		       			"fue a las %s hs el dia %s",p_me, h_p_me, f_p_me);
		
	}
	else
	{
		printf("\nNo hay ningun dato que mostrar.\n");
	}
		
}



/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 8*/

void grafico_temp(ptrNodo ptrS, int cant_nodos)
{
	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	float temp[cant_nodos];
	int i = 0; //iterador
	
	char programa[2000] = "python3 test_tem.py ";
	char datos[30];
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	

	if(ptrActual != NULL)
	{
		
		while(ptrActual != NULL)
		{
			
			temp[i] = ptrActual->temp;
			
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i++;		
		}
							
	}
	else
	{
		printf("\nNo hay ningun dato que mostrar en el grafico.\n");
	}


	for(int j = 0; j < cant_nodos; j++)
	{
		sprintf(datos," %2.2f ",temp[j]);
		strcat(programa, datos);
	}	

	system(programa);




}

/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 9*/

void grafico_hum(ptrNodo ptrS, int cant_nodos)
{
	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	float hum[cant_nodos];
	int i = 0; //iterador
	
	char programa[2000] = "python3 test_hum.py ";
	char datos[30];
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	

	if(ptrActual != NULL)
	{
		
		while(ptrActual != NULL)
		{
			
			hum[i] = ptrActual->hum;
			
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i++;		
		}
							
	}
	else
	{
		printf("\nNo hay ningun dato que mostrar en el grafico.\n");
	}


	for(int j = 0; j < cant_nodos; j++)
	{
		sprintf(datos," %2.2f ",hum[j]);
		strcat(programa, datos);
	}	

	system(programa);




}

/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 10*/

void grafico_pres(ptrNodo ptrS, int cant_nodos)
{
	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	float pres[cant_nodos];
	int i = 0; //iterador
	
	char programa[2000] = "python3 test_pre.py ";
	char datos[30];
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	

	if(ptrActual != NULL)
	{
		
		while(ptrActual != NULL)
		{
			
			pres[i] = ptrActual->pres;
			
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;
			
			i++;		
		}							
	}
	else
	{
		printf("\nNo hay ningun dato que mostrar en el grafico.\n");
	}


	for(int j = 0; j < cant_nodos; j++)
	{
		sprintf(datos," %2.2f ",pres[j]);
		strcat(programa, datos);
	}	

	system(programa);




}

/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 11*/

int lineas()
{
	FILE *archivo; 
	
	
	int lineass = 0;
	char c;
	
	/*se abre el archio donde estan guardados los datos obtenidos por los sensores*/
	archivo = fopen("datos.txt","r"); 
	if(archivo == NULL )
	{
	    	printf("\nNo se pudo abrir el archivo");
	}
	else
	{
	    while((c = fgetc(archivo)) != EOF)
		{
			
			if(c == '\n')
				lineass++;
		}
	}

	return lineass;
}


/*---------------------------------------------------------------------------------------------------------------------------*/

/*FUNCION 12*/

void rango(int tipo, int comparacion, int ma_o_me)
{
	ptrNodo ptrAnterior;
	ptrNodo ptrActual;
	
	ptrActual = ptrS;
	ptrAnterior = NULL;
	
	if(ma_o_me == 1)	
		printf("\n\nLOS VALORES QUE ESTAN POR ENCIMA DE %i SON :",comparacion);
	else
		printf("\n\nLOS VALORES QUE ESTAN POR DEBAJO DE %i SON :",comparacion);
	
	
	if(ptrActual != NULL)
	{		
		while(ptrActual != NULL)
		{	
			if(ptrActual->temp		
			ptrAnterior = ptrActual;
			ptrActual = ptrAnterior->ptrSig;	
		}							
	}
	else
	{
		printf("\nNo hay ningun dato.\n");
	}	

}


/*---------------------------------------------------------------------------------------------------------------------------*/

/*MENU*/

void menu(int cant)
{

	ptrNodo ptrInicial = NULL;
	ptrNodo ptrFinal = NULL;

	int opcion; //para manejar las opciones en el do while
	

	printf("\nCant_nodos = %i \n",cant);

	for(int i = 0; i<cant; i++)
		ingresar_cola(&ptrInicial, &ptrFinal,i);
		
	
	do{
		printf("\n1)Ver los datos obtenidos por los sensores."
		       "\n2)Guardar los datos obtenidos en un archivo."
		       "\n3)Ver el grafico de temperatura."
		       "\n4)Ver el grafico de presion."
		       "\n5)Ver el grafico de humedad.
		       "\n6)Analisis profundo."
		       "\n7)Salir.\n");
	       
		scanf("%i", &opcion);
		
		getchar(); //para el '\n' que queda en el buffer cuando se elije una opcion
		
		if(opcion > 7 || opcion < 1)
			printf("\nEL CARACTER INGRESADO NO CORRESPONDE A UNA OPCION VALIDA. INTENTELO DE NUEVO.\n");
		
		switch(opcion)
		{
			case 1:  mostrar(ptrInicial);  printf("SE MUESTRAN LAS OPCIONES NUEVAMENTE\n");        break;
			
			case 2:  if(archivo_usuario(ptrInicial) == 1)
					printf("\nArchivo guardado correctamente.\n\n");
				
				 printf("SE MUESTRAN LAS OPCIONES NUEVAMENTE\n"); break;
				 
				 
			case 3:  grafico_temp(ptrInicial,cant);   break;
			case 4:  grafico_pres(ptrInicial,cant);   break;
			case 5:  grafico_hum(ptrInicial,cant);    break;
			
			case 6:  do{ 	int op;
					int num;
					char val;
					
				 	printf("\n\t¿Que desea analizar?\n\t1)Temperatura.\n\t2)Presion.\n\t3)Humedad.\n");
				 	scanf("%i",&op);
				 	
				 	getchar(); //para el '\n' que queda en el buffer cuando se elije una opcion
				 	
				 	if(op > 3 || op < 1)
					printf("\n\tCARACTER INVALIDO. INTENTELO DE NUEVO.\n");
					
					printf("\n\t\tIngrese el numero con el cual va a comprar los valores:");
					scanf("%i",&num);
					
					printf("\n\t\tPresione 'u' para ver los valores por encima del valor ingresado
					       " y 'd' para ver los valores por debajo del valor ingresado: ");
					scanf("%c",&val);
					
					if(op >=1 && op <= 3) //si la opcion ingresada es la correcta
					{
					
						if(val == 'u')
							rango(op,num, 1);
						else 
							rango(op, num, 0);
					}
					
					
				}while(op != 3);
				 
			
			
			
			case 7: printf("\nCerrando programa...\n"); break;
						
			default: ;
		}
		
		}while(opcion != 7);


}






















































