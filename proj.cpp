#include "proj.hpp"
#include "Wordset.hpp" 
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>
 
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;
 
	while(	getline(in, line) )
	{
    	ss.clear();
    	ss << line;
    	while( ss >> word )
    	{
            words.insert( word );
    	}
	}
 
}
 
// returns path from s1 to s2
std::string convert(std::string s1, std::string s2, const WordSet & words)
{
    std::queue<std::string> q;
	std::map<std::string, std::string> mappings;
	q.push(s1);
 
	while(!q.empty()) { //loops until q is empty or break occurs
 
    	std::string word = q.front();
    	q.pop();
 
    	if (word == s2) { break; } //if s2 is reached
 
    	for (int i = 0; i < word.length(); i++) { //loop through every letter in word
            for (int j = 0; j < 26; j++) { //loop through every possible letter in alphabet
                std::string tempWord = word;
                tempWord[i] = j + 'a'; //new word (1 sub away from word)
                if (tempWord != word && words.contains(tempWord) && mappings.count(tempWord) == 0) {
                    q.push(tempWord);
                    mappings.insert(std::pair<std::string, std::string> (tempWord, word));
                }
            }
    	}
	}
 
	std::stack<std::string> conversion;
	std::string key = s2;
 
	// go through map, going from s2 to s1
	while(true) {  
    	conversion.push(key);
    	key = mappings.at(key);
    	if (key == s1) break;
	}
	std::string result = s1;
 
	while(!conversion.empty()) {
    	std::string temp = conversion.top();
    	result += " --> " + temp;
    	conversion.pop();
	}
 
	return result;
}
