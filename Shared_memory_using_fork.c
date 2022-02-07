#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
double RATINGS[40];
int NRATINGS[40];

int main() {
    int N_CUSTOMERS = 20; // liczba klientow
    int N_ROUNDS = 1000000;
    int N_GOODS = 40; //liczba produktow
    int a,b;
    int childPid[N_CUSTOMERS];
    int wpid;
    int status=0;
    //inicjalizacja zmiennych potrzebnych do pamieci wspoldzielonej
    int shmid;
    int KEY =  45281;
    long memory = N_GOODS*sizeof(int)*sizeof(double)*2;
    double *buf;

//for(int i=0;i<N_CUSTOMERS;i++){
  //  childPid[i]=fork();
//}

	//otwieranie pamieci wspoldzielonej
	shmid = shmget(KEY,memory,IPC_CREAT|0600);
	if(shmid==-1) {
		perror("shmget");
		exit(-1);
	}

	//zerowanie tablic
	for(int i = 0;i<N_GOODS;i++){
		RATINGS[i]=0;
		NRATINGS[i]=0;
	}

	buf = (double*)shmat(shmid,0,0);
	if(*buf==-1.00){
		perror("shmat");
		exit(-1);
	}
	//zerowanie bufora
	for(int i =0;i<N_GOODS*2;i++){
		buf[i]=0;
	}

   // for (int i = 0; i < N_CUSTOMERS; i++) {
      for(int i =0;i<N_CUSTOMERS;i++) {
	childPid[i]=fork();
	if(childPid[i]==0){
        for (int j = 0; j < N_ROUNDS; j++) {
           	 srand(time(NULL)+j); //inicjalizacja randu
		 b = rand() % N_GOODS; //losowanie produktu jednego z liczb N_GOODS
                NRATINGS[b]+=1;
		 a = rand() % 11; // ocena tego produktu
		RATINGS[b]=(((NRATINGS[b]-1)*RATINGS[b]+a)/NRATINGS[b]);
		buf[b]=buf[b]+1;
		buf[b+N_GOODS]=RATINGS[b];

        }
	exit(1);
    }else {
}}
while ((wpid = wait(&status)) > 0);
int suma=0;
for(int i=0;i<40;i++) {suma+=buf[i];}
 printf("SUMA %d \n",suma);
	for (int k = 0; k <40; k++) {
    printf("Numer produktu %d Ilosc zakupionych produktow [%d] Srednia Ocena %f  \n",
		k, (int)buf[k],buf[k+N_GOODS]);

}
    return 0;
}

