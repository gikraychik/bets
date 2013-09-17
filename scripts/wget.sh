#!/bin/bash
echo "Download started...($1)"
wget -a logs/wget_log -O "$2"/result.html $1
echo "Download complete."
