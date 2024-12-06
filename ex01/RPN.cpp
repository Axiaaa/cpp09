#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(RPN const & src) {
    *this = src;
}

RPN & RPN::operator=(RPN const & rhs) {
    if (this != &rhs) {
        this->_nbr = rhs._nbr;
        this->_op = rhs._op;
    }
    return *this;
}

bool RPN::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::applyOperator(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) 
                throw std::runtime_error("Error: Division by zero");
            return a / b;
        default:
            throw std::runtime_error("Error: Invalid operator");
    }
}

int RPN::evaluate(const std::string& expression) {
    std::stack<int> stack;
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (token.size() == 1 && isdigit(token[0])) {
            int number = token[0] - '0';
            stack.push(number);
        } else if (isOperator(token[0]) && token.size() == 1) {
            if (stack.size() < 2)
                throw std::runtime_error("Error: Not enough operands");
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int result = applyOperator(token[0], a, b);
            stack.push(result);
        } else {
            throw std::runtime_error("Error: Invalid token in expression");
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("Error: Invalid RPN expression");

    return stack.top();
}