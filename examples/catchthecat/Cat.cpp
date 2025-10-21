#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();

  std::vector<Point2D>path = generatePath(world);

  if (!path.empty()) {
    return path.front();
  }

  Point2D newPos;

  std::vector<Point2D>neighbors = world->getVisitableNeighbors(pos);
  if (!neighbors.empty()) {
    newPos = neighbors.at(rand % neighbors.size());

    return newPos;
  }

  throw "Cat::Move()failed";



}
