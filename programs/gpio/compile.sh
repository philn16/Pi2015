#!/bin/sh
if [ ! -z $1 ] ; then
v1=$1
if [ -z $2 ] ; then # if it doesn't exist
v2=$v1
else
v2=$2
fi

if [ $v1 == 'r' ] || [ $v2 == 'r' ] ; then
if [ $v1 != $v2 ] ; then
echo "Compiling read"
fi
g++ gpio_read_test.cpp -o read
fi
if [ $v1 == 'w' ] || [ $v2 == 'w' ] ; then
if [ $v1 != $v2 ] ; then
echo "Compiling write"
fi
g++ gpio_write_test.cpp -o write
fi

else
echo "Nothing to do"
echo "Add r | w to the end of the thing"
fi #Final fi