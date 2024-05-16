#include "socket_utils.h"

int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

int CreateSocket()
{   
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        std::cerr << "Failed to create socket\n";
    }
    
    return sockfd;
}

bool BindSocket(int socket, int port)
{

    sockaddr_in serveraddr; //used to represent IPv4 Address and port
    serveraddr.sin_family = AF_INET; //setting the address family of the serveraddr structure to AF_INET | AF_INET specifies the IPv4 address family. 
    serveraddr.sin_port = htons(port); //this sets the port number | HTON's function converts the port number form host byte order to network byte order.
    serveraddr.sin_addr.s_addr = INADDR_ANY; //we set the IP address to any available IP address on the host machine 
    memset(serveraddr.sin_zero, '\0', sizeof(serveraddr.sin_zero)); //this intializes teh remaining bytes of the serveraddr strture; insures consistent size.

                    //Sockaddr is a strucure we create, and then point to my var serveraddr which holds all the corrosponding info reguarding my server. 
    if(bind(socket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1) 
    {
        std::cerr << "Bind Failed\n";
        return false;
    }

    return true;
}

bool ListenSocket(int socket, int backlog) //backlog referes to the max length of the queue of pending connections
{   //putting the socket in a passive state to allow other sockets to connect to ours
    if(listen(socket,backlog) == -1) 
    {
        std::cerr << "Listen Failed\n";
        return false;
    }

    return true;
}

int AcceptClient(int serverSocket)
{   //accepting & error handeling to others connecting to our socket;
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1)
    {
        std::cerr << "Accept Failed\n";

    }

    return clientSocket;
}

bool ConnectToServer(int socket, const std::string &ip, int port)
{
    sockaddr_in serverAddr; //creating a sockaddr_in structure with var name serveraddr again
    serverAddr.sin_family = AF_INET; // once again we set its family to IPv4 type;
    serverAddr.sin_port = htons(port); //setting port using the function htons again;

    /* the IP address provided as string type is converted to a sutiable for use with sockaddr_in using the inet_pton func 
       inet_pton converts the IP address from a string to a binary format and stores it in the sin_addr field of serveradd structure */
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr); 
    /*The remaining bytes of the serverAddr structure are initialized to zero using memset. This step is typically performed for compatibility reasons.*/
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
    /* The connect function is called to establish a connection to the server using the client socket, We pass over the strucutre of my serveraddr settings to the pointer;
       then just check to see what it returns if -1 there is an error otherwise we are good to go!*/
    if (connect(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Connection failed" << std::endl;
        return false;
    }
    return true;

}
