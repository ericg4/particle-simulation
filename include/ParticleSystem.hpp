#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Particle.hpp"

class ParticleSystem {
  private: 
    std::vector<Particle> particles;
    sf::Vector2f emitterPosition;
    float emissionTime;
    float gravityDirection;

    sf::Vector2f boundaryCenter;
    float boundaryRadius;

    void handleParticleCollisions();
    void resolveCollision(Particle& particle1, Particle& particle2);
    bool checkCollision(const Particle& particle1, const Particle& particle2);

  public:
    ParticleSystem(sf::Vector2f position, sf::Vector2f boundaryCenter, float boundaryRadius);

    void update(float dt);
    void render(sf::RenderTarget& target);
    void emit(int particleCount);
    void setEmitterPosition(const sf::Vector2f& position);
    void renderBoundary(sf::RenderTarget& target);
    void setGravityDirection(float angle);

    size_t getParticleCount() const;
};
