#include "Generator.h"
#include "Exceptions.h"


namespace macrogen {

Generator::Generator(std::unique_ptr<FileHandler> file_handler,
                     std::unique_ptr<SyntaxAnalyzer> analyzer,
                     std::unique_ptr<ExpressionCalculator> calculator) :
file_handler(std::move(file_handler)),
analyzer(std::move(analyzer)),
calculator(std::move(calculator))
{
    
}

void Generator::convert(std::string input_filepath, std::string output_filepath, std::string exception_filepath) {
    getInputData(input_filepath);
    verifyInputData(exception_filepath);
    constructOutputData();
    writeOutputData(output_filepath, exception_filepath);
    reset();
}

void Generator::getInputData(const std::string& input_filepath) {
    input_data = file_handler->readData(input_filepath);
}

void Generator::verifyInputData(const std::string& exception_filepath) {
    std::string expression;
    std::string definition;
    for (const auto& macro : input_data) {
        expression = macro.first;
        definition = macro.second;
        checkSyntaxCorrectness(expression, definition);
    }
}

void Generator::checkSyntaxCorrectness(const std::string& expression, const std::string& definition) {
    try {
        analyzer->checkCorrectness(expression, definition);
        verified_input_data.push_back(std::pair<std::string, std::string>{expression, definition});
    }
    catch (const SyntaxAnalyzerException& e) {
        std::string message = e.what();
        exception_data.push_back(message);
    }
}

void Generator::constructOutputData() {
    std::string expression;
    std::string definition;
    for (const auto& macro : verified_input_data) {
        expression = macro.first;
        definition = macro.second;
        constructMacroResult(expression, definition);
    }
}

void Generator::constructMacroResult(const std::string& expression, const std::string& definition) {
    try {
        int multiplier = calculator->calculateResult(expression, definition);
        std::string macro_result = buildMultipliedMacroOutput(definition, multiplier);
        output_data.push_back(macro_result);
    }
    catch (ExpressionCalculatorException& e) {
        exception_data.push_back(e.what());
    }
}

std::string Generator::buildMultipliedMacroOutput(const std::string& definition, int multiplier) {
    std::string result;
    for (int i=0; i<multiplier; i++) {
        result += definition;
    }
    trimWhitespace(result);
    return result;
}

void Generator::trimWhitespace(std::string& str) {
    if (not str.empty()) {
        str.pop_back();
    }
}

void Generator::writeOutputData(const std::string& output_filepath, const std::string& exception_filepath) {
    file_handler->writeData(output_filepath, output_data);
    file_handler->writeData(exception_filepath, exception_data);
}

void Generator::reset() {
    input_data.clear();
    output_data.clear();
    exception_data.clear();
}

} //namespace macrogen




