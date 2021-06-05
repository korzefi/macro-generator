#include "ExpressionCalculator.h"


namespace macrogen {

namespace {
    const char NUMBER = '8';
    const char END = '0';
}

ExpressionCalculator::ExpressionCalculator(std::unique_ptr<LiteralValueChecker> checker,
                                           std::unique_ptr<TokenParser> token_parser) :
checker(std::move(checker)),
token_parser(std::move(token_parser))
{
    current_token = -1;
    
    Token t0, t1, t2, t3, t4, t5;
    t0.kind = NUMBER;
    t0.value = 9;
    t1.kind = '-';
    t2.kind = NUMBER;
    t2.value = 3;
    t3.kind = '*';
    t4.kind = NUMBER;
    t4.value = 2;
    t5.kind = END;
    parsed_tokens = {t0, t1, t2, t3, t4, t5};
}


int ExpressionCalculator::calculateResult(std::string expression, std::string definition) {
    int result = getExpression();
    std::cout << "Result: " << result << std::endl;
    return result;
}

int ExpressionCalculator::getExpression() {
    int left = getTerm();
    Token token = getNextToken();
    while (true) {
        switch (token.kind) {
            case '+':
                left += getTerm();
                token = getNextToken();
                break;
            case '-':
                left -= getTerm();
                token = getNextToken();
                break;
            default:
                setPrevToken();
                return left;
        }
    }
}

Token ExpressionCalculator::getNextToken() {
    current_token++;
    return parsed_tokens[current_token];
}

void ExpressionCalculator::setPrevToken() {
    current_token--;
}

int ExpressionCalculator::getTerm() {
    int left = getPrimary();
    Token token = getNextToken();
    while (true) {
        switch (token.kind) {
            case '*':
                left *= getTerm();
                token = getNextToken();
                break;
            case '/':
                // ADD EXCEPTION FOR DIVIDING BY 0
                left /= getTerm();
                token = getNextToken();
                break;
            default:
                setPrevToken();
                return left;
        }
    }
}

int ExpressionCalculator::getPrimary() {
    Token token = getNextToken();
    return token.value;
}

} //namespace macrogen
