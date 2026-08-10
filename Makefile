CC = gcc

CFLAGS = -Wall -Wextra -std=c17 -Iinclude

SRC = src/main.c \
      src/lexer.c \
	  src/vector.c
      

TARGET = lang

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET) examples/test.lang

clean:
	rm -f $(TARGET)
