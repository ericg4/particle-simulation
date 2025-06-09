#define _USE_MATH_DEFINES
#include "../include/ParticleSystem.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>

constexpr float PI = 3.14159265358979323846f;

sf::Color hsvToRgb(float h, float s, float v) {
    float c = v * s;
    float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;
    
    float r, g, b;
    
    if (h >= 0 && h < 60) {
        r = c; g = x; b = 0;
    } else if (h >= 60 && h < 120) {
        r = x; g = c; b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0; g = c; b = x;
    } else if (h >= 180 && h < 240) {
        r = 0; g = x; b = c;
    } else if (h >= 240 && h < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }
    
    return sf::Color(
        static_cast<unsigned char>((r + m) * 255),
        static_cast<unsigned char>((g + m) * 255),
        static_cast<unsigned char>((b + m) * 255)
    );
}


ParticleSystem::ParticleSystem(sf::Vector2f position)
    : emitterPosition(position), emissionTime(0.0f) {}

void ParticleSystem::update(float dt)
{
  emissionTime += dt;

  const float GRAVITY_STRENGTH = 500.0f; // pixels / second^2
  sf::Vector2f gravityForce(0.0f, GRAVITY_STRENGTH);

  for (auto &particle : particles)
  {
    particle.applyForce(gravityForce * particle.getMass());
    particle.update(dt);
  }
}

void ParticleSystem::render(sf::RenderTarget &target)
{
  for (auto &particle : particles)
  {
    particle.render(target);
  }
}

void ParticleSystem::emit(int particleCount)
{
  float speed = 150.0f;

  float minAngle = 1.0f * PI / 6.0f;
  float maxAngle = 5.0f * PI / 6.0f;
  float centerAngle = (minAngle + maxAngle) / 2.0f;
  float angleRange = (maxAngle - minAngle) / 2.0f;

  float baseAngle = centerAngle + std::sin(emissionTime * 2.0f) * angleRange;

  for (int i = 0; i < particleCount; i++)
  {
    float angle = baseAngle;

    sf::Vector2f velocity(
        std::cos(angle) * speed,
        std::sin(angle) * speed);

    float hue = std::fmod(emissionTime * 60.0f, 360.0f);
    sf::Color color = hsvToRgb(hue, 1.0f, 1.0f);

    particles.emplace_back(emitterPosition, velocity, color, 5.0f);
  }
}

void ParticleSystem::setEmitterPosition(const sf::Vector2f &position)
{
  emitterPosition = position;
}

size_t ParticleSystem::getParticleCount() const {
  return particles.size();
}