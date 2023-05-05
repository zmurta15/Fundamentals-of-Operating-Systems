
CC=gcc
 
CFLAGS = -Wall -g
OBJ = main.o matrix.o parmatmul.o

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

parmatmul: $(OBJ)
	$(CC) -o $@ $^ 

clean:
	rm -rf $(OBJ)