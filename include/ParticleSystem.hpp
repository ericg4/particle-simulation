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

  public:
    ParticleSystem(sf::Vector2f position);

    void update(float dt);
    void render(sf::RenderTarget& target);
    void emit(int particleCount);
    void setEmitterPosition(const sf::Vector2f& position);

    size_t getParticleCount() const;
};
