//Elizabeth Stevenson
//CSCE350 Project 3

#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

vector<int> number1;
vector<int> number2;
vector<int> bruteForceVector;
vector<int> karatsubaVector;

int charToInt(char character) {
    return ((int)character) - 48;
}

//int vector printer
void printIntVector(vector<int> s) {
    for (unsigned int i = 0; i < s.size(); i++) {
        cout << s.at(i);
    }
}

int findFirstDigit(int n) {
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int findLastDigit(int n) {
    return n%10;
}

vector<int> AdditionTime(vector<int> vector1, vector<int> vector2) {

}

void bruteForce(vector<int> num1, vector<int> num2) {
    vector<int> s;
    vector<int> carryOver;
    vector<vector<int>> addition;

    int product;
    int temp1;
    int temp2;
    int temp3;

    for(int i = 0; i < num2.size(); ++i) {
        for(int j = 0; j < num1.size(); ++j) {
            if(num2.at(i) == 0 && num1.at(j) == 0) {
                product = 0;
            }
            else {
                product = num2.at(i)*num1.a(j);
            }
            if (j > 0) {
                product += carryOver.at(j-1);
            }
            temp1 = product;
            temp2 = 0;
            temp3 = product;
            if (product > 9) {
                //get first digit
                temp2 = findFirstDigit(temp1);
                product = findLastDigit(temp3);
            }
            s.push_back(product);
            carryOver.push_back(temp2);
        }
        s.push_back(temp2);
        for (int k = 0; k < i; ++k) {
            s.push_back(0);
        }
        addition.push_back(s);
        s.clear();
        carryOver.clear();
    }
    for(int i = 1; i < s.size(); ++i) {
        s.at(0) = AdditionTime(s.at(0), s.at(i));
    }
    vector<int> finalAnswer;
    for(int i = 0; i < s.at(0).size(); ++i) {
        finalAnswer.push_back(s.at(0).at(i));
    }
    return finalAnswer;
}

void karatsuba(vector<int> num1, vector<int> num2) {

    
}

int main(int argc, char* argv[]) {
    string input;
    cin >> input;
    int index;
    int length = input.length();
    char character;

    for (index = 0; index < length; ++index) {
        character = input.at(index);
        if (character == '*') {
            break;
        }
        number1.push_back(charToInt(character));
    }
    
    for (++index; index < length; ++index) {
        character = input.at(index);
        number2.push_back(charToInt(character));
    }
    
/*     printIntVector(number1);
    cout << " ";
    printIntVector(number2); */

    bruteForceVector = bruteForce(number1, number2);
    cout << "** Brute Force: ";
    printIntVector(bruteForceVector);

    cout << endl;

    karatsubaVector = karatsuba(number1, number2);
    cout << "** Karatsuba: ";
    printIntVector(karatsubaVector);

    if (!cin.good()) {
        return 0;
    }
}