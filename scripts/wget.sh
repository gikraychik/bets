#!/bin/bash
echo "Download started...($1)"
wget -a logs/wget_log -T 300 -t 10 -O tmp/result.html $1
echo "Download complete."
