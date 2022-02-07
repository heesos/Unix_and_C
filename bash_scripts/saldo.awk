BEGIN {FS = ","}
{
if ( NR > 1 ) {
	arr[NR]=$6
	if ( NR > 2) {
		value=arr[NR-1] + $4;
		if( value != $6 ) {
			print "Blad w wierszu",NR
}}}}
END{

}
