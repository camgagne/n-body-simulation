// Copyright Cameron Gagne

#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class Universe : public sf::Drawable {
 public:
  Universe();
  size_t size() const;
  void step(double dt);
  const CelestialBody& operator[](size_t i) const;
  friend std::istream& operator>>(std::istream& is, Universe& universe);
  friend std::ostream& operator<<(std::ostream& os, const Universe& universe);
 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
  double uni_radius;
  std::vector<std::shared_ptr<CelestialBody>> bodies;
  std::vector<std::shared_ptr<CelestialBody>> getBodies() const;
  void addBody(std::shared_ptr<CelestialBody> body);
};

}  // namespace NB

