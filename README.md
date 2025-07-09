# MultiThreaded TCP File System

A robust, multithreaded TCP-based file transfer system built in C++ that enables seamless file sharing between server and client applications with colorful logging and real-time communication capabilities.

## 🚀 Features

- **Multithreaded Architecture**: Concurrent client handling using pthread
- **TCP File Transfer**: Reliable file sharing over TCP sockets
- **Colorful Logging System**: Enhanced debugging with color-coded log messages
- **Real-time Communication**: Chat functionality between server and client
- **Directory Browsing**: List and navigate server directories
- **File Management**: Upload, download, and manage files
- **Cross-platform Support**: Works on Linux and Unix-like systems
- **Image Support**: Built-in support for image files using STB libraries

## 📁 Project Structure

```
MultiThreadedTCP_file_system/
├── src/
│   ├── main.cpp          # Server application entry point
│   ├── client.cpp        # Client application entry point
│   └── CMakeLists.txt    # Source build configuration
├── libs/
│   ├── Server.h/.cpp     # Server class implementation
│   ├── Client.h/.cpp     # Client class implementation
│   ├── core.h            # Core definitions and logging system
│   └── CMakeLists.txt    # Library build configuration
├── external/
│   ├── stb_image.h       # STB image loading library
│   └── stb_image_write.h # STB image writing library
├── data/
│   ├── server/data/      # Server file storage
│   └── client/data/      # Client file storage
└── CMakeLists.txt        # Root build configuration
```

## 🛠️ Prerequisites

- **C++ Compiler**: GCC 7+ or Clang 6+
- **CMake**: Version 3.10 or higher
- **Libraries**: pthread, socket libraries
- **Operating System**: Linux, macOS, or WSL on Windows

## 🔧 Installation & Build

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/MultiThreadedTCP_file_system.git
cd MultiThreadedTCP_file_system
```

### 2. Create Build Directory
```bash
mkdir build && cd build
```

### 3. Configure with CMake
```bash
cmake ..
```

### 4. Build the Project
```bash
make
```

### 5. Run the Applications
```bash
# Terminal 1 - Start Server
./server

# Terminal 2 - Start Client
./client
```

## 🎯 Usage

### Server Application
The server application (`main.cpp`) provides:
- **TCP Socket Creation**: Establishes listening socket on port 14000
- **Client Connection Handling**: Accepts multiple concurrent clients
- **File Sharing**: Serves files from the `data/server/data/` directory
- **Directory Listing**: Shows available files to clients
- **Multithreaded Processing**: Handles multiple clients simultaneously

### Client Application
The client application (`client.cpp`) provides:
- **Server Connection**: Connects to server on port 14000
- **File Browsing**: Lists available files on server
- **File Download**: Downloads selected files to `data/client/data/`
- **Real-time Chat**: Communicate with server in real-time

## 📊 Logging System

The project features a comprehensive color-coded logging system:

```cpp
// Available log levels with colors
LOG_INFO(msg, ...)     // Bright Green - General information
LOG_SUCCESS(msg, ...)  // Green - Success messages
LOG_WARNING(msg, ...)  // Yellow - Warning messages
LOG_ERROR(msg, ...)    // Bright Red - Error messages
LOG_DEBUG(msg, ...)    // Cyan - Debug information
LOG_NETWORK(msg, ...)  // Blue - Network operations
LOG_FILE(msg, ...)     // Magenta - File operations
LOG_THREAD(msg, ...)   // Bright Cyan - Thread operations
```

## 🔌 Network Configuration

- **Default Port**: 14000
- **Protocol**: TCP
- **Address**: INADDR_ANY (0.0.0.0)
- **Maximum Clients**: 200 (configurable in `core.h`)
- **Buffer Size**: 1024 bytes

## 🎨 Key Components

### Core Features (`core.h`)
- Color-coded logging system
- Network constants and definitions
- Buffer size and client limits
- Cross-platform compatibility macros

### Server Class (`Server.h/.cpp`)
- Socket creation and management
- Client connection handling
- File serving capabilities
- Directory browsing
- Multithreaded client processing

### Client Class (`Client.h/.cpp`)
- Server connection establishment
- File download functionality
- Real-time server communication
- Local file management

## 🚦 Example Usage

### Starting the Server
```bash
./server
```
Output:
```
[NETWORK] Creating TCP socket...
[SUCCESS] TCP socket created successfully (fd: 3)
[NETWORK] Configuring socket for reuse...
[SUCCESS] Socket configured for reuse successfully
[NETWORK] Binding socket to port 14000...
[SUCCESS] Socket bound successfully to port 14000
[NETWORK] Starting to listen for connections (max clients: 200)...
[SUCCESS] Server listening for connections
```

### Connecting with Client
```bash
./client
```
Output:
```
[NETWORK] Creating TCP socket...
[SUCCESS] TCP socket created successfully (fd: 3)
[NETWORK] Connecting to server at port 14000...
[SUCCESS] Connection to server established successfully
[FILE] Retrieving file names from server...
[INFO] Available files on server:
[INFO]   - example.txt
[INFO]   - image.jpg
[SUCCESS] File list received from server
```

## 🔒 Security Considerations

- **Input Validation**: All user inputs are validated
- **Buffer Overflow Protection**: Safe string handling practices
- **Connection Limits**: Maximum client connections enforced
- **File Access Control**: Restricted to designated directories

## 🐛 Troubleshooting

### Common Issues

1. **Port Already in Use**
   ```bash
   # Check if port is in use
   netstat -tulnp | grep 14000
   # Kill process using the port
   sudo kill -9 <PID>
   ```

2. **Permission Denied**
   ```bash
   # Ensure proper permissions
   chmod +x server client
   ```

3. **Build Errors**
   ```bash
   # Clean build directory
   make clean
   # Rebuild
   make
   ```