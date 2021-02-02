/*
** EPITECH PROJECT, 2020
** autoCompletion
** File description:
** exception
*/

#include "Exception.hpp"

Exception::Exception(const std::string &_err) throw()
{
  this->errormsg = _err;
}

Exception::~Exception() throw()
{
}

const char *Exception::err() const throw()
{
  return (this->errormsg.c_str());
}
