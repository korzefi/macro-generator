#include "GeneratorFactory.h"


namespace macrogen {

std::unique_ptr<Generator> GeneratorFactory::createGenerator() {
    std::unique_ptr<FileHandler> file_handler = createFileHandler();
    std::unique_ptr<SyntaxAnalyzer> analyzer = createSyntaxAnalyzer();
    std::unique_ptr<ExpressionCalculator> calculator = createExpressionCalculator();
    
    return std::make_unique<Generator>(std::move(file_handler), std::move(analyzer), std::move(calculator));
}

std::unique_ptr<FileHandler> GeneratorFactory::createFileHandler() {
    std::unique_ptr<FileParser> parser = std::make_unique<FileParser>();
    return std::make_unique<FileHandler>(std::move(parser));
}

std::unique_ptr<SyntaxAnalyzer> GeneratorFactory::createSyntaxAnalyzer() {
    return std::make_unique<SyntaxAnalyzer>();
}

std::unique_ptr<ExpressionCalculator> GeneratorFactory::createExpressionCalculator() {
    std::unique_ptr<LiteralValueChecker> checker = std::make_unique<LiteralValueChecker>();
    std::unique_ptr<TokenParser> token_parser = std::make_unique<TokenParser>();
    return std::make_unique<ExpressionCalculator>(std::move(checker), std::move(token_parser));
}


} //namespace macrogen
