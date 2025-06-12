#include "../include/Particle.hpp"

Particle::Particle(const sf::Vector2f& pos, const sf::Vector2f& past_pos, const sf::Color& col, float r)
  : position(pos), past_position(past_pos), acceleration(0.0f, 0.0f), color(col), radius(r), mass(3.14f * r * r), drag(0.993f) {
}
void Particle::update(float dt) {
  sf::Vector2f displacement = position - past_position;
  past_position = position;

  position = position + displacement + acceleration * (dt * dt);

  clearAcceleration();
}

void Particle::render(sf::RenderTarget& target) const {
  sf::CircleShape shape;
  shape.setRadius(radius);
  shape.setPosition(position);
  shape.setFillColor(color);
  target.draw(shape);
}

// Acceleration getters and setters
void Particle::accelerate(const sf::Vector2f& acceleration) {
  this->acceleration += acceleration;
}

void Particle::clearAcceleration() {
  acceleration = sf::Vector2f(0.0f, 0.0f);
}

// Velocity getters and setters
sf::Vector2f Particle::getVelocity() const {
  return position - past_position;
}

void Particle::setVelocity(const sf::Vector2f& vel, float dt) {
  past_position = position - (vel * dt);
}

void Particle::addVelocity(const sf::Vector2f& vel, float dt) {
  past_position -= (vel * dt);
}

// General getters
float Particle::getRadius() const {
  return radius;
}

float Particle::getMass() const {
  return mass;
}

// Position getters and setters
void Particle::setPosition(const sf::Vector2f& pos) {
  position = pos;
}

sf::Vector2f Particle::getPosition() const {
  return position;
}

void Particle::setPastPosition(const sf::Vector2f& past_pos) {
  past_position = past_pos;
}