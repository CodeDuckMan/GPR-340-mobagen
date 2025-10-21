#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"


#include <algorithm>
using namespace std;

struct Point2DWithPriority {
  Point2D point;
  int priority;

  // reverse the comparison

  bool operator<(const Point2DWithPriority &other) const {
    return priority > other.priority;
  }
};


std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<Point2DWithPriority> frontier;                   // to store next ones to visit
  //unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  Heuristic heuristic;

  unordered_map<Point2D, double> cost_so_far;

  // bootstrap state
  auto startPosition = w->getCat();
  frontier.push({startPosition, 0});
  //frontierSet.insert(startPosition);
  cameFrom[startPosition] = startPosition;
  cost_so_far[startPosition] = 0;

  Point2D goalNode = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points




  while (!frontier.empty()) {

    // get the current from frontier
    auto current = frontier.top();

    frontier.pop();



    // Check if current is goal
    if (w->catWinsOnSpace(current.point)) {
      goalNode = current.point;
      break;
    }

    // mark current as visited

    // getVisitableNeighbours(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> currentNeighbours = w->getVisitableNeighbors(current.point);


    // iterate over the neighs:
    for (auto neighbour : currentNeighbours)
    {

      if (cameFrom.contains(neighbour)) {
        continue;
      }

      // Create new cost from current cost + the cost from current node to neighhor
      double newCost = cost_so_far[current.point] + 1;

      // If cost_so_far does not contain neighbor or if the new cost is lower than the neighbors current cost
      if (!cost_so_far.contains(neighbour) || newCost < cost_so_far[neighbour] ){

        cost_so_far[neighbour] = newCost;
      }

      float priority = newCost + heuristic.EstimateCostNodeBorder(neighbour, w->getWorldSideSize());

      // enqueue the neighbors to frontier and frontierset
      frontier.emplace(neighbour, priority);
      //frontierSet.insert(neighbour);
      cameFrom[neighbour] = current.point;

    }

    //frontierSet.erase(current);

  }

  // If we run out of nodes
  if (!cameFrom.contains(goalNode)) {
    return {};
  }
  else {
    vector<Point2D> finalPath;
    Point2D current = goalNode;
    finalPath.push_back(current);

    while (cameFrom[current] != w->getCat()) {

      finalPath.push_back(cameFrom[current]);
      current = cameFrom[current];
    }
    ranges::reverse(finalPath);
    return finalPath;

}
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isn't a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move

}
float Heuristic::EstimateCostNodeBorder(Point2D theNode, int sideSize) {

  return min(static_cast<float>(sideSize) / 2 - abs(theNode.x), static_cast<float>(sideSize) / 2 + abs(theNode.y));
}

float Heuristic::EstimateNodeNodeCost(Point2D fromNode, Point2D targetNode) {

  float dx = abs(static_cast<float>(fromNode.x) - static_cast<float>(targetNode.x));
  float dy = abs(static_cast<float>(fromNode.y) - static_cast<float>(targetNode.y));

  if (std::sin(dx) == std::sin(dy)) {
    return (dx + dy);
  }

  return max(dx, dy);

}
