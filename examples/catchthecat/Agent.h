#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
};

class Heuristic {

  Point2D goalNode = {0,0};
  float costD = 0;

  public:

  void SetGoalNode(const Point2D& newGoal) {goalNode = newGoal;};
  Point2D GetGoalNode() const { return goalNode; }

  void SetCostD(float newCostD) { costD = newCostD; }
  float GetCostD() const { return costD; }


  float EstimateCostNodeBorder(Point2D theNode, int sideSize);

  float EstimateCost(const Point2D& fromNode){ return EstimateNodeNodeCost(fromNode,goalNode); }

  float EstimateNodeNodeCost(Point2D fromNode, Point2D targetNode);

};

#endif  // AGENT_H
