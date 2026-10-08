# CarSim

A modular, physically motivated vehicle and internal-combustion-engine simulation framework written in C.

CarSim is an educational and experimental project focused on understanding vehicle dynamics, internal-combustion engines, numerical simulation, and automotive control systems by implementing the underlying models from the ground up.

The long-term goal is to build a simulation environment capable of modelling a vehicle from the engine and combustion process all the way through the drivetrain, tyres, vehicle dynamics, sensors, actuators, and control systems.

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

It is not yet an engine simulator, tyre simulator, or complete vehicle simulator.

The purpose of the current stage is to establish the architecture and numerical foundations on which progressively more detailed physical models can be built.

---

# Goals

The long-term goal of CarSim is to provide a modular environment for experimenting with physical models and automotive control systems.

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

The goal is to create a coherent simulation architecture in which individual physical models interact with each other.

---

# Design Philosophy

CarSim follows several principles.

## 1. Build from the inside out

The project will gradually progress from simple physical relationships to more detailed models.

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
```

The system should not attempt to simulate everything at once.

---

## 2. One subsystem at a time

Development follows an incremental process:

1. Understand the physical concept.
2. Understand the mathematical model.
3. Implement the smallest useful version.
4. Compile the program.
5. Test the behaviour.
6. Verify the result.
7. Commit the working milestone.
8. Move to the next subsystem.

This prevents the project from becoming a large collection of unverified models.

---

## 3. Understand the mathematics

Equations should not be treated as magic formulas.

Whenever a physical equation is introduced, the objective is to understand:

- What each variable represents
- What units the variable has
- Why the equation is physically meaningful
- What assumptions are being made
- How the equation becomes executable code
- What limitations the model has

For example, the current vehicle model uses Newton's second law:

```text
F = ma
```

which can be rearranged as:

```text
a = F / m
```

The simulation then uses numerical integration to update velocity:

```text
v_new = v_old + a × dt
```

The objective is not merely to implement the equation, but to understand the relationship between the physical system and the numerical model.

---

# Numerical Simulation

A physical vehicle exists in continuous time.

A computer simulation, however, normally evaluates the system at discrete simulation steps.

For example:

```text
t = 0.00 s
t = 0.01 s
t = 0.02 s
t = 0.03 s
...
```

The difference between consecutive simulation times is the timestep:

```text
dt
```

The simulation therefore repeatedly performs an update:

```text
current state
      ↓
calculate physical behaviour
      ↓
update state
      ↓
advance simulation time
      ↓
repeat
```

---

## Euler Integration

The initial numerical integration method used by CarSim is Euler integration.

For velocity:

```text
dv/dt = a
```

Euler integration approximates this as:

```text
v_new = v_old + a × dt
```

This is currently sufficient because the purpose is to understand the numerical process before introducing more sophisticated solvers.

Future versions may support:

- Improved Euler methods
- Runge-Kutta methods
- RK4
- Adaptive timestep methods
- General ODE solvers

More advanced numerical methods should only be introduced when they are actually required by the models.

---

# Current Vehicle Model

The current vehicle model is intentionally simple.

The current physical chain is:

```text
Throttle
   ↓
Drive force
   ↓
Net force
   ↓
Acceleration
   ↓
Numerical integration
   ↓
Vehicle speed
```

Braking introduces an opposing force:

```text
Throttle ─────→ Drive force ──┐
                              ↓
                         Net force
                              ↓
                            F / m
                              ↓
                        Acceleration
                              ↓
                         Speed update

