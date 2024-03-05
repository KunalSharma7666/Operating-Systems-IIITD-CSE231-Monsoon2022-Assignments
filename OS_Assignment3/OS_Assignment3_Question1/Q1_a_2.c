#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t fork1;
sem_t fork2;
sem_t fork3;
sem_t fork4;
sem_t fork5;

void *phil(int a){
    while(1){
        if(a==1){
            sem_wait(&fork2);      // Right
            sem_wait(&fork1);      // Left
            printf("Philosopher 1 is eating with fork1 and fork2.\n");
            sem_post(&fork2);
            sem_post(&fork1);
            printf("Philosopher 1 is thinking.\n");
        }
        if(a==2){
            sem_wait(&fork3);
            sem_wait(&fork2);
            printf("Philosopher 2 is eating with fork2 and fork3.\n");
            sem_post(&fork3);
            sem_post(&fork2);
            printf("Philosopher 2 is thinking.\n");
        }
        if(a==3){
            sem_wait(&fork4);
            sem_wait(&fork3);
            printf("Philosopher 3 is eating with fork3 and fork4.\n");
            sem_post(&fork4);
            sem_post(&fork3);
            printf("Philosopher 3 is thinking.\n");
        }
        if(a==4){
            sem_wait(&fork5);
            sem_wait(&fork4);
            printf("Philosopher 4 is eating with fork4 and fork5.\n");
            sem_post(&fork5);
            sem_post(&fork4);
            printf("Philosopher 4 is thinking.\n");
        }
        if(a==5){       // breaking the deadlock
            sem_wait(&fork5);
            sem_wait(&fork1);
            printf("Philosopher 5 is eating with fork1 and fork5.\n");
            sem_post(&fork5);
            sem_post(&fork1);
            printf("Philosopher 5 is thinking.\n");
        }
    }
}

int main(){
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;
    pthread_t th5;

    sem_init(&fork1,0,1);
    sem_init(&fork2,0,1);
    sem_init(&fork3,0,1);
    sem_init(&fork4,0,1);
    sem_init(&fork5,0,1);

    pthread_create(&th1,NULL,(void *)phil,1);
    pthread_create(&th2,NULL,(void *)phil,2);
    pthread_create(&th3,NULL,(void *)phil,3);
    pthread_create(&th4,NULL,(void *)phil,4);
    pthread_create(&th5,NULL,(void *)phil,5);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    pthread_join(th5,NULL);

    return 0;
}
