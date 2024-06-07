//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Collection of various functions used in the Forge program. 
//

#include "Logger.h"

using namespace std;

/**
 * @brief get the single instance of the Logger
 */
Logger& Logger::getInstance() {
    static Logger instance; // Guaranteed to be destroyed and instantiated on first use
    return instance;
}

/**
 * @brief set the log level
 * @param level the log level
 */
void Logger::setLogLevel(LogLevel level) {
    lock_guard<mutex> lock(mutex_);
    logLevel_ = level;
    if (logLevel_ == NONE && logfile_.is_open()) {
        logfile_.close();
    }
}

/**
 * @brief get the current log level
 * @return the log level
 */
Logger::LogLevel Logger::getLogLevel() {
    lock_guard<mutex> lock(mutex_);
    return logLevel_;
}

/**
 * @brief log messages with a specific log level
 * @param message the message to log *DEFAULT is INFO
 * @param level the log level
 */
void Logger::log(const string& message, LogLevel level) {
    lock_guard<mutex> lock(mutex_);
    if (logLevel_ == NONE || level > logLevel_) {
        return;
    }
    if (logfile_.is_open()) {
        logfile_ << message << endl;
    }
}

/**
 * @brief set log file
 * @param filename the log file name
 */
void Logger::setLogFile(const string& filename) {
    lock_guard<mutex> lock(mutex_);
    if (logLevel_ == NONE) {
        return;
    }
    if (logfile_.is_open()) {
        logfile_.close();
    }
    logfile_.open(filename, ios::app);
    if (!logfile_) {
        throw runtime_error("Unable to open log file: " + filename);
    }
}

/**
 * @brief get log level by index
 * @param index the index of the log level
 * @return the log level
 */
Logger::LogLevel Logger::getLogLevelByIndex(int index) {
    switch(index) {
        case 0: return Logger::LogLevel::NONE;
        case 1: return Logger::LogLevel::LOG_ERROR;
        case 2: return Logger::LogLevel::LOG_DEBUG;
        case 3: return Logger::LogLevel::LOG_INFO;
        case 4: return Logger::LogLevel::LOG_TRACE;
        default: throw out_of_range("Invalid index for LogLevel");
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
