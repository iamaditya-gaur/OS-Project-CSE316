#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int numBowls = 0,
    numCats = 0,
    numMices = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void* catEating(void* arg) {
  long catN = (long)arg + 1;

  sleep(rand()%5 + 1); // randomly access

  pthread_mutex_lock(&lock);
  printf("Cat %ld eating...\n", catN);
  sleep(rand()%3 + 1); // randomly eating times
  printf("Cat %ld done eating...\n", catN);
  pthread_mutex_unlock(&lock);

  pthread_exit(NULL);
}


void* miceEating(void* arg) {
  long miceN = (long)arg + 1;

  sleep(rand()%5 + 1); // randomly access

  pthread_mutex_lock(&lock);
  printf("Mice %ld eating...\n", miceN);
  sleep(rand()%3 + 1); // randomly eating times
  printf("Mice %ld done eating...\n", miceN);
  pthread_mutex_unlock(&lock);

  pthread_exit(NULL);
}

int main(int argc, char** argv) {
  printf("Enter Number Of Bowls: ");
  scanf("%d", &numBowls);

  printf("Enter Number Of Cats: ");
  scanf("%d", &numCats);

  printf("Enter Number Of Mices: ");
  scanf("%d", &numMices);

  printf("\n");

  pthread_t tids_cats[numCats];
  pthread_t tids_mices[numMices];

  for(long i=0; i<numCats; i++)
    pthread_create(&tids_cats[i], NULL, catEating, (void *)i);

  for(long i=0; i<numMices; i++)
    pthread_create(&tids_mices[i], NULL, miceEating, (void *)i);

  for(long i=0; i<numCats; i++)
    pthread_join(tids_cats[i], NULL);

  for(long i=0; i<numMices; i++)
    pthread_join(tids_mices[i], NULL);

  return 0;
}
