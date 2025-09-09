#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // Check if there is anyone nearby
  if (!neighborhood.empty()) {

    // Collect all neighborhood boid the positions
    for (int i = 0; i < neighborhood.size(); i++) {
      cohesionForce+= neighborhood[i]->getPosition();
    }

    // Devide to get average mass
    cohesionForce/= neighborhood.size();

    // Subtract to get the vector that the boid wants to go in
    cohesionForce -= boid->getPosition();

    cohesionForce = Vector2f::normalized(cohesionForce);

    }

  return cohesionForce;
}