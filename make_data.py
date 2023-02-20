from random import random
T = 1
n = 50000 
maxV = int(2e5)

for t in range(T):
	for i in range(n):
		print (int(random() * maxV) + 1, end = ' ')

	print ()

	for i in range(n):
		print (int(random() * maxV) + 1, end = ' ')
