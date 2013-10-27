#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT 100000000
typedef struct bigInt{
	unsigned char l;
	unsigned int *p;
}bigInt;

void init_b(bigInt *a){
	a->l=1;
	a->p=(unsigned int*)malloc(sizeof(unsigned int));
	*(a->p)=0;
}
void print_b(bigInt a){
	int i;
	for(i=a.l-1;i>=0;i--){
		printf("%08d",a.p[i]);
	}
}

void plusplus(bigInt *a){
	int i,j;
	unsigned int *q;
	for(i=0;i<a->l;i++){
		if(a->p[i]++ > MAX_COUNT){
			a->p[i] -= MAX_COUNT; 
			if(i==a->l-1){
				q=(unsigned int*)malloc(sizeof(unsigned int)*(a->l+1));
				for(j=0;j<a->l;j++){
					q[j] = a->p[j];
				}
				q[a->l]=0;
				free(a->p);
				a->p=q;
				a->l++;
			}
		}
		else{
			break;
		}
	}
}
int greatThan(bigInt *a,bigInt *b){
	if(a->l > b->l){
		return 1;
	}
	else if(a->l < b->l){
		return -1;
	}
	else{
		int i=a->l;
		while(i-- > 0){
			if(a->p[i] > b->p[i]) return 1;
			else if(a->p[i] < b->p[i]) return -1;
		}
		return 0;
	}
}

void plus(bigInt *a,bigInt *b,bigInt *c){
	bigInt *d=(bigInt*)malloc(sizeof(bigInt));
	int i,j;
	unsigned int *q;
	d->l = (a->l > b->l ? a->l : b->l);
	d->p = (unsigned int*)malloc(sizeof(unsigned int)*(d->l));
	for(i=0;i<a->l;i++){
		d->p[i] = a->p[i];
	}
	for(;i<d->l;i++){
		d->p[i]=0;
	}
	for(i=0;i<b->l;i++){
		d->p[i] += b->p[i];
		if(d->p[i] >= MAX_COUNT){
			if(i==d->l-1){
				q=(unsigned int*)malloc(sizeof(unsigned int)*(d->l+1));
				for(j=0;j<d->l;j++){
					q[j]=d->p[j];
				}
				q[d->l]=0;
				free(d->p);
				d->p=q;
				d->l++;
			}
			d->p[i] -= MAX_COUNT;
			d->p[i+1]++;
		}
	}
	c->l = d->l;
	c->p = d->p;
	free(d);
}
#endif
