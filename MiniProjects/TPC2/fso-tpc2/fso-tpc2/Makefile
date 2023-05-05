
CC=gcc
 
CFLAGS = -Wall -g
OBJ = main.o matrix.o log.o 

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

parmatmul: $(OBJ)
	$(CC) -o $@ $^ -pthread

clean:
	rm -rf $(OBJ)

cleanall: clean
	rm -rf parmatmul