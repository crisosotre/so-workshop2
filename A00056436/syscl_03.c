/*La syscall fork() crea un proceso hijo que es una copia exacta en memoria y en el estado de la CPU del padre y donde el hijo funciona de manera completamente aislada respecto a la CPU y la memoria. Podríamos decir que multiplexa el microprocesador y la RAM para que el proceso hijo tenga una virtualización de estos. Entonces resulta necesario diferenciarlos para que el padre y el hijo puedan realizar diferentes tareas y aprovechar el paralelismo. 
El process identification que devuelve la llamada al sistema los diferencia.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>	/* para tener pid_t */

int main(void)
{
        printf("Se hara una llamada al proceso fork\n");
	pid_t pid;
	pid = fork();
	printf("pid = %d\n", pid);
	return 0;
        printf("El proceso fork ha finalizando\n");
}
