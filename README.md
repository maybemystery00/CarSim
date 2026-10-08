# CarSim

A modular, physically motivated vehicle and internal-combustion-engine
simulation framework written in C.

CarSim is an educational and experimental project focused on understanding
vehicle dynamics, internal-combustion engines, numerical simulation, and
automotive control systems by implementing the underlying models from the
ground up.

The long-term goal is to build a simulation environment capable of modelling
a vehicle from the engine and combustion process all the way through the
drivetrain, tyres, vehicle dynamics, sensors, actuators, and control systems.

---

## Project Status

**Early development.**

The project is currently in the foundation stage.

The current implementation contains:

- A simulation clock
- A fixed simulation timestep
- A basic vehicle state
- Four wheels
- Vehicle mass
- Throttle input
- Brake input
- Clutch input
- Gear state
- Drive force
- Braking force
- Longitudinal acceleration
- Vehicle speed
- Basic numerical time integration

The current vehicle model is intentionally simplified.

It is not yet an engine simulator, tyre simulator, or complete vehicle
simulator.

The purpose of the current stage is to establish the architecture and
numerical foundations on which progressively more detailed physical models
can be built.

---

# Goals

The long-term goal of CarSim is to provide a modular environment for
experimenting with physical models and automotive control systems.

The framework is intended to eventually support:

- Internal-combustion engine simulation
- Engine rotational dynamics
- Combustion modelling
- Air and fuel systems
- Thermodynamic modelling
- Drivetrain simulation
- Gearbox and clutch modelling
- Differential modelling
- Wheel rotational dynamics
- Tyre models
- Longitudinal vehicle dynamics
- Thermal systems
- Sensors and actuators
- Electronic control systems
- Numerical integration
- Data logging
- Visualisation
- Model validation
- Fault injection
- Experimental and educational control-system development

The project is not intended to become a collection of disconnected formulas.

The goal is to create a coherent simulation architecture in which individual
physical models interact with each other.

---

# Design Philosophy

CarSim follows several principles.

## 1. Build from the inside out

The project will gradually progress from simple physical relationships to
more detailed models.

For example:

```text
Simple force model
        ↓
Vehicle dynamics
        ↓
Wheel dynamics
        ↓
Tyre model
        ↓
Drivetrain
        ↓
Engine
        ↓
Combustion
        ↓
Thermal systems
        ↓
Control systems