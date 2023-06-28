#include "main.h"

int main(int argc, char* argv[]){
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "hello from client";
    char buffer[1024] = {0};
    if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socked not open");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8090);

    if(inet_pton(AF_INET, "192.168.0.136", &serv_addr.sin_addr) <= 0){
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0){
        perror("Connect failure");
        exit(EXIT_FAILURE);
    }
    
    while(1){
        for(int i = 0; i < sizeof buffer; i++){
            buffer[i] = 0;
        }
        scanf("%s", buffer);
        if(!strcmp(buffer, "::quit")){
            shutdown(client_fd, SHUT_RDWR);
            break;
        }
        send(client_fd, buffer, strlen(buffer), 0);
        valread = read(client_fd, buffer, 1024);
        printf("%s\n", buffer);
    }
    close(client_fd);
    
    return 0;
}
