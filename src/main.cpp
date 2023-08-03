#include "config_s.h"
#include <dpp/dpp.h>
const std::string    BOT_TOKEN    = token;
int main() {
    dpp::cluster bot(BOT_TOKEN); 

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong! Why did you typed this");
        }
    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "stop") {
            event.reply("Turning off Bot now");
        }
        std::cout<<"robot has been turned off"<<endl;
        return 0;
    });

    bot.on_ready([&bot](const dpp::ready_t & event) {
        std:: cout <<" Hour Of Bot project has been turned on"<<endl;
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand ping("ping","I wonder what this do?", bot.me.id);
            dpp::slashcommand stop ("stop", "turns the robot down", bot.me.id);
            stop.set_dm_permission(true);
            stop.set_default_permissions(0);
            bot.global_command_create(ping);
            bot.global_command_create(stop);

        }
    });
    bot.start(dpp::st_wait);

}
