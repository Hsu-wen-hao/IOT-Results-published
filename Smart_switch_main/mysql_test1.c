#include </usr/include/mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

/* clnt.c */
// Client side C/C++ program to demonstrate Socket programming
//#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{
  int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    char buffer2[1024] = {0};
    int count=0;

  ///---
SYS_LOOP1:
  //while(1)
  for(;;)
  {
  //printf("1");
  printf("1\n");
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }
//SYS_LOOP1:
  if (mysql_real_connect(con, "localhost", "admin", "1234",
          "button_on_off", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  //---4.19---
  
//SYS_LOOP1:
  //while(1)
  //{

  //------

  /*if (mysql_query(con, "SELECT * FROM switch"))
  {
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;*/

  //printf("%s ", result);

  /*while ((row = mysql_fetch_row(result)))
  {
      //for(int i = 0; i < num_fields; i++)
      //{
          //printf("%s ", row[i] ? row[i] : "NULL");
          printf("%d ", num_fields);
          //printf("%s ", row[1]);
      //}

      printf("\n");
  }*/
    //row = mysql_fetch_row(result);
    //printf("%s ", row[1]); //裝置名稱
    //printf("%s ", row[2]);  on/off
    //SELECT *from getLastRecord ORDER BY id DESC LIMIT 1;
  /*for(int i = 0; i < num_fields; i++)
      {
          //printf("%s ", row[i] ? row[i] : "NULL");
          //printf("%d ", num_fields);
          printf("%s ", row[1]);
      }*/

  //---
  
  //int id = mysql_insert_id(con);

  //printf("The last inserted row id is: %d\n", id);

  /*if (mysql_query(con, "SELECT device_name FROM switch WHERE id=id"))
  {
      finish_with_error(con);
  }*/
  //if (mysql_query(con, "SELECT * FROM switch ORDER BY device_name DESC LIMIT 1;"))
  if (mysql_query(con, "SELECT * FROM switch ORDER BY id DESC LIMIT 1;"))
  {
      finish_with_error(con);
  }
  MYSQL_RES *result1 = mysql_store_result(con);
    //printf("%s\n", result);
    int num_fields = mysql_num_fields(result1);
    MYSQL_ROW row1;

    row1 = mysql_fetch_row(result1);
    printf("%s ", row1[2]); //裝置名稱

  //---
  printf("2\n");
  mysql_free_result(result1);
  mysql_close(con);
  //if(*row1[2]=='a'||'b')
  if(count==0)
  {
      count++;
      goto SYS_LOOP;    
  }
  else
  {
      goto SYS_LOOP2;
  }
  
  //}
  //exit(0);
  //goto SYS_LOOP;
  

  //exit(0);


  //----
SYS_LOOP:
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
SYS_LOOP2:
    //send(sock , hello , strlen(hello) , 0 );
    send(sock , row1[1] , strlen(row1[1]) , 0 );
    printf("Hello message sent1\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );

    send(sock , row1[2] , strlen(row1[2]) , 0 );    
    printf("Hello message sent2\n");    
    valread = recv(sock, buffer2, 1024, 0);    
    printf("%s\n",buffer2 );
    //sock.close();
    //close(sock);
    //sleep(5);
    break;
    //goto SYS_LOOP1;
    //printf("1");
    }
    //delay(5000);
    sleep(0.1); //2021/4/21
    goto SYS_LOOP1;
    return 0;
    //goto SYS_LOOP1;

    

}

/* serv.c */
// Server side C/C++ program to demonstrate Socket programming
/*#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
       
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
    // valread = read( new_socket , buffer, 1024);
    valread = recv(new_socket, buffer, 1024, 0);
    printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}*/
