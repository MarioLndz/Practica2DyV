#!/bin/bash 
#echo "" >> salida.dat
printf "" > salidaE.dat

i=50000
while [ "$i" -le 1300000 ]
do
	# Generamos los puntos	
	./generador $i
  	
	# Ejecutamos los puntos
	./especifico data.txt >> salidaE.dat

	echo "Terminado $i" 
	
	i=$(( $i + 50000 ))
done
