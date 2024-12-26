#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define REMOTE_SERVER_PORT    8888
#define LENGTH_OF_LISTEN_QUEUE     20  // 监听序列长度
#define BUFFER_SIZE                1024

typedef struct  // 定义log结构体用于存放传输过来的日志（暂定，可以修改）
{
    time_t log_time;  // 日志时间
    int task_ID;  // 日志任务ID
    int op;  // 日志内容

}Log;

int main(int argc, char **agrv){
    struct sockaddr_in server_addr;  // server_addr用于存储服务器地址信息
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;  // IPv4
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);  // 绑定所有可用的网络接口
    server_addr.sin_port = htons(REMOTE_SERVER_PORT)  // 绑定端口

    // 创建TCP套接字
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket < 0)
    {
        printf("create socket failed!\n");
        exit(1);
    }

    // 绑定套接字
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))){
        printf("server bind port:%d failed!\n", REMOTE_SERVER_PORT);
        exit(1);
    }

    // 监听连接
    if(listen(server_socket, LENGTH_OF_LISTEN_QUEUE)){
        printf("Server Listen Failed!\n");
        exit(1);
    }

    // 接受客户端连接
    while(1){
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);

        // accept()函数接受客户端连接，返还新套接字new_server_socket用于与客户端进行通信
        //client_addr保存客户端地址信息
        int new_server_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
        if(new_server_socket < 0){
            printf("Server accept failed!\n");
            break;
        }
    
    // 接收客户端数据
    Log *myLog = (Log*)malloc(sizeof(Log))  // 为Log结构体分配内存，myLog为接收数据的结构体

    int recvLog = sizeof(Log);
    char *buffer = (char*)malloc(recvlog);  // 为buffer分配内存，暂时存贮接收到的数据
    int pos = 0;
    int len;
    while(pos < recvLog){  // 用recv()接收数据，直到接收数据长度等于recvLog
        len = recv(new_server_socket, buffer + pos, BUFFER_SIZE, 0);  // 
        if(len<0){
            printf("server receive data failed!\n");
            break;
        }
        pos += len;
    }

    // 关闭客户端套接字
    close(new_server_socket);
    memccpy(myLog,buffer,recvLog); // 使用 memcpy() 将接收到的数据从 buffer 拷贝到myLog 结构体中
    printf("recv over log_time=%s task ID=%d op=%d\n", myLog->log_time,myNode->task_ID,mylog->op);
    free(buffer);
    free(myLog);
        
    }
close(server_socket);

return 0;
    
}