Brake ────────→ Brake force ─┘
```

---

# Current Vehicle State

The vehicle currently contains the following conceptual state:

```text
Car
├── Wheels[4]
├── Speed
├── Mass
├── Throttle
├── Brake
├── Clutch
├── Gear
├── Drive force
└── Acceleration
```

The four wheels are currently represented individually because future systems such as ABS, traction control, differential modelling, and tyre dynamics will require independent wheel states.

The current wheel representation contains angular velocity.

---

# Units

CarSim uses SI units wherever practical.

| Quantity | Unit |
|---|---|
| Time | seconds (s) |
| Timestep | seconds (s) |
| Distance | metres (m) |
| Speed | metres per second (m/s) |
| Acceleration | metres per second squared (m/s²) |
| Mass | kilograms (kg) |
| Force | newtons (N) |
| Torque | newton-metres (N·m) |
| Angular velocity | radians per second (rad/s) |
| Angular acceleration | radians per second squared (rad/s²) |
| Power | watts (W) |
| Temperature | °C or K, depending on the model |

Using consistent units is important because the simulator will eventually combine models from many different physical domains.

---

# Current Physical Equations

## Newton's Second Law

The fundamental equation currently used for vehicle longitudinal dynamics is:

```text
F = ma
```

Therefore:

```text
a = F / m
```

where:

- `F` is net longitudinal force
- `m` is vehicle mass
- `a` is longitudinal acceleration

---

## Vehicle Speed Integration

The current numerical update is:

```text
v_new = v_old + a × dt
```

where:

- `v_old` is the previous vehicle speed
- `a` is the calculated acceleration
- `dt` is the simulation timestep
- `v_new` is the new vehicle speed

---

## Drive Force

The current drive-force model is deliberately simplified.

The initial model uses:

```text
F_drive = F_max × throttle
```

where:

- `F_drive` is the longitudinal driving force
- `F_max` is a hypothetical maximum driving force
- `throttle` is a normalized input between 0 and 1

This is **not intended to represent a real engine**.

It is a temporary model used to establish the simulation architecture.

A future engine/drivetrain model will replace this relationship.

---

## Brake Force

The initial braking model uses:

```text
F_brake = F_brake_max × brake
```

where:

- `F_brake` is braking force
- `F_brake_max` is the assumed maximum braking force
- `brake` is a normalized brake input

The longitudinal net force is then approximately:

```text
F_net = F_drive - F_brake
```

and:

```text
a = F_net / m
```

This model intentionally ignores tyre slip, tyre-road friction limits, brake pressure dynamics, brake torque, wheel lock-up, ABS, weight transfer, and other real vehicle effects.

Those systems will be introduced later.

---

# Input Conventions

Driver inputs are represented using normalized values.

## Throttle

```text
0.0 = 0%
1.0 = 100%
```

For example:

```c
car.throttle = 0.0;
```

means no throttle.

```c
car.throttle = 1.0;
```

means full throttle.

---

## Brake

The same convention is used for braking:

```text
0.0 = no braking
1.0 = maximum braking input
```

---

## Clutch

The clutch input is reserved for future drivetrain modelling.

The exact physical interpretation will be defined when the clutch model is implemented.

---

## Gear

The gear state will eventually represent:

```text
-1 = reverse
 0 = neutral
 1 = first gear
 2 = second gear
 ...
```

The gearbox model has not yet been implemented.

---

# Planned Architecture

The eventual architecture is intended to look approximately like:

```text
                    Driver / Inputs
                           │
                           ▼
                    Controller / ECU
                           │
                           ▼
                       Actuators
                           │
                           ▼
                         Engine
                           │
                           ▼
                       Drivetrain
                           │
                           ▼
                         Wheels
                           │
                           ▼
                          Tyres
                           │
                           ▼
                        Vehicle
                           │
                           ▼
                       Environment
                           │
                           ▼
                        Sensors
                           │
                           └──────────────► Controller
