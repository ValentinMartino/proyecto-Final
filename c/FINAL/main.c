#include<stdio.h>
#include"funciones.h"

int main()
{
	ptrNodo ptrInicial = NULL;
	ptrNodo ptrFinal = NULL;
	
	//NO SE SI ESTA BIEN ESTO, PORQUE LAS FUNCIONES QUE TENEMOS SON MUY ESPECIFICAS Y SOLO HACEN UNA TAREA
	
	/*printf("\n¿Desea recuperar el archivo de la ultima vez que ejecuto el programa?(s/cualquier caracter");
	scanf("%c",&c);
	if(c == 's' || c == 'S')
	{
		for(int i = 0; i<( lineas() ) ; i++)
			ingresar_cola(&ptrInicial, &ptrFinal,i);
			
		if(archivo_usuario(ptrInicial) == 1)
			printf("\nArchivo guardado correctamente.\n\n");
		
	}
	else
		printf("\nContinua la ejecucion del programa\n");*/
	
	//int cant_nodos;
	int opcion; //para manejar las opciones en el do while
	
	//cant_nodos = leer_puerto();
	
	
	for(int i = 0; i<11 ; i++)
		ingresar_cola(&ptrInicial, &ptrFinal,i);
		
	
	
	do{
		printf("\n1)Ver los datos obtenidos por los sensores."
		       "\n2)Guardar los datos obtenidos en un archivo."
		       "\n3)Ver el grafico de temperatura."
		       "\n4)Ver el grafico de presion."
		       "\n5)Ver el grafico de humedad."
		       "\n6)Salir.\n");
	       
		scanf("%i", &opcion);
		
		getchar(); //para el '\n' que queda en el buffer cuando se elije una opcion
		
		if(opcion > 6 || opcion < 1)
			printf("\nEL CARACTER INGRESADO NO CORRESPONDE A UNA OPCION VALIDA. INTENTELO DE NUEVO.\n");
		
		switch(opcion)
		{
			case 1:  mostrar(ptrInicial);  printf("SE MUESTRAN LAS OPCIONES NUEVAMENTE\n");        break;
			
			case 2:  if(archivo_usuario(ptrInicial) == 1)
					printf("\nArchivo guardado correctamente.\n\n");
				
				 printf("SE MUESTRAN LAS OPCIONES NUEVAMENTE\n"); break;
				 
				 
			case 3:  grafico_temp(ptrInicial,11);   break;
			case 4:  grafico_pres(ptrInicial,11);   break;
			case 5:  grafico_hum(ptrInicial,11);    break;
			case 6:   printf("\nCerrando programa...\n"); break;
						
			default: ;
		}
		
		}while(opcion != 6);
		

		
	putchar('\n');
	return 0;
}


