#!/bin/bash

JAVAREEDSOLOMONDIR=~/

for i in sample-input.txt.?; do
	diff $i ${JAVAREEDSOLOMONDIR}/$i
done
