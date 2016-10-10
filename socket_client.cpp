/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<sstream>
#include<cmath>
#include<unistd.h>

std::string float_to_str(float number1,float number2){
    std::ostringstream buff;
    buff<<number1<<" "<<number2;
    return buff.str();
}
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("192.168.80.133");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    //keep communicating with server
    while(1)
    {
        //printf("Enter message : ");
        //scanf("%s" , message);
        float test_num1,test_num2;
        for(int i=1,a=21;i<=20 and a<<40;i++){
            test_num1=sqrt(i);
            test_num2=sqrt(a);
            strcpy(message,float_to_str(test_num1,test_num2).c_str());

            if( send(sock , message , strlen(message) , 0) < 0){
                puts("Send failed");
                return 1;
            }

            //Receive a reply from the server
            if( recv(sock , server_reply , 2000 , 0) < 0){
                puts("recv failed");
                break;
            }

            puts("Server reply :");
            puts(server_reply);
            a++;
            sleep(1);
        }
        //Send some data

    }

    close(sock);
    return 0;
}
