#!/bin/bash 
#echo "" >> salida.dat
i=50000
while [ "$i" -le 500000 ]
do
	# Generamos los puntos	
	./generador $1
  	
	# Ejecutamos los puntos
	./especifico data.txt $i >> salidaE.dat
      i=$(( $i + 50000 ))
done
      
