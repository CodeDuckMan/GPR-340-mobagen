#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;
  // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  if (!neighborhood.empty()) {
    Vector2f hat = Vector2f::zero();
    Vector2f target = Vector2f::zero();
    Vector2f accumulatedForce = Vector2f::zero();

    double magnitude = 0;

    for (int i = 0; i < neighborhood.size(); i++) {
      target += neighborhood[i]->getPosition() - boid->getPosition();

      magnitude = boid->getPosition().getMagnitude();
      if (magnitude != 0) {
        hat = target / magnitude;
        accumulatedForce += hat/magnitude;
      }
    }

    // todo: find and apply force only on the closest mates
  }

  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
