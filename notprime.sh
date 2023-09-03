echo "Enter the limit: "
read num

echo "The prime numbers are: "
for ((i=2; i<=num; i++));do
	isprime=true
	for ((j=2; j<=i/2; j++));do
		if [ $((i % j)) -eq 0 ];then
			isprime=false
			break
		fi
	done
	if $isprime;then
		echo "$i"
	fi
done


echo "The non-prime numbers are: "
for ((i=0; i<=num; i++));do
	if [ $i -le 1 ];then
		echo "$i"
		continue
	fi
	isprime=true
	for ((j=2; j<=i/2; j++));do
		if [ $((i % j)) -eq 0 ];then
			isprime=false
			break
		fi
	done
	if ! $isprime;then
		echo "$i"
	fi
done

