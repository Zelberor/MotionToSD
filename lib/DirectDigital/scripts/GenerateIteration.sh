#!/bin/sh

printf "#define ITERATE_1(X) (X)"

for i in  $(seq 2 $1); do
	printf "\n#define ITERATE_$i(X) (X)"
done
