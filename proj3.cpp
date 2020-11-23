//Elizabeth Stevenson
//CSCE350 Project 3

#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::max;
using namespace std;

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
    return (n%10);
}

//reverse method bc i was having trouble figuring out
//what was wrong and maybe reversing values is a good idea
vector<int> reverse(vector<int> vector) {
    vector<int> reversed;
    int place;
    for (int i = 0; i < vector.size(); ++i) {
        place = vector.size()-1-i;
        reversed.push_back(vector.at(place));
    }
    return reversed;
}

vector <int> BalanceWithZeros(vector<int> vector1, vector<int> vector2) {
    int zeros = 0;
    zeros = vector1.size() - vector2.size();
    for (int i = 0; i < zeros; ++i) {
        vector2.insert(vector2.begin(), 0);
    }
    return vector2;
}


vector<int> UnbalanceZeros(vector<int> number) {
    string s;
    string temp = "";

    if(number.at(0) == 0 && equal(number.begin()+1, number.end(), number.begin())) {
        number.clear();
        number.push_back(0);
        return number;
    } else {
        for (unsigned int i = 0; i < number.size(); ++i) {
            s += to_string(number.at(i));
        }
        s.erase(0, s.find_first_not_of('0'));
        number.clear();
        for (unsigned int i = 0; i < s.size(); ++i) {
            number.push_back(stoi(temp = s[i]));
        }
        return number;
    }
}


vector<int> VectorAddition(vector<int> vector1, vector<int> vector2) {
    vector<int> finalAnswer;
    vector<int> carryOver;
    int sum;
    int temp1;
    int temp2;
    int temp3;

    if (vector2.size() < vector1.size()) {
        vector2 = BalanceWithZeros(vector1, vector2);
    }
    else if (vector2.size() > vector1.size()) {
        vector1 = BalanceWithZeros(vector2, vector1);
    }

    //reverse(vector1.begin(), vector1.end());
    //reverse(vector2.begin(), vector2.end());
    reverse(vector1);
    reverse(vector2);

    for (unsigned int i = 0; i < vector1.size(); ++i) {
        sum = vector1.at(i) + vector2.at(i);
        if (i > 0) {
            sum += carryOver.at(i-1);
        }
        temp1 = sum;
        temp2 = 0;
        temp3 = sum;
        if (sum > 9) {
            //get first digit
            temp2 = findFirstDigit(temp1);
            sum = findLastDigit(temp3);
        }
        carryOver.push_back(temp2);
        finalAnswer.push_back(sum);
    }
    finalAnswer.push_back(temp2);
    //reverse(finalAnswer.begin(), finalAnswer.end());
    reverse(finalAnswer);
/* Print statement that would not print anything
    cout << "1 ";
    printIntVector(finalAnswer); */

    return finalAnswer;
}

vector<int> bruteForce(vector<int> num1, vector<int> num2) {
    vector<int> s;
    vector<int> carryOver;
    vector<vector<int>> addition;

    int amount;
    int temp1;
    int temp2;
    int temp3;

    //reverse(num1.begin(), num1.end());
    //reverse(num2.begin(), num2.end());
    reverse(num1);
    reverse(num2);

    for(unsigned int i = 0; i < num2.size(); ++i) {
        for(unsigned int j = 0; j < num1.size(); ++j) {
            if(num2.at(i) == 0 && num1.at(j) == 0) {
                amount = 0;
            }
            else {
                amount = num2.at(i)*num1.at(j);
            }
            if (j > 0) {
                amount += carryOver.at(j-1);
            }
            temp1 = amount;
            temp2 = 0;
            temp3 = amount;
            if (amount > 9) {
                //get first digit
                temp2 = findFirstDigit(temp1);
                amount = findLastDigit(temp3);
            }
            s.push_back(amount);
            carryOver.push_back(temp2);
        }
        s.push_back(temp2);
        //reverse(s.begin(), s.end());
        reverse(s);
        for (unsigned int k = 0; k < i; ++k) {
            s.push_back(0);
        }
        addition.push_back(s);
        carryOver.clear();
        s.clear();
    }
    for(unsigned int i = 1; i < s.size(); ++i) {
        addition.at(0) = VectorAddition(addition.at(0), addition.at(i));
    }
    vector<int> finalAnswer;
    for(unsigned int i = 0; i < addition.at(0).size(); ++i) {
        finalAnswer.push_back(addition.at(0).at(i));
    }
    return finalAnswer;
}

