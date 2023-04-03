#include <iostream>
#include <stack>
#include <string>

using namespace std;

class RpN {
private:
    stack<double> my_stack;

public:
    double calc(string input) {
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == ' ') continue;
            if (isdigit(input[i])) {
                string num_str;
                while (i < input.length() && (isdigit(input[i]) || input[i] == '.')) {
                    num_str += input[i];
                    i++;
                }
                double num = stod(num_str);
                my_stack.push(num);
                i--;
            }
            else {
                double op2 = my_stack.top();
                my_stack.pop();
                double op1 = my_stack.top();
                my_stack.pop();
                switch (input[i]) {
                case '+':
                    my_stack.push(op1 + op2);
                    break;
                case '-':
                    my_stack.push(op1 - op2);
                    break;
                case '*':
                    my_stack.push(op1 * op2);
                    break;
                case '/':
                    my_stack.push(op1 / op2);
                    break;
                }
            }
        }
        return my_stack.top();
    }

    string toReversePolish(string input) {
        string output = "";
        stack<char> my_stack_char;
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == ' ') continue;
            if (isdigit(input[i])) {
                while (i < input.length() && (isdigit(input[i]) || input[i] == '.')) {
                    output += input[i];
                    i++;
                }
                output += ' ';
                i--;
            }
            else if (input[i] == '(') {
                my_stack_char.push(input[i]);
            }
            else if (input[i] == ')') {
                while (!my_stack_char.empty() && my_stack_char.top() != '(') {
                    output += my_stack_char.top();
                    output += ' ';
                    my_stack_char.pop();
                }
                my_stack_char.pop();
            }
            else {
                while (!my_stack_char.empty() && precedence(my_stack_char.top()) >= precedence(input[i])) {
                    output += my_stack_char.top();
                    output += ' ';
                    my_stack_char.pop();
                }
                my_stack_char.push(input[i]);
            }
        }
        while (!my_stack_char.empty()) {
            output += my_stack_char.top();
            output += ' ';
            my_stack_char.pop();
        }
        return output;
    }

private:
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
};

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    RpN rpn;
    string rpn_str = rpn.toReversePolish(input);
    cout << "Reverse Polish Notation: " << rpn_str << endl;

    double result = rpn.calc(rpn_str);
    cout << "Result: " << result << endl;

    return 0;
}

