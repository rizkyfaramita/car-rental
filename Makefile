all: rental

rental: rental.o simlib.o
	gcc -o rental rental.o simlib.o -lm

clean:
	rm rental.o
	rm simlib.o
	rm rental

rental.o: rental.c
	gcc -c rental.c -o rental.o -I.

simlib.o: simlib.c
	gcc -c simlib.c -o simlib.o -I.
