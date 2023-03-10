#pragma once

/*
 *  C++ and Python Program
 *
 *  TextUtils.h
 *
 *  Date: 12-2-2022
 *  Author: Liam Rand
 */

#ifndef BANKING_TEXTUTILS_H_
#define BANKING_TEXTUTILS_H_

#include <string>

using namespace std;

//This class is static so that it's functions may be accessed without having
//to create an object instance of the class.
static class TextUtils
{
public:
	static string nCharString(size_t t_size, char t_char);
};

#endif // BANKING_TEXTUTILS_H_