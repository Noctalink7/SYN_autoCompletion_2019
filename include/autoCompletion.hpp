/*
** EPITECH PROJECT, 2020
** autoCompletion
** File description:
** hpp
*/

#ifndef AUTOCOMPLETION_HPP
#define AUTOCOMPLETION_HPP

#include "address.hpp"
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>

class AutoComp {
public:
    AutoComp();
    ~AutoComp() = default;
    Address* Parser(std::string address);
    int ProcessFile(std::string filename);
    bool searchCity(std::string input);
    bool searchStreet(std::string input);
    bool fivemost(int i);
    void fivemostAddr();
    std::vector<std::string> getupCity();
    std::vector<std::string> VecUpper(std::vector<std::string> vec);
    std::vector<Address> getList();
    void ResetChecker();
    bool getCheck();
private:
    long GetFileSize(std::string filename);
    std::vector<std::string> split(std::string str);
    bool checkCity(std::vector<Address>::iterator it);
    bool checkStreet(std::vector<Address>::iterator it);
    std::string toLower(std::string str);
    std::string toUpper(std::string str);
    std::string printVec(std::vector<std::string> vec);
    bool checkProp;
    std::vector<Address> list;
    std::string checker;
    std::string next;
    std::map<char, int> prop;
    std::vector<std::string> upCity;
    std::vector<std::string> upName;
};

#endif
