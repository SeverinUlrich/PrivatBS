#!/bin/sh
STEP=1
INC=0
MAX=300
while [ $INC -lt $MAX ]; do 
./a.out $INC
INC=`expr $INC + $STEP`
done