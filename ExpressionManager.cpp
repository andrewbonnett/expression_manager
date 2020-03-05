#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include "ExpressionManager.h"

using namespace std;

ExpressionManager :: ExpressionManager() {}

ExpressionManager :: ~ExpressionManager() {}
    
bool ExpressionManager :: isBalanced(string expression) {
    stack <char> stk; 
    bool balanced = true;
    int i = 0;
    char current;
    while (balanced == true && i < expression.length()) {
        current = expression.at(i);
        if (current == '(' || current == '[' || current == '{') {
            stk.push(current);
        }
        else if (current == ')' || current == ']' || current == '}') {
            if (stk.empty()) {
                balanced = false;
            }
            else if ( (current == ')' && stk.top() == '(') || (current == '}' && stk.top() == '{') || (current == ']' && stk.top() == '[') ) { //
                stk.pop();
            }
            else { balanced = false;}  //if current does not match the operand on the stack, then return false 
        }
        i++;
    }
    
    return balanced && stk.empty();
}

string ExpressionManager :: postfixToInfix(string postfixExpression) {
    string tmp;
    stack <string> numStack;
    string rightOperand;
    
    stringstream read(postfixExpression);
    stringstream write;

    while (read >> tmp) {
        //if first char of the token is a digit, push the token onto the stack
        if (isdigit(tmp[0])) {
            size_t found = tmp.find('.'); 
            if (found == string::npos) {
                numStack.push(tmp);
            }
            else {
                return "invalid";
            }
        }
        else if (tmp == "+" || tmp == "-" || tmp == "*" ||tmp == "/" || tmp == "%") {
            if (numStack.size() < 2) {
                return "invalid";
            }
            else {
                //store right operand
                rightOperand = numStack.top();
                numStack.pop();
                write.str(""); //clear the stringstream
                //write left operand
                write << "( " << numStack.top() << " ";
                numStack.pop();
        
                //write operator
                if (tmp == "+") {
                    write << "+ ";
                }
                else if (tmp == "-") {
                    write << "- ";
                }
                else if (tmp == "*") {
                    write << "* ";
                }
                else if (tmp == "/") {
                    write << "/ ";
                }
                else if (tmp == "%") {
                    write << "% ";
                }
                //write right operand
                write << rightOperand << " )";
                numStack.push(write.str());
            }
        }
    }
    if (numStack.size() == 1) {
        return (numStack.top());
    }
    else { return "invalid"; }
}

string ExpressionManager :: postfixEvaluate(string postfixExpression) {
    string tmp;
    int r; //return this value cast as a string
    stack <int> numStack;
    int rightOperand;
    int leftOperand;
    
    stringstream str_strm(postfixExpression);

    while (str_strm >> tmp) {
        //if first char of the token is a digit, push the token onto the stack
        if (isdigit(tmp[0])) {
            numStack.push(stoi(tmp));
        }
        else if (tmp == "+" || tmp == "-" || tmp == "*" ||tmp == "/" || tmp == "%") {
            if (numStack.empty()) {
                return "invalid";
            }
            rightOperand = numStack.top();
            numStack.pop();
            leftOperand = numStack.top();
            numStack.pop();
            //evaluate expression
            if (tmp == "+") {
                numStack.push(leftOperand + rightOperand);
            }
            else if (tmp == "-") {
                numStack.push(leftOperand - rightOperand);
            }
            else if (tmp == "*") {
                numStack.push(leftOperand * rightOperand);
            }
            else if (tmp == "/") {
                if (rightOperand == 0) {
                    return "invalid";
                }
                numStack.push(leftOperand / rightOperand);
            }
            else if (tmp == "%") {
                numStack.push(leftOperand % rightOperand);
            }
        }
        else {
            return "invalid";
        }
    }
    return (to_string(numStack.top()));
    
}

