all: hw18.o
	gcc -o hw18 hw18.o

hw18.o: hw18.c
		gcc -c hw18.c

run:
	./hw18

clean:
	rm *.o
	rm hw18
