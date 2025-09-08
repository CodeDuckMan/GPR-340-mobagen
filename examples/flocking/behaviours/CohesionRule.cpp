#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  if (!neighborhood.empty()) {

    for (int i = 0; i < neighborhood.size(); i++) {
      cohesionForce+= neighborhood[i]->getPosition();
    }

    // find center of mass
    cohesionForce/= neighborhood.size();
    cohesionForce -= boid->getPosition();
    cohesionForce = Vector2f::normalized(cohesionForce);

    }

  return cohesionForce;
}