#pragma once
#include <iostream>
#include <cstdlib>
#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif VECTOR_H
using namespace std;

class Heuristic {
public:
	double ourGoalBalancer = 1;
	double enemyGoalBalancer = 1;
	double ourPileBalancer = -0.5;
	double enemyPileBalancer = 0.5;
	double beanBalancer = 0.25;

	double getFitnessValue(vector<int> board)
	{
		if (board.size() != 14)
		{
			cout << "Incorrect board size.\n";
			return 0;
		}
		//Points in our goal.
		double ourGoalPoints = board[6] * ourGoalBalancer;
		//Points in enemy goal.
		double enemyGoalPoints = -(board[13]) * enemyGoalBalancer;
		//Piles on our side.
		double ourPilePoints = 0;
		for (int x = 0; x < 6; x++)
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
		for (int y = 6; y < 13; y++)
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
		for (int i = 0; i < 6; i++)
		{
			ourBeans = ourBeans + board[i];
		}
		//Beans on enemy side.
		double enemyBeans = 0;
		for (int j = 6; j < 13; j++)
		{
			enemyBeans = enemyBeans + board[j];
		}
		if (enemyBeans == 0)
		{
			enemyBeans = 0.001;
		}
		double beanProportion = (((ourBeans) / (enemyBeans))-1)*beanBalancer;
		double fitnessValue = ourGoalPoints + enemyGoalPoints + ourPilePoints + enemyPilePoints + beanProportion;
		//cout << fitnessValue << "\n";
		return fitnessValue;
	}

	double averageBoardValue(bool isOurBoard, vector<int> board)
	{
		double average = 0;
		if (isOurBoard)
		{
			for (int x = 0; x < 6; x++)
			{
				average = average + board[x];
			}
			average = average / 6;
			return average;
		}
		else
		{
			for (int y = 7; y < 13; y++)
			{
				average = average + board[y];
			}
			average = average / 6;
			return average;
		}
	}

};