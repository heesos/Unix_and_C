#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>

#define _POSIX_SOURCE


pthread_t tid[40];

struct memory {
	double RATINGS[40];
	int NRATINGS[40];
	pthread_mutexattr_t attr[40];
	pthread_mutex_t mutex[40];
};

struct memory *mem;

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
    long memory_shared =sizeof(struct memory);
    double *buf;

	//otwieranie pamieci wspoldzielonej
	shmid = shmget(KEY,memory_shared,IPC_CREAT|0600);
	//if(shmid==-1) {
	//	perror("shmget");
	//	exit(-1);
	//}

	//zerowanie tablic
	for(int i = 0;i<N_GOODS;i++){
		(*mem)->RATINGS[i]=0;
		(*mem)->NRATINGS[i]=0;
	}

//	mem=(struct memory*)shmat(shmid,NULL,0);
//	if((long int)mem==-1.00){
//		perror("shmat");
//		exit(-1);
//	}

	if( (long int)(mem = ((struct memory*) shmat(shmid, NULL, 0))) == -1){
	//perror("shmat");
	//exit(1);
}

	double czas;
    clock_t begin = clock();

for(int i =0; i<N_GOODS;i++) {
	pthread_mutexattr_init(&mem->attr[i]);
	pthread_mutexattr_setpshared(&mem->attr[i],PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&mem->mutex[i],(&mem->attr[i]));
}


 for(int i =0;i<N_CUSTOMERS;i++) {
	childPid[i]=fork();
	if(childPid[i]==0){
	mem=(struct memory*) shmat(shmid,NULL,0);
	if((long int)mem == -1) { perror("shmat"); exit(-1); }
        for (int j = 0; j < N_ROUNDS; j++) {
           	 srand(time(NULL)+j); //inicjalizacja randu
		 b = rand() % N_GOODS; //losowanie produktu jednego z liczb N_GOODS
		 a = rand() % 11; // ocena tego produktu
		pthread_mutex_lock(&mem->mutex[b]);
		mem->NRATINGS[b]++;
		mem->RATINGS[b]=((((mem->NRATINGS[b])-1) * mem->RATINGS[b] + a) /mem->NRATINGS[b]);
		pthread_mutex_unlock(&mem->mutex[b]);
       }
	exit(1);
    }
}


     clock_t end=clock();
czas=(double)(end-begin)/CLOCKS_PER_SEC;
while ((wpid = wait(&status)) > 0);

for(int i =0;i<N_GOODS;i++) {
pthread_mutex_destroy(&mem->mutex[i]);
}

shmdt(NULL);

int suma=0;

for(int i=0;i<40;i++) {suma+=((*mem).NRATINGS[i]);}
 printf("SUMA %d \n",suma);
 printf("CZAS CPU %lf \n",czas);
 printf("CZAS RT \n");

	for (int k = 0; k <40; k++) {
    printf("Numer produktu %d Ilosc zakupionych produktow [%d] Srednia Ocena %f  \n",
		k, mem->NRATINGS[k],mem->RATINGS[k]);
}

    return 0;
}

