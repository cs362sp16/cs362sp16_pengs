from __future__ import division
import sys
import os
import subprocess

def printc_red(msg):
	#define the color
    print '\033[91m' + msg + '\033[0m'

def printc_green(msg):
	#define the color
    print '\033[92m' + msg + '\033[0m'

def printc_yellow(msg):
	#define the color
    print '\033[93m' + msg + '\033[0m'

def count_digits(n):
	#count the width
    count = 0
    while n != 0:
        count += 1
        n = n // 10
    return count

def get_result(msg):
	#check the test result
	#caputrue the result by the first char of the string
    return msg.startswith('No')

def suspiciousness(passed, failed, totalpassed, totalfailed):
	#how we compute the result
    numerator = failed / totalfailed
    denominator = passed / totalpassed + numerator
    return numerator / denominator

def main():
    maxtest = 4
    unittests = ['unittest' + str(i) for i in range(1, maxtest + 1)]
    cardtests = ['cardtest' + str(i) for i in range(1, maxtest + 1)]
    testset = unittests + cardtests
    count = len(open('dominion.c','r').readlines()) 
    passed = [0 for i in range(count + 1)]
    failed = [0 for i in range(count + 1)]
    totalpassed = 0
    totalfailed = 0
	#run test and collect the result
    for test in testset:
        # compile and execute unit test
        subprocess.call("make clean; make all", shell=True)
        subprocess.call(test,shell=True)
        try:
            temp = subprocess.check_output(['./' + test], stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as out:
            temp = out.output
        # record test result
        result = get_result(temp)
        if (result):
            totalpassed += 1
        else:
            totalfailed += 1
        # execute gcov on source file and record results
        subprocess.call("gcov dominion.c", shell=True)
        for line in open('dominion.c.gcov', 'r').readlines():
            temp_line= line.split(':')
            num = temp_line[0].lstrip()
            i = int(temp_line[1])
            if num.startswith('-') or num.startswith('#'): 
                continue
            elif (result):
                passed[i] += 1
            else:
                failed[i] += 1
    # print tarantula results
    width = count_digits(count)
    i = 1
    for line in open("dominion.c", 'r').readlines():
        msg = str(i).rjust(width) + ':' + line[:-1]
        if passed[i] > 0 or failed[i] > 0:
            # some test executed this line
            temp = suspiciousness(passed[i], failed[i], totalpassed, totalfailed)
            if temp == 0:
				#safe part
                printc_green(msg)
            elif temp <= 0.5:
				#maybe bug
                printc_yellow(msg)
            else:
				#bugs
                printc_red(msg)
        else:
            print msg
        i += 1

#excute main
main()
