#ifndef ExpressionCalculator_h
#define ExpressionCalculator_h

#include "LiteralValueChecker.h"
#include "TokenParser.h"

#include <iostream>
#include <memory>

namespace macrogen {

class ExpressionCalculator {
public:
    ExpressionCalculator(std::unique_ptr<TokenParser> token_parser);
    
    int calculateResult(std::string expression, std::string definition);
private:
    std::unique_ptr<TokenParser> token_parser;
    std::vector<Token> parsed_tokens;
    int current_token;
    
    int getExpression();
    int getTerm();
    int getPrimary();
    Token getNextToken();
    void setPrevToken();
    void throwNegativeExceptIfNegativeResult(int result);
};

} //namespace macrogen


#endif /* ExpressionCalculator_h */
