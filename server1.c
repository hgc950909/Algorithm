//최홍규 2015005205
#include <stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include <unistd.h>


int main(int argc,char *argv[]) {
    int server_sd,clnt_sd,clnt_addr_size,fd,len,file_size=0;
    char buf[1000]={0},request[100]={0},ack[100]={0};
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    //소켓을 생성하여 TCP를 사용한다.
    //IPv4주소를 사용하기로 했다.
    if((server_sd = socket(PF_INET,SOCK_STREAM,0))== -1){
        printf("SOCKET CREATE FAILED!\n\n");
        exit(-1);
    }
    //서버 주소 구조체를 설정해준다.
    //IPv4주소를 사용하고 포트주소는 첫번째 인자로 받는다.
    //IP주소는 자동으로 찾아 저장한다.
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    //생성한 소켓을 서버 주소 구조체를 이용해 IP주소/포트 번호와 연결한다.
    if(bind(server_sd, (struct sockaddr *)&serv_addr,sizeof(serv_addr))){
        printf("BIND FAILED!\n\n");
        exit(-1);
    }
    //클라이언트의 연결요청을 받을 수 있는 상태로 만들어준다.
    if(listen(server_sd, 5)){
        printf("LISTEN FAILED!");
        exit(-1);
    }
    clnt_addr_size = sizeof(clnt_addr);
    //클라이언트의 요청이 올때까지 기다린다.
    //클라이언트의 접속요청이 도착하면 접속한 클라이언트와 통신할 수 있도록 새로운 소켓을 생성한다.
    if((clnt_sd = accept(server_sd,(struct sockaddr *)&clnt_addr,(socklen_t*)&clnt_addr_size))==-1){
        printf("\nCONNECT FAILED!\n\n");
        exit(-1);
    }
    printf("CONNECT SUCCESS!\n\n");
    //클라이언트가 서버에게 받고 싶은 파일명을 request에 저장한다.
    if( read(clnt_sd ,request, 1000) < 0){
        printf("RECEIVE FAILED!\n\n");
         exit(-1);
    }
    printf("REQUEST FILE = %s\n\n",request);
    //서버에 찾는 파일이 있다면 open한다.
    if((fd = open(request,O_RDONLY))<0){
        printf("NO FILE\n");
        exit(-1);
    }
    printf("DATA SENDING TO CLIENT     \n\n");
    //open한 파일의 데이터를 버퍼에 읽어들인다.
    //버퍼 크기보다 클 수 있으므로  반복문을 통해 끝까지 읽어들인다.
    while((len = read(fd,buf,1000))!=0){
        //버퍼에 들어온 데이터를 send함수를 통해 클라이언트에게 전송한다.
        if(send(clnt_sd,buf,len,0) < 0){
            printf("SEND FAILED!\n");
            exit(-1);
        }
        file_size+=len;
    }
    //보내는 파일의 크기를 출력한다.
    printf("SEND FILE SIZE ====> %d BYTES      [OK]\n\n",file_size);
    //파일 전송을 마치고 출력스트림을 닫는다.
    if (shutdown(clnt_sd, SHUT_WR) == -1) {
        printf("SHOUTDOWN FAILED!\n\n");
    }
    file_size =0;
    printf("WAIT FOR ACK\n\n");
    //클라이언트로부터 잘 받았다는 확인 메세지를 받는다.
    if((len=recv(clnt_sd ,ack, 1000,0)) < 0){
        printf("RECEIVED FAILED!\n");
    }
    //확인 메세지의 파일크기를 출력한다.
    printf("ACK FILE SIZE ====> %d BYTES     [OK]\n\n",len);
    //확인메세지를 출력한다.
    write(1, ack, len);
    //open한 파일을 닫아준다.
    close(fd);
    //클라이언트와 연결한 소켓을 닫아준다.
    close(clnt_sd);
    printf("\n\nCOMPLETED!\n\n");
    exit(1);
}

