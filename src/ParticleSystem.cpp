#include "../include/ParticleSystem.hpp"
#include "../include/utils/color.hpp"
#include "../include/utils/math.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>

constexpr float PI = 3.14159265358979323846f;
const float GRAVITY_STRENGTH = 1000.0f; // pixels / second^2
const float DEG_TO_RAD = 3.14159265f / 180.0f;

ParticleSystem::ParticleSystem(sf::Vector2f position, sf::Vector2f center, float radius)
  : emitterPosition(position), emissionTime(0.0f), boundaryCenter(center), boundaryRadius(radius), gravityDirection(90.0f) {
}

void ParticleSystem::update(float dt) {
  emissionTime += dt;

  sf::Vector2f gravity(std::cos(gravityDirection * DEG_TO_RAD) * GRAVITY_STRENGTH,
    std::sin(gravityDirection * DEG_TO_RAD) * GRAVITY_STRENGTH);

  const int sub_steps = 4;
  for (int i = 0; i < sub_steps; i++) {
    float sub_dt = dt / sub_steps;

    for (auto& particle : particles)
    {
      particle.accelerate(gravity);
      particle.update(sub_dt);

      sf::Vector2f particlePos = particle.getPosition();
      sf::Vector2f r = boundaryCenter - particlePos;
      float distance = utils::calcLengthOfVector(r);

      if (distance > boundaryRadius - particle.getRadius())
      {
        sf::Vector2f n = r / distance;
        sf::Vector2f perp = sf::Vector2f(-n.y, n.x);
        sf::Vector2f vel = particle.getVelocity();

        particle.setPosition(boundaryCenter - n * (boundaryRadius - particle.getRadius()));
        particle.setVelocity(2.0f * utils::dot(vel, perp) * perp - vel, 1.0f);
      }
    }
  }

  // const int collisionIterations = 4;
  // for (int i = 0; i < collisionIterations; i++) {
  //   handleParticleCollisions();
  // }
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

// void ParticleSystem::resolveCollision(Particle& particle1, Particle& particle2) {
//   sf::Vector2f pos1 = particle1.getPosition();
//   sf::Vector2f pos2 = particle2.getPosition();
//   sf::Vector2f vel1 = particle1.getVelocity();
//   sf::Vector2f vel2 = particle2.getVelocity();
//   float m1 = particle1.getMass();
//   float m2 = particle2.getMass();
//   float r1 = particle1.getRadius();
//   float r2 = particle2.getRadius();

//   sf::Vector2f delta = pos2 - pos1;
//   float distance = utils::calcLengthOfVector(delta);

//   // Prevent division by zero and handle particles at same position
//   if (distance < 0.001f) {
//     // Create artificial separation for particles at same position
//     delta = sf::Vector2f(1.0f, 0.0f);
//     distance = 0.001f;
//   }

//   sf::Vector2f unit_normal = delta / distance;
//   sf::Vector2f tangent = sf::Vector2f(-unit_normal.y, unit_normal.x);

//   float overlap = (r1 + r2) - distance;

//   // Separate overlapping particles
//   if (overlap > 0.0f) {
//     sf::Vector2f separation = unit_normal * (overlap * 0.5f + 0.1f);
//     particle1.setPosition(pos1 - separation);
//     particle2.setPosition(pos2 + separation);
//   }
//   float v1n = utils::dot(vel1, unit_normal);
//   float v2n = utils::dot(vel2, unit_normal);
//   float v1t = utils::dot(vel1, tangent);
//   float v2t = utils::dot(vel2, tangent);

//   float v1n_prime = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
//   float v2n_prime = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

//   float damping = 0.95f;

//   float relVelAlongNormal = utils::dot(vel1 - vel2, unit_normal);
//   // if (relVelAlongNormal < -0.01f) return;

//   sf::Vector2f newVel1 = tangent * v1t + unit_normal * v1n_prime * damping;
//   sf::Vector2f newVel2 = tangent * v2t + unit_normal * v2n_prime * damping;

//   if (utils::calcLengthOfVector(newVel1) < 1.0f) newVel1 = sf::Vector2f(0.0f, 0.0f);
//   if (utils::calcLengthOfVector(newVel2) < 1.0f) newVel2 = sf::Vector2f(0.0f, 0.0f);

//   particle1.setVelocity(newVel1);
//   particle2.setVelocity(newVel2);
// }

// void ParticleSystem::handleParticleCollisions() {
//   int num_objects = particles.size();
//   for (int i = 0; i < num_objects; i++) {
//     for (int j = i + 1; j < num_objects; j++) {
//       if (i == j) continue;

//       if (checkCollision(particles[i], particles[j])) {
//         resolveCollision(particles[i], particles[j]);
//       }
//     }
//   }
// }

void ParticleSystem::emit(int particleCount, float dt) {
  float initialSpeed = 350.0f;

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

    sf::Vector2f past_pos = emitterPosition - velocity * dt;
    particles.emplace_back(emitterPosition, past_pos, color, 5.0f);
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