#pragma once

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <string>

class RPN { 
    
    public:
        RPN();
        ~RPN();
        RPN(RPN const & src);
        RPN & operator=(RPN const & rhs);
        bool isOperator(char c);
        int applyOperator(char op, int a, int b);
        int evaluate(const std::string& expression);

    private:
        std::stack<int> _nbr;
        std::stack<char> _op;
};