#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define N 100000
#define CORRECTNESS 0
#define LIMIT 100000
int handleInvalidNumber(int value){
    return value * 3;
}
int handleValidNumber(int value){
    return value * 2;
}
char checkValid1(int value){
  /* zombie codes aiming to increase time for every if */
  sleep(0.0001);
  return value % 2 == 0;
}
char rule1(int value) {
  /* zombie codes aiming to increase time for every if */
  sleep(0.00001);
  return value % 5 == 0;
}
char rule2(int value) {
  /* zombie codes aiming to increase time for every if */
  sleep(0.00001);
  return value % 11 == 0;
}
char rule3(int value) {
  /* zombie codes aiming to increase time for every if */
  sleep(0.00001);
  return value % 2 == 0;
}
char checkValid2(int value){
    return rule1(value) || rule2(value) || rule3(value);
}
char strangeSum_1(long long int v[], long long int p[], long long int limit)
{

      long long int i;
      p[0] = v[0];
      for ( i = 1; i < N; i++ ) {
        p[i] = p[i-1] + v[i];
        if (checkValid1(v[i])) {
            p[i] = p[i] + handleValidNumber(v[i]);
        }
        else {
            p[i] = p[i] + handleInvalidNumber(v[i]);
        }
      }
      i--;
      #if CORRECTNESS == 1
      printf("sum result: %lld\n", p[i]);
      #endif
      return p[i] > limit;
}
char strangeSum_3(long long int v[], long long int p[], long long int limit)
{
      long long int i;
      p[0] = v[0];
      for ( i = 1; i < N; i++ ) {
        p[i] = p[i-1] + v[i];
        if (checkValid2(v[i])) {
            p[i] = p[i] + handleValidNumber(v[i]);
        }
        else {
            p[i] = p[i] + handleInvalidNumber(v[i]);
        }
      }
      i--;
      #if CORRECTNESS == 1
      printf("sum result: %lld\n", p[i]);
      #endif
      return p[i] > limit;
}
char strangeSum_sol(long long int v[], long long int p[], long long int limit)
{
      long long int i;
      p[0] = v[0];
      long long int acc = v[0];
      for ( i = 1; i < N; i++) {
        int temp = v[i];
        acc += temp;
	int increament = 0;
	sleep(0.0001);
        if(temp % 2 == 0) {increament = handleValidNumber(temp);}
        else {increament = handleInvalidNumber(temp);}
        acc += increament;
        #if CORRECTNESS == 0
          if(acc > limit) {return 1;} 
        #endif
        p[i] = acc;
      }
      #if CORRECTNESS == 1
      i--;
      printf("sum result: %lld\n", p[i]);
      #endif
      return p[i] > limit;
}
void generateDataSet(int type, long long int* v) {
  if (type == 1) {
      for(long long int i = 0; i < N; i++) {
    	v[i] = 2 * i;
      }
  }
  else if (type == 2) {
      for(long long int i = 0; i < N; i++) {
    	v[i] = 5 * i;
      }
  }
  else if (type == 3){
      for(long long int i = 0; i < N; i++) {
        int ran = rand() % 2;
    	v[i] = ran * 5 + (1 - ran) * 2;
      }
  }
  else if (type == 4) {
      for(long long int i = 0; i < N/4; i++) {
        v[i] = 0;
      }
      for(long long int i = N/4; i < N; i++) {
        v[i] = 1;
      }
  }
  else if (type == 5) {
      for(long long int i = 0; i < N; i++) {
        v[i] = rand() % 2;
      }
  }
  else if (type == 6) {
      for(long long int i = 0; i < N; i++) {
        v[i] = i+2;
      }
  }
}
void testDataSet_3(int type) {
  clock_t start, finish;
  long long int *v = (long long int *)malloc(N * sizeof(long long int));
  generateDataSet(type, v);
  long long int p[N];
  start = clock();
  char trueValue = strangeSum_3(v, p, N);
  finish = clock();
  double total = (double) (finish - start) / CLOCKS_PER_SEC;
  printf("For dataset %d, final result: %d, total time:%f\n", type, trueValue, total);
}
void testDataSet_1(int type) {
  clock_t start, finish;
  long long int *v = (long long int *)malloc(N * sizeof(long long int));
  generateDataSet(type, v);
  long long int p[N];
  start = clock();
  char trueValue = strangeSum_1(v, p, LIMIT);
  finish = clock();
  double total = (double) (finish - start) / CLOCKS_PER_SEC;
  printf("For dataset %d, final result: %d, total time:%f\n", (type - 3), trueValue, total);
  free(v);
}
void testDataSet_sol(int type) {
  clock_t start, finish;
  long long int *v = (long long int *)malloc(N * sizeof(long long int));
  generateDataSet(type, v);
  long long int p[N];
  start = clock();
  char trueValue = strangeSum_sol(v, p, LIMIT);
  finish = clock();
  double total = (double) (finish - start) / CLOCKS_PER_SEC;
  printf("For dataset %d, final result: %d, total time:%f\n", (type - 3), trueValue, total);
  free(v);
}
int main(int argc, char** argv[]) {
  if(argc == 1) {
      printf("Please input the problem you want to test!\n./problem6 <No.problem>\n");
      exit(1);
  }
  if(!strcmp(argv[1], "1")) {
      printf("Running Problem 6.1\n");
      testDataSet_1(4);
      testDataSet_1(5);
  }
  if(!strcmp(argv[1], "2")) {
      printf("Running Problem 6.2\n");
      printf("Baseline:\n");
      testDataSet_1(6);
      printf("After optimziations:\n");
      testDataSet_sol(6);
  }
  else if(!strcmp(argv[1], "3")) {
      printf("Running Problem 6.3\n");
      testDataSet_3(1);
      testDataSet_3(2);
      testDataSet_3(3);
  }
}
