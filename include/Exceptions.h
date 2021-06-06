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

class ExpressionCalculatorException : public std::exception {
public:
    const char* what() const throw() = 0;
};

class NegativeValueExpressionResultException : public ExpressionCalculatorException {
public:
    NegativeValueExpressionResultException() = default;
    const char* what() const throw() override {
        return "Negative value expression result: the result must be a positive number";
    }
};

class DivisionByZeroException : public ExpressionCalculatorException {
public:
    DivisionByZeroException() = default;
    const char* what() const throw() override {
        return "Division by 0 in an expression";
    }
};

#endif /* Exceptions_h */
