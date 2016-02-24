#!/bin/bash


for i in 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95
do 
 ./TOPOLO -s $i
done


for i in 0.2 0.4 0.6 0.8
do 
 ./TOPOLO -d $i 0.02
done


for i in 0.2 0.4 0.6 0.8
do 
 ./TOPOLO -d $i 0.04
done

for i in 0.2 0.4 0.6 0.8
do 
 ./TOPOLO -d $i 0.06
done

