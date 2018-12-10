#This is a sample makefile for our project
#Does not yet support indexer and srchindex
all: naiveinterface fileconverter create
CC= gcc

naiveinterface: naiveinterface.o input.o
	$(CC) -o naiveinterface naiveinterface.o input.o
	
naiveinterface.o: naiveinterface.c interfaceFunctions.c
	$(CC) -c naiveinterface.c
	
input.o: input.c
	$(CC) -c -std=c99 input.c
	
fileconverter: fileconverter.c
	$(CC) fileconverter.c -lm -o fileconverter
	
create: create.c
	$(CC) create.c -o create
	
#Clean target
clean:
	rm -f *.o core
	clear