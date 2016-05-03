#!/bin/sh
case $# in
	1) echo $1;
	read word;
	until [ "$word" = "Ja" -o "$word" = "Nein" ]
	do
		echo $1;
		read word;
	done
	if [ "$word" = "Ja" ]
	then
		exit 0
	else 
		exit 1
	fi
	;;
	* ) 
	exit 2
	;;
esac
