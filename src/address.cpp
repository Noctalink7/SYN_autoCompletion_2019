/*
** EPITECH PROJECT, 2020
** autoCompletion
** File description:
** address
*/

#include "address.hpp"

Address::Address(std::vector<std::string> city, int streetNumber,       \
                 std::string streetType, std::vector<std::string> streetName, \
                 std::string addr)
{
    this->_city = city;
    this->_streetNumber = streetNumber;
    this->_streetType = streetType;
    this->_streetName = streetName;
    this->_addr = addr;
}

std::vector<std::string> Address::getCity()
{
    return this->_city;
}

int Address::getNumber()
{
    return this->_streetNumber;
}

std::string Address::getType()
{
    return this->_streetType;
}

std::vector<std::string> Address::getName()
{
    return this->_streetName;
}

std::string Address::getAddr()
{
    return this->_addr;
}
