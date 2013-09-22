#! /bin/bash
echo "Processing marathonbet.com."
cd scripts/
mkdir -p tmp/
mkdir -p logs/
bash wget.sh http://www.marathonbet.com/ru/betting/Football/ tmp
bash delspaces.sh tmp/result.html tmp/nospaces.html
echo "Extraction started..."
grep -o '<div class="[t]*[o]*[d]*[a]*[y]*[-]*member-name">[^<]*</div>' < tmp/nospaces.html | sed -e 's/<div class="[t]*[o]*[d]*[a]*[y]*[-]*member-name">\([^<]*\)<\/div>/\1/g' >commands
grep -o '<td class="date">[^<]*</td>' <tmp/nospaces.html  | sed -e 's/<td class="date">\([^<]*\)<\/td>/\1/g' >dates
grep -o '<span class="selection-link coeff[^"]*">[^<]*</span>' <tmp/nospaces.html | sed -e 's/<span class="selection-link coeff[^"]*">\([^<]*\)<\/span>/\1/g' > coeff
grep -o -n '<td class="js-price' < tmp/result.html | sed -e 's/^\([0-9][0-9]*\).*/\1/g' > filled
grep -o -n 'td-min-width' < tmp/result.html | sed -e 's/^\([0-9][0-9]*\).*/\1/g' > empty
grep -o '(\([-0-9\.+][-0-9\.+]*\))<br/>' < tmp/result.html | sed -e 's/(\([-0-9\.+][-0-9\.+]*\))<br\/>/\1/g' > bonuses
grep -o -n '(\([-0-9\.+][-0-9\.+]*\))<br/>' < tmp/result.html | sed -e 's/^\([0-9][0-9]*\).*/\1/g' > bon_num
cd ../marathonbet.com/
./merge.out
cd ../scripts/
dates=$(cat dates | wc -l)
comm=$(cat commands | wc -l)
coeff=$(cat new_coeff | wc -l)
bonuses=$(cat new_bonuses | wc -l)
sum=$((2*$dates))
cd ../data
d=$(date +%F)
t=$(date +%H:%M:%S)
res=$((1))
if [ "$sum" -ne "$comm" ]
then
	$res=0
fi
sum=$((4*$dates))
if [ "$sum" -ne "$bonuses" ]
then
	res=0
fi
sum=$((10*$dates))
if [ "$sum" -ne "$coeff" ]
then
	res=0
fi
un=$((1))
if [ "$res" -ne "$un" ]
then
	echo "Error accured! Control sum differs. $d $t" >> ../scripts/logs/diffsum
	echo "Error accured! Control sum differs! $d $t";
	exit 1
fi
mkdir -p "$d"/"$t/marathonbet.com/"
cd "$d"/"$t/marathonbet.com/"
mv ../../../../scripts/commands commands
mv ../../../../scripts/new_coeff coeff
mv ../../../../scripts/new_bonuses bonuses
mv ../../../../scripts/dates dates
cd ../../../../scripts/
rm coeff empty filled
rm bon_num bonuses
rm -r tmp/

echo "Extraction finished."
echo "marathonbet.com is done."
