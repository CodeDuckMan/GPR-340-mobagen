#include "MouseInfluenceRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f MouseInfluenceRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
     ImGuiIO& io = ImGui::GetIO();

      float neighbourhoodRadius = boid->getDetectionRadius();
      if (ImGui::IsMousePosValid() && io.MouseDown[0]) {

        // Get mouse position
        Vector2f mousePos(io.MousePos.x, io.MousePos.y);

        // Check if mouse is in range of boid
        bool mouseInXRange = mousePos.x >= boid->getPosition().x - neighbourhoodRadius && mousePos.x <= boid->getPosition().x + neighbourhoodRadius;
        bool mouseInYRange = mousePos.y >= boid->getPosition().y - neighbourhoodRadius && mousePos.y <= boid->getPosition().y + neighbourhoodRadius;

        // If the boid is in the mouse range or range is set to global
        if ((mouseInXRange && mouseInYRange) || mouseGrabGlobal) {

          //The force is inversely proportional to distance
          Vector2f targetForce = Vector2f::zero(); //

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

  if (ImGui::RadioButton("Mouse Neighborhood Attraction", !mouseGrabGlobal)) {
    mouseGrabGlobal = false;
    valueHasChanged = true;
  }

  ImGui::SameLine();
  if (ImGui::RadioButton("Mouse Global Attraction", mouseGrabGlobal)) {
    mouseGrabGlobal = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}