```

The actual implementation will evolve as the project grows.

The architecture should avoid tightly coupling unrelated subsystems.

For example, the engine should not directly depend on the renderer.

Similarly, a controller should interact with the physical system through defined state, sensor, and actuator interfaces rather than directly modifying arbitrary internal variables.

---

# Planned Subsystems

The following subsystems are planned for the long-term project.

They will **not** all be implemented immediately.

---

# Engine

The engine model is intended to eventually progress from a simple rotational model to a detailed internal-combustion model.

Planned areas include:

- Crankshaft
- Rotational inertia
- Piston motion
- Connecting rod geometry
- Crank geometry
- Cylinder volume
- Crank angle
- Intake valve behaviour
- Exhaust valve behaviour
- Throttle
- Manifold pressure
- Airflow
- Volumetric efficiency
- Fuel injection
- Injector behaviour
- AFR
- Lambda
- Compression
- Combustion
- Heat release
- Ignition timing
- Cylinder pressure
- Indicated work
- Indicated torque
- Friction losses
- Pumping losses
- Accessory losses
- Exhaust flow
- Exhaust temperature
- Heat transfer
- Knock
- Turbocharging
- Supercharging
- Intercooling

The engine model will likely evolve through multiple levels of complexity.

For example:

```text
Simple torque model
        ↓
RPM-dependent torque model
        ↓
Mean-value engine model
        ↓
Crank-angle-resolved model
        ↓
Detailed thermodynamic model
        ↓
Optional chemistry integration
```

---

# Engine Rotational Dynamics

A fundamental future equation is:

```text
J × dω/dt = T_engine - T_load
```

where:

- `J` is rotational inertia
- `ω` is angular velocity
- `T_engine` is engine torque
- `T_load` is opposing torque

This will allow engine speed to emerge from torque balance rather than being artificially assigned.

---

# Combustion

Eventually the framework may model combustion at the cylinder level.

Potential quantities include:

- Cylinder volume
- Pressure
- Temperature
- Crank angle
- Air mass
- Fuel mass
- Air-fuel ratio
- Ignition timing
- Heat release
- Combustion duration
- Work produced

A future combustion model may use simplified empirical models before moving towards more detailed thermodynamic or chemical models.

---

# Cantera Integration

Cantera may eventually be used for specialized thermochemical calculations.

Potential applications include:

- Chemical equilibrium
- Thermodynamic properties
- Chemical kinetics
- Species calculations
- Combustion chemistry

Cantera is intended to be a specialized component rather than the entire simulation architecture.

CarSim should retain ownership of the overall simulation state and system architecture.

The project should not simply become a wrapper around Cantera.

---

# Drivetrain

The drivetrain will eventually connect engine torque to the wheels.

Planned components include:

- Clutch
- Gearbox
- Gear ratios
- Differential
- Driveshaft
- Final drive
- Drivetrain losses
- Wheel rotational dynamics

A simplified future torque relationship may look like:

```text
Engine torque
      ↓
Clutch
      ↓
Gearbox
      ↓
Final drive
      ↓
Differential
      ↓
Wheels
```

A simplified torque relationship may eventually resemble:

```text
T_wheel = T_engine × G × F × η
```

where:

- `G` is the selected gear ratio
- `F` is the final-drive ratio
- `η` is drivetrain efficiency

The actual model will account for the appropriate physical assumptions.

---

# Wheel Dynamics

Each wheel will eventually have independent rotational dynamics.

A basic future equation may take the form:

```text
I_wheel × dω/dt = T_wheel - T_tyre
```

where:

- `I_wheel` is wheel rotational inertia
- `ω` is wheel angular velocity
- `T_wheel` is applied wheel torque
- `T_tyre` is tyre-road resisting torque

Independent wheel states are important for:

- ABS
- Traction control
- Differential modelling
- Tyre slip
- Wheel lock-up
- Wheel spin

---

# Tyre Model

The tyre model is one of the most important future components.

Planned concepts include:

- Longitudinal slip
- Lateral slip
- Road friction
- Normal load
- Friction limits
- Combined slip
- Tyre force
- Wheel rotational speed

The first tyre model will likely be intentionally simple.

More advanced tyre models can be added later.

Potential progression:

```text
Simple friction limit
        ↓
Longitudinal slip model
        ↓
Nonlinear friction curve
        ↓
Combined longitudinal/lateral model
        ↓
