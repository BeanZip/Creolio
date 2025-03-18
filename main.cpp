#include "BotStuff.h"
#include <dpp/dpp.h>
#include <iostream>
#include <cstdlib> // For std::getenv

[[noreturn]] int main() {
    // Get the bot token from the environment variable
    const char* token = std::getenv("TOKEN");
    if (!token) {
        std::cerr << "Error: TOKEN environment variable is not set!" << std::endl;
        return 1; // Exit with an error code
    }

    // Get the guild ID from the environment variable
    const char* guildIdEnv = std::getenv("testing_id");
    dpp::snowflake guildId = 0; // Default value
    if (guildIdEnv) {
        try {
            guildId = std::stoull(guildIdEnv); // Convert string to uint64_t
        } catch (const std::exception& e) {
            std::cerr << "Error: GUILD_ID is not a valid number!" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Error: GUILD_ID environment variable is not set!" << std::endl;
        return 1;
    }

    // Create a bot instance
    BotStuff bot(token);

    // Define slash commands
    std::vector commands = {
        dpp::slashcommand("Boom", "Make an explosion!", bot.getBot().me.id),
        dpp::slashcommand("Greeting", "Simple greeting from the bot", bot.getBot().me.id),
        dpp::slashcommand("Sandwich","Makes you a random sandwich",bot.getBot().me.id)
    };

    // Setup commands for a specific guild
    bot.SetupCommands(commands);

    // Initialize and start the bot
    bot.Init();

    // Keep the program running
    std::cout << "Bot is running. Press Ctrl+C to exit." << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}