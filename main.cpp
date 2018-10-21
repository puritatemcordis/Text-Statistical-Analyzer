#include<cstdlib>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<locale>

//Function prototypes
bool CheckString(std::string str);
int TotalAlphaNumeric(std::string& str);
int TotalAlpha(std::string str);
int TotalNumeric(std::string str);
std::vector<std::string> StringToVector(std::string str, char separator);
int FindStartSubstring(std::vector<std::string> vStr, std::string substr);
int FindEndSubstring(std::vector<std::string> vStr, std::string substr);
int FindMiddleSubstring(std::vector<std::string> vStr, std::string substr);
int TotalSequence(std::vector<std::string> vStr);


int main(){

  std::string str;
  bool check = false;

  while(!check){
    std::cout << "Enter your string: (IT MUST END WITH #)" << std::endl;
    getline(std::cin, str); //sample input: tedt  tedtedted  abted  ted  ab  tteda#
    check = CheckString(str);
  }

  std::cout << "Total number of alphanumeric characters: " << TotalAlphaNumeric(str) << std::endl;
  std::cout << "Total number of letters: " << TotalAlpha(str) << std::endl;
  std::cout << "Total number of digits: " << TotalNumeric(str) << std::endl;

  std::vector<std::string> vStr = StringToVector(str, ';');

  std::cout << "Total number of words: " << vStr.size() << std::endl;
  std::cout << "Total number of words starting with \"ted\": " << FindStartSubstring(vStr, "ted") << std::endl;
  std::cout << "Total number of words ending with \"ted\": " << FindEndSubstring(vStr, "ted") << std::endl;
  std::cout << "Total number of words with \"ted\" in the middle: " << FindMiddleSubstring(vStr, "ted") << std::endl;
  std::cout << "Total number of sequences of 3 consecutive characters: " << TotalSequence(vStr) << std::endl;
  std::cout << "Total number of sequences of 3 consecutive characters: " << FindStartSubstring(vStr, "ted") + FindEndSubstring(vStr, "ted") + FindMiddleSubstring(vStr, "ted") << "/" << TotalSequence(vStr) << std::endl;

  return 0;
}

//Function definitions

//returns true if the last value is # else returns false
//@param str: string that holds user input
bool CheckString(std::string str){

  if(str[str.size() - 1] == '#') return true;

  return false;
}

//returns the amount of alphanumeric characters in the string
//@param str: pass-by-reference string that holds user input
int TotalAlphaNumeric(std::string& str){
  int counter = 0;
  for(int i = 0; i < str.size(); i++){
    if(std::isalnum(str[i]) == false){
      str[i] = ';';
      counter++;
    }
  }
  return (str.size() - counter);
}

//returns the amount of letters in the string
//@param str: pass-by-reference string that holds user input
int TotalAlpha(std::string str){
  int counter = 0;
  for(int i = 0; i < str.size(); i++){
    if(std::isalpha(str[i]) == false){
      counter++;
    }
  }
  return (str.size() - counter);
}

//returns the amount of digits in the string
//@param str: pass-by-reference string that holds user input
int TotalNumeric(std::string str){
  int counter = 0;
  for(int i = 0; i < str.size(); i++){
    if(std::isdigit(str[i]) == false){
      counter++;
    }
  }
  return (str.size() - counter);
}

//returns vector of the substrings within the string that was separated a CSV
//@param str: string that holds user input
//@param separator: CSV that separates the strings from each other
std::vector<std::string> StringToVector(std::string str, char separator){
  std::vector<std::string> vStr;

  std::stringstream ss(str);
  std::string substr;
  while(getline(ss, substr, separator)){
    if(substr == "") continue;
    if(substr == "#") break;
    vStr.push_back(substr);
  }

  return vStr;
}


//returns the amount of words that began with the substring
//@param vStr: vector of strings/words that was derived from the user's inputted string
//@param substr: string that is being sought inside the vector of strings
int FindStartSubstring(std::vector<std::string> vStr, std::string substr){
  int wordCount = 0;

  for(int i = 0; i < vStr.size(); i++){
    std::string str = vStr[i];
    int counter = 0;

    for(int j = 0; j < 4; j++){
      if(counter == 3) wordCount++;
      if(j == 4) break;
      if(str[j] == substr[j]) counter++;
    }
  }

  return wordCount;
}

//returns the amount of words that end with the substring
//@param vStr: vector of strings/words that was derived from the user's inputted string
//@param substr: string that is being sought inside the vector of strings
int FindEndSubstring(std::vector<std::string> vStr, std::string substr){
  int wordCount = 0;

  for(int i = 0; i < vStr.size(); i++){
    std::string str = vStr[i];
    int counter = 0;
    int k = substr.size() - 1;

    for(int j = str.size() -1 ; j > 0; j--){
      if(j == (str.size() - 4)) break;
      if(str[j] == substr[k]) counter++;
      if(counter == 3) wordCount++;
      k--;

    }
  }

  return wordCount;
}

//returns the amount of words that had the substring in the middle
//@param vStr: vector of strings/words that was derived from the user's inputted string
//@param substr: string that is being sought inside the vector of strings
int FindMiddleSubstring(std::vector<std::string> vStr, std::string substr){
  int wordCount = 0;

  for(int i = 0; i < vStr.size(); i++){
    std::string str = vStr[i];
    int counter = 0;
    int k = 0;

    for(int j = 1; j < str.size() - 2; j++){
      if((str[j] == 't') && ((j+3) < str.size())){
        int l = j;
        while(k < substr.size()){
          if(str[l] == substr[k]) counter++;
          if(counter == 3) wordCount++;
          k++;
          l++;
        }
      }
    }
  }

  return wordCount;
}

//returns size of a vector of strings that hold variations of 3 consecutive characters 
//@param vStr: vector of strings/words that was derived from the user's inputted string
int TotalSequence(std::vector<std::string> vStr){
  std::vector<std::string> vSequence;

  for(int i = 0; i < vStr.size(); i++){
    std::string str = vStr[i];

    for(int j = 0; j < str.size(); j++){
      std::string newstr = "";
      int k = j;

      if((j+2) < str.size()){
        while(k <= (j+2)){
          newstr.push_back(str[k]);
          k++;
        }
        vSequence.push_back(newstr);
      }
    }
  }
  return vSequence.size();
}
