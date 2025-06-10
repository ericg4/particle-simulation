#include "../include/Particle.hpp"

Particle::Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, float r)
  : position(pos), velocity(vel), acceleration(0.0f, 0.0f), color(col), radius(r), mass(3.14f * r * r), drag(0.993f) {
}
void Particle::update(float dt) {
  velocity *= drag;

  velocity += acceleration * dt;
  position += velocity * dt;

  clearForces();
}

void Particle::render(sf::RenderTarget& target) const {
  sf::CircleShape shape;
  shape.setRadius(radius);
  shape.setPosition(position - sf::Vector2f(radius, radius));
  shape.setFillColor(color);
  target.draw(shape);
}

void Particle::applyForce(const sf::Vector2f& force) {
  acceleration += force / mass;
}

void Particle::clearForces() {
  acceleration = sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f Particle::getPosition() const {
  return position;
}

sf::Vector2f& Particle::getVelocity() {
  return velocity;
}

float Particle::getRadius() const {
  return radius;
}

float Particle::getMass() const {
  return mass;
}

void Particle::setPosition(const sf::Vector2f& pos) {
  position = pos;
}

void Particle::setVelocity(const sf::Vector2f& vel) {
  velocity = vel;
}