More advanced tyre model
```

---

# Vehicle Dynamics

The vehicle model will eventually account for:

- Vehicle mass
- Longitudinal force
- Aerodynamic drag
- Rolling resistance
- Gravity
- Road gradient
- Weight transfer
- Wheel forces
- Tyre forces

A simplified future longitudinal model may eventually become:

```text
m × dv/dt = F_drive - F_brake - F_drag - F_roll - F_grade
```

This will replace the current simplified force model as the physical model becomes more sophisticated.

---

# Aerodynamics

Future aerodynamic modelling may include:

```text
F_drag = 1/2 × ρ × C_d × A × v²
```

where:

- `ρ` is air density
- `C_d` is drag coefficient
- `A` is frontal area
- `v` is vehicle speed

Future aerodynamic models may also include downforce.

---

# Rolling Resistance

Rolling resistance will eventually be modelled as an opposing force.

The exact model will depend on the desired level of physical detail.

The model may eventually account for:

- Vehicle load
- Tyre properties
- Speed
- Road conditions

---

# Thermal Systems

Thermal modelling will eventually be treated as a dynamic physical system.

Potential systems include:

- Engine temperature
- Coolant temperature
- Oil temperature
- Cylinder-head temperature
- Radiator
- Cooling fan
- Heat transfer
- Thermal inertia

A simplified thermal balance may eventually use:

```text
C × dT/dt = Q_generated - Q_lost
```

where:

- `C` is thermal capacity
- `T` is temperature
- `Q_generated` is generated heat
- `Q_lost` is heat removed from the system

---

# Control Systems

Control systems are a major long-term goal of the project.

Planned systems include:

- ECU
- Throttle control
- Fuel control
- Ignition control
- Idle control
- Cruise control
- ABS
- Traction control
- Cooling control

The framework should allow controllers to operate on simulated sensor data rather than directly accessing hidden physical state.

---

# ABS

A future ABS system will use wheel speed and vehicle speed to estimate wheel slip.

A simplified longitudinal slip relationship may be:

```text
slip = (R × ω - v) / v
```

with appropriate handling near zero vehicle speed.

The ABS controller will eventually:

1. Measure wheel speed.
2. Estimate slip.
3. Detect excessive wheel slip.
4. Reduce brake pressure.
5. Allow the wheel to recover.
6. Increase brake pressure again.
7. Repeat the control process.

Potential control mechanisms include:

- Threshold control
- Hysteresis
- Bang-bang control
- PID-based control
- More advanced control strategies

---

# Traction Control

Traction control will eventually use wheel slip to detect excessive wheel spin during acceleration.

A simplified control loop will be:

```text
Wheel speed
     ↓
Slip estimation
     ↓
Slip threshold
     ↓
Controller
     ↓
Throttle / torque reduction
     ↓
Wheel slip reduction
```

---

# PID Controllers

The framework will eventually support generic control algorithms such as:

```text
P
PI
PID
```

A PID controller can be represented conceptually as:

```text
u(t) = Kp × e(t)
     + Ki × integral(e(t))
     + Kd × derivative(e(t))
