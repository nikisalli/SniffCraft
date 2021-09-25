#pragma once

#include "sniffcraft/enums.hpp"
#include "sniffcraft/LogItem.hpp"

#include <protocolCraft/enums.hpp>
#include <protocolCraft/Message.hpp>

#include <thread>
#include <mutex>
#include <fstream>
#include <memory>
#include <queue>
#include <chrono>
#include <set>
#include <ctime>
#include <condition_variable>

class ReplayModLogger
{
public:
    ReplayModLogger(const std::string &conf_path);
    ~ReplayModLogger();
    void Log(const std::shared_ptr<ProtocolCraft::Message> msg, const ProtocolCraft::ConnectionState connection_state, const Origin origin);
    void SetServerName(const std::string& server_name_);

private:
    void LogConsume();
    void TryStart(const std::string& conf_path);
    void SaveReplayMetadataFile() const;
    void WrapMCPRFile() const;

private:
    std::chrono::time_point<std::chrono::system_clock> start_time;

    std::thread log_thread;
    std::mutex log_mutex;
    std::condition_variable log_condition;
    std::queue<LogItem> logging_queue;

    std::string session_prefix;
    std::ofstream replay_file;
    bool is_running;

    std::string server_name;
};
