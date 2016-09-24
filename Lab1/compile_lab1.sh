#!/usr/bin/env bash
cd /home/abi/ClionProjects/OSLab1/src/problem1/
gcc -o exe tictactoetomek.c 
./exe /home/abi/ClionProjects/OSLab1/input_files/problem1/tictactoetomek_input.txt
cd /home/abi/ClionProjects/OSLab1/src/problem2/
gcc -o exe whereswaldorf.c
./exe /home/abi/ClionProjects/OSLab1/input_files/problem2/whereswaldorf_input.txt
cd /home/abi/ClionProjects/OSLab1/src/problem3/
gcc -o exe gpasorter.c
./exe