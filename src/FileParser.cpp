//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Implemenation of the FileParser with the extenstion method for the factory. 
//

#include "FileParser.h"
#include "ParserFactory.h"
#include "ParsedData.h"
#include <stdexcept>

using namespace std;

/**
 * @brief Calls theh parsing implemenation of the inherited 
 * class to parse the data from a configuration map file.
 *
 * @param filePath The path to the configuration file to be parsed.
 * @return ParsedData -- The data from the configuration in string vectors.
 */
ParsedData FileParser::parseFile(const string& filePath) {
    auto extension = filePath.substr(filePath.find_last_of('.') + 1);
    auto parser = getParser(extension);
    return parser->parse(filePath);
}

/**
 * @brief Gets the parser for the file extension.
 * class to parse the data from a configuration map file.
 *
 * @param extension The extension of the mapping file.
 * @return Instance of the class that implements the parsing functionality.
 */
shared_ptr<IFileParser> FileParser::getParser(const string& extension) {
    return ParserFactory::createParser(extension);
}

