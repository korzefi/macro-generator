#include "TokenParser.h"

#include <exception>

namespace macrogen {

namespace {
std::vector<const char> OPERATORS = {'+', '-', '*', '/'};
const char NUMBER = '8';
const char END = '0';
const size_t NOT_FOUND = std::string::npos;
const int OPER_LEN = 1;
}

TokenParser::TokenParser(std::unique_ptr<LiteralValueChecker> val_checker) : val_checker(std::move(val_checker))
{
}

std::vector<Token> TokenParser::parse(const std::string& expression, const std::string& definition) {
    expression_factors.clear();
    parsed_expression.clear();
    std::vector<size_t> oper_indexes = getOperatorsIndexes(expression);
    std::sort(oper_indexes.begin(), oper_indexes.end());
    findRawFactors(expression, oper_indexes);
    getFactorsAsTokens(expression, definition);
    addEndToken();
    return parsed_expression;
}

std::vector<size_t> TokenParser::getOperatorsIndexes(const std::string& expression) {
    std::vector<size_t> opers_positions;
    for (char oper : OPERATORS) {
        auto one_oper_positions = getOneOperatorIndexes(expression, oper);
        addOneOperPositionsToAllOthers(opers_positions, one_oper_positions);
    }
    return opers_positions;
}

std::vector<size_t> TokenParser::getOneOperatorIndexes(const std::string& expression, char oper) {
    std::vector<size_t> oper_positions;
    size_t start_index = 0;
    while (true) {
        size_t pos = expression.find(oper, start_index);
        if (pos == NOT_FOUND) {
            break;
        }
        oper_positions.push_back(pos);
        start_index = pos+1;
    }
    return oper_positions;
}

void TokenParser::addOneOperPositionsToAllOthers(std::vector<size_t>& all_opers_positions, const std::vector<size_t>& one_oper_positions) {
    all_opers_positions.insert(all_opers_positions.end(), one_oper_positions.begin(), one_oper_positions.end());
}

void TokenParser::findRawFactors(const std::string& expression, const std::vector<size_t>& indexes) {
    size_t start = 0;
    for (size_t current_pos : indexes) {
        findFactorPrecedingOperator(expression, start, current_pos);
        start = current_pos;
        findOperator(expression, current_pos);
        start = current_pos + OPER_LEN;
    }
    findLastFactorFollowingOperator(expression, start);
}

void TokenParser::findFactorPrecedingOperator(const std::string& expression, size_t factor_start_pos, size_t oper_pos) {
    size_t len = oper_pos - factor_start_pos;
    std::string found_factor = expression.substr(factor_start_pos, len);
    expression_factors.push_back(found_factor);
}

void TokenParser::findOperator(const std::string& expression, size_t oper_pos) {
    std::string found_oper = expression.substr(oper_pos, OPER_LEN);
    expression_factors.push_back(found_oper);
}

void TokenParser::findLastFactorFollowingOperator(const std::string& expression, size_t last_factor_start_pos) {
    size_t len = expression.size() - last_factor_start_pos;
    std::string found_last = expression.substr(last_factor_start_pos, len);
    expression_factors.push_back(found_last);
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


