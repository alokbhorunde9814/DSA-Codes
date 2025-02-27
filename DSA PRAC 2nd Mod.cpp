/*
2.Write a program to implement stack as an abstract data type using linked list and use this ADT
for conversion of infix expression to postfix, prefix and evaluation of postfix/prefix expression.*/
#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

// Node structure for linked list
struct Node {
    char data;
    Node* next;
    Node(char val) : data(val), next(nullptr) {}
};

// Linked list based stack
class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            cerr << "Stack underflow\n";
            exit(1);
        }
        char val = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    char peek() {
        if (isEmpty()) {
            cerr << "Stack is empty\n";
            exit(1);
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// Function to check if a character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return -1;
    }
}

// Function to convert infix expression to postfix
string infixToPostfix(const string& infix) {
    string postfix;
    Stack stack;

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop(); // Pop '('
        } else if (isOperator(ch)) {
            while (!stack.isEmpty() && getPrecedence(ch) <= getPrecedence(stack.peek())) {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }

    return postfix;
}

// Function to convert infix expression to prefix
string infixToPrefix(const string& infix) {
    string prefix;
    Stack stack;

    for (char ch : infix) {
        if (isalnum(ch)) {
            prefix = ch + prefix;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                prefix = stack.pop() + prefix;
            }
            stack.pop(); // Pop '('
        } else if (isOperator(ch)) {
            while (!stack.isEmpty() && getPrecedence(ch) < getPrecedence(stack.peek())) {
                prefix = stack.pop() + prefix;
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        prefix = stack.pop() + prefix;
    }

    return prefix;
}

// Function to evaluate postfix expression
int evaluatePostfix(const string& postfix) {
    Stack stack;

    for (char ch : postfix) {
        if (isdigit(ch)) {
            stack.push(ch - '0');
        } else {
            int operand2 = stack.pop();
            int operand1 = stack.pop();
            switch (ch) {
                case '+': stack.push(operand1 + operand2); break;
                case '-': stack.push(operand1 - operand2); break;
                case '*': stack.push(operand1 * operand2); break;
                case '/': stack.push(operand1 / operand2); break;
                case '^': stack.push(pow(operand1, operand2)); break;
            }
        }
    }

    return stack.pop();
}

// Function to evaluate prefix expression
int evaluatePrefix(const string& prefix) {
    Stack stack;

    for (int i = prefix.size() - 1; i >= 0; --i) {
        char ch = prefix[i];
        if (isdigit(ch)) {
            stack.push(ch - '0');
        } else {
            int operand1 = stack.pop();
            int operand2 = stack.pop();
            switch (ch) {
                case '+': stack.push(operand1 + operand2); break;
                case '-': stack.push(operand1 - operand2); break;
                case '*': stack.push(operand1 * operand2); break;
                case '/': stack.push(operand1 / operand2); break;
                case '^': stack.push(pow(operand1, operand2)); break;
            }
        }
    }

    return stack.pop();
}

int main() {
    char choice;
    cout << "Choose an option:\n";
    cout << "1. Infix to Postfix\n";
    cout << "2. Infix to Prefix\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    cin.ignore();  // Consume newline character

    string expression;
    cout << "Enter expression: ";
    getline(cin, expression);

    switch (choice) {
        case '1': {
            string postfixExpression = infixToPostfix(expression);
            cout << "Postfix expression: " << postfixExpression << endl;
            int result = evaluatePostfix(postfixExpression);
            cout << "Result of postfix expression: " << result << endl;
            break;
        }
        case '2': {
            string prefixExpression = infixToPrefix(expression);
            cout << "Prefix expression: " << prefixExpression << endl;
            int result = evaluatePrefix(prefixExpression);
            cout << "Result of prefix expression: " << result << endl;
            break;
        }
        default:
            cout << "Invalid choice\n";
            break;
    }

    return 0;
}
