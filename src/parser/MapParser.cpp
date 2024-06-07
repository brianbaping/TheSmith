//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Parses out the data from the legacy BruTe configuration maps. 
//

#include "MapParser.h"
#include "CommonFunctions.h"
#include "ParsedData.h"
#include "Logger.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>

//using namespace spdlog;
using namespace std;

// Function prototype
string parseline(string line, string section, char delimiter);
string parselinewithcomment(string line, string section, char delimiter);
string parselinewithcomment(string line, string section, char delimiter, int index);

/**
 * @brief Parses the data from the configuration map file.
 * @param filePath The path to the configuration file to be parsed.
 * @return ParsedData The data from the configuration in string vectors.
*/
ParsedData MapParser::parse(const string& filePath) 
{
    ParsedData result;
    InstrumentData instrument;
    TrackData track;

    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    //
    // Step thru the header portion of the file
    //  
    string line;
    string value;
    string value2;

    // Write to the log file   
    Logger& logger = Logger::getInstance();
    logger.log("Parsing file: " + filePath);

    // Read the Song Name
    getline(file, line);
    value = parseline(line, "SongName", ':');
    result.addConfig("SongName", value);
    logger.log("SongName: " + value);
    
    // Read the Speed Modifier
    getline(file, line);
    value = parseline(line, "SpeedModifier", ':');
    result.addConfig("SpeedModifier", value);
    logger.log("SpeedModifier: " + value);

    // Read the Pitch Modifier
    getline(file, line);
    value = parseline(line, "PitchModifier", ':');
    result.addConfig("PitchModifier", value);
    logger.log("PitchModifier: " + value);    

    // Read the Style
    getline(file, line);
    value = parselinewithcomment(line, "Style", ' ');
    result.addConfig("Style", value);
    logger.log("Style: " + value);

    // Read the Volume
    getline(file, line);
    value = parselinewithcomment(line, "Volume", ' ');
    result.addConfig("Volume", value);
    logger.log("Volume: " + value);

    // Read the Compression
    getline(file, line);
    value = parselinewithcomment(line, "Compression", ' ');
    result.addConfig("Compression", value);
    logger.log("Compression: " + value);

    // Read the Pitch Guessing
    getline(file, line);
    if (line.length() > 0)
    {
        value = line.substr(0,3);
        result.addConfig("PitchGuessing", value);
        logger.log("PitchGuessing: " + value);
    }

    // Read the Back Folding
    getline(file, line);
    if (line.length() > 0)
    {
        value = line.substr(0, 3);
        result.addConfig("BackFolding", value);
        logger.log("BackFolding: " + value);
}

    // Read the Fade Out
    getline(file, line);
    value = parselinewithcomment(line, "FadeOut", ' ', 2);
    result.addConfig("FadeOut", value);
    logger.log("FadeOut: " + value);

    // Read the Transcriber
    getline(file, line);
    value = parseline(line, "Transcriber", ' ');
    result.addConfig("Transcriber", value);
    logger.log("Transcriber: " + value);

    // Write to the log file
    logger.log("Parsing Instruments");

    //
    // Read the Instrument Information
    //
    while(getline(file, line))
    {
        // Skip empty lines and comments
        if (line.length() == 0) {continue;}
        if (line.substr(0,1) == "%") {continue;}

        // Parse the line
        vector<string> linevector = splitForTokens(line, ' ');
        if (linevector[0] == "abctrack")
        {
            if (linevector[1] == "begin") 
            {
                /* we have a new Instrument */
                logger.log("Instrument Begin");
                instrument = InstrumentData();
                continue;
            }
            else if (linevector[1] == "end")
            {
                /* we have reached the end of the Instrument */
                logger.log("Instrument End");
                result.addInstrument(instrument);
                continue;
            }           
        }
        
        // Read ffamp   
        if (linevector[0] == "ffamp")
        {
            value = trim(linevector[1]);
            instrument.addConfig("ffamp", value);
            logger.log("ffamp: " + value);
            continue;
        }

        // Read ffshift   
        if (linevector[0] == "ffshift")
        {
            value = trim(linevector[1]);
            instrument.addConfig("ffshift", value);
            logger.log("ffshift: " + value);
            continue;
        }

        // Read ffcoupling   
        if (linevector[0] == "ffcoupling")
        {
            value = line.substr(11);
            instrument.addConfig("ffcoupling", value);
            logger.log("ffcoupling: " + value);
            continue;
        }

        // Read polyphony   
        if (linevector[0] == "polyphony")
        {
            value = trim(linevector[1]);
            instrument.addConfig("polyphony", value);
            logger.log("polyphony: " + value);
            value = trim(linevector[2]);
            instrument.addConfig("polyphonydirection", value);
            logger.log("polyphony direction: " + value);

            continue;
        }

        // Read instrument   
        if (linevector[0] == "instrument")
        {
            value = trim(linevector[1]);
            instrument.addConfig("instrument", value);
            logger.log("instrument: " + value);
            if (linevector.size() > 2)
            {
                value = trim(linevector[2]);
                instrument.addConfig("instrumentstyle", value);
                logger.log("instrument style: " + value);
            }
            if (linevector.size() > 3)
            {
                value = trim(linevector[3]);
                instrument.addConfig("instrumentextended1", value);
                logger.log("instrument extended 1: " + value);
            }
            if (linevector.size() > 4)
            {
                value = trim(linevector[4]);
                instrument.addConfig("instrumentextended2", value);
                logger.log("instrument extended 2: " + value);
            }
            continue;
        }

        // Read duration   
        if (linevector[0] == "duration")
        {
            value = trim(linevector[1]);
            instrument.addConfig("duration", value);
            logger.log("duration: " + value);
            if (linevector.size() > 2)
            {
                value = trim(linevector[2]);
                instrument.addConfig("durationamount", value);
                logger.log("duration amount: " + value);
            }
            continue;
        }

        // Read split   
        if (linevector[0] == "split")
        {
            value = trim(linevector[1]);
            instrument.addConfig("split", value);
            logger.log("split: " + value);
            continue;
        }

        // Read durationsplit   
        if (linevector[0] == "durationsplit")
        {
            value = trim(linevector[1]);
            instrument.addConfig("durationsplitlength", value);
            logger.log("durationsplit length: " + value);
            value = trim(linevector[2]);
            instrument.addConfig("durationsplitpart", value);
            logger.log("durationsplit part: " + value);
            continue;
        }

        // Read alternate   
        if (linevector[0] == "alternate")
        {
            value = trim(linevector[1]);
            instrument.addConfig("alternatecount", value);
            logger.log("alternate count: " + value);
            value = trim(linevector[2]);
            instrument.addConfig("alternatepart", value);
            logger.log("alternate part: " + value);
            continue;
        }

        // Read triller   
        if (linevector[0] == "triller")
        {
            value = trim(linevector[1]);
            instrument.addConfig("triller", value);
            logger.log("triller: " + value);
            continue;
        }

        // Read pitchbendinfo   
        if (linevector[0] == "pitchbendinfo")
        {
            value = trim(linevector[1]);
            instrument.addConfig("pitchbendinfo", value);
            logger.log("pitchbendinfo: " + value);
            value = trim(linevector[2]);
            instrument.addConfig("pitchbenddepth", value);
            logger.log("pitchbenddepth: " + value);
            continue;
        }

        // Read panning   
        if (linevector[0] == "panning")
        {
            value = trim(linevector[1]);
            instrument.addConfig("panning", value);
            logger.log("panning: " + value);
            continue;
        }

        // Read arpeggio   
        if (linevector[0] == "arpeggio")
        {
            value = trim(linevector[1]);
            instrument.addConfig("arpeggio", value);
            logger.log("arpeggio: " + value);
            if (linevector.size() > 2)
            {
                value = trim(linevector[2]);
                instrument.addConfig("arpeggioincrement", value);
                logger.log("arpeggio increment: " + value);
            }
            continue;
        }

        // Read directmapping   
        if (linevector[0] == "directmapping")
        {
            value = trim(linevector[1]);
            instrument.addConfig("indrum", value);
            logger.log("in drum: " + value);
            value = trim(linevector[2]);
            instrument.addConfig("directmapping", value);
            logger.log("direct mapping: " + value);
            continue;
        }

        // Read voladjust   
        if (linevector[0] == "voladjust")
        {
            value = trim(linevector[1]);
            instrument.addConfig("voladjust", value);
            logger.log("voladjust: " + value);
            continue;
        }

        // Read range   
        if (linevector[0] == "range")
        {
            value = trim(linevector[1]);
            instrument.addConfig("rangestart", value);
            logger.log("range start: " + value);
            value = trim(linevector[2]);
            instrument.addConfig("rangeend", value);
            logger.log("range end: " + value);
            continue;
        }

        // Read align   
        if (linevector[0] == "align")
        {
            value = trim(linevector[1]);
            instrument.addConfig("align", value);
            logger.log("align: " + value);
            continue;
        }

        // Read invert   
        if (linevector[0] == "invert")
        {
            value = "1";
            instrument.addConfig("invert", value);
            logger.log("invert: " + value);
            continue;
        }

        // Read humanizer   
        if (linevector[0] == "humanizer")
        {
            value = trim(linevector[1]);
            instrument.addConfig("humanizer", value);
            logger.log("humanizer: " + value);
            continue;
        }

        //
        // Read Midi Tracks
        //
        if (linevector[0] == "miditrack")
        {
            track = TrackData();
            value = trim(linevector[1]);
            track.addConfig("track", value);
            logger.log("track: " + value);
            value = trim(linevector[3]);
            track.addConfig("pitch", value);
            logger.log("pitch: " + value);
            value = trim(linevector[5]);
            track.addConfig("volume", value);
            logger.log("volume: " + value);
            value = trim(linevector[7]);
            track.addConfig("delay", value);
            logger.log("delay: " + value);
            value = trim(linevector[9]);
            track.addConfig("priority", value);
            logger.log("priority: " + value);
            value = "1";
            value2 = "0";
            if (linevector.size() > 11)
            {
                value = trim(linevector[11]);
                value2 = trim(linevector[12]);
            }
            track.addConfig("divide", value);
            track.addConfig("dividepart", value2);
            logger.log("divide: " + value);
            logger.log("divide part: " + value2);
            value = "0";
            value2 = "0";
            if (linevector.size() > 15)
            {
                value = trim(linevector[14]);
                value2 = trim(linevector[15]);
            }
            track.addConfig("imfmap", value);
            track.addConfig("isfmap", value2);
            logger.log("imfmap: " + value);
            logger.log("isfmap: " + value2);

            // 
            // Add the track to the instrument
            //
            instrument.addTrack(track);
        }

    }

    file.close();
    return result;

}

