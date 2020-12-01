TARGET = test
OBJECT = test.o symbolTable.o
CC = gcc -g

all: test
	./$(TARGET)

memtest: test
	# TODO: modify for linux later
	leaks -atExit -- ./$(TARGET)

test: test.o symbolTable.o
	$(CC) -o $(TARGET) test.o symbolTable.o

test.o: test.c
	$(CC) -c test.c

symbolTable.o: symbolTable.c
	$(CC) -c symbolTable.c

clean:
	rm -f $(TARGET) $(OBJECT)

