#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

#define BUF_SIZE 10000
void print(char*s,int len){
	char a[BUF_SIZE];
	char *p=a;
	while(len-->0){
		*(p++)=*(s++);
	}
	*p=0;
	printf("%s",a);
}
void webget(char* url,char* output){
	int i=0,j;
	char w[100],g[100],s[BUF_SIZE];
	if(strncmp(url,"http://",7)==0){
		url+=7;
	}
	while(*url!='/' && *url){ w[i++]=*url; url++; }
	if(*url==0) *(--url)='/'; 

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

	FILE*fp;
	if(output){ 
		fp=fopen(output,"wb");
		if(!fp){ perror("open output file"); close(fd); return ; }
	}

	i=0;
	int k=1;
	char *t;
	do{
		i=recv(fd,s,BUF_SIZE,0);
		if(i>0){ 
			printf("receive : %d\n",i); 
			if(output){
				t=s;
				if(k){
					while((*(t++)!='\r')||(strncmp(t,"\n\r\n",3)!=0));
					t+=3,k=0;
					print(s,t-s);
					printf("\n");
				}
				while((j=fwrite(t,1,i,fp))<i){
					t+=j, i-=j;
				}
			}
			else{
			       	print(s,i); 
			}
			printf("\n"); 
		}
		else if(i==0){ printf("i==0 ; break\n"); break; }
		else if(i==-1){ printf("i==-1 ; break; \n"); break; }
		else break;
	}while(1);
	close(fd);
	if(output) fclose(fp);
}

int main(){
	char url[256];
	scanf("%s",url);
	webget(url,"a.txt");
	return 0;
}
