#include "TestHsi.h"

namespace Eaagles {

	IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestHsi,"TestHsi")
	EMPTY_SERIALIZER(TestHsi)

	TestHsi::TestHsi() {
			STANDARD_CONSTRUCTOR()
			heading = 0;
			headingSD.empty();
			headingRate = 20;
			headingROSD.empty();
			dme = 0;
			dmeROSD.empty();
	}

	void TestHsi::copyData(const TestHsi& org, const bool)	{
		BaseClass::copyData(org);
		heading = org.heading;
    headingSD.empty();
    headingRate = org.headingRate;
    headingROSD.empty();
    dme = org.dme;
    dmeROSD.empty();
	}

	EMPTY_DELETEDATA(TestHsi)

	void TestHsi::updateData(const LCreal dt) {
		Simulation::AirVehicle* av = static_cast<Simulation::AirVehicle*>(getOwnship());
		heading = av->getHeadingD();
    send("hsi1", UPDATE_VALUE6, heading, headingSD);
		BaseClass::updateData(dt);
	}

	Simulation::Player* TestHsi::getOwnship()	{
		Simulation::Player* p = 0;
		Simulation::Station* sta = getStation();
		if (sta != 0) p = sta->getOwnship();
		return p;
	}

	Simulation::Simulation* TestHsi::getSimulation() {
	 Simulation::Simulation* s = 0;
	 Simulation::Station* sta = getStation();
	 if (sta != 0) s = sta->getSimulation();
	 return s;
	}

	Simulation::Station* TestHsi::getStation() {
	 if (myStation == 0) {
			Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
			if (s != 0) myStation = s;
	 }
	 return myStation;
	}
} // end of Eaagles namespace
