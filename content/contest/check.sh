#!/bin/bash
while true; do
  ./gen
  ./a > myout.txt
  ./b > brute.txt
  diff myout.txt brute.txt
  if [ $? -ne 0 ]; then break; fi
  echo AC
done
