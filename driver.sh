#!/bin/sh

sizes=()
accesses=()

# Repeat benchmark with arrays sized from 2^0 up to 2^23
let pow=1
for ((i = 0 ; i <= 23 ; i++)); do
	eval "$1 $pow 10 1000"
	accesses[$i]=$(<tmp.txt)
	sizes[$i]=$pow
	let pow=2*pow
done

# Write csv file
rm -f "$1.csv"
echo "size,accesses" >> "$1.csv"

for ((i = 0 ; i <= 23 ; i++)); do
	size=${sizes[$i]}
	access=${accesses[$i]}
	echo "$size,$access" >> "$1.csv"
done
