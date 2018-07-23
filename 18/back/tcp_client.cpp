/*************************************************************************
	> File Name: client.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月06日 星期二 16时28分05秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

char* s_gets(char* st,int n)
{
	char* ret_val;
	int i=0;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		while(st[i]!='\n'&&st[i]!='\0')
			i++;
		if(st[i]=='\n')
			st[i]='\0';
		else
			while(getchar()!='\n')
				continue;
	}
	return ret_val;
}

int main()
{
    int serfd;
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    if(inet_pton(AF_INET, "127.0.0.1",&server_address.sin_addr)==0)
	{
		printf("invalid server ip address\n");
		return 1;
	}
    serfd = socket(AF_INET, SOCK_STREAM, 0);
    if(serfd < 0)
    {
        perror("socket:");
    	return 1;
    }
   	if((connect(serfd, (struct sockaddr*)&server_address, sizeof(server_address))) < 0)
    {
        perror("connect");
        return 1;
    }
    char buff[1024];
    while(1)
    {
        printf("client:> ");
        s_gets(buff, 1024);
        //puts(buff);
        write(serfd, (void*)buff, strlen(buff));
        if((read(serfd, (void*)buff, sizeof(buff))) <= 0)
        {
        	break;
        }
        printf("server:> %s\n",buff);
    }
    close(serfd);
}
