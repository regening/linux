CC = gcc
CFLAGS = -Wall

TARGET = ls_program
SRC = main.c ls.c

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
