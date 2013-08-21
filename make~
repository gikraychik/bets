#! /bin/bash
echo "*************************************Bets extraction*************************************"
cd scripts/
mkdir -p tmp/
mkdir -p logs/
bash wget.sh http://ru.leonbets.com/
bash delspaces.sh tmp/result.html tmp/nospaces.html
bash extract.sh
d=$(date +%F)
t=$(date +%H:%M:%S)
mkdir -p ../data/"$d"/"$t"
#Next follows data download
mkdir -p tmp/downloads
cd tmp/downloads/
echo "Starting download of files. It will take much time..."
wget -i ../addr -a ../../logs/wget_log
echo "Download complete."
echo "---------------------------------------------------------------------------"
echo "Data extraction started..."
#Next follows the data extraction
x="0"
for name in *
do
	bash ../../delspaces.sh "$name" temp
	mv temp "$name"
	if [ -f "$name" ]
	then
		grep -o '<h1>[^<]*</h1>' $name | sed -e 's/<h1>\([^<]*\)<\/h1>/\1/g' >../name.txt
		y=$(cat ../name.txt)
		mkdir -p ../../../data/"$d"/"$t"/"$y"
		#grep -o '<a[[:space:]]*href="[^"]*"[[:space:]]*class="nou2">[[:space:]]*[^<]*</a>' "$name" | sed -e 's/<a[[:space:]]*href="[^"]*"[[:space:]]*class="nou2">[[:space:]]*\([^<]*\)<\/a>/\1/g' >../../../data/"$d"/"$t"/"$y"/"$x"
		grep -o '<tr class="row1">[[:space:]]*<td><script>[^<]*</script></td>[[:space:]]*<td[[:space:]]*width="[^"]*">[[:space:]]*<strong>[[:space:]]*<a href="[^"]*" class="nou2">[[:space:]]*\([^<]*\)</a>[[:space:]]*</strong>[[:space:]]*</td>[[:space:]]*<td [^<]*<a[^<]*<strong>\([^<]*\)</strong></a>[[:space:]]*[^/]*/span></td>[[:space:]]*<td [^<]*<a[^<]*<strong>\([^<]*\)</strong></a>[[:space:]]*[^/]*/span></td>[[:space:]]*<td [^<]*<a[^<]*<strong>\([^<]*\)</strong></a>[[:space:]]*[^/]*/span></td>' "$name" >../tempor
		amount=$(wc -l ../tempor | sed -e 's/\([^ ]*\) .*/\1/g')
		i="1"
		while (( $i < $amount))
		do
			tail -n 1 <../tempor | sed -e 's/<tr class="row1">[[:space:]]*<td><script>[^<]*<\/script><\/td>[[:space:]]*<td[[:space:]]*width="[^"]*">[[:space:]]*<strong>[[:space:]]*<a href="[^"]*" class="nou2">[[:space:]]*\([^<]*\)<\/a>[[:space:]]*<\/strong>[[:space:]]*<\/td>[[:space:]]*<td [^<]*<a[^<]*<strong>\([^<]*\)<\/strong><\/a>[[:space:]]*[^\/]*\/span><\/td>[[:space:]]*<td [^<]*<a[^<]*<strong>\([^<]*\)<\/strong><\/a>[[:space:]]*[^\/]*\/span><\/td>[[:space:]]*<td [^<]*<a[^<]*<strong>\([^<]*\)<\/strong><\/a>[[:space:]]*[^\/]*\/span><\/td>/\1\n\2\n\3\n\4/g' >../../../data/"$d"/"$t"/"$y"/"$i"
			head -n -1 <../tempor >../headfile
			mv ../headfile ../tempor
			i=$(($i+1))
		done
		x=$(($x + 1))
	fi
done
echo "Data extraction done."
echo "---------------------------------------------------------------------------"
echo "Cleaning..."
#Next follows cleaning
cd ../../../
rm -r scripts/tmp
for x in data/"$d"/"$t"/*
do
	rmdir --ignore-fail-on-non-empty "$x"
done
echo "Done."