```

The implementation should be separated from the physical system so that the same controller infrastructure can potentially be used for:

- Cruise control
- Temperature control
- Idle control
- Boost control
- Other experimental systems

---

# Hysteresis

Hysteresis will be useful for systems that should not rapidly switch between states.

For example:

```text
Fan ON  above 95°C
Fan OFF below 90°C
```

rather than switching at exactly one temperature.

Similar approaches may eventually be used for:

- ABS logic
- Cooling fans
- Traction control
- State machines
- Threshold-based controllers

---

# Sensors

Sensors will eventually become separate simulation components.

Potential sensors include:

- Wheel-speed sensors
- Engine-speed sensor
- Throttle-position sensor
- Manifold-pressure sensor
- Temperature sensors
- Oxygen sensors
- Vehicle-speed sensor
- Pressure sensors

The sensor system may eventually include:

- Noise
- Bias
- Quantization
- Latency
- Sampling rate
- Sensor failure
- Intermittent faults

This is important because a real controller does not have perfect access to the true internal physical state of a vehicle.

---

# Actuators

Actuators will eventually represent the physical interface between control systems and the vehicle.

Potential actuators include:

- Electronic throttle
- Fuel injector
- Ignition system
- Brake actuator
- Cooling fan
- Wastegate
- Variable valve mechanisms

Actuators may eventually include:

- Response delay
- Saturation
- Rate limits
- Nonlinear behaviour
- Failure modes

---

# Fault Injection

A long-term objective is to make the simulator useful for control-system experimentation.

Possible faults include:

- Failed sensor
- Noisy sensor
- Sensor bias
- Stuck actuator
- Delayed actuator
- Intermittent signal
- Incorrect sensor reading
- Communication failure

This could eventually allow control algorithms to be tested under abnormal conditions.

---

# Data and Parameters

Initially, CarSim does not require real-world test data.

Physically meaningful hypothetical parameters are acceptable during early development.

For example:

```text
Vehicle mass        = 1200 kg
Maximum drive force = 2400 N
Maximum brake force = 8000 N
```

These values are currently used to develop and test the simulation architecture.

They should **not** be interpreted as calibrated values for a particular real vehicle.

As the project becomes more sophisticated, parameters can be obtained from:

- Published specifications
- Engineering references
- Published physical correlations
- Open-source models
- Experimental measurements
- Manufacturer data where available

---

# Model Classification

CarSim will distinguish between different types of model information.

## Theoretical Models

Models derived from fundamental physical laws.

Examples:

```text
F = ma
```

and rotational dynamics.

---

## Empirical Models

Relationships based primarily on experimental observations.

Examples may include:

- Empirical friction curves
- Efficiency correlations
- Heat-transfer correlations

---

## Assumptions

Simplifications introduced to make a model tractable.

Examples:

- Constant vehicle mass
- Constant friction coefficient
- Simplified aerodynamic drag
- Constant maximum drive force

---

## Measured Data

Values obtained from experiments or real-world measurements.

---

## Calibrated Parameters

Parameters adjusted so that a model reproduces observed behaviour.

Keeping these categories separate is important for understanding how physically accurate a model actually is.

---

# Validation

A simulation is not considered physically trustworthy simply because the equations appear reasonable.

Models should eventually be compared against:

- Published data
- Experimental measurements
- Reference implementations
- Open-source models
- Known analytical solutions

Possible validation targets include:

- Acceleration
- Engine torque
- Engine speed
- Fuel consumption
- Cylinder pressure
- Temperature
- Wheel slip
- Braking distance
- Thermal behaviour

The project should clearly distinguish between:

```text
"The model predicts this."
```

and:

```text
"This has been validated against real data."
```

---

# Modularity

A major architectural objective is that models should be replaceable.

For example, the engine subsystem should eventually allow:

```text
Simple Engine
     ↓
Mean-Value Engine
     ↓
Crank-Angle Engine
     ↓
Detailed Engine
```

without requiring the entire vehicle simulator to be rewritten.

Similarly:

```text
Simple Tyre
     ↓
Slip Tyre
     ↓
Advanced Tyre
```

and:

```text
Rule-Based Controller
     ↓
PID Controller
     ↓
