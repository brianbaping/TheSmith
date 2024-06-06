#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/ParsedData.h"
#include "../include/MapParser.h"
#include "../include/Logger.h"
#include "../include/spdlog/sinks/stdout_color_sinks.h"

TEST_CASE("Song Parser Test") {

    spdlog::stdout_color_mt("logger");
    MapParser fileParser;
    ParsedData parsedOutData = fileParser.parse("test.map");  

    CHECK(parsedOutData.SongConfigs["SongName"] == "Albatros");
    CHECK(parsedOutData.SongConfigs["SpeedModifier"] == "0");
    CHECK(parsedOutData.SongConfigs["PitchModifier"] == "0");
    CHECK(parsedOutData.SongConfigs["Style"] == "TSO");
    CHECK(parsedOutData.SongConfigs["Volume"] == "0");
    CHECK(parsedOutData.SongConfigs["Compression"] == "1.0");
    CHECK(parsedOutData.SongConfigs["PitchGuessing"] == "%no");
    CHECK(parsedOutData.SongConfigs["BackFolding"] == "%no");
    CHECK(parsedOutData.SongConfigs["FadeOut"] == "0");
    CHECK(parsedOutData.SongConfigs["Transcriber"] == "Vydor");

    CHECK(parsedOutData.Instruments.size() == 6);
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["polyphony"] == "6");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["polyphonydirection"] == "top");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["duration"] == "2");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["durationamount"] == "10000");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["panning"] == "41");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["ffamp"] == "0.000000");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["ffshift"] == "0.000000");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["ffcoupling"] == "");
    CHECK(parsedOutData.Instruments[0].InstrumentConfigs["instrument"] == "basson_vib");

    CHECK(parsedOutData.Instruments[0].Tracks.size() == 1);
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["track"] == "6");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["pitch"] == "0");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["volume"] == "0");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["delay"] == "0");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["priority"] == "1");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["divide"] == "1");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["dividepart"] == "0");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["imfmap"] == "0");
    CHECK(parsedOutData.Instruments[0].Tracks[0].TrackConfigs["isfmap"] == "0");

}

TEST_CASE("Always Blue") {

    CHECK(1 == 1);
}

