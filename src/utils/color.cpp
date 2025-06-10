#include <SFML/Graphics.hpp>
#include "../include/utils/color.hpp"
#include <cmath>

sf::Color utils::hsvToRgb(float h, float s, float v) {
  float c = v * s;
  float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
  float m = v - c;

  float r, g, b;

  if (h >= 0 && h < 60)
  {
    r = c;
    g = x;
    b = 0;
  }
  else if (h >= 60 && h < 120)
  {
    r = x;
    g = c;
    b = 0;
  }
  else if (h >= 120 && h < 180)
  {
    r = 0;
    g = c;
    b = x;
  }
  else if (h >= 180 && h < 240)
  {
    r = 0;
    g = x;
    b = c;
  }
  else if (h >= 240 && h < 300)
  {
    r = x;
    g = 0;
    b = c;
  }
  else
  {
    r = c;
    g = 0;
    b = x;
  }

  return sf::Color(
    static_cast<unsigned char>((r + m) * 255),
    static_cast<unsigned char>((g + m) * 255),
    static_cast<unsigned char>((b + m) * 255));
}