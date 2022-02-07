#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

double RATINGS[40];
int NRATINGS[40];

int main() {
    int N_CUSTOMERS = 2; // liczba klientow
    int N_ROUNDS = 10000;
    int N_GOODS = 40; //liczba produktow
    int a,b;

    //inicjalizacja zmiennych potrzebnych do pamieci wspoldzielonej
    int shmid;
    int KEY =  45281;
    long memory = N_GOODS*sizeof(int)*sizeof(double)*2;
	double *buf;
	//otwieranie pamieci wspoldzielonej
	shmid = shmget(KEY,memory,IPC_CREAT|0600);

	//zerowanie tablic
	for(int i = 0;i<N_GOODS;i++){
		RATINGS[i]=0;
		NRATINGS[i]=0;
	}

	buf = (double*)shmat(shmid,0,0);
	//zerowanie bufora
	for(int i =0;i<N_GOODS*2;i++){
		buf[i]=0;
	}

    for (int i = 0; i < N_CUSTOMERS; i++) {
        for (int j = 0; j < N_ROUNDS; j++) {
           	 srand(time(NULL)+j); //inicjalizacja randu
		 b = rand() % N_GOODS; //losowanie produktu jednego z liczb N_GOODS
                NRATINGS[b]+=1;
		 a = rand() % 11; // ocena tego produktu
		RATINGS[b]=(((NRATINGS[b]-1)*RATINGS[b]+a)/NRATINGS[b]);
		buf[b]=buf[b]+1;
		buf[b+N_GOODS]=RATINGS[b];
        }
    }
	for (int k = 0; k <40; k++) {
    printf("Numer produktu %d Ilosc zakupionych produktow [%d] Srednia Ocena %f  \n",
		k, (int)buf[k],buf[k+N_GOODS]);
}
	for(int i=0;i<40;i++) {
		printf( "ilosc %d ocena %lf \n",NRATINGS[i],RATINGS[i]);
}
    return 0;
}
