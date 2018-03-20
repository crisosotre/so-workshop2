#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	printf("Hola voy a crear un archivo \n");
	creat("archivo.txt",S_IWUSR);
	printf("El archivo ha sido creado \n");       
	return 0;
}
