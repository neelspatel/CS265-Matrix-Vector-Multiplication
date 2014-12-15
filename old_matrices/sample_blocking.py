import scipy.sparse
import random

#constants
sampling_rate = 0.2
quadrant_sampling_rate = 0.2
height = 7
width = 7

#generage a sparse matrix, and convert to dense format
matrix = scipy.sparse.rand(height,width,density=0.1).todense()

nonzero = [[0 for i in range(height)] for j in range(width)]
for i in range(height):
	for j in range(width):
		if matrix[i, j] != 0:
			nonzero[i][j] = 1

def sample_all_quadrants(matrix, sampling_rate):
	#creates and shuffles list of indices that we will randomly sample
	sampled = [i for i in range(0, height*width)]
	middle = (height/2) * width + width/2 + 1
	sampled.remove(middle)
	random.shuffle(sampled)
	sample_cutoff = int(len(sampled)*sampling_rate)
	sampled = sampled[sample_cutoff:]

	counts = [0,0,0,0]
	hits = [0,0,0,0]

	#samples points randomly
	for sample in sampled:
		row = sample / width
		col = sample - row * width

		is_nonzero = (matrix[row, col] != 0)
		
		#if we're in quadrant 1
		if col > width/2 - 1 and row < height/2 + 1:
			counts[0] += 1
			if is_nonzero:
				hits[0] += 1
		#if we're in quadrant 2
		if col < width/2 + 1 and row < height/2 + 1:
			counts[1] += 1
			if is_nonzero:
				hits[1] += 1
		#if we're in quadrant 3
		if col < width/2 + 1 and row > height/2 - 1:
			counts[2] += 1
			if is_nonzero:
				hits[2] += 1
		#if we're in quadrant 4
		if col > width/2 - 1 and row > height/2 - 1:
			counts[3] += 1
			if is_nonzero:
				hits[3] += 1

	return zip(hits, counts)

#samples a given quadrant
def sample_quadrant(matrix, quadrant, sampling_rate):
	#shifts quadrant to the 1-4 range
	quadrant += 1

	if quadrant == 1:
		row_start = 0
		row_end = height / 2
		col_start = width / 2
		col_end = width
	elif quadrant == 2:
		row_start = 0
		row_end = height / 2
		col_start = 0
		col_end = width / 2
	elif quadrant == 3:
		row_start = height / 2
		row_end = height / 2
		col_start = 0
		col_end = width / 2
	else:
		row_start = height / 2
		row_end = height / 2
		col_start = width / 2
		col_end = width

	sampled = [(j*width)+i for i in range(col_start, col_end) for j in range(row_start, row_end)]
	middle = (height/2) * width + width/2
	sampled.remove(middle)
	random.shuffle(sampled)
	sample_cutoff = int(len(sampled)*sampling_rate)
	sampled = sampled[sample_cutoff:]

	#counts the number of nonzeroes in this quadrant
	for sample in sampled:
		row = sample / width
		col = sample - row * width

		is_nonzero = (matrix[row, col] != 0)
	


print sample_all_quadrants(matrix, sampling_rate)
#print sample_quadrant(matrix, 1, quadrant_sampling_rate)


#check all 4 (fuzzy) quadrants for a large dense block first:
#for each quadrant with over a threshold T of nonzeros (sorted by percent of nonzeros):
#	sample again in that quadrant and check if it's dense
#		if so: return one of the four 4x4 grids around this quadrant
#check the surrounding 8 blocks next:
#if we have 4 or more nonzeros, return this 3x3 block centered around x
#if we have 3 nonzeros, return this 3x3 block
#	all 3 in same r/c:
#		1 1 1
#		  x  
#		     
#		take the 2x3 block with x and all 3 nonzeros		
#	2 in the same r/c, and 1 in another r/c
#			1 1 
#			  x  
#		        1
#		if adjacent: take the two adjacent ones and x
#			1   1 
#			  x  
#		      1
#		if not adjacent: we can choose the 3x2, or the 2x1
#	all 3 in different r/c
#			1    
#			  x 1
#		      1
#		choose the densest 2x2 block
#if we have 2 nonzeros:
#	take the range of rows anc columns
#if we have 1 nonzero: take the 2x2


