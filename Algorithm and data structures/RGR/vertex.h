#ifndef VERTEX_H
#define VERTEX_H

/**
*Класс вершины графа
*/

template <class NameT, class DataT>
class Vertex {
	NameT name;     //Имя вершины
	DataT data;     //Данные вершины
	bool nameSet, dataSet;
public:
	int index;//индекс вершины
	int color;
	int distance;


	//Конструкторы
	Vertex() : nameSet(false), dataSet(false)
	{
		color = 0;//белая
		distance = INT_MAX;
	}
	Vertex(NameT name, DataT data) : name(name), data(data), nameSet(true), dataSet(true)
	{
		color = 0;//белая
		distance = INT_MAX;
	}

	//Установка, получение имени и данных
	void setName(NameT name) { this->name = name; nameSet = true; }
	void setData(DataT data) { this->data = data; dataSet = true; }
	NameT getName() { return name; }
	DataT getData() { return data; }
	bool isNameSet() { return nameSet; }
	bool isDataSet() { return dataSet; }
};

#endif // VERTEX_H
