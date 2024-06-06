#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/ParsedData.h"
#include "../include/MapParser.h"
#include "../include/Logger.h"
#include "../include/spdlog/sinks/stdout_color_sinks.h"

TEST_CASE("testing the factorial function") {

    spdlog::stdout_color_mt("logger");
    MapParser fileParser;
    ParsedData parsedOutData = fileParser.parse("test.map");  

    CHECK(parsedOutData.SongConfigs["SongName"] == "Albatros");
}

TEST_CASE("Always Blue") {

    CHECK(1 == 1);
}

