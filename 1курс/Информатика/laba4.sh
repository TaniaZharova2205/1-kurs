#!/bin/bash

string=$1
t=$2

if [ $# -ne 2 ]
	then echo "введите 2 аргумента"
	exit -1
fi

k1=0
k2=0
k3=0

case $t in
	[A-Za-z])
		k1=1
		;;
	[0-9])
		k2=1
		;;
	[\.,\!\(\)\"\?\;:])
		k3=1
		;;
esac

if [ $k1 == 1 ]
	then string=`echo $string | tr -cd [A-Za-z]`
fi

if [ $k3 == 1 ]
	then string=`echo $string | tr -cd [\.,\!\(\)\"\?\;:]`
fi

if [ $k2 == 1 ]
	then string=`echo $string | tr -cd [0-9]`
fi

count=${#string}
echo $count
exit $count
