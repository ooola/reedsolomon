#!/bin/bash

JAVAREEDSOLOMONDIR=~/src/JavaReedSolomon

for i in sample-input.txt.?; do
	diff $i ${JAVAREEDSOLOMONDIR}/$i
done
