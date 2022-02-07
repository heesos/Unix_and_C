if test "$#" -eq "1"
then
for file in *$1
do
	cp -p $file $HOME/.arch/`echo $file | sed s/$1/_arch$1/ `
done
fi
