//####Includes####//
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #include <thread>
    #include <mutex>
    #include <condition_variable>
    #include <semaphore>
    #pragma comment(lib, "ws2_32.lib")
    
    // Windows compatibility defines
    #define close closesocket
    typedef int socklen_t;
    typedef int ssize_t;  // Define ssize_t for Windows
    
    // Thread compatibility
    #define pthread_t std::thread
    #define sem_t std::counting_semaphore<1024>
    
    // Avoid macro conflicts with read/write
    #ifdef read
    #undef read
    #endif
    #ifdef write
    #undef write
    #endif
    
    // Define socket read/write functions
    #ifndef WIN32_SOCKET_FUNCS_DEFINED
    #define WIN32_SOCKET_FUNCS_DEFINED
    inline ssize_t socket_read(int s, void* buf, size_t len) {
        return recv(s, (char*)buf, (int)len, 0);
    }
    
    inline ssize_t socket_write(int s, const void* buf, size_t len) {
        return send(s, (const char*)buf, (int)len, 0);
    }
    
    // Use macros to replace read/write calls
    #define read socket_read
    #define write socket_write
    #endif
    
#else
    #include <arpa/inet.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <netinet/in.h>
#endif

#include <stdio.h>
#include <iostream>

#ifdef _WIN32
    #include <filesystem>
    #include <direct.h>
#else
    #include <dirent.h>
#endif

//####defines####//
#define logger(x) \
	std::cout<<x<<"\n" 
	/* exit(1) */

#define MAX_CLIENTS 200
#define BUFF_LEN 1024
#define END_MESSAGE_CHARACTER "$exit$"

#ifdef _WIN32
    #define DATA_PATH_SERVER "C:\\Users\\uttka\\Desktop\\github-projects\\MultiThreadedTCP_file_system\\data\\server\\data\\"
    #define DATA_PATH_CLIENT "C:\\Users\\uttka\\Desktop\\github-projects\\MultiThreadedTCP_file_system\\data\\client\\data\\"
#else
    #define DATA_PATH_SERVER "/home/uttkarsh/Distributed_file_management_system/project/data/server/data/"
    #define DATA_PATH_CLIENT "/home/uttkarsh/Distributed_file_management_system/project/data/client/data/"
#endif
