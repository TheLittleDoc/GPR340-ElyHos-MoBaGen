#include "MouseInfluenceRule.h"
#include "imgui.h"

glm::vec2 MouseInfluenceRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 force(0.f);

  // ImGui::IsMouseDown(ImGuiMouseButton_Left) returns true if the left mouse button is currently pressed.
  // ImGui::GetIO().MousePos returns the current mouse position as an ImVec2.
  // glm::length(vec) returns the length of a vector

  // begin solution
  if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    return {};
  }
  glm::vec2 mousePos = {ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y};
  float mag = glm::length(mousePos - boid.position);
  constMultiplier = 100000.f;
  if (mag < 0.0001f) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distrib(-1, 0);
    std::uniform_real_distribution<float> distribution(0.f, 1.f);
    glm::vec2 randDir = {distribution(rng) * distrib(rng), distribution(rng) * distrib(rng)};
    randDir = glm::normalize(randDir);
    return randDir * constMultiplier;
  }

  glm::vec2 direction = mousePos - boid.position;
  force = glm::normalize(direction);
  force = force * (isRepulsive ? -1.f : 1.f) * (constMultiplier / mag);

  // end solution

  return force;
}

bool MouseInfluenceRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;

  if (ImGui::RadioButton("Attractive", !isRepulsive)) {
    isRepulsive = false;
    valueHasChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::RadioButton("Repulsive", isRepulsive)) {
    isRepulsive = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}
