#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t lock;

void *increment(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);
        counter++; 
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
pthread_mutex_t t1;
void *my(void *str){
pthread_mutex_lock(&t1);
    printf("%s",str);
    pthread_mutex_unlock(&t1);
}

int main() {


    pthread_t t1;
    pthread_t t2;
    pthread_mutex_init(&t1,NULL);

    pthread_create(&t1,NULL,my,"nice work");
    pthread_create(&t2,NULL,my,"888");

pthread_join(t1,NULL);
pthread_join(t2,NULL);

}
