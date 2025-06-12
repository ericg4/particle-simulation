#pragma once
#include <SFML/Graphics.hpp>

class Particle {
  private: 
    sf::Vector2f position;
    sf::Vector2f past_position;
    sf::Vector2f acceleration;
    sf::Color color;
    float radius;
    float mass;
    float drag;

  public:
    Particle(const sf::Vector2f& pos, const sf::Vector2f& past_pos, const sf::Color& col, float r);
    
    void update(float dt);
    void render(sf::RenderTarget& target) const;

    void accelerate(const sf::Vector2f& acceleration);
    void clearAcceleration();

    sf::Vector2f getPosition() const;
    sf::Vector2f getPastPosition() const;
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& v, float dt);
    void addVelocity(const sf::Vector2f& v, float dt);
    float getRadius() const;
    float getMass() const;
    void setPosition(const sf::Vector2f& pos);
    void setPastPosition(const sf::Vector2f& past_pos);
};
