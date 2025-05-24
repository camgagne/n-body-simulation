// Copyright 2025 Cameron Gagne

#include "Universe.hpp"
#include <math.h>
#include <iostream>
#include <fstream>

namespace NB {

Universe::Universe() : uni_radius(0) {}

size_t Universe::size() const {
  return bodies.size();
}

void Universe::step(double dt) {
  const double G = 6.67e-11;

  // Store forces for each body
  std::vector<sf::Vector2f> forces;

  // Calc forces
  for (size_t i = 0; i < bodies.size(); i++) {
    sf::Vector2f netForce(0.0, 0.0);

    for (size_t j = 0; j < bodies.size(); j++) {
      if (i == j) continue;

      double dx = bodies[j]->position().x - bodies[i]->position().x;
      double dy = bodies[j]->position().y - bodies[i]->position().y;
      double rSquared = dx * dx + dy * dy;

      double r = sqrt(rSquared);
      double forceMagnitude = (G * bodies[i]->getMass() * bodies[j]->getMass()) / rSquared;

      double fX = forceMagnitude * (dx / r);
      double fY = forceMagnitude * (dy / r);

      netForce.x += fX;
      netForce.y += fY;
    }

    forces.push_back(netForce);
  }

  // Update vel
  for (size_t i = 0; i < bodies.size(); i++) {
    double ax = forces[i].x / bodies[i]->getMass();
    double ay = forces[i].y / bodies[i]->getMass();

    bodies[i]->setVelocity(bodies[i]->velocity().x + (dt * ax),
                           bodies[i]->velocity().y + (dt * ay));
  }

  // Update pos
  for (size_t i = 0; i < bodies.size(); i++) {
    bodies[i]->setPosition(bodies[i]->position().x + dt * bodies[i]->velocity().x,
                           bodies[i]->position().y + dt * bodies[i]->velocity().y, uni_radius);
  }
}

const CelestialBody& Universe::operator[](size_t i) const {
  return *bodies[i];
}


void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& body : bodies) {
    target.draw(*body, states);
  }
}

std::vector<std::shared_ptr<CelestialBody>> Universe::getBodies() const {
  return bodies;
}

void Universe::addBody(std::shared_ptr<CelestialBody> body) {
  bodies.push_back(body);
}

std::istream& operator>>(std::istream& is, Universe& universe) {
  size_t n;
  is >> n >> universe.uni_radius;

  for (size_t i = 0; i < n; i++) {
    auto body = std::make_shared<CelestialBody>();
    is >> *body;
    body->setPosition(body->position().x, body->position().y, universe.uni_radius);
    universe.addBody(body);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
  os << universe.size() << "\n" << universe.uni_radius << std::endl;
  for (const auto& body : universe.getBodies()) {
    os << *body;
  }
  return os;
}

}  // namespace NB
