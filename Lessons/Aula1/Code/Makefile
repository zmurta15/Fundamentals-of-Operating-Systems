lab-03: myMain.o  mySin.o
	gcc -o lab-03 myMain.o  mySin.o -lm

mySin.o:  mySin.c
	gcc -Wall -c mySin.c -lm

myMain.o:  myMain.c
	gcc -Wall -c myMain.c

clean:
	rm -f myMain.o mySin.o lab-03
