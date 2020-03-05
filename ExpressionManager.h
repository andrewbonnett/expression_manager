//determine if parentheses are matched in an expression
//Evaluate a postfix expression
//convert postfix to infix notation
//convert infix to postfix
#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include "ExpressionManagerInterface.h"

using namespace std;

class ExpressionManager : public ExpressionManagerInterface {

private:
    
    bool process_operator(stack<string> &operator_stack, string &postfix, string currentOperator);
    int getOperatorPrecedence(string operatorSymbol);
    bool parenthesesMatch(string closingparen, string couldbeopening);
    
public:
    ExpressionManager();
    ~ExpressionManager();
    
    bool isBalanced(string expression);
    
    string postfixToInfix(string postfixExpression);
    
    string postfixEvaluate(string postfixExpression);
    
    string infixToPostfix(string infixExpression);

};
#endif