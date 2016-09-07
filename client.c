#include "utility.h"
#include "client_util.c"

//descrittore del socket del client
int sockfd;

// --------------------------- CLOSE_CONNECTION----------------------
void close_connection(){
	char buff[BUFF_SIZE];
    
    sprintf(buff, "Close");
    while (send(sockfd, buff, BUFF_SIZE,0) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(-1, "Errore nella send di close_connection\n");
    }
    
    int x = close(sockfd);
    ERROR_HELPER(x, "Errore nella chiusura del socket\n");
    printf("Connessione chiusa\n");
    
    exit(0);
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

	int conn;

	// buffer di ricezione
	memset(buff, 0, BUFF_SIZE);
		
	// apertura socket
	sockfd = socket(PF_INET, SOCK_STREAM,0);
	ERROR_HELPER(sockfd,"Errore nell'apertura del socket\n");
	
	// struct dell'indirizzo di destinazione
	struct sockaddr_in ind_serv = {0};
	ind_serv.sin_family= AF_INET;
	ind_serv.sin_port = htons(PORTA_SERVER);
	ind_serv.sin_addr.s_addr = inet_addr(IND_SERVER);
	memset(ind_serv.sin_zero, 0, sizeof ind_serv.sin_zero); 
	
	
	// connessione con il server
	conn = connect(sockfd, (struct sockaddr*)&ind_serv, sizeof ind_serv );
	ERROR_HELPER(conn, "Errore nella connessione con il server\n" );


	
	int comando, controllo;
	//LOOP PRINCIPALE DELLE FUNZIONI
	while (1){
		printf("Lista comandi:\n 1 --> leggere la bacheca\n 2 --> spedire un nuovo messaggio\n 3 --> cancellare un messaggio\n 4 --> exit\n");
		printf("Inserisci un numero:\n");
		scanf("%d", &comando);
		switch (comando){
			case 1 : {
				controllo = read_msg(sockfd);
				if (controllo != 0) ERROR_HELPER(-1, "Errore lettura\n");
				break;
			}
			case 2 : {
				controllo = send_msg(sockfd);
				if (controllo != 0) ERROR_HELPER(-1, "Errore spedizione\n");
				break;
			}
			case 3 : {
				controllo = delete_msg(sockfd);
				if (controllo != 0) ERROR_HELPER(-1, "Errore cancellazione\n");
				break;
			}
			case 4 : {
				 close_connection(sockfd);
				return 0;

			}
			default : { printf("Comando non valido, inserire di nuovo\n"); 
				break;
			}
		}
		
	}

	return 0;
	
}

