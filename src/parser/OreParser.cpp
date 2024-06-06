//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Parses out the data from the Forge ORE file configuration maps. 
//

#include "OreParser.h"
#include "ParsedData.h"
#include "CommonFunctions.h"
//#include "Logger.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>

//using namespace spdlog;
using namespace std;

/**
 * @brief Parses the data from the ORE file.
 *
 * @param filePath The path to the ORE file to be parsed.
 * @return ParsedData -- The data from the ORE file in string vectors.
 */
ParsedData OreParser::parse(const string& filePath) 
{

    ParsedData result;
    InstrumentData instrument;
    TrackData track;

    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filePath + " for reading.");
    }

    // Write to the log file
	//get("logger")->trace("Parsing file: {}", filePath);

    //
    // Variables Used
    //  
    string line;
    string value;

    //
    // Read the Song line
    //
    getline(file, line);

    // Split the line into tokens
    vector<string> tokens = splitForTokens(line, '*');
    
    // Check if the first token is SONG
    if (tokens[0] != "SONG") {
        throw runtime_error("Invalid file format. Expected SONG, got " + tokens[0]);
    }

    // Ensure token count is correct
    // Check if the number of tokens is 17
    if ((tokens[0] == "SONG") && (tokens.size() != 12)) {
        throw runtime_error("Invalid file format. Expected 12 tokens, got " + tokens.size());
    }

    // Song ID
    value = tokens[1]; 
    result.addConfig("SongID", value);
	//get("logger")->trace("SongID: {}", value);

    // Song Name
    value = tokens[2]; 
    result.addConfig("SongName", value);
	//get("logger")->trace("SongName: {}", value);

    // Read the Transcriber
    value = tokens[3]; 
    result.addConfig("Transcriber", value);
	//get("logger")->trace("Transcriber: {}", value);

    // Read the Speed Modifier
    value = tokens[4]; 
    result.addConfig("SpeedModifier", value);
	//get("logger")->trace("SpeedModifier: {}", value);

    // Read the Pitch Modifier
    value = tokens[5]; 
    result.addConfig("PitchModifier", value);
	//get("logger")->trace("PitchModifier: {}", value);

    // Read the Style
    value = tokens[6]; 
    result.addConfig("Style", value);
	//get("logger")->trace("Style: {}", value);

    // Read the Volume
    value = tokens[7]; 
    result.addConfig("Volume", value);
	//get("logger")->trace("Volume: {}", value);

    // Read the Compression
    value = tokens[8]; 
    result.addConfig("Compression", value);
	//get("logger")->trace("Compression: {}", value);

    // Read the Pitch Guessing
    value = tokens[9]; 
    result.addConfig("PitchGuessing", value);
	//get("logger")->trace("PitchGuessing: {}", value);

    // Read the Back Folding
    value = tokens[10]; 
    result.addConfig("BackFolding", value);
	//get("logger")->trace("BackFolding: {}", value);

    // Read the Fade Out
    value = tokens[11]; 
    result.addConfig("FadeOut", value);
	//get("logger")->trace("FadeOut: {}", value);

    //
    // Read the rest of the file in a loop
    //
    while(getline(file, line))
    {
        // Split the line into tokens
        vector<string> tokens = splitForTokens(line, '*');

        if (tokens[0] == "SONG")
        {
            if (tokens[1] == "END") 
            {
                /* we have reached the end of the Song */
            	//get("logger")->trace("End of Song");
                break;
            }
        }

        if (tokens[0] == "ABCTRACK")
        {
            if (tokens[1] == "END") 
            {
                /* we have reached the end of the Instrument */
                result.addInstrument(instrument);
                continue;
            }

            // Ensure token count is correct
            // Check if the number of tokens is 17
            if (tokens.size() != 17) {
                throw runtime_error("Invalid file format. Expected 17 tokens, got " + tokens.size());
            }


            /* we have a new Instrument */
            instrument = InstrumentData();

            // Read the SongID
            value = tokens[1]; 
            instrument.addConfig("SongID", value);
        	//get("logger")->trace("\tSongID: {}", value);

            // Read the Instrument ID
            value = tokens[2]; 
            instrument.addConfig("InstrumentID", value);
        	//get("logger")->trace("\tInstrumentID: {}", value);

            // Read the ABC Title
            value = tokens[3]; 
            instrument.addConfig("ABCTitle", value);
        	//get("logger")->trace("\tABCTitler: {}", value);

            // Read the ABC Index
            value = tokens[4]; 
            instrument.addConfig("ABCIndex", value);
        	//get("logger")->trace("\tABCIndex: {}", value);

            // Read the Volume Adjust
            value = tokens[5]; 
            instrument.addConfig("VolumeAdjust", value);
        	//get("logger")->trace("\tVolumeAdjust: {}", value);

            // Read the Polyphony
            value = tokens[6]; 
            instrument.addConfig("Polyphony", value);
        	//get("logger")->trace("\tPolyphony: {}", value);

            // Read the Polyphony Direction
            value = tokens[7]; 
            instrument.addConfig("PolyphonyDirection", value);
        	//get("logger")->trace("\tPolyphonyDirection: {}", value);

            // Read the Duration
            value = tokens[8]; 
            instrument.addConfig("Duration", value);
        	//get("logger")->trace("\tDuration: {}", value);

            // Read the Duration Length
            value = tokens[9]; 
            instrument.addConfig("Duration Length", value);
        	//get("logger")->trace("\tDuration Length: {}", value);

            // Read the Panning 1
            value = tokens[10]; 
            instrument.addConfig("Panning1", value);
        	//get("logger")->trace("\tPanning1: {}", value);

            // Read the Panning 2
            value = tokens[11]; 
            instrument.addConfig("Panning2", value);
        	//get("logger")->trace("\tPanning2: {}", value);

            // Read the Panning 3
            value = tokens[12]; 
            instrument.addConfig("Panning3", value);
        	//get("logger")->trace("\tPanning3: {}", value);

            // Read the ffAmp
            value = tokens[13]; 
            instrument.addConfig("ffAmp", value);
        	//get("logger")->trace("\tffAmp: {}", value);

            // Read the ffShift
            value = tokens[14]; 
            instrument.addConfig("ffShift", value);
        	//get("logger")->trace("\tffShift: {}", value);

            // Read the ffCoupling
            value = tokens[15]; 
            instrument.addConfig("ffCoupling", value);
        	//get("logger")->trace("\tffCoupling: {}", value);

            // Read the Instrument
            value = tokens[16]; 
            instrument.addConfig("Instrument", value);
        	//get("logger")->trace("\tInstrument: {}", value);

            continue;
        }
        
        if (tokens[0] == "MIDTRACK")
        {
            /* we have a new miditrack */
            track = TrackData();

            // Ensure token count is correct
            // Check if the number of tokens is 12
            if (tokens.size() != 12) {
                throw runtime_error("Invalid file format. Expected 12 tokens, got " + tokens.size());
            }

            // Read the Instrument ID
            value = tokens[1]; 
            track.addConfig("InstrumentID", value);
        	//get("logger")->trace("\t\tInstrumentID: {}", value);

            // Read the Midi Track ID
            value = tokens[2]; 
            track.addConfig("MidiTrackID", value);
        	//get("logger")->trace("\t\tMidiTrackID: {}", value);

            // Read the Mid Track Number
            value = tokens[3]; 
            track.addConfig("MidTrackNumber", value);
        	//get("logger")->trace("\t\tMidTrackNumber: {}", value);

            // Read the Pitch
            value = tokens[4]; 
            track.addConfig("Pitch", value);
        	//get("logger")->trace("\t\tPitch: {}", value);

            // Read the Volume
            value = tokens[5]; 
            track.addConfig("Volume", value);
        	//get("logger")->trace("\t\tVolume: {}", value);

            // Read the Delay
            value = tokens[6]; 
            track.addConfig("Delay", value);
        	//get("logger")->trace("\t\tDelay: {}", value);

            // Read the Priority
            value = tokens[7]; 
            track.addConfig("Priority", value);
        	//get("logger")->trace("\t\tPriority: {}", value);

            // Read the Divide
            value = tokens[8]; 
            track.addConfig("Divide", value);
        	//get("logger")->trace("\t\tDivide: {}", value);

            // Read the Divide Part
            value = tokens[9]; 
            track.addConfig("DividePart", value);
        	//get("logger")->trace("\t\tDividePart: {}", value);

            // Read the IMFMAP
            value = tokens[10]; 
            track.addConfig("IMFMAP", value);
        	//get("logger")->trace("\t\tIMFMAP: {}", value);

            // Read the ISFMAP
            value = tokens[11]; 
            track.addConfig("ISFMAP", value);
        	//get("logger")->trace("\t\tISFMAP: {}", value);

            // Add the track to the instrument
            instrument.addTrack(track);
        }
    }

    file.close();
    return result;
}

