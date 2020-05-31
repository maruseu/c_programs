for i in *.c; do
	cc $i -o "${i%.*}.out"
done
