import subprocess
import sys

if len(sys.argv) !=4:
	print "Argument is worry, re-input again\n"
add = []
add.append(sys.argv[1]) 
add.append(sys.argv[2])
seed = sys.argv[3]

for i in range(2):
	subprocess.call("cp -f " + add[i] + "/dominion.c" + " .", shell=True)
	subprocess.call("make clean; make all", shell=True)
	subprocess.call("testdominion " + str(seed) + " >> dominion" + str(i) + ".out", shell=True)
	subprocess.call("gcov dominion.c >> dominion" + str(i) + ".out.gcov", shell=True)

r = subprocess.call("diff dominion0.out dominion1.out >> diff.out", shell=True)
if(r!=0):
	print "TEST FALED! Check the output file\n"
else:
	print "TEST PASSED!\n"
