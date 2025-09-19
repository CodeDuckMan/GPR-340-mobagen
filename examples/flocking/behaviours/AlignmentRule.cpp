#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = boid->getVelocity();

    // Get the average velocity from each boid in the neighborhood
    for (int i = 0; i < neighborhood.size(); i++) {
      averageVelocity += neighborhood[i]->getVelocity();
    }

    // Devide by neighborhood size to get average velocity
    averageVelocity /= neighborhood.size() + 1;

  return averageVelocity.normalized();
}