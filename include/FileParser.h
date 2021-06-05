#ifndef FileParser_h
#define FileParser_h

#include "Exceptions.h"

#include <vector>
#include <string>
#include <utility>

namespace macrogen {

typedef std::vector<std::pair<std::string, std::string>> data_type;

class FileParser {
public:
    FileParser() = default;
    
    data_type parse(std::string raw_file);
    
private:
    data_type parsed_macros;
    
    void parse(const std::string& raw_file, long macro_begining_index);
    std::string getExpression(const std::string& raw_file, long& begining_index);
    std::string getDefinition(const std::string& raw_file, long& begining_index);
};

} //namespace macrogen


#endif /* FileParser_h */
