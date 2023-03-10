#include "TextUtils.h"

/*
 *  Grocery Frequency Program
 *
 *  TextUtils.cpp
 *
 *  Date: 12-9-2022
 *  Author: Liam Rand
 */

 /**
  * Returns a string of length t_size, each character a t_char.
  * For example, nCharString(5, '*') should return "*****"
  * This function is static so that it may be accessed without an
  * instantiated object of this class.
  *
  * @param t_size string length, >=0
  * @return string of t_size t_chars
  */
string TextUtils::nCharString(size_t t_size, char t_char)
{
	//The generated string containing n amount of cs
	string charString = "";

	//Loop t_size times and append t_char to the generated string each time
	for (int i = 0; i < t_size; i++)
	{
		charString += t_char;
	}

	//Return the generated string
	return charString;
}
