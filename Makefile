main: main.o funkcije.o
	gcc main.o funkcije.o -lm -o main
main.o: main.c
	gcc -c main.c
funkcije.o: funkcije.c
	gcc -c funkcije.c

.PHONY: clean
clean:
	rm -rf *.o *~
