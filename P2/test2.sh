#Cabecera no necesaria en ARCH??
#!/bin/bash

#a) Copie dos ficheros de texto que ocupen más de un boque (por ejemplo fuseLib.c y
#   myFS.h) a nuestro SF y a un directorio temporal, por ejemplo ./copiasTemporales
echo Copiando ficheros en /punto-montaje/copiasTemporales...
cp /src/fuseLib.c  /punto-montaje
cp /src/myFS.h     /punto-montaje
cp /src/fuseLib.c  /copiasTemporales
cp /src/myFS.h     /copiasTemporales

#b) Audite el disco y haga un diff entre los ficheros originales y los copiados en el SF
#   Trunque el primer fichero (man truncate) en copiasTemporales y en nuestro SF de
#   manera que ocupe un bloque de datos menos.
#if ./audita disco-virtual; then
    #diff /test/fichero1.txt /punto-montaje/fichero1.txt
    #if $? != 1 
#else
#    echo Error auditando disco-virtual
#fi


#c) Audite el disco y haga un diff entre el fichero original y el truncado.
./audita disco-virtual

#d) Copie un tercer fichero de texto a nuestro SF.
cp /src/fuseLib.h /punto-montaje

#e) Audite el disco y haga un diff entre el fichero original y el copiado en el SF
./audita disco-virtual
diff /src/fuseLib.h /punto-montaje/fuseLib.h

#f) Trunque el segundo fichero en copiasTemporales y en nuestro SF haciendo que
#   ocupe algún bloque de datos más.


#g) Audite el disco y haga un diff entre el fichero original y el truncado










