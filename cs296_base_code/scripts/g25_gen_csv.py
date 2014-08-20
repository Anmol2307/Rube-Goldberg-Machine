#!/usr/bin/python3

import os
import subprocess
import re
file_csv = open ('data/'+'lab09_g25_data.csv' ,"w")	
for i in range(1,101):
	for j in range(1,101):
		file = open ('data/'+'out.txt' ,"w")
		subprocess.call(['bin/cs296_base',str(j)],stdout=file)
		file.close()
		file = open ('data/'+'out.txt' ,"r")
		lines=file.readlines()
		file_csv.write(str(i))
		for line in lines:
			num = re.findall(r"[-+]?\d*\.\d+|\d+", line)
			file_csv.write(',')
			file_csv.write(num[0])
		file_csv.write('\n')
os.remove('data/out.txt')
