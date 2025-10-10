#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

  // Add bootstrap case : top left to stack
  if (w->GetNodeColor(Point2D (-w->GetSize() / 2,-w->GetSize() / 2)) == Color::DarkGray) {
    stack.emplace_back(-w->GetSize() / 2,-w->GetSize() / 2);
  }

    Point2D top = stack.back();

    // If top has neighbors
    if (!getVisitables(w, top).empty()) {
      w->SetNodeColor(top, Color::CornflowerBlue);

      // getNeighbors
      std::vector<Point2D> neighbors = getVisitables(w, top);
      Point2D nextNeighbor;

      if (neighbors.size() == 1) {
        nextNeighbor = neighbors.front();
      }

      else {
        int randomIndex = rand() % neighbors.size();
        nextNeighbor = neighbors[(randomIndex)];

        // remove wall that will be in that direction
        // Check right
        if (nextNeighbor.x - top.x > 0)
          w->SetEast(top, false);

        // Check left
        if (nextNeighbor.x - top.x < 0)
          w->SetWest(top, false);

        // Check up
        if (nextNeighbor.y - top.y > 0)
          w->SetNorth(top, false);

        // Check down
        if (nextNeighbor.y - top.y < 0)
          w->SetSouth(top, false);


      }

      stack.push_back(nextNeighbor);
    }

    else {
      w->SetNodeColor(top, Color::Black);
      stack.pop_back();
    }



  return !stack.empty();
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this


  if (w->GetNodeColor(p.Up()) == Color::DarkGray) {
    visitables.push_back(p.Up());
}

  if (w->GetNodeColor(p.Right()) == Color::DarkGray) {
    visitables.push_back(p.Right());
}

  if (w->GetNodeColor(p.Down()) == Color::DarkGray) {
    visitables.push_back(p.Down());
}

  if (w->GetNodeColor(p.Right()) == Color::DarkGray) {
    visitables.push_back(p.Right());
}

  return visitables;
}
