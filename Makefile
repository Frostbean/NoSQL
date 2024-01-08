# Makefile for a C project with multiple static libraries

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-L.
LIBS=-linput -lcommand -ldb -llink -lalloc
TARGET=myprogram
OBJECT = alloc.o link.o input.o db.o command.o
LIBRARY = liballoc.a liblink.a libinput.a libdb.a libcommand.a

all: liballoc.a liblink.a libinput.a libdb.a libcommand.a $(TARGET)

liballoc.a: alloc.o
	ar rcs liballoc.a alloc.o

liblink.a: link.o
	ar rcs liblink.a link.o

libinput.a: input.o
	ar rcs libinput.a input.o

libdb.a: db.o
	ar rcs libdb.a db.o

libcommand.a: command.o
	ar rcs libcommand.a command.o

$(TARGET): liballoc.a liblink.a libinput.a libdb.a libcommand.a
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET) $(LIBRARY) $(OBJECT)
