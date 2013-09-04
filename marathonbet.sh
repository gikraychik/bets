#! /bin/bash
#! /bin/bash
echo "*************************************Bets extraction*************************************"
cd scripts/
mkdir -p tmp/
mkdir -p logs/
bash wget.sh http://www.marathonbet.com/ru/betting/Football/
bash delspaces.sh tmp/result.html tmp/nospaces.html
echo "Extraction started..."
grep -o '<div class="member-name">[^<]*</div>' < tmp/nospaces.html | sed -e 's/<div class="member-name">\([^<]*\)<\/div>/\1/g' >>commands_soon
grep -o '<div class="today-member-name">[^<]*</div>' < tmp/nospaces.html | sed -e 's/<div class="today-member-name">\([^<]*\)<\/div>/\1/g' >>commands_today
grep -o '<td class="date">[^<]*</td>' <tmp/nospaces.html  | sed -e 's/<td class="date">\([^<]*\)<\/td>/\1/g' >>dates
grep '[а-яА-Я]' < dates > dates_soon
grep -v '[а-яА-Я]' < dates > dates_today
grep -o '<span class="selection-link coeff[^"]*">[^<]*</span>' <tmp/nospaces.html | sed -e 's/<span class="selection-link coeff[^"]*">\([^<]*\)<\/span>/\1/g' > coeff
grep -o -n '<td class="js-price' < tmp/result.html | sed -e 's/^\([0-9][0-9]*\).*/\1/g' > filled
grep -o -n 'td-min-width' < tmp/result.html | sed -e 's/^\([0-9][0-9]*\).*/\1/g' > empty
while read line
do
	a1+=("$line")
done < filled
while read line
do
	vals+=("$line")
done < coeff
while read line
do
	a2+=("$line")
done < empty
let i=0
let j=0
let amount=${#vals[*]}
while true
do
	if [ "$i" -ge "${#a1[*]}" ]
	then
		break
	fi
	if [ "$j" -ge "${#a2[*]}" ]
	then
		break
	fi
	while [ ${a1[i]} -le ${a2[j]} ]
	do
		if [ "$i" -ge "${#a1[*]}" ]
		then
			break
		fi
		if [ "$j" -ge "${#a2[*]}" ]
		then
			break
		fi
		echo "${vals[i]}" >> new_coeff
		i=$((i+1))
	done
	if [ "$i" -ge "${#a1[*]}" ]
	then
		break
	fi
	if [ "$j" -ge "${#a2[*]}" ]
	then
		break
	fi
	while [ ${a1[i]} -ge ${a2[j]} ]
	do
		if [ "$i" -ge "${#a1[*]}" ]
		then
			break
		fi
		if [ "$j" -ge "${#a2[*]}" ]
		then
			break
		fi
		echo "0.0" >> new_coeff
		j=$((j+1))
	done
done
while true
do
	if [ "$i" -ge "${#a1[*]}" ]
	then
		break
	fi
	echo "${vals[i]}" >> new_coeff
	i=$((i+1))
done
let i=0
while read line
do
	new+=("$line")
done < new_coeff


#for ((i=0; i<${#vals[*]};i++))
#do
#	echo "${vals[i]}"
#done

echo "Extraction finished."
echo "Done."
