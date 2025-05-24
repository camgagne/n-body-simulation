// Copyright 2025 Cameron Gagne

#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 public:
  CelestialBody();
  sf::Vector2f position() const;
  sf::Vector2f velocity() const;
  double getMass() const;
  void setVelocity(double vx, double vy);
  void setPosition(double x, double y, double universe_radius);
  friend std::istream& operator>>(std::istream& is, CelestialBody& body);
  friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);
 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
  sf::Vector2f pos;
  sf::Vector2f vel;
  double  mass;
  sf::Sprite sprite;
  std::string textureFilename;
  sf::Texture texture;
  void setTexture(const std::string& filename);
};

}  // namespace NB

