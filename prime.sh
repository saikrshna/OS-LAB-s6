echo "Enter the number: "
read n

if [ $n -le 1 ]; then
    echo "$n is not a prime number."
    exit
fi


for ((i=2; i<n/2; i++));
do
	isprime=true
	if [ $((n%i)) -eq 0 ]; then
		isprime=false
		break
	fi
done

if $isprime; then
    echo "$n is a prime number."
else
    echo "$n is not a prime number."
fi
