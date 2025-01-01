//This header handles all the declaration regard to https request, 



/*
required methods
(github?) initialization webpage, include step by step and link, Auth2.0 setup webpage link
Processing the startup json files, 
    - allow multiple type of input

when we recieve signal do something

*/
class webProcesses{
    public :
        void initializationParse(std::string jsonPath);
        int ngrokInit();
        bool isOnline();//to see if current host is connect to internet, may consider application termination?
        void sendPostRequest();

    private :
        void foo();//pending name change; does something when we recieve signal
        void ngrokCodeProcess(int code);//based on the code that was responded by ngrokInit() or updateNgrok(), post related system informations ?

}

//switching to a web hook based approach
/*
workflow : 
request api json (the keys and such)
initiate the ngrok with the specific opened ports
send the updated url to google



when a "signal" is sent to me
request authentication code to google
make query to the google(youtube) to see updates that has the same time as the "signal"
makes the related post
*/

