#!/bin/bash

JAVAREEDSOLOMONDIR=~/code/JavaReedSolomon

for i in sample-input.txt.?; do
	diff $i ${JAVAREEDSOLOMONDIR}/$i
done
