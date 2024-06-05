//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Collection of various functions used in the Forge program. 
//

#include <CommonFunctions.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <algorithm>

using namespace std;

/**
 * @brief Splits a string into tokens based on a delimiter.
 *
 * @param s The string to be split.
 * @return vector<string> -- Vector of strings split out by token.
 */
vector<string> splitForTokens(const string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
     if (token!="")
       tokens.emplace_back(token);
   }
   return tokens;
}

/**
 * @brief Remove the white spaces from the left of a string.
 *
 * @param s The string to be trimmed.
 * @return string -- The string without spaces.
 */
string ltrim(const string &s) {
    string result = s;
    result.erase(result.begin(), find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    return result;
}

/**
 * @brief Remove the white spaces from the right of a string.
 *
 * @param s The string to be trimmed.
 * @return string -- The string without spaces.
 */
string rtrim(const string &s) {
    string result = s;
    result.erase(find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), result.end());
    return result;
}

/**
 * @brief Remove the white spaces around a string.
 *
 * @param s The string to be trimmed.
 * @return string -- The string without spaces.
 */
string trim(const string &s) {
    return rtrim(ltrim(s));
}

