//
// Authors:   	  Bruzo of Gladden, Vydor of Landroval
// Creation Date: June 4, 2024
// Last Modified: June 4, 2024
// URL:           https://github.com
//
// Description:   Converts Midi files into ABC format 
//                for play in the Lord of the Rings Online game.
//

#include "CommonFunctions.h"
#include "Options.h"
#include "MidiFile.h"
#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "ParsedData.h"
#include "FileParser.h"

#include <iostream>

using namespace std;
using namespace smf;
using namespace spdlog;


// Global variables
Options  options;


void     checkOptions        (Options& opts);
void     processFile         (const string& inputfilename, const string& outputfilename);
void     help	             (void);
void     usage               (const string& command);


///////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

	// Process command-line options
	options.setOptions(argc, argv);
	checkOptions(options);

	// Set up logging
	int debuglevel = options.getInteger("debuglevel");
	if (debuglevel >= 0) spdlog::basic_logger_mt("logger", "Forge.log");
	if (debuglevel < 0) spdlog::stdout_color_mt("logger");    
    
	// debug levels are 5 - Critical, 4 - Error, 3 - Warn, 2 - Info, 1 - Debug, 0 - Trace, -1 - None
	spdlog::set_level(static_cast<spdlog::level::level_enum>(debuglevel));  

	// Get the input and output filenames
	string midifilename;
	string outputfilename;
	string configfilename;

	try {
		midifilename = trim(options.getString("midi"));
		outputfilename = trim(options.getString("output"));
		configfilename = trim(options.getString("config"));
	}
	catch (const exception& e) {
		get("logger")->error("Error: {}", e.what());
		exit(1);	
	}

	// Start the program
	get("logger")->info("Firing up the Forge");   

	// Parse the config file
	FileParser fileParser;
	ParsedData parsedOutData = fileParser.parseFile(configfilename);

	// Process the midi file
	processFile(midifilename, outputfilename);

	// End the program
	return 0;
}

///////////////////////////////////////////////////////////////////////////



//
// processFile -- Loop thru the midi
//
void processFile(const string& inputfilename, const string& outputfilename) {

	// Start processing the file
	get("logger")->trace("Processing file: {}", inputfilename);


	// Open the midi file
	MidiFile midifile(inputfilename);

	// Loop thru the midi file
	for (int i=0; i<midifile.getTrackCount(); i++) {
		for (int j=0; j<midifile.getEventCount(i); j++) {
			if (!midifile[i][j].isNoteOff()) {
				continue;
			}
		}
	}
	midifile.write(outputfilename);
}


/**
 * @brief Check the options from the command line.
 *
 * @param opts The options from the command line.
 */
void checkOptions(Options& opts) {
	opts.define("a|author=b",   "author of the program");
	opts.define("v|version=b",  "version of the program");
	opts.define("u|usage=b",  "example useage of the program");
	opts.define("h|help=b",   "list of options for the program");
	opts.define("d|debuglevel=i:-1",   "5 Critical, 4 Error, 3 Warn, 2 Info, 1 Debug, 0 Trace, -1 None");
	opts.define("m|midi=s:test.mid",   "the midi file to convert");
	opts.define("c|config=s:test.map",   "the config file to convert");
	opts.define("o|output=s:new.abc", "ABC output filename");
	opts.process();

	if (opts.getBoolean("author")) {
		cout << "Written by Bruzo of Gladden, "
		     << "Vydor of Landroval" << endl;
		exit(0);
	} else if (opts.getBoolean("version")) {
		cout << "Forge, version 1.0 (4 Jun 2024)\n"
		     << "compiled: " << __DATE__ << endl;
		exit(0);
	} else if (opts.getBoolean("usage")) {
		usage(opts.getCommand());
		exit(0);
	} else if (opts.getBoolean("help")) {
		help();
		exit(0);
	} 
}



/**
 * @brief Shows the help output for the command line arugments.
 *
 */
void help(void) {
	cout <<
	"Valid Flags are: a - Author\n" <<
	"                 v - Version\n" <<
	"                 u - Usage\n" <<
	"                 h - Help\n" <<
	"                 d - Debug level (5 Critical, 4 Error, 3 Warn, 2 Info, 1 Debug, 0 Trace [-1] None)\n" <<
	"                 m - Midi file\n" <<
	"                 c - Config file\n" <<
	"                 o - Output file\n" <<
	"                 \n"
	<< endl;
}



/**
 * @brief Shows the usage of the Forge.
 *
 */
void usage(const string& command) {
	cout << command << " -m <midifile> -c <configfile> -o <abcfile> (default abc name is new.abc) \n"
	<< endl;
}



