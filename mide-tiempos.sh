#!/bin/bash 
#echo "" >> salida.dat
printf "" > dyv.dat

i=50000
while [ "$i" -le 1300000 ]
do
	# Generamos los puntos	
	./generador $i
  	
	# Ejecutamos los puntos
	./dyv data.txt >> dyv.dat

	echo "Terminado $i" 
	
	i=$(( $i + 50000 ))
done
