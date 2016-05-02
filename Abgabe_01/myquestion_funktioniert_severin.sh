#!/bin/sh
frage="Haben Sie die Frage verstanden? Ja/Nein"
while :
do
	echo "$frage"
	read word
	case $word in
		ja | Ja* )
		echo "1"
		break;
		;;
		nein | Nein* )
		echo "0"
		;;
		* )
		echo "2"
		echo "Programm wird beendet!"
		exit
		;;
	esac
done
