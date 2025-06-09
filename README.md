# Particle Simulation

A real-time particle physics simulation built with SFML 3.x and C++. Features rainbow-colored particles with realistic gravity, mouse-controlled emission, and performance monitoring.

## Features

### 🌈 Visual Effects
- **Rainbow particle colors** - Particles cycle through the entire color spectrum
- **Smooth 60 FPS rendering** with real-time performance metrics
- **Oscillating emission patterns** - Particles spray in animated fan patterns

### ⚡ Realistic Physics
- **Gravity simulation** with proper acceleration physics
- **Mass-based dynamics** - Different particle masses for varied behavior
- **Air resistance/drag** for natural terminal velocity
- **Force-based physics system** using F = ma

### 🎮 Interactive Controls
- **Mouse-controlled emitter** - Particles follow your cursor
- **Click and hold** - Continuous particle emission while mouse button pressed
- **ESC key** - Exit the simulation

### 📊 Performance Monitoring
- **Real-time FPS display**
- **Frame time monitoring** (milliseconds per frame)
- **Active particle count**

## Dependencies

- **SFML 3.x** - Graphics and window management
- **CMake 3.16+** - Build system
- **C++17 compiler** (GCC, Clang, or MSVC)

## Installation

### macOS
```bash
# Install SFML via Homebrew
brew install sfml
```

## Building

```bash
# Clone the repository
git clone https://github.com/ericg4/particle-simulation.git
cd particle_simulation

# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Compile
make

# Run the simulation
./particle_simulation
```

## Usage

### Controls
- **Mouse Movement** - Controls particle emitter position
- **Left Mouse Button (Hold)** - Emit particles continuously
- **ESC Key** - Exit simulation

### Features in Action
- Particles spray downward with realistic gravity
- Emission angle oscillates left-to-right over time
- Colors cycle through rainbow spectrum
- Physics simulate mass, drag, and acceleration

## Project Structure

```
particle_simulation/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── Particle.cpp       # Individual particle physics
│   └── ParticleSystem.cpp # Particle management & rendering
├── include/               # Header files
│   ├── Particle.hpp       # Particle class definition
│   └── ParticleSystem.hpp # Particle system definition
├── CMakeLists.txt         # Build configuration
└── README.md             # This file
```

## Technical Details

### Physics System
- **Acceleration-based physics** with proper force integration
- **Gravity constant**: 500 pixels/second²
- **Drag coefficient**: 0.98 (2% velocity loss per frame)

### Rendering
- **HSV to RGB color conversion** for smooth rainbow transitions
- **Real-time performance metrics** displayed on screen
- **Efficient particle cleanup** (removes off-screen/dead particles)

### Performance
- **Target**: 60 FPS with hundreds of active particles
- **Optimizations**: Vector-based particle storage, efficient collision detection
- **Memory management**: Automatic cleanup of expired particles

## Customization

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is open source. Feel free to use and modify!

## Acknowledgments

- Built with [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library
- Inspired by real-time particle physics simulations