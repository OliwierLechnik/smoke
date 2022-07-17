#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const float DEG_TO_RAD =  M_PI/180;
const float RAD_TO_DEG =  180/M_PI;

template<typename Container, typename Lambda>
Container&& remove_erase_if( Container&& c, Lambda&& test ) {
  using std::begin; using std::end;
  auto it = std::remove_if( begin(c), end(c), std::forward<Lambda>(test) );
  c.erase(it, c.end());
  return std::forward<Container>(c);
}