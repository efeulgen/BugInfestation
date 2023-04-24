
#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

std::string CurrentTimeToString()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y  %H:%M:%S", std::localtime(&now));
    return output;
}

void Logger::Log(const std::string &message)
{
    std::string out = "LOG: [" + CurrentTimeToString() + "]: " + message;
    std::cout << "\x1B[32m" << out << "\033[0m" << std::endl;
}

void Logger::Err(const std::string &message)
{
    std::string out = "ERR: [" + CurrentTimeToString() + "]: " + message;
    std::cout << "\x1B[91m" << out << "\033[0m" << std::endl;
}
