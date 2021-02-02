/*
** EPITECH PROJECT, 2020
** autoCompletion
** File description:
** adresse
*/

#ifndef _ADRESS_HPP
#define _ADRESS_HPP

#include <string>
#include <vector>

enum streetType {
    ALLEE,
    AVENUE,
    BOULEVARD,
    CHEMIN,
    IMPASSE,
    PLACE,
    QUAI,
    RUE,
    SQUARE
};

class Address {
public:
    Address(std::vector<std::string> city, int streetNumber,    \
            std::string streetType, std::vector<std::string> streetName, std::string addr);
    ~Address() = default;
    std::vector<std::string> getCity();
    int getNumber();
    std::string getType();
    std::vector<std::string> getName();
    std::string getAddr();
private:
    std::vector<std::string> _city;
    int _streetNumber;
    std::string _streetType;
    std::vector<std::string> _streetName;
    std::string _addr;
};

#endif
