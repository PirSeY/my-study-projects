#include <locale.h>
#include "edge.h"
#include "graph.h"
#include "vertex.h"
#include "graph_forms.h"
#include "task_one.h"
#include "vertex_map.h"
#include <iostream>
#include <iomanip>
#include <string>

#include <conio.h>

using namespace std;

void PrintMenuVertex() {
	cout << "\n���� ��������� ������"
		<< "\n1 ��������� �� ������"
		<< "\n2 ��������� �� �����"
		<< "\n3 ������� � ����������"
		<< "\n4 �������� ���"
		<< "\n5 ���������� ���"
		<< "\n6 �������� ������"
		<< "\n7 ���������� ������"
		<< "\n8 �������� ������"
		<< "\n9 �����"
		<< "\n";
}


void vertexIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph, MapVertex<string, Vertex<string, int>*>& mapVertex)
{
	Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator vertexIterator(*graph);
	int key;

	while (true)
	{
		_getch();
		PrintMenuVertex();
		cin >> key;
		switch (key)
		{
		case 1: cout << "\n" << vertexIterator.begin() << "\n";
			break;
		case 2:
			if (vertexIterator.onEnd())
				cout << "\n" << "off" << "\n";
			else
				cout << "\n" << "on" << "\n";
			break;
		case 3: cout << "\n" << ++vertexIterator << "\n";
			break;

		case 4:
			try
			{
				if ((*vertexIterator)->isNameSet() == true)
					cout << "\n��� " << (*vertexIterator)->getName() << "\n";
				else
					cout << "\nfalse" << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}

			break;
		case 5:
		{
			cout << "\n������� ��� " << "\n";
			string name;
			cin >> name;

			bool success;//���� ������� � ������� ����

			try
			{
				if ((*vertexIterator)->isNameSet() == false)
					success = mapVertex.addPair(name, (*vertexIterator));
				else
					success = mapVertex.replaceName((*vertexIterator)->getName(), name);
			}
			catch (int ex)
			{
				success = false;
			}


			try
			{
				if (success)
				{
					(*vertexIterator)->setName(name);
					cout << "true" << "\n";
				}
				else
					cout << "false" << "\n";
			}
			catch (int ex)
			{
				cout << "false" << "\n";
			}


		}
		break;
		case 6:


			try
			{
				if ((*vertexIterator)->isDataSet() == true)
					cout << "\n������ " << (*vertexIterator)->getData() << "\n";
				else
					cout << "\nfalse" << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}

			break;
		case 7:
		{
			cout << "\n������� ������ " << "\n";
			int data;
			cin >> data;
			try
			{
				(*vertexIterator)->setData(data);
				cout << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}

		}
		break;
		case 8:
			try
			{
				cout << "\n" << (*vertexIterator)->index << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}

			break;
		case 9:  return;
		}
	}
}

void PrintMenuEdge() {
	cout << "\n���� ��������� �����"
		<< "\n1 ��������� �� ������"
		<< "\n2 ��������� �� �����"
		<< "\n3 ������� � ����������"
		<< "\n4 �������� ���"
		<< "\n5 ���������� ���"
		<< "\n6 �������� ������"
		<< "\n7 ���������� ������"
		<< "\n8 �������� ������"
		<< "\n9 �����"
		<< "\n";
}

void edgeIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph)
{
	//menu edge iterator	
	Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator edgeIterator(*graph);

	int key;
	while (true)
	{
		_getch();
		PrintMenuEdge();

		cin >> key;
		switch (key)
		{
		case 1: cout << "\n" << edgeIterator.begin() << "\n";
			break;
		case 2:
			if (edgeIterator.onEnd())
				cout << "\n" << "off" << "\n";
			else
				cout << "\n" << "on" << "\n";
			break;
		case 3: cout << "\n" << ++edgeIterator << "\n";
			break;
		case 4:
			try
			{
				if ((*edgeIterator)->isWeightSet() == true)
					cout << "\n��� " << (*edgeIterator)->getWeight() << "\n";
				else
					cout << "\nfalse" << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}

			break;
		case 5:
		{
			cout << "\n������� ��� " << "\n";
			int weight;
			cin >> weight;
			try
			{
				(*edgeIterator)->setWeight(weight);
				cout << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}
		}
		break;
		case 6:
			try
			{
				if ((*edgeIterator)->isDataSet() == true)
					cout << "\n������ " << (*edgeIterator)->getData() << "\n";
				else
					cout << "\nfalse" << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}

			break;
		case 7:
		{
			cout << "\n������� ������ ";
			int data;
			cin >> data;
			try
			{
				(*edgeIterator)->setData(data);
				cout << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}

		}
		break;
		case 8:
		{
			try
			{
				//cout<<"�������� ������"<<"\n";
				cout << "\n" << (*edgeIterator)->v1->index << " " << (*edgeIterator)->v2->index << "\n";
			}
			catch (int ex)
			{
				cout << "\nfalse" << "\n";
			}


		}
		break;

		case 9: return;

		}
	}
}

