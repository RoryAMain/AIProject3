#include "BoardNode.cpp"
#include <vector>

using namespace std;

class MiniMax
{
private:
	int maxDepth = 5;
	int currentDepth;
public:

	MiniMax(int maxDepthIn)
	{
		maxDepth = maxDepthIn;
	}

	void setMaxDepth(int depthIn)
	{
		maxDepth = depthIn;
	}

	int getMaxDepth()
	{
		return maxDepth;
	}

	int getCurrentDepth()
	{
		return currentDepth;
	}

	void setCurrentDepth(int currentDepthIn)
	{
		currentDepth = currentDepthIn;
	}

	bool anyChildrenLeft(BoardNode *parent)
	{
		for (int x = 0; x < 6; x++)
		{
			if (parent->childList[x] != NULL)
			{
				if (!(parent->childList[x]->getVisited()))
				{
					return true;
				}
			}
		}
		return false;
	}

	BoardNode* getBestChild(BoardNode* parent)
	{
		BoardNode* best;
		double bestCost = -INFINITY;
		for (int x = 0; x < 6; x++)
		{
			if (parent->childList[x]->getFitnessCost() > bestCost && !(parent->childList[x]->getVisited()))
			{
				bestCost = parent->getFitnessCost();
				best = parent->childList[x];
			}
			return best;
		}
	}

	BoardNode* getWorstChild(BoardNode* parent)
	{
		BoardNode* worst;
		double worstCost = INFINITY;
		for (int x = 0; x < 6; x++)
		{
			if (parent->childList[x]->getFitnessCost() < worstCost && !(parent->childList[x]->getVisited()))
			{
				worstCost = parent->getFitnessCost();
				worst = parent->childList[x];
			}
			return worst;
		}
	}

	double playMiniMax(BoardNode *parent,vector<int> boardState)
	{
		//For given parent, generate children nodes and their board states.

		while (anyChildrenLeft(parent))
		{
			if (parent->getDepth() == maxDepth + currentDepth)
			{
				return parent->getFitnessCost();
			}
			if (parent->getAlpha() >= parent->getBeta())
			{
				if (parent->getIsMax())
				{
					return parent->getAlpha();
				}
				else
				{
					return parent->getBeta();
				}
			}

			if (parent->getIsMax())
			{
				BoardNode* bestChild = getBestChild(parent);
				bestChild->setVisited(true);
				double tempAlpha = playMiniMax(bestChild, bestChild->board);
				if (tempAlpha > parent->getAlpha())
				{
					parent->setAlpha(tempAlpha);
				}
			}
			else
			{
				BoardNode* worstChild = getWorstChild(parent);
				worstChild->setVisited(true);
				double tempBeta = playMiniMax(worstChild, worstChild->board);
				if (tempBeta < parent->getBeta())
				{
					parent->setBeta(tempBeta);
				}
			}

		}

		if (parent->getIsMax()) {
			return parent->getAlpha();
		}
		else {
			return parent->getBeta();
		}
	}
};