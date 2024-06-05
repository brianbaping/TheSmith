//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   The interface for the file parser classes.
//

#ifndef IFILEPARSER_H
#define IFILEPARSER_H

#include <string>
#include <vector>
#include "ParsedData.h"

class IFileParser {
public:
    virtual ~IFileParser() = default;
    virtual ParsedData parse(const std::string& filePath) = 0;

};

#endif // IFILEPARSER_H
