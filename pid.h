#ifndef PID_H
#define PID_H


class PIDController {

	private:
	// Configuration variables
	double m_kp, m_ki, m_kd;
	double m_minout;
	double m_maxout;
	double m_input, m_target, m_output = 0;

	// State variables
	double m_lastInput = 0;
	double m_iTerm = 0;
	double m_cumErr = 0;

	bool m_reset = true;

	public:
	PIDController(double kp, double ki, double kd, double minout, double maxout,
			double initialOut);
	PIDController(double kp, double ki, double kd);

	// Changes the target
	void target(double tg) {
		this->m_target = tg;
	}
	double target() {
		return this->m_target;
	}

	// Sets input
	void input(double in) {
		this->m_input = in;
	}

	// Gets computer value of output
	double output() {
		return this->m_output;
	}

	// Pauses the controller, as it was disconnected from the system.
	virtual void pause() {
		this->m_reset = true;
	}

	// Updates state of the controller using input variable and
	// updates the output.
	// deltaTime is in miliseconds
	void update(long deltaTime);

};

#endif
