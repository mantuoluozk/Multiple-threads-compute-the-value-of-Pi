#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Matrix{
    float m[512][512];
}Matrix;
typedef struct Args{
    long n;
    long begin;
    long step;
}Args;
void *cal(void *arg);
void show(Matrix ma);
long n = 512;
Matrix res;
Matrix tmp;
Matrix start;
int main(int argc, char *argv[]){
    long val;
    long np = atol(argv[1]);
	long num = atol(argv[2]);


    for(int i = 0; i < n; i++)
    	for(int j = 0; j < n; j++){
    		res.m[i][j] = 0.00001;
			tmp.m[i][j] = 0.00001;
			start.m[i][j] = 0.00001;
		}
	for(int i = 1 ; i < num; i++){
		pthread_t *pid;
		pid = (pthread_t *)malloc(np * sizeof(pthread_t));
		Args *arg;
		for(int i = 0; i < np; i++){
			arg = (Args *)malloc(sizeof(Args));
			arg->n = n;
			arg->begin = i*(n/np);
			arg->step = i*(n/np) + n/np;
			pthread_create(&pid[i], NULL, cal, (void *)arg);
			
		}
		for (int i = 0; i < np; i++) 
			pthread_join(pid[i],(void*)val);
		free(pid);
//把tmp的的值传给start
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				start.m[i][j] = tmp.m[i][j];
			}
		}
	}
	//show(tmp);
	return 0;
}
void *cal(void *_arg){
    Args *arg = (Args *)_arg;
    for(int i = arg->begin; i < arg->step; i++){
    	for(int j = 0; j < arg->n; j++){
    	    for(int k = 0; k < arg->n; k++){
				if(k==0){
					tmp.m[i][j] = start.m[i][k] * res.m[k][j];
				}
				else{
					tmp.m[i][j] = tmp.m[i][j] + start.m[i][k] * res.m[k][j];
				}
			}
		}
    }
	return NULL;
}   

void show(Matrix ma){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
	    	printf("%.10f",ma.m[i][j]);
	    	printf(" ");
		}
		printf("\n");
    }
}

