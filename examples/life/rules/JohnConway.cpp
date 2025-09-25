#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

  int numNeighbors = 0;
  bool currentCellState = false;
  for (int i = 0; i < world.SideSize(); ++i) {
    for (int j = 0; j < world.SideSize(); ++j) {

      numNeighbors = CountNeighbors(world,Point2D (i,j));

      currentCellState = world.Get(Point2D(i, j));

      if (((numNeighbors == 2 || numNeighbors == 3) && currentCellState) || (numNeighbors == 3 && !currentCellState)) {
        world.SetNext(Point2D(i,j), true);
      }
      else {
        world.SetNext(Point2D(i,j), false);
      }
      numNeighbors =0;
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement

  int targetY = point.y;
  int targetX = point.x;
  int numNeighbors = 0;


  for (int i = -1; i < 2; ++i) {
    for (int j = -1; j < 2; ++j) {

      // Check neighbor state and if self
      if (world.Get(Point2D(targetX + i, targetY + j)) && (i != 0 || j != 0)) {
        numNeighbors++;
      }

    }
  }

  return numNeighbors;
}
