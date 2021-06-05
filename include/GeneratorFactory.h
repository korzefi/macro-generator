#ifndef GeneratorFactory_h
#define GeneratorFactory_h

#include "Generator.h"

#include <iostream>

namespace macrogen {

class GeneratorFactory {
public:
    GeneratorFactory() = default;
    static std::unique_ptr<Generator> createGenerator();
    
private:
    static std::unique_ptr<FileHandler> createFileHandler();
    static std::unique_ptr<SyntaxAnalyzer> createSyntaxAnalyzer();
    static std::unique_ptr<ExpressionCalculator> createExpressionCalculator();
};

} //namespace macrogen



#endif /* GeneratorFactory_h */
