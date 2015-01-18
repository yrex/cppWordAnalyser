//
//  main.cpp
//  WordFreq
//
//  Created by Soroush Javidi on 10/01/2015.
//  Copyright (c) 2015 Soroush Javidi. All rights reserved.
//

#include <iostream>
#include "WordAnalyser.h"

int main(int argc, const char * argv[]) {
    
    WordAnalyser wa;
    std::string output_filename = "";
    if (argc == 2) {
        wa = WordAnalyser(argv[1]);
    }
    else if (argc == 3) {
        wa = WordAnalyser(argv[1], argv[2]);
    }
    else if (argc == 4) {
        wa = WordAnalyser(argv[1], argv[2]);
        output_filename = argv[3];
    }
    else {
        std::cout << "WordFreq SourceFile [ExcludeWordsFile OutputCSVFile]" << std::endl;
        std::cout << "explanation of these inputs:" << std::endl;
        std::cout << "    [1] SourceFile: Source file path" << std::endl;
        std::cout << "    [2] ExcludeWordsFile: Excluded words file path" << std::endl;
        std::cout << "    [3] OutputCSVFile: Output CSV file path" << std::endl << std::endl;
        
        return 0;
    }
   
    // std::string source_file = "TheRaven.txt";
    // std::string exclude_words_file = "excluded_words.txt";

    // WordAnalyser wa = WordAnalyser(source_file, exclude_words_file);
    
    std::cout << "Filename: " << wa.filename() << "\n";
    
    // analyse word density in source file
    KV_wordmap word_density;
    word_density = wa.get_freq_count();
    
    // print results to screen
    wa.pretty_print(word_density, true);
    
    // save results to file if an output file is given
    if (output_filename != "") {
        wa.save_toCSV(word_density, output_filename);
    }
    
    return 0;
}