Advanced Controller
```

The rest of the simulation should interact with well-defined interfaces rather than relying on the internal implementation of a specific model.

---

# Project Structure

The project will gradually evolve towards a structure similar to:

```text
CarSim/
│
├── src/
│   ├── simulation/
│   ├── engine/
│   ├── combustion/
│   ├── intake/
│   ├── fuel/
│   ├── thermal/
│   ├── drivetrain/
│   ├── vehicle/
│   ├── tyres/
│   ├── control/
│   ├── sensors/
│   ├── actuators/
│   ├── numerical/
│   └── logging/
│
├── include/
│   └── corresponding headers
│
├── tests/
│
├── data/
│   ├── engine/
│   ├── vehicle/
│   └── experimental/
│
├── docs/
│
├── README.md
├── Makefile
├── LICENSE
└── .gitignore
```

This structure is a long-term target.

Directories should only be introduced when their corresponding subsystem actually becomes necessary.

---

# Current Source Structure

At the current development stage, the project is intentionally much smaller.

The basic structure is:

```text
CarSim/
│
├── src/
│   ├── main.c
│   ├── simulation.c
│   └── car.c
│
├── include/
│   ├── simulation.h
│   └── car.h
│
├── tests/
│
├── docs/
│
├── Makefile
├── README.md
├── LICENSE
└── .gitignore
```

---

# Core Modules

## Simulation

The simulation module owns global simulation time.

Conceptually:

```c
typedef struct
{
    double time;
    double dt;
} Simulation;
```

The simulation clock is separate from the physical state of the car.

---

## Car

The car module owns vehicle state.

The current model contains:

- Speed
- Mass
- Throttle
- Brake
- Clutch
- Gear
- Drive force
- Acceleration
- Four wheels

The car update function advances the physical state by one timestep.

---

# Separation of Responsibilities

The project deliberately separates simulation time from physical models.

For example:

```text
Simulation
    ↓
provides dt
    ↓
Car
    ↓
updates physical state
```

The car does not need to own the global simulation clock.

This separation will become increasingly important when the simulator contains many interacting subsystems.

---

# Build System

CarSim currently uses a simple Makefile with GCC.

A typical build command is:

```bash
make
```

The resulting executable is:

```text
carsim.exe
```

The program can be executed with:

```bash
./carsim.exe
```

The project currently targets a Windows development environment using GCC through MSYS2.

---

# Compiler

The project currently uses:

```text
GCC
```

The code is intended to remain portable C wherever practical.

Platform-specific functionality should be isolated rather than spread throughout the physics code.

---

# Development Workflow

The recommended development cycle is:

```text
Understand
    ↓
Design
    ↓
Implement
    ↓
Compile
    ↓
Test
    ↓
Verify
    ↓
Commit
    ↓
Repeat
```

Each commit should represent a meaningful working milestone.

Example commits:

```text
Initialize CarSim project
Add simulation clock
Add basic car and wheel model
Add basic force and acceleration model
Add throttle driven vehicle acceleration
Add basic braking force
```

---

# Testing Philosophy

Testing should begin simple.

For every new physical model, test known cases.

For example:

### Zero Force

```text
F = 0
```

should produce:

```text
a = 0
```

### Positive Force

```text
F > 0
```

should produce:

```text
a > 0
```

### Larger Mass

For the same force:

```text
larger mass → smaller acceleration
```

### Braking

A braking force opposing motion should produce:

```text
negative acceleration
```

### Numerical Timestep

Changing the timestep should change the numerical approximation but should not fundamentally change the intended physical behaviour when the integration method is sufficiently accurate.

More rigorous numerical tests will be introduced as the simulator grows.

---

# Future Testing

Eventually the project may contain automated tests for:

- Physics equations
- Numerical integration
- Engine models
- Drivetrain models
- Tyre models
- Controllers
- Sensor models
- Thermal systems

Regression tests will help ensure that improving one subsystem does not silently break another.

---

# Visualisation

The core simulator should remain independent of rendering.

The long-term architecture may use a separate visualisation layer.

For example:

```text
Simulation
    ↓
State
    ↓
