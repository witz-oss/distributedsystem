#ifndef DISTRIBUTEDSYSTEM_HTTP_H
#define DISTRIBUTEDSYSTEM_HTTP_H

#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

class Http {
private:
    std::vector<std::string> splitVecLine;
    const std::string delimiter1 = "\r\n";
    const std::string delimiter2 = " ";
    const std::string baseURL = "localhost:9090";
public:
    Http()= default;
    Http(std::string http){
        splitVector(http);
    };

    std::string getRequest(){
        return splitLine(splitVecLine.at(0)).at(0);
    }
    const std::string getIdRequest(){
        return splitLine(splitVecLine.at(0)).at(1);
    }
    std::string createPOST(std::string id, std::string& msg){
        std::string requestString = "POST ";
        requestString += id;
        requestString += " HTTP/1.1\r\n";
        requestString += ("Host: " + baseURL + "\r\n");
        requestString += ("Accept: text/html\r\n");
        requestString += ("Content-type:application/x-www-form-urlencoded\r\n");
        requestString += ("Content-Length: " + std::to_string(msg.length()));
        requestString += "\r\n\r\n";

        requestString += msg;

        return requestString;
    }
    std::vector<std::string> msgPOST(){
        std::vector<std::string> split;

        split.push_back(getIdRequest());

        std::string postMSG = splitVecLine.at(6);
        postMSG = std::regex_replace(postMSG, std::regex("≥"), "<tr>");
        postMSG = std::regex_replace(postMSG, std::regex("≤"), "</tr>");
        postMSG = std::regex_replace(postMSG, std::regex(" "), "<td>");
        postMSG = std::regex_replace(postMSG, std::regex("\t"), "</td>");

        split.push_back(postMSG);

        return split;
    }
    std::string creatOK(std::string& msg){
        std::string str = "<table border=\"1\"><tbody><tr>" + msg + "</tr></tbody></table>";
        std::string requestString = "HTTP/1.1 200 OK\r\n";
        requestString += ("Content-type: text/html\r\n");
        requestString += ("Content-Length: " + std::to_string(str.length()));
        requestString += "\r\n\r\n";

        requestString += str;

        return requestString;
    }
    const std::string Creat404(){
        std::string msg = "HTTP1/1 404 NOT FOUND\r\n\r\n";
        return msg;
    };

    void splitVector(std::string& str) {
        size_t pos_start = 0, pos_end, delim_len = delimiter1.length();
        std::string token;

        while ((pos_end = str.find(delimiter1, pos_start)) != std::string::npos) {
            token = str.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            splitVecLine.push_back (token);
        }
        splitVecLine.push_back(str.substr (pos_start));
    }
    std::vector<std::string> splitLine(std::string& str) {
        std::vector<std::string> splitVecWord;
        size_t pos_start = 0, pos_end, delim_len = delimiter2.length();
        std::string token;

        while ((pos_end = str.find(delimiter2, pos_start)) != std::string::npos) {
            token = str.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            splitVecWord.push_back (token);
        }
        splitVecWord.push_back(str.substr (pos_start));

        return splitVecWord;
    }

};


#endif //DISTRIBUTEDSYSTEM_HTTP_H
