#!/bin/sh

export LD_PRELOAD=$PWD/libft_malloc.so
for file in test/test*.c
do
	gcc $file -L. -lft_malloc -o ${file%.c}
done



./test0
