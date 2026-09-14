#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 cohesionForce(0.f);

  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.

  if (neighborhood.size() == 0)
    return {};

  glm::vec2 cm(0.f);
  // begin solution
  for (auto boid : neighborhood ) {
    cm += boid.position;
  }
  cm /= neighborhood.size();
  glm::vec2 dir = glm::normalize(boid.position - cm);

  if (distance(boid.position, cm) == 0)
    return {};

  cohesionForce += -dir * distance(boid.position, cm);

  // end solution

  return cohesionForce;
}
