#ifndef BOTSTUFF_H
#define BOTSTUFF_H

#include <dpp/cluster.h>
#include <dpp/appcommand.h>
#include <memory>
#include <vector>

class BotStuff {
private:
    std::unique_ptr<dpp::cluster> bot; // Removed static

    void setBot(std::unique_ptr<dpp::cluster> bot_cluster); // Removed static

public:
    BotStuff(const char* token);
    void SetupCommands(const std::vector<dpp::slashcommand> &commandList); // Changed to std::vector
    dpp::cluster& getBot(); // Removed static
    int Init();
};

#endif // BOTSTUFF_H