#ifndef SyntaxAnalyzer_h
#define SyntaxAnalyzer_h

#include <iostream>
#include <string>

namespace macrogen {

class SyntaxAnalyzer {
public:
    SyntaxAnalyzer() = default;
    void checkCorrectness(const std::string& expression, const std::string& definition);
    
private:
    void checkForMissingElement(const std::string& expression, const std::string& definition);
    void checkForCorrectExpressionSyntax(const std::string& expression);
    std::vector<size_t> getOperatorsLocations(const std::string& expression);
    std::vector<size_t> getSingleOperatorLocations(const std::string& expression, char oper);
    bool isFound(size_t pos);
    void checkOperatorsCoexistence(const std::vector<size_t>& oper_locations);
};

} //namespace macrogen


#endif /* SyntaxAnalyzer_h */
