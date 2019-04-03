#include"unp.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv)
{

struct sockaddr_in serv;
serv.sin_family=AF_INET;
serv.sin_port=htons(13);
if(inet_pton(AF_INET, argv[1],&serv.sin_addr)<=0)
        err_quit("inet_pton error for %s", argv[1]);

cout<<serv.sin_family<<endl;
cout<<serv.sin_port<<endl;
cout<<serv.sin_addr.s_addr<<endl;

struct sockaddr  *serv1=(SA*)&serv;

cout<<serv1->sa_data<<endl;
cout<<serv1->sa_family<<endl;




return 0;

}