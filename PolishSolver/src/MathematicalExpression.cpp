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

#include <iostream>
#include <stack>
#include <cstdlib>
#include <sstream>
#include <string>

#include "MathematicalExpression.h"


using namespace std;

MathematicalExpression::MathematicalExpression()
{
    this->expression = "";
    this->isResultCalculated = false;
    this->result = 0.0;
}

MathematicalExpression::MathematicalExpression(string expression)
{
    this->expression = expression;
    this->isResultCalculated = false;
    this->result = 0.0;
}

double MathematicalExpression::getResult()
{
    return this->result;
}

void MathematicalExpression::setExpression(string expression)
{
    this->expression = expression;
    this->isResultCalculated = false;
    this->result = 0;
}

double MathematicalExpression::evaluateTerm(char op, double operand1, double operand2)
{
    switch(op)
    {
    case '+':
        return operand1 + operand2;
        break;
    case '-':
        return operand1 - operand2;
        break;
    case '*':
        return operand1 * operand2;
        break;
    case '/':
        return operand1 / operand2;
        break;
    default:
        return 0.0;
    }
}

double MathematicalExpression::evaluate()
{
    string errorMessage = expressionErrorMessage(this->expression);
    if(errorMessage.empty()) // Hata mesaji bossa ifade hatasiz demektir. Ä°slemler gerceklestirilmeli.
    {
        if(isResultCalculated)
        {
            cout << this->expression << " = " << this->result << endl;
            return this->result;
        }
        else
        {
            this->result = this->evaluate(this->expression);
            this->isResultCalculated = true;
            return this->result;
        }
    }
    else // Hata varsa bas.
    {
        cout << errorMessage << endl;
    }
}

double MathematicalExpression::evaluate(string expression)
{
    string errorMessage = expressionErrorMessage(expression);
    if(!errorMessage.empty())
    {
        cout << errorMessage << endl;
        return 0;
    }

    stack<char> symbols;
    stack<double> operands;

    int index = 0;
    char current = 0;
    char *charAfterDouble = NULL;

    char op=0;
    double d1=0,d2=0;
    string temp = "";

    // Her bir karakter icin:
    // Bosluksa atla,
    // '(' ise bir sonraki indisteki operatoru stack'e at,
    // ')' ise sayi stack'inden iki sayi, operator stack'inden bir operator al. Islemi hesapla.
    // Usttekilerden biri degilse sayinin baslangici olmak zorundadÄ±r. Sayiyi strtod ile al. strtod'un ikinci parametresi ile sayidan sonraki karaktere eris. Onun indisini bul. Ana indisi bulunan deger yap.
    while(index < expression.length())
    {
        index = skipBlankChars(expression, index);
        current = expression.at(index);
        if(current == '(')
        {
            index++; // reach operand
            symbols.push(expression.at(index));
            index++; // go over operand
            index = this->skipBlankChars(expression, index);
        }
        else if(current == ')')
        {
            op = symbols.top();
            symbols.pop();

            d2 = operands.top();
            operands.pop();

            d1 = operands.top();
            operands.pop();

            operands.push(evaluateTerm(op,d1,d2));

            index++;
        }
        else // Burada sayi oldugunu biliyoruz.
        {
            temp = expression.substr(index);
            operands.push( strtod(temp.c_str(), &charAfterDouble) ); // Find what comes after double value.

            index = expression.find(*charAfterDouble,index); // Go to whatever comes after double value. Could be a space character or ')'
        }
    }
    cout << expression << " = " << operands.top() << endl;
    return operands.top();
}


int MathematicalExpression::skipBlankChars(std::string str, int idx)
{
    for(; isspace(str.at(idx)); idx++)
        ;
    return idx;
}


string MathematicalExpression::expressionErrorMessage(string expr)
{
    int parans = 0;
    int operators = 0;
    int operands = 0;
    const int LENGTH = expr.length();

    char * charAfterNumber;
    ostringstream errorMessage;

    for(int i = 0; i < LENGTH;)
    {
        if(isspace(expr.at(i)))
        {
            i++;
            continue;
        }
        else if(expr.at(i) == '(')
        {
            parans++;
            if( i+1 >= LENGTH || !isOperator(expr.at(i+1)) ) // parantez acimindan sonra operator olmali.
            {
                errorMessage << "Hesaplanamayan expression :\"" << expr << "\" " << i+1 << " indisinde operator yok.";
                return errorMessage.str();
            }

            operators++; // Ustteki return'de cikmadi. Demekki operator var.

            if( i+2 >= LENGTH || !isspace(expr.at(i+2)) ) // parantez acimindan iki karakter sonra bosluk olmali. Standart isspace fonksiyonu kullanildi.
            {
                errorMessage << "Hesaplanamayan expression :\"" << expr << "\" " << i+2 << " indisinde bosluk yok.";
                return errorMessage.str();
            }

            i += 2;
        }
        else if(expr.at(i) == ')')
        {
            parans--;
            operators--;
            operands--; // Ýki deger kullanip bir deger yazildigindan bir azalmali.
            i++;
        }
        else // Sayi olmali
        {
            if(isOperator(expr.at(i))) // Buraya girerse operatorden once '(' yok demektir.
            {
                errorMessage << "Hesaplanamayan expression :\"" << expr << "\" " << i << " indisindeki operatorden once '(' bekleniyor.";
                return errorMessage.str();
            }

            if( i-1 >= 0 && !isspace(expr.at(i-1))) // Sayidan once bosluk olmali
            {
                errorMessage << "Hesaplanamayan expression :\"" << expr << "\" " << i << " indisindeki sayidan once bosluk bekleniyor.";
                return errorMessage.str();
            }

            strtod(expr.substr(i).c_str(), &charAfterNumber); // Sayiyi parse etmeye calis. Sayidan sonraki karakteri charAfterNumber gostersin.
            if(!isspace(*charAfterNumber) && *charAfterNumber != ')') // Sayidan sonra bosluk veya ')' yoksa hata ver.
            {
                errorMessage << "Hesaplanamayan expression :\"" << expr << "\" " << i << " indisindeki sayidan sonra bosluk veya ')' bekleniyor.";
                return errorMessage.str();
            }
            operands++;
            i = expr.find(*charAfterNumber, i); // Sayidan sonra ilk bulunan bosluk veya ')' ise oraya atla.
        }
    }

    if(parans != 0)
    {
        errorMessage << "Hesaplanamayan expression :\"" << expr << "\" parantez acildigi kadar kapatilmamis.";
        return errorMessage.str();
    }
    else if(operators != 0)
    {
        errorMessage << "Hesaplanamayan expression :\"" << expr << "\" operatorler sifirlanamamis.";
        return errorMessage.str();
    }
    else if(operands != 1) // En sonda stack'te 1 eleman kalmali. O da ifadenin sonuc degeri.
    {
        errorMessage << "Hesaplanamayan expression :\"" << expr << "\" operandlar beklenen sayida degil.";
        return errorMessage.str();
    }
    else // Hata saptanmadi. Bos string don.
    {
        return "";
    }
}

bool MathematicalExpression::isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}
