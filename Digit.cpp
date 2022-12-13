// Digit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/// <summary>
/// provided function
std::vector<int> string_to_digits(std::string s) {
    std::vector<int> out;

    for (int i = 0; i < s.size(); i++) {

        std::string digit_string;
        digit_string.push_back(s[i]);

        int digit_int = std::stoi(digit_string);

        out.push_back(digit_int);
    }

    return out;

}
/// </summary>

bool checkAboutCanPlay(std::string roundText, std::string valueforCheck) {
    if (roundText == "709" && valueforCheck == "70")
        int a = 3;
    std::string tempRoundText = roundText;
    std::string tempValueForCheck = valueforCheck;
    for (int i = 0; i < tempValueForCheck.length(); i++) {
        int index = tempRoundText.find(tempValueForCheck.at(i));
        if (index == string::npos)
            return false;
        else
            tempRoundText=tempRoundText.erase(index,1);
    }
    return true;
}
int getSubRoundScore(std::vector<int> round, std::vector<int> value, std::vector<int> perscore) {
    int score = 0;
    for (int i = 0; i < value.size();) {
        ///check for subsequence
        int subSeqSize = 1;
        int tempIndex = i;
        do {
            if (tempIndex + 1 < value.size() && (value.at(tempIndex)) == (value.at(tempIndex + 1))-1)
                subSeqSize++, tempIndex++;
            else break;
        } while (1);
        for (int j = 0; j < subSeqSize; j++)
            score += perscore.at(value.at(i + j)) * subSeqSize;
        i += subSeqSize;
    }
    return score;
}
int main()
{
    fstream newfile;  ///using for read files
    std::vector<std::string> allowed;
    std::vector<int> values;
    std::vector<std::string> rounds;
    //read from allowed.txt
    newfile.open("allowed.txt", ios::in);
    if (newfile.is_open()) {
        string tp;
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            allowed.push_back(tp);
        }
        newfile.close();     
    }
    //read from allowed.txt


    //read from values.txt
    newfile.open("values.txt", ios::in);
    if (newfile.is_open()) {
        string tp;
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            values.push_back(std::atoi(tp.c_str()));
        }
        newfile.close();
    }
    //read from values.txt
    
    //read from rounds.txt
    newfile.open("rounds.txt", ios::in);
    if (newfile.is_open()) {
        string tp;
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            rounds.push_back(tp);
        }
        newfile.close();
    }
    //read from rounds.txt

    /// <gameLogic>
    newfile.open("output.txt", ios::out);
    if (!newfile.is_open()) {
        std::cout << "can not write to file";
        return 0;
    }
    for (int i = 0; i < rounds.size(); i++) {
        std::string maxString="";
        int maxValue;
        bool maxselected = false;
        for (int j = 0; j < allowed.size(); j++) {
            if (checkAboutCanPlay(rounds.at(i), allowed.at(j))) {
                int score = getSubRoundScore(string_to_digits(rounds.at(i)), string_to_digits(allowed.at(j)), values);
                if (!maxselected || score > maxValue) {
                    maxValue = score;
                    maxString = allowed.at(j);
                    maxselected = true;
                }
            }
        }
        newfile << rounds.at(i) <<" ";
        newfile << maxString << " ";
        newfile << maxValue << " ";
        newfile << "\n";
    }
    newfile.close();
    /// </gameLogic>
}
