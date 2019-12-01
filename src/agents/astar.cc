#include "agents/astar.hh"
#include "utils.hh"

AstarNode::AstarNode(Point2D pos, Point2D target, AstarNode* parent)
  : pos_(pos),
  parent_(parent)
{
  if(parent_)
    distFromStart_ = parent_->distFromStart_ + 1;
  else
    distFromStart_ = 0;
  distToGoal_ = pos_.dist(target);
  totalDist_ = distFromStart_ + distToGoal_;
}

SortedList::SortedList(AstarNode* top)
{
  SortedListNode* n = new SortedListNode;
  n->astarNode_ = top;
  n->next_ = nullptr;
  top_ = n;
}

void SortedList::print()
{
  std::cout << "sortedList: ";
  SortedListNode* n = top_;
  while(n)
  {
    n->astarNode_->pos_.print();
    n = n->next_;
  }
  std::cout << std::endl;
}

void SortedList::insertSorted(AstarNode* newNode)
{
  SortedListNode* n = new SortedListNode;
  n->astarNode_ = newNode;

  SortedListNode* currentNode = top_;

  if(not top_ or newNode->totalDist_ < currentNode->astarNode_->totalDist_)
  {
    top_ = n;
    n->next_ = currentNode;
    return;
  }

  while(currentNode and currentNode->next_)
  {
    if(newNode->totalDist_ < currentNode->astarNode_->totalDist_
        and newNode->totalDist_ >= currentNode->next_->astarNode_->totalDist_)
    {
      if(newNode->pos_.x == currentNode->next_->astarNode_->pos_.x
          and newNode->pos_.y == currentNode->next_->astarNode_->pos_.y)
      {
        return;
      }
      n->next_ = currentNode->next_;
      currentNode->next_ = n;
      return;
    }
    currentNode = currentNode->next_;
  }

  n ->next_ = nullptr;
  currentNode->next_ = n;
}

SortedListNode* SortedList::pop()
{
  if(top_)
  {
    SortedListNode* previousTop = top_;
    top_ = top_->next_;
    return previousTop;
  }
  return top_;
}

direction astar(Map& map, Point2D start, Point2D target)
{
  bool targetReached = false;
  if(start == target)
    targetReached = true;

  AstarNode* startNode = new AstarNode(start, target, nullptr);
  SortedList nodesToVisit(startNode);
  std::vector<Point2D> visitedNodes;
  while (nodesToVisit.top_ and not targetReached)
  {
    SortedListNode* currentNode = nodesToVisit.pop();
    visitedNodes.push_back(currentNode->astarNode_->pos_);
    Point2D p = currentNode->astarNode_->pos_;
    std::vector<Point2D> neighbors;
    Point2D pUp(p.x,p.y-1);
    Point2D pDown(p.x,p.y+1);
    Point2D pRight(p.x+1,p.y);
    Point2D pLeft(p.x-1,p.y);
    neighbors.push_back(pUp);
    neighbors.push_back(pDown);
    neighbors.push_back(pRight);
    neighbors.push_back(pLeft);
    for (size_t i = 0; i < neighbors.size(); i++)
    {
      if(not pointInVector(visitedNodes, neighbors[i])
          and (map.get(neighbors[i]) == status::empty or map.get(neighbors[i]) == status::apple))
      { 
        AstarNode* nodeToInsert = new AstarNode(neighbors[i], target, currentNode->astarNode_);
        nodesToVisit.insertSorted(nodeToInsert);
        if(neighbors[i] == target)
        {
          targetReached = true;
          break;
        }
      }
    }
    if (targetReached)
    {
      AstarNode* targetNode = nodesToVisit.top_->astarNode_;
      while(targetNode)
      {
        if(targetNode->parent_->parent_)
          targetNode = targetNode->parent_;
        else
        {
          return start.directionToGo(targetNode->pos_);
        }
      }
    }
  }
}
