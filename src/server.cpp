#include "socket_utils.h"
//Threading allows my server to complete multiple actions at once
#include <thread>
//Vector lib allows access to dynamic arrays
#include <vector>

#define PORT 8080
#define BUFFER_SIZE 1024

void HandleClient(int clientSocket)
{
    char buffer[BUFFER_SIZE]; // an array with the size of our BUFFER_SIZE
    while (true) // A NEVER ENDING LOOP OF DOOM!
    {
        memset(buffer, 0, BUFFER_SIZE); //memset function fills our buffer with tons of 0's effectivly clearing our buffer
        //we see the amount of bytes we recieve on the client socket and store it in our buffer, If the bytes exceeds the buffer size, they are discarded
        int bytesReceived = recv(clientSocket, buffer , BUFFER_SIZE, 0);
        if (bytesReceived <= 0)
        {
            std::cerr << "Error in recv(). Quitting\n";
            break;
        }
        std::cout << "Received: " << buffer << '\n';
            //Socket , Buffer , Length , flags
        send(clientSocket, buffer, bytesReceived, 0);
        /*
        We send the data stored in the buffer array over to the clientSocket. 
        the data to be sent is taken from the buffer, and the number of bytes to be sent is determined by the 'bytesRecieved' var which contains the actual number of bytes
        from the client;
        the send function returns the number of bytes actually sent, which may be less than the specified length if not all the data could be sent in one go. 
        if any error occours it will return -1; 

        Basically this function sends the data received from the client back to the client itself, ( in this case an echo server ), 
        Echoing back the recieved data to the client.*/ 
       close(clientSocket);
       // we close the socket that we created, this is important to release the associated system resources and properly clean up the connection!
       //close calls to close our socket assoicated with the client connection after the data has been sent back to the client or when an error occurs.
    }
};

int main()
{
    //create a server socket
    int serverSocket = CreateSocket();
    if (serverSocket == -1) return -1;
    //bind the server socket to a port
    if(!BindSocket(serverSocket, PORT)) 
    {
        close(serverSocket);
        return -1;
    }

    //set the socket to listen mode
    if (!ListenSocket(serverSocket, 10)) 
    {
        close(serverSocket);
        return -1;
    }

    //Accept and handle incoming client connections
    std::vector<std::thread> threads; //creates a vector (dynamic array) called threads that holds instances of the std::thread class;
    /*By storing our thread instances in a vector we can manage multiple threads easily. eg; we can make a new thread for each client connection.
    We can later join the threads back together to save resources once the client has disconnected from the server.*/
    while (true) //THE LOOP OF DOOM ONCE AGAIN!
    {
        int clientSocket = AcceptClient(serverSocket);
        if(clientSocket != 1)
        {
            threads.push_back(std::thread(HandleClient,clientSocket)); 
            //this adds a new thread to our vector of threads I made earlier. the push_back fnc appends a new thread.
            //this basically creates a new thread that exectues our handleClient function, with clientsocket as a argument. this lets multplie connections at once.
        }
    }
    
    for (auto& th : threads)
    {
        if (th.joinable())
        th.join();
    }

    close(serverSocket);
    return 0;
};