#pragma once
#include <SFML/Graphics.hpp>

class Particle {
  private: 
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Color color;
    float radius;
    float mass;
    float drag;

  public:
    Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const sf::Color& col, float r);
    
    void update(float dt);
    void render(sf::RenderTarget& target) const;

    void applyForce(const sf::Vector2f& force);
    void clearForces();

    sf::Vector2f getPosition() const;
    sf::Vector2f& getVelocity();
    float getRadius() const;
    float getMass() const;
    void setPosition(const sf::Vector2f& pos);
    void setVelocity(const sf::Vector2f& vel);
};
