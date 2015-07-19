#ifndef MATHEMATICALEXPRESSION_H
#define MATHEMATICALEXPRESSION_H

#include <string>

class MathematicalExpression
{
    bool isResultCalculated;
    std::string expression;
    double result;
public:
    MathematicalExpression();
    MathematicalExpression(std::string);
    double getResult();
    void setExpression(std::string);
    double evaluateTerm(char,double,double);
    double evaluate();
    double evaluate(std::string);
    int skipBlankChars(std::string, int); // Returns the index of first non-space character. Starting from second argument. Returns second argument if first argument starts with a non-space character.
    std::string expressionErrorMessage(std::string); // Returns "" if there are no errors found or an error message otherwise.
    bool isOperator(char); // Checks if argument is '+' or  '-' or '/' or '*' 
};

#endif // MATHEMATICALEXPRESSION_H
