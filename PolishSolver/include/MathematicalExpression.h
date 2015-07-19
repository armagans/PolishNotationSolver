/*

Copyright 2015 Armağan Salman

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

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
