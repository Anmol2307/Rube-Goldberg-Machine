#!/usr/bin/python3
import numpy
from numpy import genfromtxt
import matplotlib as mplot
import matplotlib.pyplot as pyplot

data_csv=genfromtxt('data/lab09_g25_data.csv', delimiter=",")
x = []
for i in range(1,101):
	x.append(i)

ystep = []
ycol = []
yvel = []
ypos = []
yloop = []

for i in range(0,100):
	ystep.append(0.0)
	ycol.append(0.0)
	yvel.append(0.0)
	ypos.append(0.0)
	yloop.append(0.0)
	
for i in range(0,100):
	for j in range (0,100):
		ystep[i] = ystep[i] + data_csv[i+j*100][2]
		ycol[i] = ycol[i] + data_csv[i+j*100][3]
		yvel[i] = yvel[i] + data_csv[i+j*100][4]
		ypos[i] = ypos[i] + data_csv[i+j*100][5]
		yloop[i] = yloop[i] + data_csv[i+j*100][6]		
	ystep[i]=ystep[i]/100.0	
	ycol[i]=ycol[i]/100.0
	yvel[i]=yvel[i]/100.0
	ypos[i]=ypos[i]/100.0
	yloop[i]=yloop[i]/100.0

maxsteptime=ystep[0]
maxlooptime=yloop[0]
for i in range(1,100):
	if (ystep[i]>maxsteptime) :
		maxsteptime=ystep[i]
	if (yloop[i]>maxlooptime) :
		maxlooptime=yloop[i]

guardstep=maxsteptime*1.5
guardloop=maxlooptime*1.5



#1

pyplot.ylim([0,guardloop])
pyplot.plot(x, ystep, 'b+', label='Average Step Time')
pyplot.plot(x, yloop, 'c*', label='Average Loop Time')

pyplot.legend(bbox_to_anchor=(0. , 1., 2., .02), loc=2)

pyplot.title("Avg Step Time & Loop Time vs Iteration Value")

pyplot.xlabel("Iteration Values")
pyplot.ylabel("Step Time Interval")

pyplot.savefig("plots/g25_lab09_plot01.png")
pyplot.clf()

#2

pyplot.ylim([0,guardstep])

pyplot.plot(x, ystep, 'bx', label='Average Step Time')
pyplot.plot(x, ycol, 'c.', label='Average Collision Time')
pyplot.plot(x, yvel, 'r+', label='Average Velocity Update Time')
pyplot.plot(x, ypos, 'g*', label='Average Position Update Time')

pyplot.legend(bbox_to_anchor=(-1., 1., 2., .02), loc=1)

pyplot.title("Collision Time, Velocity & Position Updates vs Iteration Value")

pyplot.xlabel("Iteration Values")
pyplot.ylabel("Step Time Interval")

pyplot.savefig("plots/g25_lab09_plot02.png")
pyplot.clf()


ystepn = []
ycoln = []
yveln = []
yposn = []
yloopn = []
for i in range(0,100):
	ystepn.append(0.0)
	ycoln.append(0.0)
	yveln.append(0.0)
	yposn.append(0.0)
	yloopn.append(0.0)

for i in range(0,100):
	for j in range(0,100):
		ystepn[i] = ystepn[i] + data_csv[100*i+j][2]
		ycoln[i] = ycoln[i] + data_csv[100*i+j][3]
		yveln[i] = yveln[i] + data_csv[100*i+j][4]
		yposn[i] = yposn[i] + data_csv[100*i+j][5]
		yloopn[i] = yloopn[i] + data_csv[100*i+j][6]
	ystepn[i]=ystepn[i]/100.0	
	ycoln[i]=ycoln[i]/100.0
	yveln[i]=yveln[i]/100.0
	yposn[i]=yposn[i]/100.0
	yloopn[i]=yloopn[i]/100.0

maxsteptime=ystepn[0]
maxlooptime=yloopn[0]
for i in range(1,100):
	if (ystepn[i]>maxsteptime) :
		maxsteptime=ystepn[i]
	if (yloopn[i]>maxlooptime) :
		maxlooptime=yloopn[i]

guardstep=maxsteptime*1.5
guardloop=maxlooptime*1.5


#3

pyplot.ylim([0,guardloop])
pyplot.plot(x, ystepn, 'b+', label='Average Step Time')
pyplot.plot(x, yloopn, 'c*', label='Average Loop Time')

pyplot.legend(bbox_to_anchor=(-1. , 1., 2., .02), loc=1)

pyplot.title("Avg Step Time & Loop Time vs Rerun Value")

pyplot.xlabel("Rerun Values")
pyplot.ylabel("Step Time Interval")

pyplot.savefig("plots/g25_lab09_plot03.png")
pyplot.clf()

#4

pyplot.ylim([0,guardstep])
pyplot.plot(x, ystepn, 'bx', label='Average Step Time')
pyplot.plot(x, ycoln, 'c.', label='Average Collision Time')
pyplot.plot(x, yveln, 'r+', label='Average Velocity Update Time')
pyplot.plot(x, yposn, 'g*', label='Average Position Update Time')

pyplot.legend(bbox_to_anchor=(-1., 1., 2., .02), loc=1)

pyplot.title("Collision Time, Velocity & Position Updates vs Rerun Value")

pyplot.xlabel("Rerun Values")
pyplot.ylabel("Step Time Interval")

pyplot.savefig("plots/g25_lab09_plot04.png")
pyplot.clf()

#5

ystepl = []
ystep_lo = []
ystep_hi = []

for i in range(0,100):
	ystepl.append(0.0)
	ystep_lo.append(0.0)
	ystep_hi.append(0.0)

for i in range(0,100):
	ystep_lo[i] =  data_csv[i][2]
	ystep_hi[i] =  data_csv[i][2]
	for j in range(0,100):
		temp=data_csv[i+j*100][2]
		ystepl[i] += temp
		if (ystep_lo[i] > temp ):
			 ystep_lo[i] = temp
		if (ystep_hi[i] < temp ):
			 ystep_hi[i] = temp
	ystepl[i] = ystepl[i]/100.0
		 


pyplot.errorbar(x, ystepl, yerr=[ystep_lo,ystep_hi], fmt='r_', label='Variation in Step Time')

pyplot.title("Step Time(With Errors) vs Iteration Value")

pyplot.xlabel("Iteration Values")
pyplot.ylabel("Step Time")

pyplot.legend(bbox_to_anchor=(-1. , 1., 2., .02), loc=1)

         
pyplot.savefig("plots/g25_lab09_plot05.png")
pyplot.clf()

#6

yhist = []

for i in range(0,100):
	yhist.append(0.0)

for i in range(0,100):
	yhist[i]=data_csv[2+100*i][2]

pyplot.hist([float(i) for i in yhist],bins=50,label='Frequency')

counts, bins = numpy.histogram([float(i) for i in yhist], bins=50)

cum = numpy.cumsum(counts)
pyplot.plot(bins[1:], cum,label='Cumulative Frequency')


pyplot.legend(bbox_to_anchor=(0., 1., 2., .02), loc=2)

pyplot.title("Step Time Frequency Plot")

pyplot.xlabel("Step Time")
pyplot.ylabel("Number of runs")

pyplot.savefig("plots/g25_lab09_plot06.png")

