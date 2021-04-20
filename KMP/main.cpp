//
//  main.cpp
//  KMP
//
//  Created by anmin on 19.04.2021.
//

#include <iostream>
#include <algorithm>
#include <ctime>
#include <unistd.h>
#include <random>
#include <string>

using namespace std;
  
void KMP(string X, string Y)
{
    int m = X.length();
    int n = Y.length();
    int stepCount = 0;
    // if `Y` is an empty string
    if (n == 0)
    {
        cout << "The pattern occurs with shift 0";
        return;
    }
 
    // if X's length is less than that of Y's
    if (m < n)
    {
        cout << "Pattern not found";
        return;
    }
 
    // `next[i]` stores the index of the next best partial match
    int next[n + 1];
 
    for (int i = 0; i < n + 1; i++) {
        stepCount++;
        next[i] = 0;
    }
 
    for (int i = 1; i < n; i++)
    {
        stepCount++;
        int j = next[i + 1];
 
        while (j > 0 && Y[j] != Y[i]) {
            j = next[j];
        }
 
        if (j > 0 || Y[j] == Y[i]) {
            next[i + 1] = j + 1;
        }
    }
 
    for (int i = 0, j = 0; i < m; i++)
    {
        if (X[i] == Y[j])
        {
            if (++j == n) {
                cout << "The pattern occurs with shift " << i - j + 1 << endl;
            }
        }
        else if (j > 0)
        {
            j = next[j];
            stepCount++;
            i--;    // since `i` will be incremented in the next iteration
        }
    }
    cout << "Step is  " << stepCount << endl;
}

string generate(int max_length){
    string possible_characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<> dist(0, possible_characters.size()-1);
    string ret = "";
    for(int i = 0; i < max_length; i++){
        int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
        ret += possible_characters[random_index];
    }
    return ret;
}

int main() {
    srand(time(0));
    int rundom = rand() % 100;
        string test = generate(rundom);
    int one = (rand() % rundom) + 1;
    int two = (rand() % 10) + 1;
    int min = one;
    int max = one + two;
        string subString = test.substr(min,max);
    
    std::cout << test << " string \n";
    std::cout << test.length() << " string length \n";
    std::cout << subString << " substring \n";
    std::cout << subString.length() << " substring length \n";
    
    auto start = std::chrono::system_clock::now();
        KMP(test, subString);
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    std::cout << elapsed.count() << " time" << '\n';
    
    return 0;
}