Logger / Renderer
```

Possible future visualisation technologies include lightweight graphical libraries such as raylib.

The renderer should not determine how the physical simulation works.

This allows the simulator to run:

- Headless
- In a terminal
- For automated tests
- For data generation
- With a graphical interface

---

# Logging

A future logging subsystem will allow simulation data to be recorded.

Potential logged quantities include:

```text
Time
Vehicle speed
Acceleration
Throttle
Brake
Engine RPM
Engine torque
Wheel speed
Tyre slip
Temperature
Pressure
Fuel flow
Lambda
Controller output
```

Data may eventually be exported to formats suitable for external analysis and plotting.

---

# Model Complexity

CarSim will intentionally support multiple levels of model complexity.

A simple model is not automatically a bad model.

For example, a simple tyre model can be useful for learning vehicle dynamics before introducing a complex nonlinear tyre model.

The important requirement is to clearly state the assumptions and limitations of each model.

---

# External Libraries

CarSim may use established open-source libraries when they provide specialized functionality that would be unreasonable to reimplement.

Potential examples include:

- Cantera for thermochemistry and chemical kinetics
- Numerical libraries for advanced ODE solving
- Other specialized scientific libraries where appropriate

However, external libraries should complement the framework rather than replace its architecture.

The project should retain direct understanding and implementation of the important physical and software concepts.

---

# What CarSim Is Not

CarSim is not initially intended to be:

- A commercial vehicle simulator
- A complete CFD package
- A professional engine-development tool
- A replacement for dedicated combustion software
- A game engine
- A graphical driving game
- A wrapper around Cantera
- A collection of disconnected physics equations

The primary purpose is learning, experimentation, modelling, and control-system development.

---

# Long-Term Vision

The ultimate goal is to reach a point where the simulator can represent a complete vehicle system.

A possible final high-level flow is:

```text
                    DRIVER
                       │
                       ▼
                  INPUT SYSTEM
                       │
                       ▼
                CONTROL SYSTEMS
                  /    │    \
                 /     │     \
              ECU     ABS     TCS
                │       │       │
                ▼       │       │
             ACTUATORS  │       │
                │       │       │
                ▼       ▼       ▼
              ENGINE ← CONTROLLERS
                │
                ▼
             CLUTCH
                │
                ▼
            GEARBOX
                │
                ▼
           DIFFERENTIAL
                │
                ▼
              WHEELS
                │
                ▼
              TYRES
                │
                ▼
             VEHICLE
                │
                ▼
            ENVIRONMENT
                │
                ▼
             SENSORS
                │
                └──────────────► CONTROL SYSTEMS
```

Inside the engine, the eventual model may become:

```text
Throttle
    ↓
Air intake
    ↓
Manifold
    ↓
Airflow
    ↓
Cylinder filling
    ↓
Fuel injection
    ↓
AFR / Lambda
    ↓
Compression
    ↓
Ignition
    ↓
Combustion
    ↓
Heat release
    ↓
Cylinder pressure
    ↓
Piston force
    ↓
Crankshaft torque
    ↓
