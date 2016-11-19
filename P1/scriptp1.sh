#!/bin/bash
if test -e mitar -a -x mitar; then
	echo "Mitar existe y es ejecutable."

	if test -e tmp; then
		echo "Directorio tmp encontrado => Borrando.."
		rm -r tmp
	fi
	echo "Creando Directorio tmp.."
	mkdir tmp
	cd ./tmp
	echo "Creando Archivo uno(fich1.txt).."
	echo "Hola Mundo!" > fich1.txt
	echo "Creando Archivo dos(fich2.txt).."
	head -c 10 /etc/passwd > fich2.txt
	echo "Creando Archivo tres(fich3.dat).."
	head -c 20 /dev/random > fich3.dat

	echo "Comprimiendo en fichtar.mtar.."
	./../mitar -c -f fichtar.mtar fich1.txt fich2.txt fich3.dat
	
	mkdir out
	mv fichtar.mtar ./out/
	cd ./out

	./../../mitar -x -f fichtar.mtar
	echo "Descomprimeindo contenido de fichtar en ./out/.."	
	cd ..

	echo "Comprobando diferencias de fich1, original con el descomprimido.."
	DIFF=$(diff fich1.txt ./out/fich1.txt) 
	if [ "$DIFF" != "" ] 
	then
	  echo diff -q fich1.txt ./out/fich1.txt
	  exit 0
	else
		echo "Fich1 iguales!"
		echo "Comprobando diferencias de fich2, original con el descomprimido.."
	  	DIFF=$(diff fich1.txt ./out/fich1.txt) 
		if [ "$DIFF" != "" ] 
		then
		      echo iff -q fich2.txt ./out/fich2.txt
		      exit 0
		else	

		      echo "Fich2 iguales!"
		      echo "Comprobando diferencias de fich3, original con el descomprimido.."
		      DIFF=$(diff fich1.txt ./out/fich1.txt) 
		      if [ "$DIFF" != "" ] 
		      then
			  
			    echo diff -q fich3.dat ./out/fich3.dat
			    exit 0
		      else
			    echo "Fich3 iguales!"
			    cd ../..
			    echo "Correcto"
			    exit 1
		      fi


		fi

	fi




			
else
	echo "mitar no existe o no es ejecutable"
fi
