#pragma once
#include "alg/sort.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Chart : public sf::Drawable {
protected:
  sf::Vector2u size;
  float barWidth;

  std::vector<unsigned> const &dataRef;

  std::vector<sf::RectangleShape> bars;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
  void Reset();

  // Progresses the sorting 1 "tick" (see individual definitions for specifics)
  // and updates the visuals accordingly
  void Update(Sort const *sorterPtr);

  Chart(unsigned const chartWidth, unsigned const chartHeight,
        std::vector<unsigned> const &data);
};
