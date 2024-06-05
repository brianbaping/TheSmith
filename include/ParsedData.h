//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   The structure of the parsed data from the maps.
//

#ifndef PARSEDDATA_H
#define PARSEDDATA_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

// Class representing TrackData
class TrackData {
public:
    std::unordered_map<std::string, std::string> TrackConfigs;

    void addConfig(const std::string& key, const std::string& value);
    void printConfigs() const;
};

// Class representing InstrumentData
class InstrumentData {
public:
    std::unordered_map<std::string, std::string> InstrumentConfigs;
    std::vector<TrackData> Tracks;

    void addConfig(const std::string& key, const std::string& value);
    void addTrack(const TrackData& track);
    void printConfigs() const;
    void printTracks() const;
};

// Class representing ParsedData
class ParsedData {
public:
    std::unordered_map<std::string, std::string> SongConfigs;
    std::vector<InstrumentData> Instruments;

    void addConfig(const std::string& key, const std::string& value);
    void addInstrument(const InstrumentData& instrument);
    void printConfigs() const;
    void printInstruments() const;
};

#endif // PARSEDDATA_H