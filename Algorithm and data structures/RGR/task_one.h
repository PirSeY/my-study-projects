#ifndef TASK_ONE_H
#define TASK_ONE_H

/**
*ѕоиск диаметра
*/

#include "graph.h"
#include <queue>
using namespace std;


template <class VertexT, class EdgeT>
class TaskOne
{
private:
	Graph<VertexT, EdgeT>* graph;   //ќбрабатываемый граф
	bool** matrix;                  //ћатрица смежности
	int result;

	int maxDistanceVertex(int vertexIndex)
	{
		for (int i = 0;i < graph->getVertexCount();i++)
		{
			VertexT* vertex = graph->getVertex(i);
			vertex->color = 0;
			vertex->distance = INT_MAX;
		}

		VertexT* vertexPointer = graph->getVertex(vertexIndex);
		vertexPointer->color = 1;
		vertexPointer->distance = 0;

		//создаем очередь из указателей на вершины
		queue<int> vertexIndexQueue;
		vertexIndexQueue.push(vertexIndex);

		//находим рассто€ни€ до всех вершин
		while (!vertexIndexQueue.empty())
		{
			int vertexFirstIndex = vertexIndexQueue.front();
			vertexIndexQueue.pop();
			VertexT* vertexFirstPointer = graph->getVertex(vertexFirstIndex);
			for (int j = 0;j < graph->getVertexCount();j++)
			{
				VertexT* vertexSecondPointer = graph->getVertex(j);
				if (matrix[vertexFirstIndex][j] == true && vertexSecondPointer->color == 0)
				{
					vertexSecondPointer->color = 1;
					vertexSecondPointer->distance = vertexFirstPointer->distance + 1;
					vertexIndexQueue.push(j);
				}
			}
			vertexFirstPointer->color = 2;

		}

		//ищем максимальное из них
		int maxDistance = 0;
		for (int i = 0;i < graph->getVertexCount();i++)
		{
			VertexT* vertex = graph->getVertex(i);
			if (vertex->distance > maxDistance)
				maxDistance = vertex->distance;
		}

		return maxDistance;

	}



public:
	// онструкторы-деструкторы
	TaskOne(Graph<VertexT, EdgeT>* g) : graph(g)
	{
		restart();
	}
	TaskOne(const TaskOne<VertexT, EdgeT>& taskOne)
	{
		graph = taskOne.graph;
		restart();
	}

	void set(Graph<VertexT, EdgeT>* g)
	{
		graph = g;
		restart();
	}

	void restart()
	{
		//—троим матрицу смежности
		matrix = new bool* [graph->getVertexCount()];

		for (int i = 0; i < graph->getVertexCount(); ++i)
		{
			matrix[i] = new bool[graph->getVertexCount()];
			for (int j = 0; j < graph->getVertexCount(); ++j)
			{
				if (graph->hasEdge(i, j))
					matrix[i][j] = true;
				else
					matrix[i][j] = false;
			}
		}

		result = 0;
		for (int i = 0;i < graph->getVertexCount();i++)
		{
			int interMax = maxDistanceVertex(i);
			if (interMax > result)
				result = interMax;
		}

		//освобождаем пам€ть выделенную под матрицу
		for (int i = 0;i < graph->getVertexCount();i++)
			delete[] matrix[i];

		delete[] matrix;

	}

	int getResult()
	{
		return result;
	}
};

#endif // TASK_ONE_H
