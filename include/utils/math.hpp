#pragma once
#include <SFML/Graphics.hpp>

namespace utils {
  float dot(const sf::Vector2f& a, const sf::Vector2f& b);
  float calcDistance(const sf::Vector2f& a, const sf::Vector2f& b);
  float calcLengthOfVector(const sf::Vector2f& a);
}