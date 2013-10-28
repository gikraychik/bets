#!/usr/bin/env python
# -*- coding: koi8-r -*-
import urllib
import lxml.html
import datetime
import sys

dateIn = sys.argv[1]
timeIn = sys.argv[2]
outputFile = "../data/" + dateIn + "/" + timeIn + "/leonbets.com/log.txt"

leonbets = urllib.urlopen("http://ru.leonbets.com/")
docMain = lxml.html.document_fromstring(leonbets.read())

def getInfo(data):
    result = ""
    i = 0
    for s in data:
        result = result + s[0].text_content().strip() + " "
        if i == 3: break
        i = i + 1
    return result

def getTime(data):
    ms = ""
    i = 15;
    while data[i] != ")":
        ms = ms + data[i]
        i = i + 1
    result = datetime.datetime.fromtimestamp(int(ms) / 1000.0)
    result = str(result.year) + " " + str(result.month) + " " + str(result.day) + " " + str(result.hour) + " " + str(result.minute) 
    return result


# print "Starting"
output = open(outputFile, "w")
links = docMain.get_element_by_id("lg1").iterlinks()
for link in links:
    output.write("------------------\n")
    page = urllib.urlopen(link[2])
    doc = lxml.html.document_fromstring(page.read())
    matches = doc.find_class("row1")
    for i in range(0, len(matches)):
        # print lxml.html.tostring(matches[i])
        info = matches[i].text_content()
        if info[:5] != "print":
            continue
        else:
            info = getTime(info) + " " + getInfo(matches[i].iterlinks())
            output.write(info.encode("UTF-8"))
            output.write("\n")
            
        
    matches = doc.find_class("row2")
    for i in range(0, len(matches)):
        info = matches[i].text_content()
        if info[:5] != "print":
            continue
        else:
            info = getTime(info) + " " + getInfo(matches[i].iterlinks())
            output.write(info.encode("UTF-8"))
            output.write("\n")

output.close()
# print "Done!"
