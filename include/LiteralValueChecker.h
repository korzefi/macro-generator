#ifndef LiteralValueChecker_h
#define LiteralValueChecker_h

#include <iostream>
#include <string>

namespace macrogen {

class LiteralValueChecker {
public:
    LiteralValueChecker() = default;
    
    int getLiteralValue(const std::string& factor, const std::string& definition);
};

} //namespace macrogen


#endif /* LiteralValueChecker_h */
