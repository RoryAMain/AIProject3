#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Heuristic {
public:
	double ourGoalBalancer = 1;
	double enemyGoalBalancer = 1;
	double ourPileBalancer = -0.25;
	double enemyPileBalancer = 0.25;
	double beanBalancer = 0.5;

	double getFitnessValue(vector<int> board)
	{
		if (board.size() != 14)
		{
			cout << "Incorrect board size.\n";
			return 0;
		}
		//Points in our goal.
		double ourGoalPoints = board[7] * ourGoalBalancer;
		//Points in enemy goal.
		double enemyGoalPoints = -(board[0]) * enemyGoalBalancer;
		//Piles on our side.
		double ourPilePoints = 0;
		for (int x = 1; x < 7; x++)
		{
			double average = averageBoardValue(1, board);
			if (board[x] > average)
			{
				ourPilePoints =(ourPilePoints + (board[x] - average));
			}
		}
		ourPilePoints = ourPilePoints*ourPileBalancer;
		//Piles on enemy side.
		double enemyPilePoints = 0;
		for (int y = 8; y < 14; y++)
		{
			double average = averageBoardValue(0, board);
			if (board[y] > average)
			{
				enemyPilePoints = ((enemyPilePoints + (board[y]) - average));
			}
		}
		enemyPilePoints = enemyPilePoints*enemyPileBalancer;
		//Beans on our side.
		double ourBeans = 0;
		for (int i = 1; i < 7; i++)
		{
			ourBeans = ourBeans + board[i];
		}
		//Beans on enemy side.
		double enemyBeans = 0;
		for (int j = 8; j < 14; j++)
		{
			enemyBeans = enemyBeans + board[j];
		}
		if (enemyBeans == 0)
		{
			enemyBeans = 0.001;
		}
		double beanProportion = (((ourBeans) / (enemyBeans))-1)*beanBalancer;
		double fitnessValue = ourGoalPoints + enemyGoalPoints + ourPilePoints + enemyPilePoints + beanProportion;
		return fitnessValue;
	}

	double averageBoardValue(bool isOurBoard, vector<int> board)
	{
		double average = 0;
		if (isOurBoard)
		{
			for (int x = 1; x < 7; x++)
			{
				average = average + board[x];
			}
			average = average / 6;
			return average;
		}
		else
		{
			for (int y = 8; y < 14; y++)
			{
				average = average + board[y];
			}
			average = average / 6;
			return average;
		}
	}

};

int main(int argc, char* argv[])
{
	Heuristic test;
	vector<int> board = { 
		//Enemy Goal
		0,
		//Our spots
		3,3,3,3,3,3,
		//Our Goal
		0,
		//Enemy Spots
		3,3,3,3,3,3
	};
	cout << "Board Size: " << board.size() << "\n";
	double fitnessValue = test.getFitnessValue(board);
	cout << "Fitness value: " << fitnessValue << "\n";
	
	system("pause");

	return 0;
}
