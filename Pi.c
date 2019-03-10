#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

double res;

typedef struct Args {
	long n;
	long begin;
	long step;
} Args;

void *cal(void *arg);

int main(int argc, char *argv[]) {
	long i;
	long n = atol(argv[1]);
	int np = atoi(argv[2]);//线程数
	Args *arg;
	double* val;

	pthread_t *pid;
	pid = (pthread_t *)malloc(np * sizeof(pthread_t));
	
	res = 0.0;
	for (i = 0; i < np; i++) {
		arg = (Args *)malloc(sizeof(Args));
		arg->n = n;
		arg->begin = i + 1;
		arg->step = np;
		pthread_create(&pid[i], NULL, cal, (void *)arg);
	}
	for (i = 0; i < np; i++) {
		pthread_join(pid[i], (void *)val);
	}
	res = sqrt(res * 8.0);
	printf("%lf\n", res);
	free(pid);
	return 0;
}

void *cal(void *_arg) {
	long i;
	double val;
	long t = 1;
	Args *arg = (Args *)_arg;
	
	val = 0.0;
	for (i = arg->begin; i <= arg->n;  i += arg->step) {
		t = 2*i-1;
		val += 1.0 / (t * t);
	}
	res += val;
	return NULL;
}
