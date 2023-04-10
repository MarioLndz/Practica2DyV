# Nombre archivo: Makefile
# Uso: make
# Descripción:	Construye los tres binarios de nombres generador, especifico y dyv, respectivamente.

#------------------------------------------------------------------#

# Variable que indica el compilador que se va a utilizar
CC=g++

#Variable que indica las opciones que se le va a pasar al compilador
CPPFLAGS= -Wall

# Variable que indica el directorio del proyecto Divide y Venceras
DyV_DIR= ./DivideyVenceras

# Variable que indica el directorio del proyecto Especifico
ESPEC_DIR= ./Especifico

# Variable que indica el directorio del proyecto Generador
GENERADOR_DIR= ./Generador

#------------------------------------------------------------------#

all: dyv especifico generador cleanObj

# ---------- Divide y venceras ----------

dyv: main_dyv.o punto_dyv.o $(DyV_DIR)/include/QuickSort.h
	$(CC) $(CPPFLAGS) -I $(DyV_DIR)/include -o dyv punto_dyv.o main_dyv.o

main_dyv.o: $(DyV_DIR)/src/main.cpp $(DyV_DIR)/include/QuickSort.h
	$(CC) $(CPPFLAGS) -I $(DyV_DIR)/include -c $< -o $@

punto_dyv.o: $(DyV_DIR)/src/punto.cpp $(DyV_DIR)/include/punto.h
	$(CC) $(CPPFLAGS) -I $(DyV_DIR)/include -c $< -o ./$@

# ---------- ESPECIFICO ----------

especifico: main_especifico.o punto_especifico.o $(ESPEC_DIR)/include/QuickSort.h
	$(CC) $(CPPFLAGS) -I $(ESPEC_DIR)/include -o especifico punto_especifico.o main_especifico.o

main_especifico.o: $(ESPEC_DIR)/src/main.cpp $(ESPEC_DIR)/include/QuickSort.h
	$(CC) $(CPPFLAGS) -I $(ESPEC_DIR)/include -c $< -o $@

punto_especifico.o: $(ESPEC_DIR)/src/punto.cpp $(ESPEC_DIR)/include/punto.h
	$(CC) $(CPPFLAGS) -I $(ESPEC_DIR)/include -c $< -o ./$@

# ---------- GENERADOR ----------

generador: $(GENERADOR_DIR)/generador.cpp
	$(CC) $(CPPFLAGS) $(GENERADOR_DIR)/generador.cpp -o generador

cleanObj:
	rm *.o

