#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

// #define SOL

static int nthread = 1;
static int round = 0;

struct barrier {
  pthread_mutex_t barrier_mutex;
  pthread_cond_t barrier_cond;
  int nthread;      // Number of threads that have reached this round of the barrier
  int round;     // Barrier round
} bstate;

static void
barrier_init(void)
{
  assert(pthread_mutex_init(&bstate.barrier_mutex, NULL) == 0);
  assert(pthread_cond_init(&bstate.barrier_cond, NULL) == 0);
  bstate.nthread = 0;
}

static void 
barrier()
{	
	pthread_mutex_lock(&bstate.barrier_mutex);
	bstate.nthread++;
	if(bstate.nthread == nthread){//라운드가 끝나는 경우
		bstate.nthread=0;//변수를 초기화 시켜준다.
		pthread_cond_broadcast(&bstate.barrier_cond);//라운드가 끝났으므로 모든 thread를 꺠워준다.
		bstate.round++;//라운드 카운트를 하나 증가시킨다.
	}
  	else if( bstate.nthread < nthread){//아직 라운드가 끝나지 않은 경우
		pthread_cond_wait(&bstate.barrier_cond,&bstate.barrier_mutex);//라운드가 끝날 때까지 sleep
	}
	pthread_mutex_unlock(&bstate.barrier_mutex);

}

static void *
thread(void *xa)
{
  long n = (long) xa;
  long delay;
  int i;

  for (i = 0; i < 20000; i++) {
    int t = bstate.round;
    assert (i == t);
    barrier();
    usleep(random() % 100);
  }
}

int
main(int argc, char *argv[])
{
  pthread_t *tha;
  void *value;
  long i;
  double t1, t0;

  if (argc < 2) {
    fprintf(stderr, "%s: %s nthread\n", argv[0], argv[0]);
    exit(-1);
  }
  nthread = atoi(argv[1]);
  tha = malloc(sizeof(pthread_t) * nthread);
  srandom(0);

  barrier_init();

  for(i = 0; i < nthread; i++) {
    assert(pthread_create(&tha[i], NULL, thread, (void *) i) == 0);
  }
  for(i = 0; i < nthread; i++) {
    assert(pthread_join(tha[i], &value) == 0);
  }
  printf("OK; passed\n");
}
