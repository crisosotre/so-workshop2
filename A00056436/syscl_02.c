#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Bibliotecas para las llamadas al sistema */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <unistd.h>
#include <fcntl.h>

#define TAM_BUFFER 64

int main()
{
	int c_pid,archi,bytes,result;
	char buffer[TAM_BUFFER];
	/* La llamada al sistema fork() crea un proceso hijo y asigna el PID 
	 * de este a la variable "c_pid" del proceso padre. En el proceso 
	 * hijo la variable c_pid toma el valor de 0.
	 * Si no se pudo crear el proceso, la funcion retornara -1. */ 
	c_pid = fork();
	/* Si c_pid<0 significa que el proceso hijo no pudo ser creado. */
	if (c_pid < 0)
	{
		printf("Ha ocurrido un error al crear el proceso");
		/* La llamada al sistema exit(n) termina la ejecucion del programa
		 * retornando n, en este caso -1 indica un error. */
		 exit(-1);
	}
	/* Si c_pid==0 significa que estamos en el proceso hijo. */
	else if (c_pid==0)
	{
		/* La llamada al sistema "getpid()" retorna el pid del proceso. */
		c_pid =  getpid();
		/* El proceso hijo escribira en un archivo */
		printf("Soy el proceso hijo, mi pid es %d, ahora escribire en un archivo\n",c_pid);
		/* Se carga al buffer lo que se quiere escribir */
		strcpy(buffer,"Hola, soy el proceso hijo\n");
		/* Se intenta abrir el archivo llamado test con la llamada al 
		 * sistema "open(archivo,flags_de_permisos)". En las flags se puede
		 * usar el "|" (or de bits), en este caso usamos las flag:
		 * O_RDWR = Abre el archivo en modo lectura/escritura.
		 * O_CREAT = Crea el archivo en caso de no existir.
		 * S_IRWXU = Lectura, escritura y ejecucion para el propietario.
		 * Entonces test sera abierto o creado y ademas se le da lectura
		 * escritura al usuario propietario.
		 * La funcion devolvera un descriptor para el archivo si logra 
		 * abrirlo, en caso contrario, devolvera -1 */
		archi = open ("test", O_RDWR | O_CREAT, S_IRWXU);
		if (archi == -1) printf("No pude abrir el archivo!\n");
		else 
		{
			/* Ahora escribiremos en el archivo abierto con la llamada al
			 * sistema "write(descriptor, buffer, tamanio_del_bufer)" esta
			 * funcion nos retornara el numero de bytes escritos. */
			bytes = write(archi,buffer,strlen(buffer));
			printf("Logre escribir %d bytes!\n",bytes);
			/* Con la llamada al sistema "close(descriptor)" cerramos el 
			 * archivo. */
			close(archi);
		}
		/* Como el proceso a terminado su labor deberia cerrarse, pero lo 
		 * dejaremos colgado por el momento */
		printf("Como termine lo que tenia que hacer perdere el tiempo\n");
		/* El proceso descanzara por 30 segundos */
		sleep(30);
	}
	/* Si c_pid>0 entonces nos encontramos en el proceso padre y c_pid vale
	 * el PID del proceso hijo */
	else
	{
		/* El proceso padre esperara que el hijo termine su labor por tres 
		 * segundos, despues de esto utilizara la llamada al sistema 
		 * "kill(pid,flag)" con la flag "SIGKILL" para matar al proceso 
		 * hijo. Retorna -1 en caso de error. */
		printf("Soy el proceso padre, mi pid es %d, esperare 3 segundos que mi hijo termine su labor.\n",getpid());
		sleep(3);
		printf("Parece que mi hijo esta perdiendo el tiempo, le matare\n");
		result = kill(c_pid,SIGKILL);
		if (result=-1) printf("No logre matar a mi hijo\n");
		else printf("Mate a mi hijo!\n");
		/* Veremos que hizo el hijo, para ello abrimos el archivo en modo 
		 * solo lectura */
		printf("Ahora leere lo que escribio mi hijo\n");
		archi = open ("test", O_RDONLY);
		if (archi == -1) printf("No pude abrir el archivo!\n");
		else 
		{
			/* Ahora leeremos lo que hizo el hijo con la llamada al sistema 
			 * "read(descriptor, buffer, tamanio_del_bufer)" la cual retorna
			 * la cantidad de bytes leidos. */
			bytes = read(archi,buffer,TAM_BUFFER);
			printf("Logre leer %d bytes!\n",bytes);
			/* Cerramos el archivo */
			close(archi);
			/* Agregamos un '\0' (fin de string) al final de lo leido. */
			buffer[bytes] = '\0';
			printf("El archivo leido dice:\n%s",buffer);
		}
		/* exit(0) nos indica una finalizacion del programa exitosa */
		exit(0);
	}
}
