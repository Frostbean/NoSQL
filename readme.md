# HW1
String Type Processing
* SET
* GET
* DEL

# HW3
List Type Processing
* LPUSH
* RPUSH
* LPOP
* RPOP
* LLEN
* LRANGE

# How to use
gcc -c alloc.c
ar rcs liballoc.a alloc.o
AND
gcc -c link.c
ar rcs liblink.a link.o
AND
gcc -c input.c
ar rcs libinput.a input.o
AND
gcc -c db.c
ar rcs libdb.a db.o
AND
gcc -c command.c
ar rcs libcommand.a command.o

gcc main.c link.o alloc.o db.o input.o command.o
OR
gcc main.c -L. -llink -lalloc -ldb -linput -lcommand [-o a.out]

gcc main.c -L. -linput -lcommand -ldb -llink -lalloc && ./a.out

Note: link between libraries can be better organized
Bug: strcmp has different result on ubuntu and windows
Bug: Values sometimes mess up. However, same operations not always lead to same result
Hint: link from the current library to later library