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
    
    std::vector<size_t> getOperatorsIndexes(const std::string& expression);
    std::vector<size_t> getOneOperatorIndexes(const std::string& expression, char oper);
    void addOneOperPositionsToAllOthers(std::vector<size_t>& all_opers_positions, const std::vector<size_t>& one_oper_positions);
    void findRawFactors(const std::string& expression, const std::vector<size_t>& indexes);
    void findFactorPrecedingOperator(const std::string& expression, size_t factor_start_pos, size_t oper_pos);
    void findLastFactorFollowingOperator(const std::string& expression, size_t last_factor_start_pos);
    void findOperator(const std::string& expression, size_t oper_pos);
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
