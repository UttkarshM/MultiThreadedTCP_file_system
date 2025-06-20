# MultiThreaded TCP File System

A multithreaded client-server file system implementation using TCP sockets that allows clients to browse, transfer, and manage files on a remote server. The system supports concurrent client connections through multithreading and provides features for file transfer, directory listing, and basic chat functionality.

## Features

- **Multithreaded Server**: Handles multiple client connections simultaneously using pthread
- **File Transfer**: Download files from server to client with automatic copying
- **Directory Browsing**: List files and directories available on the server
- **Image Support**: Built-in support for image file handling using STB libraries
- **Chat Functionality**: Basic communication between client and server
- **Cross-platform**: Designed to work on Unix-like systems (Linux/macOS)

## Architecture

### Server Components
- **TCP Socket Management**: Creates, binds, and listens on specified ports
- **Thread Pool**: Manages concurrent client connections using pthread
- **File Operations**: Handles file reading, directory listing, and file transfers
- **Image Processing**: Supports image loading and writing using STB libraries

### Client Components
- **TCP Connection**: Establishes connection to server
- **File Retrieval**: Downloads and saves files from server
- **Interactive Interface**: Provides user interface for file selection
- **Local File Management**: Manages downloaded files in client data directory

## Project Structure

```
MultiThreadedTCP_file_system/
├── src/
│   ├── main.cpp          # Server application entry point
│   ├── client.cpp        # Client application entry point
│   └── CMakeLists.txt    # Source build configuration
├── libs/
│   ├── Server.h/.cpp     # Server class implementation
│   ├── Client.h/.cpp     # Client class implementation
│   ├── core.h            # Common definitions and constants
│   └── CMakeLists.txt    # Library build configuration
├── external/
│   ├── stb_image.h       # Image loading library
│   └── stb_image_write.h # Image writing library
├── data/
│   ├── server/data/      # Server file storage directory
│   └── client/data/      # Client download directory
└── build/                # Build output directory
```

## Prerequisites

- **Operating System**: Linux/Unix-based system (currently configured for Linux paths)
- **Compiler**: GCC with C++11 support
- **Build System**: CMake 3.10 or higher
- **Libraries**: 
  - pthread (POSIX threads)
  - Standard C++ libraries

## Installation

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd MultiThreadedTCP_file_system
   ```

2. **Create build directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Build the project**:
   ```bash
   cmake ..
   make
   ```

## Usage

### Starting the Server

1. **Run the server**:
   ```bash
   ./src/server
   ```

2. **Server Configuration**:
   - Default port: 14000
   - Maximum clients: 200
   - Server data path: `/home/uttkarsh/Distributed_file_management_system/project/data/server/data/`

### Running the Client

1. **Run the client**:
   ```bash
   ./src/client
   ```

2. **Client Operations**:
   - Connects to server on localhost:14000
   - Lists available files on server
   - Prompts user to select a file for download
   - Downloads selected file to client data directory

### Configuration

Update the paths in `libs/core.h` to match your system:

```cpp
#define DATA_PATH_SERVER "/your/server/data/path/"
#define DATA_PATH_CLIENT "/your/client/data/path/"
```

## Key Features Explained

### Multithreading
- Server uses a thread pool to handle multiple clients
- Each client connection runs in a separate thread
- Thread synchronization using semaphores and mutexes

### File Transfer Protocol
- Server lists available files to client
- Client selects desired file
- Server reads file content and sends line by line
- Client receives and saves file with `_copy_` prefix
- Transfer completion marked with `$exit$` terminator

### Network Communication
- TCP socket-based communication
- Custom protocol for file listing and transfer
- Error handling for connection failures
- Support for socket reuse to avoid port conflicts

## API Reference

### Server Class Methods
- `create_tcp_socket()`: Initialize TCP socket
- `bind_tcp_socket()`: Bind socket to address and port
- `listen_tcp_socket()`: Start listening for connections
- `accept_tcp()`: Accept incoming client connections
- `show_directories_files()`: Send file list to client
- `get_file_content()`: Transfer file content to client

### Client Class Methods
- `create_tcp_socket()`: Create client socket
- `connect_tcp_socket()`: Connect to server
- `get_file_names()`: Retrieve and display server file list
- `get_file_content()`: Download and save file from server

## Troubleshooting

### Common Issues

1. **Port already in use**:
   - Change the port number in both client and server
   - Or wait for the port to be released

2. **Permission denied**:
   - Ensure data directories exist and have proper permissions
   - Update paths in `core.h` to accessible locations

3. **Connection refused**:
   - Verify server is running before starting client
   - Check firewall settings

4. **File not found**:
   - Ensure server data directory contains files
   - Verify paths are correctly configured

## Development

### Adding New Features

1. **New File Operations**: Extend Server/Client classes with additional methods
2. **Protocol Extensions**: Modify the communication protocol in both client and server
3. **Enhanced Security**: Add authentication and encryption features
4. **GUI Interface**: Create graphical user interface for easier interaction

### Code Style
- Follow existing naming conventions
- Use proper error handling with logger macro
- Maintain thread safety in multithreaded sections
- Comment complex algorithms and protocol implementations

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is open source. Please check the repository for specific license information.

## Future Enhancements

- [ ] Windows compatibility
- [ ] Encrypted file transfers
- [ ] User authentication
- [ ] File upload functionality
- [ ] GUI client interface
- [ ] Configuration file support
- [ ] Logging system
- [ ] Unit tests

## Contact

For questions or support, please open an issue in the repository.

