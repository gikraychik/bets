#!/bin/bash
#grep -o '<div[[:space:]]*class="lineb">[[:space:]]*Футбол[[:space:]]*</div>[[:space:]]*</a>[[:space:]]*</td>[[:space:]]*</tr>[[:space:]]*<tr>[[:space:]]*<td>[[:space:]]*<div[^>]*>[[:space:]]*<div>[[:space:]]*<div[^>]*>[[:space:]]*<a href="\([^"]*\)[^>]*\([^<]*\)<\/a>' tmp/nospaces.html >tmp/extraction
grep -o '<div[^>]*>[[:space:]]*<a href="[^"]*"[^>]*>[^<]*</a>[[:space:]]*</div>' tmp/nospaces.html |
sed -e 's/<div[^>]*>[[:space:]]*<a href="\([^"]*\)"[^>]*>[^<]*<\/a>[[:space:]]*<\/div>/\1/g' >tmp/extraction
