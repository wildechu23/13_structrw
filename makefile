all: structrw.o
	gcc -o structrw structrw.o

structrw.o: structrw.c
	gcc -c structrw.c

run:
	./structrw
