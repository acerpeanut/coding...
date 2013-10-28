#ifndef _HUFFUMAN_H_
#define _HUFFUMAN_H_

#include "bigInt.h"
#include <string.h>
typedef struct node{
	bigInt sum;
	char flag;
	struct node* left;
	struct node* right;
}node;

void init(node*p){ p->left=p->right=NULL; init_b(&(p->sum)); p->flag=0; }
void copy(node*a,node*b){ 
	a->sum=b->sum;
	a->flag=b->flag;
	a->left=b->left;
	a->right=b->right;
}
void huffuman(node**p,int i){
	if(i>=2){
		int j,k;
		for(j=0;j<2;j++){
			for(k=0;k<i-j-1;k++){
				if(greatThan(&(p[k]->sum),&(p[k+1]->sum))<=0){
					node* tmp=p[k+1];
					p[k+1]=p[k];
					p[k]=tmp;
				}
			}
		}
		node *q=(node*)malloc(sizeof(node));
		init(q);
		q->left=p[i-2];
		q->right=p[i-1];
		
		plus(&(p[i-1]->sum),&(p[i-2]->sum),&(q->sum));
	
		p[i-1]->flag=1;
		p[i-2]->flag=0;
	
		p[i-2]=q;
		huffuman(p,i-1);
	}
}
void display(node *a,char* s){
	if(a->left && a->right){
		char* s1=(char*)malloc(sizeof(char)*100);
		s[strlen(s)+1]=0;
		s[strlen(s)]=a->flag+'0';

		strcpy(s1,s);
		display(a->left,s);
		display(a->right,s1);
	}
	else{
		print_b(a->sum);
		printf("：%s%d\n",s,a->flag);
		free(s);
	}
}
#endif
