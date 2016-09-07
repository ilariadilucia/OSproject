#include "utility.h"

//funzione che ritorna 1 se la bacheca è vuota, 0 altrimenti
int empty(){
    int vuota = 0;
    pthread_mutex_lock(&sem_struct);
    if (b == NULL){
        vuota = 1;
    }
    else vuota = 0;
    pthread_mutex_unlock(&sem_struct);
    return vuota;
}

//inserisce un nuovo elemento nella lista collegata
int insert_new_element(char mittente[], char oggetto[], char testo[], char psw[]){
	
    int ret=0;
    bacheca* temp;
    //creazione messaggio
    messaggio nuovo_elemento;
    strcpy(nuovo_elemento.mittente, mittente);
    strcpy(nuovo_elemento.oggetto, oggetto);
    strcpy(nuovo_elemento.testo, testo);
    strcpy(nuovo_elemento.psw, psw);
   
    //aggiunta messaggio nella bacheca
    
    if (empty()==1){
		
        pthread_mutex_lock(&sem_struct);
        bacheca* nuova_bacheca = (bacheca*)malloc(sizeof(bacheca));
        nuova_bacheca->x = nuovo_elemento;
		
        nuova_bacheca->next = NULL;
        b = nuova_bacheca;
        ret = 1;

    }
    else {
        pthread_mutex_lock(&sem_struct);
        temp = b;
        while(temp->next!=NULL)	{
            temp=temp->next;
        }
         bacheca* nuova_bacheca = (bacheca*)malloc(sizeof(bacheca));
        (*nuova_bacheca).x = nuovo_elemento;
        (*nuova_bacheca).next = NULL;
        temp->next = nuova_bacheca;
        ret = 1;

    }
    pthread_mutex_unlock(&sem_struct);

    return ret;
}





//elimina un elemento dalla lista collegata

int delete_element(char oggetto[]){
	
    int ret = 0;
    
   
    bacheca* temp;
    bacheca* prec;
    messaggio temp2;
    
    
    //se la bacheca è vuota
    if (empty() == 1){
        printf("La bacheca è vuota\n");
        
    }
    //la bacheca non è vuota
    else {
		
        prec = b;
        temp = b;
        while (temp != NULL){
            temp2 = temp->x;
           
            if (equal(temp2.oggetto, oggetto)==0){
            
                if (temp == b){
                    b = temp->next;
                    free((void*)temp);
                   
                    ret = 1;
                }
                else{
                    prec->next = temp->next;
                    free((void*)temp);
                 
                    ret = 1;

                }
            }
            
            if (temp == b){
                temp = temp->next;
            }
            else {
                temp = temp->next;
                prec = prec->next;
            }
            
        }
        ret = 1;
    }

    return ret;
}


int equal(char a[], char b[]){
    int ret;
    ret = strcmp(a, b);
    return ret;
}





