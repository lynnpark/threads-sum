#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 100000000
#define NUM_THREADS 5


struct thread_data {
        int thread_num;
        int* nums;
        int len;
        int sum;
};


void* Sum(void* thrdarg) {
   struct thread_data* mydata = (struct thread_data)thrdarg;
   int i;

   for(i=0; i<mydata->len; i++)
   {
    	mydata->sum += mydata->nums[i];
   }

   pthread_exit(NULL);
}

int main () {
   pthread_t threads[NUM_THREADS];
   struct thread_data t_data_arr[NUM_THREADS];
   int* data[NUM_THREADS];
   int rc, i, j, c=0, total_sum=0;


   for( i=0; i<LEN; i++ ){
     data[i] = i%7;
   }

   for(i=0; i<NUM_THREADS; i++) {
      t_data_arr[i].thread_num = i;
      t_data_arr[i].len = 20000000; /* (LEN/NUM_THREADS) */
      for(j=0; j<t_data_arr[i].len; j++) {
        t_data_arr[i].nums[j] = data[c];
        c++;
      }
      rc = pthread_create(&threads[i], NULL, Sum, (void*) &t_data_arr[i]);

      if(rc) {
		printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
      }

	  for(i=0; i<NUM_THREADS; i++){
        rc = pthread_join(threads[i], NULL);
        if(rc) {
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
        }
        total_sum += t_data_arr[i].sum;
      }
      pthread_exit(NULL);
   }


  /* Compute and print sum  */
  printf ("Sum =  %d\n", total_sum );

  free(data);

  pthread_exit(NULL);
}

