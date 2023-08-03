#include "config_s.h"
#include "include.h"
const std::string    BOT_TOKEN    = token;
bool running_state;
int main() {
    dpp::cluster bot(BOT_TOKEN); 
    dpp::log_t writeLogToFile();
    bot.on_log(dpp::utility::cout_logger());
    //bot.on_log(writeLogToFile());

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
        running_state = false;
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
    running_state = true; 
    bot.start(dpp::st_return);
    /*this is used to hold the bot in the "online" state, setting 
    running_state to false would state the bot is false, therefore ending the program/returning the value 0
    */
    while(running_state){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
/*
This is an attempt to redirect or mirro cout to a .log file, more research needed
*/
dpp::log_t writeLogToFile(){
    time_t now = time(0);
    string now_string = ctime(&now);
    string path = "../logs/"+ now_string +".log";
    ofstream newfile(path);
    fstream file;
    file.open("cout.txt", ios::out);
    string line;

    // Backup streambuffers of  cout
    streambuf* stream_buffer_cout = cout.rdbuf();
    streambuf* stream_buffer_cin = cin.rdbuf();

    // Get the streambuffer of the file
    streambuf* stream_buffer_file = file.rdbuf();

    // Redirect cout to file
    cout.rdbuf(stream_buffer_file);

    /* Redirect cout back to screen removed from the code because dpp handlled it ?
    cout.rdbuf(stream_buffer_cout);
    */
    //file.close();
}