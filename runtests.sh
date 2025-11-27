#!/bin/sh

for file in test/test*.c
do
	gcc -o ${file%.c} $file 
done


export LD_PRELOAD=$PWD/libft_malloc.so


for file in test/test*.c
do
	./${file%.c}
done
