#ifndef CLIENT_UTIL_H
#define	CLIENT_UTIL_H

//funzione che legge tutti i messaggi dalla bacheca
int read_msg(int sockfd);

//funzione che invia un nuovo messaggio alla bacheca
int send_msg(int sockfd);

//funzione che elimina un messaggio dalla bacheca
int delete_msg(int sockfd);

//funzione che chiude la connessione con il socket
int close_connection(int sockfd);

#endif