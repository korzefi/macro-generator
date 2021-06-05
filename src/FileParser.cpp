#include "FileParser.h"
#include <iostream>

namespace macrogen {

namespace {
    const char* REPT = ".REPT";
    const char* ENDM = ".ENDM";
    const int OFFSET = 6;
    const unsigned long NOT_FOUND = std::string::npos;
}

data_type FileParser::parse(std::string raw_file) {
    int file_beggining_index = 0;
    parse(raw_file, file_beggining_index);
    return parsed_macros;
}

void FileParser::parse(const std::string& raw_file, long macro_begining_index) {
    std::string expression;
    std::string definition;
    try {
        expression = getExpression(raw_file, macro_begining_index);
        definition = getDefinition(raw_file, macro_begining_index);
        parsed_macros.push_back(std::pair<std::string, std::string>(expression, definition));
        parse(raw_file, macro_begining_index);
    }
    catch(const NoMoreReptFoundException& e) {
        return;
    }
    catch(const NoMoreEndmFoundException& e) {
        std::string empty_definition = "";
        parsed_macros.push_back(std::pair<std::string, std::string>(expression, empty_definition));
        return;
    }
}

std::string FileParser::getExpression(const std::string& raw_file, long& begining_index) {
    long expression_start = raw_file.find(REPT, begining_index);
    if (expression_start == NOT_FOUND) {
        throw NoMoreReptFoundException();
    }
    long expression_end = raw_file.find("\n", expression_start);
    long expression_len = expression_end - (expression_start + OFFSET);
    
    begining_index = expression_end + 1;
    return raw_file.substr(expression_start + OFFSET, expression_len);
}

std::string FileParser::getDefinition(const std::string &raw_file, long& begining_index) {
    long definition_start = begining_index;
    long definition_end = raw_file.find(ENDM, definition_start);
    long definition_len = definition_end - definition_start;
    if (definition_end == NOT_FOUND) {
        throw NoMoreEndmFoundException();
    }
    
    begining_index = definition_end + OFFSET;
    return raw_file.substr(definition_start, definition_len);
}


} //namespace macrogen
