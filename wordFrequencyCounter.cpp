#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <algorithm>
#include <vector>

bool is_not_alphanumeric(char c) {
    return !std::isalnum(c);
}

std::map<std::string, int> countWordFrequency(std::string bookFileName) {
    std::ifstream infile(bookFileName);
    if (!infile) {
        std::cerr << "Error: failed to open input file " << bookFileName << std::endl;
        exit(1);
    }

    std::string word;
    std::map<std::string, int> wordFrequency;
    
    while (infile >> word) {
        for (int i = 0; i < word.length(); i++) {
            word[i] = std::tolower(word[i]);
        }

        word.erase(std::remove_if(word.begin(), word.end(), is_not_alphanumeric), word.end());

        if (!word.empty()) {
            wordFrequency[word]++;
        }
    }

    return wordFrequency;
}

std::vector<std::pair<std::string, int> > orderWords(std::map<std::string, int> wordFrequency){
    auto sorted_words = std::vector<std::pair<std::string, int> >(wordFrequency.begin(), wordFrequency.end());

    std::sort(std::begin(sorted_words), std::end(sorted_words), [] (auto lhs, auto rhs) {
        return lhs.second < rhs.second;
    });

    return sorted_words;
}

void printWordFrequency(std::vector<std::pair<std::string, int> > sortedWords) {
    for (const auto &value : sortedWords) {
        std::cout << value.first << ": " << value.second << std::endl;
    }
}

int findWordFrequency(std::map<std::string, int> wordFrequency, std::string word) {
    auto it = wordFrequency.find(word);
    if(it != wordFrequency.end()) {
        std::cout << word << ": " << it->second << std::endl;
        return it->second;
    } else {
        std::cout << "Word: " << word << " not found" << std::endl;
        return -1; 
    }
}

std::map<std::string, int> pruneStopWords(std::map<std::string, int> wordFrequency) {
    std::vector<std::string> stopWords = {"a", "an", "the", "and", "or", "but", "if", "when", "where", 
                                         "which", "that", "this", "it", "they", "he", "she", "him", "to", "of"};

    for(const auto &word : stopWords) {
        wordFrequency.erase(word);
    }

    return wordFrequency;
}

int main(int argc, char* argv[]) {
    if(strcmp(argv[1], "-h") == 0 || argc > 4) {
        if(argc > 4) {
            std::cerr << "Too many arguments" << std::endl;
        }
        std::cout << "This program reads in a text file and outputs the frequency of each word in the file." << std::endl;
        std::cout << "Usage: [filename] [-w | -s | -h | -p]" << std::endl;
        std::cout << "Options: " << std::endl;
        std::cout << "-h, display this help message" << std::endl;
        std::cout << "-w [word], allows the user to specify a word to find its frequency in the file" << std::endl;
        std::cout << "-s, allows the user to prune 20 pre-programmed stop words" << std::endl;
        std::cout << "-p, allows the user to print every word frequency" << std::endl;
        return 0;
    }

    std::string bookFileName = argv[1];
    std::string mode = argv[2];    

    std::string filename = argv[1];
    std::map<std::string, int> map = countWordFrequency(filename);

    if(mode == "-w") {
        if(argc < 4) {
            std::cerr << "Error: No word specified for -w mode." << std::endl;
            std::cerr << "Usage: [filename] -w [word]" << std::endl;
            return 1;
        }
        std::string word = argv[3];
        findWordFrequency(map, word);
    } else if(mode == "-s") {
        std::map<std::string, int> prunedMap = pruneStopWords(map);
        std::vector<std::pair<std::string, int> > sortedWords = orderWords(prunedMap);
        printWordFrequency(sortedWords);
    } else if(mode == "-p") {
        std::vector<std::pair<std::string, int> > sortedWords = orderWords(map);
        printWordFrequency(sortedWords);
    }


    return 0;
}