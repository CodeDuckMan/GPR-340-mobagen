#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

  int numNeighbors = 0;
  for (int i = 0; i < world.SideSize(); ++i) {
    for (int j = 0; j < world.SideSize(); ++j) {

      numNeighbors = CountNeighbors(world,Point2D (i,j));
      if (numNeighbors < 2 || numNeighbors > 3) {
        world.SetNext(Point2D(i,j), false);
      }
      else {
        world.SetNext(Point2D(i,j), true);
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement

  bool self = false;
  int targetY = point.y;
  int targetX = point.x;
  int numNeighbors = 0;


  for (int i = -1; i < 1; ++i) {
    for (int j = -1; j < 1; ++j) {

      if (i == 0 && j == 0) {
        self = true;
      }
      else {
        self = false;
      }

      // Check if self
      if (world.Get(Point2D(targetY+i, targetX + j)) && !self) {
        numNeighbors++;
      }

    }
  }

  return numNeighbors;
}
