if test "$1" = "-a"
then
     if [ ! -z "$2" ]
     then
         shift 1;
	 for var in "$@"
         do
	    ls -1a "$var" | wc -l
	 done
      else
	    ls -1a | wc -l
     fi

elif [ "$1" != "-a" ] 
then
     if [ ! -z "$1" ]
     then
	for var in "$@"
	do
	   ls -1 "$var" | wc -l
        done
      else
	   ls -1 | wc -l
fi
fi
