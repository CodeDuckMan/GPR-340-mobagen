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
  unordered_set<Point2D> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  Heuristic heuristic;

  unordered_map<Point2D, double> cost_so_far;

  // bootstrap state
  auto startPosition = w->getCat();
  frontier.push({startPosition, 0});
  //frontierSet.insert(startPosition);
  cameFrom[startPosition] = startPosition;
  cost_so_far[startPosition] = 0;

  Point2D goalNode = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  std::vector<Point2D> currentNeighbours;

    auto current = frontier.top();

  while (!frontier.empty()) {

    // get the current from frontier

    // Check if current is goal
    if (current.point == goalNode) {
      break;
    }

    // mark current as visited
    visited.emplace(current.point);

    // getVisitableNeighbours(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    currentNeighbours = w->neighbors(current.point);

    // if neighbor is not valid or has been visited, remove from currentNeighbors
    for (int i = 0; i < currentNeighbours.size(); ++i) {
      if (!w->isValidPosition(currentNeighbours.at(i)) || visited.contains(currentNeighbours.at(i))) {
        currentNeighbours.erase(currentNeighbours.begin() + i);
      }
    }

    // iterate over the neighs:
    for (auto neighbour : currentNeighbours)
    {
      // Create new cost from current cost + the cost from current node to neighhor
      float newCost = cost_so_far[current.point] + 1;

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

    currentNeighbours.clear();
    //frontierSet.erase(current);
    frontier.pop();

    // do this up to find a visitable border and break the loop
    if (cameFrom.contains(Point2D::INFINITE)) {
      break;
    }

  }

  // If we run out of nodes
  if (!cameFrom.contains(goalNode)) {
    return vector<Point2D>();
  }
  else {

    vector<Point2D> finalPath;
    while (current.point != w->getCat()) {
      finalPath.push_back(cameFrom[current.point]);
      current.point = cameFrom[current.point];
    }
    std::reverse(finalPath.begin(), finalPath.end());
    return finalPath;

}
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isn't a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move

}
float Heuristic::EstimateCostNodeBorder(Point2D theNode, int sideSize) {

  return min(sideSize / 2 - abs(theNode.x), sideSize / 2 + abs(theNode.y));
}

float Heuristic::EstimateNodeNodeCost(Point2D fromNode, Point2D targetNode) {

  float dx = abs(static_cast<float>(fromNode.x) - static_cast<float>(targetNode.x));
  float dy = abs(static_cast<float>(fromNode.y) - static_cast<float>(targetNode.y));

  return (dx + dy);

}
