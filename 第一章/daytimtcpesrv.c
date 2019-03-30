#include"unp.h"
#include<time.h>

int main(int argc, char **argv)
{

    int listenfd, connfd;
    struct sockaddr_in servaddr;

    char buff[MAXLINE];

    time_t ticks;

    //定义套接字
    listenfd=Socket(AF_INET, SOCK_STREAM, 0);

    //初始化套接字
    bzero(&servaddr, sizeof(servaddr));


    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(13);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

    // 将套接字和本地IP地址绑定
    Bind(listenfd,(SA*)&servaddr, sizeof(servaddr));

    //将套接字转为监听套接字
    Listen(listenfd, LISTENQ);

    for( ; ; )
    {

        //接受客户端连接，生成已连接描述符
        connfd=Accept(listenfd, (SA*) NULL, NULL);

        ticks=time(NULL);

        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }

    
}