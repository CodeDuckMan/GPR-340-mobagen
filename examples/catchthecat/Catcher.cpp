#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;

  std::vector<Point2D>path = generatePath(world);

  if (!path.empty()) {
    return path.back();
  }


  for (;;) {
    // Gets the cats current valid neighbors and fills in a random one
    std::vector<Point2D>pointNeighbors = world->getVisitableNeighbors(world->getCat());
    Point2D point = pointNeighbors.at(rand() % pointNeighbors.size());

    return point;

  }
}
