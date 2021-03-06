#include <iostream>
#include <sys/types.h> // bind
#include <sys/socket.h> // bind
#include <stdio.h> // perror
#include <errno.h> // perror
using namespace std;


class server{
public:
struct sockaddr_in srv;
struct sockaddr_in clt;
int port;
int sockfd;
int trys;

server(){
port = 4000;
srv.sin_family = AF_INET;
srv.sin_port = htons(port);
srv.sin_addr.s_addr = htonl(INADDR_ANY);
memset(&(srv.sin_zero),0,8);
trys=10;
}

bool socket(){
cout<<"socketing ... "<<endl;
if(sockfd = ::socket(AF_INET,SOCK_STREAM,0) == -1){
perror("socket error");
exit(1);
}
}
bool bind(){
int i=0;
while(1){
cout<<"binding ... "<<endl;
if(::bind(sockfd,(struct sockaddr*)&srv,sizeof(struct sockaddr))==-1){
if(i++ < trys){
srv.sin_port = htons(++port);
continue;
}
else{
perror("bind error");
exit(1);
}
}
}
}
bool connect(){
	if(::connect(sockfd,(struct sockaddr*)&srv,sizeof(struct sockaddr))==-1){
		return false;
	}
	return true;
}
};
