//Om Ganapathy Appa Thunai....
//CLIENT SIDE APPLICATION TO INFUENCE THE OS TO COMMUNICATE
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
int main(){
	//creating the socket for the communication
	int socket_sfd=socket(AF_INET,SOCK_STREAM,0);
	if(socket_sfd >=0){
		printf("Socket creation successful.....\n\n");
	}
	else{
		perror("Socket creation failed.........:");
		printf("\n\n");
	}
	//here we wont bind the socket with the port and IP the OS automatically binds it
	//Befor the client connects to the server then client should know the server IP and the host right
	struct sockaddr_in server_port;
	memset(& server_port,0,sizeof(server_port));
	server_port.sin_family=AF_INET;
	server_port.sin_port=htons(4016);
	server_port.sin_addr.s_addr=inet_addr("172.20.156.231");
	//And here the client needs to connect to the server
	if(connect(socket_sfd,(struct sockaddr *) & server_port,sizeof(struct sockaddr_in)) == -1){
		perror("Connection to the server failed.... :");
		printf("\n\n");
	}
	//If connection to the server is working fine then we can send and revice the data
	char data_recived[500];
        char data_to_send[500];
        int live_status;
        int n_b=0;
	while(true){
	memset(data_recived,0,sizeof(data_recived));
        memset(data_to_send,0,sizeof(data_to_send));
	printf("You: ");
	scanf(" %[^\n]",data_to_send);
	send(socket_sfd,data_to_send,strlen(data_to_send),0);
	n_b=recv(socket_sfd,data_recived,sizeof(data_recived)-1,0);
	data_recived[n_b]='\0';
	printf("Instructor: %s",data_recived);
	printf("Live status :");
	scanf("%d",&live_status);
	if(live_status== 1){
		continue;
	}
	else{
		break;
	}
}
}
