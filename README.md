# control_system
The control_system project focuses on the generic control system alogrithm, implementation, and the corresponding unit tests (google test) in C++.

## Outline
**A. Algorithm and Implementation**
	1. Data processing
		a. [x]Saturation
		b. Interpolation
			- [x]1D
			- [ ]2D
		c. Optimization
			- [ ]Local minimum
			- [ ]Global minimum
		d. State Estimation and filter
			- [ ]Low pass filter
			- [ ]Moving average filter
			- [ ]Kalman filter
	2. Controller
		a. PID controller
			aa. Generic
				- [x]Default integral holding
			bb. With integral anti-windup
				- [ ]Clamped
				- [ ]Backward-calculation
			cc. [ ]With gain scheduling
		b. [ ]Linear quadratic regulator (LQR)
		c. [ ]Model predictive control (MPC)
	3. Modeling
		a. [ ]Transfer function
		b. [ ]State space
		c. [ ]System identification 
	4. Unit testing using Googel Test

