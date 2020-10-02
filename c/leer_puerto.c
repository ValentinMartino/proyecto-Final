# include <stdio.h> /* Standard input / output definitions */
# include <fcntl.h> /* File control definitions */
# include <unistd.h> /* UNIX standard function definitions */
# include "termset.h"

int main ( void )
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

     archivo = fopen("temperaturas.txt", "w");
		
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
			ban = 0;
			
		printf("\n%c BAN = %i\n", basura, ban);
				
	}
		

     for (int i = 0; i<6; i++)
       {
       	
       	if(i%3 == 0 && i != 0)
         {
         	printf("\n");
         	fprintf(archivo, "\n");
         }
	 	read(fd, leido_1 , 5);

	 	fprintf(archivo,"%s\t",leido_1);
	 	printf("%s\t",leido_1);    	
       }

     fclose(archivo); //cerramos el archivo de texto
     close (fd);
     
     putchar('\n');
     return 0;
}
