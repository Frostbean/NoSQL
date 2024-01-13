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
* ZREM
* ZREMRANGEBYSCORE

# How to use
make
gcc main.c -L. -ldatabase -o main
LD_LIBRARY_PATH=. ./main

# Note
Note: link between libraries can be better organized
Bug: strcmp has different result on ubuntu and windows
Bug: Values sometimes mess up. However, same operations not always lead to same result
Hint: link from the current library to later library
Bug: using valgrind can find conditional jump without initialized variable
Some memory leaks(DBfind to hash type)
Bug on second modify value on hashtable
Changeing setNode->value to setNode->member
Input not cleared