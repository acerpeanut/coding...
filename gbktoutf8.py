#!/usr/bin/python
# gbktoutf8.py a.txt b.txt
import sys

i = sys.argv[1]
o = sys.argv[2]

print i," ",o

f = file(i ,'r')
fw = file(o ,'w')
while True:
	a = f.readline()
	if len(a) != 0:
		b = a.decode('gb2312')
		fw.write( b.encode('utf-8') )
	else:
		break
else:
	print 'Done'
