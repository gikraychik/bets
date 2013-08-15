#!/bin/bash
tr -d '\n' <tmp/result.html | tr -d '\t' | sed -e 's/\r//g' | sed -e 's/\(<[^<]*>\)[\b\t]*\(<\)/\1\2/g' >tmp/nospaces.html
