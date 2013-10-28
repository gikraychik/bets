#! /bin/bash
echo "Processing leonbets.com"
# d - date, first parametr
# t - time, second parametr
d=$1 
t=$2

mkdir -p ../data/$d/$t/leonbets.com/
touch ../data/$d/$t/leonbets.com/log.txt
echo "Extracting data"
./leonbets.py $d $t  
echo "Successfully extracted"
echo "leonbets.com is done"
