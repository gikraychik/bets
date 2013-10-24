#! /bin/bash
mkdir -p data/
cd scripts/
mkdir -p tmp1/
mkdir -p logs/
d=$(date +%F)
t=$(date +%H:%M:%S)
bash wget.sh "http://www.marathonbet.com/ru/results.htm?form_name=form&Football=on&dateFilterSelector=YESTERDAY&submit=%D0%9F%D0%BE%D0%BA%D0%B0%D0%B7%D0%B0%D1%82%D1%8C" tmp1
bash delspaces.sh tmp1/result.html tmp1/nospaces.html
echo "Extraction started..."
grep -o '<td class="date">[[:space:]]*\([^<]*\)</td>[[:space:]]*<td class="name">[[:space:]]*\([^<]*\)[[:space:]]*</td>[[:space:]]*<td>\([^<]*\)</td>' < tmp1/nospaces.html | sed -e 's/<td class="date">[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td class="name">[[:space:]]*\([^<]*\)[[:space:]]*<\/td>[[:space:]]*<td>\([^<]*\)<\/td>/\1\n\2\n\3/g' > marres
#grep -o '<td class="date">[[:space:]]*\([^<]*\)</td>[[:space:]]*<td class="name">[[:space:]]*[<]*[b]*[>]*[<]*[u]*[>]*\([^<-]*\)[<]*[/]*[u]*[>]*[<]*[/]*[b]*[>]*[[:space:]]*-[[:space:]]*[<]*[b]*[>]*[<]*[u]*[>]*\([^<]*\)[<]*[/]*[u]*[>]*[<]*[/]*[b]*[>]*</td>[[:space:]]*<td>\([^<]*\)</td>' < tmp1/nospaces.html | sed -e 's/<td class="date">[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td class="name">[[:space:]]*[<]*[b]*[>]*[<]*[u]*[>]*\([^<-]*\)[<]*[\/]*[u]*[>]*[<]*[\/]*[b]*[>]*[[:space:]]*-[[:space:]]*[<]*[b]*[>]*[<]*[u]*[>]*\([^<]*\)[<]*[\/]*[u]*[>]*[<]*[\/]*[b]*[>]*<\/td>[[:space:]]*<td>\([^<]*\)<\/td>/\1\n\2-\3\n\4/g' >> marres

grep -o '<td class="date">[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td class="name">[[:space:]]*<b><u>\([^<]*\)<\/u><\/b>[[:space:]]*-[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td>\([^<]*\)<\/td>' < tmp1/nospaces.html | sed -e 's/<td class="date">[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td class="name">[[:space:]]*<b><u>\([^<]*\)<\/u><\/b>[[:space:]]*-[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td>\([^<]*\)<\/td>/\1\n\2-\3\n\4/g' >> marres
grep -o '<td class="date">[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td class="name">[[:space:]]*\([^<]*\)<b><u>\([^<]*\)<\/u><\/b>[[:space:]]*<\/td>[[:space:]]*<td>\([^<]*\)<\/td>' < tmp1/nospaces.html | sed -e 's/<td class="date">[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td class="name">[[:space:]]*\([^<]*\)<b><u>\([^<]*\)<\/u><\/b>[[:space:]]*<\/td>[[:space:]]*<td>\([^<]*\)<\/td>/\1\n\2-\3\n\4/g' >> marres

echo "Extraction finished."
rm -r tmp1/
mkdir -p "../data/$d"
cd "../data/$d"
mkdir -p results/marathonbet.com/
mv ../../scripts/marres "results/marathonbet.com/$t"
echo "Results succesfully recieved from site http://marathonbet.com"
