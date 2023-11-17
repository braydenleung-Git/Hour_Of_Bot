#include "config_s.h"
#include "include.h"
const std::string    BOT_TOKEN    = token;
bool running_state;
int main() {
    dpp::cluster bot(BOT_TOKEN); 

    bot.on_log(dpp::utility::cout_logger());

    dpp::utility::uptime uptime;


    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong! Why did you typed this");
            std::cout<<"Executed Ping Command"<<endl;
        }
    });
    
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "stop") {
            bot.direct_message_create(403048067521183746,dpp::message("Robot has been turned off"),dpp::utility::log_error());
            std::cout<<"Attempted Contact Admin about Shutdown"<<endl;
            //std::cout<<"Robot has been turned off"<<endl;
            event.reply("Shutting Down. . .");
            running_state = false;
            std::cout<<"Executed Stop Command"<<endl;
        }
    });

    bot.on_slashcommand([&uptime](const dpp::slashcommand_t& event){
        if(event.command.get_command_name()== "uptime"){
            event.reply(uptime.to_string());
            std::cout<<"Executed Uptime Command"<<endl;
        }
    });

    bot.on_ready([&bot](const dpp::ready_t & event) {
        std:: cout <<"Hour Of Bot project has been turned on"<<endl;
        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand ping("ping","I wonder what this do?", bot.me.id);
            dpp::slashcommand stop ("stop", "turns the robot down", bot.me.id);
            dpp::slashcommand uptime_m("uptime", "calls the bot's uptime", bot.me.id);
            stop.set_dm_permission(true);
            stop.set_default_permissions(0);
            uptime_m.set_dm_permission(true);
            uptime_m.set_default_permissions(0);
            bot.global_command_create(ping);
            bot.global_command_create(stop);
            bot.global_command_create(uptime_m);

        }
    });
    
    running_state = true; 
    bot.start(dpp::st_return);
    /*this is used to hold the bot in the "online" state, setting 
    running_state to false would state the bot is false, therefore ending the program/returning the value 0
    */
    while(running_state){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    bot.~cluster();
    return 0;
}
/*
This is an attempt to redirect or mirror cout to a .log file, more research needed
*/
