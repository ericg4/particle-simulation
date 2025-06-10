cmake_minimum_required(VERSION 3.16)
project(ParticleSimulation)

add_executable(particle_simulation src/main.cpp src/Particle.cpp src/ParticleSystem.cpp src/utils/color.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML REQUIRED COMPONENTS Graphics Window System)

target_link_libraries(particle_simulation SFML::Graphics SFML::Window SFML::System)

target_include_directories(particle_simulation PRIVATE include)