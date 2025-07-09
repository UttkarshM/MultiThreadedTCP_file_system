// ######### INCLUDES ######### //
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

// ######### DEFINES ######### //
#define MAX_CLIENTS 200
#define BUFF_LEN 1024
#define END_MESSAGE_CHARACTER "$exit$"
#define DATA_PATH_SERVER "./data/server/data/"
#define DATA_PATH_CLIENT "./data/client/data/"

// ######### COLORED LOGGING SYSTEM ######### //
enum TextColor {
    TEXT_COLOR_BLACK,
    TEXT_COLOR_RED,
    TEXT_COLOR_GREEN,
    TEXT_COLOR_YELLOW,
    TEXT_COLOR_BLUE,
    TEXT_COLOR_MAGENTA,
    TEXT_COLOR_CYAN,
    TEXT_COLOR_WHITE,
    TEXT_COLOR_BRIGHT_BLACK,
    TEXT_COLOR_BRIGHT_RED,
    TEXT_COLOR_BRIGHT_GREEN,
    TEXT_COLOR_BRIGHT_YELLOW,
    TEXT_COLOR_BRIGHT_BLUE,
    TEXT_COLOR_BRIGHT_MAGENTA,
    TEXT_COLOR_BRIGHT_CYAN,
    TEXT_COLOR_BRIGHT_WHITE,
    TEXT_COLOR_COUNT
};

template <typename ...Args>
void _log(const char* prefix, const char* msg, TextColor textColor, Args... args) {
    static const char* TextColorTable[TEXT_COLOR_COUNT] = {
        "\x1b[30m", // TEXT_COLOR_BLACK
        "\x1b[31m", // TEXT_COLOR_RED
        "\x1b[32m", // TEXT_COLOR_GREEN
        "\x1b[33m", // TEXT_COLOR_YELLOW
        "\x1b[34m", // TEXT_COLOR_BLUE
        "\x1b[35m", // TEXT_COLOR_MAGENTA
        "\x1b[36m", // TEXT_COLOR_CYAN
        "\x1b[37m", // TEXT_COLOR_WHITE
        "\x1b[90m", // TEXT_COLOR_BRIGHT_BLACK
        "\x1b[91m", // TEXT_COLOR_BRIGHT_RED
        "\x1b[92m", // TEXT_COLOR_BRIGHT_GREEN
        "\x1b[93m", // TEXT_COLOR_BRIGHT_YELLOW
        "\x1b[94m", // TEXT_COLOR_BRIGHT_BLUE
        "\x1b[95m", // TEXT_COLOR_BRIGHT_MAGENTA
        "\x1b[96m", // TEXT_COLOR_BRIGHT_CYAN
        "\x1b[97m", // TEXT_COLOR_BRIGHT_WHITE
    };

    char formatBuffer[8192] = {};
    snprintf(formatBuffer, sizeof(formatBuffer), "%s %s %s \033[0m", 
             TextColorTable[textColor], prefix, msg);

    char textBuffer[8912] = {};
    snprintf(textBuffer, sizeof(textBuffer), formatBuffer, args...);

    puts(textBuffer);
}

// ######### LOGGING MACROS ######### //
#define LOG_INFO(msg, ...) _log("[INFO]", msg, TEXT_COLOR_BRIGHT_GREEN, ##__VA_ARGS__)
#define LOG_SUCCESS(msg, ...) _log("[SUCCESS]", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) _log("[WARNING]", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) _log("[ERROR]", msg, TEXT_COLOR_BRIGHT_RED, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) _log("[DEBUG]", msg, TEXT_COLOR_CYAN, ##__VA_ARGS__)
#define LOG_NETWORK(msg, ...) _log("[NETWORK]", msg, TEXT_COLOR_BLUE, ##__VA_ARGS__)
#define LOG_FILE(msg, ...) _log("[FILE]", msg, TEXT_COLOR_MAGENTA, ##__VA_ARGS__)
#define LOG_THREAD(msg, ...) _log("[THREAD]", msg, TEXT_COLOR_BRIGHT_CYAN, ##__VA_ARGS__)

// Legacy logger for backward compatibility
#define logger(x) LOG_ERROR(x)
