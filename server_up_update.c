//Om Ganapathy Appa Thunai....
//CREATING AN SERVER END USING API IN Lunix AND PERFORMING SOCKET PROGRAMMING
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<fcntl.h>
int main(){
	//Creating the socket(this tells the OS to create an socket obj and return it)
	int socket_sfd=socket(AF_INET,SOCK_STREAM,0);
	//Before binding the socket we need to tell where the socket resides as an interface
	struct sockaddr_in inter_addr;
	memset(&inter_addr, 0, sizeof(inter_addr));
	inter_addr.sin_family=AF_INET;
	inter_addr.sin_port=htons(4016);
	inter_addr.sin_addr.s_addr=inet_addr("172.20.156.231");
	//bindign the socket or assiging the socket
	int binder=bind(socket_sfd,(struct sockaddr *)&inter_addr,sizeof(struct sockaddr_in));
	if(binder == -1){
		perror("The socket binding failed...");
		return(0);
	}
	else{
		printf("Binding successfull....\n\n");
	}
	//Then listening to the port that whether do we get any request
	if(listen(socket_sfd,5)==0){
		printf("The Listening successfull...");
	}
	else{
		perror("The Listening failed...:");
	}
	//accepting the communication request
	//creating the data variable to transmit the data
	
	//creating the client end network address structure
        struct sockaddr_in client_sfd;
	int accept_sfd;
	socklen_t length=sizeof(struct sockaddr_in);

	while(true){

	 accept_sfd=accept(socket_sfd,(struct sockaddr *)&client_sfd,&length);
        if(accept_sfd >=0){
                printf("Communication request accepted...\n\n");
        }
        else{
                perror("Communication request Failed...:");
		return(0);
                break;
        }

    int pid = fork();
    if(pid==0){
		char pid[11];
		char accept_sfds[11];
		char cip[20];
		sprintf(pid,"%d",getppid());
		sprintf(accept_sfds,"%d",accept_sfd);
		inet_ntop(AF_INET,&client_sfd.sin_addr,cip,sizeof(cip));
		printf("Accept_sfd in string :%s\n\n",accept_sfds);
		printf("Pid in string :%s\n\n",pid);
		printf("Client IP:%s\n\n",cip);
		//handling the client by using the client handling program
		 fcntl(accept_sfd,F_SETFD,0);
		execlp("xterm","xterm","-hold","-e","./client_handlerf.out",accept_sfds,pid,cip,NULL);
	}
	else if(pid<0){
		perror("Fork failed....:");
	}	
	
	}
	
	close(socket_sfd);
}

