#!/bin/bash

# Assumes that position $1 is the file name
declare -a arr=("Tina_AskCal" "rail516" "lp_pds_10" "ch7-9-b5" "nh2010" "TF17" "wy2010" "shar_te2-b3" "il2010" "mc2depi" "ut2010" "lp_pds_02" "roadNet-PA")

PERF_EVENTS="dTLB-load-misses,dTLB-store-misses,iTLB-load-misses,cpu-clock,cache-misses,L1-dcache-load-misses,L1-dcache-store-misses"

for FILENAME in "${arr[@]}"
do
	echo $FILENAME

	#tests our calculation
	perf stat -e $PERF_EVENTS -o test_matrices/"$FILENAME"_our_perf.txt ./run test_matrices/"$FILENAME"_output.txt test_matrices/"$FILENAME"_vector.txt test_matrices/"$FILENAME"_calculated.txt

	#diff test_matrices/"$FILENAME"_calculated.txt test_matrices/"$FILENAME"_expected_result.txt

	#tests naive calculation
	perf stat -e $PERF_EVENTS -o test_matrices/"$FILENAME"_naive_perf.txt ./naive test_matrices/"$FILENAME"_naive_output.txt test_matrices/"$FILENAME"_vector.txt test_matrices/"$FILENAME"_naive_calculated.txt
	#diff test_matrices/"$FILENAME"_naive_calculated.txt test_matrices/"$FILENAME"_expected_result.txt

done
