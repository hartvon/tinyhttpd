#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    struct sockaddr_in address;

    //填充地址结构，指定服务器的 IP 和 端口
    address.sin_family = AF_INET;
    // inet_addr 可以参考 man inet_addr
    //可以用现代的inet_pton()替代inet_addr(), example 中有参考例子
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(atoi(argv[1])); 
    int len = sizeof(address);

    //申请一个流 socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //下面的语句可以输出连接的 IP 地址
    //但是inet_ntoa()是过时的方法，应该改用 inet_ntop(可参考 example)。但很多代码仍然遗留着inet_ntoa.
    // printf("%s\n", inet_ntoa( address.sin_addr));

    int result = connect(sockfd, (struct sockaddr*)&address, len);

    printf("connect success\n");

    if (result == -1) {
        perror("oops: client1");
        exit(1);
    }

    //往服务端写一个字节
    char ch = 'A';
    if (write(sockfd, &ch, 1) != -1) {
        printf("char to server = %c\n", ch);
    }

    //从服务端读一个字符
    if (read(sockfd, &ch, 1) != -1) {
        printf("char from server = %c\n", ch);
    }

    close(sockfd);

    return 0;
}
