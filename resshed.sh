#! /bin/bash
d=$(date +%F)
t=$(date +%H)
while (true)
do
	if [ "$t" -eq "23" ]
	then
		bash marres.sh
		sleep 3600
	fi
	sleep 300
done
