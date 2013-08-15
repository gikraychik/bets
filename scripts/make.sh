#! /bin/bash
#echo "Download of the main page started..."
#wget -a logs/wget_log -O tmp/result.html http://ru.leonbets.com/
#echo "Download of the main page complete."
bash wget.sh http://ru.leonbets.com/
bash delspaces.sh
sed -e 's/<div[[:space:]]*class="lineb">[[:space:]]*Футбол[[:space:]]*<\/div>.*<a href="\([^"]*\)[^>]*\([^<]*\)<\/a>/\1\n\2/g' tmp/nospaces.html >tmp/extraction
