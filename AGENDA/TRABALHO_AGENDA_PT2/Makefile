##### MakeFile #####

all: agenda
agenda: agenda.o sort_algo.o data_structure.o
	gcc -o agenda agenda.o sort_algo.o data_structure.o

data_structure.o:
	gcc -c data_structure.c -Wall
	
sort_algo.o:
	gcc -c sort_algo.c -Wall

agenda.o: agenda.c
	gcc -c agenda.c -Wall


