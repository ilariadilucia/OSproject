#ifndef _UTILITYH_
#define _UTILITYH_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <sys/types.h>  //per la funzione socket	
#include <sys/socket.h>   //per la funzione socket
#include <netinet/in.h>  // per le strutture dati sockaddr
#include <pthread.h>
#include <semaphore.h>
#include <signal.h> // gestione segnali
#include <unistd.h> // per i file
#include <fcntl.h>
#include <arpa/inet.h>
#include <signal.h>

#define BUFF_SIZE 1024 // dimensione del buffer
#define IND_SERVER "127.0.0.1" // indirizzo del server (locale)
#define PORTA_SERVER 3025
#define MAX_USERS 100


pthread_mutex_t sem;
//semaforo struct
pthread_mutex_t sem_struct;

//struct per il messaggio
typedef struct {
	char mittente[BUFF_SIZE];
	char oggetto[BUFF_SIZE];
	char testo[3*BUFF_SIZE];
    char psw[BUFF_SIZE];
} messaggio;

//struct per la bacheca (lista collegata)
typedef struct nodo_bacheca {
    messaggio x;
    struct nodo_bacheca* next;
} bacheca;

bacheca* b;


#define ERROR_HELPER(ret, message)  do {                                \
            if (ret < 0) {                                              \
                fprintf(stderr, "%s: %s\n", message, strerror(errno));  \
                exit(EXIT_FAILURE);                                     \
            }                                                           \
        } while (0)



#endif

