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

# HW6
Hash Type Processing
* HSET
* HGET
* HDEL

# HW5
Sorted Set Type Processing
* ZADD
* ZCARD
* ZCOUNT
* ZINTERSTORE - dev
* ZUNIONSTORE - dev
* ZRANGE
* ZRANGEBYSCORE
* ZRANK
* ZREM - dev
* ZREMBYSCORE - dev

# How to use (new)
make
gcc main.c -L. -ldatabase -o main
LD_LIBRARY_PATH=. ./main

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

gcc -c -fPIC -o murmurhash.o murmurhash.c
gcc -shared -Wl,-soname,libmurmurhash.so.1 -o murmurhash.so.1.0.0 murmurhash.o
ln -s libmurmurhash.so.1.0.0 libmurmurhash.so
ln -s libmurmurhash.so.1.0.0 libmurmurhash.so.1
<!-- gcc main.c -L. -lmurmurhash -o main_dynamic -->

gcc main.c -L. -linput -lcommand -ldb -llink -lalloc && ./a.out

Note: link between libraries can be better organized
Bug: strcmp has different result on ubuntu and windows
Bug: Values sometimes mess up. However, same operations not always lead to same result
Hint: link from the current library to later library
Bug: using valgrind can find conditional jump without initialized variable
Some memory leaks(DBfind to hash type)
Bug on second modify value on hashtable
Changeing setNode->value to setNode->member
Input not cleared