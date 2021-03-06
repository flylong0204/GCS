//------------------------------------------------------------------------------
// Demo of sub-displays
//------------------------------------------------------------------------------

#include "Factory.h"
#include "SimStation.h"

#include <openeaagles/basic/Pair.h>
#include <openeaagles/basic/Timers.h>
#include <openeaagles/basic/Parser.h>
#include <openeaagles/basicGL/Graphic.h>

#include <openeaagles/gui/glut/GlutDisplay.h>
#include <GL/glut.h>

#include <openeaagles/basic/Factory.h>
#include <openeaagles/basicGL/Factory.h>
#include <openeaagles/gui/glut/Factory.h>
#include <openeaagles/dis/Factory.h>
#include <openeaagles/instruments/Factory.h>
#include <openeaagles/ioDevice/Factory.h>
#include <openeaagles/simulation/Factory.h>
#include <openeaagles/dynamics/Factory.h>

namespace Eaagles {
	
	// Description (input) File -- After being processed by the C preprocessor
	const char* testFileName = "../gcs.edl";
	// Frame Rate
	const int frameRate = 60;
	// Top level Station
	static Eaagles::Simulation::Station* station = 0;

	// build a station
	static Eaagles::Simulation::Station* builder(const char* const fileName) 	{
		Eaagles::Simulation::Station* p = 0;
		// Read the description file
		int errors = 0;
		Eaagles::Basic::Object* q1 = Eaagles::Basic::lcParser(fileName, Eaagles::Factory::createObj, &errors);
		if (errors > 0) {
			std::cerr << "File: " << fileName << ", errors: " << errors << std::endl;
			return 0;
		}
		if (q1 != 0) {
			// When we were given a Basic::Pair, get the pointer to its object.
			Eaagles::Basic::Pair* pp = dynamic_cast<Eaagles::Basic::Pair*>(q1);
			if (pp != 0) {
				q1 = pp->object();
			}
			// What we should have here is the Station object
			p = dynamic_cast<Eaagles::Simulation::Station*>(q1);
		}
		return p;
	}
		
	static void updateDataCB(int msecs) {
		// Current time
		double time = Eaagles::getComputerTime();
		// Compute delta time
		static double time0 = time;   // N-1 Time
		Eaagles::LCreal dt = static_cast<Eaagles::LCreal>(time - time0);
		time0 = time;
		station->updateData(dt);
	}
	
	int exec(int argc, char* argv[]) {
		glutInit(&argc, argv);
	  
		station = builder(testFileName);
		if (station == 0) {
			std::cerr << "Invalid configuration file!" << std::endl;
			return EXIT_FAILURE;
		}

		station->event(Eaagles::Basic::Component::RESET_EVENT);
		
		double dt = 1.0/static_cast<double>(frameRate);
		int msecs = static_cast<int>(dt * 1000);

		station->updateData(dt);
		station->updateTC(dt);
		station->event(Eaagles::Basic::Component::RESET_EVENT);

		station->event(Eaagles::Basic::Component::USER_EVENTS+1);

		glutTimerFunc(msecs, updateDataCB, msecs);
		station->createTimeCriticalProcess();
		
		glutMainLoop();
		return EXIT_SUCCESS;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	const int argc = 1;
	char* argv[argc] = {};
	return Eaagles::exec(argc, argv);
}