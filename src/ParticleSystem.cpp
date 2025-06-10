#include "../include/ParticleSystem.hpp"
#include "../include/utils/color.hpp"
#include "../include/utils/math.hpp"
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
    float distance = utils::calcDistance(particlePos, boundaryCenter);

    if (distance > boundaryRadius - particle.getRadius())
    {
      sf::Vector2f normal = toParticle / distance;

      sf::Vector2f newPos = boundaryCenter + normal * (boundaryRadius - particle.getRadius());
      particle.setPosition(newPos);

      sf::Vector2f vel = particle.getVelocity();
      float dotProduct = utils::dot(vel, normal);
      sf::Vector2f reflection = vel - 2.0f * dotProduct * normal;
      particle.setVelocity(reflection);
    }
  }

  handleParticleCollisions();
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

bool ParticleSystem::checkCollision(const Particle& particle1, const Particle& particle2) {
  sf::Vector2f pos1 = particle1.getPosition();
  sf::Vector2f pos2 = particle2.getPosition();

  float distance = utils::calcDistance(pos1, pos2);
  float collisionDistance = particle1.getRadius() + particle2.getRadius();

  return distance < collisionDistance; // Use < instead of <= for cleaner detection
}

void ParticleSystem::resolveCollision(Particle& particle1, Particle& particle2) {
  sf::Vector2f pos1 = particle1.getPosition();
  sf::Vector2f pos2 = particle2.getPosition();
  sf::Vector2f vel1 = particle1.getVelocity();
  sf::Vector2f vel2 = particle2.getVelocity();
  float m1 = particle1.getMass();
  float m2 = particle2.getMass();
  float r1 = particle1.getRadius();
  float r2 = particle2.getRadius();

  sf::Vector2f delta = pos2 - pos1;
  float distance = utils::calcLengthOfVector(delta);

  // Prevent division by zero and handle particles at same position
  if (distance < 0.001f) {
    // Create artificial separation for particles at same position
    delta = sf::Vector2f(1.0f, 0.0f);
    distance = 0.001f;
  }

  sf::Vector2f unit_normal = delta / distance;
  sf::Vector2f tangent = sf::Vector2f(-unit_normal.y, unit_normal.x);

  float overlap = (r1 + r2) - distance;

  // **CRITICAL: Separate overlapping particles**
  if (overlap > 0.0f) {
    sf::Vector2f separation = unit_normal * (overlap * 0.5f);
    particle1.setPosition(pos1 - separation);
    particle2.setPosition(pos2 + separation);
  }
  float v1n = utils::dot(vel1, unit_normal);
  float v2n = utils::dot(vel2, unit_normal);
  float v1t = utils::dot(vel1, tangent);
  float v2t = utils::dot(vel2, tangent);

  float v1n_prime = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
  float v2n_prime = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

  particle1.setVelocity(tangent * v1t + unit_normal * v1n_prime); 
  particle2.setVelocity(tangent * v2t + unit_normal * v2n_prime);
}

void ParticleSystem::handleParticleCollisions() {
  for (size_t i = 0; i < particles.size(); i++) {
    for (size_t j = i + 1; j < particles.size(); j++) {
      if (&particles[i] == &particles[j]) continue;

      if (checkCollision(particles[i], particles[j])) {
        resolveCollision(particles[i], particles[j]);
      }
    }
  }
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