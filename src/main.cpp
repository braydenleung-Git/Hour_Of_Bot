/*#include "config_s.h"
#include "main.h"
const std::string BOT_TOKEN = token;
bool running_state;*/

/*
    Todo list:
        

*/
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "external/cpp-httplib/httplib.h"
#include "config_s.h"

int main() {
    // 1. Your OAuth 2.0 access token:
    std::string access_token = "YOUR_ACCESS_TOKEN";

    // 2. Create a client pointing to Google's API endpoint.
    //    Using port 443 for HTTPS.
    httplib::SSLClient cli("www.googleapis.com", 443);

    // 3. Set up the headers with Authorization: Bearer <token>
    httplib::Headers headers = {
        {"Authorization", "Bearer " + access_token},
        {"Accept", "application/json"}
    };

    // 4. Make a GET request to the YouTube Data API endpoint.
    //    This example requests the user's channel info (mine=true).
    auto res = cli.Get("/youtube/v3/channels?part=snippet&mine=true", headers);

    // 5. Check the response
    if (res) {
        if (res->status == 200) {
            std::cout << "Request succeeded!\n";
            std::cout << "Response body: " << res->body << "\n";
        } else {
            std::cerr << "Request failed. Status code: " << res->status << "\n";
            std::cerr << "Body: " << res->body << "\n";
        }
    } else {
        std::cerr << "Request error: " << httplib::to_string(res.error()) << "\n";
    }

    return 0;
}

/*
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
            event.reply(fmt::format("Uptime: {}",uptime.to_string()));
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
    bot.start(dpp::st_return);*/
    /*this is used to hold the bot in the "online" state, setting 
    running_state to false would state the bot is false, therefore ending the program/returning the value 0
    *//*
    while(running_state){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    bot.~cluster();
    return 0;
}*/
