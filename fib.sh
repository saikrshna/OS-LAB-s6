echo "Enter the limit:"
read num
a=0
b=1
if [ $num -eq 0 ];then
	echo "$a"
elif [ $num -eq 1 ];then
	echo "$a"
	echo "$b"
elif [ $num -ge 2 ];then
	echo "$a"
	echo "$b"
	for((i=2;i<num;i++));do
		c=$((a+b))
		a=$b
		b=$c
		echo "$c"
	done
fi
