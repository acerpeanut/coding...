#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int substr(char*s, char*p,int **index,int* size){ // ‘少年’方法的实现
	int i=0,k=0,l=0,m=0;
	int *a=(int*)malloc(sizeof(int)*100);
	int *b=(int*)malloc(sizeof(int)*100);
	int *t;
	do{
		if(p[0]==s[i]) a[k++]=i;  // a存储匹配p[0]的字符的位置
	}while(s[i++]);
	while(++l<strlen(p)){  // 模式串的第l个字符
		for(i=0,m=0;i<k;i++){
			if(!s[a[i]+l]) break;
		       	s[a[i]+l]==p[l] && (b[m++]=a[i]);
		}
		t=a,a=b,b=t;    // 交换 a 和 b
		k=m;     // k 为 a 长度
	}
	*size=k;
	*index=a;
	free(b);
	return 0;
}
int main(){
	int *a,size,i;
	char s[100],p[100];
	scanf("%s%s",s,p);
	substr(s,p,&a,&size);
	for(i=0;i<size;i++) printf("%d\n",a[i]);
	return 0;
}