void PrintMenuOutputEdge() {
	cout << "\n���� ��������� ��������� �����"
		<< "\n1 ��������� �� ������"
		<< "\n2 ��������� �� �����"
		<< "\n3 ������� � ����������"
		<< "\n4 �������� ���"
		<< "\n5 ���������� ���"
		<< "\n6 �������� ������"
		<< "\n7 ���������� ������"
		<< "\n8 �������� ������� �����"
		<< "\n9 ������� ������ �������"
		<< "\n10 ����� � ������� ����"
		<< "\n";
}


void outputEdgeIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph)
{
	int vertexIndex;
	while (true)
	{
		cout << "�������� �������";
		///*
		cin >> vertexIndex;
		if (vertexIndex >= graph->getVertexCount() || graph->getVertexCount() < 0)
			continue;

		Vertex<string, int>* vertex;
		try
		{
			vertex = graph->getVertex(vertexIndex);

		}
		catch (int ex)
		{
			cout << "\nfalse" << "\n";
			continue;
		}
		Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(*graph, *vertex);

		/*cout << "\n���� ��������� ��������� �����"
			<< "\n1 ��������� �� ������"
			<< "\n2 ��������� �� �����"
			<< "\n3 ������� � ����������"
			<< "\n4 �������� ���"
			<< "\n5 ���������� ���"
			<< "\n6 �������� ������"
			<< "\n7 ���������� ������"
			<< "\n8 �������� ������� �����"
			<< "\n9 ������� ������ �������"
			<< "\n10 ����� � ������� ����"
			<< "\n";*/

		int key;
		bool work = true;
		while (work)
		{
			_getch();
			PrintMenuOutputEdge();

			cin >> key;
			switch (key)
			{
			case 1: cout << "\n" << outputEdgeIterator.begin() << "\n";
				break;
			case 2:
				if (outputEdgeIterator.onEnd())
					cout << "\n" << "off" << "\n";
				else
					cout << "\n" << "on" << "\n";
				break;
			case 3: cout << "\n" << ++outputEdgeIterator << "\n";
				break;
			case 4:
				try
				{
					if ((*outputEdgeIterator)->isWeightSet() == true)
						cout << "\n��� " << (*outputEdgeIterator)->getWeight() << "\n";
					else
						cout << "\nfalse" << "\n";
				}
				catch (int ex)
				{
					cout << "\nfalse" << "\n";
				}

				break;
			case 5:
			{
				cout << "\n������� ��� " << "\n";
				int weight;
				cin >> weight;
				try
				{
					(*outputEdgeIterator)->setWeight(weight);
					cout << "\n";
				}
				catch (int ex)
				{
					cout << "\nfalse" << "\n";
				}

			}
			break;
			case 6:
				try
				{
					if ((*outputEdgeIterator)->isDataSet() == true)
						cout << "\n������ " << (*outputEdgeIterator)->getData() << "\n";
					else
						cout << "\nfalse" << "\n";
				}
				catch (int ex)
				{
					cout << "\nfalse" << "\n";
				}

				break;
			case 7:
			{
				cout << "\n������� ������ ";
				int data;
				cin >> data;

				try
				{
					(*outputEdgeIterator)->setData(data);
					cout << "\n";
				}
				catch (int ex)
				{
					cout << "\nfalse" << "\n";
				}


			}
			break;
			case 8:
			{
				try
				{
					//cout<<"�������� ������"<<"\n";
					cout << "\n" << (*outputEdgeIterator)->v1->index << " " << (*outputEdgeIterator)->v2->index << "\n";
				}
				catch (int ex)
				{
					cout << "\nfalse" << "\n";
				}


			}
			break;
			case 9: work = false;
				break;
			case 10: return;
				break;

			}
		}
	}

}

