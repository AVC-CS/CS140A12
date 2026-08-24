#!/bin/sh
# Build main.cpp and capture its output into result.txt, which the T1-T4 tests then read.
#
# Regenerating result.txt here is correct for THIS assignment: the deliverable is main.cpp, and
# result.txt is only the program's output. (Contrast A11, where the generated files ARE the
# submission and this script must not create them.)
g++ -Wall -Wextra --std=c++17 main.cpp -o a.out || exit 1
timeout 10 ./a.out > result.txt
