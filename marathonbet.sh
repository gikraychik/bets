#! /bin/bash
#! /bin/bash
echo "*************************************Bets extraction*************************************"
cd scripts/
mkdir -p tmp/
mkdir -p logs/
#bash wget.sh http://www.marathonbet.com/ru/betting/Football/
bash delspaces.sh tmp/result.html tmp/nospaces.html
echo "Extraction started..."
grep -o '<div class="member-name">[^<]*</div>' < tmp/nospaces.html | sed -e 's/<div class="member-name">\([^<]*\)<\/div>/\1/g' >>commands_soon
grep -o '<div class="today-member-name">[^<]*</div>' < tmp/nospaces.html | sed -e 's/<div class="today-member-name">\([^<]*\)<\/div>/\1/g' >>commands_today
grep -o '<td class="date">[^<]*</td>' <tmp/nospaces.html  | sed -e 's/<td class="date">\([^<]*\)<\/td>/\1/g' >>dates
grep '[а-яА-Я]' < dates > dates_soon
grep -v '[а-яА-Я]' < dates > dates_today
grep -o '<span class="selection-link coeff[^"]*">[^<]*</span>' <tmp/nospaces.html | sed -e 's/<span class="selection-link coeff[^"]*">\([^<]*\)<\/span>/\1/g' > coeff


echo "Extraction finished."
echo "Done."
