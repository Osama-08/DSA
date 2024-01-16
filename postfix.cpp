#include <iostream>
using namespace std;

class stack {
public:
    int* arr;
    int top;
    int size;

    stack(int size) {
        this->size = size;
        top = -1;
        arr = new int[size];
    }

    void push(int val) {
        if (top < size - 1) {
            top++;
            arr[top] = val;
        } else {
            cout << "Overflow" << endl;
        }
    }

    void pop() {
        if (top >= 0) {
            top--;
        } else {
            cout << "Underflow" << endl;
        }
    }

    int& getTop() {
        if (top >= 0) {
            return arr[top];
        } else {
            cout << "Underflow" << endl;
            static int dutop = -1;
            return dutop;
        }
    }

    int empty() {
        return top == -1;
    }

    void print() {
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << endl;
        }
    }
};

int prec(char c) {
    if (c == '^') {
        return 3;
    } else if (c == '/' || c == '*') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    }
    return -1;
}

char ass(char c) {
    if (c == '^') {
        return 'R';
    }
    return 'L';
}

void convert_infix_to_Postfix(string s) {
    string res;
    char c;
    stack st(100);

    for (int i = 0; i < s.length(); i++) {
        c = s[i];
        if (isalnum(c)) {
            res += c;
        } else if (c == '(') {
            st.push('(');
        } else if (c == ')') {
            while (st.getTop() != '(') {
                res += st.getTop();
                st.pop();
            }
            st.pop();
        } else {
            while (!st.empty() && (prec(c) < prec(st.getTop()) || (prec(c) == prec(st.getTop()) && ass(c) == 'L'))) {
                res += st.getTop();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        res += st.getTop();
        st.pop();
    }

    cout << res << endl;
}

int main() {
    string exp = "a+b+c";
    convert_infix_to_Postfix(exp);
    return 0;
}
