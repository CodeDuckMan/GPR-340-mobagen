#include "MouseInfluenceRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f MouseInfluenceRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
     ImGuiIO& io = ImGui::GetIO();
      if (ImGui::IsMousePosValid() && io.MouseDown[0]) {

        Vector2f mousePos(io.MousePos.x, io.MousePos.y); // todo: use this
        float detectionRadius = boid->getDetectionRadius();

        // Check if mouse is in range of boid
        bool mouseInXRange = mousePos.x >= boid->getPosition().x - detectionRadius && mousePos.x <= boid->getPosition().x + detectionRadius;
        bool mouseInYRange = mousePos.y >= boid->getPosition().y - detectionRadius && mousePos.y <= boid->getPosition().y + detectionRadius;

        if (mouseInXRange && mouseInYRange) {

          //The force is inversely proportional to distance
          Vector2f targetForce = Vector2f::zero(); // todo: change this

          targetForce = mousePos - boid->getPosition();
          targetForce = targetForce - boid->getVelocity();

          if (isRepulsive)
            targetForce *= -1.f;

          return targetForce;

        }
      }
      else
          return Vector2f::zero();
  return Vector2f::zero();
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