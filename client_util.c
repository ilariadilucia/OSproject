#include "utility.h"
#include "struct_util.c"

int ret;


/* ----------------------------- READ MESSAGES --------------------------------------*/

int read_msg(int sockfd){
    char buff[BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    int msg_len;
    sprintf(buff, "Leggere");
    msg_len = strlen(buff);
    while ( (ret = send(sockfd, buff,msg_len , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di read_msg");
    }
    
    memset(buff, 0, BUFF_SIZE);

    while (1){
        //ricevo il messaggio dal server
        while ((msg_len = recv(sockfd, buff, BUFF_SIZE, 0))<0){
            if (errno == EINTR) continue;
            ERROR_HELPER(ret, "Errore nella recv di read_msg");
        }
       
        //controllo se il messaggio non è STOP
        if (strcmp(buff, "STOP")==0) {
			printf("Bacheca vuota\n");
			break;
       }
        //stampo il messaggio
		printf("%s\n", buff);
		memset(buff, 0, BUFF_SIZE);
		
        sprintf(buff, "OK");
       
        
        while ( (ret = send(sockfd, buff,strlen(buff), 0)) < 0) {
            if (errno == EINTR) continue;
        }
        
        
        printf("\n\n");
        
        memset(buff, 0, BUFF_SIZE);

    }
    return 0;
}


// ---------------------------------- SEND MESSAGES -------------------------------------
int send_msg(int sockfd){
    char buff[BUFF_SIZE];
    int ret, recv_bytes, msg_len;
    char mittente[BUFF_SIZE];
    char oggetto[BUFF_SIZE];
    char testo[BUFF_SIZE*3];
    char chiave[BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    sprintf(buff, "Spedire");
    msg_len = strlen(buff);
    while ( (ret = send(sockfd, buff,msg_len , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, BUFF_SIZE, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    
    while (1){
    //manda il mittente
    printf("Inserire il nome del mittente del messaggio:\n");
    scanf("%s", mittente);
    if (mittente != NULL) break;
	}

    while ( (ret = send(sockfd, mittente,BUFF_SIZE , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di send_msg");
    }
    printf("%d\n", recv_bytes);
    buff[recv_bytes] = '\0';
    
	while (1){
    //manda l'oggetto
    printf("Inserire l'oggetto del messaggio:\n");
    scanf("%s", oggetto);
    if (oggetto != NULL) break;
	}
    while ( (ret = send(sockfd, oggetto,strlen(oggetto) , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di send_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    while (1){
    //manda il testo
    printf("Inserire il testo del messaggio:\n");
    scanf("%s", testo);
	//fgets(testo, BUFF_SIZE, stdin);
	
    if (testo != NULL) break;
	}
    while ( (ret = send(sockfd, testo,strlen(testo) , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di send_msg");
    }
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di send_msg");
    }
    
    //riceve la chiave
    while ( (recv_bytes = recv(sockfd, buff, BUFF_SIZE, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di send_msg");
    }
    buff[recv_bytes] = '\0';
    strcpy(chiave, buff);
    
    printf("La tua chiave è: %s\n", chiave);

    return 0;
}



//------------------------------------- CANCELLARE ------------------------------
int delete_msg(int sockfd){
    char buff[BUFF_SIZE];
    int ret, recv_bytes, msg_len;
    char psw[BUFF_SIZE];
    char utente[BUFF_SIZE];
    char oggetto[BUFF_SIZE];
    memset(buff, 0, BUFF_SIZE);
    sprintf(buff, "Cancellare");
    msg_len = strlen(buff);
    while ( (ret = send(sockfd, buff,msg_len , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di delete_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di delete_msg");
    }
    while (1){
    printf("Inserire nome utente:\n");
    scanf("%s", utente);
    if (utente != NULL) break;
}
    //mando l'utente al server
    while ( (ret = send(sockfd, utente,sizeof(utente) , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di delete_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di delete_msg");
    }
    while (1){
    printf("Inserire oggetto messaggio da cancellare:\n");
    scanf("%s", oggetto);
    if (oggetto != NULL) break;
}
    //mando l'oggetto al server
    while ( (ret = send(sockfd, oggetto,sizeof(oggetto) , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di delete_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di delete_msg");
    }
    while (1){
    printf("Inserire la psw:\n");
    scanf("%s", psw);
    if (psw != NULL) break;
	}
    //mando la password al server
    while ( (ret = send(sockfd, psw,sizeof(psw) , 0)) < 0) {
        if (errno == EINTR) continue;
        ERROR_HELPER(ret, "errore nella send di delete_msg");
    }
    memset(buff, 0, BUFF_SIZE);
    //riceve l'ok dal server
    while ( (recv_bytes = recv(sockfd, buff, 2, 0)) < 0 ) {
        if (errno == EINTR) continue;
        ERROR_HELPER(recv_bytes, "Errore nella recv di delete_msg");
    }
    
    //se ritorna ok la password era giusta e il messaggio è stato cancellato
    if (strcmp(buff, "OK")==0)
        printf("Messaggio cancellato correttamente\n");
    else {
        printf("Problemi nella cancellazione del messaggio\n");
        return 1;
    }
    
    return 0;
}







