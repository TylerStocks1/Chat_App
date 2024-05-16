#include "socket_utils.h"


#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int clientSocket = CreateSocket(); //creating the socket and making sure its set up correctly!
    if (clientSocket == -1) return -1;

    if(!ConnectToServer(clientSocket, "127.0.0.1", PORT)) //establish a connection to the server with our IP & PORT NUM
    {
        close(clientSocket);
        return -1;
    }

    char buffer[BUFFER_SIZE]; //creating our array with our max buffer size of 1024;
    std::string userInput; //variable for our user input

    while(true) //THE NEVER ENDING LOOP OF DOOM!
    {
        std::cout << "Enter a message: "; //asking usr for input
        std::getline(std::cin, userInput); // we use getline since we are grabbing a whole bunch of text (string) rather than just a char
        if(userInput == "exit") break; // if user says exit, we exit out of the loop 
        send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
        /* we send data from the client to the server | usrInput.c_str() this gets a pointer to the underalying char array of the userinput string. 
           userinput.size() + 1 , This specifies the length of data to be sent, so we return the size of the userinput.size & then + 1 to include the null terminatior '\0'
           the null terminator is required for c style strings to indicate the end of strings. | 0 is the flags , 0 indicates no special flags.

           In recap because ill know i forget what any of this means, this line of code sends the contents of userInput string (with the null terminator) from the client socket
           to the server. The server will process it accordingly. 
        */
        memset(buffer, 0, BUFFER_SIZE); // this actively fills our buffer with 0's 
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0); //and checking what we recieve, if more than 0 we output otherwise there is an error
        if (bytesReceived > 0)
        {
            std::cout << "Server: " << buffer << "\n";
        }
    }

    close(clientSocket);
    return 0;
}