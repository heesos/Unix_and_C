#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/un.h>
#include <sys/socket.h>

#define GNIAZDKO_SERWERA "/tmp/gniazdko_serwera"
#define BUF_SIZE 64
#define TRUE 1

double RATINGS[40];
int NRATINGS[40];

int main() {
    int N_CUSTOMERS = 20; // liczba klientow
    int N_ROUNDS = 1000000;
    int N_GOODS = 40; //liczba produktow
    int a,b,c;
    int childPid[N_CUSTOMERS];
    int wpid;
    int status=0;
	int packs=0;
	int sock;
	socklen_t serv_len, cli_len;
	struct sockaddr_un serv_addrstr, cli_addrstr;
	char mes[BUF_SIZE];

	sock = socket(PF_UNIX,SOCK_DGRAM, 0);
	serv_addrstr.sun_family=AF_UNIX;
	strcpy(serv_addrstr.sun_path,GNIAZDKO_SERWERA);

	unlink(GNIAZDKO_SERWERA);
	serv_len = sizeof(serv_addrstr);
	if (bind(sock, (struct sockaddr *)&serv_addrstr, serv_len) == -1){
		perror("BIND ERROR");
		exit(-1);
	}


	//zerowanie tablic
	for(int i = 0;i<N_GOODS;i++){
		RATINGS[i]=0;
		NRATINGS[i]=0;
	}

	//wysylka na serwer
      for(int i =0;i<N_CUSTOMERS;i++) {
	childPid[i]=fork();
	if(childPid[i]==0){
        for (int j = 0; j < N_ROUNDS; j++) {
           	 srand(time(NULL)+j); //inicjalizacja randu
		 b = rand() % N_GOODS; //losowanie produktu jednego z liczb N_GOODS
                //NRATINGS[b]+=1;
		 a = rand() % 11; // ocena tego produktu
		//RATINGS[b]=(((NRATINGS[b]-1)*RATINGS[b]+a)/NRATINGS[b]);
		memcpy(mes,&b,sizeof(int));
		memcpy(mes+sizeof(int),&a,sizeof(int));
		sendto(sock,mes,sizeof(mes),0,(struct sockaddr *)&serv_addrstr,serv_len);
        }
	exit(1);
    }
}
	//odbior wiadomosci z serwera
	while(TRUE) {
		if(packs==N_CUSTOMERS*N_ROUNDS) break;
		c=recvfrom(sock,&mes,sizeof(mes),0,(struct sockaddr *)0,0);
		if (c==-1) {
			perror("blad recvfrom");
			printf("Klient: wyslane %d, blad odczytu odpowiedzi\n", c);
		}else {
			memcpy((void *)&b, (void *)mes, sizeof(int));
			memcpy((void *)&a, (void *)(mes+sizeof(int)), sizeof(int));
			NRATINGS[b]+=1;
			RATINGS[b]=(((NRATINGS[b]-1)*RATINGS[b]+a)/NRATINGS[b]);
			packs++;
		}
	}




while ((wpid = wait(&status)) > 0);

int suma=0;
	for (int k = 0; k <40; k++) {
    		printf("Numer produktu %d Ilosc zakupionych produktow [%d] Srednia Ocena %f  \n",
		k, NRATINGS[k],RATINGS[k]);
		suma=suma+NRATINGS[k];

}
	printf("SUMA: %d\n",suma);
    return 0;
}

