// Copyright 2025 Cameron Gagne

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

int main(int argc, char *argv[]) {
  double yearsInSec = std::stod(argv[1]);
  double dt = std::stod(argv[2]);
  double currentTime = 0;
  NB::Universe universe;
  std::cin >> universe;

  sf::RenderWindow window(sf::VideoMode(800, 800), "NBody Simulation");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(universe);
    window.display();
    if (currentTime >= yearsInSec) {
      window.close();
    } else {
      universe.step(dt);
      currentTime += dt;
    }
  }

  std::cout << universe;
  return 0;
}

