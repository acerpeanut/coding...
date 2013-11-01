#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
void print(char*s,int len){
	char a[1000];
	char *p=a;
	while(len-->0){
		*(p++)=*(s++);
	}
	*p=0;
	printf("%s",a);
}
void webget(char* url){
	int i=0,j;
	char w[100],g[100],s[1000];
	while(*url!='/'){ w[i++]=*url; url++; }
	w[i++]=0;

	struct hostent* phost=gethostbyname(w);
	char* ip=phost->h_addr_list[0];
	sprintf(s,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",url,w);
	printf("send : \n%s\n",s);

	struct sockaddr_in web;
	web.sin_family = AF_INET;
	web.sin_port = htons(80);
	web.sin_addr = *(struct in_addr*)ip;
	bzero(&web.sin_zero,8);

	int fd=socket(AF_INET,SOCK_STREAM,0);
	connect(fd,(struct sockaddr*)&web,sizeof(web));
	send(fd,s,strlen(s),0);

	i=0;
	do{
		i=recv(fd,s,1000,0);
		if(i>0){ printf("receive : %d\n",i); print(s,i); printf("\n"); }
		else if(i==0){ printf("i==0 ; break\n"); break; }
		else if(i==-1){ printf("i==-1 ; break; \n"); break; }
		else break;
	}while(1);
}

int main(){
	webget("www.baidu.com/");
	return 0;
}