string ExpressionManager :: infixToPostfix(string infixExpression) {
    if (!isBalanced(infixExpression)) {
        return "invalid";
    }
    
    
    string temp;
    stack<string> operator_stack;
    string postfix = "";
    vector<string> tokens;
    stringstream str_strm(infixExpression);
    int numOperands = 0;
    int numOperators = 0;
    
    //while there are more tokens in the infix string
    while (str_strm >> temp) {
        tokens.push_back(temp);
    }
    cout << "Size of token array " << tokens.size() << endl;
    
    for (int i = 0; i < tokens.size(); i++) {
        if (isdigit( tokens.at(i)[0] ) ) {
            size_t found = tokens.at(i).find('.'); 
            if (found == string::npos) {
                postfix.append(tokens.at(i) );
                cout << postfix << endl;
                postfix.append(" ");
                numOperands++;
            }
            else {
                return "invalid";
            }
        }
        else if ( tokens.at(i) == "+" || tokens.at(i) == "-" || tokens.at(i) == "*" || tokens.at(i) == "/" || tokens.at(i) == "%" ||
        tokens.at(i) == "(" || tokens.at(i) == "{" || tokens.at(i) == "[" || tokens.at(i) == ")" || tokens.at(i) == "}" || tokens.at(i) == "]") {
            //returns true or false
            process_operator(operator_stack, postfix, tokens.at(i) ); //this may or may not be proper syntax?
            cout << postfix << endl;
            
            if ( tokens.at(i) == "+" || tokens.at(i) == "-" || tokens.at(i) == "*" || tokens.at(i) == "/" || tokens.at(i) == "%") { numOperators++; }
        }
        else {
            cout << tokens.at(i) << " is invalid. Returning invalid.\n";
            return "invalid";
        }
    }
    
    cout << "NumOperators: " << numOperators << endl;
    cout << "NumOperands: " << numOperands << endl;
    if (numOperators >= numOperands) {
        return "invalid";
    }
    while (!operator_stack.empty()) {
        postfix.append(operator_stack.top());
        operator_stack.pop();
        if (!operator_stack.empty()) {
            postfix.append(" ");
        }
    }
    cout << "RETURNING " << postfix << endl;
    return postfix;
    
}


bool ExpressionManager :: process_operator(stack<string> &operator_stack, string &postfix, string currentOperator) {
    //if the operator stack is empty OR the top stack is an opening parenthesis OR
    //the current operator is an opening parenthesis 
    //Push the current operator onto the stack
    //return true
    cout << "Process operator function called for " << currentOperator << endl;
    if (operator_stack.empty()) {
        cout << "stack was empty, the operator " << currentOperator <<" was added to the stack" << endl;
        operator_stack.push(currentOperator);
        return true;
    }
    else if (operator_stack.top() == "(" || operator_stack.top() == "{" || operator_stack.top() == "[") {
        operator_stack.push(currentOperator);
        return true;
    }
    else if (currentOperator == ")" || currentOperator == "}" || currentOperator == "]") {
        //while the top of the operator stack is not a matching opening parenthesis
        while (parenthesesMatch( currentOperator, operator_stack.top() )  == false) {
            cout << currentOperator << " and " << operator_stack.top() << " are not matching" << endl;
            //pop off the top of the stack and append it to postfix (with a space after)
            //if operator stack becomes empty without finding a matching parenthesis, return false
            postfix.append( operator_stack.top() );
            postfix.append(" ");
            operator_stack.pop();
            if (operator_stack.empty() == true) {
                return false;
            }
        }
        //pop off the matching opening parenthesis and return true
        operator_stack.pop();
        return true;
    }
    
    //else
    //while the current operator precedence is less than or equal to the stack top precedence, pop stack onto postfix
    //push the current operator
    //return true 
    
    else {
        cout << "This code should be running" << endl;
        if (operator_stack.empty() == true) { // dont do anything
        }
        else {
            while ( getOperatorPrecedence(currentOperator) <= getOperatorPrecedence(operator_stack.top() ) ) {
                cout << "currentOperator "  << currentOperator << " has less than or equal precedence to " << operator_stack.top() << endl;
                postfix.append(operator_stack.top());
                cout << postfix << endl;
                postfix.append(" ");
                operator_stack.pop();
                if (operator_stack.empty() == true) {
                    break;
                }
            }
            operator_stack.push(currentOperator);
            return true;
        }
    }
}

int ExpressionManager :: getOperatorPrecedence(string operatorSymbol) {
    if (operatorSymbol == ")" || operatorSymbol == "}" || operatorSymbol == "]" ) {
        return 2;
    }
    else if (operatorSymbol == "*" || operatorSymbol == "/" || operatorSymbol == "%" ) {
        return 2;
    }
    else if (operatorSymbol == "+" || operatorSymbol == "-") {
        return 1;
    }
    else {
       return 0;
    }
}

bool ExpressionManager :: parenthesesMatch( string closingparen , string couldbeopening ) {
    if (closingparen == ")" && couldbeopening == "(") {
        return true;
    }
    else if (closingparen == "}" && couldbeopening == "{") {
        return true;
    }
    else if (closingparen == "]" && couldbeopening == "[") {
        return true;
    }
    else {
        return false;
    }
}