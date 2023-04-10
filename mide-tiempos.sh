#!/bin/bash 
#echo "" >> salida.dat
i=50000
while [ "$i" -le 500000 ]
do
    ./Especifico data.txt $i >> salidaE.dat
      i=$(( $i + 50000 ))
done
      
