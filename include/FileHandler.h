#ifndef FileHandler_h
#define FileHandler_h

#include "FileParser.h"
#include <string>
#include <fstream>

namespace macrogen {

class FileHandler {
public:
    FileHandler(std::unique_ptr<FileParser> parser);
    data_type readData(const std::string& input_filepath);
    void writeData(const std::string& filepath, std::vector<std::string> output);
    
private:
    std::string raw_macros;
    data_type parsed_macros;
    std::unique_ptr<FileParser> parser;
    
    void readRawFile(const std::string& input_filepath);
    std::string readLines(std::ifstream& ifs);
    void parse();
    void saveResults(std::ofstream& ofs, const std::vector<std::string>& output);
};

} //namespace macrogen


#endif /* FileHandler_h */
