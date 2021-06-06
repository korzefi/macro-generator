#ifndef LiteralValueChecker_h
#define LiteralValueChecker_h

#include <iostream>
#include <string>

namespace macrogen {

class LiteralValueChecker {
public:
    LiteralValueChecker() = default;
    
    int getLiteralValue(const std::string& factor, const std::string& definition);
private:
    std::pair<size_t, size_t> getStartEndPositionIfExists(const std::string& factor, const std::string& definition);
    std::string getFactorValue(std::pair<size_t, size_t> occurence_pos, const std::string& definition);
    int convertToIntegerValue(const std::string& str_value);
};

} //namespace macrogen


#endif /* LiteralValueChecker_h */
