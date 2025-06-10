#define _USE_MATH_DEFINES
#include "../include/ParticleSystem.hpp"
#include "../include/utils/color.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>

constexpr float PI = 3.14159265358979323846f;
const float GRAVITY_STRENGTH = 350.0f; // pixels / second^2
const float DEG_TO_RAD = 3.14159265f / 180.0f;

ParticleSystem::ParticleSystem(sf::Vector2f position, sf::Vector2f center, float radius)
  : emitterPosition(position), emissionTime(0.0f), boundaryCenter(center), boundaryRadius(radius), gravityDirection(90.0f) {
}

void ParticleSystem::update(float dt) {
  emissionTime += dt;

  sf::Vector2f gravityForce(std::cos(gravityDirection * DEG_TO_RAD) * GRAVITY_STRENGTH,
    std::sin(gravityDirection * DEG_TO_RAD) * GRAVITY_STRENGTH);

  for (auto& particle : particles)
  {
    particle.applyForce(gravityForce * particle.getMass());
    particle.update(dt);

    sf::Vector2f particlePos = particle.getPosition();
    sf::Vector2f toParticle = particlePos - boundaryCenter;
    float distance = std::sqrt(toParticle.x * toParticle.x + toParticle.y * toParticle.y);

    if (distance > boundaryRadius - particle.getRadius())
    {
      sf::Vector2f normal = toParticle / distance;

      sf::Vector2f newPos = boundaryCenter + normal * (boundaryRadius - particle.getRadius());
      particle.setPosition(newPos);

      sf::Vector2f vel = particle.getVelocity();
      float dotProduct = vel.x * normal.x + vel.y * normal.y;
      sf::Vector2f reflection = vel - 2.0f * dotProduct * normal;
      particle.setVelocity(reflection);
    }
  }
}

void ParticleSystem::render(sf::RenderTarget& target) {
  for (auto& particle : particles)
  {
    particle.render(target);
  }
}

void ParticleSystem::renderBoundary(sf::RenderTarget& target) {
  sf::CircleShape boundaryCircle(boundaryRadius);
  boundaryCircle.setPosition(boundaryCenter - sf::Vector2f(boundaryRadius, boundaryRadius));
  boundaryCircle.setFillColor(sf::Color(0, 0, 0, 0));
  boundaryCircle.setOutlineColor(sf::Color(255, 255, 255, 128));
  boundaryCircle.setOutlineThickness(2.0f);
  target.draw(boundaryCircle);
}

void ParticleSystem::emit(int particleCount) {
  float initialSpeed = 250.0f;

  float minAngle = 1.0f * PI / 6.0f;
  float maxAngle = 5.0f * PI / 6.0f;
  float centerAngle = (minAngle + maxAngle) / 2.0f;
  float angleRange = (maxAngle - minAngle) / 2.0f;

  float baseAngle = centerAngle + std::sin(emissionTime * 2.0f) * angleRange;

  for (int i = 0; i < particleCount; i++)
  {
    float angle = baseAngle;

    sf::Vector2f velocity(
      std::cos(angle) * initialSpeed,
      std::sin(angle) * initialSpeed);

    float hue = std::fmod(emissionTime * 60.0f, 360.0f);
    sf::Color color = utils::hsvToRgb(hue, 1.0f, 1.0f);

    particles.emplace_back(emitterPosition, velocity, color, 5.0f);
  }
}

void ParticleSystem::setEmitterPosition(const sf::Vector2f& position) {
  emitterPosition = position;
}

size_t ParticleSystem::getParticleCount() const {
  return particles.size();
}

void ParticleSystem::setGravityDirection(float angle) {
  gravityDirection = angle;
}