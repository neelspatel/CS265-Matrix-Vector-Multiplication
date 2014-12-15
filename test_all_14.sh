#!/bin/bash

# Assumes that position $1 is the file name
declare -a arr=("Tina_AskCal" "rail516" "lp_pds_10" "ch7-9-b5" "nh2010" "TF17" "wy2010" "shar_te2-b3" "il2010" "mc2depi" "ut2010" "lp_pds_02" "roadNet-PA")


for FILENAME in "${arr[@]}"
do
	echo $FILENAME


	#tests our calculation
	./run 1_4test_matrices/"$FILENAME"_output.txt 1_4test_matrices/"$FILENAME"_vector.txt 1_4test_matrices/"$FILENAME"_calculated.txt
	diff 1_4test_matrices/"$FILENAME"_calculated.txt 1_4test_matrices/"$FILENAME"_expected_result.txt

	#tests naive calculation
	./naive 1_4test_matrices/"$FILENAME"_naive_output.txt 1_4test_matrices/"$FILENAME"_vector.txt 1_4test_matrices/"$FILENAME"_naive_calculated.txt
	diff 1_4test_matrices/"$FILENAME"_naive_calculated.txt 1_4test_matrices/"$FILENAME"_expected_result.txt

done