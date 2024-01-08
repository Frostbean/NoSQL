# Makefile for a C project with multiple static libraries

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-L.
LIBS=-linput -lcommand -ldb -llink -lalloc
TARGET=libdatabase.so
OBJECT = alloc.o link.o input.o db.o command.o
LIBRARY = libdatabase.so

.PHONY: all clean

all: $(OBJECT) $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) -shared $(CFLAGS) -o $(TARGET) $(OBJECT)

.c.o:
	$(CC) -fPIC $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(LIBRARY) $(OBJECT)
