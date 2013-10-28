#! /bin/bash
echo "Processing leonbets.com"
d="2013-10-28"
t="22:10:30"

mkdir -p ../data/$d/$t/leonbets.com/
touch ../data/$d/$t/leonbets.com/log.txt
echo "Extracting data"
./leonbets.py $d $t  
echo "Successfully extracted"
echo "leonbets.com is done"
