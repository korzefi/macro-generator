#include "SyntaxAnalyzer.h"
#include "Exceptions.h"

#include <vector>
#include <string>
#include <iostream>

namespace macrogen {

namespace {
    const std::vector<char> OPERATORS = {'+', '-', '*', '/'};
}

void SyntaxAnalyzer::checkCorrectness(const std::string &expression, const std::string &definition) {
    checkForMissingElement(expression, definition);
    checkForCorrectExpressionSyntax(expression);
}

void SyntaxAnalyzer::checkForMissingElement(const std::string& expression, const std::string& definition) {
    if (expression.empty()) {
        const char* message = "Missing element: expression";
        throw MissingElementException(message);
    }
    else if (definition.empty()) {
        const char* message = "Missing element: definition";
        throw MissingElementException(message);
    }
}

void SyntaxAnalyzer::checkForCorrectExpressionSyntax(const std::string& expression) {
    std::vector<size_t> oper_locations = getOperatorsLocations(expression);
    std::sort(oper_locations.begin(), oper_locations.end());
    checkOperatorsCoexistence(oper_locations);
}

std::vector<size_t> SyntaxAnalyzer::getOperatorsLocations(const std::string& expression) {
    std::vector<size_t> oper_indexes;
    for (char oper : OPERATORS) {
        auto locations = getSingleOperatorLocations(expression, oper);
        oper_indexes.insert(oper_indexes.end(), locations.begin(), locations.end());
    }
    
    return oper_indexes;
}

std::vector<size_t> SyntaxAnalyzer::getSingleOperatorLocations(const std::string& expression, char oper) {
    std::vector<size_t> locations;
    size_t pos = expression.find(oper, 0);
    while (isFound(pos)) {
        locations.push_back(pos);
        pos = expression.find(oper, pos+1);
    }
    return locations;
}

bool SyntaxAnalyzer::isFound(size_t pos) {
    return pos != std::string::npos;
}

void SyntaxAnalyzer::checkOperatorsCoexistence(const std::vector<size_t>& oper_locations) {
    for (int i=0; i+1 < oper_locations.size(); i++) {
        if (oper_locations[i+1] - oper_locations[i] == 1) {
            throw IncorrectExpressionSyntaxException();
        }
    }
}

} //namespace macrogen


