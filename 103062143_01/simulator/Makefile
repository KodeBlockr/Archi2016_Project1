CC = gcc -Wall
SRCS = ./*.c
OBS = ./*.o

single_cycle: SRC
	$(CC) -o $@ $(OBS)

SRC: $(SRCS)
	$(CC) -c $(SRCS)

clean: $(OBS)
	rm $(OBS) single_cycle
