//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   The parser for the Forge ORE files.
//

#ifndef OREPARSER_H
#define OREPARSER_H

#include "IFileParser.h"

class OreParser : public IFileParser {
public:
    ParsedData parse(const std::string& filePath) override;
};

#endif // OREPARSER_H