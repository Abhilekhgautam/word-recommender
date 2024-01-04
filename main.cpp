#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;


int main(){
   // get the data
   std::ifstream f("/home/abhilekh/Downloads/result.json");
   std::ofstream o("./filtered.txt");
   auto data = json::parse(f);

   auto msg_array = data["messages"];
   // purify the data
   for(const auto& msg: msg_array){
     if(!msg["text"].is_string()) continue;
     std::string content = msg["text"].template get<std::string>();
     // trying to ensure that the word is at least 2 words
     // c++23 specific feature- contains.
     if(content.empty() || content.length() <= 4 || !content.contains(' ')) continue;
     o << content << '\n';
   }
}
