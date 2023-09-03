echo "Enter the string:"
read str
rev=""
length=${#str}
echo "length is $length"

for ((i=length-1;i>=0;i--));do
	rev="$rev${str:$i:1}"
done

echo "reversed string is: $rev"
if [ $rev == $str ];then
	echo "Palindrome"
else
	echo "Not Palindrome"
fi
