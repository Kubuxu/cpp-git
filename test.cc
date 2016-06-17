#include <iostream>

#include "pid.h"

int main(int argc, char const* argv[])
{
	// Here we will simpulate PID controller controlling electric kettle
	// which is boling water. The model isn't really realistic as you ususally
	// don't controll kettle by wats but why not.

	// Our aim is to boil water for yerba mate.
	// Which means we want to initally boil  and then settle on 75C.
	// We will be boiling about 200ml (200g) of watter with 2000W kettle.

	PIDController pid(15, 2.25, 0, 0, 2000, 2000);
	pid.target(100);

	double waterHeatCap = 4.184 * 200;
	const double ambientTemp = 20;
	double waterTemp = ambientTemp;
	// 5 minutes of simulation
	// every 1 second, print every 10 seconds
	for (int i = 0; i < 20 * 60 + 1; i++) {
		// If water start to boil change target to 75C
		if (waterTemp > 95) {
			pid.target(75);
		}
		if (true || i % 10 == 0) {
			/*std::cout << "Time: " << i << " Power: " << pid.output()
				<< " Temp: " << waterTemp << " Target: " << pid.target() << std::endl;
				*/
			std::cout << waterTemp << std::endl;
		//	std::cout << pid.output() << std::endl;
		}
		// Power added to water over second divded over heat capacity
		waterTemp += (pid.output() / waterHeatCap);
		waterTemp -= 0.0003 * (waterTemp - ambientTemp)*(waterTemp - ambientTemp); // Naive heat loss
		if (waterTemp > 100) {
			waterTemp = 100;
		}
		pid.input(waterTemp);
		pid.update(1 * 1000);
	}

	return 0;
}
