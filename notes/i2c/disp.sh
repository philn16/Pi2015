#!/bin/sh
A0=$1
if [ ! -z $A0 ]; 
then
if [ $A0 == 'a' ];
then
i2cdump -y 1 0x77
fi
if [ $A0 == 'b' ];
then
i2cdump -y -r 0x80-0x81 1 0x77
fi
else
i2cdump -y -r 0x80-0x80 1 0x77
fi
