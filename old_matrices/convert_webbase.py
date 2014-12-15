outputfile = open("webbase-int.txt", "w+")

with open("webbase-float.txt", "r+") as inputfile:
	for line in inputfile.readlines():
		cur_line = line.split(' ')
		cur_line[2] = str(int(float(cur_line[2])*10 - 5))

		outputfile.write(' '.join(cur_line) + '\n')

		print ' '.join(cur_line)

outputfile.close()