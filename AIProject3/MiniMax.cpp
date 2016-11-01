#pragma once
#include "BoardNode.cpp"
/*
#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif VECTOR_H
*/

using namespace std;

class MiniMax
{
private:
	int maxDepth = 5;
	int currentDepth;

	bool anyChildrenLeft(BoardNode *parent)
	{
		for (int x = 0; x < 6; x++)
		{
			if (parent->childList[x] != NULL)
			{
				if (!(parent->childList[x]->getVisited()) && !(parent->childList[x]->isIllegalMove()))
				{
					return true;
				}
			}
		}
		return false;
	}

	BoardNode* getBestChild(BoardNode* parent)
	{
		BoardNode* best = NULL;
		double bestCost = -INFINITY;
		for (int x = 0; x < 6; x++)
		{
			if (parent->childList[x]->getFitnessCost() > bestCost && !(parent->childList[x]->getVisited()) && !(parent->childList[x]->isIllegalMove()))
			{
				bestCost = parent->getFitnessCost();
				best = parent->childList[x];
			}
		}
		return best;
	}

	BoardNode* getWorstChild(BoardNode* parent)
	{
		BoardNode* worst = NULL;
		double worstCost = INFINITY;
		for (int x = 0; x < 6; x++)
		{
			if (parent->childList[x]->getFitnessCost() < worstCost && !(parent->childList[x]->getVisited()) && !(parent->childList[x]->isIllegalMove()))
			{
				worstCost = parent->getFitnessCost();
				worst = parent->childList[x];
			}
		}
		return worst;
	}

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

	

	double playMiniMax(BoardNode *parent,vector<int> boardState)
	{
		//For given parent, generate children nodes and their board states.
	
		BoardNode firstMove(parent, 1);
		BoardNode secondMove(parent, 2);
		BoardNode thirdMove(parent, 3);
		BoardNode fourthMove(parent, 4);
		BoardNode fifthMove(parent, 5);
		BoardNode sixthMove(parent, 6);

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

	int bestChoice(BoardNode* head)
	{
		BoardNode child0(head, 0);
		BoardNode child1(head, 1);
		BoardNode child2(head, 2);
		BoardNode child3(head, 3);
		BoardNode child4(head, 4);
		BoardNode child5(head, 5);

		double test;
		double maxTest = -INFINITY;
		int choice;


		test = playMiniMax(&child0, child0.board);
		if (test > maxTest)
		{
			maxTest = test;
			choice = 1;
		}
		cout << "Move 0: " << test << "\n";

		test = playMiniMax(&child1, child1.board);
		if (test > maxTest)
		{
			maxTest = test;
			choice = 2;
		}
		cout << "Move 1: " << test << "\n";

		test = playMiniMax(&child2, child2.board);
		if (test > maxTest)
		{
			maxTest = test;
			choice = 3;
		}

		cout << "Move 2: " << test << "\n";

		test = playMiniMax(&child3, child3.board);
		if (test > maxTest)
		{
			maxTest = test;
			choice = 4;
		}

		cout << "Move 3: " << test << "\n";

		test = playMiniMax(&child4, child4.board);
		if (test > maxTest)
		{
			maxTest = test;
			choice = 5;
		}
		cout << "Move 4: " << test << "\n";

		test = playMiniMax(&child5, child5.board);
		if (test > maxTest)
		{
			maxTest = test;
			choice = 6;
		}
		cout << "Move 5: " << test << "\n";

		return choice;
	}

};