# control_system
- The control_system project focuses on the generic control system alogrithm, implementation, and the corresponding unit tests (google test) in C++.
- The project scope also includes the simulation modeling mainly to verify the algorithm of the controllers.
- Gnuplot is used for data visualization of the results.

## Outline
A. Algorithm and Implementation
1. Data processing
	- [x] Saturation
	- [ ] Interpolation
		- [x] 1D
		- [ ] 2D
	- [ ] Optimization
		- [ ] Local minimum
		- [ ] Global minimum
	- [ ] State Estimation and filter
		- [ ] Low pass filter
		- [ ] Moving average filter
		- [ ] Kalman filter
2. Controller
	- [ ] PID controller
		- [x] Generic PID with default integral holding
		- [ ] With integral anti-windup
			- [ ] Clamped
			- [ ] Backward-calculation
		- [ ] With gain scheduling
	- [ ] Linear quadratic regulator (LQR)
	- [ ] Model predictive control (MPC)
3. Modeling
	- [ ] Transfer function
	- [ ] State space
		- [x] Mass-spring-damper system
		- [x] Vehicle kinematic model
		- [ ] Vehicle dynamic model
	- [ ] System identification
4. Solver
	- [x] Euler's method

B. Unit testing using Googel Test

C. System integration
- [x] Mass-spring-damper system with PID controller
