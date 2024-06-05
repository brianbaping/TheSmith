//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   FileParser is a parent for the parser classes.
//

#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "IFileParser.h"
#include <memory>
#include <string>

class FileParser {
public:
    ParsedData parseFile(const std::string& filePath);

// allows the FileParser to be used in the factory pattern
private:
    std::shared_ptr<IFileParser> getParser(const std::string& extension);
};

#endif // FILEPARSER_H
