#include "SeparationRule.h"
#include "imgui.h"
#include <glm/glm.hpp>

glm::vec2 SeparationRule::computeForce(const std::vector<BoidView>& boids, int selfIndex) {
  glm::vec2 separatingForce(0.f);

  // the header have the desiredMinimalDistance member variable, which is the distance that the boids should try to maintain from each other.
  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.
  // multiply by (desiredMinimalDistance / distance) is the proportionality factor that makes the force stronger when the boids are closer together, and weaker when they are farther apart.

  // begin solution
  if (boids.size() == 0) {
    return {};
  }
  glm::vec2 forceAccumulator(0.f);
  for (auto nboid : boids) {
        glm::vec2 diff = boids[selfIndex].position - nboid.position;
        float distance = glm::length(diff);
        if (distance < radius && distance > 0.f) {
          glm::vec2 dir = glm::normalize(boids[selfIndex].position - nboid.position);
          forceAccumulator += dir * (radius / distance);
        }
  }

  separatingForce += forceAccumulator * radius;

  // end solution

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;
  if (ImGui::DragFloat("Desired Separation", &radius, 0.05f)) {
    valueHasChanged = true;
  }
  return valueHasChanged;
}
void SeparationRule::drawRadius(const BoidView& boid, ImDrawList* dl) const {
    dl->AddCircle({boid.position.x, boid.position.y}, radius, IM_COL32(255, 0, 0, 100), 0, 1.0f);
 }
