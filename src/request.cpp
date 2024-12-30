#include "request.h"

class request{
    public : 
    
}



using json = nlohmann::json;

// OAuth 2.0 credentials
const std::string CLIENT_ID = "YOUR_CLIENT_ID";
const std::string CLIENT_SECRET = "YOUR_CLIENT_SECRET";
const std::string REDIRECT_URI = "http://localhost:8080";
const std::string AUTHORIZATION_ENDPOINT = "https://accounts.google.com/o/oauth2/auth";
const std::string TOKEN_ENDPOINT = "https://oauth2.googleapis.com/token";

// Step 1: Generate Authorization URL
std::string getAuthorizationUrl() {
    std::string scope = "https://www.googleapis.com/auth/youtube.readonly";
    return AUTHORIZATION_ENDPOINT + "?client_id=" + CLIENT_ID +
           "&redirect_uri=" + REDIRECT_URI +
           "&response_type=code&scope=" + scope +
           "&access_type=offline";
}

// Step 2: Start a simple local server to capture the authorization code
std::string getAuthorizationCode() {
    httplib::Server svr;
    std::string authorization_code;

    svr.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        auto query = req.get_param_value("code");
        authorization_code = query;

        res.set_content("<h1>Authorization Code Received</h1><p>You can close this tab.</p>", "text/html");
        svr.stop();
    });

    std::cout << "Open the following URL in your browser to authorize:\n"
              << getAuthorizationUrl() << std::endl;

    std::cout << "Waiting for authorization code..." << std::endl;
    svr.listen("localhost", 8080);

    return authorization_code;
}

// Step 3: Exchange Authorization Code for Access Token
json getAccessToken(const std::string &authorization_code) {
    httplib::SSLClient cli("oauth2.googleapis.com");
    httplib::Headers headers = {
        {"Content-Type", "application/x-www-form-urlencoded"}
    };

    std::string body = "client_id=" + CLIENT_ID +
                       "&client_secret=" + CLIENT_SECRET +
                       "&code=" + authorization_code +
                       "&grant_type=authorization_code" +
                       "&redirect_uri=" + REDIRECT_URI;

    auto res = cli.Post("/token", headers, body, "application/x-www-form-urlencoded");

    if (res && res->status == 200) {
        return json::parse(res->body);
    } else {
        std::cerr << "Failed to get access token: " << (res ? res->body : "No response") << std::endl;
        exit(1);
    }
}

int main() {
    try {
        // Step 1: Get Authorization Code
        std::string authorization_code = getAuthorizationCode();
        std::cout << "Authorization Code: " << authorization_code << std::endl;

        // Step 2: Exchange Authorization Code for Access Token
        json token_response = getAccessToken(authorization_code);

        // Step 3: Output Access Token
        std::cout << "Access Token: " << token_response["access_token"] << std::endl;
        if (token_response.contains("refresh_token")) {
            std::cout << "Refresh Token: " << token_response["refresh_token"] << std::endl;
        }
        std::cout << "Token Expires In: " << token_response["expires_in"] << " seconds" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}




#include <iostream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp> // Include the JSON library (https://github.com/nlohmann/json)
#include <thread>
#include <regex>
#include <cstdlib>

using json = nlohmann::json;

// OAuth 2.0 credentials
const std::string CLIENT_ID = "YOUR_CLIENT_ID";
const std::string CLIENT_SECRET = "YOUR_CLIENT_SECRET";
const std::string REDIRECT_URI = "http://localhost:8080";
const std::string AUTHORIZATION_ENDPOINT = "https://accounts.google.com/o/oauth2/auth";
const std::string TOKEN_ENDPOINT = "https://oauth2.googleapis.com/token";

// Step 1: Generate Authorization URL
std::string getAuthorizationUrl() {
    std::string scope = "https://www.googleapis.com/auth/youtube.readonly";
    return AUTHORIZATION_ENDPOINT + "?client_id=" + CLIENT_ID +
           "&redirect_uri=" + REDIRECT_URI +
           "&response_type=code&scope=" + scope +
           "&access_type=offline";
}

// Step 2: Start a simple local server to capture the authorization code
std::string getAuthorizationCode() {
    httplib::Server svr;
    std::string authorization_code;

    svr.Get("/", [&](const httplib::Request &req, httplib::Response &res) {
        auto query = req.get_param_value("code");
        authorization_code = query;

        res.set_content("<h1>Authorization Code Received</h1><p>You can close this tab.</p>", "text/html");
        svr.stop();
    });

    std::cout << "Open the following URL in your browser to authorize:\n"
              << getAuthorizationUrl() << std::endl;

    std::cout << "Waiting for authorization code..." << std::endl;
    svr.listen("localhost", 8080);

    return authorization_code;
}

// Step 3: Exchange Authorization Code for Access Token
json getAccessToken(const std::string &authorization_code) {
    httplib::SSLClient cli("oauth2.googleapis.com");
    httplib::Headers headers = {
        {"Content-Type", "application/x-www-form-urlencoded"}
    };

    std::string body = "client_id=" + CLIENT_ID +
                       "&client_secret=" + CLIENT_SECRET +
                       "&code=" + authorization_code +
                       "&grant_type=authorization_code" +
                       "&redirect_uri=" + REDIRECT_URI;

    auto res = cli.Post("/token", headers, body, "application/x-www-form-urlencoded");

    if (res && res->status == 200) {
        return json::parse(res->body);
    } else {
        std::cerr << "Failed to get access token: " << (res ? res->body : "No response") << std::endl;
        exit(1);
    }
}

int main() {
    try {
        // Step 1: Get Authorization Code
        std::string authorization_code = getAuthorizationCode();
        std::cout << "Authorization Code: " << authorization_code << std::endl;

        // Step 2: Exchange Authorization Code for Access Token
        json token_response = getAccessToken(authorization_code);

        // Step 3: Output Access Token
        std::cout << "Access Token: " << token_response["access_token"] << std::endl;
        if (token_response.contains("refresh_token")) {
            std::cout << "Refresh Token: " << token_response["refresh_token"] << std::endl;
        }
        std::cout << "Token Expires In: " << token_response["expires_in"] << " seconds" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
