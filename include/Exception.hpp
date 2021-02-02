/*
** EPITECH PROJECT, 2020
** autoCompletion
** File description:
** exception
*/

#ifndef _EXCEPTION_HPP
# define _EXCEPTION_HPP

#include <iostream>
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception (const std::string &_err) throw();
    ~Exception() throw();
    const char* err() const throw();
    std::string errormsg;
};

#endif
