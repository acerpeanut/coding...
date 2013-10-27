#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

/* 服务器要监听的本地端口 */
#define MYPORT 4000
/* 能够同时接受多少没有 accept 的连接 */
#define BACKLOG 10
main()
{
/* 在 sockfd 上进行监听,new_fd 接受新的连接 */
int sockfd, new_fd ;
/* 自己的地址信息 */
struct sockaddr_in my_addr;
/* 连接者的地址信息*/
struct sockaddr_in their_addr;
int sin_size;

if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
{
/* 输出错误提示并退出 */
perror("socket");
exit(1);
}
/* 主机字节顺序 */
my_addr.sin_family = AF_INET;
/* 网络字节顺序,短整型 */
my_addr.sin_port = htons(MYPORT);
/* 将运行程序机器的 IP 填充入 s_addr */
my_addr.sin_addr.s_addr = INADDR_ANY;
/* 将此结构的其余空间清零 */
bzero(&(my_addr.sin_zero), 8);
/* 这里是我们一直强调的错误检查!
! */ if (bind(sockfd, (struct sockaddr *)&my_addr,
sizeof(struct sockaddr)) == -1)
{
/* 如果调用 bind()失败,则给出错误提示,退出 */
perror("bind");
exit(1);
}
/* 这里是我们一直强调的错误检查!
! */
if (listen(sockfd, BACKLOG) == -1)
{
/* 如果调用 listen 失败,则给出错误提示,退出 */
perror("listen");
exit(1);
}
while(1)
{
/* 这里是主 accept()循环 */
sin_size = sizeof(struct sockaddr_in);
/* 这里是我们一直强调的错误检查!
! */


if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t*)&sin_size)) == -1)
{
/* 如果调用 accept()出现错误,则给出错误提示,进入下一个循环 */
perror("accept");
continue;
}
/* 服务器给出出现连接的信息 */
printf("server: got connection from %s\n"
, inet_ntoa(their_addr.sin_addr));
/* 这里将建立一个子进程来和刚刚建立的套接字进行通讯 */
if (!fork()){
/* 这里是子进程 */
/* 这里就是我们说的错误检查! */
    if (send(new_fd, "Hello, world!\n"
, 14, 0) == -1)
    {
/* 如果错误,则给出错误提示,然后关闭这个新连接,退出 */
        perror("send");
        close(new_fd);
        exit(0);
    }
/* 关闭 new_fd 代表的这个套接字连接 */
    char buf[100];
    if( recv(new_fd,buf,100,0) != -1){  printf("%s\n",buf);  }
close(new_fd);

}
}
/* 等待所有的子进程都退出 */
while(waitpid(-1,NULL,WNOHANG) > 0);
}
