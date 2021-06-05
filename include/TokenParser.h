#ifndef TokenParser_h
#define TokenParser_h

#include "LiteralValueChecker.h"

#include <vector>
#include <string>

namespace macrogen {

struct Token {
    char kind;
    int value;
};

class TokenParser {
public:
    TokenParser(std::unique_ptr<LiteralValueChecker> val_checker);
    std::vector<Token> parse(const std::string& expression, const std::string& definition);
private:
    std::unique_ptr<LiteralValueChecker> val_checker;
    std::vector<Token> parsed_expression;
    std::vector<std::string> expression_factors;
    
    std::vector<size_t> getFactorsIndexes(const std::string& expression);
    void findRawFactors(const std::string& expression, const std::vector<size_t>& indexes);
    void getFactorsAsTokens(const std::string& expression, const std::string& definition);
    bool isOperType(const std::string& factor);
    char getOperAsChar(const std::string& oper);
    Token createOperToken(char oper);
    bool isValueType(const std::string& factor);
    Token createValToken(int val);
    void addEndToken();
};

} // namespace macrogen

#endif /* TokenParser_h */
