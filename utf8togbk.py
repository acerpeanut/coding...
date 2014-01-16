#!/usr/bin/python
# utf8togbk.py a.txt b.txt

import sys

i = sys.argv[1]
o = sys.argv[2]

print i," ",o

f = file(i ,'r')
fw = file(o ,'w')
while True:
	a = f.readline()
	if len(a) != 0:
		b = a.decode('utf-8')
		fw.write( b.encode('gb2312') )
	else:
		break
else:
	print 'Done'
