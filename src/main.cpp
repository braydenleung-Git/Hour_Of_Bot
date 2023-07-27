#include "config_s.h"
#include <dpp/dpp.h>
const std::string    BOT_TOKEN    = token;

int main() {
    dpp::cluster bot(BOT_TOKEN);   

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong! connection Valid!");
        }
    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "stop") {
            bot.shutdown();
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("stop", "Turns off the bot", bot.me.id));
        }
    }); 
    

    bot.start(dpp::st_wait);
}