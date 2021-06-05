#ifndef Exceptions_h
#define Exceptions_h

#include <exception>
#include <string>

class FileParserException : public std::exception {
public:
    virtual const char* what() const throw() = 0;
};

class NoMoreReptFoundException : public FileParserException {
public:
    NoMoreReptFoundException() = default;
    const char* what() const throw() override {
        return "No more .REPT statements were found";
    }
};

class NoMoreEndmFoundException : public FileParserException {
public:
    NoMoreEndmFoundException() = default;
    const char* what() const throw() override {
        return "No more .ENDM statements were found";
    }
};

class SyntaxAnalyzerException : public std::exception {
public:
    const char* what() const throw() = 0;
};

class MissingElementException : public SyntaxAnalyzerException {
public:
    explicit MissingElementException(const char* missing_element_type) : missing_element_type(missing_element_type) {}
    
    const char* what() const throw() override {
        return missing_element_type;
    }
private:
    const char* missing_element_type;
};

class IncorrectExpressionSyntaxException : public SyntaxAnalyzerException {
public:
    IncorrectExpressionSyntaxException() = default;
    const char* what() const throw() override {
        return "Incorrect expression syntax: there are successive operators";
    }
};

#endif /* Exceptions_h */
