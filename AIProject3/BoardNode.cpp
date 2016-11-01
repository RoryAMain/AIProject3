#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif VECTOR_H
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
	bool illegalMove;
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
		illegalMove = false;
		board = {
			//Our spots
			3,3,3,3,3,3,
			//Our Goal
			0,
			//Enemy Spots
			3,3,3,3,3,3,
			//Enemy Goal
			0
		};
		fitnessCost = heuristicChecker.getFitnessValue(board);
	}

	BoardNode(BoardNode* parentIn, int moveNumber)
	{
		parent = parentIn;
		isMax = !(parent->isMax);
		alpha = parent->alpha;
		beta = parent->beta;
		depth = (parentIn->depth) + 1;
		visited = false;
		illegalMove = false;
		switch (moveNumber)
		{
		case 1:
		case 7:
			parent->child0 = this;
			break;
		case 2:
		case 8:
			parent->child1 = this;
			break;
		case 3:
		case 9:
			parent->child2 = this;
			break;
		case 4:
		case 10:
			parent->child3 = this;
			break;
		case 5:
		case 11:
			parent->child4 = this;
			break;
		case 6:
		case 12:
			parent->child5 = this;
			break;
		default:
			cout << "Invalid Number\n";
		}

		if (!isMax)
		{
			moveNumber = moveNumber + 6;
		}

		parent->updateChildList();

		int tempArr[14];
		copy(parent->board.begin(), parent->board.end(), tempArr);
	
		string playerTurn;
		if (isMax)
		{
			playerTurn = "SOUTH";
		}
		else
		{
			playerTurn = "NORTH";
		}

		board = predict(tempArr, playerTurn, moveNumber);
		fitnessCost = heuristicChecker.getFitnessValue(board);
	}

	void updateChildList()
	{
		childList= { child0,child1,child2,child3,child4,child5 };
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

	bool isIllegalMove()
	{
		return illegalMove;
	}

	void setIllegalMove(bool boolIn)
	{
		illegalMove = boolIn;
	}
	
	vector<int> predict(int board[], string playerTurn, int chosenCupIn)
	{
		int handfull;
		int currentcup;
		int otherBoard[14];
		int chosencup;
		vector<int> illegal{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		for (int i = 0; i < 14; i++)
		{
			otherBoard[i] = board[i];
		}


		while (true) {
			//cin >> chosencup; //takes in the cup number from player
			// You might want to add an if statement concerning the above line so that it applies only to NORTH
			//below is error checking in case we have clumsy fingers
			chosencup = chosenCupIn;
			if (chosencup < 1 || chosencup > 12)
			{
				//cout << "Please enter a valid move." << endl;
				//cin.clear();
				//cin.ignore(10000, '\n');
				illegalMove = true;
				return illegal;
			}
			else if (chosencup < 7 && otherBoard[chosencup - 1] == 0)
			{
				//cout << "You can't take from there. There are no seeds." << endl;
				//cin.clear();
				//cin.ignore(10000, '\n');
				illegalMove = true;
				return illegal;
			}
			else if (otherBoard[chosencup] == 0 && chosencup >6)
			{
				//cout << "You can't take from there. There are no seeds." << endl;
				//cin.clear();
				//cin.ignore(10000, '\n');
				illegalMove = true;
				return illegal;
			}
			else
			{
				//all cups that are before the SOUTH capture cup counts starting from 0
				//So when the player inputs a number, it's decremented by 1 to match normal conventions
				if (chosencup < 7)
					chosencup--;
				break;
			}
		}

		currentcup = chosencup;
		//taking the handful and then emptying the pit
		handfull = otherBoard[chosencup];
		otherBoard[chosencup] = 0;

		while (handfull != 0)
		{
			//traversing board
			currentcup++;
			if (playerTurn == "NORTH" && currentcup == 6) {}//NORTH does not put anything in SOUTH pit
			else if (playerTurn == "SOUTH" && currentcup == 13) {}//SOUTH does not put anything in NORTH pit
			else if (currentcup == 14)
			{
				//This is when you got to loop back to the beginning once reaching the end of the array
				currentcup = 0;
				otherBoard[currentcup]++;
				handfull--;
			}
			else
			{
				//drop seed
				otherBoard[currentcup]++;
				handfull--;
			}

			//capture
			if (playerTurn == "SOUTH" && handfull == 0 && currentcup < 6 && otherBoard[currentcup] == 1)
			{
				//SOUTH drops seed in empty pit on SOUTH side
				switch (currentcup) {
				case 0:
					otherBoard[6] = otherBoard[6] + otherBoard[12];
					otherBoard[12] = 0;
					break;
				case 1:
					otherBoard[6] = otherBoard[6] + otherBoard[11];
					otherBoard[11] = 0;
					break;
				case 2:
					otherBoard[6] = otherBoard[6] + otherBoard[10];
					otherBoard[10] = 0;
					break;
				case 3:
					otherBoard[6] = otherBoard[6] + otherBoard[9];
					otherBoard[9] = 0;
					break;
				case 4:
					otherBoard[6] = otherBoard[6] + otherBoard[8];
					otherBoard[8] = 0;
					break;
				default:
					otherBoard[6] = otherBoard[6] + otherBoard[7];
					otherBoard[7] = 0;
					break;
				}
			}
			else if (playerTurn == "NORTH" && handfull == 0 && currentcup > 6 && currentcup != 13 && otherBoard[currentcup] == 1) {
				//NORTH drops seed into empty pit on NORTH side
				switch (currentcup) {
				case 7:
					otherBoard[13] = otherBoard[13] + otherBoard[5];
					otherBoard[5] = 0;
					break;
				case 8:
					otherBoard[13] = otherBoard[13] + otherBoard[4];
					otherBoard[4] = 0;
					break;
				case 9:
					otherBoard[13] = otherBoard[13] + otherBoard[3];
					otherBoard[3] = 0;
					break;
				case 10:
					otherBoard[13] = otherBoard[13] + otherBoard[2];
					otherBoard[2] = 0;
					break;
				case 11:
					otherBoard[13] = otherBoard[13] + otherBoard[1];
					otherBoard[1] = 0;
					break;
				default:
					otherBoard[13] = otherBoard[13] + otherBoard[0];
					otherBoard[0] = 0;
					break;
				}
			}
		}
		vector<int> temp(begin(otherBoard), end(otherBoard));
		return temp;
	}
};
/*
int main()
{
	BoardNode head;
	for (int x = 0; x < 14; x++)
	{
		//cout << head.board[x];
	}
	//cout << "\n";

	BoardNode child(&head, head.child0, 1);
	for (int x = 0; x < 14; x++)
	{
		cout << child.board[x] << " ";
	}
	cout << "\n";
	system("pause");
}*/