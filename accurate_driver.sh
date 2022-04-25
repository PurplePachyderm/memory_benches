#!/bin/sh

sizes=()
accesses=()

# Repeat benchmark with arrays sized from 0 up to max
# Adviced max values :
# - 500 000 000 : for bandwidth
# - 1000 000 : for latency
let i=0
let size=0
let max=500000000

while [ $size -le $max ]
do
	if [[ $size -lt 10000 ]]; then
		let "size=size+100"
	elif [[ $size -lt 100000 ]]; then
		let "size=size+2000"
	elif [[ $size -lt 1000000 ]]; then
		let "size=size+20000"
	elif [[ $size -lt 10000000 ]]; then
		let "size=size+400000"
	elif [[ $size -lt 100000000 ]]; then
		let "size=size+4000000"
	elif [[ $size -lt 1000000000 ]]; then
		let "size=size+50000000"
	else
		let "size=size+500000000"
	fi
	sizes[$i]=$size

	eval "$1 $size 5 50"
	accesses[$i]=$(<tmp.txt)
	let "i=i+1"

done

# Write csv file
rm -f "$1.csv"
echo "size,accesses" >> "$1.csv"

for ((i = 0 ; i < ${#sizes[@]} ; i++)); do
	size=${sizes[$i]}
	access=${accesses[$i]}
	echo "$size,$access" >> "$1.csv"
done
