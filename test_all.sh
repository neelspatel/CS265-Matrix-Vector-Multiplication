#!/bin/sh

# Assumes that position $1 is the file name
declare -a arr=("Tina_AskCal" "rail516" "lp_pds_10" "ch7-9-b5" "nh2010" "TF17" "wy2010" "shar_te2-b3" "il2010" "mc2depi" "ut2010" "lp_pds_02" "roadNet-PA")


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