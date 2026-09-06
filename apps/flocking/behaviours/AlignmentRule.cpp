#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 averageVelocity(0.f);
  // glm::vec2 can be divided by a float, which will divide each component of the vector by that float.
  averageVelocity = boid.velocity;
  // begin solution
  if (neighborhood.size() == 1) {
    averageVelocity += neighborhood.front().velocity;
    averageVelocity /= 2;
    return averageVelocity;
  } else if (neighborhood.size() == 0) {
    return {};
  }

  for (auto nboid : neighborhood) {
    averageVelocity += nboid.velocity;
  }

  averageVelocity /= (neighborhood.size() + 1);

  return averageVelocity;
  // end solution
}
