#include <limits>
#include <algorithm>

#include "pid.h"


//TODO(C++17) This will be part of C++17, replace it then
template <typename T>
T clamp(T in, T low, T high) {
    return std::min(std::max(in, low), high);
}

PIDController::PIDController
	(double kp, double ki, double kd, double minout, double maxout, double initialOut)
	: m_kp(kp), m_ki(ki), m_kd(kd), m_minout(minout), m_maxout(maxout), m_output(initialOut) {}


PIDController::PIDController(double kp, double ki, double kd)
	: PIDController::PIDController(kp, ki, kd,
			std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 0) {}


// Updates state of the controller using input variable and
// updates the output.
// deltaTime is in miliseconds
void PIDController::update(long deltaTime) {
	if (this->m_reset) {
		// Reset is done in two cases, at initial start and after PID controller
		// was disconnected from the system.
		this->m_lastInput = this->m_input;
		this->m_iTerm = this->m_output;
		this->m_reset = false;
	}

	if (deltaTime <= 0){
		return;
	}

	double err = this->m_target - this->m_input; // Calucate current error
	double dtime = deltaTime / 1000.0; // Delate time in seconds

	this->m_iTerm = this->m_iTerm + this->m_ki * err * dtime; // Calculate integrative error
	this->m_iTerm = clamp(this->m_iTerm, this->m_minout, this->m_maxout); // Clamp it

	// Calculate derivative from last step
	// Normally the derivative of error is used but it has some problems
	// If the target is moved then the derivative or error is just plain old wrong
	// As it turns out derivative of input is equal derivative of error
	// unless target is moved, if it is moved the derivative of input is still right.
	// This is just what we want.
	double dinput = (this->m_input - this->m_lastInput) / dtime;


	// Calculate total ouput, as differential term is to prevent overshooting
	// the higher is it the lower should be the ouput, that is why it is negative
	this->m_output = this->m_kp * err + this->m_iTerm - this->m_kd * dinput;
	this->m_output = clamp(this->m_output, this->m_minout, this->m_maxout); // Clamp it

	this->m_lastInput = this->m_input; // Update last input for calucation of derivative term
}
