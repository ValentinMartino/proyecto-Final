# include <stdio.h> /* Standard input / output definitions */
# include <fcntl.h> /* File control definitions */
# include <unistd.h> /* UNIX standard function definitions */
# include "termset.h"

int main ( void )
{
  int fd ; /* Descriptor de archivo del puerto */
  char leido_1 [6], leido_2[6]; /*caracter para tomar los datos obtenidos del puerto serie*/
  char basura [6];


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

     archivo = fopen("Temperaturas.txt", "w");
		
     if(archivo == NULL)
       {
	 printf("\nNo se pudo crear el archivo.\n");
	 return -1;
       }

     tcflush ( fd , TCIOFLUSH );

     fprintf(archivo,"A continuacion se muestran las temperaturas listadas");

     //ciclo infinito
     for (int i = 0; i<5; i++)
       {
	 if(i==0)
	   read(fd, basura, 6);
	 else
	   {
	     read(fd, leido_1, 6);
	     // read(fd, leido_2, 6);

	     //ingresamos las temperaturas al archivo de texto que creamos
	 
	     //	 fprintf(archivo,"\n- %s ", leido_1);
      
	     printf("\ntemp = %s ",leido_1);
	     // printf("\nhum = %s",leido_2);
	   }
	 tcdrain (fd);
      
	 sleep (5);
       }

     fclose(archivo); //cerramos el archivo de texto
     close (fd);
     return 0;
}
