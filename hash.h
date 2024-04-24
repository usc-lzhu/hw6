#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int index = 4;
        int end = k.length();
        int start;

        unsigned long long w[5] = {0};
        unsigned long long result = 0;
        unsigned long long subkeyResult = 0;

        while (end >= 0) {
            if (end - 6 >= 0) {
                start = end - 6;
            }
            else {
                start = 0;
            }

            for (int i = start; i < end; ++i) {
                subkeyResult = subkeyResult * 36 + letterDigitToNumber(k[i]);
            }

            w[index] = subkeyResult;
            --index;
            subkeyResult = 0;
            end = end - 6;
        }


        for (int i = 0; i < 5; ++i) {
            // std::cout << "w[" << i << "] = " << w[i] << std::endl;
            result += rValues[i] * w[i];
        }

        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z') {
            return (letter - 'a');
        }
        else if (letter >= 'A' && letter <= 'Z') {
            return (letter - 'A');
        }
        else {
            return (letter - '0' + 26);
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
