#!/bin/bash
for i in *.c; do
	cc $i -o "${i%.*}" -lX11 -pedantic -Wall -Wextra -O3
done
