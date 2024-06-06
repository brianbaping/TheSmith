#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    // Enum for log levels
    enum LogLevel {
        NONE,
        LOG_ERROR,
        LOG_INFO
    };

    // Static method to get the single instance of Logger
    static Logger& getInstance();

    // Delete copy constructor and assignment operator to ensure singleton
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Method to set the log level
    void setLogLevel(LogLevel level);

    // Method to get the current log level
    LogLevel getLogLevel();

    // Method to log messages with a specific log level (default is INFO)
    void log(const std::string& message, LogLevel level = LOG_INFO);

    // Method to set log file
    void setLogFile(const std::string& filename);

    // Method to get log level by index
    Logger::LogLevel getLogLevelByIndex(int index);

private:
    // Private constructor
    Logger();

    ~Logger();

    std::ofstream logfile_;
    LogLevel logLevel_;
    std::mutex mutex_;
};

#endif // LOGGER_H
