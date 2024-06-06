#include "Logger.h"

// Static method to get the single instance of Logger
Logger& Logger::getInstance() {
    static Logger instance; // Guaranteed to be destroyed and instantiated on first use
    return instance;
}

// Method to set the log level
void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    logLevel_ = level;
    if (logLevel_ == NONE && logfile_.is_open()) {
        logfile_.close();
    }
}

// Method to get the current log level
Logger::LogLevel Logger::getLogLevel() {
    std::lock_guard<std::mutex> lock(mutex_);
    return logLevel_;
}

// Method to log messages with a specific log level
void Logger::log(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logLevel_ == NONE || level > logLevel_) {
        return;
    }
    if (logfile_.is_open()) {
        logfile_ << message << std::endl;
    }
}

// Method to set log file
void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logLevel_ == NONE) {
        return;
    }
    if (logfile_.is_open()) {
        logfile_.close();
    }
    logfile_.open(filename, std::ios::app);
    if (!logfile_) {
        throw std::runtime_error("Unable to open log file: " + filename);
    }
}

Logger::LogLevel Logger::getLogLevelByIndex(int index) {
    switch(index) {
        case 0: return Logger::LogLevel::NONE;
        case 1: return Logger::LogLevel::LOG_ERROR;
        case 2: return Logger::LogLevel::LOG_INFO;
        default: throw std::out_of_range("Invalid index for LogLevel");
    }
}

// Private constructor
Logger::Logger() : logLevel_(NONE) {
    // Default to no log file if log level is NONE
}

// Destructor
Logger::~Logger() {
    if (logfile_.is_open()) {
        logfile_.close();
    }
}
