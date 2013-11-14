#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree{
	char path[10];
	int len[10];
}tree,*ptree;

int inside(int a,int *b,int len){
	while(len-->=0){
		if(a==b[len]) return 1;
	}
	return 0;
}

int main(){
	int count;
	int tmp;
	scanf("%d",&count);
	int i=0;
	ptree th=(ptree)malloc(sizeof(tree)*count);
	memset(th,0,sizeof(tree)*count);
	char *ch=(char*)malloc(count+1);
	for(i=0;i<count;){
		scanf("%c",&ch[i]);
		if(ch[i]<='z'&&ch[i]>='a'){
			i++;
		}
		else continue;
	}
	int j=0;
	for(i=0;i<count;i++){
		for(j=0;j<count;j++){
			scanf("%d",&tmp);
			th[i].len[j] = (tmp==-1?100000:tmp);
		}
	}
	int visit[10]={0,0,0,0,0,0,0,0,0,0};
	int top=1;
	int less=0;
	for(;top<count;){
		for(j=0;j<count;j++){
			if(! inside(j,visit,top)){
				less=j;
				break;
			}
		}
		for(j=1;j<count;j++){
			if(th[0].len[less]>th[0].len[j] && !inside(j,visit,top)){
				less = j;
			}
		}
		for(j=0;j<count;j++){
			if(th[less].len[j]+th[0].len[less] < th[0].len[j]){
				th[0].len[j] = th[less].len[j]+th[0].len[less];
				strcpy(th[j].path,th[less].path);
				*(th[j].path+strlen(th[j].path))=ch[less];
			}
		}
		visit[top++]=less;
	}
	th[0].len[0] = 0;
	for(i=0;i<count;i++){
		printf("%c(%d) : %s\n",ch[i],th[0].len[i],th[i].path);
	}
	return 0;
}
