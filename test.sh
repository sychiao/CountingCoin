#!/usr/bin/env bash
exe=orgin/CountingCoin_CU_LLVM
total=.total
bd=.breakdown
out=out.csv
count=5

set -x

echo "Hello User please enter the title name of the data"
read title
echo $title >> $out
echo "Overhead,Erode,Dilate,Canny,Hough,cleanup,Total" >> $out

while [ $count -gt 0 ];
do
count=$(($count-1))

/usr/bin/time -f'%e' -o $total  ./$exe &> $bd

data=`cat $bd`
for i in $data
do
    echo -n $i >> $out
    echo -n "," >> $out
done
cat $total >> $out
sleep 1
done

echo "" >> $out
echo "" >> $out
rm -f $total $bd
