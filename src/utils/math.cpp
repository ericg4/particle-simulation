#include "../include/utils/math.hpp"
#include <cmath>

float utils::dot(const sf::Vector2f& a, const sf::Vector2f& b) {
  return a.x * b.x + a.y * b.y;
}

float utils::calcDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float utils::calcLengthOfVector(const sf::Vector2f& a) {
  return std::sqrt(a.x * a.x + a.y * a.y);
}