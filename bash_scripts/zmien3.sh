for file in "$@"
do
	if expr "$file" : '.*\.txt$' > /dev/null
	then
		x=`echo "$file" | sed s/.txt/_org.txt/`
		mv "$file" "$x"
	else
		echo "$file ten plik nie ma koncowki .txt"
	fi

done

