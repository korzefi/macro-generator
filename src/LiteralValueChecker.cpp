#include "LiteralValueChecker.h"


namespace macrogen {

namespace {
const size_t NOT_FOUND = std::string::npos;
};

int LiteralValueChecker::getLiteralValue(const std::string& factor, const std::string& definition) {
    auto pos = getStartEndPositionIfExists(factor, definition);
    if (pos.first == NOT_FOUND) {
        return 0;
    }
    std::string str_value = getFactorValue(pos, definition);
    int result = convertToIntegerValue(str_value); //returns 0 if cannot be converted
    return result;
}

std::pair<size_t, size_t> LiteralValueChecker::getStartEndPositionIfExists(const std::string& factor, const std::string& definition) {
    std::pair<size_t, size_t> result;
    std::string factor_with_assignment_oper = factor + "=";
    std::string end_marker = " ";
    size_t start_index = definition.find(factor_with_assignment_oper);
    if (start_index == NOT_FOUND) {
        result.first = NOT_FOUND;
        result.second = NOT_FOUND;
        return result;
    }
    size_t end_index = definition.find(end_marker, start_index);
    result.first = start_index + factor_with_assignment_oper.size();
    result.second = end_index;
    return result;
}

std::string LiteralValueChecker::getFactorValue(std::pair<size_t, size_t> occurence_pos, const std::string& definition) {
    size_t start_index = occurence_pos.first;
    size_t end_index = occurence_pos.second;
    size_t len = end_index - start_index;
    return definition.substr(start_index, len);
}

int LiteralValueChecker::convertToIntegerValue(const std::string& str_value) {
    try {
        int result = std::stoi(str_value);
        return result;
    }
    catch (const std::invalid_argument& e) {
        return 0;
    }
}

} //namespace macrogen



