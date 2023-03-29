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

std::map<std::string, int> pruneStopWords(std::map<std::string, int> wordFrequency) {
    std::map<std::string, int> prunedMap;

    std::vector<std::string> stopWords = {
        "a", "an", "and", "are", "as", "at", "be", "but", "by", "for", 
        "if", "in", "into", "is", "it", "no", "not", "of", "on", "or", 
        "such", "that", "the", "their", "then", "there", "these", "they", 
        "this", "to", "was", "will", "with", "he", "she", "you", "your", 
        "i", "me", "my", "we", "us", "our", "him", "his", "her", "hers"
    };

    for (const auto& stopWord : stopWords) {
        wordFrequency.erase(stopWord);
    }

    return prunedMap;
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
    int wordCuont = 0;
    
    auto it = wordFrequency.find(word);
    if(it!= wordFrequency.end()) {
        return it->second;
    } else {   
        return 0;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename> [<word>]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::map<std::string, int> map = countWordFrequency(filename);
    std::vector<std::pair<std::string, int> > sortedWords = orderWords(map);

    if (argc == 2) {
        printWordFrequency(sortedWords);
    } else if (argc == 3) {
        std::string wordToFind = argv[2];
        int frequency = findWordFrequency(map, wordToFind);
        std::cout << "Frequency of '" << wordToFind << "': " << frequency << std::endl;
    } else {
        std::cout << "Usage: " << argv[0] << " <filename> [<word>]" << std::endl;
        return 1;
    }

    return 0;
}


