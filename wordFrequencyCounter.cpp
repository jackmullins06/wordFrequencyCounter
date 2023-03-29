#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <algorithm>
#include <vector>

/*
 * Function: is_not_alphanumeric
 * 
 * Determines whether a given character is not alphanumeric.
 * c: the character to check
 * returns: true if the character is not alphanumeric, false otherwise
 */
bool is_not_alphanumeric(char c) {
    return !std::isalnum(c);
}

/*
 * Function: countWordFrequency
 * 
 * Reads a text file and counts the frequency of each word, ignoring case and punctuation.
 * bookFileName: the name of the text file to read
 * returns: a map of each unique word and its frequency in the file
 */
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

/*
 * Function: orderWords
 * 
 * Orders a map of word frequencies by frequency in ascending order and returns a vector of word-frequency pairs.
 * wordFrequency: the map of word frequencies to order
 * returns: a vector of word-frequency pairs ordered by frequency in ascending order
 */
std::vector<std::pair<std::string, int> > orderWords(std::map<std::string, int> wordFrequency){
    auto sorted_words = std::vector<std::pair<std::string, int> >(wordFrequency.begin(), wordFrequency.end());

    std::sort(std::begin(sorted_words), std::end(sorted_words), [] (auto lhs, auto rhs) {
        return lhs.second < rhs.second;
    });

    return sorted_words;
}

/*
 * Function: printWordFrequency
 * 
 * Prints the word-frequency pairs in a given vector to the console.
 * sortedWords: the vector of word-frequency pairs to print
 */
void printWordFrequency(std::vector<std::pair<std::string, int> > sortedWords) {
    for (const auto &value : sortedWords) {
        std::cout << value.first << ": " << value.second << std::endl;
    }
}

/**
 * Function: findWordFrequency
 * 
 * Finds the frequency of a given word in a map of word frequencies.
 * wordFrequency: the map of word frequencies to search
 * word: the word to find the frequency of
 * returns: the frequency of the word in the map, or 0 if the word is not found
 */
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

    if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        std::cout << "This program reads in a text file and outputs the frequency of each word in the file." << std::endl;
        std::cout << "Usage: " << argv[0] << " <filename> [<word>]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help       Display this help message" << std::endl;
        //std::cout << "  -t --top         Display the top n words in the text file" << std::endl;
        return 0;
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


