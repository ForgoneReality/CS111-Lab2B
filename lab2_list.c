/*NAME: CAO XU
EMAIL: cxcharlie@gmail.com
ID: 704551688*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <string.h>
#include <getopt.h>
#include <sched.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include "SortedList.h"
#include <stdbool.h>

static int threads;
static int iterations;
static int lists;
bool yield_i;
bool yield_d;
bool yield_l;

SortedList_t* bigboi; //now an array of SortedLists

pthread_t* thread_a; //array of the thr4eads
SortedListElement_t* stuffz; //the random stuff all threads will have a part of

int* addme;//prob shouldn't be global but w/e
int opt_yield;
char syncc; //sync is some keyword :/

pthread_mutex_t* lock;
volatile int* spinlock;

long long * waiter;

const char* alph = "abcdefghijklmnopqrstuvwxyz";

void freedom(){
  free(stuffz);
  free(addme);
  free(thread_a);
  if (syncc == 'm' || syncc == 's')
    free(waiter);
  //free spinlocks
  //other frees?
}

void handler(int sig)
{
  if (sig == SIGSEGV)
    {
      fprintf(stderr, "SEGMENTATION FAULT CAUGHT");
      exit(2);
    }
}

unsigned int hash(const char* x){
  return(x[0] % lists);
}

void* thread_worker(void *addd){
  //inserts its elements
  struct timespec start;
  struct timespec end;
  int index = *((int*) addd);
  int i = index * iterations;//extract i from addd, then convert to real offset
  for (int j = 0; j < iterations; j++)
    {
      int hash_index = hash(stuffz[j+i].key);
      switch(syncc)
	{
	case 'n':
	  SortedList_insert(&bigboi[hash_index], &stuffz[j+i]);
	  break;
	case 'm':
	  if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
	    {
	      fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
	      exit(1);
	    }
	  if (pthread_mutex_lock(&lock[hash_index]) != 0)
            {
              fprintf(stderr, "Error occurred while locking: %s", strerror(errno));
              exit(1);
            }
	  if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
	    {
	      fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
	      exit(1);
	    }
	  waiter[index] += (((end.tv_sec - start.tv_sec) * 1000000000) + end.tv_nsec - start.tv_nsec);
	  SortedList_insert(&bigboi[hash_index], &stuffz[j+i]);
          if (pthread_mutex_unlock(&lock[hash_index]) != 0)
            {
              fprintf(stderr, "Error occurred while unlocking: %s", strerror(errno));
              exit(1);
            }
          break;
	case 's':
	  if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
            {
              fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
              exit(1);
            }
	   while(__sync_lock_test_and_set(&spinlock[hash_index], 1))
            {
              //do nothing
            }
	   if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
            {
              fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
              exit(1);
            }
	   waiter[index] += (((end.tv_sec - start.tv_sec) * 1000000000) + end.tv_nsec - start.tv_nsec);
	   SortedList_insert(&bigboi[hash_index], &stuffz[j+i]);
          __sync_lock_release(&spinlock[hash_index]);
          break;
	default:
	  fprintf(stderr, "Shouldn't even be possible to get here");
          exit(1);
          break;
	}
    }
  //get list length
  switch(syncc)
    {
    case 'n':
      for (int i = 0; i<lists; i++)
	{
	  if (SortedList_length(&bigboi[i]) < 0)
	    {
	      fprintf(stderr, "Corrupted list! Invalid length");
	      exit(2);
	    }
	}
      break;
    case 'm':
      if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
	{
	  fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
	  exit(1);
	}
      for (int i=0; i<lists; i++)
	{
	 
	  if (pthread_mutex_lock(&lock[i]) != 0)
	    {
	      fprintf(stderr, "Error occurred while locking: %s", strerror(errno));
	      exit(1);
	    }
	}
      
      if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
        {
          fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
          exit(1);
        }
      waiter[index] += (((end.tv_sec - start.tv_sec) * 1000000000) + end.tv_nsec - start.tv_nsec);
      
      for (int i=0; i<lists; i++)
	{
	  if (SortedList_length(&bigboi[i]) < 0)
	    {
	      fprintf(stderr, "Corrupted sublist %d! Invalid length", i);
	      exit(2);
	    }
	}
      for (int i=0; i< lists; i++)
	{
	  if (pthread_mutex_unlock(&lock[i]) != 0)
	    {
	      fprintf(stderr, "Error occurred while unlocking: %s", strerror(errno));
	      exit(1);
	    }
	}
      break;
    case 's':
      if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
	{
	  fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
	  exit(1);
	}

      for (int i = 0; i<lists; i++)
	{
	  while(__sync_lock_test_and_set(&spinlock[i], 1))
	    {
	      //do nothing
	    }
	}
            
      if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
        {
          fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
          exit(1);
        }
      waiter[index] += (((end.tv_sec - start.tv_sec) * 1000000000) + end.tv_nsec - start.tv_nsec);
      
      for (int i = 0; i < lists; i++)
	{
	  if (SortedList_length(&bigboi[i]) < 0)
	    {
	      fprintf(stderr, "Corrupted sublist %d! Invalid length", i);
	      exit(2);
	    }
	}
      for (int i = 0; i < lists; i++)
	{
	  __sync_lock_release(&spinlock[i]);
	}
      break;
    default:
      fprintf(stderr, "Shouldn't even be possible to get here");
      exit(1);
      break;
    }

  //delete its elements
  for (int j = 0; j < iterations; j++)
    {//want to make sure we're deleting the element tmp we look up, so keep both fxs in same lock
      int hash_index = hash(stuffz[j+i].key);
      switch(syncc)
	{
	case 'n':
	  {
	  SortedListElement_t* tmp = SortedList_lookup(&bigboi[hash_index], stuffz[i+j].key); 
	  if (tmp == NULL)
	    {
	      fprintf(stderr, "Corrupted list! Invalid lookup");
	      exit(2);
	    }
	  //if no sync argument
	  if (SortedList_delete(tmp) == 1)
	    {
	      fprintf(stderr, "Corrupted list! Invalid delete");
	      exit(2);
	    }
	  break;
	  }
	case 'm':
	  {
	    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
	      {
		fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
		exit(1);
	      }
	    
	    if (pthread_mutex_lock(&lock[hash_index]) != 0)
	      {
		fprintf(stderr, "Error occurred while locking: %s", strerror(errno));
		exit(1);
	      }
	    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
	      {
		fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
		exit(1);
	      }
	    waiter[index] += (((end.tv_sec - start.tv_sec) * 1000000000) + end.tv_nsec - start.tv_nsec);


	    SortedListElement_t* tmp = SortedList_lookup(&bigboi[hash_index], stuffz[i+j].key);
	    if (tmp == NULL)
	      {
		fprintf(stderr, "Corrupted list! Invalid lookup");
		exit(2);
	      }
	    //if no sync argument
	    if (SortedList_delete(tmp) == 1)
	      {
		fprintf(stderr, "Corrupted list! Invalid delete");
		exit(2);
	      }
	    if (pthread_mutex_unlock(&lock[hash_index]) != 0)
	      {
		fprintf(stderr, "Error occurred while unlocking: %s", strerror(errno));
		exit(1);
	      }
	    break;
	  }
	case 's':
	  {
	    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
	      {
		fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
		exit(1);
	      }
	    while(__sync_lock_test_and_set(&spinlock[hash_index], 1))
	      {
		//do nothing
	      }
	    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
	      {
		fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
		exit(1);
	      }
	    waiter[index] += (((end.tv_sec - start.tv_sec) * 1000000000) + end.tv_nsec - start.tv_nsec);


	    SortedListElement_t* tmp = SortedList_lookup(&bigboi[hash_index], stuffz[i+j].key);
	    if (tmp == NULL)
	      {
		fprintf(stderr, "Corrupted list! Invalid lookup");
		exit(2);
	      }
          //if no sync argument
	    if (SortedList_delete(tmp) == 1)
	      {
		fprintf(stderr, "Corrupted list! Invalid delete");
		exit(2);
	      }
	    __sync_lock_release(&spinlock[hash_index]);
	    break;
	  }
	default:
	  fprintf(stderr, "should not be possible to get here");
	  exit(1);
	  break;
	  
	}
    }
  return 0;
}

int main(int argc, char **argv) {
  signal(SIGSEGV, handler);
  lists=1;
  opt_yield = 0;
  threads = 1;
  iterations = 1;
  yield_l = false;
  yield_d = false;
  yield_i = false;
  char testname[64];
  strcpy(testname, "list-");
  syncc='n';
  struct option long_options[] = {
				  {"threads", required_argument, NULL, 't'},
				  {"iterations", required_argument, NULL, 'i'},
				  {"yield", required_argument, NULL, 'y'},
				  {"sync", required_argument, NULL, 's'},
				  {"lists", required_argument, NULL, 'l'},
				  {0,0,0,0}
  };

  int i;
  while( (i = getopt_long(argc, argv, "", long_options, NULL)) != -1) {
    switch (i)
      {
      case 't':
	threads = atoi(optarg);
        break;
      case 'i':
        iterations=atoi(optarg);
        break;
      case 'l'://assume given a valid number for l
	lists = atoi(optarg);
	break;
      case 'y':
	if (strlen(optarg) > 3)
	  {
	    fprintf(stderr, "Incorrect usage: --yield takes three possible inputs i, d, and l");
	    exit(1);
	  }
        for (size_t j = 0; j<strlen(optarg); j++)
	  {
	    if (optarg[j] == 'l')
	      yield_l = true;
	    else if (optarg[j] == 'd')
	      yield_d = true;
	    else if (optarg[j] == 'i')
	      yield_i = true;
	    else
	      {
		fprintf(stderr, "Incorrect usage: --yield takes max three possible inputs i, d, and l");
		exit(1);
	      }//i chose to ignore repeats 
	  }
        if(yield_i)
	  {
	  opt_yield |= INSERT_YIELD;
	  strcat(testname, "i");
	  }
       	if(yield_d)
	  {
	  opt_yield |= DELETE_YIELD;
	  strcat(testname, "d");
	  }
       	if(yield_l)
	  {
	  opt_yield |= LOOKUP_YIELD;
	  strcat(testname, "l");
	  }
       	break;
      case 's':
	if (strlen(optarg) > 1)
	  {
	    fprintf(stderr, "Incorrect usage: --sync only takes options 'm' and 's'");
	    exit(1);
	  }
	if (optarg[0] == 'm')
	  {
	    syncc = 'm';
	  }
	else if (optarg[0] == 's')
	  syncc = 's';
	else
	  {
	    fprintf(stderr, "Incorrect usage: --sync only takes options 'm' and 's'");
	    exit(1);
	  }
      	break;
      default:
        fprintf(stderr, "Incorrect Usage: --thread=n, --iterations=n, --yield, and --sync=x are the available options");
        exit(1);
      }
  }

  if (!yield_i && !yield_d && !yield_l)
    {
      strcat(testname, "none-");
    }
  else
    strcat(testname, "-");

  if(syncc == 'n')
    strcat(testname, "none");
  else if (syncc == 'm')
    strcat(testname, "m");
  else if (syncc == 's')
    strcat(testname, "s");
  else{
    fprintf(stderr, "Bro... how did u even get here");
    exit(1);
  }
  
    //Initialization Step:
  atexit(freedom);

  if(syncc=='m' || syncc=='s')
    {
      waiter = (long long *)malloc(threads*sizeof(long long));
      if (waiter == NULL)
	{
	  fprintf(stderr, "Erorr occurred while mallocing: %s", strerror(errno));
	  exit(1);
	}
      memset(waiter, 0, threads * sizeof(long long));
    }

  if(syncc=='m')
    {
      lock = malloc(lists*sizeof(pthread_mutex_t));
      if (lock == NULL)
        {
          fprintf(stderr, "Erorr occurred while mallocing: %s", strerror(errno));
          exit(1);
        }

      for(int i = 0; i < lists; i++)
	{
	  if (pthread_mutex_init(&lock[i], NULL) != 0)
	    {
	      fprintf(stderr, "Error occurred while initializing lock: %s", strerror(errno));
	      exit(1);
	    }

	}
    }

  else if(syncc=='s')
    {
      spinlock = malloc(lists*sizeof(volatile int));
      for( int i = 0; i< lists; i++)
	{
	  spinlock[i] = 0;
	}
    }

  bigboi = malloc(lists*sizeof(SortedList_t));
  if (bigboi == NULL)
    {
      fprintf(stderr, "Erorr occurred while mallocing: %s", strerror(errno));
      exit(1);
    }
  for (int i = 0; i < lists; i++)
    {
      bigboi[i].next = &bigboi[i];
      bigboi[i].prev = &bigboi[i];
      bigboi[i].key = NULL;
    }
  
  stuffz = (SortedListElement_t*)malloc(threads*iterations*sizeof(SortedListElement_t));
  if (stuffz == NULL)
    {
      fprintf(stderr, "Erorr occurred while mallocing: %s", strerror(errno));
      exit(1);
    }

  time_t t;
  /* Intializes random number generator */
  srand((unsigned) time(&t));
  for (int i = 0; i < threads*iterations; i++)
    {
      stuffz[i].key = alph+ (random() % 25);
    }
  
  addme = (int*)malloc(threads * sizeof(int));
  if (addme == NULL)
    {
      fprintf(stderr, "Erorr occurred while mallocing: %s", strerror(errno));
      exit(1);
    }
  
  struct timespec start;
  struct timespec end;

  if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
    {
      fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
      exit(1);
    }

  thread_a = (pthread_t*)malloc(threads*sizeof(pthread_t));
  if (thread_a == NULL)
    {
      fprintf(stderr, "Erorr occurred while mallocing: %s", strerror(errno));
      exit(1);
    }
  
  for (int i = 0; i<threads; i++)
    {
      addme[i] = i;
      if (pthread_create(&thread_a[i], NULL, thread_worker, &addme[i]) != 0)
      {
        fprintf(stderr, "Error occured while creating pthread %d: %s", i, strerror(errno));
        exit(1);
      }
    }
  
  for(int j = 0; j < threads; j++){
    if (pthread_join(thread_a[j], NULL) != 0)
      {
        fprintf(stderr, "Erorr occurred while joining thread %d : %s", j, strerror(errno));
        exit(1);
      }
  }
  if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
    {
      fprintf(stderr, "Error occured while getting clocktime: %s", strerror(errno));
      exit(1);
    }
  //ADD FINAL LENGTH CHECK

  for (int i = 0; i<lists; i++)
    {
      int y = SortedList_length(&bigboi[i]);
      if (y < 0)
	{
	  fprintf(stderr, "Error occurred: bigboi %d length is invalid", i);
	  exit(2);
	}
      else if (y > 0)
	{
	  fprintf(stderr, "Error occurred: final combined list is not empty");
	  exit(2);
	}
    }
  

  /*  int boi = SortedList_length(Node);//Node still points at bigboi's head
  if (boi < 0)
    {
      fprintf(stderr, "Error occurred getting bigboi's length: %s", strerror(errno));
      exit(1);
    }
  if (boi > 0)
    {
      fprintf(stderr, "bigboi not empty: %d", boi);
      exit(2);
    }
  */
  long long column8;
  if(syncc == 'n')
    column8 = 0;
  else
    {
      if (waiter == NULL)
	{
	  fprintf(stderr, "The array containing all wait times is NULL");
	  exit(1);
	}
      for (int k = 0; k < threads; k++)
	{
	  long long l = waiter[k];
	  if (l < 0)
	    {
	      fprintf(stderr, "got negative time for waiting lol");
	      exit(1);
	    }
	  column8+=l;
	}
    }

  long long total_runtime = (((end.tv_sec - start.tv_sec) * 1000000000) + end.tv_nsec - start.tv_nsec);
  int operations = threads * iterations *3;
  printf("%s,%d,%d,%d,%d,%lld,%lld,%lld\n", testname, threads, iterations, lists, operations, total_runtime, (total_runtime/((long long)(operations))), (column8/((long long)(operations)))); 
  exit(0); 
}

//CHECK EXIT ERRORS 1 VS 2
