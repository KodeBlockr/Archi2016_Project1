all:single_cycle
single_cycle: processor.o
	gcc processor.o -o single_cycle
processor.o: processor.c
	gcc -c processor.c -o processor.o
clean:
	rm -rf processor *.o
