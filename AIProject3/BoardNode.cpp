#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "Heuristic.cpp"

using namespace std;

class BoardNode {
private:
	Heuristic heuristicChecker;
	bool isMax;
	bool visited;
	double alpha;
	double beta;
	double fitnessCost;
	int depth;
public:
	vector<int> board;
	BoardNode* parent;
	BoardNode* child0;
	BoardNode* child1;
	BoardNode* child2;
	BoardNode* child3;
	BoardNode* child4;
	BoardNode* child5;
	vector<BoardNode*> childList = { child0,child1,child2,child3,child4,child5 };

	//If this is the first node.
	BoardNode()
	{
		parent = NULL;
		isMax = 1;
		alpha = -INFINITY;
		beta = INFINITY;
		depth = 0;
		visited = true;
		board = {
			//Enemy Goal
			0,
			//Our spots
			3,3,3,3,3,3,
			//Our Goal
			0,
			//Enemy Spots
			3,3,3,3,3,3
		};
		fitnessCost = heuristicChecker.getFitnessValue(board);
	}

	BoardNode(BoardNode* parentIn, BoardNode* thisNode)
	{
		parent = parentIn;
		thisNode = this;
		isMax = !(parent->isMax);
		alpha = parent->alpha;
		beta = parent->beta;
		depth = (parentIn->depth) + 1;
		visited = false;
		//set board based on game playing
		fitnessCost = heuristicChecker.getFitnessValue(board);
	}

	int getDepth()
	{
		return depth;
	}

	void setIsMax(bool maxIn)
	{
		isMax = maxIn;
	}

	bool getIsMax()
	{
		return isMax;
	}

	void setAlpha(double alphaIn)
	{
		alpha = alphaIn;
	}

	double getAlpha()
	{
		return alpha;
	}

	void setBeta(double betaIn)
	{
		beta = betaIn;
	}

	double getBeta()
	{
		return beta;
	}

	bool getVisited()
	{
		return visited;
	}

	void setVisited(bool boolIn)
	{
		visited = boolIn;
	}

	void setFitnessCost(double costIn)
	{
		fitnessCost = costIn;
	}

	double getFitnessCost()
	{
		return fitnessCost;
	}
};