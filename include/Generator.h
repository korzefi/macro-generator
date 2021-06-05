#ifndef Generator_h
#define Generator_h

#include "FileHandler.h"
#include "SyntaxAnalyzer.h"
#include "ExpressionCalculator.h"

#include <iostream>
#include <string>
#include <memory>

namespace macrogen {

class Generator {
public:
    Generator(std::unique_ptr<FileHandler> file_handler,
              std::unique_ptr<SyntaxAnalyzer> analyzer,
              std::unique_ptr<ExpressionCalculator> calculator);
    
    void convert(std::string input_filepath, std::string output_filepath, std::string exception_filepath);
    
private:
    data_type input_data;
    data_type verified_input_data;
    std::vector<std::string> output_data;
    std::vector<std::string> exception_data;
    std::unique_ptr<FileHandler> file_handler;
    std::unique_ptr<SyntaxAnalyzer> analyzer;
    std::unique_ptr<ExpressionCalculator> calculator;
    
    void getInputData(const std::string& input_filepath);
    void initializeOutputData();
    void verifyInputData(const std::string& exception_filepath);
    void checkSyntaxCorrectness(const std::string& expression, const std::string& definition);
    void constructOutputData();
    void constructMacroResult(const std::string& expression, const std::string& definition);
    std::string buildMultipliedMacroOutput(const std::string& definition, int multiplier);
    void trimWhitespace(std::string& str);
    void writeOutputData(const std::string& output_filepath, const std::string& exception_filepath);
    void reset();
};

} //namespace macrogen



#endif /* Generator_h */
