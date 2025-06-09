#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/ParticleSystem.hpp"

int main()
{
  const unsigned int WINDOW_WIDTH = 1200;
  const unsigned int WINDOW_HEIGHT = 800;

  sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Particle Simulation");
  window.setFramerateLimit(60);

  sf::Vector2f center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  float boundaryRadius = 350.0f;

  ParticleSystem particleSystem(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), center, boundaryRadius);

  sf::Clock clock;

  float fps = 0.0f;

  sf::Font font;
  // Try to load a font - you might need to adjust the path
  if (!font.openFromFile("/System/Library/Fonts/Arial.ttf"))
  {
    // If Arial fails, try loading default font or another system font
    if (!font.openFromFile("/System/Library/Fonts/Helvetica.ttc"))
    {
      std::cout << "Warning: Could not load font. Text may not display properly." << std::endl;
    }
  }

  sf::Text fpsText(font);
  fpsText.setCharacterSize(24);
  fpsText.setFillColor(sf::Color::White);
  fpsText.setPosition(sf::Vector2f(10.0f, 10.0f));
  fpsText.setString("FPS: 0");

  sf::Text frameTimeText(font);
  frameTimeText.setCharacterSize(20);
  frameTimeText.setFillColor(sf::Color::White);
  frameTimeText.setPosition(sf::Vector2f(10.0f, 40.0f));
  frameTimeText.setString("Frame Time: 0.000 ms");

  sf::Text particleCountText(font);
  particleCountText.setCharacterSize(20);
  particleCountText.setFillColor(sf::Color::White);
  particleCountText.setPosition(sf::Vector2f(10.0f, 70.0f));
  particleCountText.setString("Particle Count: 0");

  std::cout << "Particle Simulation Started" << std::endl;
  std::cout << "Window Size: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;
  std::cout << "Controls: Mouse to move emitter, Click to emit particles" << std::endl;

  while (window.isOpen())
  {
    float dt = clock.restart().asSeconds();

    fps = 1.0f / dt;

    while (auto event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>() ||
          (event->is<sf::Event::KeyPressed>() &&
           event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
      {
        window.close();
      }

      if (event->is<sf::Event::KeyPressed>()) {
        if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
          particleSystem.setGravityDirection(270.0f);
        } else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
          particleSystem.setGravityDirection(90.0f);
        } else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
          particleSystem.setGravityDirection(180.0f);
        } else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
          particleSystem.setGravityDirection(0.0f);
        }
      }
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    particleSystem.setEmitterPosition(sf::Vector2f(mousePos.x, mousePos.y));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
      particleSystem.emit(1);
    }

    particleSystem.update(dt);

    std::string fpsString = "FPS: " + std::to_string(static_cast<int>(fps));
    fpsText.setString(fpsString);

    std::string frameTimeString = "Frame Time: " + std::to_string(dt * 1000.0f) + " ms";
    frameTimeText.setString(frameTimeString);

    std::string particleCountString = "Particle Count: " + std::to_string(particleSystem.getParticleCount());
    particleCountText.setString(particleCountString);

    window.clear(sf::Color::Black);
    particleSystem.render(window);
    particleSystem.renderBoundary(window);

    window.draw(fpsText);
    window.draw(frameTimeText);
    window.draw(particleCountText);

    window.display();
  }

  std::cout << "Window Closed" << std::endl;
  return 0;
}