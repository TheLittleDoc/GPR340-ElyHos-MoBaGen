#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& boids, int selfIndex) {
  glm::vec2 cohesionForce(0.f);

  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.

  if (boids.size() == 0)
    return {};

  glm::vec2 cm(0.f);
  // begin solution
  for (auto boid : boids) {
    cm += boid.position;
  }
  cm /= boids.size();
  glm::vec2 dir = glm::normalize(boids[selfIndex].position - cm);

  if (distance(boids[selfIndex].position, cm) == 0)
    return {};

  cohesionForce += -dir * distance(boids[selfIndex].position, cm);

  // end solution

  return cohesionForce;
}
bool CohesionRule::drawImguiRuleExtra() {
  ImGui::DragFloat("Cohesion Radius", &radius, 0.05f);
  return true;
}

void CohesionRule::drawRadius(const BoidView& boid, ImDrawList* dl) const {
  dl->AddCircle({boid.position.x, boid.position.y}, radius, IM_COL32(0, 255, 255, 100), 0, 1.0f);

}

