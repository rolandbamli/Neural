#!/usr/bin/env python

import re
import matplotlib.pyplot as plt
import os

def histogram(nums):
	(x, y, z) = plt.hist(nums, 100, (0,1), histtype='stepfilled')
	plt.show
	plt.savefig("histogram.png")

	print "Range\t\t\tNumber of outputs\n"

	for i in xrange(len(x)):
		if i+1 == len(x):
			next = 1
		else:
			next = y[i+1]
		print '[', format(y[i], '.2f'), '-', format(next, '.2f'), ']', '\t', x[i]

def runNeural():
	os.system("./neural > result.txt")

def main():
	runNeural()
	f = open('result.txt', 'r')
	text = f.read()
	f.close()
	nums = re.findall('0\.\d+', text) + re.findall('\d\.\d+e-\d+', text)

	for i in range(len(nums)):
		if 'e' in nums[i]:
			coefficient = float(nums[i][:nums[i].find('e')])
			exponent = ((-1)*(int(nums[i][(nums[i].find('e'))+2:])))
			tmp = coefficient*(10**exponent)
			nums[i] = round(float(tmp), 3)	
		nums[i] = round(float(nums[i]), 3)

	histogram(nums)

if __name__=="__main__":
	main()
