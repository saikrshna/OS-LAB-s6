echo "Enter the limit: "
read limit
a=0
b=1
for((i=0; i<=limit; i++));do
	c=$((a+b))
	while [ $i -lt $c ];do
		echo "$i"
		((i++))
	done
	a=$b
	b=$c
done
