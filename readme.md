#Word Analyser

###Background
You may want to find the word usage density in a text file, for exmaple to generate a tag cloud. The WordAnalyser class can be used to analyse a source text file and produce an analysis.

###Usage
A WordAnalyser object can be instantiated as
```c++
WordAnalyser();
WordAnalyser(std::string _source_file_name);
WordAnalyser(std::string _source_file_name, std::string _excluded_words_file_name);
```


###ToDo
Add further configurations to make the class more versatile.

- Output to JSON
- Allow to add exclusion words in the code

