#ifndef SERVER_UTIL_H
#define	SERVER_UTIL_H

#include "utility.h"

// per il server
#define MAX_REG 100
#define PORTA_SERVER 3025
#define PATH_FILE  "file.txt"
#define OK2 "ok"
#define NUM_REG_FILE "reg.txt"
#define USER_FILE "user.txt"


pthread_mutex_t sem;
pthread_t thread;
int ret;


//definizioni di funzioni
int read_msg(int sock);
int send_msg(int sock);
int delete_msg(int sock);
int close_connection();
void* funzione(void* arg);


#endif
