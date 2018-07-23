/*************************************************************************
	> File Name: udp_client.cpp
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月14日 星期三 19时39分21秒
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
    socklen_t len = sizeof(server_address);
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    if((inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) == 0))
    {
        printf("invalid server ip address\n");
        return 1;
    }
    serfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(serfd < 0)
    {
        perror("socket");
        return 1;
    }
    char buff[1024];
    while(1)
    {
        printf("udp_client:> ");
        s_gets(buff, 1024);
        sendto(serfd, buff, strlen(buff), 0,(struct sockaddr*)&server_address, len);
        if((recvfrom(serfd, buff, 1024, 0, (struct sockaddr*)&server_address, &len)) < 0)
        {
            break;
        }
        printf("server:> %s\n", buff);
    }
    close(serfd);
}
