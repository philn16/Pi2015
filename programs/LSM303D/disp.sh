#!/bin/sh
address='0x1d'
A0=$1
if [ ! -z $A0 ]; 
then
if [ $A0 == 'a' ];
then
i2cdump -y 1 $address
fi
if [ $A0 == 'b' ];
then
i2cdump -y -r 0x28-0x2d 1 $address
fi
else
i2cdump -y -r 0x28-0x2d 1 $address
fi
