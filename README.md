# control_system
The control_system project focuses on the generic control system alogrithm, implementation, and the corresponding unit tests (google test) in C++.

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
	- [ ] System identification 

B. Unit testing using Googel Test
