# Simple Chatting Application in C++

This project is a simple chatting application implemented in C++. It uses web sockets and a server-client architecture to facilitate communication between multiple clients.

## Features

- **Server-Client Architecture**: The application follows a server-client model, where clients connect to a central server to exchange messages.
- **Web Sockets**: Web sockets are used for real-time communication between clients and the server, providing a fast and efficient way to exchange data.
- **Multi-Threading**: Threads are used to handle incoming client connections and messages concurrently, allowing the server to handle multiple clients simultaneously.
- **Vector-based Client Management**: The server uses a vector to manage client connections dynamically, allowing for easy scalability and efficient resource management.
- **Echo Server Functionality**: The server echoes back messages received from clients, demonstrating basic communication functionality.

## Getting Started

To run the application, follow these steps:

1. Clone the repository to your local machine.
2. Compile the server and client source files using a C++ compiler.
3. Start the server by running the compiled executable.
4. Start one or more client instances and connect them to the server.
5. Start chatting!

## Usage

- Run the server executable to start the server.
- Run the client executable and specify the server's IP address and port to connect to the server.
- Start typing messages to chat with other connected clients.

## Contributing

Contributions are welcome! If you'd like to contribute to this project, please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the [MIT License](LICENSE).
