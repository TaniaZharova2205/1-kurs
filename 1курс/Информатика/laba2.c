#!/bin/bash
# Программа перекодировки текста КОИ-8 в ср1251 
  
function winkoi
{
	num=( 01 02 27 07 04 05 26 32 11 12 13 14 15 16 17 20 22 23 24 25 06 10 03 36 33 35 37 31 30 34 00 21 )
	for i in ${num[*]}
	do
		low=$low"\3$i"
		up=$up"\3` expr $i + 40 `"
	done
	echo $up$low
	return 
}


if test $# -lt 2 
	then echo "Usage: `basename $0` $1 $2 "
	exit −7 
fi 

if ! test -f $1 
	then echo "$1: No such regular file" >&2 
	exit 2 
fi

if ! test -r $1 
	then echo "$1: Permission denied to read" >&2 
	exit 13 
fi 

curdir=`pwd` 
outdir=`expr $2 : '\(.*/\)' \| $curdir`
if [ ! -w $outdir -a ! -e $2 ] 
	then echo "$outdir: Permission denied to write" >&2 
	exit -13 
fi

if test -d $2 
	then echo "$2: Is directory" >&2 
	exit 21  
fi 

if [ -e $2 -a ! -w $2 ] 
	then echo $2: Permission denied to rewrite 
	exit 13  
fi 
if [[ "$3" = "-f" && -f $2 ]] 
	then echo "$2 already exists, rewriting is not possible"
else 
	cat $1 | tr `winkoi` "\300-\337\340-\377" >$2 #from KOI-8 to CP1251
fi	
exit 0 
