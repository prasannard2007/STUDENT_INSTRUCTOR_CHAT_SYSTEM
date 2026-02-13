//Creating an Client_handling program
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<errno.h>
#include<semaphore.h>

int main(int argc,char * argv[]){
		
	char data_recived[500];
	char data_to_send[500];
	int live_status;
	int n_b=0;
	//creating the socket to handle the client end communication
	//printf("The process id in string :%s and accept_sfd id in string :%s\n\n",argv[2],argv[1]);
	int accept_sfd=atoi(argv[1]);
	printf("\t\t\t CLIENT IP :%s\t\t\t\n\n",argv[3]);
	int pid=atoi(argv[2]);
	/*printf("The pid :%d and the process :%d\n\n",pid,accept_sfd);
	Accessing the SFD using the inetr process inspection
	char path[20];
	snprintf(path,sizeof(path),"/proc/%d/fd/%d",pid,accept_trans);
	int accept_sfd=open(path,O_RDWR);
	printf("The accept file discrptor value:%d",accept_sfd);
	if(accept_sfd>0){
		printf("The file discreptor imported success fully..\n\n");
	}
	else{
		perror("SFD Failed....:");
	}
	if(fcntl(accept_sfd,F_GETFD)==-1){
		perror("SFD CLOSED :");
	}
	else{
		printf("SFD STILL OPEN	\n\n");
	}*/
while(true){
	//child process to handle the client communication
    memset(data_recived,0,sizeof(data_recived));
	memset(data_to_send,0,sizeof(data_to_send));
	n_b=recv(accept_sfd,data_recived,sizeof(data_recived)-1,0);
	printf("number of bits recived :%d\n\n",n_b);
	data_recived[n_b]='\0';
	printf("Client: %s\n",data_recived);
	printf("Server: ");
	scanf(" %[^\n]",data_to_send);
	send(accept_sfd,data_to_send,strlen(data_to_send),0);
	printf("\nLive status :");
	scanf("%d",&live_status);
	printf("\n");
	if(live_status==1){
		continue;
	}
	else{
		send(accept_sfd,"SERVER_WNET_DOWN",strlen("SERVER_WENT_DOWN"),0);
		break;
	}
	}
         close(accept_sfd);
}

