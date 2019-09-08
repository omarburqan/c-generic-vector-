TARGET=main

# all .c files in this directory are my sources
SOURCES=$(wildcard *.c)

OBJS=$(SOURCES:.c=.o)

INC_DIR=../include
CC=gcc
LDFLAGS= -g

CFLAGS= -c -Wall -ansi $(LDFLAGS) -pedantic  -Werror -Wconversion -D_DEBUG -I$(INC_DIR)
CXXFLAGS=$(CFLAGS)


.PHONY: clean run gdb

$(TARGET): $(OBJS)


include .depends

.depends:
	$(CC) -MM -I$(INC_DIR) $(SOURCES) > .depends

clean:
	rm -f $(OBJS) $(TARGET) .depends

run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb -q ./$(TARGET)

leak:
	valgrind  ./$(TARGET) --leak-check=full
	
open:
	gedit vector.c vector.h test.h test.c main.c &
	
