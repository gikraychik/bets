#! /bin/bash
echo "*************************************ligastavok.com*************************************"
cd scripts/
mkdir -p tmp/
mkdir -p logs/
bash wget.sh http://www.ligastavok.com/Topics/?st=33
echo "Deleting spaces..."
bash delspaces.sh tmp/result.html tmp/nospaces.html
echo "Deleted."
echo "Forming addresses..."
echo "http&#58;//www.ligastavok.com/Topics/Events.aspx?st=33&t=" >addr
grep -o 'Events\.aspx?st=33&t=[0-9][0-9]*' < tmp/nospaces.html |
	sed -e 's/Events\.aspx?st=33&t=\([0-9][0-9]*\)/\1,/g' | tr -d '\n' | sed -e 's/\(.*\),/\1/g' >> addr
addr=$(cat addr | tr -d '\n' | tr -d ' ')
echo "Formation done."
rm tmp/result.html
bash wget.sh "'$addr'"
echo "Extraction done."

#rm -r tmp
#rm -r logs
echo "Done."
