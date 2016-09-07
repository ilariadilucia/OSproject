#include "server_util.c"
#include "utility.h"
#include "struct_util.c"

int sockfd;

int close_connection(){
    // chiusura del file
    ERROR_HELPER(ret, "Errore nella chiusura del file\n");
    ret =close(sockfd);
    ERROR_HELPER(ret, "Errore nella chiusura del server\n");
    printf("Connessione chiusa\n");
    
    return 0;
    
}

	
int main(){
	
	signal(SIGINT, close_connection);
    signal(SIGTERM, close_connection);
    signal(SIGQUIT, close_connection);
    signal(SIGILL, close_connection);
    signal(SIGHUP, close_connection);
    signal(SIGSEGV, close_connection);
    signal(SIGPIPE, close_connection);
    
	char buff[BUFF_SIZE];
	//inizializzazione del semaforo
	ret = pthread_mutex_init(&sem, NULL);
	if (ret != 0) ERROR_HELPER(-1, "Errore nella creazione del semaforo\n");
	
    //inizializzazione del semaforo struct
    ret = pthread_mutex_init(&sem_struct, NULL);
    if (ret != 0) ERROR_HELPER(-1, "Errore nella creazione del semaforo struct\n");


	int sockaddr_len = sizeof(struct sockaddr_in);
	int client_fd;
	struct sockaddr_in server_addr = {0};  // indirizzo del server
	
	struct sockaddr_in* client_addr = calloc(1, sizeof(struct sockaddr_in));  // indirizzo del client
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	ERROR_HELPER(sockfd, "Errore nell'apertura del socket\n");
	
	server_addr.sin_family= AF_INET;
	server_addr.sin_port = htons(PORTA_SERVER);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int reuse = 1;
	ret = setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
	ERROR_HELPER(ret, "Cannot set SO_REUSEDADDR option\n");
	
	// BIND
	ret = bind(sockfd, (struct sockaddr*) &server_addr, sockaddr_len);
	ERROR_HELPER(ret, "Errore nella bind\n");
	
	//LISTEN
	ret = listen(sockfd, MAX_USERS);
	ERROR_HELPER(ret, "Errore nella listen\n");
	

	

	// WHILE PRINCIPALE
	while (1){
		//accetto le connessioni
		memset(buff, 0, BUFF_SIZE);
		client_fd = accept(sockfd, (struct sockaddr*) client_addr, (socklen_t*)&sockaddr_len);
		
		if (client_fd == -1 && errno == EINTR) continue;
		ERROR_HELPER(client_fd, "Errore nell'accept\n");
		
		pthread_t thread;
		
		int* arg = &client_fd;
	
		if (pthread_create(&thread, NULL, funzione, (void*)arg) != 0){
			fprintf(stderr, "Impossibile creare un nuovo thread, errore %d\n", errno);
			exit(1);
		}

		if (pthread_detach(thread) != 0) ERROR_HELPER(-1, "Errore nel detach del thread\n");
	    

		client_addr = calloc(1, sizeof(struct sockaddr_in));
    }
	
	pthread_mutex_destroy(&sem);
	return 0;
}



