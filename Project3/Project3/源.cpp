#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

vector<char> saveF(const string& function) {
    vector<char> charList;
    for (char c : function) {
        charList.push_back(c);
    }
    return charList;
}

void getcoef(const vector<char>& charList, vector<int>& L) {
    char sign = '+';
    int index = 0;
    int maxIndex = 0;
    for (char c : charList) {
        if (c == '-') {
            sign = '-';
            if (charList[index + 1] != 'x') {
                L[0] = -1;
                return;
            }
        }
        else if (c == '+') {
            sign = '+';
            if (charList[index + 1] != 'x') {
                L[0] = 1;
                return;
            }
        }
        else if (c == 'x') {
            if (charList[index + 1] != '^') {
                L[1] = (sign == '-') ? -1 : 1;
            }
        }

        else if (isdigit(c)) {
            int num = c - '0';
            while (isdigit(charList[index + 1])) {
                num = num * 10 + (charList[index + 1] - '0');
                index++;
            }
            maxIndex = max(maxIndex, num);
            if (index >= L.size()) {
                L.resize(maxIndex + 1, 0);
            }
            L[num] = (sign == '-') ? -1 : 1;
        }
        index++;
    }
}
void reverseList(vector<int>& L) {
    int left = 0;
    int right = L.size() - 1;
    while (left < right) {
        int temp = L[left];
        L[left] = L[right];
        L[right] = temp;
        left++;
        right--;
    }
}

void addZeros(vector<int>& L1, vector<int>& L2) {
    int size = L1.size();
    int zeros = L2.size() - 1;
    L1.resize(size + zeros);
    for (int i = size - 1; i >= 0; --i) {
        L1[i + zeros] = L1[i];
    }
    for (int i = 0; i < zeros; i++) {
        L1[i] = 0;
    }
}

int isSameSign(int I1, int I2) {
    if (I1 * I2 == 1)
        return 1;
    else
        return 0;
}

void listNegate(vector<int>& L) {
    for (int& num : L) {
        if (num == 1) {
            num = -1;
        }
        else if (num == -1) {
            num = 1;
        }
    }
}

int operations(int a, int b) {
    if (a == 1 && b == 1) {
        return 0;
    }
    else if (a == 1 && b == 0) {
        return 1;
    }
    else if (a == 1 && b == -1) {
        return -1;
    }
    else if (a == 0 && b == 1) {
        return -1;
    }
    else if (a == 0 && b == 0) {
        return 0;
    }
    else if (a == 0 && b == -1) {
        return 1;
    }
    else if (a == -1 && b == 1) {
        return 1;
    }
    else if (a == -1 && b == 0) {
        return -1;
    }
    else if (a == -1 && b == -1) {
        return 0;
    }
}
void changeSign(vector<int>& L, int zeros) {
    for (int i = 0; i < zeros; ++i) {
        if (L[i] != 0) {
            L[i] = -L[i];
        }
    }
}
void getcrc(vector<int>& L1, vector<int>& L2) {
    int index1 = L1.size() - 1;
    int index2 = L2.size() - 1;
    int manyzeros = 0;
    int difference = index1 - index2;
    cout << "defference is " << difference << endl;
    //difference = difference * 2 + 1;
    for (int a = 1; a <= difference + 1; a++) {
        if (L1[index1] == 0) {
            cout << "a = " << a << endl;
            if (manyzeros == 0)
                a--;
            index1--;
            manyzeros = 1;
            cout << "the top is 0;" << endl;
        }

        else if (isSameSign(L1[index1], L2[index2])) {
            cout << "a = " << a << endl;
            cout << "there is the same sign" << endl;
            for (int i = 0; i <= index2; i++) {
                cout << "L1[" << index1 - i << "] = " << L1[index1 - i] << ", and L2[" << index2 - i << "] = " << L2[index2 - i] << endl;
                L1[index1 - i] = operations(L1[index1 - i], L2[index2 - i]);
                cout << "New L1[" << index1 - i << "] = " << L1[index1 - i] << endl;
            }
            manyzeros = 0;
        }
        else {
            cout << "a = " << a << endl;
            cout << "there need to change the sign" << endl;
            listNegate(L2);
            for (int i = 0; i <= index2; i++) {
                cout << "L1[" << index1 - i << "] = " << L1[index1 - i] << ", and L2[" << index2 - i << "] = " << L2[index2 - i] << endl;
                L1[index1 - i] = operations(L1[index1 - i], L2[index2 - i]);
                cout << "New L1[" << index1 - i << "] = " << L1[index1 - i] << endl;
            }
            manyzeros = 0;
        }
    }
    changeSign(L1, difference);
}

int main() {
    cout << "Input L1: ";
    vector<int> L1;
    string input;
    cout << "Enter a list of numbers separated by spaces:" << endl;
    getline(cin, input);

    stringstream ss(input);
    int num;
    while (ss >> num) {
        L1.push_back(num);
    }
    string inputL2;
    cout << "Input L2: ";
    cin >> inputL2;
    //string inputL2 = "x^6-x^4+x^2+x-1";
    vector<char> charList = saveF(inputL2);
    vector<int> L2;
    getcoef(charList, L2);
    reverseList(L1);
    cout << "L1 list: ";
    cout << "L1.size = " << L1.size() << endl;
    for (int i = L1.size() - 1; i >= 0; --i) {
        cout << L1[i] << " ";
    }
    cout << endl;
    cout << "L2 list: ";
    cout << "L2.size = " << L2.size() << endl;
    for (int i = L2.size() - 1; i >= 0; --i) {
        cout << L2[i] << " ";
    }
    addZeros(L1, L2);
    cout << "Step1: +0 " << endl;
    cout << "L1 list: ";
    cout << "L1.size = " << L1.size() << endl;
    for (int i = L1.size() - 1; i >= 0; --i) {
        cout << L1[i] << " ";
    }
    cout << endl;
    cout << "Step1: getcrc " << endl;
    getcrc(L1, L2);
    cout << "L1 list: ";
    cout << "L1.size = " << L1.size() << endl;
    for (int i = L1.size() - 1; i >= 0; --i) {
        cout << L1[i] << " ";
    }
    return 0;
}
