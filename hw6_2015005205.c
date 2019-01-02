#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>

#define SOL
#define NBUCKET 5
#define NKEYS 100000
pthread_mutex_t g_lock[5];//한 버킷당 각각의 lock을 걸어주기 위해 lock의 인자를 5개의 배열로 만들었다.

struct entry {
  int key;
  int value;
  struct entry *next;
};
struct entry *table[NBUCKET];
int keys[NKEYS];
int nthread = 1;
volatile int done;


double
now()
{
 struct timeval tv;
 gettimeofday(&tv, 0);
 return tv.tv_sec + tv.tv_usec / 1000000.0;
}

static void
print(void)
{
  int i;
  struct entry *e;
  for (i = 0; i < NBUCKET; i++) {
    printf("%d: ", i);
    for (e = table[i]; e != 0; e = e->next) {
      printf("%d ", e->key);
    }
    printf("\n");
  }
}

static void 
insert(int key, int value, struct entry **p, struct entry *n)
{
  struct entry *e = malloc(sizeof(struct entry));
  e->key = key;
  e->value = value;
  e->next = n;
  *p = e;
}

static 
void put(int key, int value)
{
  int i = key % NBUCKET;
  pthread_mutex_lock(&g_lock[i]);//race condition을 막기위해 insert함수 전체에 lock을 걸어주었다. insert할떄마다
  insert(key, value, &table[i], table[i]);//버킷의 주소가 바뀌므로 한 thread에서 insert함수가 끝난후 다른 thread에서 사용하도록
  pthread_mutex_unlock(&g_lock[i]);//lock을 걸어줄 필요가 있다고 생각했다.
}

static struct entry*
get(int key)
{
  struct entry *e = 0;
  for (e = table[key % NBUCKET]; e != 0; e = e->next) {
    if (e->key == key) break;
  }
  return e;
}

static void *
thread(void *xa)
{
  long n = (long) xa;
  int i;
  int b = NKEYS/nthread;
  int k = 0;
  double t1, t0;

  //  printf("b = %d\n", b);
  t0 = now();
  for (i = 0; i < b; i++) {
    // printf("%d: put %d\n", n, b*n+i);
    put(keys[b*n + i], n);
  }
  t1 = now();
  printf("%ld: put time = %f\n", n, t1-t0);

  // Should use pthread_barrier, but MacOS doesn't support it ...
  __sync_fetch_and_add(&done, 1);
  while (done < nthread) ;

  t0 = now();
  for (i = 0; i < NKEYS; i++) {
    struct entry *e = get(keys[i]);
    if (e == 0) k++;
  }
  t1 = now();
  printf("%ld: get time = %f\n", n, t1-t0);
  printf("%ld: %d keys missing\n", n, k);
  return NULL;
}

int
main(int argc, char *argv[])
{
  pthread_t *tha;
  void *value;
  long i;
  double t1, t0;
  for(int j=0; j<5; j++){
  	pthread_mutex_init(&g_lock[j],0);//각각의 버킷에서 lock을 걸어줄 인자들을 0으로 초기화 해주었다.
  }
  if (argc < 2) {
    fprintf(stderr, "%s: %s nthread\n", argv[0], argv[0]);
    exit(-1);
  }
  nthread = atoi(argv[1]);
  tha = malloc(sizeof(pthread_t) * nthread);
  srandom(0);
  assert(NKEYS % nthread == 0);
  for (i = 0; i < NKEYS; i++) {
    keys[i] = random();
  }
  t0 = now();
  for(i = 0; i < nthread; i++) {
    assert(pthread_create(&tha[i], NULL, thread, (void *) i) == 0);
  }
  for(i = 0; i < nthread; i++) {
    assert(pthread_join(tha[i], &value) == 0);
  }
  t1 = now();
  printf("completion time = %f\n", t1-t0);
}
