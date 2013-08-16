#!/bin/bash
tr -d '\n' <$1 | tr -d '\t' | sed -e 's/\r//g' | sed -e 's/\(<[^<]*>\)[\b\t]*\(<\)/\1\2/g' >$2
