




void ingresar_cola(ptrNodo *ptrS, ptrNodo *ptrF )
{
	ptrNodo ptrActual;
	ptrNodo ptrNuevo;
	ptrNodo ptrFinal;
	int dato;



	ptrNuevo = (ptrNodo)malloc(sizeof(NODO));//se crea espacio para el nodo
	ptrActual = *ptrS;
	ptrFinal = *ptrF;

	if(ptrNuevo != NULL)//si se pudo crear el espacio entra
	{
    		
    		/*ACA VA LA FUNCION QUE LEE EL ARCHIVO Y GUARDA LOS DATOS EN EL NODO*/
    		
    		
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

