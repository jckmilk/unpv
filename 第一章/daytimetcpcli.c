#include"unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE+1];
    struct sockaddr_in servaddr;
    //参数检测
    if(argc!=2)
        err_quit("usage: a.out <IPaddress>");
    
    //创建一个套接字
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");
    //填充地址为0
    bzero(&servaddr, sizeof(servaddr));
    

    //制定服务器的地址类型设置
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(13);
    //地址转换
    if(inet_pton(AF_INET, argv[1],&servaddr.sin_addr)<=0)
        err_quit("inet_pton error for %s", argv[1]);

    // 连接
    if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr))<0)
        err_sys("connect error");

    //读取数据
    while((n=read(sockfd, recvline, MAXLINE))>0)
    {
        recvline[n]=0;
        if(fputs(recvline,stdout)==EOF)
            err_sys("fputs error");
    }

    if(n<0)
        err_sys("read error");

    exit(0);

}