vector<int> VectorSubtract(vector<int> vector1, vector<int> vector2) {
    vector<int> finalAnswer;
    vector<int> temp;
    
    //okay maybe my issue is with the balancing 0s
    vector1 = UnbalanceZeros(vector1);
    vector2 = UnbalanceZeros(vector2);

    if ((vector1.at(0) == 0) && (vector2.at(0) == 0) && (vector1.size() == 1) && (vector2.size() == 1)) {
        return vector1;
    }

    if ((vector1.size()==vector2.size() && (vector1.at(0) < vector2.at(0))) || vector1.size() < vector2.size()) {
        for (unsigned int i = 0; i < vector1.size(); i++) {
            temp.push_back(vector1.at(i));
        }
        vector1.clear();
        for (unsigned int i = 0; i < vector2.size(); ++i) {
            vector1.push_back(vector2.at(i));
        }
        vector2.clear();
        for (unsigned int i = 0; i < temp.size(); ++i) {
            vector2.push_back(temp.at(i));
        }
        temp.clear();
    }

    //making both number vectors be same length
    if (vector2.size() < vector1.size()) {
        vector2 = BalanceWithZeros(vector1, vector2);
    }
    else if (vector2.size() > vector1.size()) {
        vector1 = BalanceWithZeros(vector2, vector1);
    }

    //reverse(vector1.begin(), vector1.end());
    //reverse(vector2.begin(), vector2.end());
    reverse(vector1);
    reverse(vector2);
/*
    //if 2 vectors are the same, returns 0
    if(vector1 == vector2) {
        vector<int> zeroVector;
        zeroVector.push_back(0);
        return zeroVector;
    }
*/

    for (unsigned int i = 0; i < vector1.size(); ++i) {
        if (vector1.at(i) < vector2.at(i)) {
            vector1.at(i+1) = vector1.at(i+1) - 1;
            vector1.at(i) = vector1.at(i) + 10;
        }
        finalAnswer.push_back(abs(vector1.at(i) - vector2.at(i)));
    }

/* I tried using these print statements but it was not printing for some weird reason
    cout << "2 ";
    printIntVector(finalAnswer);
*/
    //reverse(finalAnswer.begin(), finalAnswer.end());
    reverse(finalAnswer);
    return finalAnswer;
}

vector<int> toTheTenth(vector<int> vector, int num1, int num2) {
    for (int i = 0; i < (num1*num2); ++i) {
        vector.push_back(0);
    }
    return vector;
}

vector<int> karatsuba(vector<int> num1, vector<int> num2) {
    vector<int> a0; //last m digits in a
    vector<int> a1; //remaining digits in a
    vector<int> b0; //last m digits in b
    vector<int> b1; //remaining digits in b
    vector<int> c2; //karatsuba(a1, b1)
    vector<int> c0; //karatsuba(a0, b0)
    vector<int> c1; //karatsuba(a1+a0, b1+b0)-c2-c0
    vector<int> special;

    if (num1.size() < 10 && num2.size() < 10) {
        return bruteForce(num1, num2);
    }
    else {
        unsigned int m = floor((max(num1.size(), num2.size()))/2);

        //making both number vectors be same length
        if (num2.size() < num1.size()) {
            num2 = BalanceWithZeros(num1, num2);
        }
        else if (num2.size() > num1.size()) {
            num1 = BalanceWithZeros(num2, num1);
        }

        //setting up a0 and a1 with num1
        for (unsigned int i = 0; i < num1.size(); ++i) {
            if(num1.size()%2 == 0) {
                if (i >= m) {
                    a0.push_back(num1.at(i));
                }
                else {
                    a1.push_back(num1.at(i));
                }
            }
            else {
                if (i > m) {
                    a0.push_back(num1.at(i));
                }
                else {
                    a1.push_back(num1.at(i));
                }
            }
        }

/* Same thing here, cout and printIntVector did not print
        cout << "a0 ";
        printIntVector(a0);

        cout << "a1 ";
        printIntVector(a1); */

        //setting up b0 and b1 with num2
        for (unsigned int i = 0; i < num2.size(); ++i) {
            if (num1.size()%2 == 0) { //num2.size()
                if (i >= m) {
                    b0.push_back(num2.at(i));
                }
                else {
                    b1.push_back(num2.at(i));
                }
            }
            else {
                if (i > m) {
                    b0.push_back(num2.at(i));
                }
                else {
                    b1.push_back(num2.at(i));
                }
            }
        }

/*
        cout << "b0 ";
        printIntVector(b0);
        cout << "b1 ";
        printIntVector(b1); */

        c2 = karatsuba(a1, b1);
        c0 = karatsuba(a0, b0);
        //a1+a0, b1+b0
        special = karatsuba(VectorAddition(a1, a0), VectorAddition(b1, b0));
        // -c2-c0
        c1 = VectorSubtract(special, VectorSubtract(c2, c0));
        //return 10^2m * c2 + 10^m *c1 + c0
        toTheTenth(c2, 2, m);
        toTheTenth(c1, 1, m);
        return VectorAddition(VectorAddition(c2,c1),c0);
    }
    
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
    
    /* printIntVector(number1);
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
