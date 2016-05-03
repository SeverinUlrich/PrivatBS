#!/bin/sh
hour=$(date +"%H")
zeit=$(date +"%H:%M")
if [ $hour -lt 12 ]; then
	tz="Morgen"
elif [ $hour -lt 15 ]; then
	tz="Tag"
elif [ $hour -lt 18 ]; then
	tz="Nachmittag"
elif [ $hour -lt 23 ]; then
	tz="Abend"
else
	echo "Gute Nacht"
fi
echo "Guten $tz $USER, die Uhrzeit betraegt: $zeit Uhr." 
