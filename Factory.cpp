//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"
#include "TestIoHandler.h"
#include "SimStation.h"
#include "TestDisplay.h"
#include "TestMap.h"
#include "TestHsi.h"
#include "TestPfd.h"
#include "JSBSimNetModel.h"

#include <openeaagles/basic/Object.h>
#include <xPanel/Factory.h>

// class factories
#include <../shared/xZeroMQHandlers/Factory.h>
#include <openeaagles/basic/Factory.h>
#include <openeaagles/basicGL/Factory.h>
#include <openeaagles/gui/glut/Factory.h>
#include <openeaagles/dis/Factory.h>
#include <openeaagles/instruments/Factory.h>
#include <openeaagles/ioDevice/Factory.h>
#include <openeaagles/otw/Factory.h>
#include <openeaagles/sensors/Factory.h>
#include <openeaagles/simulation/Factory.h>
#include <openeaagles/dynamics/Factory.h>

#include <cstring>

namespace Eaagles {

	Factory::Factory(){}

	Basic::Object* Factory::createObj(const char* name) {
		Basic::Object* obj = 0;
		if ( std::strcmp(name, SimStation::getFactoryName()) == 0 ) {
			obj = new SimStation();
		}
		if ( std::strcmp(name, TestPfd::getFactoryName()) == 0 ) {
			obj = new TestPfd;
		}
		if (std::strcmp(name, TestMap::getFactoryName()) == 0 ) {
			obj = new TestMap;
		}
		if (std::strcmp(name, TestHsi::getFactoryName()) == 0 ) {
			obj = new TestHsi;
		}
		if ( std::strcmp(name, TestDisplay::getFactoryName()) == 0 ) {
			obj = new TestDisplay();
		}
		if ( std::strcmp(name, TestIoHandler::getFactoryName()) == 0 ) {
			obj = new TestIoHandler();
		}
		if (std::strcmp(name, JSBSimNetModel::getFactoryName()) == 0) {
			obj = new JSBSimNetModel();
		}
		// Example libraries
		if (obj == 0) 
			obj = xPanel::Factory::createObj(name);
		if (obj == 0) 
			obj = xZeroMQHandlers::Factory::createObj(name);
		// Framework libraries
		if (obj == 0) 
			obj = Eaagles::Simulation::Factory::createObj(name);
		if (obj == 0) 
			obj = Instruments::Factory::createObj(name);
		if (obj == 0) 
			obj = IoDevice::Factory::createObj(name);
		if (obj == 0) 
			obj = Instruments::Factory::createObj(name);
		if (obj == 0) 
			obj = Dynamics::Factory::createObj(name);
		if (obj == 0) 
			obj = Sensor::Factory::createObj(name);
		if (obj == 0) 
			obj = Otw::Factory::createObj(name);
		if (obj == 0) 
			obj = Network::Dis::Factory::createObj(name);
		if (obj == 0) 
			obj = BasicGL::Factory::createObj(name);
		if (obj == 0) 
			obj = Glut::Factory::createObj(name);
		if (obj == 0) 
			obj = Basic::Factory::createObj(name);

		return obj;
	}
}  // end namespace Eaagles

