//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Factory that returns an instance of the FileParser depending extension of the file. 
//

#include "ParserFactory.h"
#include "MapParser.h"
#include "OreParser.h"
#include <stdexcept>

using namespace std;

/**
 * @brief Creates a parser based on the file extension.
 *
 * @param extension The extension of the file to be parsed.
 * @return Instance of the class that implements the parsing functionality.
 */
shared_ptr<IFileParser> ParserFactory::createParser(const string& extension) {
    if (extension == "map") {
        return make_shared<MapParser>();
    } else if (extension == "ore") {
        return make_shared<OreParser>();
    } else {
        throw runtime_error("Unsupported file extension");
    }
}
