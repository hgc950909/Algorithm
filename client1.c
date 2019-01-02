//최홍규 2015005205
#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include <unistd.h>
#include<arpa/inet.h>

int main(int argc,char *argv[]){
    int fd,sd,len;
    char buf[1000]={0},newfile[100]={0},request[100]={0};
    struct sockaddr_in serv_addr;
     int file_size=0;
    //서버에서 받은 파일을 저장할 파일명을 입력한다.
	printf("NEW FILE NAME ====> ");
	scanf("%s",newfile);
    printf("\n");
    //입력받은 파일명으로 데이터를 저장할 파일을 생성한다.
    if((fd = open(newfile,O_WRONLY | O_CREAT | O_TRUNC,0644))<0){
        printf("FILE CREATE FAILED!\n\n");
        exit(-1);
    }
    //서버와 연결하기 위한 소켓을 생성하여 TCP를 사용한다.
    //IPv4주소를 사용하기로 했다.
    if((sd = socket(PF_INET, SOCK_STREAM, 0))==-1){
        printf("SOCKET CREATE FAILED!!\n\n");
        exit(-1);
    }
    //서버 주소 구조체를 설정해준다.
    //IPv4주소를 사용한다
    //IP주소는 입력받은 첫번째 인자, 포트주소는 두번째 인자이다.
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    //서버와 연결을 요청한다.
    if(connect(sd, (struct sockaddr *)&serv_addr,sizeof(serv_addr))){
        printf("CONNECT FAILED\n\n");
        exit(-1);
    }
    printf("CONNECT SUCCESS!\n\n");
    //서버에서 전송받을 파일명을 request에 저장한다.
	printf("\nREQUEST FILE NAME ====> ");
	scanf("%s",request);
    printf("\n");
    //전송받을 파일명을 서버에 보낸다.
    if(send(sd,request,1000,0)<0){
        printf("SEND FAILED\n");
    }
    printf("DATA SENDING FROM SERVER\n\n");
    //전송받은 데이터를 생성한 파일에 저장한다.
    while((len = recv(sd, buf, 1000,0)) != 0) {
        file_size+=len;
        write(fd, buf, len);
    }
    //전송받은 파일크기를 출력한다.
    printf("RECEIVE FILE SIZE ====> %d BYTES     [OK]\n\n",file_size);
    printf("SENDING ACK!\n\n");
    //데이터를 잘받았다는 메세지를 서버에 보낸다.
    len = send(sd, "THANK YOU!\n", 10,0);
    //잘받았다는 메세지의 크기를 출력한다.
    printf("ACK SIZE ====> %d BYTES      [OK]\n\n",len);
    printf("THANK YOU!\n\n");
    //파일을 닫는다.
    close(fd);
    //소켓을 닫는다.
    close(sd);
    printf("COMPLETED!\n\n");
    exit(1);
}

