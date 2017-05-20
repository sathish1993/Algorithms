run:
	gcc -g strassen.c -o strassen.o -lm
	gcc -g tromino.c -o tromino.o -lm

clean:
	rm *.o
