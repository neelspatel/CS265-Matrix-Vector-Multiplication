#!/bin/sh

# Assumes that position $1 is the file name

./naive "test_matrices/$1_naive_output.txt" "test_matrices/$1_vector.txt" "test_matrices/$1_naive_calculated.txt"

echo

diff "test_matrices/$1_naive_calculated.txt" "test_matrices/$1_expected_result.txt"