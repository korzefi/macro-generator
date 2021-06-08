#include "ExpressionCalculator.h"
#include "Exceptions.h"


namespace macrogen {

ExpressionCalculator::ExpressionCalculator(std::unique_ptr<TokenParser> token_parser) :
token_parser(std::move(token_parser))
{
    current_token = -1;
}

int ExpressionCalculator::calculateResult(std::string expression, std::string definition) {
    parsed_tokens.clear();
    current_token = -1;
    parsed_tokens = token_parser->parse(expression, definition);
    int result = getExpression();
    throwNegativeExceptIfNegativeResult(result);
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
    int divisor = 1;
    while (true) {
        switch (token.kind) {
            case '*':
                left *= getTerm();
                token = getNextToken();
                break;
            case '/':
                divisor = getTerm();
                if (divisor == 0) {
                    divisor = 1;
                    throw DivisionByZeroException();
                }
                left /= divisor;
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

void ExpressionCalculator::throwNegativeExceptIfNegativeResult(int result) {
    if (result < 0) {
        throw NegativeValueExpressionResultException();
    }
}

} //namespace macrogen
