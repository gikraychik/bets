#! /bin/bash
cd scripts/
mkdir -p tmp/
mkdir -p logs/
#bash wget.sh "http://www.marathonbet.com/ru/results.htm?form_name=form&Football=on&dateFilterSelector=YESTERDAY&submit=%D0%9F%D0%BE%D0%BA%D0%B0%D0%B7%D0%B0%D1%82%D1%8C"
bash delspaces.sh tmp/result.html tmp/nospaces.html
echo "Extraction started..."
grep -o '<td class="date">[[:space:]]*\([^<]*\)</td>[[:space:]]*<td class="name">\([^<]*\)</td>[[:space:]]*<td>\([^<]*\)</td>' < tmp/nospaces.html | sed -e 's/<td class="date">[[:space:]]*\([^<]*\)<\/td>[[:space:]]*<td class="name">\([^<]*\)<\/td>[[:space:]]*<td>\([^<]*\)<\/td>/\1\n\2\n\3/g' > marres
echo "Extraction finished."
echo "Results recieved."
