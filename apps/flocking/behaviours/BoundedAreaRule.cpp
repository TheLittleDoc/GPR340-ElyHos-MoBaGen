#include "BoundedAreaRule.h"
#include "imgui.h"
#include <glm/glm.hpp>
#include <algorithm>

glm::vec2 BoundedAreaRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 force(0.f);
  ImVec2 displaySize = ImGui::GetIO().DisplaySize;
  // desiredDistance is the distance from the borders that the boids should try to maintain. 
  glm::vec2 normal = {};
  // begin solution
  glm::vec2 futurePos = boid.velocity * 0.0167f + boid.position;
  //early return if future pos is in box
  if (futurePos.x >= desiredDistance && futurePos.x <= displaySize.x - desiredDistance &&
      futurePos.y >= desiredDistance && futurePos.y <= displaySize.y - desiredDistance) {
    return {};
  }

  // nearest border
  if (futurePos.x < desiredDistance) {
    normal = glm::vec2(1.f, 0.f);
  } else if (futurePos.x > displaySize.x - desiredDistance) {
    normal= glm::vec2(-1.f, 0.f);
  } else if (futurePos.y < desiredDistance) {
    normal = glm::vec2(0.f, 1.f);
  } else if (futurePos.y > displaySize.y - desiredDistance) {
    normal = glm::vec2(0.f, -1.f);
  }
  // when a border is approached, a center-pointing force is applied
  glm::vec2 centerDir = boid.position - glm::vec2(displaySize.x / 2.f, displaySize.y / 2.f);
  if (glm::length(centerDir) > 0.f) {
    centerDir = glm::normalize(centerDir);
    force += -centerDir * (desiredDistance * 4 / glm::length(centerDir));
  }
  force -= normal;
  // end solution

  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImVec2 displaySize = ImGui::GetIO().DisplaySize;
  float widthWindows = displaySize.x > 0.f ? displaySize.x : 1280.f;
  float heightWindows = displaySize.y > 0.f ? displaySize.y : 800.f;
  bool valueHasChanged = false;
  int minHeightWidth = static_cast<int>(std::min(widthWindows, heightWindows));

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0, minHeightWidth / 3, "%i")) {
    valueHasChanged = true;
  }
  return valueHasChanged;
}

void BoundedAreaRule::drawWorldOverlay(ImDrawList* dl) const {
  ImVec2 displaySize = ImGui::GetIO().DisplaySize;
  float w = displaySize.x > 0.f ? displaySize.x : 1280.f;
  float h = displaySize.y > 0.f ? displaySize.y : 800.f;
  float d = static_cast<float>(desiredDistance);
  ImU32 col = IM_COL32(128, 128, 128, 200);

  dl->AddLine({d, d}, {w - d, d}, col);
  dl->AddLine({w - d, d}, {w - d, h - d}, col);
  dl->AddLine({w - d, h - d}, {d, h - d}, col);
  dl->AddLine({d, h - d}, {d, d}, col);
}