/**
 * @brief Parses a line from the file.
 * @param line The line to parse.
 * @param section The section to parse.
 * @param delimiter The delimiter to use.
 * @return string The value of the parsed line.
 */
string parseline(string line, string section, char delimiter)
{
    string value;
    vector<string> linevector = splitForTokens(line, delimiter);
    if (linevector.size() != 2) 
    {
        throw runtime_error("Invalid file format: Missing " + section );
    }
    value = trim(linevector[1]);
    return value;
}

/**
 * @brief Parses a line from the file with a comment.
 * @param line The line to parse.
 * @param section The section to parse.
 * @param delimiter The delimiter to use.
 * @return string The value of the parsed line.
 */
string parselinewithcomment(string line, string section, char delimiter)
{
    return parselinewithcomment(line, section, delimiter, 1);
}

/**
 * @brief Parses a line from the file with a comment.
 * @param line The line to parse.
 * @param section The section to parse.
 * @param delimiter The delimiter to use.
 * @param index The index to use.
 * @return string The value of the parsed line.
 */
string parselinewithcomment(string line, string section, char delimiter, int index)
{
    string value;
    vector<string> linevector = splitForTokens(line, ' ');
    if (linevector.size() < 1) 
    {
        throw runtime_error("Invalid file format: Missing " + section);
    }
    value = trim(linevector[index]);
    return value;
}
    