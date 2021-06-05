#include "TokenParser.h"

#include <exception>

namespace macrogen {

namespace {
std::vector<const char> OPERATORS = {'+', '-', '*', '/'};
const char NUMBER = '8';
const char END = '0';
}

TokenParser::TokenParser(std::unique_ptr<LiteralValueChecker> val_checker) : val_checker(std::move(val_checker))
{
}

std::vector<Token> TokenParser::parse(const std::string& expression, const std::string& definition) {
    
    std::vector<size_t> oper_indexes = getFactorsIndexes(expression);
    std::sort(oper_indexes.begin(), oper_indexes.end());
    findRawFactors(expression, oper_indexes);
    getFactorsAsTokens(expression, definition);
    addEndToken();
    return parsed_expression;
}

std::vector<size_t> TokenParser::getFactorsIndexes(const std::string& expression) {
    std::vector<size_t> oper_positions;
    for (char oper : OPERATORS) {
        int start_index = 0;
        size_t pos = expression.find(start_index, oper);
        oper_positions.push_back(pos);
    }
    return oper_positions;
}

void TokenParser::findRawFactors(const std::string& expression, const std::vector<size_t>& indexes) {
    size_t start = 0;
    for (auto current_pos : indexes) {
        size_t len = current_pos - start;
        std::string found_factor = expression.substr(start, len);
        expression_factors.push_back(found_factor);
        start = current_pos;
    }
}

void TokenParser::getFactorsAsTokens(const std::string& expression, const std::string& definition) {
    for (const auto& factor : expression_factors) {
        if (isOperType(factor)) {
            char oper = getOperAsChar(factor);
            Token oper_token = createOperToken(oper);
            parsed_expression.push_back(oper_token);
        }
        else if (isValueType(factor)) {
            int val = std::stoi(factor);
            Token val_token = createValToken(val);
            parsed_expression.push_back(val_token);
        }
        else {
            int val = val_checker->getLiteralValue(factor, definition);
            Token val_token = createValToken(val);
            parsed_expression.push_back(val_token);
        }
    }
}

bool TokenParser::isOperType(const std::string& factor) {
    if (factor.size() > 1) {
        return false;
    }
    char factor_val = getOperAsChar(factor);
    auto oper = std::find(OPERATORS.begin(), OPERATORS.end(), factor_val);
    return oper != OPERATORS.end();
}

char TokenParser::getOperAsChar(const std::string& oper) {
    char factor_char = oper[0];
    return factor_char;
}

Token TokenParser::createOperToken(char oper) {
    Token result;
    result.kind = oper;
    return result;
}

bool TokenParser::isValueType(const std::string& factor) {
    try {
        std::stoi(factor);
        return true;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
}

Token TokenParser::createValToken(int val) {
    Token result;
    result.kind = NUMBER;
    result.value = val;
    return result;
}

void TokenParser::addEndToken() {
    Token end_token;
    end_token.kind = END;
    parsed_expression.push_back(end_token);
}

} // namespace macrogen


