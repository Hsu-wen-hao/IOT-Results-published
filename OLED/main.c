#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
#define UDP_TEST_PORT       50001

//---

/* serv.c */
// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

//---

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pthread.h>
#include<my_debug.h>

#include<bcm2835.h>
//#include<bme280.h>
#include "I2C_SSD1306Z.h"	

//#define LCD_I2C_SLA   0x3c

//---
 
int main(int argC, char* arg[])
{
    struct sockaddr_in addr;

    int sockfd, len = 0, newsockfd;   

    int addr_len = sizeof(struct sockaddr_in);

    char buffer[256];

    int a =0, data; 

    char input[256];

    char output_message[256];

    char bb[256]="";

    //---
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer1[1024] = {0};
    char mysql_device_name_buffer[1024] = {0};
    char *hello = "Hello from server";
    
    int count=0;

    //--- 

    struct bme280_t *bme;
	//int count = 300;

    bcm2835_init();
    i2c_start();

    //printf("init oled\n");
	
	Init_LCD();
	//clear_LCD();
    
    //---
//SYS_LOOP1:
//while(1)
//{
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    SYS_LOOP1:
    while(1)
    {
    printf("1\n");
    // valread = read( new_socket , buffer, 1024);
    valread = recv(new_socket, mysql_device_name_buffer, 1024, 0);
    //valread = recv(new_socket, mysql_device_name_buffer, 1024, MSG_DONTWAIT);
    printf("%s\n",mysql_device_name_buffer);
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

    valread = recv(new_socket, buffer1, 1024, 0);    
    printf("%s\n",buffer1 );    
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

    if(count==0)
    {
      count++;
      goto SYS_LOOP3;    
    }
    else
    {
        goto SYS_LOOP;
    }



    //---

    /* 建立socket，注意必须是SOCK_DGRAM */
SYS_LOOP3:
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

        perror ("socket");

        exit(1);

    }

 

    /* 填写sockaddr_in 结构 */

    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;

    addr.sin_port = htons(UDP_TEST_PORT);

    addr.sin_addr.s_addr = htonl(INADDR_ANY) ;// 接收任意IP发来的数据

 

    /* 绑定socket */

    if (newsockfd=bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0) {

        perror("connect");

        exit(1);

    }

 

    //while(1) {
SYS_LOOP:

        //---

        //bcm2835_init();
        //i2c_start();
        //Init_LCD();
	    //clear_LCD();

        //---

        bzero(buffer, sizeof(buffer));

        len = recvfrom(sockfd, buffer, sizeof(buffer), 0,

                       (struct sockaddr *)&addr ,&addr_len);

        /* 显示client端的网络地址和收到的字符串消息 */

        /*printf("Received a string from client %s, string is: %s\n",

                inet_ntoa(addr.sin_addr), buffer);*/
        
        printf("Received a string from client %s, %s\n",

                inet_ntoa(addr.sin_addr), buffer);

        /* 将收到的字符串消息返回给client端 */
        
        //---輸出訊息---
        //*output_message = 'a';
        //sendto(sockfd,output_message, len, 0, (struct sockaddr *)&addr, addr_len);

        //bzero(buffer, sizeof(buffer));
        //*buffer = 'c';

        //---輸入所要的輸出訊息

        printf("%s\n", mysql_device_name_buffer);
        printf("%s\n", buffer);
        //printf("123 --%d\n", mysql_device_name_buffer[9]);
        //printf("123 %s\n", &mysql_device_name_buffer);
        //printf("123 %s\n", &buffer);

        //print_Line(0, mysql_device_name_buffer);

        //if(*mysql_device_name_buffer==*buffer)
        if(strcmp(mysql_device_name_buffer, buffer)==0)
        //if(&mysql_device_name_buffer == &buffer)
        //if(mysql_device_name_buffer[9] == '2')
        {
            printf("2");
            //delay(1000);
            clear_LCD();
            print_Line(0, buffer);
            if(*buffer1=='a')
            {
                //---傳至 arduino (client)           
                *output_message = 'a';
                sendto(sockfd,output_message, len, 0, (struct sockaddr *)&addr, addr_len);
                //---接收 arduino (client) 回傳的值 
                bzero(bb, sizeof(bb));
                recvfrom(sockfd, &bb, sizeof(bb), 0,
                       (struct sockaddr *)&addr ,&addr_len);
                printf("%s\n", bb);

                //Init_LCD();
	            clear_LCD();

                print_Line(1, "on");
                //bcm2835_close();
            }
            else if(*buffer1=='b')
            {            
                *output_message = 'b';
                sendto(sockfd,output_message, len, 0, (struct sockaddr *)&addr, addr_len);
                bzero(bb, sizeof(bb));
                recvfrom(sockfd, &bb, sizeof(bb), 0,
                       (struct sockaddr *)&addr ,&addr_len);
                printf("%s\n", bb);

                //Init_LCD();
	            clear_LCD();

                print_Line(1, "off");
                //bcm2835_close();
            }
            //bcm2835_close();
        }
        /*else
        {
            printf("no match");
        }*/

        /*if(mysql_device_name_buffer[9] == '2')
        {
            printf("3");
            if(*buffer1=='a')
            {
                //---傳至 arduino (client)           
                *output_message = 'a';
                sendto(sockfd,output_message, len, 0, (struct sockaddr *)&addr, addr_len);
                //---接收 arduino (client) 回傳的值 
                bzero(bb, sizeof(bb));
                recvfrom(sockfd, &bb, sizeof(bb), 0,
                       (struct sockaddr *)&addr ,&addr_len);
                printf("%s\n", bb);
            }
            else if(*buffer1=='b')
            {            
                *output_message = 'b';
                sendto(sockfd,output_message, len, 0, (struct sockaddr *)&addr, addr_len);
                bzero(bb, sizeof(bb));
                recvfrom(sockfd, &bb, sizeof(bb), 0,
                       (struct sockaddr *)&addr ,&addr_len);
                printf("%s\n", bb);
            }
        }*/
        /*else
        {
            printf("no match");
        }*/

        //sleep(10);
        goto SYS_LOOP1;

        /*scanf("%s", input);       

        if(*input=='a')
        {
            //---傳至 arduino (client)           
            *output_message = 'a';
            sendto(sockfd,output_message, len, 0, (struct sockaddr *)&addr, addr_len);
            //---接收 arduino (client) 回傳的值 
            bzero(bb, sizeof(bb));
            recvfrom(sockfd, &bb, sizeof(bb), 0,

                       (struct sockaddr *)&addr ,&addr_len);
            printf("%s\n", bb);
        }
        else if(*input=='b')
        {            
            *output_message = 'b';
            sendto(sockfd,output_message, len, 0, (struct sockaddr *)&addr, addr_len);
            bzero(bb, sizeof(bb));
            recvfrom(sockfd, &bb, sizeof(bb), 0,

                       (struct sockaddr *)&addr ,&addr_len);
            printf("%s\n", bb);
        }
        else
        {
            sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
        }*/
        //---
        

        /*if(*input=='a')
        {
            bzero(buffer, sizeof(buffer));
            *buffer = 'a';
            sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
        }
        else if(*input=='b')
        {
            bzero(buffer, sizeof(buffer));
            *buffer = 'b';
            sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
        }
        else
        {
            sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
        }*/

        
        /*if(a1==0)
        {
            bzero(buffer, sizeof(buffer));
            *buffer = 'c';
            sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
            a1=1;            
        }

        if(a1==1)
        {
            bzero(buffer, sizeof(buffer));
            *buffer = 'b';
            sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
            a1=0;
        }*/

        //sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
        //bzero(buffer, sizeof(buffer));
        //*buffer = 'b';
        //sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
        //sendto(sockfd,buffer, len, 0, (struct sockaddr *)&addr, addr_len);
        //sendto(sockfd,a, len, 0, (struct sockaddr *)&addr, addr_len);
    }

 

    return 0;

}
