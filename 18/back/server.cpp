/*************************************************************************
	> File Name: 1.c
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2018年03月05日 星期一 20时51分37秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<pthread.h>

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE 512
#define UDP_BUFFER_SIZE 1024

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);    
}
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("usage: %s port\n", basename(argv[0]));
        return 1;
    }
    int port = atoi(argv[1]);
    int ret = 0;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET; //ipv4
    address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != 1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    /*创建UDP socket, 并将其捆绑到端口port上*/
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    int udpfd = socket(PF_INET, SOCK_DGRAM, 0);
    assert(udpfd >= 0);

    ret = bind(udpfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != 1);
    
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    /*注册TCP socket 和 UDP socket 上的可读事件*/
    addfd(epollfd, listenfd);
    addfd(epollfd, udpfd);
    
    while(1)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        //printf("number = %d\n", number);
        if(number < 0)
        {
            printf("epoll failure\n");
            break;
        }
        for(int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd)
            {
            	printf("connect arrived\n");
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
                if(connfd <= 0)
                {
                	perror("accept ");
                }
                addfd(epollfd, connfd);
            }
            else if(sockfd == udpfd)
            {
                char buf[UDP_BUFFER_SIZE];
                memset(buf, '\0', UDP_BUFFER_SIZE);
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                ret = recvfrom(udpfd, buf, UDP_BUFFER_SIZE - 1, 0,
                              (struct sockaddr*)&client_address, &client_addrlength);
                if(ret > 0)
                {
                    sendto(udpfd, buf, UDP_BUFFER_SIZE - 1, 0,
                          (struct sockaddr*)&client_address, client_addrlength);
                }
            }
            else if(events[i].events & EPOLLIN)
            {
                char buf[TCP_BUFFER_SIZE];
                while(1)
                {
                    memset(buf, '\0', TCP_BUFFER_SIZE);
                    ret = recv(sockfd, buf, TCP_BUFFER_SIZE - 1, 0);
                    if(ret < 0)
                    {
                        if((errno == EAGAIN) || (errno == EWOULDBLOCK))
                        {
                            break;  //EAGAIN
                            		//非阻塞模式下调用了阻塞操作，在该操作没有完成就返回这个错误
                            		//这个错误不会破坏socket的同步，不用管它，下次循环接着recv就可以
                        }
                        close(sockfd);
                        break;
                    }
                    else if(ret == 0)
                    {
                        close(sockfd);
                    }
                    else
                    {
                    	printf("buff = %s, len = %d\n", buf, strlen(buf));
                        send(sockfd, buf, ret, 0);
                    }
                }
            }
            else
            {
                printf("something else happend\n");
            }
        }
    }
    close(listenfd);
    return 0;
}
