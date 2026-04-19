// Copyright 2026 NNTU-CS

#include <string>
#include <cctype>
#include <stdexcept>
#include "../include/tstack.h"

int getPriority(char op) {
    switch (op) {
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
    default: return 0;
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;
    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.is_empty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.is_empty()) {
                stack.pop();
            }
        } else if (isOperator(c)) {
            while (!stack.is_empty() && stack.top() != '(' && 
                   getPriority(stack.top()) >= getPriority(c)) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(c);
        }
    }
    while (!stack.is_empty()) {
        result += stack.pop();
        result += ' ';
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < pref.length(); i++) {
        char c = pref[i];

        if (isdigit(c)) {
            int num = 0;
            while (i < pref.length() && isdigit(pref[i])) {
                num = num * 10 + (pref[i] - '0');
                i++;
            }
            stack.push(num);
            i--;
        } else if (isOperator(c)) {
            int b = stack.pop();
            int a = stack.pop();
            int result = 0;

            switch (c) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = a / b; break;
            }
            stack.push(result);
        }
    }

    return stack.pop();
}
