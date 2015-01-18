//
//  WordAnalyser.h
//  WordFreq
//
//  Created by Soroush Javidi on 10/01/2015.
//  Copyright (c) 2015 Soroush Javidi. All rights reserved.
//

#ifndef __WordFreq__WordAnalyser__
#define __WordFreq__WordAnalyser__

#include <stdio.h>
#include <string>
#include <map>
#include <vector>


typedef std::map<std::string, unsigned int> KV_wordmap;
typedef std::pair<std::string, unsigned int> wordmap_pair;
typedef std::pair<unsigned int, std::string> reverse_wordmap_pair;


/* CLASS WordAnalyser
   ------------------
   Find the word densitiy in a given string.
   Output the results to screen, or save in a file.
*/

class WordAnalyser {
private:
    
    std::string excluded_words_file_name;
    std::vector<std::string> exclusions;
    std::string punctation_str = "!@£$%^&*()-_=+`~,<.>/?;:'\"\\|";
    std::vector<char> punctuations;
    std::string source_file_name;
    void update_word_map(KV_wordmap & word_freq_map, const std::string & str);
    

public:
    
    // Constructors and destructor
    WordAnalyser();
    WordAnalyser(std::string _source_file_name);
    WordAnalyser(std::string _source_file_name, std::string _excluded_words_file_name);
    virtual ~WordAnalyser();
    
    // methods
    std::string filename();
    KV_wordmap get_freq_count();
    bool is_excluded_word(const std::string & str);
    void populate_punctuations(const std::string & punctuation_input);
    void populate_exclusions(const std::string & exclusion_file);
    void pretty_print(const KV_wordmap & word_map, bool sorted = false);
    void save_toCSV(const KV_wordmap & word_map, const std::string & output_file_name, const std::string & separator = ";");
    void set_excluded_words_filename(std::string _excluded_words_file_name);
    void set_filename(std::string _source_file_name);
    void strip_punctuation(std::string & input_string);
    
};

#endif /* defined(__WordFreq__WordAnalyser__) */
