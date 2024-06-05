//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Map parser for the legacy BruTe config maps.
//

#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "IFileParser.h"

class MapParser : public IFileParser {
public:
    ParsedData parse(const std::string& filePath) override;
};

#endif // MAPPARSER_H
