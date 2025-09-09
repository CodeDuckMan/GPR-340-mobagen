#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
  Vector2f targetForce = Vector2f::zero();

  int windowSizeX = this->world->engine->window->size().x;
  int windowSizeY = this->world->engine->window->size().y;

  // Check if boid is in bounding area by radius
  bool boidAboveWindowX = boid->getPosition().x + desiredDistance > windowSizeX;
  bool boidBelowWindowX = boid->getPosition().x - desiredDistance < 0;
  bool boidAboveWindowY = boid->getPosition().y + desiredDistance > windowSizeY;
  bool boidBelowWindowY = boid->getPosition().y - desiredDistance < 0;

  // Apply targetForce depending on the previous checks
  if (boidAboveWindowX)
    targetForce.x -= boid->getPosition().x;
  else if (boidBelowWindowX)
    targetForce.x += boid->getPosition().x;
  if (boidAboveWindowY)
    targetForce.y -= boid->getPosition().y;
  else if (boidBelowWindowY)
    targetForce.y += boid->getPosition().y;

  return targetForce;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}