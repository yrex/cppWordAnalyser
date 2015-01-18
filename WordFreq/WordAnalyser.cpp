//
//  WordAnalyser.cpp
//  WordFreq
//
//  Created by Soroush Javidi on 10/01/2015.
//  Copyright (c) 2015 Soroush Javidi. All rights reserved.
//


#ifndef __WordFreq__WordAnalyser__CPP__
#define __WordFreq__WordAnalyser__CPP__


#include "WordAnalyser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>


// Constructors
// ------------

// Default constructor
WordAnalyser::WordAnalyser() {}

// Constructor with a source file name
WordAnalyser::WordAnalyser(std::string _source_file_name) {
    
    source_file_name = _source_file_name;
    
    // populate the punctation list
    populate_punctuations(punctation_str);
}

// Constructor with a source file name and a file name to words to exclude from results
WordAnalyser::WordAnalyser(std::string _source_file_name, std::string _excluded_words_file_name) {
    
    source_file_name = _source_file_name;
    excluded_words_file_name = _excluded_words_file_name;
    
    // populate the punctation list
    populate_punctuations(punctation_str);
    // populate the excluded words list
    populate_exclusions(excluded_words_file_name);
}

// Destructor
WordAnalyser::~WordAnalyser() {}



// Methods
// -------
std::string WordAnalyser::filename() {
    
    /*
     get the source file name
    */
    return source_file_name;
}

void WordAnalyser::set_excluded_words_filename(std::string _excluded_words_file_name) {
    
    /*
     set the excluded words filename
    */
    
    
    excluded_words_file_name = _excluded_words_file_name;
}

void WordAnalyser::set_filename(std::string _source_file_name) {
    
    /*
     set the source filename
     */
    
    source_file_name = _source_file_name;
}

void WordAnalyser::populate_punctuations(const std::string & punctuation_input) {
    
    /*
     populate the punctations vector from string input.
     each character of the input is taken as one punctation.
    */
    
    for (int i = 0; i < punctuation_input.size(); i++) {
        punctuations.push_back(punctuation_input[i]);
    }

}

void WordAnalyser::populate_exclusions(const std::string & exclusion_file) {
    
    /*
     populate the excluded words array from an input string
    */
    
    std::ifstream input_file(exclusion_file);
    std::string line;
    // If file exists, open it
    if (input_file.is_open()) {
        
        // Get each line
        while (std::getline(input_file, line)) {
            exclusions.push_back(line);
        }
        
        input_file.close();
    }
    else {
        std::cout << "Unable to open file " << exclusion_file << std::endl;
    }
    
}

void WordAnalyser::strip_punctuation(std::string & input_string) {
    
    /*
     remove punctuations from the input string
    */
    
    // find punctions in input_string
    
    for (std::size_t i = 0; i < punctuations.size(); i++) {
        
        input_string.erase(
                           std::remove(input_string.begin(), input_string.end(), punctuations[i]),
                           input_string.end()
                           );
    }
}

bool WordAnalyser::is_excluded_word(const std::string &str) {
    
    /*
     check if the string is a word that should be excluded
    */
    
    for (std::size_t i = 0; i < exclusions.size(); i++) {
        if (exclusions[i] == str) {
            return true;
        }
    }
    
    return false;
}

void WordAnalyser::update_word_map(KV_wordmap & word_freq_map, const std::string & str) {
    
    /*
     update the word map key-value pair with the input string
    */
    
    if (word_freq_map.count(str) != 0) {
        // update
        word_freq_map[str]++;
    }
    else {
        // insert
        word_freq_map[str] = 1;
    }
    
}

void WordAnalyser::pretty_print(const KV_wordmap & word_map, bool sorted) {
    
    /*
     print results in a nice format.
     
     results are printed in alphabetical order by default, but can be
     ordered by frequency if the 'sorted' flag is set to true.
    */
    
    if (sorted) {
        // sort ascending and print
        reverse_wordmap_pair word_freq_pair;
        std::vector<reverse_wordmap_pair> vector_of_word_map;
        
        // copy map into a vector
        for (KV_wordmap::const_iterator const_it = word_map.begin(); const_it != word_map.end(); const_it++) {
            word_freq_pair.first = const_it->second;
            word_freq_pair.second = const_it->first;
            vector_of_word_map.push_back(word_freq_pair);
        }
        
        // sort vector
        std::sort(vector_of_word_map.begin(), vector_of_word_map.end());
        
        // print
        std::cout << " --------------------------" << std::endl;
        for (std::size_t i = 0; i < vector_of_word_map.size(); i++) {
            
            std::printf("|%-20s|%5u|\n", vector_of_word_map[i].second.c_str(), vector_of_word_map[i].first);
            
            // std::cout << vector_of_word_map[i].second << "\t" << vector_of_word_map[i].first << std::endl;
        }
        std::cout << " --------------------------" << std::endl;
        
    }
    else {
        // print in alphabetic order
        std::cout << " --------------------------" << std::endl;
        for (KV_wordmap::const_iterator const_it = word_map.begin(); const_it != word_map.end(); const_it++) {
            
            std::printf("|%-20s|%5u|\n", const_it->first.c_str(), const_it->second);
            
            // std::cout << const_it->first << "\t" << const_it->second << std::endl;
        }
        std::cout << " --------------------------" << std::endl;
    }
    
}

void WordAnalyser::save_toCSV(const KV_wordmap & word_map, const std::string & output_file_name, const std::string & separator) {
    
    /*
     save the results to a CSV file.
     
     the separator is set to a semicolon by default. This can be changed using the separator argument.
    */
    
    std::ofstream output_file(output_file_name);
    
    if (output_file.is_open()) {
        for (KV_wordmap::const_iterator const_it = word_map.begin(); const_it != word_map.end(); const_it++) {
            output_file << const_it->first.c_str() << separator << const_it->second << std::endl;
        }
    }
    output_file.close();
}


KV_wordmap WordAnalyser::get_freq_count() {
    
    /*
     
     Analyse the source file and produces a map of words and their frequency.
     
     this method performs the following steps:
      1. Read source_file_name line by line
      2. Extract words
      3. Strip puncuations
      4. Exclude blocked words
      5. Insert or update word count in word_map
      6. return word_map
    */
    

    
    std::string line;
    std::ifstream input_file(source_file_name);
    std::istringstream iss;
    std::string word;
    
    // Hold the word frequency map
    KV_wordmap word_map;
    
    // If file exists, open it
    if (input_file.is_open()) {
        
        // Get each line
        while (std::getline(input_file, line)) {
            
            // get each word in line of text
            iss.str(line);
            while (iss >> word) {
                
                // exclude punctuations
                strip_punctuation(word);
                
                // convert word to lowercase
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                
                // Check if it is an excluded word...
                // if not, add to word frequency vector
                if ( (word != "") && (! is_excluded_word(word)) ) {
                    update_word_map(word_map, word);
                }
                
            }
            
            // Clear the stream because after you read in the whole string, the eof-flag is set to true
            iss.clear();
        }
        
        input_file.close();
    }
    else {
        std::cout << "Unable to open file " << source_file_name << std::endl;
    }
    
    return word_map;
}



#endif