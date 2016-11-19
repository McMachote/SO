#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mitar.h"

extern char *uso;

/** Copia el nBytes del fichero origen al fichero destino.
 *
 * origen: puntero al descriptor FILE del fichero origen
 * destino: puntero al descriptor FILE del fichero destino
 * nBytes: numero de bytes a copiar
 *
 * Devuelve el numero de bytes copiados o -1 en caso de error. 
 */
int copynFile(FILE *origen, FILE *destimo, int nBytes){//nBytes filtra bytes
 // Completar la funci�n


	if(origen!=NULL && destimo!=NULL){ //Comprabar ficheros

		char ch;


		int i=0;
		while( i<nBytes && (( ch = fgetc(origen) ) != EOF )){

			fputc(ch, destimo);
			i++;
		}


		return i;
	}
	else{
		exit (EXIT_FAILURE);
	}
}

/** Carga en memoria la cabecera del tarball.
 *
 * tarFile: puntero al descriptor FILE del tarball
 * header: direcci�n de un puntero que se inicializar� con la direcci�n de un
 * buffer que contenga los descriptores de los ficheros cargados.
 * nFiles: direcci�n de un entero (puntero a entero) que se inicializar� con el
 * n�mero de ficheros contenido en el tarball (primeros bytes de la cabecera).
 *
 * Devuelve EXIT_SUCCESS en caso de exito o EXIT_FAILURE en caso de error
 * (macros definidas en stdlib.h).
 */
int readHeader(FILE *tarFile, stHeaderEntry **header, int *nFiles){
// Completar la funci�n
	if(tarFile!=NULL){

		int fileSize;

		fread(nFiles,sizeof(int),1,tarFile);
		int i;
		char *buf= malloc(sizeof(char)*TAMSTRING);
		int headerIndex = sizeof(int);
		for(i = 0; i < *nFiles; i++){

			fseek(tarFile, headerIndex, SEEK_SET);
			loadstr(tarFile,&buf);

			fseek(tarFile,headerIndex+TAMSTRING,SEEK_SET);
			fread(&fileSize,sizeof(int),1,tarFile);


			header[0][i].name=(char*)malloc((strlen(buf)+1)*sizeof(char));
			strcpy(header[0][i].name, buf);
			header[0][i].size = fileSize;
			headerIndex += (TAMSTRING * sizeof(char)) + sizeof (int);
		}
		free(buf);
		return EXIT_SUCCESS;
	}else{
		exit (EXIT_FAILURE);
	}
}

/** Carga una cadena de caracteres de un fichero.
 *
 * file: direcci�n de la estructura FILE del fichero
 * buf: direcci�n del puntero en que se inicializar� con la direcci�n donde se
 * copiar� la cadena. Ser� una direcci�n del heap obtenida con malloc.
 *
 * Devuelve: 0 si tuvo exito, -1 en caso de error.
 */
int loadstr( FILE *file, char** buf ){
 // Completar la funci�n
	if(file!=NULL){

		char c='a';
		int n = 0;

		do{
			c = getc(file);

			buf[0][n] = c;
			n++;
		}while( ( (!feof(file)) && (c != '\0') ) && n < TAMSTRING);


		return 0;
	}
	else{
		return -1;
	}
}

/** crea un tarball a partir de unos ficheros de entrada.
 *
 * nfiles:    numero de ficheros de entrada
 * filenames: array con los nombres de los ficheros de entrada (rutas)
 * tarname:   nombre del tarball
 * 
 * devuelve exit_success en caso de exito y exit_failure en caso de error
 * (macros definidas en stdlib.h).
 *
 * ayuda: calcular primero el espacio necesario para la cabecera del tarball,
 * saltar dicho espacio desde el comienzo del archivo e ir copiando uno a uno
 * los ficheros, rellenando a la vez una representaci�n de la cabecera del
 * tarball en memoria. al final copiar la cabecera al comienzo del tarball.
 * recordar que  que no vale un simple sizeof de stheaderentry para saber el
 * tama�o necesario en disco para el descriptor de un fichero puesto que sizeof
 * no calcula el tama�o de la cadena apuntada por name, sino el tama�o del
 * propio puntero. para calcular el tama�o de una cadena c puede usarse la
 * funci�n strlen.
 */
int createTar(int nFiles, char *fileNames[], char tarName[]) {
	// Completar la funci�n
	int i;
	stHeaderEntry cabecera;//variable para guardar cabeceras
	FILE *current_file;
	FILE *tarFile = fopen(tarName, "wb");//"ab"->binary file. only in windows
	//putc(nFiles, tarFile);
	fwrite(&nFiles, sizeof(int), 1, tarFile);
	int headerIndex = sizeof(int); //Contador para controlar cabecera
	int fileIndex = (nFiles * ((TAMSTRING * sizeof(char)) + sizeof (int))) + sizeof(int); //COntador para controlar ficheros
	//cabeceras

	for(i = 0; i < nFiles; i++){

		fseek(tarFile, headerIndex, SEEK_SET);
		current_file = fopen(fileNames[i], "r");

		fseek(current_file, 0, SEEK_END);
		int curren_fileSize = ftell(current_file);
		rewind(current_file);

		cabecera.name=fileNames[i];
		cabecera.size=curren_fileSize;

		fwrite(cabecera.name, strlen(cabecera.name)+1, 1, tarFile); //50?
		fseek(tarFile,headerIndex+TAMSTRING,SEEK_SET);
		fwrite(&cabecera.size, sizeof(int), 1, tarFile);
		//putc(curren_fileSize, tarFile);
		//fwrite(curren_fileSize, sizeof(int), 1, tarFile);

		fseek(tarFile, fileIndex, SEEK_SET);
		copynFile(current_file, tarFile, curren_fileSize);

		fileIndex += curren_fileSize;
		headerIndex += (TAMSTRING * sizeof(char)) + sizeof (int);

		fclose(current_file);
	}

	fclose(tarFile);

	return EXIT_SUCCESS;
}

/** Extrae todos los ficheros de un tarball.
 *
 * tarName: cadena C con el nombre del tarball
 *
 * Devuelve EXIT_SUCCES en caso de exito y EXIT_FAILURE en caso de error (macros
 * definidas en stdlib.h).
 *
 * AYUDA: debemos cargar primero la cabecera, con lo que nos situaremos al
 * comienzo del primer fichero almacenado. Entonces recorriendo la cabecera
 * sabremos el nombre que debemos ir dando a los ficheros y la cantidad de bytes
 * que debemos leer del fichero para cargar su contenido.
 */
int extractTar(char tarName[]) {
	FILE * tarFile = fopen(tarName,"r");
	FILE *nuevo;
	// Completar la funci�n
	//leer numero de archivos
	char *nombre = (char *)malloc(sizeof(char) * TAMSTRING);
	int *nFiles=malloc(sizeof(int));
	//leer cabeceras
	stHeaderEntry *heads=malloc(sizeof(char)*TAMSTRING+sizeof(int));// = malloc((*nFiles)*(sizeof(char)*50));
	readHeader(tarFile, &heads,nFiles);
	//copiar archivos con cabecera
	int i=0;
	for(i=0; i < *nFiles; i++){
		strcpy(nombre, heads[i].name);
		nuevo = fopen(nombre, "w");
		copynFile(tarFile, nuevo, heads[i].size);
		free(heads[i].name);
		fclose(nuevo);
	}

	fclose(tarFile);
	//liberar heads
	free(nombre);
	free(nFiles);
	free(heads);
	return EXIT_SUCCESS;
}
  