void PrintMenuTaskOne() {
	cout << "\n���� ������� �������"
		<< "\n1 restart"
		<< "\n2 result"
		<< "\n3 �����"
		<< "\n";
}

void taskOneMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph)
{
	TaskOne<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> taskOne(graph);

	int key;
	while (true)
	{
		_getch();
		PrintMenuTaskOne();
		cin >> key;
		switch (key)
		{
		case 1: taskOne.restart();
			break;
		case 2: cout << "\n" << taskOne.getResult() << "\n";
			break;
		case 3: return;

		}
	}
}


void PrintMenu() {
	cout << "\n������� ����" << "\n"
		 << "\n1 - ������� ���� � ���� �������"
		 << "\n2 - ������� ���� � ���� �������"
		 << "\n3 - ������ ��������� ���� ������"
		 << "\n4 - �������� ����� ������"
		 << "\n5 - �������� ����� �����"
		 << "\n6 - �������� ��� �����"
		 << "\n7 - �������� ����� ������������� �����"
		 << "\n8 - �������� ���������� �����������"
		 << "\n9 - ������������� � M-�����"
		 << "\n10 - ������������� � L-�����"
		 << "\n11 - �������� �������"
		 << "\n12 - ������� ������� �� �����"
		 << "\n13 - ������� ������� �� �������"
		 << "\n14 - �������� ����� �� ������"
		 << "\n15 - �������� ����� �� ��������"
		 << "\n16 - ������� ����� �� ������"
		 << "\n17 - ������� ����� �� ��������"
		 << "\n18 - ���� ��������� ������"
		 << "\n19 - ���� ��������� �����"
		 << "\n20 - ���� ��������� ���������"
		 << "\n21 - ���� ������� �������"
		 << "\n";
}


