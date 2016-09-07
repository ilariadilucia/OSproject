#include "server_util.h"
#include "utility.h"




// ---------------------------------- SEND MESSAGES -------------------------------------
int send_msg(int sockfd){
    char buff[BUFF_SIZE];
    int recv_bytes;
    int ret, msg_len;
    char mittente[BUFF_SIZE];
    char oggetto[BUFF_SIZE];
    char testo[BUFF_SIZE*3];
    char chiave[BUFF_SIZE];
    //il server manda ok al client
    sprintf(buff, "OK");
    msg_len = strlen(buff);
    while ((ret = send(sockfd, buff, msg_len, 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //arrivo del mittente
    while ( (recv_bytes = recv(sockfd, mittente, BUFF_SIZE, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di read_msg");
    }
    
    mittente[recv_bytes] = '\0';
    printf("mittente : %s\n", mittente);
    memset(buff, 0, BUFF_SIZE);
    //il server manda ok al client
    sprintf(buff, "OK");
    
    while ( (ret = send(sockfd, buff, 2, 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //arrivo dell'oggetto
    while ( (recv_bytes = recv(sockfd, oggetto, sizeof(oggetto), 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di read_msg");
    }
    oggetto[recv_bytes] = '\0';
    printf("oggetto : %s\n", oggetto);
    memset(buff, 0, BUFF_SIZE);

    //il server manda ok al client
    while ( (ret = send(sockfd, "OK", 2, 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //arrivo del testo
    while ( (recv_bytes = recv(sockfd, testo, sizeof(testo), 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di read_msg");
    }
    
    testo[recv_bytes] = '\0';
    printf("testo : %s\n", testo);
    memset(buff, 0, BUFF_SIZE);
    //il server manda ok al client
    while ( (ret = send(sockfd, "OK", 2, 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //generazione della chiave
    char c[BUFF_SIZE];
	int i = rand() % 100 + 1;
	sprintf(c, "%d", i);

    
    strcpy(chiave, c);
    //mandiamo la chiave al client
    while ( (ret = send(sockfd, chiave, strlen(chiave), 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    
    //CHIAMARE LA FUNZIONE CHE AGGIUNGE IN CODA ALLA LOSTA COLLEGATA
    if (insert_new_element(mittente, oggetto, testo, chiave)==0){
		printf("Problemi\n");
	}
    
    return 0;
}


/* ----------------------------- READ MESSAGES --------------------------------------*/
int read_msg(int sockfd){
    char buff[4*BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    int msg_len;
    int recv_bytes;
    bacheca* temp = b;
    pthread_mutex_lock(&sem);
    if (empty()==1) printf("Bacheca ancora vuota\n");
    while (temp != NULL){
		strcat(buff, "Mittente: ");
        strcat(buff, temp->x.mittente);
        strcat(buff, "\n");
        strcat(buff, "Oggetto: ");
        strcat(buff, temp->x.oggetto);
        strcat(buff, "\n");
        strcat(buff, "Testo: ");
        strcat(buff, temp->x.testo);
        strcat(buff, "\n");
        //mando buf al client
        msg_len = strlen(buff);
        while ((ret = send(sockfd, buff, msg_len, 0)) < 0){
            if (errno == EINTR) continue;
            ERROR_HELPER(ret, "Errore nella send di read_msg");
        }
        memset(buff, 0, BUFF_SIZE);
        //aspettiamo l'ok del client
        while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
            if (errno == EINTR) continue;
            ERROR_HELPER(recv_bytes, "Errore nella recv di read_msg");
        }
        
        memset(buff, 0, BUFF_SIZE);
        temp = temp->next;
    }
    pthread_mutex_unlock(&sem);
    memset(buff, 0, BUFF_SIZE);
    sprintf(buff, "STOP");
    while ((ret = send(sockfd, buff, strlen(buff), 0)) < 0){
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "Errore nella send di read_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    
    return 0;
}






//------------------------------------- CANCELLARE ------------------------------
int delete_msg(int sockfd){
    char buff[BUFF_SIZE];
    char utente[BUFF_SIZE];
    char oggetto[BUFF_SIZE];
    char psw[BUFF_SIZE];
    int recv_bytes;
    memset(buff, 0, BUFF_SIZE);
    //il server manda ok al client
    while ( (ret = send(sockfd, "OK", 2, 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di delete_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    
    //arrivo dell'utente
    while ( (recv_bytes = recv(sockfd, utente, sizeof(utente), 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di delete_msg");
    }
    
    utente[recv_bytes] = '\0';
    memset(buff, 0, BUFF_SIZE);
    //il server manda ok al client
    while ( (ret = send(sockfd, "OK", 2, 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di delete_msg");
    }
	memset(buff, 0, BUFF_SIZE);
    //arrivo dell'oggetto
    while ( (recv_bytes = recv(sockfd, oggetto, sizeof(oggetto), 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di delete_msg");
    }
    
    oggetto[recv_bytes] = '\0';
    memset(buff, 0, BUFF_SIZE);
    //il server manda ok al client
    while ( (ret = send(sockfd, "OK", 2, 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di delete_msg");
    }
	memset(buff, 0, BUFF_SIZE);
    //arrivo della password
    while ( (recv_bytes = recv(sockfd, psw, sizeof(psw), 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di delete_msg");
    }
    
    psw[recv_bytes] = '\0';
    memset(buff, 0, BUFF_SIZE);
    
    //la pass è giusta
    if (control_psw(utente, psw) == 1){
        if (delete_element(oggetto)==1) {           
            while ( (ret = send(sockfd, "OK", 2, 0)) < 0) {
                if (errno == EINTR) continue;
                ERROR_HELPER(ret, "errore nella send di delete_msg");
            }
            memset(buff, 0, BUFF_SIZE);

        }
        else {
            
            return 1;
        }
    }
   
    //la psw è sbagliata
    else{
        while ( (ret = send(sockfd, "NON OK", 2, 0)) < 0) {
            if (errno == EINTR) continue;
            ERROR_HELPER(ret, "errore nella send di delete_msg");
        }
        memset(buff, 0, BUFF_SIZE);

        return 1;
    }
    
    return 0;
}


int control_psw(char utente[], char psw[]){
    int ret = 0;
    bacheca* temp = b;
    messaggio temp2;
    
    while (temp != NULL){
		
        temp2 = temp->x;
        
        if (equal(utente, temp2.mittente) == 0){
			
            if (equal(psw, temp2.psw) == 0){
                ret = 1;
            }
        }
        temp = temp->next;
    }
   
    return ret;
}




void* funzione(void* arg){
    char buff2[BUFF_SIZE];
    memset(buff2, 0, BUFF_SIZE);
    int ris, ret;
    int sock_client = *((int*) arg);
    while (1){
		memset(buff2, 0, BUFF_SIZE);
        // aspettiamo che il client ci dica che operazione vuole fare
        while (recv(sock_client, buff2, BUFF_SIZE, 0) < 0 ){
            if (errno == EINTR) continue;
            ERROR_HELPER(-1, "Errore\n");
        }
     
        
        if (strcmp(buff2, "Leggere")==0){
            ris = read_msg(sock_client);
            if (ris != 0) ERROR_HELPER(-1, "Errore nel leggere\n");
            continue;
        }
        else if (strcmp(buff2, "Spedire")==0){
            ris = send_msg(sock_client);
            if (ris != 0) ERROR_HELPER(-1, "Errore nel spedire\n");
            continue;
        }
        else if (strcmp(buff2, "Cancellare")==0){
            ris = delete_msg(sock_client);
            if (ris != 0) ERROR_HELPER(-1, "Errore nel cancellare\n");
            continue;
        }
        
        else if (strcmp(buff2, "Close")==0){
            printf("client chiede la chiusura della connessione\n");
            close_connection(sock_client);
            
            break;
            
        }
        
    }
    
    return 0;
    
}



