#!/usr/bin/env bash
#exe=
total=.total
bd=.breakdown
out=out.csv
count=5



echo "Overhead,Erode,Dilate,Canny,Hough,Total" > $out

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

#rm -f $total $bd

