// Copyright 2025 Cameron Gagne

#include "CelestialBody.hpp"
#include <iomanip>
#include <iostream>

namespace NB {

CelestialBody::CelestialBody() : pos(0, 0), vel(0, 0), mass(0) {}

sf::Vector2f CelestialBody::position() const {
  return pos;
}

sf::Vector2f CelestialBody:: velocity() const {
  return vel;
}

double CelestialBody::getMass() const {
  return mass;
}

void CelestialBody::setVelocity(double vx, double vy) {
  vel = sf::Vector2f(vx, vy);
}

void CelestialBody::setPosition(double x, double y, double universe_radius) {
  pos = sf::Vector2f(x, y);

  double scaleFactor = 400.0 / universe_radius;
  double screenX = static_cast<double>(400.0 + x * scaleFactor);
  double screenY = static_cast<double>(400.0 - y * scaleFactor);

  sprite.setPosition(screenX, screenY);
}

void CelestialBody::setTexture(const std::string& filename) {
  texture.loadFromFile(filename);
  sprite.setTexture(texture);
}


void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite, states);
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
  double x, y, vx, vy, mass;
  std::string filename;

  is >> x >> y >> vx >> vy >> mass >> filename;

  body.pos.x = x;
  body.pos.y = y;
  body.vel.x = vx;
  body.vel.y = vy;
  body.mass = mass;
  body.textureFilename = filename;
  body.setTexture(filename);

  return is;
}



std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
  os  << body.pos.x << " " << body.pos.y << " "  << body.vel.x;
  os << " " << body.vel.y << " " << body.mass;
  os << " " << body.textureFilename << std::endl;
  return os;
}

}  // namespace NB
