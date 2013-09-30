#! /bin/bash
while (true)
do
	d=$(date +%F)
	t=$(date +%H)
	if [ "$t" -eq "18" ]
	then
		bash results/marres.sh
		sleep 3600
	fi
	sleep 300
done