Engine rotational dynamics
```

This is a long-term objective, not the current implementation.

---

# Development Roadmap

The roadmap is intentionally flexible.

## Phase 1 — Simulation Foundation

- [x] Project structure
- [x] Simulation clock
- [x] Fixed timestep
- [x] Basic car state
- [x] Four-wheel representation
- [x] Vehicle mass
- [x] Drive force
- [x] Newton's second law
- [x] Basic Euler integration
- [x] Throttle input
- [x] Basic braking force

---

## Phase 2 — Basic Vehicle Dynamics

Planned:

- [ ] Prevent physically invalid negative forward speed
- [ ] Rolling resistance
- [ ] Aerodynamic drag
- [ ] Road gradient
- [ ] More explicit net-force model
- [ ] Better vehicle state organisation
- [ ] Basic wheel radius
- [ ] Wheel rotational speed

---

## Phase 3 — Drivetrain

Planned:

- [ ] Engine shaft
- [ ] Clutch
- [ ] Gearbox
- [ ] Gear ratios
- [ ] Final drive
- [ ] Differential
- [ ] Driveshaft
- [ ] Drivetrain efficiency
- [ ] Wheel torque

---

## Phase 4 — Engine

Planned:

- [ ] Engine rotational inertia
- [ ] Engine speed
- [ ] Torque generation
- [ ] Torque curve
- [ ] Throttle influence
- [ ] Engine load
- [ ] Idle behaviour

---

## Phase 5 — Improved Engine Physics

Planned:

- [ ] Crank geometry
- [ ] Piston motion
- [ ] Cylinder volume
- [ ] Intake
- [ ] Exhaust
- [ ] Manifold pressure
- [ ] Airflow
- [ ] Volumetric efficiency
- [ ] Fuel injection
- [ ] AFR
- [ ] Combustion
- [ ] Heat release
- [ ] Ignition timing
- [ ] Cylinder pressure
- [ ] Indicated work
- [ ] Friction losses
- [ ] Pumping losses

---

## Phase 6 — Thermal Systems

Planned:

- [ ] Engine heat generation
- [ ] Coolant model
- [ ] Oil model
- [ ] Radiator
- [ ] Heat transfer
- [ ] Thermal inertia
- [ ] Cooling fan
- [ ] Temperature control

---

## Phase 7 — Tyres and Advanced Vehicle Dynamics

Planned:

- [ ] Wheel slip
- [ ] Longitudinal tyre force
- [ ] Road friction
- [ ] Normal load
- [ ] Weight transfer
- [ ] Advanced friction models
- [ ] Lateral dynamics
- [ ] Combined slip

---

## Phase 8 — Control Systems

Planned:

- [ ] Sensor framework
- [ ] Actuator framework
- [ ] ECU architecture
- [ ] Throttle control
- [ ] Fuel control
- [ ] Ignition control
- [ ] Idle control
- [ ] Cruise control
- [ ] PID controllers
- [ ] Hysteresis
- [ ] ABS
- [ ] Traction control

---

## Phase 9 — Faults and Validation

Planned:

- [ ] Sensor noise
- [ ] Sensor latency
- [ ] Sensor failures
- [ ] Actuator failures
- [ ] Fault injection
- [ ] Reference-model comparison
- [ ] Experimental validation
- [ ] Automated regression testing

---

## Phase 10 — Advanced Models

Potential future work:

- [ ] Turbocharger
- [ ] Supercharger
- [ ] Intercooler
- [ ] Variable valve timing
- [ ] Detailed combustion
- [ ] Cantera integration
- [ ] Advanced numerical solvers
- [ ] Adaptive timesteps
- [ ] Advanced tyre models
- [ ] More complete thermal networks
- [ ] Advanced control algorithms

---

# Educational Purpose

CarSim is being developed as a practical way to learn several subjects simultaneously.

## Physics

- Newtonian mechanics
- Rotational dynamics
- Thermodynamics
- Fluid mechanics
- Heat transfer
- Combustion
- Friction
- Vehicle dynamics

## Mathematics

- Algebra
- Differential equations
- Numerical integration
- Functions
- Numerical methods
- Control theory
- Data analysis

## Computer Science

- C programming
- Structs
- Functions
- Modular design
- Headers
- Compilation
- Build systems
- Memory management
- Testing
- Version control

## Automotive Engineering

- Engines
- Drivetrains
- Tyres
- Braking
- ABS
- Traction control
- Sensors
- ECUs
- Thermal management

---

# Philosophy of the Project

The project is deliberately being built from simple models towards complex ones.

The intention is to avoid treating a sophisticated simulator as a black box.

A model should be understandable before it becomes complicated.

The progression should therefore look like:

```text
Simple physics
      ↓
Understand the equation
      ↓
Implement it
      ↓
Test it
      ↓
Identify its limitations
      ↓
Improve the model
      ↓
Validate it
```

The simulator should become more realistic because the underlying models become better—not simply because more code is added.

---

# License

CarSim is released under the MIT License.

See [LICENSE](LICENSE) for the full license text.

---

# Author

**Mayukh Sahu**

CarSim is being developed as a long-term personal project combining:

- C programming
- Physics
- Automotive engineering
- Numerical simulation
- Control systems
- Computational modelling

The project is intentionally being developed incrementally, with the goal of understanding the underlying systems rather than simply assembling existing simulation software.

---

# Status

CarSim is an active early-stage project.

The architecture and physical models are expected to evolve substantially as new concepts are introduced and tested.

The current implementation should therefore be considered experimental and educational rather than a validated engineering simulation.
```