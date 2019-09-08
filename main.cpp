#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>

using namespace std;


// A function to check elements in vector is same or not
bool CheckSame(vector<int> vectorCode)
{
    bool isSame = false;
    for(int i = 0; i < vectorCode.size(); ++i)
    {
        int j = i + 1;
        while (j < vectorCode.size())
        {
            if (vectorCode.at(i) == vectorCode.at(j))
            {
                isSame = true;
                break;
            }
            ++j;
        }
    }
    return isSame;
}


// A function to put every single integer in code to a vector
vector<int> GetVector(int fCode, int fNumDigit)
{
    //number of digits in the code from the user
    int numCodeDigit = 0;

    vector<int> fCodeVal(0);

    //determine how many digits in a number
    if (fCode / 10000 > 0)
    {
        numCodeDigit = 5;
    }
    else
    {
        if (fCode / 1000 > 0)
        {
            numCodeDigit = 4;
        }
        else
        {
            if (fCode / 100 > 0)
            {
                numCodeDigit = 3;
            }
            else
            {
                if (fCode / 10 > 0)
                {
                    numCodeDigit = 2;
                }
                else
                {
                    numCodeDigit = 1;
                }
            }
        }
    }

    //determine how many 0s need to put in the code from user
    if (fNumDigit > numCodeDigit)
    {
        for (int i = 1; i <= (fNumDigit - numCodeDigit); ++i)
        {
            fCodeVal.push_back(0);
        }
    }

    //put every single integer to codeVal
    for (int i = numCodeDigit; i > 0; --i)
    {
        int powNum = pow(10,i - 1);
        fCodeVal.push_back(fCode / powNum);
        fCode = fCode % powNum;
    }
    return fCodeVal;
}


// A function to print out every element in a vector
void PrintNumInCode(vector<int> vectorCode)
{
    for (int i = 0; i < vectorCode.size() - 1; ++i)
    {
        cout << vectorCode.at(i) << "-";
    }
    cout << vectorCode.at(vectorCode.size() - 1) << endl;
}


// A function to get elements in a vector to guess
vector<int> GetGuessVector(int digit)
{
    vector<int> guessVector;
    int guessNum = 0;
    bool isSame = false;
    cout << "Enter Guess: ";
    cin >> guessNum;
    guessVector = GetVector(guessNum, digit);
    isSame = CheckSame(guessVector);
    while(isSame == true || guessNum > pow(10, digit))
    {
        if (guessNum > pow(10, digit))
        {
            cout << "You can only enter " << digit << " digits." << endl;
            cout << "Enter Guess: ";
            cin >> guessNum;
            guessVector = GetVector(guessNum, digit);
            isSame = CheckSame(guessVector);
        }
        else
        {
            cout << "Each number must be different." << endl;
            cout << "Enter Guess: ";
            cin >> guessNum;
            guessVector = GetVector(guessNum, digit);
            isSame = CheckSame(guessVector);
        }
    }
    return guessVector;
}


// A function to compare original code and a code user guessed
// location and element both same: bull; only element same: cow
int CompVector(vector<int> fCodeVal, vector<int> guessVector)
{
    int sumBull = 0;
    int sumCow = 0;
    for(int i = 0; i < fCodeVal.size(); ++i)
    {
        if(fCodeVal.at(i) == guessVector.at(i))
        {
            sumBull += 1;
        }
        else
        {
            for(int j = 0; j < fCodeVal.size(); ++j)
            {
                if(fCodeVal.at(i) == guessVector.at(j))
                {
                    sumCow += 1;
                }
            }
        }
    }
    if(sumBull != fCodeVal.size())
    {
        cout << sumBull << " bulls" << endl;
        cout << sumCow << " cows" << endl;
    }
    else
    {
        cout << sumBull << " bulls... ";
    }
    return sumBull;
}


int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>
                  (std::chrono::system_clock::now().time_since_epoch()).count()%2000000000);
    // needed to autograde some test cases in Mimir

    //number of digits in code
    int numDigit = 0;

    //code get from user
    int code = 0;

    //total bulls
    int sumOfBull = 0;

    //vector named codeVal to store every number in original code
    vector<int> codeVal(0);

    //vector named guessVal to store every number in code the user guessed
    vector<int> guessVal(0);

    //a number to control the rang of random number
    int controlRand = 0;

    //control integers in code is same or not
    bool isSame = false;


    cout << "Enter number of digits in code (3, 4 or 5): ";
    cin >> numDigit;

    //repeat until a valid number is entered
    while (numDigit != 0 && numDigit != 3 && numDigit != 4 && numDigit != 5)
    {
        cout << "Enter number of digits in code: ";
        cin >> numDigit;
    }

        do{
            //0 is a cheat code, ask user to enter code
            if (numDigit == 0)
            {
                cout << "Enter code: ";
                cin >> code;
                cout << "Enter number of digits in code: ";
                cin >> numDigit;
                while (numDigit != 0 && numDigit != 3 && numDigit != 4 && numDigit != 5) {
                    cout << "Enter number of digits in code: ";
                    cin >> numDigit;
                }
            }
            else
            {
                controlRand = pow(10, numDigit);
                code = rand() % controlRand;      //random number from 0 to (10^numDigit) - 1
            }

            codeVal = GetVector(code, numDigit);
            isSame = CheckSame(codeVal);

        } while(isSame == true); // repeat if there are digits are same

    cout << "Number to guess: ";
    PrintNumInCode(codeVal);

    //repeat until original code and code user guessed are same
    while(sumOfBull != numDigit)
    {
        guessVal = GetGuessVector(numDigit);
        sumOfBull = CompVector(codeVal, guessVal);
    }

    //print the code user guessed is correct!
    for (int i = 0; i < guessVal.size() - 1; ++i)
    {
        cout << guessVal.at(i) << "-";
    }
    cout << guessVal.at(guessVal.size() - 1) << " is correct!" << endl;
    return 0;
}