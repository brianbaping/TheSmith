#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

class Logger {
public:
    static std::shared_ptr<spdlog::logger> getInstance() {
        static std::shared_ptr<spdlog::logger> instance = createInstance();
        return instance;
    }

    static void setLogLevel(spdlog::level::level_enum level) {
        getInstance()->set_level(level);
    }

    static void setPattern(const std::string& pattern) {
        getInstance()->set_pattern(pattern);
    }

private:
    Logger() = default; // Private constructor

    static std::shared_ptr<spdlog::logger> createInstance() {
        // Initialize console and file loggers
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/app_log.txt", true);
        std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

        auto logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::info); // Set default log level
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v"); // Set log format
        spdlog::register_logger(logger);

        return logger;
    }
};

#endif // LOGGER_H
