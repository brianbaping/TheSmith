#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/ParsedData.h"
#include "../include/MapParser.h"

TEST_CASE("testing the factorial function") {


    MapParser fileParser;
    ParsedData parsedOutData = fileParser.parse("test.map");  

    InstrumentData instrumentData;
    TrackData trackData;
    parsedOutData.addConfig("author", "John Doe");
    instrumentData.addConfig("instrument", "guitar");
    trackData.addConfig("track", "1");   
    CHECK(parsedOutData.SongConfigs["author"] == "John Doe");
    CHECK(instrumentData.InstrumentConfigs["instrument"] == "guitar");
    CHECK(trackData.TrackConfigs["track"] == "1");
}