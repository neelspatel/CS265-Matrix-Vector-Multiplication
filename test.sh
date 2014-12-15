#!/bin/sh

# Assumes that position $1 is the file name

./run "test_matrices/$1_output.txt" "test_matrices/$1_vector.txt" "test_matrices/$1_calculated.txt"

echo

diff "test_matrices/$1_calculated.txt" "test_matrices/$1_expected_result.txt"