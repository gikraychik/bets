#! /bin/bash
#bash wget.sh http://ru.leonbets.com/
#bash delspaces.sh
#bash extract.sh
d=$(date +%F)
t=$(date +%H:%M:%S)
mkdir -p ../data/"$d"/"$t"
#Next follows data download
#mkdir -p tmp/downloads
cd tmp/downloads/
#echo "Starting download of files. It will take much time..."
#wget -i ../addr -a ../../logs/wget_log
#echo "Download complete."
#Next follows the data extraction
x="0"
for name in *
do
	if [ -f "$name" ]
	then
		grep -o '<h1>[^<]*</h1>' $name | sed -e 's/<h1>\([^<]\)*<\/h1>/\1/g' >../../../data/"$d"/"$t"/"$x"
		x=$(($x + 1))
	fi
done

cd ../../