int main(int argc, char* argv[])
{

	Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>* graph =
		new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>(6, 10, false, false);

	MapVertex<string, Vertex<string, int>*> mapVertex;

	setlocale(LC_ALL, "rus");
	
	int key;
	while (true)
	{
		_getch();
		PrintMenu();

		cin >> key;
		switch (key)
		{
		case 1:
		{
			cout << setw(6) << "";
			for (int i = 0;i < graph->getVertexCount();i++)
			{

				cout << setw(6) << "(i" << i;
				if (graph->getVertex(i)->isNameSet() == true)
					cout << "," << graph->getVertex(i)->getName();
				cout << ")";

			}
			cout << "\n\n\n";

			for (int i = 0;i < graph->getVertexCount();i++)
			{
				cout << setw(6) << "(i" << i;
				if (graph->getVertex(i)->isNameSet() == true)
					cout << "," << graph->getVertex(i)->getName();
				cout << ")";

				for (int j = 0;j < graph->getVertexCount();j++)
				{
					if (graph->hasEdge(i, j))
					{
						if (graph->getEdge(i, j)->isWeightSet())
							cout << setw(7) << graph->getEdge(i, j)->getWeight();
						else
							cout << setw(7) << "+ ";

					}
					else
						cout << setw(7) << "- ";
				}
				cout << "\n\n\n";
			}
		}
		break;

		case 2:
		{
			for (int i = 0;i < graph->getVertexCount();i++)
			{
				cout << setw(10) << "(i" << i;
				if (graph->getVertex(i)->isNameSet() == true)
					cout << "," << graph->getVertex(i)->getName();
				cout << ")   ";

				Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator
					outputEdgeIterator(*graph, *(graph->getVertex(i)));

				outputEdgeIterator.begin();
				while (outputEdgeIterator.onEnd() == false)
				{
					int index = 0;
					if ((*outputEdgeIterator)->v1->index != i)
						index = (*outputEdgeIterator)->v1->index;
					else
						index = (*outputEdgeIterator)->v2->index;

					cout << setw(6) << "->(";
					cout << "i" << graph->getVertex(index)->index;
					if (graph->getVertex(index)->isNameSet() == true)
						cout << "," << graph->getVertex(index)->getName();
					if ((*outputEdgeIterator)->isWeightSet())
						cout << "|" << (*outputEdgeIterator)->getWeight();

					cout << ") ";

					++outputEdgeIterator;
				}
				cout << "\n\n\n";
			}
		}
		break;

		case 3:
		{
			//��������� ���� � ��������� �������
			cout << "������� �������� ����� �������, ��������";
			int weightMax;
			int weightMin;
			cin >> weightMin;
			cin >> weightMax;


			//������������� ����
			srand(time(NULL));
			for (int i = 0;i < graph->getVertexCount();i++)
			{
				for (int j = 0;j < graph->getVertexCount();j++)
				{
					if (graph->hasEdge(i, j))
					{
						int weight = rand() % (weightMax - weightMin) + weightMin;
						//������������ ��� �����
						graph->getEdge(i, j)->setWeight(weight);
					}

				}
			}
		}
		break;

		case 4:cout << "\n" << graph->getVertexCount() << "\n";
			break;

		case 5:cout << "\n" << graph->getEdgeCount() << "\n";
			break;

		case 6:
			if (graph->isDirected())
				cout << "\n" << "directed" << "\n";
			else
				cout << "\n" << "not directed" << "\n";
			break;

		case 7:
			if (graph->isDense())
				cout << "\n" << "matrix" << "\n";
			else
				cout << "\n" << "list" << "\n";

			break;

		case 8:
			cout << "\n" << graph->getRatio() << "\n";
			break;

		case 9:
			graph->toDenseGraph();
			break;

		case 10:
			graph->toSparseGraph();
			break;

		case 11:
			try
			{
				graph->insertVertex();
			}
			catch (int ex)
			{
				cout << "false" << "\n";
			}

			break;



		case 12:
		{
			cout << "\n������� ���\n";
			string name;
			cin >> name;
			try
			{
				int index = mapVertex.getData(name)->index;
				mapVertex.delPair(name);
				cout << graph->deleteVertex(index) << "\n";
			}
			catch (int ex)
			{
				cout << false << "\n";
			}
		}
		break;

		case 13:
		{
			cout << "\n������� ������\n";
			int index;
			cin >> index;
			try
			{
				if (graph->getVertex(index)->isNameSet() == true)
				{
					mapVertex.delPair(graph->getVertex(index)->getName());
				}
				cout << graph->deleteVertex(index) << "\n";
			}
			catch (int ex)
			{
				cout << false << "\n";
			}


		}
		break;

		case 14:
		{
			cout << "\n������� ����� ������\n";
			string name1;
			cin >> name1;
			string name2;
			cin >> name2;
			try
			{
				int index1 = mapVertex.getData(name1)->index;
				int index2 = mapVertex.getData(name2)->index;

				graph->insertEdge(index1, index2);
				cout << "\ntrue\n";
			}
			catch (int ex)
			{
				cout << false << "\n";
			}
		}
		break;

		case 15:
		{
			cout << "\n������� ������� ������\n";
			int index1;
			cin >> index1;
			int index2;
			cin >> index2;
			try
			{
				graph->insertEdge(index1, index2);
				cout << "\ntrue\n";
			}
			catch (int ex)
			{
				cout << false << "\n";
			}
		}
		break;

		case 16:
		{
			cout << "\n������� ����� ������\n";
			string name1;
			cin >> name1;
			string name2;
			cin >> name2;

			try
			{
				int index1 = mapVertex.getData(name1)->index;
				int index2 = mapVertex.getData(name2)->index;

				cout << graph->deleteEdge(index1, index2) << "\n";
			}
			catch (int ex)
			{
				cout << false << "\n";
			}

		}
		break;

		case 17:
		{
			cout << "\n������� ������� ������\n";
			int index1;
			cin >> index1;
			int index2;
			cin >> index2;
			cout << graph->deleteEdge(index1, index2) << "\n";

		}
		break;

		case 18:vertexIteratorMenu(graph, mapVertex);
			break;

		case 19:edgeIteratorMenu(graph);
			break;

		case 20:outputEdgeIteratorMenu(graph);
			break;

		case 21:taskOneMenu(graph);
			break;

		}

	}
	int v;
	cin >> v;
}
