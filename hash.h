#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;
//typedef std::unsigned long long HASH_INDEX_T;

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
        unsigned long long w[5]={0,0,0,0,0};
        int j=4;
        int l=k.length();
        while(l>0){
            size_t start=std::max(0,l-6);
            size_t len=std::min((size_t)6,l-start);
            unsigned long long result=0;
            unsigned long long multiplier = pow(36,len-1);
            for(size_t i=start; i<start+len; i++){
                HASH_INDEX_T temp=letterDigitToNumber(k[i]);
                result+=temp*multiplier;
                multiplier/=36;
            }
            w[j]=result;
            l=start; j--;
        }
        HASH_INDEX_T ans=0;
        ans=(rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4]);
        return ans;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter>='A'&&letter<='Z'){
            letter='a'+(letter-'A');
        }
        HASH_INDEX_T result;
        if(letter>='0'&&letter<='9'){
            result=letter-'0'+26;
        }else{
            result=letter-'a';
        }
        return result;
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
