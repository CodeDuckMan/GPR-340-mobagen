#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  if (!neighborhood.empty()) {
    Vector2f hat = Vector2f::zero();
    Vector2f target = Vector2f::zero();

    double magnitude = 0;

    // Collect all boid positions in neighborhood
    for (int i = 0; i < neighborhood.size(); i++) {
      target += (boid->getPosition() - neighborhood[i]->getPosition()) ;

      // If target magnitude
      magnitude = target.getMagnitude();
      if (magnitude < desiredDistance && magnitude != 0) {
        hat = target / magnitude;
        separatingForce += hat * desiredDistance / magnitude;
      }
    }
  }

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
