#include "BotStuff.h"
#include <dpp/cluster.h>
#include <dpp/once.h>
#include <iostream>

using dpp::utility::cout_logger;

// Constructor
BotStuff::BotStuff(const char* token) {
    if (!token) {
        std::cerr << "You must set the TOKEN environment variable!" << std::endl;
        return;
    }
    setBot(std::make_unique<dpp::cluster>(token));
}

// Set the bot
void BotStuff::setBot(std::unique_ptr<dpp::cluster> bot_cluster) {
    if (!bot_cluster) {
        std::cerr << "You must set the BOT cluster!" << std::endl;
        return;
    }
    bot = std::move(bot_cluster);
}

// Get the bot
dpp::cluster& BotStuff::getBot() {
    if (!bot) {
        throw std::runtime_error("You must set the BOT cluster like a good boy :3");
    }
    return *bot;
}

// Setup commands
void BotStuff::SetupCommands(const std::vector<dpp::slashcommand>& commandList) {
    // Validate guildId

    // Ensure the bot is initialized
    try {
       bot->on_log([](const dpp::log_t& event) {
        std::cout << event.message << std::endl;
       });
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    using CommandHandler = std::function<void(const dpp::slashcommand_t&)>;

    std::unordered_map<std::string, CommandHandler> commandHandlers = {
        {"boom", [](const dpp::slashcommand_t& event) {
            event.reply("Kaboom!!!");
        }},
        {"greeting", [](const dpp::slashcommand_t& event) {
            event.reply("Greetings from Afar!");
        }},
        {"sandwich", [](const dpp::slashcommand_t& event) {
            event.reply("Here's your sandwich! 🥪");
        }}
    };
    // Register slash command event handler
    bot->on_slashcommand([this, commandHandlers](const dpp::slashcommand_t& event) {
        const auto it = commandHandlers.find((event.command.get_command_name()));
        std::cout << event.command.get_command_name() + " made functional now!" << std::endl;
        if (it != commandHandlers.end()) {
            it->second(event);
        } else {
            std::cerr << "Command " << event.command.get_command_name() << " not found!" << std::endl;
        }
    });

    // Register guild-specific command
    // TODO: add on_read
    bot->on_ready([this, commandList](const dpp::ready_t&) {
         if (dpp::run_once<struct register_bot_commands>()) {
             for (const auto& command : commandList) {
                 bot->global_command_create(command,  [command](const dpp::confirmation_callback_t& callback) {
                     if (callback.is_error()) {
                         std::cerr << "Failed to register command: " << callback.http_info.body << " (" << command.name << ")" << std::endl;
                     } else {
                         std::cout << "Command registered successfully! (" << command.name << ")" << std::endl;
                     }
                 });
             }
             std::cout << "There are " + std::to_string(commandList.size()) + " commands created." << std::endl;
         }
     });

    std::cout << "There are " + std::to_string(commandList.size()) + " commands created." << std::endl;
}

// Initialize the bot
int BotStuff::Init() {
    getBot().start(dpp::st_wait);
    return 0;
}
