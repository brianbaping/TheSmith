//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Container for the configuration data held in the maps. 
//

#include "ParsedData.h"

using namespace std;

/**
 * @brief Adds a configuration to the track data.
 *
 * @param key The key of the configuration.
 * @param value The value of the configuration.
 * @return void
 */
void TrackData::addConfig(const string& key, const string& value) {
    TrackConfigs[key] = value;
}

/**
 * @brief Prints the configurations of the track data.
*/
void TrackData::printConfigs() const {
    for (const auto& [key, value] : TrackConfigs) {
        cout << key << ": " << value << endl;
    }
}

/**
 * @brief Adds a configuration to the instrument data.
 *
 * @param key The key of the configuration.
 * @param value The value of the configuration.
 * @return void
 */
void InstrumentData::addConfig(const string& key, const string& value) {
    InstrumentConfigs[key] = value;
}

/**
 * @brief Adds an track to the instrument track list.
 *
 * @param track The track to add.
 * @return void
 */
void InstrumentData::addTrack(const TrackData& track) {
    Tracks.push_back(track);
}

/**
 * @brief Prints the configurations of the instrument data.
*/
void InstrumentData::printConfigs() const {
    for (const auto& [key, value] : InstrumentConfigs) {
        cout << key << ": " << value << endl;
    }
}

/**
 * @brief Prints the tracks of the instrument data.
*/
void InstrumentData::printTracks() const {
    for (const auto& track : Tracks) {
        track.printConfigs();
    }
}

/**
 * @brief Adds a configuration to the song data.
 *
 * @param key The key of the configuration.
 * @param value The value of the configuration.
 * @return void
 */
void ParsedData::addConfig(const string& key, const string& value) {
    SongConfigs[key] = value;
}

/**
 * @brief Adds an instrument to the songs instrument list.
 *
 * @param instrument The instrument to add.
 * @return void
 */
void ParsedData::addInstrument(const InstrumentData& instrument) {
    Instruments.push_back(instrument);
}

/**
 * @brief Prints the configurations of the song data.
*/
void ParsedData::printConfigs() const {
    for (const auto& [key, value] : SongConfigs) {
        cout << key << ": " << value << endl;
    }
}

/**
 * @brief Prints the instruments and tracks of the song data.
*/
void ParsedData::printInstruments() const {
    for (const auto& instrument : Instruments) {
        instrument.printConfigs();
        instrument.printTracks();
    }
}