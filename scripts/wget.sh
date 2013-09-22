#!/bin/bash
#$1 - adress you download file from
#$2 - directory used to download files
echo "Download started...($1)"
wget -a logs/wget_log -O "$2"/result.html $1
echo "Download complete."
