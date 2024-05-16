#include "include/socket_utils.h"
//Threading allows my server to complete multiple actions at once
#include <thread>
//Vector lib allows access to dynamic arrays
#include <vector>

#define PORT 8080
#define BUFFER_SIZE 1024

void HandleCLient(int clientSocket)
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
        Echoing back the recieved data to the client.
        */ 

       close(clientSocket);
       // we close the socket that we created, this is important to release the associated system resources and properly clean up the connection!
       //close calls to close our socket assoicated with the client connection after the data has been sent back to the client or when an error occurs.
    }



}
