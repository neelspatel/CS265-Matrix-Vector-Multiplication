#!/bin/sh

# Assumes that position $1 is the file name
declare -a arr=("rail516" "shar_te2-b3" "lp_pds_02")


for FILENAME in "${arr[@]}"
do
	echo $FILENAME


	#tests our calculation
	./run test_matrices/"$FILENAME"_output.txt test_matrices/"$FILENAME"_vector.txt test_matrices/"$FILENAME"_calculated.txt
	diff test_matrices/"$FILENAME"_calculated.txt test_matrices/"$FILENAME"_expected_result.txt

	#tests naive calculation
	./naive test_matrices/"$FILENAME"_naive_output.txt test_matrices/"$FILENAME"_vector.txt test_matrices/"$FILENAME"_naive_calculated.txt
	diff test_matrices/"$FILENAME"_naive_calculated.txt test_matrices/"$FILENAME"_expected_result.txt

done