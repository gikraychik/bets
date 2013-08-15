#!/bin/bash
iconv -f windows-1251 -t utf-8 -o tmp/result-utf8.html tmp/result.html
rm tmp/result.html
mv tmp/result-utf8.html tmp/result.html
