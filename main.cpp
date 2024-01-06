#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <boost/algorithm/string.hpp>

//#include "json.hpp"


//using json = nlohmann::json;

static const std::vector<char> Symbols
                                    {'#', '.', ',',  ';', '&', '{',
                                    '}', ']', '[', '(', ')', '\t',
                                    '<', '>', '+', '-',  '=', '"', ':', '/','|','='
                                    , '@', '!', '$', '%', '^', '*', '_', '~', '?'
                                    };

static bool IsSymbol(const char& ch){
    for(const auto& s: Symbols){
        if (ch == s) return true;
    }
    return false;
}

std::unordered_map<std::string, long> Index;
std::vector<std::unordered_map<std::string, long>> LookUp;

std::vector<std::string> Recommendword(const std::string& InputWord){
    std::vector<std::string> Recommend;
    auto Found = Index.find(InputWord);
    if(Found == Index.end()) return Recommend;
    else{
        auto LookUpIndex = Index[InputWord];
	int TotalOccurence{};
        for(const auto& [word, count]: LookUp[LookUpIndex]){
          TotalOccurence += count;  
        }
	for(const auto& [word, count]: LookUp[LookUpIndex]){
       	  float Probability = (float)count / (float)TotalOccurence;
	  if(Probability > 0.60f){
	     Recommend.emplace_back(word);	  
	  }
	}
        return Recommend;
    }
}

int main(){
   // get the data purify it and store it back to some file 
   /*
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
   */ 

   // read the data, store the count and do more stuffs

   std::ifstream FilteredData("/home/abhilekh/CPP/naive-bayes-algorithm/filtered.txt");
   std::string Content;

   std::unordered_map<std::string, int> WordCounter;
   char Temp;
   // read the lines into a vector
   while(FilteredData.good()) {
       FilteredData.get(Temp);
       if (!IsSymbol(Temp) && Temp != '\n'){
           Content += Temp;
       } else if(Temp == '\n'){
           boost::algorithm::trim(Content);
           Content += '\n';
       }
   }


   std::vector<std::string> SplitByNewLine;
   boost::split(SplitByNewLine, Content, boost::is_any_of("\n"));

   for(const auto& elt: SplitByNewLine){
       std::vector<std::string> SplitBySpace;
       boost::split(SplitBySpace, elt, boost::is_any_of(" "));

       for(auto It = SplitBySpace.begin(), End = SplitBySpace.end() ; It != End ; ++It){
           auto Found = Index.find(*It);
           if(Found != Index.end()){
               long index = Index[*It];
               if(It + 1 != End){
                   auto Found = LookUp[index].find(*(It + 1));
                   if(Found != LookUp[index].end()){
                       LookUp[index][*(It + 1)] += 1;
                   } else {
                       LookUp[index][*(It + 1)] = 1;
                   }
               }
           } else{
               std::unordered_map<std::string, long> Temp;
               long NewIndex = LookUp.size();
               Index[*It] = NewIndex;
               LookUp.emplace_back(Temp);
           }
       }
   }

//   for(const auto& [word, address]: Index){
//       std::cout << word << ":\n";
//       for(const auto& [mword, count]: LookUp[address]){
//           std::cout << mword << ":" << count << '\n';
//       }
//       std::cout << "==========================\n";
//   }

   auto Recommendation = Recommendword("mero");
   for(const auto& word: Recommendation){
     std::cout << word << '\n';	   
   }
}
