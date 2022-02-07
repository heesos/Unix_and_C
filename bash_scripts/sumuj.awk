BEGIN{
FS=" "
}

{
flag=1;
	if (NR == 1) {
	imie[NR]=$1;
	nazwisko[NR]=$2;
	indeks[NR]=$3;
	punkty[NR]=$4;
	}
	if (NR >= 2) {
	for(x = 1; x<=length(indeks);x++) {
		if( $3 == indeks[x] ) {
		punkty[x]=$4+punkty[x];
		flag = 0;
	}
}
		if(flag > 0) {
		nr=length(indeks)+1;
		imie[nr]=$1;
		nazwisko[nr]=$2;
		indeks[nr]=$3;
		punkty[nr]=$4;
	
	}
	}
}

END{
for(j=1;j<=length(indeks);j++) {
print imie[j],nazwisko[j],indeks[j],punkty[j];
}
}
