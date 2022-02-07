for entry in *
do 
	echo $entry
	x=`echo "$entry" | sed -e 's/ /_/g'`
	mv "$entry" "$x"
done
