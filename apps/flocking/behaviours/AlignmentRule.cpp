#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& boids, int selfIndex) {
  glm::vec2 averageVelocity(0.f);
  // glm::vec2 can be divided by a float, which will divide each component of the vector by that float.
  averageVelocity = boids[selfIndex].velocity;
  // begin solution
  if (boids.size() == 1) {
    averageVelocity += boids.front().velocity;
    averageVelocity /= 2;
    return averageVelocity;
  } else if (boids.size() == 0) {
    return {};
  }

  for (auto nboid : boids) {

    averageVelocity += nboid.velocity;
  }

  averageVelocity /= (boids.size() + 1);

  return averageVelocity;
  // end solution
}
bool AlignmentRule::drawImguiRuleExtra() {
  ImGui::DragFloat("Alignment Radius", &radius, 0.05f);
  return true;
}
void AlignmentRule::drawRadius(const BoidView& boid, ImDrawList* dl) const {
  dl->AddCircle({boid.position.x, boid.position.y}, radius, IM_COL32(255, 255, 0, 100), 0, 1.0f);
}
