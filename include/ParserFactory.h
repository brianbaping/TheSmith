//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   The factory for the parser types.
//

#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

#include "IFileParser.h"
#include <memory>
#include <string>

class ParserFactory {
public:
    static std::shared_ptr<IFileParser> createParser(const std::string& extension);
};

#endif // PARSERFACTORY_H
