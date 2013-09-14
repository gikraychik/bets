#! /bin/bash
#! /bin/bash
echo "*************************************Bets extraction*************************************"
cd scripts/
mkdir -p tmp/
mkdir -p logs/
bash wget.sh http://www.marathonbet.com/ru/betting/Football/
bash delspaces.sh tmp/result.html tmp/nospaces.html
echo "Extraction started..."
grep -o '<div class="[t]*[o]*[d]*[a]*[y]*[-]*member-name">[^<]*</div>' < tmp/nospaces.html | sed -e 's/<div class="[t]*[o]*[d]*[a]*[y]*[-]*member-name">\([^<]*\)<\/div>/\1/g' >commands
grep -o '<td class="date">[^<]*</td>' <tmp/nospaces.html  | sed -e 's/<td class="date">\([^<]*\)<\/td>/\1/g' >dates
grep -o '<span class="selection-link coeff[^"]*">[^<]*</span>' <tmp/nospaces.html | sed -e 's/<span class="selection-link coeff[^"]*">\([^<]*\)<\/span>/\1/g' > coeff
grep -o -n '<td class="js-price' < tmp/result.html | sed -e 's/^\([0-9][0-9]*\).*/\1/g' > filled
grep -o -n 'td-min-width' < tmp/result.html | sed -e 's/^\([0-9][0-9]*\).*/\1/g' > empty
.././merge.out
grep -o '(\([0-9.-+][0-9.-+]*\))<br/>' < tmp/result.html | sed -e 's/(\([0-9\.-+][0-9\.-+]*\))<br\/>/\1/g' > bonuses

comm=$(cat commands | wc -l)
coeff=$(cat new_coeff | wc -l)
sum=$((5*$comm))
cd ../data
d=$(date +%F)
t=$(date +%H:%M:%S)
if [ "$sum" -ne "$coeff" ]
then
	echo "Error accured! Control sum differs."
	rm new_coeff
	exit 1
fi
cd marathonbet.com
mkdir -p "$d"/"$t/marathonbet.com/"
cd "$d"/"$t/marathonbet.com/"
mv ../../../../scripts/commands commands
mv ../../../../scripts/new_coeff coeff
mv ../../../../scripts/bonuses bonuses
cd ../../../../scripts/

echo "Extraction finished."
echo "Done."
