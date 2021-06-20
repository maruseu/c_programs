#!/bin/bash
for i in *.c; do
	clang $i -o "${i%.*}" -lX11 -lpthread -pedantic -Wall -Wextra -O3
done
